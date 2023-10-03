/*
 * ValveCaster audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "PluginValveCaster.hpp"
#include "ValveCaster.cc"
#include "ValveCasterBooster.cc"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginValveCaster::PluginValveCaster()
    : Plugin(paramCount, 0, 0),
      srChanged(false),
      needs_ramp_down(false),
      needs_ramp_up(false),
      bypassed(false),
      bypass_(2),
      boost_(2),
      needs_boost_down(false),
      needs_boost_up(false),
      boost_is(false),
      dsp(valvecaster::plugin()),
      dspb(valvecasterbooster::plugin())
{
    for (unsigned p = 0; p < paramCount; ++p) {
        Parameter param;
        initParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

PluginValveCaster::~PluginValveCaster() {
    dsp->del_instance(dsp);
    dspb->del_instance(dspb);
}

// -----------------------------------------------------------------------
// Init

void PluginValveCaster::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= paramCount)
        return;

    switch (index) {
        case BYPASS:
            parameter.name = "Bypass";
            parameter.shortName = "Bypass";
            parameter.symbol = "BYPASS";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 1.0f;
            parameter.designation = kParameterDesignationBypass;
            parameter.hints = kParameterIsAutomatable|kParameterIsBoolean;
            break;
        case GAIN:
            parameter.name = "Gain";
            parameter.shortName = "Gain";
            parameter.symbol = "GAIN";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.5f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case TONE:
            parameter.name = "Tone";
            parameter.shortName = "Tone";
            parameter.symbol = "TONE";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.5f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case VOLUME:
            parameter.name = "Volume";
            parameter.shortName = "Volume";
            parameter.symbol = "VOLUME";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.5f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case BOOST:
            parameter.name = "Boost";
            parameter.shortName = "Boost";
            parameter.symbol = "BOOST";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomatable|kParameterIsBoolean;
            break;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginValveCaster::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;
    srChanged = true;
    activate();
    srChanged = false;
}

/**
  Get the current value of a parameter.
*/
float PluginValveCaster::getParameterValue(uint32_t index) const {
    //fprintf(stderr, "getParameterValue %i %f\n", index,fParams[index]);
    return fParams[index];
}

/**
  Change a parameter value.
*/
void PluginValveCaster::setParameterValue(uint32_t index, float value) {
    fParams[index] = value;
    //fprintf(stderr, "setParameterValue %i %f\n", index,value);
    dsp->connect(index, value);
    dspb->connect(index, value);
}

void PluginValveCaster::setOutputParameterValue(uint32_t index, float value)
{
    fParams[index] = value;
    //fprintf(stderr, "setOutputParameterValue %i %f\n", index,value);
}

// -----------------------------------------------------------------------
// Process

void PluginValveCaster::activate() {
    // plugin is activated
    fSampleRate = getSampleRate();
    ramp_down_step = 32 * (256 * fSampleRate) / 48000; 
    ramp_up_step = ramp_down_step;
    ramp_down = ramp_down_step;
    ramp_up = 0.0;
    boost_down = ramp_down_step;
    boost_up = 0.0;
    dsp->init((uint32_t)fSampleRate);
    dspb->init((uint32_t)fSampleRate);
}

void PluginValveCaster::run(const float** inputs, float** outputs,
                              uint32_t frames) {

    if (srChanged) return;
    // get the left and right audio inputs
    const float* const inpL = inputs[0];
   // const float* const inpR = inputs[1];

    // get the left and right audio outputs
    float* const outL = outputs[0];
   // float* const outR = outputs[1];

    // do inplace processing on default
    if(outL != inpL)
        memcpy(outL, inpL, frames*sizeof(float));

    // working buffer
    float buf[frames];
    memcpy(buf, inpL, frames*sizeof(float));

    // check if booster is enabled
    if (boost_ != static_cast<uint32_t>(fParams[BOOST])) {
        boost_ = static_cast<uint32_t>(fParams[BOOST]);
        if (boost_) {
            needs_boost_up = true;
            needs_boost_down = false;
        } else {
            needs_boost_down = true;
            needs_boost_up = false;
        }
    }
    
    // booster buffer
    float buf1[frames];
    if (needs_boost_down || needs_boost_up) {
         memcpy(buf1, inpL, frames*sizeof(float));
    }
    
    // check if bypass is pressed
    if (bypass_ != static_cast<uint32_t>(fParams[BYPASS])) {
        bypass_ = static_cast<uint32_t>(fParams[BYPASS]);
        if (!bypass_) {
            needs_ramp_down = true;
            needs_ramp_up = false;
        } else {
            needs_ramp_down = false;
            needs_ramp_up = true;
            bypassed = false;
        }
    }

    // bypass buffer
    float buf0[frames];
    if (needs_ramp_down || needs_ramp_up) {
         memcpy(buf0, inpL, frames*sizeof(float));
    }

    if (!bypassed) {
        if (boost_is) dspb->compute(frames, buf, buf);

        if (needs_boost_down) {
            float fade = 0;
            for (uint32_t i=0; i<frames; i++) {
                if (boost_down >= 0.0) {
                --boost_down; 
                }
                fade = MAX(0.0,boost_down) /ramp_down_step ;
                buf[i] = buf[i] * fade + buf1[i] * (1.0 - fade);
            }

            if (boost_down <= 0.0) {
                // when boosted down, clear buffer from dspb
                dspb->clear_state_f();
                needs_boost_down = false;
                boost_is = false;
                boost_down = ramp_down_step;
                boost_up = 0.0;
            } else {
                boost_up = boost_down;
            }

        } else if (needs_boost_up) {
            boost_is = true;
            float fade = 0;
            for (uint32_t i=0; i<frames; i++) {
                if (boost_up < ramp_up_step) {
                ++boost_up ;
                }
                fade = MIN(ramp_up_step,boost_up) /ramp_up_step ;
                buf[i] = buf[i] * fade + buf1[i] * (1.0 - fade);
            }

            if (boost_up >= ramp_up_step) {
                needs_boost_up = false;
                boost_up = 0.0;
                boost_down = ramp_down_step;
            } else {
                boost_down = boost_up;
            }
        }
        dsp->compute(frames, buf, buf);
    }
    // check if ramping is needed
    if (needs_ramp_down) {
        float fade = 0;
        for (uint32_t i=0; i<frames; i++) {
            if (ramp_down >= 0.0) {
                --ramp_down; 
            }
            fade = MAX(0.0,ramp_down) /ramp_down_step ;
            outL[i] = buf[i] * fade + buf0[i] * (1.0 - fade);
        }
        if (ramp_down <= 0.0) {
            // when ramped down, clear buffer from dsp
            dsp->clear_state_f();
            needs_ramp_down = false;
            bypassed = true;
            ramp_down = ramp_down_step;
            ramp_up = 0.0;
        } else {
            ramp_up = ramp_down;
        }
    } else if (needs_ramp_up) {
        float fade = 0;
        for (uint32_t i=0; i<frames; i++) {
            if (ramp_up < ramp_up_step) {
                ++ramp_up ;
            }
            fade = MIN(ramp_up_step,ramp_up) /ramp_up_step ;
            outL[i] = buf[i] * fade + buf0[i] * (1.0 - fade);
        }
        if (ramp_up >= ramp_up_step) {
            needs_ramp_up = false;
            ramp_up = 0.0;
            ramp_down = ramp_down_step;
        } else {
            ramp_down = ramp_up;
        }
    } else {
        memcpy(outL, buf, frames*sizeof(float));
    }
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginValveCaster();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

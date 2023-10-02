/*
 * TubeScreamer audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "PluginTubeScreamer.hpp"
#include "TubeScreamer.cc"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginTubeScreamer::PluginTubeScreamer()
    : Plugin(paramCount, 0, 0),
      srChanged(false),
      needs_ramp_down(false),
      needs_ramp_up(false),
      bypassed(false),
      bypass_(2),
      dsp(tubescreamer::plugin())
{
    for (unsigned p = 0; p < paramCount; ++p) {
        Parameter param;
        initParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

PluginTubeScreamer::~PluginTubeScreamer() {
    dsp->del_instance(dsp);
}

// -----------------------------------------------------------------------
// Init

void PluginTubeScreamer::initParameter(uint32_t index, Parameter& parameter) {
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
        case LEVEL:
            parameter.name = "Level";
            parameter.shortName = "Level";
            parameter.symbol = "LEVEL";
            parameter.ranges.min = -20.0f;
            parameter.ranges.max = 4.0f;
            parameter.ranges.def = -16.0f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case TONE:
            parameter.name = "Tone";
            parameter.shortName = "Tone";
            parameter.symbol = "TONE";
            parameter.ranges.min = 100.0f;
            parameter.ranges.max = 1000.0f;
            parameter.ranges.def = 400.0f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case DRIVE:
            parameter.name = "Drive";
            parameter.shortName = "Drive";
            parameter.symbol = "DRIVE";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.5f;
            parameter.hints = kParameterIsAutomatable;
            break;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginTubeScreamer::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;
    srChanged = true;
    activate();
    srChanged = false;
}

/**
  Get the current value of a parameter.
*/
float PluginTubeScreamer::getParameterValue(uint32_t index) const {
    //fprintf(stderr, "getParameterValue %i %f\n", index,fParams[index]);
    return fParams[index];
}

/**
  Change a parameter value.
*/
void PluginTubeScreamer::setParameterValue(uint32_t index, float value) {
    fParams[index] = value;
    //fprintf(stderr, "setParameterValue %i %f\n", index,value);
    dsp->connect(index, value);
}

void PluginTubeScreamer::setOutputParameterValue(uint32_t index, float value)
{
    fParams[index] = value;
    //fprintf(stderr, "setOutputParameterValue %i %f\n", index,value);
}

// -----------------------------------------------------------------------
// Process

void PluginTubeScreamer::activate() {
    // plugin is activated
    fSampleRate = getSampleRate();
    ramp_down_step = 32 * (256 * fSampleRate) / 48000; 
    ramp_up_step = ramp_down_step;
    ramp_down = ramp_down_step;
    ramp_up = 0.0;
    dsp->init((uint32_t)fSampleRate);
}

void PluginTubeScreamer::run(const float** inputs, float** outputs,
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

    float buf0[frames];
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

    if (needs_ramp_down || needs_ramp_up) {
         memcpy(buf0, inpL, frames*sizeof(float));
    }
    if (!bypassed) {
        dsp->compute(frames, outL, outL);
    }
    // check if ramping is needed
    if (needs_ramp_down) {
        float fade = 0;
        for (uint32_t i=0; i<frames; i++) {
            if (ramp_down >= 0.0) {
                --ramp_down; 
            }
            fade = MAX(0.0,ramp_down) /ramp_down_step ;
            outL[i] = outL[i] * fade + buf0[i] * (1.0 - fade);
        }
        if (ramp_down <= 0.0) {
            // when ramped down, clear buffer from dsp
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
            outL[i] = outL[i] * fade + buf0[i] * (1.0 - fade);
        }
        if (ramp_up >= ramp_up_step) {
            needs_ramp_up = false;
            ramp_up = 0.0;
            ramp_down = ramp_down_step;
        } else {
            ramp_down = ramp_up;
        }
    }
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginTubeScreamer();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

/*
 * MetalTone audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "resampler.cc"
#include "resampler-table.cc"
#include "zita-resampler/resampler.h"
#include "gx_resampler.cc"

#include "PluginMetalTone.hpp"
#include "MetalTone_pre.cc"
#include "MetalTone_dist.cc"
#include "MetalTone_post.cc"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginMetalTone::PluginMetalTone()
    : Plugin(paramCount, 0, 0),
      dsp(metaltone_pre::plugin()),
      dspd(metaltone_dist::plugin()),
      dspp(metaltone_post::plugin())
{
    for (unsigned p = 0; p < paramCount; ++p) {
        Parameter param;
        initParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

PluginMetalTone::~PluginMetalTone() {
    dsp->del_instance(dsp);
    dspd->del_instance(dspd);
    dspp->del_instance(dspp);
}

// -----------------------------------------------------------------------
// Init

void PluginMetalTone::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= paramCount)
        return;

    switch (index) {
        case DIST:
            parameter.name = "Dist";
            parameter.shortName = "Dist";
            parameter.symbol = "DIST";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case HIGH:
            parameter.name = "High";
            parameter.shortName = "High";
            parameter.symbol = "HIGH";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.5f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case LEVEL:
            parameter.name = "Level";
            parameter.shortName = "Level";
            parameter.symbol = "LEVEL";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.3f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case LOWS:
            parameter.name = "Low";
            parameter.shortName = "Low";
            parameter.symbol = "LOWS";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.5f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case MIDFREQ:
            parameter.name = "MidFreq";
            parameter.shortName = "MidFreq";
            parameter.symbol = "MIDFREQ";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.5f;
            parameter.hints = kParameterIsAutomatable;
            break;
        case MIDDLE:
            parameter.name = "Middle";
            parameter.shortName = "Middle";
            parameter.symbol = "MIDDLE";
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
void PluginMetalTone::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;
}

/**
  Get the current value of a parameter.
*/
float PluginMetalTone::getParameterValue(uint32_t index) const {
    //fprintf(stderr, "getParameterValue %i %f\n", index,fParams[index]);
    return fParams[index];
}

/**
  Change a parameter value.
*/
void PluginMetalTone::setParameterValue(uint32_t index, float value) {
    fParams[index] = value;
    //fprintf(stderr, "setParameterValue %i %f\n", index,value);
    dsp->connect(index, value);
    dspd->connect(index, value);
    dspp->connect(index, value);
}

void PluginMetalTone::setOutputParameterValue(uint32_t index, float value)
{
    fParams[index] = value;
    //fprintf(stderr, "setOutputParameterValue %i %f\n", index,value);
}

// -----------------------------------------------------------------------
// Process

void PluginMetalTone::activate() {
    // plugin is activated
    fSampleRate = getSampleRate();
    dsp->init((uint32_t)fSampleRate);
    dspd->init((uint32_t)fSampleRate);
    dspp->init((uint32_t)fSampleRate);
}

void PluginMetalTone::run(const float** inputs, float** outputs,
                              uint32_t frames) {

    // get the left and right audio inputs
    const float* const inpL = inputs[0];
   // const float* const inpR = inputs[1];

    // get the left and right audio outputs
    float* const outL = outputs[0];
   // float* const outR = outputs[1];

    // do inplace processing on default
    if(outL != inpL)
        memcpy(outL, inpL, frames*sizeof(float));

    dsp->compute(frames, outL, outL);
    dspd->compute(frames, outL, outL);
    dspp->compute(frames, outL, outL);
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginMetalTone();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

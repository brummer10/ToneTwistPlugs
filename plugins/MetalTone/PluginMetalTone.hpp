/*
 * MetalTone audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef PLUGIN_METALTONE_H
#define PLUGIN_METALTONE_H

#include "DistrhoPlugin.hpp"


template<class T> inline T mydsp_faustpower2_f(T x) {return (x * x);}
template<class T> inline T mydsp_faustpower3_f(T x) {return ((x * x) * x);}
template<class T> inline T mydsp_faustpower4_f(T x) {return (((x * x) * x) * x);}
template<class T> inline T mydsp_faustpower5_f(T x) {return ((((x * x) * x) * x) * x);}
template<class T> inline T mydsp_faustpower6_f(T x) {return (((((x * x) * x) * x) * x) * x);}

#define always_inline inline __attribute__((__always_inline__))

#include "MetalTone_pre.hpp"
#include "MetalTone_dist.hpp"
#include "MetalTone_post.hpp"

START_NAMESPACE_DISTRHO

#ifndef MIN
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#endif

#ifndef MAX
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#endif

#ifndef CLAMP
#define CLAMP(v, min, max) (MIN((max), MAX((min), (v))))
#endif

#ifndef DB_CO
#define DB_CO(g) ((g) > -90.0f ? powf(10.0f, (g) * 0.05f) : 0.0f)
#endif

// -----------------------------------------------------------------------

class PluginMetalTone : public Plugin {
public:
    enum Parameters {
        DIST = 0, 
        HIGH, 
        LEVEL, 
        LOWS, 
        MIDFREQ, 
        MIDDLE,
        paramCount
    };

    PluginMetalTone();

    ~PluginMetalTone();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override {
        return "MetalTone";
    }

    const char* getDescription() const override {
        return "";
    }

    const char* getMaker() const noexcept override {
        return "brummer";
    }

    const char* getHomePage() const override {
        return "https://github.com/brummer10/ToneTwistPlugs";
    }

    const char* getLicense() const noexcept override {
        return "https://spdx.org/licenses/GPL-2.0-or-later";
    }

    uint32_t getVersion() const noexcept override {
        return d_version(0, 1, 3);
    }

    // Go to:
    //
    // http://service.steinberg.de/databases/plugin.nsf/plugIn
    //
    // Get a proper plugin UID and fill it in here!
    int64_t getUniqueId() const noexcept override {
        return d_cconst('a', 'b', 'c', 'd');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;
    void loadProgram(uint32_t index) override;

    void setOutputParameterValue(uint32_t index, float value);

    // -------------------------------------------------------------------
    // Optional

    // Optional callback to inform the plugin about a sample rate change.
    void sampleRateChanged(double newSampleRate) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;

    void run(const float**, float** outputs, uint32_t frames) override;


    // -------------------------------------------------------------------

private:
    float           fParams[paramCount];
    double          fSampleRate;
    // pointer to dsp class
    metaltone_pre::Dsp* dsp;
    metaltone_dist::Dsp* dspd;
    metaltone_post::Dsp* dspp;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginMetalTone)
};

struct Preset {
    const char* name;
    float params[PluginMetalTone::paramCount];
};

const Preset factoryPresets[] = {
    {
        "Default",  // preset name
        {0.0f, 0.5, 0.3, 0.5, 0.5, 0.5}      // array of presetCount float param values
    }
};

const uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_METALTONE_H

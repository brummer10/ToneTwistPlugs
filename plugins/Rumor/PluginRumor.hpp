/*
 * Rumor audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef PLUGIN_RUMOR_H
#define PLUGIN_RUMOR_H

#include "DistrhoPlugin.hpp"


template<class T> inline T mydsp_faustpower2_f(T x) {return (x * x);}
template<class T> inline T mydsp_faustpower3_f(T x) {return ((x * x) * x);}
template<class T> inline T mydsp_faustpower4_f(T x) {return (((x * x) * x) * x);}
template<class T> inline T mydsp_faustpower5_f(T x) {return ((((x * x) * x) * x) * x);}
template<class T> inline T mydsp_faustpower6_f(T x) {return (((((x * x) * x) * x) * x) * x);}

#define always_inline inline __attribute__((__always_inline__))

#include "Rumor.hpp"

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

class PluginRumor : public Plugin {
public:
    enum Parameters {
        INTENSITY = 0, 
        LEVEL, 
        dpf_bypass,
        paramCount
    };

    PluginRumor();

    ~PluginRumor();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override {
        return "Rumor";
    }

    const char* getDescription() const override {
        return R"(The Rumor is modeled after the Devi Ever Ruiner(*), a pure, nasty growling bass fuzz pedal,
with bold out-front presence, and cutting articulation.

It features Level and a Intensity control.

Features:
Modeled by Brummer
Based on the Devi Ever Ruiner(*)

(*) 'Other product names modeled in this software are trademarks of their respective companies that do not endorse and are not associated or affiliated with this software.
Devi Ever Ruiner is a trademark or trade name of another manufacturer and was used merely to identify the product whose sound was reviewed in the creation of this 
product. All other trademarks are the property of their respective holders.')" ;
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

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;

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
    bool            srChanged;
    // bypass ramping
    bool needs_ramp_down;
    bool needs_ramp_up;
    float ramp_down;
    float ramp_up;
    float ramp_up_step;
    float ramp_down_step;
    bool bypassed;
    uint32_t bypass_;
    // pointer to dsp class
    rumor::Dsp* dsp;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginRumor)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_RUMOR_H

/*
 * TubeScreamer audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef PLUGIN_TUBESCREAMER_H
#define PLUGIN_TUBESCREAMER_H

#include "DistrhoPlugin.hpp"

#include "TubeScreamer.hpp"

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

class PluginTubeScreamer : public Plugin {
public:
    enum Parameters {
        dpf_bypass = 0,
        LEVEL,
        TONE,
        DRIVE,
        paramCount
    };

    PluginTubeScreamer();

    ~PluginTubeScreamer();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override {
        return "TubeScreamer";
    }

    const char* getDescription() const override {
        return R"(TubeScreamer is a analog emulation of the classic Ibanez TS-9(*)

Features:
Modeled by Brummer
Based on the Ibanez TS-9(*)

(*) 'Other product names modeled in this software are trademarks of their respective companies that do not endorse and are not associated or affiliated with this software.
Ibanez TS-9 is trademark or trade name of other manufacturer and was used merely to identify the product whose sound was reviewed in the creation of this product.
All other trademarks are the property of their respective holders.'
)" ;
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
    tubescreamer::Dsp* dsp;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginTubeScreamer)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_TUBESCREAMER_H

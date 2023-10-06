/*
 * BoobTube audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef UI_BOOBTUBE_H
#define UI_BOOBTUBE_H

#include <functional>
#include <list>
#include "DistrhoUI.hpp"
#include "PluginBoobTube.hpp"
#include "Cairo.hpp"
#include "CairoWidgets.hpp"
#include "UiSizeGroup.hpp"
#include "ResizeHandle.hpp"

START_NAMESPACE_DISTRHO

/**
  The main UI class
*/

class UIBoobTube : public UI
{
public:
    UIBoobTube();
    ~UIBoobTube();

protected:
    void parameterChanged(uint32_t, float value) override;
    void sampleRateChanged(double newSampleRate) override;

    void uiIdle() override;
    void uiReshape(uint width, uint height) override;
    
    void onCairoDisplay(const CairoGraphicsContext& context) override;

    void onResize(const ResizeEvent& ev) override;

private:
    CairoColourTheme theme;
    int kInitialHeight;
    int kInitialWidth;
    bool blocked;
    ResizeHandle fResizeHandle;
    ScopedPointer<UiSizeGroup> sizeGroup;

    ScopedPointer<CairoKnob> gainKnob;
    ScopedPointer<CairoKnob> toneKnob;
    ScopedPointer<CairoKnob> volumeKnob;
    ScopedPointer<CairoSwitch> boostSelect;
    ScopedPointer<CairoPushButton> bypassSwitch;
    ScopedPointer<CairoLed> bypassLed;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UIBoobTube)
};

END_NAMESPACE_DISTRHO

#endif

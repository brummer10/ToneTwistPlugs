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

START_NAMESPACE_DISTRHO

/**
  class to handle resizing for all SubWindows
*/

class UiSizeGroup
{
public:
    // init the SizeGroup by store the inital size of the parent widget
    UiSizeGroup(const uint width, const uint height)
      : initW(width), initH(height)
    {
        scaleHFactor = 1.0f;
        scaleWFactor = 1.0f;
        scaleFactor = 1.0f;
    };

    ~UiSizeGroup() {};

    // add a SubWidget to the group and set the initial size/position
    void addToSizeGroup(SubWidget * const widget, const uint x, const uint y, const uint w, const uint h)
    {
        widget->setSize(w, h);
        widget->setAbsolutePos(x, y);

        const SizeGroup sg = { widget, x, y, w, h };
        sizeGroup.push_back(sg);
    }

    // add a SubWidget to the group and get the size/position
    void addToSizeGroup(SubWidget * const widget)
    {
        const DGL::Rectangle<uint> rec = widget->getConstrainedAbsoluteArea();

        const SizeGroup sg = { widget, rec.getX(), rec.getY(), rec.getWidth(), rec.getHeight() };
        sizeGroup.push_back(sg);
    }

    // resize all registered SubWidgets of the group by aspect ratio
    void resizeAspectSizeGroup(const uint w, const uint h)
    {
        scaleHFactor = static_cast<float>(h)/static_cast<float>(initH);
        scaleWFactor = static_cast<float>(w)/static_cast<float>(initW);
        scaleFactor = scaleHFactor < scaleWFactor ? scaleHFactor : scaleWFactor;
        
        for (auto const& i : sizeGroup) {
            i.widget->setSize(i.w * scaleFactor, i.h * scaleFactor);
            i.widget->setAbsolutePos(((i.x + i.w * 0.5) * scaleWFactor) - (i.w * 0.5 * scaleFactor),
                                    ((i.y + i.h * 0.5) * scaleHFactor) - (i.h * 0.5 * scaleFactor));
        }
    }

    float getScaleFactor()
    {
        return scaleFactor;
    }

    float getScaleHFactor()
    {
        return scaleHFactor;
    }

    float getScaleWFactor()
    {
        return scaleWFactor;
    }

protected:
    // struct to hold initial size/position for a SubWidget
    struct SizeGroup {
        SubWidget * const widget;
        const uint x;
        const uint y;
        const uint w;
        const uint h;
    };
    
private:
    std::list<SizeGroup> sizeGroup;
    const uint initW;
    const uint initH;
    float scaleHFactor;
    float scaleWFactor;
    float scaleFactor;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UiSizeGroup)
};

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

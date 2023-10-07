/*
 * MetalTone audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "UIMetalTone.hpp"
#include "Window.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UIMetalTone::UIMetalTone()
: UI(285, 400, true), theme(), fResizeHandle(this) {
    kInitialHeight = 400;
    kInitialWidth = 285;
    blocked = false;
    sizeGroup = new UiSizeGroup(kInitialWidth, kInitialHeight);
    theme.setIdColour(theme.idColourForgroundNormal, 0.67, 0.42, 0.26, 1.0);

    driveKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Dist", PluginMetalTone::DIST);
    driveKnob->setAdjustment(0.0, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(driveKnob, 20, 75, 60, 80);

    lowKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Low", PluginMetalTone::LOWS, true);
    lowKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(lowKnob, 80, 30, 60, 80);

    highKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "High", PluginMetalTone::HIGH, true);
    highKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(highKnob, 145, 30, 60, 80);

    levelKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Level", PluginMetalTone::LEVEL);
    levelKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(levelKnob, 205, 75, 60, 80);

    midfreqKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "MidFreq", PluginMetalTone::MIDFREQ, true);
    midfreqKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(midfreqKnob, 80, 120, 60, 80);

    middleKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Middle", PluginMetalTone::MIDDLE, true);
    middleKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(middleKnob, 145, 120, 60, 80);

    bypassLed = new CairoLed(this, theme);
    sizeGroup->addToSizeGroup(bypassLed, 132, 20, 20, 20);

    bypassSwitch = new CairoPushButton(this, theme, &blocked, bypassLed,
                dynamic_cast<UI*>(this), "MetalTone", PluginMetalTone::dpf_bypass);
    sizeGroup->addToSizeGroup(bypassSwitch, 30, 220, 225, 150);
    
    if (isResizable()) fResizeHandle.hide();
}

UIMetalTone::~UIMetalTone() {

}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UIMetalTone::parameterChanged(uint32_t index, float value) {
    // fprintf(stderr, "index %i, value %f\n", index, value);
    switch (index) {
        case PluginMetalTone::DIST:
            driveKnob->setValue(value);
            break;
        case PluginMetalTone::LOWS:
            lowKnob->setValue(value);
            break;
        case PluginMetalTone::HIGH:
            highKnob->setValue(value);
            break;
        case PluginMetalTone::LEVEL:
            levelKnob->setValue(value);
            break;
        case PluginMetalTone::MIDFREQ:
            midfreqKnob->setValue(value);
            break;
        case PluginMetalTone::MIDDLE:
            middleKnob->setValue(value);
            break;
         case PluginMetalTone::dpf_bypass:
            bypassSwitch->setValue(value);
            bypassLed->setValue(value);
            break;
   }
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UIMetalTone::sampleRateChanged(double newSampleRate) {
    (void) newSampleRate ;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UIMetalTone::uiIdle() {

}

/**
  Window reshape function, called when the parent window is resized.
*/
void UIMetalTone::uiReshape(uint width, uint height) {
    (void)width;
    (void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks

/**
  A function called to draw the view contents.
*/
void UIMetalTone::onCairoDisplay(const CairoGraphicsContext& context) {
    cairo_t* const cr = context.handle;
    int width = getWidth();
    int height = getHeight();

    cairo_push_group (cr);

    theme.setCairoColour(cr, theme.idColourBackground);
    cairo_paint(cr);
    theme.boxShadow(cr, width, height, 25, 25);

    cairo_pop_group_to_source (cr);
    cairo_paint (cr);
}

void UIMetalTone::onResize(const ResizeEvent& ev)
{
    UI::onResize(ev);
    sizeGroup->resizeAspectSizeGroup(ev.size.getWidth(), ev.size.getHeight());
}

UI* createUI() {
    return new UIMetalTone;
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

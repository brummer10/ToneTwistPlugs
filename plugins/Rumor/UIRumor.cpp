/*
 * Rumor audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "UIRumor.hpp"
#include "Window.hpp"
#include "krakel.c"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UIRumor::UIRumor()
: UI(285, 400, true), theme(), fResizeHandle(this) {
    kInitialHeight = 400;
    kInitialWidth = 285;
    blocked = false;
    sizeGroup = new UiSizeGroup(kInitialWidth, kInitialHeight);
    theme.setIdColour(theme.idColourForgroundNormal, 0.47, 0.1, 0.1, 1.0);
    texture = theme.cairo_image_surface_create_from_stream (krakel_png);

    levelKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Level", PluginRumor::LEVEL);
    levelKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(levelKnob, 40, 65, 80, 100);

    intensityKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Intensity", PluginRumor::INTENSITY);
    intensityKnob->setAdjustment(0.0, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(intensityKnob, 165, 65, 80, 100);

    bypassLed = new CairoLed(this, theme);
    sizeGroup->addToSizeGroup(bypassLed, 132, 20, 20, 20);

    bypassSwitch = new CairoPushButton(this, theme, &blocked, bypassLed,
                dynamic_cast<UI*>(this), "Rumor   ", PluginRumor::dpf_bypass);
    sizeGroup->addToSizeGroup(bypassSwitch, 30, 220, 225, 150);
    
    if (isResizable()) fResizeHandle.hide();
}

UIRumor::~UIRumor() {
    cairo_surface_destroy(texture);
}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UIRumor::parameterChanged(uint32_t index, float value) {
    // fprintf(stderr, "index %i, value %f\n", index, value);
    switch (index) {
        case PluginRumor::INTENSITY:
            intensityKnob->setValue(value);
            break;
        case PluginRumor::LEVEL:
            levelKnob->setValue(value);
            break;
         case PluginRumor::dpf_bypass:
            bypassSwitch->setValue(value);
            bypassLed->setValue(value);
            break;
    }
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UIRumor::sampleRateChanged(double newSampleRate) {
    (void) newSampleRate ;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UIRumor::uiIdle() {

}

/**
  Window reshape function, called when the parent window is resized.
*/
void UIRumor::uiReshape(uint width, uint height) {
    (void)width;
    (void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks

/**
  A function called to draw the view contents.
*/
void UIRumor::onCairoDisplay(const CairoGraphicsContext& context) {
    cairo_t* const cr = context.handle;
    const int width = getWidth();
    const int height = getHeight();
    const float scaleH = sizeGroup->getScaleHFactor();
    const float scaleW = sizeGroup->getScaleWFactor();

    cairo_push_group (cr);

    theme.setCairoColour(cr, theme.idColourForground);
    cairo_paint(cr);

    cairo_pattern_t *pat = cairo_pattern_create_for_surface(texture);
    cairo_pattern_set_extend (pat, CAIRO_EXTEND_REPEAT);
    cairo_set_source(cr, pat);
    cairo_paint (cr);
    cairo_pattern_destroy (pat);

    theme.boxShadow(cr, width, height, 25, 25);

    cairo_rectangle(cr, 25 * scaleW, 25 * scaleH, width - (50 * scaleW), height - (50 * scaleH));
    theme.setCairoColour(cr, theme.idColourBackground);
    cairo_fill_preserve(cr);
    theme.setCairoColour(cr, theme.idColourBoxShadow);
    cairo_set_line_width(cr,8);
    cairo_stroke_preserve(cr);
    theme.setCairoColour(cr, theme.idColourForground, 0.5f);
    cairo_set_line_width(cr,1);
    cairo_stroke(cr);

    cairo_pop_group_to_source (cr);
    cairo_paint (cr);
}

void UIRumor::onResize(const ResizeEvent& ev)
{
    UI::onResize(ev);
    sizeGroup->resizeAspectSizeGroup(ev.size.getWidth(), ev.size.getHeight());
}

UI* createUI() {
    return new UIRumor;
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

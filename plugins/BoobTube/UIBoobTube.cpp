/*
 * BoobTube audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "UIBoobTube.hpp"
#include "Window.hpp"
#include "leder2.c"


START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UIBoobTube::UIBoobTube()
: UI(285, 400, true), theme(), fResizeHandle(this) {
    kInitialHeight = 400;
    kInitialWidth = 285;
    blocked = false;
    sizeGroup = new UiSizeGroup(kInitialWidth, kInitialHeight);
    theme.setIdColour(theme.idColourForgroundNormal, 0.641, 0.698, 0.626, 1.0);
    theme.setIdColour(theme.idColourForgroundPrelight, 0.933, 0.82, 0.8, 1.0);
    theme.setIdColour(theme.idColourBackgroundActive, 0.667, 0.149, 0.008, 1.0);
    theme.setIdColour(theme.idColourBackground, 0.321, 0.255, 0.255, 1.0);
    texture = theme.cairo_image_surface_create_from_stream (leder2_png);

    gainKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Gain", PluginBoobTube::GAIN);
    gainKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(gainKnob, 35, 40, 80, 100);

    toneKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Tone", PluginBoobTube::TONE, true);
    toneKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(toneKnob, 107, 106, 70, 90);

    volumeKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Volume", PluginBoobTube::VOLUME);
    volumeKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(volumeKnob, 170, 40, 80, 100);

    boostSelect = new CairoSwitch(this, theme, &blocked,
                dynamic_cast<UI*>(this), "40/60V", PluginBoobTube::BOOST);
    sizeGroup->addToSizeGroup(boostSelect, 185, 146, 50, 60);

    bypassLed = new CairoLed(this, theme);
    sizeGroup->addToSizeGroup(bypassLed, 132, 20, 20, 20);

    bypassSwitch = new CairoPushButton(this, theme, &blocked, bypassLed,
                dynamic_cast<UI*>(this), "BoobTube ", PluginBoobTube::dpf_bypass);
    sizeGroup->addToSizeGroup(bypassSwitch, 30, 220, 225, 150);
    
    if (isResizable()) fResizeHandle.hide();
}

UIBoobTube::~UIBoobTube() {
    cairo_surface_destroy(texture);
}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UIBoobTube::parameterChanged(uint32_t index, float value) {
    // fprintf(stderr, "index %i, value %f\n", index, value);
    switch (index) {
         case PluginBoobTube::dpf_bypass:
            bypassSwitch->setValue(value);
            bypassLed->setValue(value);
            break;
         case PluginBoobTube::GAIN:
            gainKnob->setValue(value);
            break;
         case PluginBoobTube::TONE:
            toneKnob->setValue(value);
            break;
         case PluginBoobTube::VOLUME:
            volumeKnob->setValue(value);
            break;
         case PluginBoobTube::BOOST:
            boostSelect->setValue(value);
            break;
   }
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UIBoobTube::sampleRateChanged(double newSampleRate) {
    (void) newSampleRate ;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UIBoobTube::uiIdle() {

}

/**
  Window reshape function, called when the parent window is resized.
*/
void UIBoobTube::uiReshape(uint width, uint height) {
    (void)width;
    (void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks

/**
  A function called to draw the view contents.
*/
void UIBoobTube::onCairoDisplay(const CairoGraphicsContext& context) {
    cairo_t* const cr = context.handle;
    const int width = getWidth();
    const int height = getHeight();
    const float scale = sizeGroup->getScaleFactor();
    const float scaleH = sizeGroup->getScaleHFactor();
    const float scaleW = sizeGroup->getScaleWFactor();

    cairo_push_group (cr);

    theme.setCairoColour(cr, theme.idColourBackground);
    cairo_paint(cr);

    cairo_pattern_t *pat = cairo_pattern_create_for_surface(texture);
    cairo_pattern_set_extend (pat, CAIRO_EXTEND_REPEAT);
    cairo_set_source(cr, pat);
    cairo_paint (cr);
    cairo_pattern_destroy (pat);

    theme.boxShadow(cr, width, height, 25, 25);

    const int x = (142  * scaleW) - (117 * scale);
    const int y = (295  * scaleH) - (80 * scale);
    const int w = 234 * scale;
    const int h = 160 * scale;

    cairo_rectangle(cr, x, y, w, h);
    theme.setCairoColour(cr, theme.idColourBackgroundNormal, 0.5f);
    cairo_fill(cr);

    cairo_pop_group_to_source (cr);
    cairo_paint (cr);
}

void UIBoobTube::onResize(const ResizeEvent& ev)
{
    UI::onResize(ev);
    sizeGroup->resizeAspectSizeGroup(ev.size.getWidth(), ev.size.getHeight());
}

UI* createUI() {
    return new UIBoobTube;
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

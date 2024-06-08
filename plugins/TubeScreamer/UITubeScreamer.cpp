/*
 * TubeScreamer audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "UITubeScreamer.hpp"
#include "Window.hpp"
#include "krakel2.c"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UITubeScreamer::UITubeScreamer()
: UI(285, 400, true), theme(), fResizeHandle(this) {
    kInitialHeight = 400;
    kInitialWidth = 285;
    blocked = false;
    sizeGroup = new UiSizeGroup(kInitialWidth, kInitialHeight);
    theme.setIdColour(theme.idColourForgroundNormal, 0.622, 0.671, 0.612, 1.0);
    theme.setIdColour(theme.idColourBackgroundActive, 0.204, 0.922, 0.278, 1.0);
    theme.setIdColour(theme.idColourBackground, 0.031, 0.675, 0.486, 1.0);
    texture = theme.cairo_image_surface_create_from_stream (krakel2_png);

    levelKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Level", PluginTubeScreamer::LEVEL);
    levelKnob->setAdjustment(16.0, -20.0, 4.0, 0.1);
    sizeGroup->addToSizeGroup(levelKnob, 35, 45, 80, 100);

    toneKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Tone", PluginTubeScreamer::TONE);
    toneKnob->setAdjustment(400.0, 100.0, 1000.0, 5.0);
    sizeGroup->addToSizeGroup(toneKnob, 107, 105, 70, 90);

    driveKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Drive", PluginTubeScreamer::DRIVE);
    driveKnob->setAdjustment(0.5, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(driveKnob, 170, 45, 80, 100);

    bypassLed = new CairoLed(this, theme);
    sizeGroup->addToSizeGroup(bypassLed, 132, 20, 20, 20);

    bypassSwitch = new CairoPushButton(this, theme, &blocked, bypassLed,
                dynamic_cast<UI*>(this), "TubeScreamer", PluginTubeScreamer::dpf_bypass);
    sizeGroup->addToSizeGroup(bypassSwitch, 30, 220, 225, 150);
    
    if (isResizable()) fResizeHandle.hide();
}

UITubeScreamer::~UITubeScreamer() {
    cairo_surface_destroy(texture);
}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UITubeScreamer::parameterChanged(uint32_t index, float value) {
    // fprintf(stderr, "index %i, value %f\n", index, value);
    switch (index) {
         case PluginTubeScreamer::dpf_bypass:
            bypassSwitch->setValue(value);
            bypassLed->setValue(value);
            break;
         case PluginTubeScreamer::LEVEL:
            levelKnob->setValue(value);
            break;
         case PluginTubeScreamer::TONE:
            toneKnob->setValue(value);
            break;
         case PluginTubeScreamer::DRIVE:
            driveKnob->setValue(value);
            break;
   }
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UITubeScreamer::sampleRateChanged(double newSampleRate) {
    (void) newSampleRate ;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UITubeScreamer::uiIdle() {

}

/**
  Window reshape function, called when the parent window is resized.
*/
void UITubeScreamer::uiReshape(uint width, uint height) {
    (void)width;
    (void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks

/**
  A function called to draw the view contents.
*/
void UITubeScreamer::onCairoDisplay(const CairoGraphicsContext& context) {
    cairo_t* const cr = context.handle;
    const int width = getWidth();
    const int height = getHeight();
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

    cairo_rectangle(cr, 25 * scaleW, 215 * scaleH, width - (50 * scaleW), height - (240 * scaleH));
    theme.setCairoColour(cr, theme.idColourBackgroundNormal, 0.5f);
    cairo_fill(cr);

    cairo_pop_group_to_source (cr);
    cairo_paint (cr);
}

void UITubeScreamer::onResize(const ResizeEvent& ev)
{
    UI::onResize(ev);
    sizeGroup->resizeAspectSizeGroup(ev.size.getWidth(), ev.size.getHeight());
}

UI* createUI() {
    return new UITubeScreamer;
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

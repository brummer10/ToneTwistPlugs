/*
 * TubeScreamer audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "UITubeScreamer.hpp"
#include "Window.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UITubeScreamer::UITubeScreamer()
: UI(285, 400, true), theme() {
    kInitialHeight = 400;
    kInitialWidth = 285;
    blocked = false;
    sizeGroup = new UiSizeGroup(kInitialWidth, kInitialHeight);
    theme.setIdColour(theme.idColourForgroundNormal, 0.0, 0.271, 0.212, 1.0);
    theme.setIdColour(theme.idColourBackgroundActive, 0.204, 0.922, 0.278, 1.0);
    theme.setIdColour(theme.idColourBackground, 0.008, 0.643, 0.467, 1.0);

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

    bypassSwitch = new CairoSwitch(this, theme, &blocked, bypassLed,
                dynamic_cast<UI*>(this), "TubeScreamer", PluginTubeScreamer::BYPASS);
    sizeGroup->addToSizeGroup(bypassSwitch, 30, 220, 225, 150);

    setGeometryConstraints(kInitialWidth, kInitialHeight, true);
}

UITubeScreamer::~UITubeScreamer() {

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
         case PluginTubeScreamer::BYPASS:
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
    theme.boxShadow(cr, width, height, 25, 25);

    cairo_rectangle(cr, 25 * scaleW, 215 * scaleH, width - (50 * scaleW), height - (240 * scaleH));
    theme.setCairoColour(cr, theme.idColourBackgroundNormal, 1.0f);
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

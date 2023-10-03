/*
 * NewPedal audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "UINewPedal.hpp"
#include "Window.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UINewPedal::UINewPedal()
: UI(285, 400, true), theme() {
    kInitialHeight = 400;
    kInitialWidth = 285;
    blocked = false;
    sizeGroup = new UiSizeGroup(kInitialWidth, kInitialHeight);

    bypassLed = new CairoLed(this, theme);
    sizeGroup->addToSizeGroup(bypassLed, 132, 20, 20, 20);

    bypassSwitch = new CairoPushButton(this, theme, &blocked, bypassLed,
                dynamic_cast<UI*>(this), "NewPedal", PluginNewPedal::dpf_bypass);
    sizeGroup->addToSizeGroup(bypassSwitch, 30, 220, 225, 150);

    setGeometryConstraints(kInitialWidth, kInitialHeight, true);
}

UINewPedal::~UINewPedal() {

}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UINewPedal::parameterChanged(uint32_t index, float value) {
    // fprintf(stderr, "index %i, value %f\n", index, value);
    switch (index) {
         case PluginNewPedal::dpf_bypass:
            bypassSwitch->setValue(value);
            bypassLed->setValue(value);
            break;
   }
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UINewPedal::sampleRateChanged(double newSampleRate) {
    (void) newSampleRate ;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UINewPedal::uiIdle() {

}

/**
  Window reshape function, called when the parent window is resized.
*/
void UINewPedal::uiReshape(uint width, uint height) {
    (void)width;
    (void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks

/**
  A function called to draw the view contents.
*/
void UINewPedal::onCairoDisplay(const CairoGraphicsContext& context) {
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

void UINewPedal::onResize(const ResizeEvent& ev)
{
    UI::onResize(ev);
    sizeGroup->resizeAspectSizeGroup(ev.size.getWidth(), ev.size.getHeight());
}

UI* createUI() {
    return new UINewPedal;
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

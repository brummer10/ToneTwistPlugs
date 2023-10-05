/*
 * CollisionDrive audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "UICollisionDrive.hpp"
#include "Window.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UICollisionDrive::UICollisionDrive()
: UI(285, 400), theme() {
    kInitialHeight = 400;
    kInitialWidth = 285;
    blocked = false;
    sizeGroup = new UiSizeGroup(kInitialWidth, kInitialHeight);
    theme.setIdColour(theme.idColourForgroundNormal, 0.2, 0.92, 0.95, 1.0);
    theme.setIdColour(theme.idColourBackgroundActive, 0.1, 0.92, 0.95, 1.0);
    theme.setIdColour(theme.idColourBackgroundNormal, 0.12, 0.13, 0.16, 1.0);
    theme.setIdColour(theme.idColourBackground, 0.12, 0.13, 0.16, 1.0);

    brightKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Bright", PluginCollisionDrive::BRIGHT, true);
    brightKnob->setAdjustment(0.0, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(brightKnob, 155, 30, 60, 80);

    gateKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Gate", PluginCollisionDrive::GATE, false, true);
    gateKnob->setAdjustment(-55.0, -95.0, -10.0, 1.0);
    sizeGroup->addToSizeGroup(gateKnob, 115, 120, 60, 80);

    attackKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Attack", PluginCollisionDrive::ATTACK);
    attackKnob->setAdjustment(3.0, 0.0, 5.0, 1.0);
    sizeGroup->addToSizeGroup(attackKnob, 30, 110, 60, 80);

    driveKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Drive", PluginCollisionDrive::DRIVE);
    driveKnob->setAdjustment(0.1, 0.0, 1.0, 0.01);
    sizeGroup->addToSizeGroup(driveKnob, 195, 110, 60, 80);

    levelKnob = new CairoKnob(this, theme, &blocked,
                dynamic_cast<UI*>(this), "Level", PluginCollisionDrive::LEVEL);
    levelKnob->setAdjustment(-10.0, -20.0, 4.0, 0.5);
    sizeGroup->addToSizeGroup(levelKnob, 70, 30, 60, 80);

    bypassLed = new CairoLed(this, theme);
    sizeGroup->addToSizeGroup(bypassLed, 132, 20, 20, 20);

    bypassSwitch = new CairoPushButton(this, theme, &blocked, bypassLed,
                dynamic_cast<UI*>(this), "CollisionDrive", PluginCollisionDrive::dpf_bypass);
    sizeGroup->addToSizeGroup(bypassSwitch, 30, 220, 225, 150);
}

UICollisionDrive::~UICollisionDrive() {

}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UICollisionDrive::parameterChanged(uint32_t index, float value) {
    // fprintf(stderr, "index %i, value %f\n", index, value);
    switch (index) {
        case PluginCollisionDrive::BRIGHT:
            brightKnob->setValue(value);
            break;
        case PluginCollisionDrive::GATE:
            gateKnob->setValue(value);
            break;
        case PluginCollisionDrive::ATTACK:
            attackKnob->setValue(value);
            break;
        case PluginCollisionDrive::DRIVE:
            driveKnob->setValue(value);
            break;
        case PluginCollisionDrive::LEVEL:
            levelKnob->setValue(value);
            break;
        case PluginCollisionDrive::V1:
             gateKnob->setIndicator(value);
            break;
         case PluginCollisionDrive::dpf_bypass:
            bypassSwitch->setValue(value);
            bypassLed->setValue(value);
            break;
   }
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UICollisionDrive::sampleRateChanged(double newSampleRate) {
    (void) newSampleRate ;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UICollisionDrive::uiIdle() {

}

/**
  Window reshape function, called when the parent window is resized.
*/
void UICollisionDrive::uiReshape(uint width, uint height) {
    (void)width;
    (void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks

/**
  A function called to draw the view contents.
*/
void UICollisionDrive::onCairoDisplay(const CairoGraphicsContext& context) {
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

void UICollisionDrive::onResize(const ResizeEvent& ev)
{
    UI::onResize(ev);
    sizeGroup->resizeAspectSizeGroup(ev.size.getWidth(), ev.size.getHeight());
}

UI* createUI() {
    return new UICollisionDrive;
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

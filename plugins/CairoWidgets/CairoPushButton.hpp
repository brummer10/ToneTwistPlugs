/*
 * CairoPushButton for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROPUSHBUTTON_H
#define CAIROPUSHBUTTON_H

#include <functional>
#include <atomic>

#include "extra/Runner.hpp"

#include "CairoColourTheme.hpp"
#include "CairoLed.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class CairoPushButton : public CairoSubWidget, public Runner
{
public:

    explicit CairoPushButton(SubWidget* const parent, CairoColourTheme &theme_,
            bool *blocked_, ScopedPointer<CairoLed>& led_, UI *ui, const char* lab, const uint32_t index)
        : CairoSubWidget(parent),
          theme(theme_),
          blocked(blocked_),
          led(led_),
          setParameterValue([ui] (const uint32_t index, float value)
                                {ui->setParameterValue(index, value);}),
          label(lab),
          port(index)
          {
            init();
          }

    explicit CairoPushButton(TopLevelWidget* const parent, CairoColourTheme &theme_,
            bool *blocked_, ScopedPointer<CairoLed>& led_, UI *ui, const char* lab, const uint32_t index)
        : CairoSubWidget(parent),
          theme(theme_),
          blocked(blocked_),
          led(led_),
          setParameterValue([ui] (const uint32_t index, float value)
                                {ui->setParameterValue(index, value);}),
          label(lab),
          port(index)
          {
            init();
          }

    void setValue(float v)
    {
        value = v;
        repaint();
    }

protected:

    void init()
    {
        value = 0.0f;
        state = 0;
        fontSize = getFontSize();
        prelight = false;
        setState.store(false, std::memory_order_release);
    }

    uint getFontSize()
    {
        size_t s = strlen(label);
        return (s * 0.7);
    }

    bool run() override
    {
        if (setState.load(std::memory_order_acquire)) {
            setState.store(false, std::memory_order_release);
            state = 0;
            repaint();
            return false;
        } else {
            setState.store(true, std::memory_order_release);
            return true;
        }
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        const Size<uint> sz = getSize();
        const int w = sz.getWidth();
        const int h = sz.getHeight();

        cairo_push_group (cr);

        theme.setCairoColour(cr, theme.idColourBackgroundNormal, 1.0f);
        cairo_paint(cr);

        if (prelight) {
            theme.setCairoColour(cr, theme.idColourBackgroundPrelight);
            cairo_paint(cr);
        }

        if (state) {
            cairo_rectangle(cr, 1, 1, w -2, h -2);
            cairo_set_line_width(cr,2);
            theme.setCairoColour(cr, theme.idColourBackgroundNormal);
            cairo_stroke(cr);
            cairo_set_line_width(cr,1);
            cairo_move_to(cr, 1,h);
            cairo_line_to(cr, 1, 1);
            cairo_line_to(cr, w-2, 1);
            theme.setCairoColour(cr, theme.idColourBoxShadow);
            cairo_stroke(cr);
        }
        else
            theme.boxShadow(cr, w, h, 5, 5);

        int offset = 0;
        cairo_text_extents_t extents;
        if(state==1) {
            offset = 2;
        }
        cairo_set_font_size (cr, w / fontSize);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_text_extents(cr, label , &extents);

        theme.setCairoColour(cr, theme.idColourForgroundNormal);
        cairo_move_to (cr, (w-extents.width)*0.5 +offset, (h+extents.height)*0.75 +offset);
        cairo_show_text(cr, label);

        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

    bool onMouse(const MouseEvent& event) override
    {
        if (event.press && (event.button == 1)  && contains(event.pos)) // mouse button is pressed
        {
            value = value ? 0.0f : 1.0f;
            state = 1;
            led->setValue(value);
            setParameterValue(port, value);
            repaint();
        }
        else if (state)
        {
            state = 0;
            repaint();
        }

        return CairoSubWidget::onMouse(event);
    }

    bool onScroll(const ScrollEvent& event) override
    {
        if (!contains(event.pos))
            return CairoSubWidget::onScroll(event);

        const float set_value = (event.delta.getY() > 0.f) ? 0.f : 1.f;
        if (set_value != value) {
            state = 1;
            setValue(set_value);
            led->setValue(value);
            setParameterValue(port, value);
            if (!isRunnerActive()) startRunner(250);
        }

        return CairoSubWidget::onScroll(event);
    }

    bool onMotion(const MotionEvent& event) override
    {
        if (contains(event.pos)) // enter
        {
            if (!prelight && !(*blocked)) {
                prelight = true;
                (*blocked) = true;
                repaint();
            }
        }
        else if (prelight) // leave
        {
            prelight = false;
            (*blocked) = false;
            repaint();
        }

        return CairoSubWidget::onMotion(event);
    }

private:
    CairoColourTheme &theme;
    bool *blocked;
    ScopedPointer<CairoLed>& led;
    std::function<void(const uint32_t, float) > setParameterValue;
    float value;
    uint state;
    bool prelight;
    const char* label;
    const uint32_t port;
    uint fontSize;
    std::atomic<bool> setState;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoPushButton)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif

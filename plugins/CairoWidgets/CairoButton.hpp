/*
 * CairoButton for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROBUTTON_H
#define CAIROBUTTON_H

#include <functional>

#include "CairoColourTheme.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class CairoButton : public CairoSubWidget
{
public:

    explicit CairoButton(SubWidget* const parent, CairoColourTheme &theme_,
                    bool *blocked_, UI *ui, const char* lab, const uint32_t index)
        : CairoSubWidget(parent),
          theme(theme_),
          blocked(blocked_),
          setParameterValue([ui] (const uint32_t index, float value)
                                {ui->setParameterValue(index, value);}),
          label(lab),
          port(index)
          {
            init();
          }

    explicit CairoButton(TopLevelWidget* const parent, CairoColourTheme &theme_,
                    bool *blocked_, UI *ui, const char* lab, const uint32_t index)
        : CairoSubWidget(parent),
          theme(theme_),
          blocked(blocked_),
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
        state = (int)value;
        repaint();
    }

protected:

    void init()
    {
        value = 0.0f;
        state = 0;
        prelight = false;
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        const Size<uint> sz = getSize();
        const int w = sz.getWidth();
        const int h = sz.getHeight();

        cairo_push_group (cr);

        if (!state)
            theme.setCairoColour(cr, theme.idColourBackgroundNormal);
        else 
            theme.setCairoColour(cr, theme.idColourBackgroundActive);
        cairo_paint(cr);

        if (prelight) {
            theme.setCairoColour(cr, theme.idColourBackgroundPrelight);
            cairo_paint(cr);
        }

        if (!state)
            theme.boxShadowOutset(cr, w, h);
        else
            theme.boxShadowInset(cr, w, h); 

        int offset = 0;
        cairo_text_extents_t extents;
        if(state==0) {
            theme.setCairoColour(cr, theme.idColourForgroundNormal);
        } else if(state==1) {
            theme.setCairoColour(cr, theme.idColourForgroundActive);
            offset = 2;
        }
        cairo_set_font_size (cr, h/2.2);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_text_extents(cr, label , &extents);

        cairo_move_to (cr, (w-extents.width)*0.5 +offset, (h+extents.height)*0.45 +offset);
        cairo_show_text(cr, label);

        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

    bool onMouse(const MouseEvent& event) override
    {
        if (!event.press && contains(event.pos)) // mouse button release
        {
            value = value ? 0.0f : 1.0f;
            state = !state;
            setParameterValue(port, value);
            repaint();
        }

        return CairoSubWidget::onMouse(event);
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
    std::function<void(const uint32_t, float) > setParameterValue;
    float value;
    uint state;
    bool prelight;
    const char* label;
    const uint32_t port;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoButton)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif

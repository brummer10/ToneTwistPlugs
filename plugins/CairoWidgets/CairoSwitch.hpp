/*
 * CairoSwitch for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROSWITCH_H
#define CAIROSWITCH_H

#include <functional>

#include "CairoColourTheme.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class CairoSwitch : public CairoSubWidget
{
public:

    explicit CairoSwitch(SubWidget* const parent, CairoColourTheme &theme_,
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

    explicit CairoSwitch(TopLevelWidget* const parent, CairoColourTheme &theme_,
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


    void roundrec(cairo_t *cr, double x, double y, double width, double height, double r) {
        cairo_arc(cr, x+r, y+r, r, M_PI, 3*M_PI/2);
        cairo_arc(cr, x+width-r, y+r, r, 3*M_PI/2, 0);
        cairo_arc(cr, x+width-r, y+height-r, r, 0, M_PI/2);
        cairo_arc(cr, x+r, y+height-r, r, M_PI/2, M_PI);
        cairo_close_path(cr);
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        const Size<uint> sz = getSize();
        const int w = sz.getWidth();
        const int h = sz.getHeight() * 0.5;
        const int centerH = h * 0.5;
        const int centerW = state ? w - centerH : centerH ;
        const int offset = h * 0.2;

        cairo_push_group (cr);
        
        roundrec(cr, 1, 1, w-2, h-2, centerH);
        theme.knobShadowOutset(cr, w  , h, 0, 0);
        cairo_stroke_preserve (cr);

        cairo_new_path(cr);
        roundrec(cr, offset, offset, w - (offset * 2), h - (offset * 2), centerH-offset);
        theme.setCairoColour(cr, theme.idColourBoxShadow);
        cairo_fill_preserve(cr);
        if (state) {
            theme.setCairoColourWithAlpha(cr, theme.idColourBackgroundActive, 0.6f);
            cairo_fill_preserve(cr);
        }
        theme.setCairoColour(cr, theme.idColourBoxShadow);
        cairo_set_line_width(cr,1);
        cairo_stroke_preserve (cr);

        cairo_new_path(cr);
        cairo_arc(cr,centerW, centerH, h/2.8, 0, 2 * M_PI );
        theme.setCairoColour(cr, theme.idColourBackground);
        cairo_fill_preserve(cr);
        theme.knobShadowOutset(cr, w * 0.5 , h, centerW - centerH, 0);
        theme.setCairoColour(cr, theme.idColourBoxShadow);
        cairo_set_line_width(cr,1);
        cairo_stroke_preserve (cr);

        cairo_new_path(cr);
        cairo_arc(cr,centerW, centerH, h/3.6, 0, 2 * M_PI );
        theme.setCairoColour(cr, theme.idColourBackgroundNormal);
        cairo_fill_preserve(cr);
        theme.knobShadowInset(cr, w * 0.5 , h, centerW - centerH, 0);
        cairo_stroke (cr);

        cairo_text_extents_t extents;
        if (prelight) theme.setCairoColour(cr, theme.idColourForgroundPrelight);
        else theme.setCairoColour(cr, theme.idColourForgroundNormal);
        cairo_set_font_size (cr, h * 0.5);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_text_extents(cr, label , &extents);

        cairo_move_to (cr, (w-extents.width)*0.5, (h+extents.height + offset));
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

    bool onScroll(const ScrollEvent& event) override
    {
        if (!contains(event.pos))
            return CairoSubWidget::onScroll(event);

        const float set_value = (event.delta.getY() > 0.f) ? 1.f : 0.f;
        setValue(set_value);
        setParameterValue(port, value);
        
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
    std::function<void(const uint32_t, float) > setParameterValue;
    float value;
    uint state;
    bool prelight;
    const char* label;
    const uint32_t port;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoSwitch)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif

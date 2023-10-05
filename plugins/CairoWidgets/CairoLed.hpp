/*
 * CairoLed for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROLED_H
#define CAIROLED_H

#include <functional>

#include "CairoColourTheme.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class CairoLed : public CairoSubWidget
{
public:

    explicit CairoLed(SubWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          theme(theme_)
          {
            init();
          }

    explicit CairoLed(TopLevelWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          theme(theme_)
          {
            init();
          }

    void setValue(float v)
    {
        state = (int)v;
        repaint();
    }

protected:

    void init()
    {
        state = 0;
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        const Size<uint> sz = getSize();
        const int w = sz.getWidth();
        const int h = sz.getHeight();
        const int r = h < w ? (h - 2) * 0.5 : (w - 2) * 0.5;

        cairo_push_group (cr);
        cairo_arc(cr,w * 0.5, h * 0.5, r, 0, 2 * M_PI );

        if (!state) {
            cairo_pattern_t* pat = cairo_pattern_create_radial (w * 0.5, h * 0.5,
                                                1, w * 0.5, h * 0.5, r);
            cairo_pattern_add_color_stop_rgba (pat, 0,  0.83, 0.1, 0.1, 1.0);
            cairo_pattern_add_color_stop_rgba (pat, 0.6,  0.33, 0.1, 0.1, 1.0);
            cairo_pattern_add_color_stop_rgba (pat, 1,  0.3, 0.3, 0.3, 1.0);
            cairo_set_source (cr, pat);
            cairo_fill_preserve(cr);
            cairo_pattern_destroy (pat);
        }
        else
        {
            cairo_pattern_t* pat = cairo_pattern_create_radial (w * 0.5, h * 0.5,
                                                1, w * 0.5, h * 0.5, r);
            cairo_pattern_add_color_stop_rgba (pat, 0,  0.3, 0.1, 0.1, 1.0);
            cairo_pattern_add_color_stop_rgba (pat, 0.7,  0.2, 0.1, 0.1, 1.0);
            cairo_pattern_add_color_stop_rgba (pat, 1,  0.3, 0.3, 0.3, 1.0);
            cairo_set_source (cr, pat);
            cairo_fill_preserve(cr);
            cairo_pattern_destroy (pat);
        }

        cairo_set_line_width(cr,2);
        theme.setCairoColour(cr, theme.idColourBoxShadow);
        cairo_stroke (cr);
        cairo_new_path (cr);

        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

private:
    CairoColourTheme &theme;
    uint state;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoLed)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif

/*
 * CairoProgressBar for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROPROGRESSBAR_H
#define CAIROPROGRESSBAR_H

#include "CairoColourTheme.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class CairoProgressBar : public CairoSubWidget
{
public:

    explicit CairoProgressBar(SubWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          theme(theme_)
          {
            init();
          }

    explicit CairoProgressBar(TopLevelWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          theme(theme_)
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
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        cairo_push_group (cr);

        const Size<uint> sz = getSize();
        const int width = sz.getWidth();
        const int height = sz.getHeight();

        theme.setCairoColour(cr,theme.idColourFrame);
        cairo_rectangle(cr,0, 0, width, height);
        cairo_set_line_width(cr,2);
        cairo_stroke(cr);

        theme.setCairoColour(cr, theme.idColourBackgroundProgress);
        cairo_rectangle(cr,0, 0, width * value, height);
        cairo_fill(cr);

        cairo_text_extents_t extents;
        cairo_set_font_size (cr, height/2.2);
        char s[64];
        snprintf(s, 63,"%d%%",  (int) (value * 100.0));
        cairo_text_extents(cr,s , &extents);
        cairo_move_to (cr, width * 0.5 - extents.width * 0.5,  height * 0.5 + extents.height * 0.5 );
        theme.setCairoColour(cr, theme.idColourForground);
        cairo_set_operator(cr, CAIRO_OPERATOR_ADD);
        cairo_show_text(cr, s);
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        cairo_new_path (cr);
        theme.boxShadowInset(cr, width, height);
        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

private:
    CairoColourTheme &theme;
    float value;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoProgressBar)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif

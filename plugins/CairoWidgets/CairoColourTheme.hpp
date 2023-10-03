/*
 * CairoColourTheme for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROCOLOURTHEME_H
#define CAIROCOLOURTHEME_H

#include "Cairo.hpp"

START_NAMESPACE_DGL

class CairoColourTheme
{
public:
    CairoColourTheme()
    {
        init();
    }

    struct CairoColour{
        double r;
        double g;
        double b;
        double a;
    };

    void setCairoColour(cairo_t* const cr, const CairoColour idColour, float darker = 0.8f)
    {
        cairo_set_source_rgba(cr, idColour.r * darker, idColour.g * darker,
                                idColour.b * darker, idColour.a);
    }

    void setCairoColourWithAlpha(cairo_t* const cr, const CairoColour idColour, float alpha = 1.0f)
    {
        cairo_set_source_rgba(cr, idColour.r, idColour.g, idColour.b, alpha);
    }

    void setIdColour(CairoColour &idColour, double r, double g, double b, double a) {
        idColour = CairoColour {r, g, b, a};
    }

    void boxShadowInset(cairo_t* const cr, int width, int height)
    {
        cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, width, 0);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.95, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.1, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;
        pat = cairo_pattern_create_linear (0, 0, 0, height);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.9, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.1, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.0);
        cairo_pattern_add_color_stop_rgba 
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
    }

    void boxShadowOutset(cairo_t* const cr, int width, int height)
    {
        cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, width, 0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.05, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.95, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.0);
        cairo_pattern_add_color_stop_rgba 
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;
        pat = cairo_pattern_create_linear (0, 0, 0, height);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.1, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.9, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
    }

    void boxShadow(cairo_t* const cr, int width, int height, int w, int h, int x = 0, int y = 0, bool fill = false)
    {
        cairo_pattern_t *pat = cairo_pattern_create_linear (x, y, x + w, y);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.8);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.4, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.3);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.0);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        if (fill) cairo_fill_preserve (cr);
        else cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;

        pat = cairo_pattern_create_linear (x, y, x, y + h);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.8);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.4, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.3);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.0);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        if (fill) cairo_fill_preserve (cr);
        else cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;

        pat = cairo_pattern_create_linear (x + width - w, y, x +width, y);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.4, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.3);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.8);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        if (fill) cairo_fill_preserve (cr);
        else cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;

        pat = cairo_pattern_create_linear (x, y + height - h, x, y +height);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.4, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.3);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.8);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        if (fill) cairo_fill_preserve (cr);
        else cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;
    }

    void knobShadowOutset(cairo_t* const cr, int width, int height, int x = 0, int y = 0)
    {
        cairo_pattern_t *pat = cairo_pattern_create_linear (x, y, x + width, y + height);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.45, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.4);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.65, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.4);
        cairo_pattern_add_color_stop_rgba 
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        cairo_fill_preserve (cr);
        cairo_pattern_destroy (pat);
    }

    void knobShadowInset(cairo_t* const cr, int width, int height, int x = 0, int y = 0)
    {
        cairo_pattern_t* pat = cairo_pattern_create_linear (x, y, x + width, y + height);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.65, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.4);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.55, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.4);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        cairo_fill (cr);
        cairo_pattern_destroy (pat);
    }

    CairoColour idColourBackground;
    CairoColour idColourBackgroundNormal;
    CairoColour idColourBackgroundPrelight;
    CairoColour idColourBackgroundActive;
    CairoColour idColourBackgroundProgress;

    CairoColour idColourForground;
    CairoColour idColourForgroundNormal;
    CairoColour idColourForgroundPrelight;
    CairoColour idColourForgroundActive;

    CairoColour idColourFrame;

    CairoColour idColourBoxShadow;
    CairoColour idColourBoxLight;

protected:

    void init()
    {
        setIdColour(idColourBackground, 0.13, 0.13, 0.13, 1);
        setIdColour(idColourBackgroundNormal, 0.13, 0.13, 0.13, 1.0);
        setIdColour(idColourBackgroundPrelight, 0.63, 0.63, 0.63, 0.03);
        setIdColour(idColourBackgroundActive, 0.63, 0.13, 0.13, 1.0);
        setIdColour(idColourBackgroundProgress, 0.4, 0.4, 0.4, 1.0);

        setIdColour(idColourForground, 0.63, 0.63, 0.63, 1.0);
        setIdColour(idColourForgroundNormal, 0.63, 0.63, 0.63, 1.0);
        setIdColour(idColourForgroundPrelight, 0.83, 0.83, 0.83, 1.0);
        setIdColour(idColourForgroundActive, 0.93, 0.63, 0.63, 1.0);

        setIdColour(idColourFrame, 0.03, 0.03, 0.03, 1.0);

        setIdColour(idColourBoxShadow,  0.05, 0.05, 0.05, 1.0);
        setIdColour(idColourBoxLight, 0.33, 0.33, 0.33, 1.0);
    }

private:
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoColourTheme)
};

END_NAMESPACE_DGL

#endif

/*
 * CairoPeekMeter for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROPEEKMETER_H
#define CAIROPEEKMETER_H

#include "CairoColourTheme.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class CairoPeekMeter : public CairoSubWidget
{
public:

    explicit CairoPeekMeter(SubWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          image(nullptr),
          theme(theme_)
          {
            init();
          }

    explicit CairoPeekMeter(TopLevelWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          image(nullptr),
          theme(theme_)
          {
            init();
          }

    void setValue(float v)
    {
        value = v;
        repaint();
    }

    ~CairoPeekMeter() {
        cairo_surface_destroy(image);
    }

protected:
    void init()
    {
        old_value = -70.0f;
        std_value = -70.0f;
        value = -70.0f;
    }

    float power2db(float power)
    {
        const float falloff = 27 * 60 * 0.0005;
        const float fallsoft = 6 * 60 * 0.0005;
        //power = 20.*log10(power);
        if (power <=  20.*log10(0.00021)) { // -70db
            power = 20.*log10(0.00000000001); //-137db
            old_value = MIN(0.0,old_value - fallsoft);
        }
        // retrieve old meter value and consider falloff
        if (power < std_value) {
            power = MAX(power, std_value - falloff);
            old_value = MIN(0.0,old_value - fallsoft);
        }
        if (power > old_value) {
            old_value = power ;
        }
        
        std_value = power;
        return  power;
    }

    float logMeter (float db)
    {
        float def = 0.0f; /* Meter deflection %age */

        if (db < -70.0f) {
            def = 0.0f;
        } else if (db < -60.0f) {
            def = (db + 70.0f) * 0.25f;
        } else if (db < -50.0f) {
            def = (db + 60.0f) * 0.5f + 2.5f;
        } else if (db < -40.0f) {
            def = (db + 50.0f) * 0.75f + 7.5f;
        } else if (db < -30.0f) {
            def = (db + 40.0f) * 1.5f + 15.0f;
        } else if (db < -20.0f) {
            def = (db + 30.0f) * 2.0f + 30.0f;
        } else if (db < 6.0f) {
            def = (db + 20.0f) * 2.5f + 50.0f;
        } else {
            def = 115.0f;
        }

        /* 115 is the deflection %age that would be
           when db=6.0. this is an arbitrary
           endpoint for our scaling.
        */
        return def/115.0f;
    }


    void drawMeterImage(int width, int height)
    {
        image = cairo_image_surface_create( 
                            CAIRO_FORMAT_ARGB32, width, height*2);
        cairo_t *cri = cairo_create (image);
        cairo_push_group (cri);

        theme.setCairoColour(cri, theme.idColourFrame);
        cairo_paint(cri);

        cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, width, 0.0);
        cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.1, 0.5, 0.1, 0.4);
        cairo_pattern_add_color_stop_rgba(pat, 0.8, 0.4, 0.4, 0.1, 0.4);
        cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.5, 0.0, 0.0, 0.4);
        cairo_set_source(cri, pat);

        int c = (height) * 0.5 ;
        int ci = c-2;

        int i = 1;
        int j = 1;
        for(;i<width;) {
            for(;j<height;) {
                cairo_rectangle(cri,i,j,2,ci);
                cairo_fill(cri);
                j +=c;
            }
            i +=3;
            j = 1;
        }

        cairo_pattern_destroy (pat);
        pat = cairo_pattern_create_linear (0, 0, width, 0.0);
        cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.1, 0.5, 0.1, 1);
        cairo_pattern_add_color_stop_rgba(pat, 0.8, 0.4, 0.4, 0.1, 1);
        cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.5, 0.0, 0.0, 1);
        cairo_set_source(cri, pat);
        i = 1;
        j = 1;
        for(;i<width;) {
            for(;j<height;) {
                cairo_rectangle(cri,i,height+j,2,ci);
                cairo_fill(cri);
                j +=c;
            }
            i +=3;
            j = 1;
        }

        cairo_pattern_destroy (pat);
        cairo_pop_group_to_source (cri);
        cairo_paint (cri);
        cairo_destroy(cri);
    }


    void drawMeterScale(cairo_t* const cr, int y0, int rect_width, int rect_height)
    {
        double x0      = 0;

        int  db_points[] = { -50, -40, -30, -20, -15, -10, -6, -3, 0, 3 };
        char  buf[32];

        cairo_set_font_size (cr, (float)rect_height * 0.5);
        theme.setCairoColour(cr, theme.idColourForground);

        for (unsigned int i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
        {
            float fraction = logMeter(db_points[i]);
            //cairo_set_source_rgb (cr,0.32 + 0.22*i/2,0.5 +  0.1*i/2, 0.1);

            cairo_move_to (cr, x0+(rect_width * fraction),y0+rect_height*0.1);
            cairo_line_to (cr, x0+(rect_width * fraction) ,y0+rect_height*0.6);
            if (i<6)
            {
                snprintf (buf, sizeof (buf), "%d", db_points[i]);
                cairo_move_to (cr, x0+(rect_width * fraction)+3,y0+rect_height);
            }
            else
            {
                snprintf (buf, sizeof (buf), " %d", db_points[i]);
                cairo_move_to (cr, x0+(rect_width * fraction)+3,y0+rect_height );
            }
            cairo_show_text (cr, buf);
        }

        theme.setCairoColour(cr, theme.idColourForground);
        cairo_set_line_width(cr, 1.5);
        cairo_stroke(cr);
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        cairo_push_group (cr);

        const Size<uint> sz = getSize();
        const int width = sz.getWidth();
        const int height = sz.getHeight() * 0.5;

        double meterstate = logMeter(power2db(value));
        double oldstate = logMeter(old_value);
        cairo_set_source_surface (cr, image, 0, height * 0.5);
        cairo_rectangle(cr,0, height * 0.5, width, height * 0.5);
        cairo_fill(cr);
        cairo_set_source_surface (cr, image, 0, -height);
        cairo_rectangle(cr, 0,height * 0.5, width*meterstate, height * 0.5);
        cairo_fill(cr);

        cairo_rectangle(cr,(width*oldstate)-3, height * 0.5, 3, height * 0.5);
        cairo_fill(cr);
        drawMeterScale(cr, height, width, height * 0.5);
        theme.boxShadowInset(cr, width, height*2);
        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

    void onResize(const ResizeEvent& ev) override
    {
        cairo_surface_destroy(image);
        image = nullptr;
        drawMeterImage(ev.size.getWidth(), ev.size.getHeight() * 0.5);
    }

private:
    cairo_surface_t* image;
    CairoColourTheme &theme;
    float value;
    float old_value;
    float std_value;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoPeekMeter)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif

/*
 * CairoKnob for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROKNOB_H
#define CAIROKNOB_H

#include <functional>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "CairoColourTheme.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class CairoKnob : public CairoSubWidget
{
public:

    explicit CairoKnob(SubWidget* const parent, CairoColourTheme &theme_, bool *blocked_,
            UI *ui, const char* lab, const uint32_t index, bool center_ = false, bool indicator = false)
        : CairoSubWidget(parent),
          theme(theme_),
          blocked(blocked_),
          setParameterValue([ui] (const uint32_t index, float value)
                                {ui->setParameterValue(index, value);}),
          label(lab),
          port(index),
          center(center_),
          isIndicator(indicator)
          {
            init();
          }

    explicit CairoKnob(TopLevelWidget* const parent, CairoColourTheme &theme_, bool *blocked_,
            UI *ui, const char* lab, const uint32_t index, bool center_ = false, bool indicator = false)
        : CairoSubWidget(parent),
          theme(theme_),
          blocked(blocked_),
          setParameterValue([ui] (const uint32_t index, float value)
                                {ui->setParameterValue(index, value);}),
          label(lab),
          port(index),
          center(center_),
          isIndicator(indicator)
          {
            init();
          }

    void setValue(float v)
    {
        value = v;
        state = getState();
        repaint();
    }
    
    void setAdjustment(float value_, float min_value_, float max_value_, float value_step_)
    {
        value = value_;
        min_value = min_value_;
        max_value = max_value_;
        value_step = value_step_;
        state = getState();
        stepper = get_stepper();
        repaint();
    }

    void setIndicator(float v)
    {
        indic = (int)v;
        repaint();
    }

protected:

    void init()
    {
        value = 0.0f;
        min_value = 0.0f;
        max_value = 1.0f;
        value_step = 0.01f;
        posY = 0.0f;
        v = 0;
        indic = 0.0f;
        inDrag = false;
        state = getState();
        prelight = false;
        stepper = get_stepper();
    }

    float get_stepper()
    {
        float range = std::fabs(max_value - min_value);
        float steps = range / value_step;
        return steps * 0.01f;
    }

    float getState()
    {
        return (value - min_value) / (max_value - min_value);
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;

        /** get size for the knob **/
        const Size<uint> sz = getSize();
        const int width = sz.getWidth();
        const int height = sz.getHeight() - (sz.getHeight() * 0.15);

        const int grow = (width > height) ? height:width;
        const int knob_x = grow-1;
        const int knob_y = grow-1;

        const int knobx = (width - knob_x) * 0.5;
        const int knobx1 = width* 0.5;

        const int knoby = (height - knob_y) * 0.5;
        const int knoby1 = height * 0.5;

        /** get geometric values for the knob **/
        const double scale_zero = 20 * (M_PI/180); // defines "dead zone"
        const double angle = scale_zero + state * 2 * (M_PI - scale_zero);

        const double pointer_off =knob_x/3.5;
        const double radius = MIN(knob_x-pointer_off, knob_y-pointer_off) / 2;
        const double lengh_x = (knobx+radius+pointer_off/2) - radius * sin(angle);
        const double lengh_y = (knoby+radius+pointer_off/2) + radius * cos(angle);
        const double radius_x = (knobx+radius+pointer_off/2) - radius * sin(angle);
        const double radius_y = (knoby+radius+pointer_off/2) + radius * cos(angle);

        /** draw the knob **/
        cairo_push_group (cr);

        cairo_arc(cr,knobx1, knoby1, knob_x/2.1, 0, 2 * M_PI );
        theme.knobShadowOutset(cr, width, height);
        cairo_stroke_preserve (cr);
        cairo_new_path (cr);

        cairo_arc(cr,knobx1, knoby1, knob_x/2.4, 0, 2 * M_PI );
        theme.knobShadowOutset(cr, width, height);
        cairo_set_line_width(cr,knobx1/10);
        theme.setCairoColour(cr, theme.idColourBoxShadow);
        cairo_stroke_preserve (cr);
        cairo_new_path (cr);

        cairo_arc(cr,knobx1, knoby1, knob_x/3.1, 0, 2 * M_PI );
        if (isIndicator)
        {
            if (indic) theme.setCairoColour(cr, theme.idColourBackgroundNormal);
            else theme.setCairoColour(cr, theme.idColourBackgroundActive, 0.3);
        }
        else
        {
            theme.setCairoColour(cr, theme.idColourBackgroundNormal);
        }
        cairo_fill_preserve (cr);
        theme.knobShadowInset(cr, width, height);
        cairo_new_path (cr);

        /** create a rotating pointer on the kob**/
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND); 
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_BEVEL);
        cairo_move_to(cr, radius_x, radius_y);
        cairo_line_to(cr,lengh_x,lengh_y);
        cairo_set_line_width(cr,knobx1/10);
        theme.setCairoColour(cr, theme.idColourForground);
        cairo_stroke_preserve(cr);
        cairo_new_path (cr);

        /** create a indicator ring around the knob **/
        const double add_angle = 90 * (M_PI / 180.);
        cairo_new_sub_path(cr);
        theme.setCairoColour(cr, theme.idColourBackgroundActive);
        cairo_set_line_width(cr,knobx1/25);
        if (!center)
        {
            cairo_arc (cr, knobx1, knoby1, knob_x/2.4,
                  add_angle + scale_zero, add_angle + angle);
        }
        else
        {
            const double mid_angle = scale_zero + 0.5 * 2 * (M_PI - scale_zero);
            if (state < 0.5f)
                cairo_arc_negative (cr, knobx1, knoby1, knob_x/2.4,
                  add_angle + mid_angle, add_angle + angle);
            else
                cairo_arc (cr, knobx1, knoby1, knob_x/2.4,
                  add_angle + mid_angle, add_angle + angle);
        }
        cairo_stroke(cr);

        /** show value on the kob**/
        theme.setCairoColour(cr, theme.idColourForground);
        cairo_text_extents_t extents;
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, height * 0.15);
        char s[17];
        char sa[17];
        const char* format[] = {"%.1f", "%.2f", "%.3f"};
        if (fabs(value_step)>0.99) {
            snprintf(s, 16,"%d",  (int) value);
        } else if (fabs(value_step)>0.09) {
            snprintf(s, 16, format[1-1], value);
        } else {
            snprintf(s, 16, format[2-1], value);
        }
        snprintf(sa, strlen(s),"%s",  "000000000000000");
        cairo_text_extents(cr, sa, &extents);
        int wx = extents.width * 0.5;
        cairo_text_extents(cr, s, &extents);
        cairo_move_to (cr, knobx1 - wx, knoby1+extents.height/2);
        cairo_show_text(cr, s);
        cairo_new_path (cr);

        /** show label below the knob**/
        if (prelight) theme.setCairoColour(cr, theme.idColourForgroundPrelight);
        else theme.setCairoColour(cr, theme.idColourForgroundNormal);
        cairo_set_font_size (cr, height * 0.18);
        cairo_text_extents(cr,label , &extents);
        cairo_move_to (cr, (width*0.5)-(extents.width/2), height + (height * 0.15)-(extents.height*0.1));
        cairo_show_text(cr, label);
        cairo_new_path (cr);

        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

    bool onKeyboard(const KeyboardEvent& event) override {
        if (event.press && prelight)
        {
            int set_value = 0;
            if (event.key == 57357) set_value = 1; // UpArrow
            else if (event.key == 57359) set_value = -1; // DownArrow
            float  v = value + (value_step * set_value);
            v = MIN(max_value, MAX(min_value, v));
            setValue(v);
            setParameterValue(port, value);
        }
        return CairoSubWidget::onKeyboard(event);
    }

    bool onMouse(const MouseEvent& event) override
    {
        if (event.press && (event.button == 1) && contains(event.pos)) // mouse button pressed
        {
            posY = event.pos.getY();
            inDrag = true;
        }
        else
        {
            inDrag = false;
        }

        return CairoSubWidget::onMouse(event);
    }

    bool onScroll(const ScrollEvent& event) override
    {
        if (!contains(event.pos))
            return CairoSubWidget::onScroll(event);

        const float set_value = (event.delta.getY() > 0.f) ? 1.f : -1.f;
        float  v1 = value + (value_step * set_value);
        v1 = MIN(max_value, MAX(min_value, v1));
        setValue(v1);
        setParameterValue(port, value);
        
        return CairoSubWidget::onScroll(event);
    }

    bool onMotion(const MotionEvent& event) override
    {
        if (inDrag && (std::abs(posY - event.pos.getY()) > 0.f))
        {
            const float set_value = (posY - event.pos.getY() > 0.f) ? 1.f : -1.f ;
            v += stepper * value_step;
            posY = event.pos.getY();
            if (v >= value_step)
            {
                v = value + (value_step * set_value);
                v = MIN(max_value, MAX(min_value, v));
                setValue(v);
                setParameterValue(port, value);
                v = 0;
            }
        }
        if (contains(event.pos)) // enter
        {
            if (!prelight && !(*blocked)) {
                prelight = true;
                (*blocked) = true;
                repaint();
            }
        }
        else if (prelight && !inDrag) // leave
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
    float min_value;
    float max_value;
    float value_step;
    float posY;
    float v;
    float stepper;
    bool inDrag;
    float state;
    bool prelight;
    const char* label;
    const uint32_t port;
    bool center;
    bool isIndicator;
    int indic;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoKnob)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif

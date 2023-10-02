/*
 * CairoToolTip for the DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  0BSD 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROTOOLTIP_H
#define CAIROTOOLTIP_H

#include <atomic>
#include "extra/Runner.hpp"

#include "CairoColourTheme.hpp"

START_NAMESPACE_DGL

// -----------------------------------------------------------------------

class CairoToolTip : public CairoSubWidget, public Runner
{
public:

    explicit CairoToolTip(SubWidget* const parent_, CairoColourTheme &theme_, const char* lab)
        : CairoSubWidget(parent_),
          parent(parent_),
          theme(theme_),
          label(lab)
          {
            init();
          }

    explicit CairoToolTip(TopLevelWidget* const parent_, CairoColourTheme &theme_, const char* lab)
        : CairoSubWidget(parent_),
          parent(parent_),
          theme(theme_),
          label(lab)
          {
            init();
          }

    ~CairoToolTip() {if (isRunnerActive()) stopRunner();}

    void setLabel(const char* lab)
    {
        label = lab;
        state.store(false, std::memory_order_release);
        if (!isRunnerActive()) {
            if (!isVisible()) show();
            startRunner(2500);
        }
        repaint();
    }
    
    void unset()
    {
        if (isVisible()) hide();
        parent->repaint();
    }

protected:
    void init()
    {
        hide();
        state.store(false, std::memory_order_release);
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        cairo_push_group (cr);

        const Size<uint> sz = getSize();
        const int w = sz.getWidth();
        const int h = sz.getHeight();
        theme.setCairoColour(cr, theme.idColourBackground);
        
        cairo_rectangle(cr, 0, 0, w, h);
        cairo_fill_preserve(cr);
        theme.setCairoColour(cr, theme.idColourFrame);
        cairo_stroke(cr);
        cairo_text_extents_t extents;
        theme.setCairoColour(cr, theme.idColourForground);
        cairo_set_font_size (cr, h * 0.24);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_text_extents(cr, label , &extents);

        cairo_move_to (cr, (w-extents.width)*0.5, (h+extents.height)*0.45);
        cairo_show_text(cr, label);
        cairo_new_path (cr);
        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

    bool run() override
    {
        if (state.load(std::memory_order_acquire)) {
            state.store(false, std::memory_order_release);
            unset();
            return false;
        } else {
            state.store(true, std::memory_order_release);
            return true;
        }
    }

private:
    Widget * const parent;
    CairoColourTheme &theme;
    const char* label;
    std::atomic<bool> state;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoToolTip)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DGL

#endif

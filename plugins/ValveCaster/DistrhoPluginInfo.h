/*
 * ValveCaster audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef DISTRHO_PLUGIN_INFO_H
#define DISTRHO_PLUGIN_INFO_H

#define DISTRHO_PLUGIN_BRAND "brummer"
#define DISTRHO_PLUGIN_NAME  "ValveCaster"
#define DISTRHO_PLUGIN_URI   "urn:brummer10:valvecaster"
#define DISTRHO_PLUGIN_CLAP_ID "com.github.brummer10.valvecaster"

#define DISTRHO_PLUGIN_HAS_UI           1
#define DISTRHO_UI_USE_NANOVG           0
#define DISTRHO_UI_USE_CAIRO            1
#define DISTRHO_UI_USER_RESIZABLE       1

#define DISTRHO_PLUGIN_IS_RT_SAFE       1
#define DISTRHO_PLUGIN_NUM_INPUTS       1
#define DISTRHO_PLUGIN_NUM_OUTPUTS      1
#define DISTRHO_PLUGIN_WANT_TIMEPOS     0
#define DISTRHO_PLUGIN_WANT_PROGRAMS    0
#define DISTRHO_PLUGIN_WANT_MIDI_INPUT  0
#define DISTRHO_PLUGIN_WANT_MIDI_OUTPUT 0
#define DISTRHO_PLUGIN_WANT_PARAMETER_VALUE_CHANGE_REQUEST 0

#define DISTRHO_PLUGIN_LV2_CATEGORY "lv2:DistortionPlugin"
#define DISTRHO_PLUGIN_VST3_CATEGORIES "Fx|distortion|Mono"
#define DISTRHO_PLUGIN_CLAP_FEATURES "audio-effect", "distortion", "mono"

#define DPF_VST3_DONT_USE_BRAND_ID     1
#define DISTRHO_PLUGIN_BRAND_ID BrTw
#define DISTRHO_PLUGIN_UNIQUE_ID bVCa

#endif // DISTRHO_PLUGIN_INFO_H

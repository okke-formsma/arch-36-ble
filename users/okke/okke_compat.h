#pragma once

#include "quantum.h"
//be forward compatible with newer qmk.
#ifndef A
    #define COMPAT_MODE
    #define A LALT
    #define G LGUI
    #define MOD_MASK_CTRL            (MOD_BIT(KC_LCTRL)  | MOD_BIT(KC_RCTRL))
    #define MOD_MASK_SHIFT           (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
    #define MOD_MASK_ALT             (MOD_BIT(KC_LALT)   | MOD_BIT(KC_RALT))
    #define MOD_MASK_GUI             (MOD_BIT(KC_LGUI)   | MOD_BIT(KC_RGUI))
    #define MOD_MASK_CS              (MOD_MASK_CTRL  | MOD_MASK_SHIFT)
    #define MOD_MASK_CA              (MOD_MASK_CTRL  | MOD_MASK_ALT)
    #define MOD_MASK_CG              (MOD_MASK_CTRL  | MOD_MASK_GUI)
    #define MOD_MASK_SA              (MOD_MASK_SHIFT | MOD_MASK_ALT)
    #define MOD_MASK_SG              (MOD_MASK_SHIFT | MOD_MASK_GUI)
    #define MOD_MASK_AG              (MOD_MASK_ALT   | MOD_MASK_GUI)
    #define MOD_MASK_CSA             (MOD_MASK_CTRL  | MOD_MASK_SHIFT | MOD_MASK_ALT)
    #define MOD_MASK_CSG             (MOD_MASK_CTRL  | MOD_MASK_SHIFT | MOD_MASK_GUI)
    #define MOD_MASK_CAG             (MOD_MASK_CTRL  | MOD_MASK_ALT   | MOD_MASK_GUI)
    #define MOD_MASK_SAG             (MOD_MASK_SHIFT | MOD_MASK_ALT   | MOD_MASK_GUI)
    #define MOD_MASK_CSAG            (MOD_MASK_CTRL  | MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI)
    #define KC_BRIU   KC_NO //sorry no support
    #define KC_BRID   KC_NO //nope
    typedef uint32_t layer_state_t;
    void tap_code16(uint16_t code);
#endif
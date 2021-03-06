#pragma once

#include "quantum.h"
#include "okke.h"
#include "okke_process_record.h"

#include "app_ble_func.h"

// clang-format off
#include "app_ble_func.h"

#if (!defined(LAYOUT) && defined(KEYMAP))
#  define LAYOUT KEYMAP
#endif

/* Replace `LAYOUT()` with `LAYOUT_UNFOLD()` in `keymap.c` when using any of the
 * row abstractions below, to ensure that QMK macros will receive the expected
 * number of arguments.
 */
#define LAYOUT_UNFOLD(...) LAYOUT(__VA_ARGS__)


/* Maintain standard 5-key, half-row macros, below these utility macros and
 * automatically apply `MT(MOD_*, keycode)` mod-tap modifiers with e.g.
 * the `MODS_L()` and `MODS_R()` utility macros.
 */

#define MT_BASIC_L(kc_0, kc_1, kc_2, kc_3, kc_4) \
        MT(MOD_LCTL, (kc_0)),                    \
        MT(MOD_LGUI, (kc_1)),                    \
        MT(MOD_LALT, (kc_2)),                    \
        MT(MOD_LSFT, (kc_3)),                    \
        (kc_4)
#define MODS_L(...) MT_BASIC_L(__VA_ARGS__)

#define MT_BASIC_R(kc_4, kc_3, kc_2, kc_1, kc_0) \
        (kc_4),                                  \
        MT(MOD_LSFT, (kc_3)),                    \
        MT(MOD_LALT, (kc_2)),                    \
        MT(MOD_LGUI, (kc_1)),                    \
        MT(MOD_LCTL, (kc_0))
#define MODS_R(...) MT_BASIC_R(__VA_ARGS__)

#define LT_BASIC_L(kc_0, kc_1, kc_2, kc_3, kc_4) \
        LT(_SYS, (kc_0)),                        \
        LT(_BLE, (kc_1)),                        \
        (kc_2),                                  \
        LT(_I3, (kc_3)),                         \
        (kc_4)
#define LYRS_L(...) LT_BASIC_L(__VA_ARGS__)

#define LT_BASIC_R(kc_4, kc_3, kc_2, kc_1, kc_0) \
        (kc_4),                                  \
        LT(_I3, (kc_3)),                         \
        (kc_2),                                  \
        LT(_BLE, (kc_1)),                        \
        LT(_SYS, (kc_0))
#define LYRS_R(...) LT_BASIC_R(__VA_ARGS__)

#define _____________________________________________________ \
          _______,   _______,   _______,   _______,   _______

#define _______________________________                       \
          _______,   _______,   _______

#define ___ _______


#define FUNC_ERGO_L__________________________________________ \
            KC_F7,     KC_F5,     KC_F3,     KC_F1,     KC_F9
#define NUMROW_ERGO_L________________________________________ \
             KC_7,      KC_5,      KC_3,      KC_1,      KC_9
#define NUMROW_ERGO_L_MODS___________________________________ \
 MODS_L(NUMROW_ERGO_L________________________________________)

#define FUNC_ERGO_R__________________________________________ \
            KC_F8,    KC_F10,     KC_F2,     KC_F4,     KC_F6
#define NUMROW_ERGO_R________________________________________ \
             KC_8,      KC_0,      KC_2,      KC_4,      KC_6
#define NUMROW_ERGO_R_MODS___________________________________ \
 MODS_R(NUMROW_ERGO_R________________________________________)


#define FUNC_L_______________________________________________ \
            KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5
#define NUMROW_L_____________________________________________ \
             KC_1,      KC_2,      KC_3,      KC_4,      KC_5
#define NUMROW_L_MODS________________________________________ \
 MODS_L(NUMROW_L_____________________________________________)

#define FUNC_R_______________________________________________ \
            KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10
#define NUMROW_R_____________________________________________ \
             KC_6,      KC_7,      KC_8,      KC_9,      KC_0
#define NUMROW_R_MODS________________________________________ \
 MODS_R(NUMROW_R_____________________________________________)


#define THUMB_ERGO_L___________________                       \
                  OSM(MOD_LSFT), LT(_NAV, KC_SPC), OSL(_SYM)

#define THUMB_ERGO_R___________________                       \
        OSL(_SYM), LT(_NUM, KC_BSPC), OSM(MOD_LSFT)

#define COLEMAK_DHM_L1_______________________________________ \
             KC_Q,      KC_W,      KC_F,      KC_P,      KC_B
#define COLEMAK_DHM_L2_______________________________________ \
             KC_A,      KC_R,      KC_S,      KC_T,      KC_G
#define COLEMAK_DHM_L3_______________________________________ \
             KC_Z,      KC_X,      KC_C,      KC_D,      KC_V
#define COLEMAK_DHM_L2_MODS__________________________________ \
 MODS_L(COLEMAK_DHM_L2_______________________________________)
#define COLEMAK_DHM_L3_LYRS__________________________________ \
 LYRS_L(COLEMAK_DHM_L3_______________________________________)

#define COLEMAK_DHM_R1_______________________________________ \
             KC_J,      KC_L,      KC_U,      KC_Y,   KC_QUOT
#define COLEMAK_DHM_R2_______________________________________ \
             KC_M,      KC_N,      KC_E,      KC_I,      KC_O
#define COLEMAK_DHM_R3_______________________________________ \
             KC_K,      KC_H,   KC_COMM,    KC_DOT,   KC_SCLN
#define COLEMAK_DHM_R2_MODS__________________________________ \
 MODS_R(COLEMAK_DHM_R2_______________________________________)

#define LAYOUT_COMMON_COLEMAK_DHM                              \
        COLEMAK_DHM_L1_______________________________________, \
        COLEMAK_DHM_R1_______________________________________, \
        COLEMAK_DHM_L2_MODS__________________________________, \
        COLEMAK_DHM_R2_MODS__________________________________, \
        COLEMAK_DHM_L3_LYRS__________________________________, \
        COLEMAK_DHM_R3_______________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________


#define QWERTY_L1____________________________________________ \
             KC_Q,      KC_W,      KC_E,      KC_R,      KC_T
#define QWERTY_L2____________________________________________ \
             KC_A,      KC_S,      KC_D,      KC_F,      KC_G
#define QWERTY_L3____________________________________________ \
             KC_Z,      KC_X,      KC_C,      KC_V,      KC_B
#define QWERTY_L2_MODS_______________________________________ \
 MODS_L(QWERTY_L2____________________________________________)
#define QWERTY_L3_LYRS_______________________________________ \
 LYRS_L(QWERTY_L3____________________________________________)

#define QWERTY_R1____________________________________________ \
             KC_Y,      KC_U,      KC_I,      KC_O,      KC_P
#define QWERTY_R2____________________________________________ \
             KC_H,      KC_J,      KC_K,      KC_L,   KC_QUOT
#define QWERTY_R3____________________________________________ \
             KC_N,      KC_M,   KC_COMM,    KC_DOT,   KC_SCLN
#define QWERTY_R2_MODS_______________________________________ \
 MODS_R(QWERTY_R2____________________________________________)

#define LAYOUT_COMMON_QWERTY                                   \
        QWERTY_L1____________________________________________, \
        QWERTY_R1____________________________________________, \
        QWERTY_L2_MODS_______________________________________, \
        QWERTY_R2_MODS_______________________________________, \
        QWERTY_L3_LYRS_______________________________________, \
        QWERTY_R3____________________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________


#define DVORAK_L1____________________________________________ \
          KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y
#define DVORAK_L2____________________________________________ \
             KC_A,      KC_O,      KC_E,      KC_U,      KC_I
#define DVORAK_L3____________________________________________ \
          KC_SCLN,      KC_Q,      KC_J,      KC_K,      KC_X
#define DVORAK_L2_MODS_______________________________________ \
 MODS_L(DVORAK_L2____________________________________________)
#define DVORAK_L3_LYRS_______________________________________ \
 LYRS_L(DVORAK_L3____________________________________________)

#define DVORAK_R1____________________________________________ \
             KC_F,      KC_G,      KC_C,      KC_R,      KC_L
#define DVORAK_R2____________________________________________ \
             KC_D,      KC_H,      KC_T,      KC_N,      KC_S
#define DVORAK_R3____________________________________________ \
             KC_B,      KC_M,      KC_W,      KC_V,      KC_Z
#define DVORAK_R2_MODS_______________________________________ \
 MODS_R(DVORAK_R2____________________________________________)

#define LAYOUT_COMMON_DVORAK                                   \
        DVORAK_L1____________________________________________, \
        DVORAK_R1____________________________________________, \
        DVORAK_L2_MODS_______________________________________, \
        DVORAK_R2_MODS_______________________________________, \
        DVORAK_L3_LYRS_______________________________________, \
        DVORAK_R3____________________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________


#define COLEMAK_L1___________________________________________ \
             KC_Q,      KC_W,      KC_F,      KC_P,      KC_G
#define COLEMAK_L2___________________________________________ \
             KC_A,      KC_R,      KC_S,      KC_T,      KC_D
#define COLEMAK_L3___________________________________________ \
             KC_Z,      KC_X,      KC_C,      KC_V,      KC_B
#define COLEMAK_L2_MODS______________________________________ \
 MODS_L(COLEMAK_L2___________________________________________)
#define COLEMAK_L3_LYRS______________________________________ \
 LYRS_L(COLEMAK_L3___________________________________________)

#define COLEMAK_R1___________________________________________ \
             KC_J,      KC_L,      KC_U,      KC_Y,   KC_QUOT
#define COLEMAK_R2___________________________________________ \
             KC_H,      KC_N,      KC_E,      KC_I,      KC_O
#define COLEMAK_R3___________________________________________ \
             KC_K,      KC_M,   KC_COMM,    KC_DOT,   KC_SCLN
#define COLEMAK_R2_MODS______________________________________ \
 MODS_R(COLEMAK_R2___________________________________________)

#define LAYOUT_COMMON_COLEMAK                                  \
        COLEMAK_L1___________________________________________, \
        COLEMAK_R1___________________________________________, \
        COLEMAK_L2_MODS______________________________________, \
        COLEMAK_R2_MODS______________________________________, \
        COLEMAK_L3_LYRS______________________________________, \
        COLEMAK_R3___________________________________________, \
        THUMB_ERGO_L___________________,                       \
        THUMB_ERGO_R___________________


#define SYSTEM_L1____________________________________________ \
            RESET,     DEBUG,   MG_NKRO,    DF_MOD,   RGB_TOG
#define SYSTEM_L2____________________________________________ \
          KC_LSFT,   KC_LCTL,   KC_LALT,   KC_LGUI,   KC_CAPS
#define SYSTEM_L3____________________________________________ \
          RESET,     _______,   _______,  TG(_NAV),   _______
#define SYSTEM_L4______________________                       \
                              _______________________________

#define SYSTEM_R1____________________________________________ \
          RGB_MOD,   RGB_SPI,   RGB_HUI,   RGB_SAI,   RGB_VAI
#define SYSTEM_R2____________________________________________ \
          KC_BRIU,   KC_MPRV,   KC_MPLY,   KC_MUTE,   KC_MNXT
#define SYSTEM_R3____________________________________________ \
          KC_BRID,  TG(_NUM),   KC_VOLD,   KC_VOLU,   RESET
#define SYSTEM_R4______________________                       \
        _______________________________


#define LAYOUT_COMMON_SYSTEM                                   \
        SYSTEM_L1____________________________________________, \
        SYSTEM_R1____________________________________________, \
        SYSTEM_L2____________________________________________, \
        SYSTEM_R2____________________________________________, \
        SYSTEM_L3____________________________________________, \
        SYSTEM_R3____________________________________________, \
        SYSTEM_L4______________________,                       \
        SYSTEM_R4______________________

#define I3_L1________________________________________________ \
          G(A(KC_1)), G(A(KC_2)), G(A(KC_3)), G(A(KC_4)), G(A(KC_5))
#define I3_L2________________________________________________ \
          G(KC_1),    G(KC_2),    G(KC_3),    G(KC_4),    G(KC_5)
#define I3_L3________________________________________________ \
          _______,   _______,   _______,  _______,   _______
#define I3_L4__________________________                       \
                              _______________________________

#define I3_R1________________________________________________ \
          G(A(KC_6)), G(A(KC_7)), G(A(KC_8)), G(A(KC_9)), G(A(KC_0))
#define I3_R2________________________________________________ \
          G(KC_6),    G(KC_7),    G(KC_8),    G(KC_9),    G(KC_0)
#define I3_R3________________________________________________ \
          _______,   _______,   _______,   _______,   _______
#define I3_R4__________________________                       \
        _______________________________

#define LAYOUT_COMMON_I3                                       \
        I3_L1________________________________________________, \
        I3_R1________________________________________________, \
        I3_L2________________________________________________, \
        I3_R2________________________________________________, \
        I3_L3________________________________________________, \
        I3_R3________________________________________________, \
        I3_L4__________________________,                       \
        I3_R4__________________________


#define BLE_L1_______________________________________________ \
          DELBNDS,   AD_WO_L,   _______,  BLE_DIS,   BLE_EN
#define BLE_L2_______________________________________________ \
          BATT_LV,   _______,   ENT_DFU,  USB_DIS,   USB_EN
#define BLE_L3_______________________________________________ \
          RESET,     _______,   _______,  _______,   _______
#define BLE_L4_________________________                       \
                              _______________________________

#define BLE_R1_______________________________________________ \
          BLE_EN ,   BLE_DIS,   _______,  AD_WO_L,   DELBNDS
#define BLE_R2_______________________________________________ \
          USB_EN ,   USB_DIS,   ENT_DFU,  _______,   BATT_LV
#define BLE_R3_______________________________________________ \
        _______,     _______,   _______,  _______,   RESET
#define BLE_R4_________________________                       \
        _______________________________

#define LAYOUT_COMMON_BLE                                      \
        BLE_L1_______________________________________________, \
        BLE_R1_______________________________________________, \
        BLE_L2_______________________________________________, \
        BLE_R2_______________________________________________, \
        BLE_L3_______________________________________________, \
        BLE_R3_______________________________________________, \
        BLE_L4_________________________,                       \
        BLE_R4_________________________


#define NAVIGATION_L1________________________________________ \
          KC_PSCR,   KC_ACL0,   KC_ACL1,   KC_ACL2,   _______
#define NAVIGATION_L2________________________________________ \
          KC_LSFT,   KC_LCTL,   KC_LALT,   KC_LGUI,   KC_BTN3
#define NAVIGATION_L3________________________________________ \
          _______,   KC_WH_U,   KC_WH_D,  TG(_NAV),    KC_INS
#define NAVIGATION_L4__________________                       \
                                _______,   _______,    KC_ESC

#define NAVIGATION_R1________________________________________ \
          KC_BSPC,   KC_HOME,   KC_PGDN,   KC_PGUP,    KC_END
#define NAVIGATION_R2________________________________________ \
          KC_BTN2,   KC_LEFT,   KC_DOWN,     KC_UP,   KC_RGHT
#define NAVIGATION_R3________________________________________ \
          KC_BTN1,   KC_MS_L,   KC_MS_D,   KC_MS_U,   KC_MS_R
#define NAVIGATION_R4__________________                       \
           KC_DEL,    KC_ENT,   _______

#define LAYOUT_COMMON_NAVIGATION                               \
        NAVIGATION_L1________________________________________, \
        NAVIGATION_R1________________________________________, \
        NAVIGATION_L2________________________________________, \
        NAVIGATION_R2________________________________________, \
        NAVIGATION_L3________________________________________, \
        NAVIGATION_R3________________________________________, \
        NAVIGATION_L4__________________,                       \
        NAVIGATION_R4__________________


#define NUMERAL_GEN_L4_________________                       \
                                _______,    KC_TAB,    KC_ESC

#define NUMERAL_GEN_R4_________________                       \
        _______________________________

#define NUMERAL_ERGO_L1______________________________________ \
        FUNC_ERGO_L__________________________________________
#define NUMERAL_ERGO_L2______________________________________ \
        NUMROW_ERGO_L_MODS___________________________________
#define NUMERAL_ERGO_L3______________________________________ \
           KC_F12,    KC_F11,   KC_MINS,    KC_SPC,   KC_BSPC
#define NUMERAL_ERGO_L4________________                       \
                              NUMERAL_GEN_L4_________________

#define NUMERAL_ERGO_R1______________________________________ \
        FUNC_ERGO_R__________________________________________
#define NUMERAL_ERGO_R2______________________________________ \
        NUMROW_ERGO_R_MODS___________________________________
#define NUMERAL_ERGO_R3______________________________________ \
           KC_DEL,  TG(_NUM),   _______,   _______,   KC_SLSH
#define NUMERAL_ERGO_R4________________                       \
        NUMERAL_GEN_R4_________________

#define LAYOUT_COMMON_NUMERAL_ERGO                             \
        NUMERAL_ERGO_L1______________________________________, \
        NUMERAL_ERGO_R1______________________________________, \
        NUMERAL_ERGO_L2______________________________________, \
        NUMERAL_ERGO_R2______________________________________, \
        NUMERAL_ERGO_L3______________________________________, \
        NUMERAL_ERGO_R3______________________________________, \
        NUMERAL_ERGO_L4________________,                       \
        NUMERAL_ERGO_R4________________


#define NUMERAL_L1___________________________________________ \
        FUNC_L_______________________________________________
#define NUMERAL_L2___________________________________________ \
        NUMROW_L_MODS________________________________________
#define NUMERAL_L3___________________________________________ \
           KC_F11,    KC_F12,   KC_MINS,    KC_SPC,   KC_BSPC
#define NUMERAL_L4_____________________                       \
                              NUMERAL_GEN_L4_________________

#define NUMERAL_R1___________________________________________ \
        FUNC_R_______________________________________________
#define NUMERAL_R2___________________________________________ \
        NUMROW_R_MODS________________________________________
#define NUMERAL_R3___________________________________________ \
           KC_DEL,  TG(_NUM),   _______,   _______,   KC_SLSH
#define NUMERAL_R4_____________________                       \
        NUMERAL_GEN_R4_________________

#define LAYOUT_COMMON_NUMERAL                                  \
        NUMERAL_L1___________________________________________, \
        NUMERAL_R1___________________________________________, \
        NUMERAL_L2___________________________________________, \
        NUMERAL_R2___________________________________________, \
        NUMERAL_L3___________________________________________, \
        NUMERAL_R3___________________________________________, \
        NUMERAL_L4_____________________,                       \
        NUMERAL_GEN_R4_________________


#define SYMBOL_L1____________________________________________ \
          KC_EXLM,     KC_AT,   KC_HASH,    KC_DLR,   KC_PERC
#define SYMBOL_L2____________________________________________ \
          KC_PLUS,    KC_EQL,   KC_LPRN,   KC_RPRN,    KC_DQT
#define SYMBOL_L3____________________________________________ \
            KC_LT,   KC_PIPE,   KC_MINS,     KC_GT,   KC_BSLS
#define SYMBOL_L4______________________                       \
                                _______,  _______,   _______
#define SYMBOL_L2_MODS_______________________________________ \
 MODS_L(   KC_F21,    KC_EQL,    KC_F23,    KC_F24,    KC_DQT)

#define SYMBOL_R1____________________________________________ \
          KC_CIRC,   KC_AMPR,   KC_ASTR,   KC_QUES,   KC_QUOT
#define SYMBOL_R2____________________________________________ \
          KC_COLN,   KC_RBRC,   KC_LBRC,   KC_RCBR,   KC_LCBR
#define SYMBOL_R3____________________________________________ \
           KC_GRV,   KC_UNDS,   KC_SLSH,   KC_TILD,   KC_SCLN
#define SYMBOL_R4______________________                       \
          _______, _______,   _______
#define SYMBOL_R2_MODS_______________________________________ \
 MODS_R(  KC_COLN,   KC_RBRC,   KC_LBRC,    KC_F23,    KC_F24)

#define LAYOUT_COMMON_SYMBOL                                   \
        SYMBOL_L1____________________________________________, \
        SYMBOL_R1____________________________________________, \
        SYMBOL_L2_MODS_______________________________________, \
        SYMBOL_R2_MODS_______________________________________, \
        SYMBOL_L3____________________________________________, \
        SYMBOL_R3____________________________________________, \
        SYMBOL_L4______________________,                       \
        SYMBOL_R4______________________

// clang-format on

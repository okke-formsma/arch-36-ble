#pragma once

#include "quantum.h"

#define LAYOUT( \
    L00, L01, L02, L03, L04,    R05, R06, R07, R08, R09, \
    L10, L11, L12, L13, L14,    R15, R16, R17, R18, R19, \
    L20, L21, L22, L23, L24,    R25, R26, R27, R28, R29, \
              L32, L33, L34,    R35, R36, R37 \
) \
{ \
    { L00,   L01,   L02,   L03,   L04 }, \
    { L10,   L11,   L12,   L13,   L14 }, \
    { L20,   L21,   L22,   L23,   L24 }, \
    { KC_NO, KC_NO, L32,   L33,   L34 }, \
    { R09,   R08,   R07,   R06,   R05 }, \
    { R19,   R18,   R17,   R16,   R15 }, \
    { R29,   R28,   R27,   R26,   R25 }, \
    { KC_NO, KC_NO, R37,   R36,   R35 }, \
}


#define LAYOUT_kc( \
     L00, L01, L02, L03, L04, L05,           R00, R01, R02, R03, R04, R05, \
     L10, L11, L12, L13, L14, L15,           R10, R11, R12, R13, R14, R15, \
     L20, L21, L22, L23, L24, L25,           R20, R21, R22, R23, R24, R25, \
                         L30, L31, L32, R30, R31, R32 \
  ) \
  LAYOUT( \
  KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04, KC_##L05,                     KC_##R00, KC_##R01, KC_##R02, KC_##R03, KC_##R04, KC_##R05, \
  KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14, KC_##L15,                     KC_##R10, KC_##R11, KC_##R12, KC_##R13, KC_##R14, KC_##R15, \
  KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24, KC_##L25,                     KC_##R20, KC_##R21, KC_##R22, KC_##R23, KC_##R24, KC_##R25, \
                                          KC_##L30, KC_##L31, KC_##L32, KC_##R30, KC_##R31, KC_##R32 \
  )


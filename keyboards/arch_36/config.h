/*
Copyright 2019 Obosob <obosob@riseup.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "config_common.h"


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    obosob
#define PRODUCT         Arch-36 Keyboard
#define DESCRIPTION     Split 30 percent ergonomic keyboard

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

// wiring
#define MATRIX_ROW_PINS { D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F7, B1, B3, B2, B6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D2

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN D3
#define RGBLED_SPLIT { 6, 6 }
#define RGBLED_NUM 12
#define RGBLIGHT_LED_MAP {  2,  1,  0,   5,  4,  3, \
                            9, 10, 11,   6,  7,  8 }
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define EE_HANDS
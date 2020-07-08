/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2018 Sekigon

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

#define ENABLE_STARTUP_ADV_NOLIST

/* Pretty fast bluetooth settings */
#define BLE_NUS_MIN_INTERVAL 30
#define BLE_NUS_MAX_INTERVAL 30
#define BLE_HID_MAX_INTERVAL 50
#define BLE_HID_SLAVE_LATENCY 3

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    obosob
#define PRODUCT         Arch-36 Keyboard
#define DESCRIPTION     Split 30 percent ergonomic keyboard

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    1

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */ 
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#define PROGMEM // arm-gcc does not interpret PROGMEM

#define RGB_DI_PIN PIN1 //D3     // The pin the LED strip is connected to
#define RGBLED_NUM 6
#define RGBLIGHT_SPLIT 6


#ifdef OLED_ENABLE
  #define SSD1306OLED
#endif
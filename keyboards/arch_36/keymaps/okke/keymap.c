/* Copyright 2020 Okke Formsma <okke@formsma.nl>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

uint16_t copy_paste_timer;

enum layers {
    QWERTY = 0,
    COLEMAK,
    SPECIALS,
    NUMBERS,
    NAV,
    I3
};

#define OK_A    MT(MOD_LCTL, KC_A)
#define OK_S    MT(MOD_LGUI, KC_S)
#define OK_D    MT(MOD_LALT, KC_D)
#define OK_F    MT(MOD_LSFT, KC_F)
#define OK_J    MT(MOD_RSFT, KC_J)
#define OK_K    MT(MOD_RALT, KC_K)
#define OK_L    MT(MOD_RGUI, KC_L)
#define OK_SCLN    MT(MOD_RCTL, KC_SCLN)
#define OK_QUOT    MT(MOD_RCTL, KC_QUOT)
#define OK_V    LT(I3, KC_V)
#define OK_M    LT(I3, KC_M)


#define CM_A    MT(MOD_LCTL, KC_A)
#define CM_R    MT(MOD_LGUI, KC_R)
#define CM_S    MT(MOD_LALT, KC_S)
#define CM_T    MT(MOD_LSFT, KC_T)
#define CM_N    MT(MOD_RSFT, KC_N)
#define CM_E    MT(MOD_LALT, KC_E)
#define CM_I    MT(MOD_LGUI, KC_I)
#define CM_O    MT(MOD_LCTL, KC_O)
#define CM_D    LT(I3, KC_D)
#define CM_H    LT(I3, KC_H)


#define OK_GRV  MT(MOD_LCTL, KC_GRV)
#define OK_1    MT(MOD_LCTL, KC_1)
#define OK_2    MT(MOD_LGUI, KC_2)
#define OK_3    MT(MOD_LALT, KC_3)
#define OK_4    MT(MOD_LSFT, KC_4)
#define OK_7    MT(MOD_LSFT, KC_7)
#define OK_8    MT(MOD_LALT, KC_8)
#define OK_9    MT(MOD_LGUI, KC_9)
#define OK_0    MT(MOD_LCTL, KC_0)

#define OK_F5   MT(MOD_LCTL, KC_F5)
#define OK_F6   MT(MOD_LGUI, KC_F6)
#define OK_F7   MT(MOD_LALT, KC_F7)
#define OK_F8   MT(MOD_LSFT, KC_F8)

#define OK_QWE TO(QWERTY)
#define OK_COL TO(COLEMAK)

// THUMB KEYS
#define OK_TAB LT(NAV, KC_TAB)
#define OK_SPC LT(SPECIALS, KC_SPC)
#define OK_ENT LT(NUMBERS, KC_ENT)
#define OK_BSPC LT(NAV, KC_BSPC)
#define OK_SHFT OSM(MOD_LSFT)
#define OK_DEL LT(NUMBERS, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY/COLEMAK
 */
    [QWERTY] = LAYOUT(
      KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   
      OK_A,   OK_S,   OK_D,   OK_F,   KC_G,    KC_H,    OK_J,    OK_K,    OK_L,    OK_QUOT,
      KC_Z,   KC_X,   KC_C,   OK_V,   KC_B,    KC_N,    OK_M,    KC_COMM, KC_DOT,  KC_SCLN,
                      OK_TAB, OK_SPC,  OK_ENT,  OK_BSPC, OK_SHFT, OK_DEL
    ),
    [COLEMAK] = LAYOUT(
      KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
      CM_A,   CM_R,   CM_S,   CM_T,   KC_G,   KC_M,    CM_N,    CM_E,    CM_I,    CM_O,   
      KC_Z,   KC_X,   KC_C,   CM_D,   KC_V,   KC_K,    CM_H,    KC_COMM, KC_DOT,  KC_SCLN,
                     _______, _______, _______, _______, _______, _______
    ),

/*
 * Specials: specials
 */
    [SPECIALS] = LAYOUT(
      KC_EXLM, KC_AT,  KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_GRV,  KC_TILD,
      KC_PLUS, KC_EQL, KC_LPRN, KC_RPRN, KC_NO,   KC_NO,   KC_RBRC, KC_LBRC, KC_RCBR, KC_LCBR,   
      KC_BSLS, KC_PIPE, KC_MINS, KC_UNDS, KC_NO,  KC_NO,   KC_COLN, KC_SCLN, KC_QUES, KC_SLSH, 
                         _______, _______, _______, _______,  KC_DEL, KC_BSPC
    ),
/*
* numbers
*/
    [NUMBERS] = LAYOUT(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
      KC_F11,   KC_F12,  KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_BTN5, KC_NO,
                        _______, _______, _______, _______, _______, _______
    ),
/*
 * navigation
 */
    [NAV] = LAYOUT(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
      OK_F5,   OK_F6,   OK_F7,   OK_F8,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
      KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CAPS, KC_BTN4, _______, _______, KC_BTN5, _______,
                        _______, _______, _______, _______, _______, _______ 
    ),
/* i3 hotkeys - top row carries windows to workspace, home row navigates to workspace.*/
    [I3] = LAYOUT(
      G(A(KC_1)), G(A(KC_2)), G(A(KC_3)), G(A(KC_4)), G(A(KC_5)), G(A(KC_6)), G(A(KC_7)), G(A(KC_8)), G(A(KC_9)), G(A(KC_0)),
      G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5), G(KC_6), G(KC_7), G(KC_8), G(KC_9), G(KC_0),
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                        _______, _______, _______, _______, _______, _______
    ),
};

/*
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CM_A:
        case CM_O:
        //case OK_A: //same as CM_A
        case OK_SCLN:
            return 100;
        case LT(1, KC_GRV):
            return 130;
        default:
            return TAPPING_TERM;
    }
}
*/

#ifdef COMBO_ENABLE
enum combos {
    COMBO_ESC,
};

const uint16_t PROGMEM combo_esc[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
};
#endif

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_0;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

bool is_keyboard_left(void);
void render_status_bar(void) {
    uint8_t modifiers = get_mods();
    if(is_keyboard_left()) {
        oled_write_P(PSTR("ctrl"), (modifiers & MOD_MASK_CTRL));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("gui"), (modifiers & MOD_MASK_GUI));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("alt"), (modifiers & MOD_MASK_ALT));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("shift"), (modifiers & MOD_MASK_SHIFT));
    } else {
        oled_write_P(PSTR("shift"), (modifiers & MOD_MASK_SHIFT));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("alt"), (modifiers & MOD_MASK_ALT));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("gui"), (modifiers & MOD_MASK_GUI));
        oled_write_P(PSTR(" "), false);
        oled_write_P(PSTR("ctrl"), (modifiers & MOD_MASK_CTRL));
    }
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("       Okke\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case QWERTY:
            oled_write_P(PSTR("qwerty\n"), false);
            break;
        case COLEMAK:
            oled_write_P(PSTR("colemak\n"), false);
            break;
        case NUMBERS:
            oled_write_P(PSTR("numbers\n"), false);
            break;
        case SPECIALS:
            oled_write_P(PSTR("specials\n"), false);
            break;
        case NAV:
            oled_write_P(PSTR("navigtion\n"), false);
            break;
        case I3:
            oled_write_P(PSTR("i3\n"), false);
            break;
        default:
            oled_write_P(PSTR("whut?\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)    ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)   ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
        render_status_bar();
    }
}
#endif
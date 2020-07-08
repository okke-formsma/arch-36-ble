#include QMK_KEYBOARD_H
#include "app_ble_func.h"

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "eeprom.h"

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

const uint8_t is_master = IS_LEFT_HAND;

void nrfmicro_power_enable(bool enable);
extern uint8_t nrfmicro_switch_pin(void);

bool has_usb(void);

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layers {
    QWERTY = 0,
    COLEMAK,
    NUMBERS,
    SYM,
    NAV,
    BLE
};

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
};


#define OK_A    MT(MOD_LCTL, KC_A)
#define OK_S    MT(MOD_LGUI, KC_S)
#define OK_D    MT(MOD_LALT, KC_D)
#define OK_F    MT(MOD_LSFT, KC_F)
#define OK_J    MT(MOD_RSFT, KC_J)
#define OK_K    MT(MOD_RALT, KC_K)
#define OK_L    MT(MOD_RGUI, KC_L)
#define OK_SCLN    MT(MOD_RCTL, KC_SCLN)


#define CM_A    MT(MOD_LCTL, KC_A)
#define CM_R    MT(MOD_LGUI, KC_R)
#define CM_S    MT(MOD_LALT, KC_S)
#define CM_T    MT(MOD_LSFT, KC_T)
#define CM_N    MT(MOD_RSFT, KC_N)
#define CM_E    MT(MOD_LALT, KC_E)
#define CM_I    MT(MOD_LGUI, KC_I)
#define CM_O    MT(MOD_LCTL, KC_O)

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


#define OK_ENNUM LT(NUMBERS, KC_ENT) /* enter numbers */
#define OK_SPMOV LT(MOVE, KC_SPC) /* space numbers */
#define OK_NUM MO(NUMBERS)
#define OK_MOV MO(MOVE)
#define OK_QWE TO(QWERTY)
#define OK_COL TO(COLEMAK)

#define TAB_BLE LT(BLE, KC_TAB)
#define SP_NUM LT(NUMBERS, KC_SPC)
#define EN_MOV LT(MOVE, KC_ENT)
#define DEL_MOV LT(MOVE, KC_DEL)
#define BSP_NUM LT(NUMBERS, KC_BSPC)
#define ESC_BLE LT(BLE, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: QWERTY
 *
 * ,----------------------------------.                              ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|                              |------+------+------+------+------|
 * |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |
 * |  ctrl|  gui | alt  | shift|      |                              |      | shift| alt  |  gui | ctrl |
 * |------+------+------+------+------+                              +------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |                              |   N  |   M  | ,  < | . >  | /  ? |
 * `-------------+------+------+------+------+------|  |------+------+------+------+------+-------------'
 *                             | tab  | spc  | ent  |  | del  | bspc | esc  |
 *                             | ble  | numb | move |  | move | numb | ble  |
 *                             ----------------------  ----------------------
 */
    [QWERTY] = LAYOUT(
      KC_Q,   KC_W,   KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   
      OK_A,   OK_S,   OK_D,   OK_F,    KC_G,    KC_H,    OK_J,    OK_K,    OK_L,    OK_SCLN,
      KC_Z,   KC_X,   KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT,
                      TAB_BLE, SP_NUM,  EN_MOV,  DEL_MOV, BSP_NUM, ESC_BLE
    ),
/*
 * Numbers: numbers, specials
 * keep ,. for easy typing of numbers and IPs, keep backspace
 * ,----------------------------------.  ,----------------------------------.
 * |  !   |  @   |  #   |  $   |  %   |  |  ^   |  &   |  *   |  (   |  )   |
 * |------+------+------+------+------|  |------+------+------+------+------|
 * |  1   |  2   |  3   |  4   |  5   |  |  6   |  7   |  8   |  9   |  0   |
 * |  ctrl|  gui | alt  | shift|      |  |      | shift| alt  |  gui | ctrl |
 * |------+------+------+------+------+  +------+------+------+------+------|
 * |  ~   |  `   |  _   |  [   |  ]   |  |  {   |  }   |      |      |  +   |
 * `-------------+------+------+------+  +------+------+------+-------------'
 * 
 */
    [NUMBERS] = LAYOUT(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,  OK_F5,   OK_F6,   OK_F7,   OK_F8, KC_F9,   KC_F10,
      OK_1,    OK_2,   OK_3,    OK_4,    KC_5,     KC_6,    OK_7,    OK_8,    OK_9,    OK_0,   
      KC_F11,  KC_F12,
      KC_TILD, KC_GRV, KC_UNDS, KC_LBRC, ENT_DFU, ENT_DFU, KC_RCBR, _______, _______, KC_PLUS,
                       _______, _______, _______, KC_BSPC, _______, KC_DEL
    ),
/*
 * F-keys, navigation
 *
 * ,----------------------------------.   ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |      |   | home | pgdn | pgup | end  |      |
 * |------+------+------+------+------|   |------+------+------+------+------|
 * |  F5  |  F6  |  F7  |  F8  |      |   | left | down | up   | right|      |
 * |  ctrl|  gui | alt  | shift|      |
 * |------+------+------+------+------+   +------+------+------+------+------|
 * |  F9  |  F10 |  F11 |  F12 | CAPS |   | mous4|      |      | mous5|      |
 * `-------------+------+------+------+   +------+------+------+-------------'
 * mous4 = back
 * mous5 = forward
 */
    [SYM] = LAYOUT(
      KC_EXLM, KC_AT,  KC_HASH, KC_DLR , KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
      KC_PLUS, KC_EQ
                        _______, _______, _______, _______, _______, _______
    ),
    [NAV] = LAYOUT(
      KC_EXLM, KC_AT,  KC_HASH, KC_DLR , KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
      OK_F5,   OK_F6,   OK_F7,   OK_F8,   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
      KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_CAPS, KC_BTN4, _______, _______, KC_BTN5, _______,
                        _______, _______, _______, _______, _______, _______
    ),
    [BLE] = LAYOUT(
      AD_WO_L, USB_EN,  USB_DIS, BLE_EN, BLE_DIS, BLE_DIS, BLE_EN,  USB_DIS, USB_EN,  AD_WO_L,
      ADV_ID0, ADV_ID1, ADV_ID2, ADV_ID3, ADV_ID4, ADV_ID4, ADV_ID3, ADV_ID2, ADV_ID1, ADV_ID0,
      DEL_ID0, DEL_ID1, DEL_ID2, DEL_ID3, DEL_ID4, DEL_ID4, DEL_ID3, DEL_ID2, DEL_ID1, DEL_ID0,
      
                        DELBNDS, _______, _______, _______, _______, DELBNDS
    ),
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  layer_state_set(default_layer);
}

// // Setting ADJUST layer RGB back to default
// void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
//   if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
//     #ifdef RGBLIGHT_ENABLE
//        //rgblight_mode(RGB_current_mode);
//     #endif
//     layer_on(layer3);
//   } else {
//     layer_off(layer3);
//   }
// }

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  //NRF_LOG_INFO("process_record_user, keycode: %d\n", keycode);

#ifdef SSD1306OLED
  iota_gfx_flush(); // wake up screen
#endif

  if (record->event.pressed) {
    set_keylog(keycode, record);
    //set_timelog();


    //eeprom_write_dword(EECONFIG_RGBLIGHT, 666);
  }

  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      return false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }
  }

  return true;
}

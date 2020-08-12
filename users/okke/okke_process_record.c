
#include QMK_KEYBOARD_H
#include "app_ble_func.h"

#include "okke_process_record.h"
#include "okke.h"
#include "print.h"


#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#include "eeprom.h"
#include <string.h>


const uint8_t is_master = IS_LEFT_HAND;

void nrfmicro_power_enable(bool enable);
extern uint8_t nrfmicro_switch_pin(void);

bool has_usb(void);


__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, print matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
#  if defined(REVERSE_ROW_COL)
  xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.row, record->event.key.col, record->event.pressed);
#  else
  xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#  endif
#endif // KEYLOGGER_ENABLE

  bool handoff = true;

  /* Use normal Numeral LAYOUT with some default layer(s) */
  if (keycode >> 8 == LT(_NUM, KC_NO) >> 8) {
    switch (biton32(default_layer_state)) {
      case _QWERTY:
        { action_t action;
          action.code = ACTION_LAYER_TAP_KEY(_NUM_N & 0xF, keycode & 0xFF);
          process_action(record, action);
        }
        handoff = false;
        break;
    }
  } else if (keycode == TG(_NUM)) {
    switch (biton32(default_layer_state)) {
      case _QWERTY:
        { action_t action;
          action.code = ACTION_LAYER_TOGGLE(_NUM_N & 0xFF);
          process_action(record, action);
        }
        handoff = false;
        break;
    }
  }
  /* Handle advanced keycodes in mod-tap macros */
#ifdef MT_MAP_KEYMAP
  MT_MAP_KEYMAP
#endif // MT_MAP_KEYMAP
#ifdef MT_MAP_USER
  MT_MAP_USER
#endif // MT_MAP_USER
  if(!process_record_ble(keycode, record)) {
    return false;
  }
  switch (keycode) {
    case DF_MODE_FORWARD:
    case DF_MODE_REVERSE:
      process_record_df_mode(keycode, record);
      break;
    case SKC_BULLET_ELLIPSIS:
      process_record_skc(A(KC_8), A(KC_SCLN), record);
      break;
    case SKC_NDASH_MDASH:
      process_record_skc(A(KC_MINS), S(A(KC_MINS)), record);
      break;
  }

  return process_record_keymap(keycode, record)
    && handoff;
}


/* Cycle through default layers on tap (in reverse direction on Shift + tap).
 */
bool process_record_df_mode(uint16_t keycode, const keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }
  const uint8_t mods_held = mod_config(get_mods());
  const uint8_t mods_osm = mod_config(get_oneshot_mods());
  del_mods(mods_held);
  clear_oneshot_mods();
  if ((mods_held | mods_osm) & MOD_MASK_SHIFT) {
    keycode =
      (keycode == DF_MODE_FORWARD)
      ? DF_MODE_REVERSE
      : DF_MODE_FORWARD;
  }
  uint8_t default_layer = biton32(default_layer_state);
  if (keycode == DF_MODE_FORWARD) {
    default_layer =
      (default_layer < LAYERS_BASIC_MAX)
      ? default_layer + 1
      : LAYERS_BASIC;
  } else {
    default_layer =
      (default_layer > LAYERS_BASIC
      && default_layer <= LAYERS_BASIC_MAX)
      ? default_layer - 1
      : LAYERS_BASIC_MAX;
  }
  default_layer_set(1UL << default_layer);
  add_mods(mods_held);
  return true;
}

/* Send any keycode `kc_0` on tap, and any other keycode `kc_1` on Shift + tap.
 */
bool process_record_skc(const uint16_t kc_0, const uint16_t kc_1, const keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }
  const uint8_t mods_held = mod_config(get_mods());
  const uint8_t mods_osm = mod_config(get_oneshot_mods());
  del_mods(mods_held);
  clear_oneshot_mods();
  if ((mods_held | mods_osm) & MOD_MASK_SHIFT) {
    tap_code16(kc_1);
  } else {
    tap_code16(kc_0);
  }
  add_mods(mods_held);
  return true;
}

/* Send a standard ANSI string, applying held or one-shot shift as expected.
 */
bool process_record_ss(const char str[], const keyrecord_t *record) {
  if (!record->event.pressed) {
    return true;
  }
  const uint8_t mods_held = mod_config(get_mods());
  const uint8_t mods_osm = mod_config(get_oneshot_mods());
  del_mods(mods_held);
  clear_oneshot_mods();
  if (mods_held & MOD_MASK_SHIFT) {
    add_mods(MOD_MASK_SHIFT);
  }
  if (mods_osm & MOD_MASK_SHIFT) {
    set_oneshot_mods(MOD_MASK_SHIFT);
  }
  send_string(str);
  del_mods(MOD_MASK_SHIFT);
  clear_oneshot_mods();
  add_mods(mods_held);
  return true;
}


bool process_record_ble(uint16_t keycode, keyrecord_t *record) {
  char str[16];

  xprintf("process_record_user, keycode: %d\n", keycode);
  //NRF_LOG_INFO("process_record_user, keycode: %d\n", keycode);

  #ifdef SSD1306OLED
    iota_gfx_flush(); // wake up screen
  #endif

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



#ifdef SSD1306OLED

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//const char *read_host_led_state(void);
//const char *read_mode_icon(bool swap);

const char *read_rgb_info(void);

#include "nrf_gpio.h"
void matrix_render_user(struct CharacterMatrix *matrix) {
//  if (is_master) 
{
    //matrix_write_ln(matrix, read_layer_state());
    //matrix_write_ln(matrix, read_keylog());

    char str[64];
    {
    sprintf(str, "Okke's sweet %s", "keyboard");
    matrix_write_ln(matrix, str);

#if (IS_LEFT_HAND)
      sprintf (str, "Master: %s%s%s",
        get_usb_enabled() && !get_ble_enabled() ? "USB mode":"",
        get_ble_enabled() && ble_connected() ? "connected":"",
        get_ble_enabled() && !ble_connected() ? "disconnected":""
      );
#else
      sprintf(str, "Slave: %s", ble_connected() ? "connected" : "disconnected");
#endif

      matrix_write_ln(matrix, str);
    }

    uint8_t modifiers = get_mods();
#if (IS_LEFT_HAND)
    if(modifiers & MOD_MASK_CTRL){
      matrix_write(matrix, "ctrl ");
    }
    if(modifiers & MOD_MASK_GUI){
      matrix_write(matrix, "gui ");
    }
    if(modifiers & MOD_MASK_ALT){
      matrix_write(matrix, "alt ");
    }
    if(modifiers & MOD_MASK_SHIFT){
      matrix_write(matrix, "shift ");
    }
#else
    if(modifiers & MOD_MASK_SHIFT){
      matrix_write(matrix, "shift ");
    }
    if(modifiers & MOD_MASK_ALT){
      matrix_write(matrix, "alt ");
    }
    if(modifiers & MOD_MASK_GUI){
      matrix_write(matrix, "gui ");
    }
    if(modifiers & MOD_MASK_CTRL){
      matrix_write(matrix, "ctrl ");
    }
#endif
    matrix_write_ln(matrix, "");

    {
      char vc[16], str[32];
      int vcc = get_vcc();
      sprintf(vc, "%4dmV", vcc);
      sprintf(str, "Bat: %s USB: %s", vcc==0 || vcc>4400 || nrfmicro_switch_pin()==0 ? "off   " : vc, has_usb()? "on":"off");
      //sprintf(str, "Switch pin: %d", nrfmicro_switch_pin());
      matrix_write_ln(matrix, str);
    }

    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  }
// else {
//    matrix_write_ln(matrix, read_layer_state()); // somehow removes the dead pixel
//    matrix_write(matrix, read_logo());
//  }

}

void iota_gfx_task_user(void) {
  ScreenOffInterval = has_usb() ? 60*10*1000 : 60*5*1000; // ms
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

#endif
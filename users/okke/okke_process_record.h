#pragma once

#include "quantum.h"

enum keycodes_user {
  DF_MODE_FORWARD = SAFE_RANGE,
  DF_MODE_REVERSE,
  SKC_BULLET_ELLIPSIS,
  SKC_NDASH_MDASH,
  SAFE_RANGE_BLE
};


enum keycodes_ble {
    AD_WO_L = SAFE_RANGE_BLE, /* Start advertising without whitelist  */
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
    SAFE_RANGE_KEYMAP
};
// clang-format off

#define DF_MOD    DF_MODE_FORWARD
#define DF_RMOD   DF_MODE_REVERSE
#define MG_NKRO   MAGIC_TOGGLE_NKRO

// clang-format on


bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_ble(uint16_t keycode, keyrecord_t *record);

bool process_record_df_mode(uint16_t keycode, const keyrecord_t *record);
bool process_record_skc(const uint16_t kc_0, const uint16_t kc_1, const keyrecord_t *record);
bool process_record_ss(const char str[], const keyrecord_t *record);

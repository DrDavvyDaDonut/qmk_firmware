#pragma once

//  easier bootloader access
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1 // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17 // Specify a optional status led by GPIO number which blinks when entering the bootloader

//  booting right side
#define BOOTMAGIC_ROW_RIGHT 4
#define BOOTMAGIC_COLUMN_RIGHT 0

// 1000hz Polling Rate
#define USB_POLLING_INTERVAL_MS 1
#define NKRO_DEFAULT_ON true

#define EE_HANDS

#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define QUICK_TAP_TERM 120
#define FLOW_TAP_TERM 150

#define COMBO_VARIABLE_LEN
#define COMBO_TERM 50

//  constant mouse keys
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL        //  momentary mouse

#define MK_C_OFFSET_UNMOD     3   //  default

#define MK_C_INTERVAL_UNMOD   8

#define MK_W_OFFSET_UNMOD     1

#define MK_W_INTERVAL_UNMOD   100 //  default

//  led config
#define WS2812_DI_PIN GP25
#define RGBLIGHT_LED_COUNT 2
#define RGBLED_SPLIT { 1, 1 }

//  split syncing
// #define SPLIT_POINTING_ENABLE 
// #define SPLIT_ACTIVITY_ENABLE

#define RGBLIGHT_SLEEP
#pragma once

//  easier bootloader access
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17 // Specify a optional status led by GPIO number which blinks when entering the bootloader

// 1000hz Polling Rate
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

#define PIMORONI_TRACKBALL_SCALE 1

#define EE_HANDS

#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define QUICK_TAP_TERM 120
#define QUICK_TAP_TERM_PER_KEY


#define COMBO_VARIABLE_LEN
#define COMBO_TERM 50

//  constant mouse keys
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL        //  momentary mouse

#define MK_C_OFFSET_0   	    1   //  speeds
#define MK_C_OFFSET_UNMOD     3   //  default
#define MK_C_OFFSET_1   	    8
#define MK_C_OFFSET_2   	    16

#define MK_C_INTERVAL_0 	    8   //  timings
#define MK_C_INTERVAL_1 	    8
#define MK_C_INTERVAL_UNMOD   8
#define MK_C_INTERVAL_2 	    8

#define MK_W_OFFSET_0   	    1   //  speeds
#define MK_W_OFFSET_1   	    1
#define MK_W_OFFSET_UNMOD     1
#define MK_W_OFFSET_2   	    1

#define MK_W_INTERVAL_0 	    300 //  timings
#define MK_W_INTERVAL_1 	    200
#define MK_W_INTERVAL_UNMOD   100 //  default
#define MK_W_INTERVAL_2       30

#define BOOTMAGIC_ROW_RIGHT 4
#define BOOTMAGIC_COLUMN_RIGHT 0

#define RGBLIGHT_SLEEP
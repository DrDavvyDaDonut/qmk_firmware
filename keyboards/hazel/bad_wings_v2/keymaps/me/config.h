#pragma once

//  bootloader shit (press q)
#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0

// 1000hz Polling Rate
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

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

#define MK_C_OFFSET_UNMOD     3   //  default

#define MK_C_INTERVAL_UNMOD   8

#define MK_W_OFFSET_UNMOD     1

#define MK_W_INTERVAL_UNMOD   100 //  default


//  cirque
#define CIRQUE_PINNACLE_POSITION_MODE  CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_TAP_ENABLE

#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE

#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE 

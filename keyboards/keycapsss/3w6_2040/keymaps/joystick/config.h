#pragma once

//  easier bootloader access
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17 // Specify a optional status led by GPIO number which blinks when entering the bootloader

// 1000hz Polling Rate
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO

#define EE_HANDS

//  boot things
#define BOOTMAGIC_ROW_RIGHT 4
#define BOOTMAGIC_COLUMN_RIGHT 0

#define RGBLIGHT_SLEEP

// Joystick Button Count
#define JOYSTICK_BUTTON_COUNT 17

// Joystick Axes Count
#define JOYSTICK_AXIS_COUNT 4

// Joystick Axes Resolution
#define JOYSTICK_AXIS_RESOLUTION 8
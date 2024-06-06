/* Copyright 2015-2021 Jack Humbert
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

#pragma once

// // 1000hz Polling Rate
// #define USB_POLLING_INTERVAL_MS 1

// #define QMK_KEYS_PER_SCAN 12

// Joystick Button Count
#define JOYSTICK_BUTTON_COUNT 17

// Joystick Axes Count
#define JOYSTICK_AXIS_COUNT 4

// Joystick Axes Resolution
#define JOYSTICK_AXIS_RESOLUTION 8

#undef RGBLIGHT_ANIMATIONS

//  tapping toggle
#define TAPPING_TOGGLE 2

//  constant mouse keys
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL          //  momentary mouse

#define MK_C_OFFSET_0   	    1   //  speeds
#define MK_C_OFFSET_UNMOD     3  //  default
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
#define MK_W_INTERVAL_UNMOD   100  //  default
#define MK_W_INTERVAL_2       30


//  mouse keys on the 120 hz
// #define MOUSEKEY_INTERVAL       8

//  INTERIA
// #define MOUSEKEY_INERTIA
// #define MOUSEKEY_DELAY 100
// #define MOUSEKEY_MAX_SPEED 22
// #define MOUSEKEY_TIME_TO_MAX 22
// #define MOUSEKEY_FRICTION 100
// #define MOUSEKEY_MOVE_DELTA 1


//  accelerated mouse
// #define MOUSEKEY_DELAY          0
// #define MOUSEKEY_WHEEL_DELAY    0
// #define MOUSEKEY_MAX_SPEED      6
// #define MOUSEKEY_TIME_TO_MAX    32

#ifdef AUDIO_ENABLE
  #define PITCH_STANDARD_A 440.0f
  #define AUDIO_PIN A5
  #define AUDIO_PIN_ALT A4
  #define AUDIO_DAC_SAMPLE_WAVEFORM_SINE
  #define AUDIO_ENABLE_TONE_MULTIPLEXING
  #define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10

  #define NEW_WORLD_SYMPHONY M__NOTE(_E6, 256-8), M__NOTE(_REST, 8), M__NOTE(_FS6, 128-8), M__NOTE(_REST, 8), M__NOTE(_G6, 128-8), M__NOTE(_REST, 8), M__NOTE(_FS6, 192-8), M__NOTE(_REST, 8), M__NOTE(_E6, 64-8), M__NOTE(_REST, 8), M__NOTE(_E6, 256)
  #define MEGALOVANIA M__NOTE(_D7, 8), M__NOTE(_REST, 2), M__NOTE(_D7, 8), M__NOTE(_REST, 2), M__NOTE(_D8, 16), M__NOTE(_REST, 4), M__NOTE(_A7, 20), M__NOTE(_REST, 10), M__NOTE(_GS7, 10), M__NOTE(_REST, 10), M__NOTE(_G7, 10), M__NOTE(_F7, 30),M__NOTE(_D7, 10),M__NOTE(_F7, 10),M__NOTE(_G7, 10)  

#endif

#define FORCE_NKRO
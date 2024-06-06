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

#include QMK_KEYBOARD_H
#include "muse.h"

// #pragma message "resetting the colors of the thing so it's not all red"

enum preonic_layers {
  _BASE,
  _NUM,
  _LOWER,
  _RAISE,
  _ADJUST,
  _GAMEPAD,
  _MOUSE,
  _MUSIC
};

void keyboard_post_init_user(void){
  set_single_persistent_default_layer(_BASE);
}

float NEW_WORLD[][2] = SONG(NEW_WORLD_SYMPHONY);
float MEGA[][2] = SONG(MEGALOVANIA);

// layer specific things

// layer_state_t layer_state_set_user(layer_state_t state) {
//   if (layer_state_cmp(state, _GAMEPAD)) {
//   } else {
//   }
//   return state;
// }

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
  JOYSTICK_AXIS_VIRTUAL,
  JOYSTICK_AXIS_VIRTUAL,
  JOYSTICK_AXIS_VIRTUAL,
  JOYSTICK_AXIS_VIRTUAL
};

enum preonic_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,

  LS_UPUP,  //  left stick
  LS_DOWN,
  LS_LEFT,
  LS_RGHT,
  RS_UPUP,  //  right stick
  RS_DOWN,
  RS_LEFT,
  RS_RGHT,

  DP_UPUP,  //  d pad
  DP_DOWN,
  DP_LEFT,
  DP_RGHT,

  LS_SLOW,  //  slow down joysticks
  RS_SLOW,

  SANSUNDERTALE,
  DVORAK

};

#define QWERTY    TO(_BASE)
#define NUM       TT(_NUM)
#define WINLEFT   SGUI(KC_LEFT)
#define WINRGHT   SGUI(KC_RGHT)
#define GAMEPAD   TO(_GAMEPAD)
#define TEMPMOS   MO(_MOUSE)
#define MOUSERR   TO(_MOUSE)
#define MUSICSS   TO(_MUSIC)

/*
joystick shit
*/
#define	BC_DOWN   JS_0   //  button cluster
#define	BC_RGHT   JS_1
#define	BC_LEFT   JS_2
#define	BC_UPUP   JS_3
#define	L1_PRSS   JS_4   //  bumpers
#define	R1_PRSS   JS_5
#define	L2_PRSS   JS_6   //  triggers
#define	R2_PRSS   JS_7
#define	GC_SLCT   JS_8   //  select
#define	GC_STRT   JS_9   //  start
#define	LS_PRSS   JS_10  //  sticks
#define	RS_PRSS   JS_11
// #define DP_UPUP   JS_12  //  d pad
// #define DP_DOWN   JS_13
// #define DP_LEFT   JS_14
// #define DP_RGHT   JS_15
#define	GC_HOME   JS_16  //  home (xbox button)

bool LSU = false;
bool LSD = false;
bool LSL = false;
bool LSR = false;
bool RSU = false;
bool RSD = false;
bool RSL = false;
bool RSR = false;
bool DPU = false;
bool DPD = false;
bool DPL = false;
bool DPR = false;

int8_t leftValue = 127;
int8_t leftDiag = 90;
int8_t rightValue = 127;
int8_t rightDiag = 90;

//  i used this because i couldn't get joystick_read_axis() to work
int8_t leftHor = 0;
int8_t leftVer = 0;
int8_t rightHor = 0;
int8_t rightVer = 0;

void leftStick(void){
  joystick_set_axis(0, leftHor * ((leftVer == 0) ? leftValue : leftDiag));
  joystick_set_axis(1, leftVer * ((leftHor == 0) ? leftValue : leftDiag));
}

void rightStick(void){
  joystick_set_axis(2, rightHor * ((rightVer == 0) ? rightValue : rightDiag));
  joystick_set_axis(3, rightVer * ((rightHor == 0) ? rightValue : rightDiag));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

    case LS_SLOW:
      leftValue = record->event.pressed ? 63: 127;
      leftDiag = record->event.pressed ? 45: 90;
      leftStick();
      return false;
      break;
    case RS_SLOW:
      rightValue = record->event.pressed ? 63: 127;
      rightDiag = record->event.pressed ? 45: 90;
      rightStick();
      return false;
      break;
    case LS_UPUP:
      LSU = record->event.pressed ? true : false;
      leftVer = record->event.pressed ? -1  : (LSD ? 1 : 0);
      leftStick();
      return false;
      break;
    case LS_DOWN:
      LSD = record->event.pressed ? true : false;
      leftVer = record->event.pressed ? 1  : (LSU ? -1 : 0);
      leftStick();
      return false;
      break;
    case LS_LEFT:
      LSL = record->event.pressed ? true : false;
      leftHor = record->event.pressed ? -1  : (LSR ? 1 : 0);
      leftStick();
      return false;
      break;
    case LS_RGHT:
      LSR = record->event.pressed ? true : false;
      leftHor = record->event.pressed ? 1  : (LSL ? -1 : 0);
      leftStick();
      return false;
      break;
    case RS_UPUP:
      RSU = record->event.pressed ? true : false;
      rightVer = record->event.pressed ? -1  : (RSD ? 1 : 0);
      rightStick();
      return false;
      break;
    case RS_DOWN:
      RSD = record->event.pressed ? true : false;
      rightVer = record->event.pressed ? 1  : (RSU ? -1 : 0);
      rightStick();
      return false;
      break;
    case RS_LEFT:
      RSL = record->event.pressed ? true : false;
      rightHor = record->event.pressed ? -1  : (RSR ? 1 : 0);
      rightStick();
      return false;
      break;
    case RS_RGHT:
      RSR = record->event.pressed ? true : false;
      rightHor = record->event.pressed ? 1  : (RSL ? -1 : 0);
      rightStick();
      return false;
      break;
    case DP_UPUP:
      if(record->event.pressed){
        DPU = true;
        register_joystick_button(12);
        unregister_joystick_button(13);
      } else {
        DPU = false;
        unregister_joystick_button(12);
        if (DPD) {
          register_joystick_button(13);
        }
      }
      return false;
      break;
    case DP_DOWN:
      if(record->event.pressed){
        DPD = true;
        register_joystick_button(13);
        unregister_joystick_button(12);
      } else {
        DPD = false;
        unregister_joystick_button(13);
        if (DPU) {
          register_joystick_button(12);
        }
      }
      return false;
      break;
    case DP_LEFT:
      if(record->event.pressed){
        DPL = true;
        register_joystick_button(14);
        unregister_joystick_button(15);
      } else {
        DPL = false;
        unregister_joystick_button(14);
        if (DPR) {
          register_joystick_button(15);
        }
      }
      return false;
      break;
    case DP_RGHT:
      if(record->event.pressed){
        DPR = true;
        register_joystick_button(15);
        unregister_joystick_button(14);
      } else {
        DPR = false;
        unregister_joystick_button(15);
        if (DPL) {
          register_joystick_button(14);
        }
      }
      return false;
      break;
    case SANSUNDERTALE:
      if(record->event.pressed){
        PLAY_SONG(MEGA);
      }
      return false;
      break;
    case DVORAK:
      if(record->event.pressed){
        PLAY_SONG(NEW_WORLD);
      }
      return false;
      break;
    default:
      return true;
      break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_ESC,  NUM,     KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

[_NUM] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_UP,   _______, _______, KC_CIRC, KC_P7,   KC_P8,   KC_P9,   KC_PAST, KC_BSPC,
  KC_LCTL, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_LPRN, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_PMNS,
  KC_LSFT, _______, WINLEFT, _______, WINRGHT, _______, KC_RPRN, KC_P1,   KC_P2,   KC_P3,   KC_PSLS, KC_PENT,
  _______, QWERTY,  KC_LGUI, KC_LALT, TEMPMOS, KC_SPC,  KC_SPC,  KC_P0,   KC_P0,   KC_PDOT, KC_NUM,  _______
),

[_LOWER] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_INS,  _______, _______, KC_BRIU, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  KC_HOME, _______, _______, KC_BRID, _______, _______, _______, _______, _______, _______, _______, KC_END,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, TEMPMOS, _______, _______, _______, KC_MPLY, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

[_RAISE] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  _______, _______, _______, _______, _______, _______, KC_PGUP, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, _______, _______, _______, _______, KC_PGDN, KC_GRV,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_CAPS, _______, _______, _______, _______, _______, _______, QWERTY,  GAMEPAD, MOUSERR, MUSICSS, _______,
  _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_GAMEPAD] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,
  KC_TAB,  _______, _______, LS_UPUP, L1_PRSS, _______, _______, R1_PRSS, R2_PRSS, RS_PRSS, _______, _______,
  GC_HOME, _______, LS_LEFT, LS_DOWN, LS_RGHT, L2_PRSS, LS_PRSS, BC_UPUP, BC_LEFT, BC_RGHT, BC_DOWN, _______,
  KC_LSFT, _______, DP_LEFT, DP_UPUP, DP_DOWN, DP_RGHT, RS_LEFT, RS_DOWN, RS_UPUP, RS_RGHT, _______, GC_SLCT,
  GC_STRT, _______, _______, KC_LALT, LS_SLOW, KC_MPLY, KC_MPLY, RS_SLOW, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT

),

[_MOUSE] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,
  _______, _______, KC_WH_L, KC_MS_U, KC_WH_R, _______, _______, KC_WH_L, KC_MS_U, KC_WH_R, _______, _______,
  _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, KC_BTN3,
  _______, _______, KC_BTN3, KC_BTN2, KC_BTN1, KC_WH_D, KC_WH_D, _______, _______, _______, KC_BTN2, _______,
  _______, _______, _______, _______, _______, KC_ACL1, KC_ACL1, KC_ACL0, KC_ACL2, _______, _______, _______

),

[_MUSIC] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SANSUNDERTALE,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, DVORAK,  DVORAK,  _______, _______, _______, _______, _______
)

/*
[] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
*/

};


// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// Copyright 2023 Ben Roe (@keycapsss)
// Copyright 2023 Tom Barnes (@keyboard-magpie)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

void socdCleaner(uint8_t * totalState, uint8_t bit, bool on, uint16_t keyOne, uint16_t keyTwo);

enum layers {
  _BASE = 0,
  _GAMEPAD
};

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
  JOYSTICK_AXIS_VIRTUAL,
  JOYSTICK_AXIS_VIRTUAL,
  JOYSTICK_AXIS_VIRTUAL,
  JOYSTICK_AXIS_VIRTUAL
};

enum keycodes {
  LS_UPUP = SAFE_RANGE,  //  left stick
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
};

//  mods
#define BASE      TO(_BASE)
#define GAMEPAD   TO(_GAMEPAD)

#define ctrlA     LCTL_T(KC_A)
#define shftZ     LSFT_T(KC_Z)
#define lGuiC     LGUI_T(KC_C)
#define lAltV     LALT_T(KC_V)
#define ctlSemi   RCTL_T(KC_SCLN)
#define shftSls   RSFT_T(KC_SLSH)
#define guiComm   RGUI_T(KC_COMM)
#define rAltM     RALT_T(KC_M)
#define winLeft   S(G(KC_LEFT))
#define winRght   S(G(KC_RGHT))

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

uint8_t gameSOCD = 0;
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

int8_t leftHor = 0;
int8_t leftVer = 0;
int8_t rightHor = 0;
int8_t rightVer = 0;
//  on startup
void keyboard_post_init_user(void){
  set_single_persistent_default_layer(_GAMEPAD);
}

void leftStick(void){
  joystick_set_axis(0, leftHor * ((leftVer == 0) ? leftValue : leftDiag));
  joystick_set_axis(1, leftVer * ((leftHor == 0) ? leftValue : leftDiag));
}

void rightStick(void){
  joystick_set_axis(2, rightHor * ((rightVer == 0) ? rightValue : rightDiag));
  joystick_set_axis(3, rightVer * ((rightHor == 0) ? rightValue : rightDiag));
}

//  process keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
    default:
      return true;
      break;
    }
  return true;
}

//  layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX


    _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,  _______,  _______,  XXXXXXX
*/
  [_BASE] = LAYOUT_split_3x5_3(
    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
    ctrlA,    KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     ctlSemi,
    shftZ,    KC_X,     lGuiC,    lAltV,    KC_B,                         KC_N,     rAltM,    guiComm,  KC_DOT,   shftSls,
                                  GAMEPAD,  KC_BSPC,  KC_DEL,   KC_ENT,   KC_SPC,   GAMEPAD 
  ),
  [_GAMEPAD] = LAYOUT_split_3x5_3(
    KC_TAB,   _______,  LS_UPUP,  _______,  _______,                      _______,  L2_PRSS,  L1_PRSS,  R1_PRSS,  R1_PRSS,
    _______,  LS_LEFT,  LS_DOWN,  LS_RGHT,  LS_PRSS,                      RS_PRSS,  BC_UPUP,  BC_LEFT,  BC_RGHT,  BC_DOWN,
    _______,  DP_LEFT,  DP_UPUP,  DP_DOWN,  DP_RGHT,                      RS_LEFT,  RS_DOWN,  RS_UPUP,  RS_RGHT,  _______,
                                  GC_SLCT,  LS_UPUP,  GC_STRT,  KC_ESC,   _______,  BASE
  )
  // clang-format on
};

void socdCleaner(uint8_t * totalState, uint8_t bit, bool on, uint16_t keyOne, uint16_t keyTwo){

  if (on){
    *totalState |= bit;
  } else {
    *totalState &= ~bit;
  }

  bool highNibble = bit >> 4;

  uint8_t state = (0x03 << (highNibble << 2)) & *totalState;
  uint8_t start = (0x0C << (highNibble << 2)) & *totalState;

  state >>= (highNibble << 2);
  start >>= (highNibble << 2);

  if (state < 3){
    switch (state){
      case 1:
        register_code(keyOne);
        unregister_code(keyTwo);
        break;
      case 2:
        unregister_code(keyOne);
        register_code(keyTwo);
        break;
      default:
        unregister_code(keyOne);
        unregister_code(keyTwo);
        break;
    }

    *totalState &= ~(0x0C << (highNibble << 2));
    *totalState |= ((state << 2) << (highNibble << 2));
    return;
  }

  switch (start) {
    case 4:
      unregister_code(keyOne);
      register_code(keyTwo);
      break;
    case 8:
      register_code(keyOne);
      unregister_code(keyTwo);
      break;
    default:
      unregister_code(keyOne);
      unregister_code(keyTwo);
      break;
  }
}
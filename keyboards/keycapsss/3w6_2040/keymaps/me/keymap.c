// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// Copyright 2023 Ben Roe (@keycapsss)
// Copyright 2023 Tom Barnes (@keyboard-magpie)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#ifdef CONSOLE_ENABLE
  #include "print.h"
#endif

enum layers {
  _BASE = 0,
  _ALTER,
  _SYMBOLS,
  _NUM,
  _ADJUST,
  _MOUSE,
  _GAME,
  _GAMEPAD
};

enum keycodes {
  BLLSPD0 = SAFE_RANGE,
  BLLSPD1,
  BLLSPD2,

  // socd cleaning
  SOCD_ML,
  SOCD_MR,
  SOCD_MU,
  SOCD_MD,

  //  scrollArrowToggle
  toggle
};

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

#define spcSymb   LT(_SYMBOLS, KC_SPC)
#define entSymb   LT(_SYMBOLS, KC_ENT)
#define zeroSym   LT(_SYMBOLS, KC_P0)
#define quotAlt   LT(_ALTER, KC_QUOT)

#define BASE      TO(_BASE)
#define ALT       MO(_ALTER)
#define SYM       MO(_SYMBOLS)
#define NUMPADD   MO(_NUM)
#define MOUSERR   TO(_MOUSE)
#define GAMERRR   TO(_GAME)
#define GAMEPAD   TO(_GAMEPAD)

uint8_t currButton = 0;
uint8_t prevButton = 0;

bool scrollOrArrow = true;

bool xNeg = false;
bool yNeg = false;

uint8_t xCount = 0;
uint8_t yCount = 0;

int8_t xSum = 0;
int8_t ySum = 0;

uint8_t moreShit;
uint8_t vec;

uint8_t pimoroniThreshold = 6;

uint8_t highest_layer = _BASE;

uint8_t bllSpd = 1;
uint8_t mouseSOCD = 0;

void keyboard_post_init_user(void){
  combo_disable();
  set_single_persistent_default_layer(_BASE);
  pimoroni_trackball_set_rgbw(40,20,40,40);
  // while (!host_keyboard_led_state().num_lock){
  //   tap_code(KC_NUM);
  // }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _SYMBOLS, _ALTER, _ADJUST);
  state = update_tri_layer_state(state, _SYMBOLS, _NUM, _ADJUST);

  highest_layer = get_highest_layer(state);

  if (state >= _GAME){
    pimoroni_trackball_set_rgbw(60,60,60,60);
  } else {
    pimoroni_trackball_set_rgbw(40,20,40,40);
  }

  if (highest_layer == _ALTER){
    register_mods(MOD_LALT);  
  } else {
    unregister_mods(MOD_LALT);
  }

  if (layer_state_cmp(state, _ADJUST)){
    combo_enable();
  } else {
    combo_disable();
  }

  return state;
}

void socdCleaner(uint8_t * totalState, uint8_t bit, bool on, uint16_t keyOne, uint16_t keyTwo){

  if (on){
    *totalState |= bit;
  } else {
    *totalState &= ~bit;
  }

  bool highNibble = bit >> 4;

  uint8_t state = (0x03 << (highNibble * 4)) & *totalState;
  uint8_t start = (0x0C << (highNibble * 4)) & *totalState;

  state >>= (highNibble * 4);
  start >>= (highNibble * 4);

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

    *totalState &= ~(0x0C << (highNibble * 4));
    *totalState |= ((state * 4) << (highNibble * 4));
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BLLSPD0:
      if (record->event.pressed){
        bllSpd = 1;
        register_code(KC_ACL0);
      } else {
        bllSpd = 3;
        unregister_code(KC_ACL0);
      }
      return false;
      break;
    case BLLSPD1:
      if (record->event.pressed){
        bllSpd = 8;
        register_code(KC_ACL1);
      } else {
        bllSpd = 3;
        unregister_code(KC_ACL1);
      }
      return false;
      break;
    case BLLSPD2:
      if (record->event.pressed){
        bllSpd = 16;
        register_code(KC_ACL2);
      } else {
        bllSpd = 3;
        unregister_code(KC_ACL2);
      }
      return false;
      break;
    case SOCD_ML:
      socdCleaner(&mouseSOCD, 0x01, record->event.pressed, KC_MS_L, KC_MS_R);
      return false;
      break;
    case SOCD_MR:
      socdCleaner(&mouseSOCD, 0x02, record->event.pressed, KC_MS_L, KC_MS_R);
      return false;
      break;
    case SOCD_MU:
      socdCleaner(&mouseSOCD, 0x10, record->event.pressed, KC_MS_U, KC_MS_D);
      return false;
      break;
    case SOCD_MD:
      socdCleaner(&mouseSOCD, 0x20, record->event.pressed, KC_MS_U, KC_MS_D);
      return false;
      break;
    case toggle:
      if (record->event.pressed){
        scrollOrArrow = ! scrollOrArrow;
      }
      return false;
      break;
    default:
      return true;
      break;
    }
  return true;
}

// bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case shftZ:
//       // Immediately select the hold action when another key is pressed.
//       return true;
//     case shftSls:
//       return true;
//     default:
//       // Do not select the hold action when another key is pressed.
//       return false;
//   }
// }

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case spcSymb:
      return 0;
    default:
      return QUICK_TAP_TERM;
  }
}


const key_override_t shiftPlusMinus = ko_make_basic(MOD_MASK_SHIFT, KC_PPLS, KC_PMNS);
const key_override_t shiftMultDivid = ko_make_basic(MOD_MASK_SHIFT, KC_PAST, KC_PSLS);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &shiftPlusMinus,
    &shiftMultDivid,
    NULL // Null terminate the array of overrides!
};

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

  //  handling pure mousing
  if (highest_layer == _MOUSE){
    mouse_report.x = mouse_report.x * bllSpd;
    mouse_report.y = mouse_report.y * bllSpd;

    return mouse_report;
  }

  //  handling ball presses each cycle
  currButton = mouse_report.buttons;

  //  activates on edge of presses
  if (prevButton != currButton){
    
    action_exec(MAKE_KEYEVENT(7, 2, currButton));

    // only update if different
    prevButton = currButton;
  }

  //  direction handling

  switch (highest_layer){
    case _GAME:
      /*
      if (mouse_report.x | mouse_report.y){
        if (!xCount){
          xCount = 50;
        }
        xSum += mouse_report.x;
        ySum += mouse_report.y;
      }

      if(moreShit){
        moreShit--;
        if(!moreShit){
          unregister_code(KC_LEFT);
          unregister_code(KC_UP);
          unregister_code(KC_RIGHT);
          unregister_code(KC_DOWN);
        }
      }

      if(xCount){
        xCount--;
        if(!xCount){

          vec = xSum * xSum + ySum * ySum;

          uprintf("%i",vec);
          
          if (vec > (pimoroniThreshold * pimoroniThreshold)){
            moreShit = xSum & 0x80;
            moreShit >>= 1;
            moreShit |= ySum & 0x80;
            moreShit >>= 1;
            moreShit |= xSum ^ 0x80;
            moreShit >>= 1;
            moreShit |= ySum ^ 0x80;
            xSum = 0;
            ySum = 0;
            switch(moreShit){
              case 1:
                unregister_code(KC_LEFT);
                unregister_code(KC_UP);
                unregister_code(KC_RIGHT);
                register_code(KC_DOWN);
                break;
              case 2:
                unregister_code(KC_LEFT);
                unregister_code(KC_UP);
                register_code(KC_RIGHT);
                unregister_code(KC_DOWN);
                break;
              case 3:
                unregister_code(KC_LEFT);
                unregister_code(KC_UP);
                register_code(KC_RIGHT);
                register_code(KC_DOWN);
                break;
              case 4:
                unregister_code(KC_LEFT);
                register_code(KC_UP);
                unregister_code(KC_RIGHT);
                unregister_code(KC_DOWN);
                break;
              case 6:
                unregister_code(KC_LEFT);
                register_code(KC_UP);
                register_code(KC_RIGHT);
                unregister_code(KC_DOWN);
                break;
              case 8:
                register_code(KC_LEFT);
                unregister_code(KC_UP);
                unregister_code(KC_RIGHT);
                unregister_code(KC_DOWN);
                break;
              case 9:
                register_code(KC_LEFT);
                unregister_code(KC_UP);
                unregister_code(KC_RIGHT);
                register_code(KC_DOWN);
                break;
              case 12:
                register_code(KC_LEFT);
                register_code(KC_UP);
                unregister_code(KC_RIGHT);
                unregister_code(KC_DOWN);
                break;
              default:
                break;
            }
            moreShit = 150;
          }

          
        }
      }
      */
      

      break; 
    case _ALTER:

      break; 
    case _BASE:
      if (scrollOrArrow){
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
      } else {

      }
      break; 
    default:
      break; 
  }

  mouse_report.x = 0;
  mouse_report.y = 0;
  mouse_report.buttons = 0;

  return mouse_report;

}

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
                                  NUMPADD,  KC_BSPC,  quotAlt,  entSymb,  spcSymb,  toggle 
  ),
  [_ALTER] = LAYOUT_split_3x5_3(
    KC_TAB,   XXXXXXX,  KC_UP,    XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  KC_VOLU,  XXXXXXX,  XXXXXXX,
    KC_LCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  GAMERRR,                      XXXXXXX,  KC_MPRV,  KC_VOLD,  KC_MNXT,  XXXXXXX,
    KC_LSFT,  XXXXXXX,  KC_LGUI,  MOUSERR,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  KC_MUTE,  XXXXXXX,  XXXXXXX,
                                  XXXXXXX,  XXXXXXX,  _______,  SYM,      KC_MPLY,  _______
  ),
  [_SYMBOLS] = LAYOUT_split_3x5_3(
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_LCTL,  KC_LEFT,  KC_UP,    KC_DOWN,  KC_RGHT,                      KC_PGUP,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_BSLS,                      KC_PGDN,  KC_GRV,   KC_COMM,  KC_DOT,   KC_SLSH,
                                  NUMPADD,  KC_BSPC,  KC_DEL,   _______,  _______,  _______
  ),
  [_NUM] = LAYOUT_split_3x5_3(
    KC_TAB,   winLeft,  KC_UP,    winRght,  KC_QUOT,                      KC_CIRC,  KC_P7,    KC_P8,    KC_P9,    KC_PAST,
    KC_LCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_SPC,                       KC_LPRN,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_BSLS,                      KC_RPRN,  KC_P1,    KC_P2,    KC_P3,    KC_PENT,
                                  _______,  KC_MPLY,  KC_MPLY,  KC_NUM,   zeroSym,  SYM    
  ),
  [_ADJUST] = LAYOUT_split_3x5_3(
    KC_F1,    KC_F2,    KC_F4,    KC_F8,    KC_F16,                       _______,  KC_WH_L,  SOCD_MU,  KC_WH_R,  KC_BTN3,
    KC_LCTL,  _______,  _______,  _______,  GAMERRR,                      KC_WH_U,  SOCD_ML,  SOCD_MD,  SOCD_MR,  KC_BTN1,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  GAMEPAD,                      KC_WH_D,  MOUSERR,  _______,  _______,  KC_BTN2,
                                  _______,  _______,  _______,  _______,  _______,  _______
  ),
  [_MOUSE] = LAYOUT_split_3x5_3(
    KC_TAB,   KC_Q, KC_W, KC_E, KC_R,                      BASE,     KC_WH_L,  SOCD_MU,  KC_WH_R,  KC_BTN3,
    KC_LCTL,  KC_A, KC_S, KC_D, KC_F,                      KC_WH_U,  SOCD_ML,  SOCD_MD,  SOCD_MR,  KC_BTN1,
    KC_SPC,   KC_Z, KC_X, KC_C, KC_V,                      KC_WH_D,  BASE,     _______,  _______,  KC_BTN2,
                                  KC_Q, KC_LSFT, KC_E,  BLLSPD0,  BLLSPD1,  XXXXXXX
  ),
  [_GAME] = LAYOUT_split_3x5_3(
    KC_TAB, KC_W, KC_E, KC_R, KC_T,                        KC_Y, KC_U, KC_I,    KC_O,   KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G,                        KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,
    KC_ESC, KC_X, KC_C, KC_V, KC_B,                     KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                   KC_LSFT, KC_BSPC, KC_LALT,   KC_ENT, KC_SPC, BASE 
  ),
  [_GAMEPAD] = LAYOUT_split_3x5_3(
    KC_TAB,   KC_Q, KC_W, KC_E, KC_R,             KC_Y, KC_U, KC_I,    KC_O,    KC_P,    
    KC_LCTL,  KC_A, KC_S, KC_D, KC_F,             KC_H, KC_J, KC_K,    KC_L,    KC_ENT,    
    KC_SPC,   KC_Z, KC_X, KC_C, KC_V,             KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,  
                          KC_Q, KC_LSFT, KC_E, KC_ESC, KC_SPC, BASE 
  )
  // clang-format on
};

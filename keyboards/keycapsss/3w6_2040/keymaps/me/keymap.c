// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// Copyright 2023 Ben Roe (@keycapsss)
// Copyright 2023 Tom Barnes (@keyboard-magpie)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#ifdef CONSOLE_ENABLE
  #include "print.h"
#endif

void socdCleaner(uint8_t * totalState, uint8_t bit, bool on, uint16_t keyOne, uint16_t keyTwo);

//  layer controls
#define BASE      TO(_BASE)
#define ALT       MO(_ALTER)
#define SYM       MO(_SYMBOLS)
#define NUMPADD   MO(_NUM)
#define HKGAMER   TO(_HOLLOW)
#define MCGAMER   TO(_MINECRAFT)
#define GAMEPAD   TO(_GAMEPAD)
#define FIGHTER   TO(_FIGHTER)
#define FISHING   TO(_FISH)
#define GUITARR   TO(_GUITAR)
#define POKEONE   TO(_POKEONE)
#define POKETWO   TO(_POKETWO)

//  mods
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

//  thumbs
#define spcSymb   LT(_SYMBOLS, KC_SPC)
#define entSymb   LT(_SYMBOLS, KC_ENT)
#define zeroSym   LT(_SYMBOLS, KC_P0)
#define quotAlt   LT(_ALTER, KC_QUOT)

//  gamer keys
#define swpG      SH_T(KC_G)
#define swpT      SH_T(KC_3)
#define MS_3      MS_BTN3
#define DROP      C(KC_Q)

/*
*   LAYER NAMES
*/
enum layers {
  _BASE = 0,
  _HOLLOW,
  _ALTER,
  _SYMBOLS,
  _NUM,
  _ADJUST,
  _GAMEPAD,
  _FISH,
  _GUITAR,
  _MINECRAFT,
  _FIGHTER,
  _POKEONE,
  _POKETWO
};

enum keycodes {
  //  socd cleaning
  SOCD_ML = SAFE_RANGE,
  SOCD_MR,
  SOCD_MU,
  SOCD_MD,

  HK_L,
  HK_R,
  HK_U,
  HK_D,

  LEFT,
  RGHT,
  UPUP,
  DOWN,

  AR_D,
  AR_L,
  AR_R,
  AR_U,

  //  scrollArrowToggle
  toggle
};


bool scrollOrArrow = false;

uint8_t highest_layer = _BASE;

uint8_t bllSpd = 1;
uint8_t mouseSOCD = 0;
uint8_t gameSOCD = 0;

//  on startup
void keyboard_post_init_user(void){
  combo_disable();
  swap_hands_off();
  set_single_persistent_default_layer(_BASE);
  pimoroni_trackball_set_rgbw(40,20,40,40);
}

//  on layer change
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _SYMBOLS, _ALTER, _ADJUST);
  state = update_tri_layer_state(state, _SYMBOLS, _NUM, _ADJUST);

  highest_layer = get_highest_layer(state);

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

//  process keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
    case HK_L:
      socdCleaner(&gameSOCD, 0x01, record->event.pressed, KC_S, KC_F);
      return false;
      break;
    case HK_R:
      socdCleaner(&gameSOCD, 0x02, record->event.pressed, KC_S, KC_F);
      return false;
      break;
    case HK_U:
      socdCleaner(&gameSOCD, 0x10, record->event.pressed, KC_E, KC_D);
      return false;
      break;
    case HK_D:
      socdCleaner(&gameSOCD, 0x20, record->event.pressed, KC_E, KC_D);
      return false;
      break;
    case LEFT:
      socdCleaner(&gameSOCD, 0x01, record->event.pressed, KC_A, KC_D);
      return false;
      break;
    case RGHT:
      socdCleaner(&gameSOCD, 0x02, record->event.pressed, KC_A, KC_D);
      return false;
      break;
    case UPUP:
      socdCleaner(&gameSOCD, 0x10, record->event.pressed, KC_W, KC_S);
      return false;
      break;
    case DOWN:
      socdCleaner(&gameSOCD, 0x20, record->event.pressed, KC_W, KC_S);
      return false;
      break;
    case AR_L:
      socdCleaner(&gameSOCD, 0x01, record->event.pressed, KC_LEFT, KC_RGHT);
      return false;
      break;
    case AR_R:
      socdCleaner(&gameSOCD, 0x02, record->event.pressed, KC_LEFT, KC_RGHT);
      return false;
      break;
    case AR_U:
      socdCleaner(&gameSOCD, 0x10, record->event.pressed, KC_UP, KC_DOWN);
      return false;
      break;
    case AR_D:
      socdCleaner(&gameSOCD, 0x20, record->event.pressed, KC_UP, KC_DOWN);
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

//  custom timing for shift
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case shftZ:
      // Immediately select the hold action when another key is pressed.
      return true;
    case shftSls:
      return true;
    default:
      // Do not select the hold action when another key is pressed.
      return false;
  }
}

//  quick raise after space
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case spcSymb:
      return 0;
    default:
      return QUICK_TAP_TERM;
  }
}

//  numpad override
const key_override_t shiftPlusMult = ko_make_basic(MOD_MASK_SHIFT, KC_PPLS, KC_PAST);
const key_override_t shiftMinusDivide = ko_make_basic(MOD_MASK_SHIFT, KC_PMNS, KC_PSLS);
const key_override_t shiftEnterPeriod = ko_make_basic(MOD_MASK_SHIFT, KC_PENT, KC_PDOT);

const key_override_t *key_overrides[] = {
    &shiftPlusMult,
    &shiftMinusDivide,
    &shiftEnterPeriod
};

//  mouse 

int8_t x = 0;
int8_t y = 0;
uint8_t count = 0;

uint8_t currButton = 0;
uint8_t prevButton = 0;

uint16_t pimoroniThreshold = 1;
uint16_t pimoroniCountThreshold = 50;

void sendCodes(uint8_t up, uint8_t down, uint8_t left, uint8_t right){
  unregister_code(left);
  unregister_code(right);
  unregister_code(down);
  unregister_code(up);

  //  count on bit only
  if (count & 0x80){
    if (x > pimoroniThreshold){
      register_code(right);
    } else if (x < -pimoroniThreshold){
      register_code(left);
    }
    if (y > pimoroniThreshold){
      register_code(down);
    } else if (y < -pimoroniThreshold){
      register_code(up);
    }
  }
}

void pimoroniBallHandling(report_mouse_t mouse_report, uint8_t up, uint8_t down, uint8_t left, uint8_t right){
  
  //  ball move

  if (mouse_report.x){
    count |= 0x80;      //  turn on counting bit
    if (mouse_report.x > 0){
      x++;
    } else {
      x--;
    }
  }
  
  if (mouse_report.y){
    count |= 0x80;      //  turn on counting bit
    if (mouse_report.y > 0){
      y++;
    } else {
      y--;
    }
  }

  //  update count if either counting bits are on
  if (count & 0xC0){
    count++;
  }
  //  if cumulitive distance greater than threshold, update
  if (x*x + y*y > pimoroniThreshold*pimoroniThreshold){
    pimoroni_trackball_set_rgbw(255,255,255,255);
    sendCodes(up, down, left, right);
    count = 0x40;
    x = 0;
    y = 0;
    return;
  }
  if ((count & 0x3f) > pimoroniCountThreshold){
    pimoroni_trackball_set_rgbw(0,0,0,0);
    sendCodes(up, down, left, right);
    count = 0x40;
    x = 0;
    y = 0;
  }
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

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
    case _GAMEPAD:
      // pimoroniBallHandling(mouse_report, KC_UP, KC_DOWN, KC_LEFT, KC_RGHT);
      break; 
    case _BASE:
      if (scrollOrArrow){
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
      } else {
        // pimoroniBallHandling(mouse_reporqt, KC_UP, KC_DOWN, KC_LEFT, KC_RGHT);
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

/*
*   LAYER 
*/
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
  [_HOLLOW] = LAYOUT_split_3x5_3(
    KC_TAB, KC_W, HK_U, KC_R, KC_T,                  KC_Y, KC_U, KC_I,    KC_O,   KC_P,
    KC_A,   HK_L, HK_D, HK_R, KC_G,                  KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,
    KC_ESC, KC_X, KC_C, KC_V, KC_B,                  KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                     NUMPADD, KC_G, KC_LALT, KC_ESC, KC_SPC, BASE
  ),
  [_ALTER] = LAYOUT_split_3x5_3(
    KC_TAB,   XXXXXXX,  KC_UP,    FIGHTER,  HKGAMER,                      XXXXXXX,  XXXXXXX,  KC_VOLU,  XXXXXXX,  XXXXXXX,
    KC_LCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  GAMEPAD,                      XXXXXXX,  KC_MPRV,  KC_VOLD,  KC_MNXT,  XXXXXXX,
    KC_LSFT,  XXXXXXX,  KC_LGUI,  GUITARR,  MCGAMER,                      XXXXXXX,  XXXXXXX,  KC_MUTE,  XXXXXXX,  XXXXXXX,
                                  _______,  _______,  _______,  SYM,      KC_MPLY,  _______
  ),
  [_SYMBOLS] = LAYOUT_split_3x5_3(
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_LCTL,  KC_LEFT,  KC_UP,    KC_DOWN,  KC_RGHT,                      KC_PGUP,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_BSLS,                      KC_PGDN,  KC_GRV,   KC_COMM,  KC_DOT,   KC_SLSH,
                                  NUMPADD,  KC_BSPC,  KC_DEL,   _______,  _______,  _______
  ),
  [_NUM] = LAYOUT_split_3x5_3(
    KC_TAB,   winLeft,  KC_UP,    winRght,  KC_QUOT,                      KC_CIRC,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,
    KC_LCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_SPC,                       KC_LPRN,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_BSLS,                      KC_RPRN,  KC_P1,    KC_P2,    KC_P3,    KC_PENT,
                                  _______,  KC_MPLY,  KC_MPLY,  KC_P0,    zeroSym,  KC_NUM    
  ),
  [_ADJUST] = LAYOUT_split_3x5_3(
    KC_F1,    KC_F2,    KC_F4,    KC_F8,    KC_F16,                       _______,  KC_WH_L,  SOCD_MU,  KC_WH_R,  KC_BTN3,
    KC_LCTL,  _______,  _______,  _______,  _______,                      KC_WH_U,  SOCD_ML,  SOCD_MD,  SOCD_MR,  KC_BTN1,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  _______,                      KC_WH_D,  _______,  _______,  _______,  KC_BTN2,
                                  _______,  _______,  _______,  _______,  _______,  _______
  ),
  [_GAMEPAD] = LAYOUT_split_3x5_3(
    KC_T,     swpG, UPUP, KC_B, KC_R,                   KC_Y, KC_U, KC_I, KC_O, KC_P,    
    KC_LCTL,  LEFT, DOWN, RGHT, KC_F,                   KC_H, KC_J, KC_K, KC_L, KC_F1,    
    KC_SPC,   KC_Z, KC_X, KC_C, KC_V,                   KC_N, KC_M, KC_1, KC_2, KC_3,  
                          KC_Q, KC_LSFT,  KC_E, KC_ESC, KC_TAB, BASE 
  ),
  [_FISH] = LAYOUT_split_3x5_3(
    _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,  _______,  _______,  BASE
  ),
  [_GUITAR] = LAYOUT_split_3x5_3(
    _______,  _______,  _______,  _______,  _______,                      _______,  KC_7,  KC_8,  KC_9,  _______,
    KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         _______,  KC_4,  KC_5,  KC_6,  _______,
    _______,  _______,  _______,  _______,  _______,                      _______,  KC_1,  KC_2,  KC_3,  _______,
                                  _______,  KC_T,     KC_Y,     _______,  _______,  FISHING
  ),
  [_MINECRAFT] = LAYOUT_split_3x5_3(
    KC_TAB,   swpT, KC_W, KC_4,   KC_5,               KC_8,   KC_7, KC_I,   KC_O, KC_P,    
    KC_F5,    KC_A, KC_S, KC_D,   KC_6,               KC_9,   KC_J, KC_K,   KC_L, KC_F1,    
    KC_LSFT,  KC_Z, KC_X, KC_E,   KC_Q,               DROP,   MS_3, KC_SPC, KC_1, KC_2,  
                          KC_SPC, KC_1, KC_2, KC_ESC, KC_F3,  BASE 
  ),
  [_FIGHTER] = LAYOUT_split_3x5_3(
    KC_TAB,   KC_Q,     AR_U,     KC_E,     _______,                      _______,  _______,  KC_B,     KC_X,     _______,
    KC_LCTL,  AR_L,     AR_D,     AR_R,     _______,                      _______,  KC_Z,     KC_C,     KC_LSFT,  KC_V,
    KC_ESC,   POKEONE,  POKETWO,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
                                  KC_Q,     KC_BSPC,  KC_E,    KC_ENT,    KC_SPC,   BASE
  ),
  [_POKEONE] = LAYOUT_split_3x5_3(
    _______,  _______,  KC_W,     _______,  _______,                      _______,  KC_U,     KC_I,     KC_O,     _______,
    _______,  KC_A,     KC_S,     KC_D,     _______,                      _______,  KC_L,     KC_J,     KC_K,     KC_W,
    FIGHTER,  POKEONE,  POKETWO,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
                                  _______,  KC_W,     _______,  KC_ESC,   _______,  BASE
  ),
  [_POKETWO] = LAYOUT_split_3x5_3(
    _______,  _______,  KC_T,     _______,  _______,                      _______,  KC_P4,    KC_P5,    KC_P6,    _______,
    _______,  KC_F,     KC_G,     KC_H,     _______,                      _______,  KC_P3,    KC_P1,    KC_P2,    KC_T,
    FIGHTER,  POKEONE,  POKETWO,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,
                                  _______,  KC_T,     _______,  KC_ESC,   _______,  BASE
  )
  // clang-format on
};

//  enter the row and column, recieve new (column, row)
//  default (NO SWAPPING)
/*
  {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}},
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}},
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}},
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}},
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}},
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}},
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}},
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}},
*/

//  pure swap  
/*
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}},
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}},
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}},
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}},
  {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}},
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}},
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}},
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}},
*/

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{3, 7}, {1, 0}, {2, 0}, {3, 4}, {4, 4}},
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 5}},
  {{0, 2}, {1, 2}, {2, 2}, {3, 6}, {4, 6}},
  {{0, 3}, {1, 3}, {2, 6}, {1, 6}, {0, 6}},
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}},
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}},
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}},
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}},
};

//  simulatious opposing cardinal direction cleaning
//  total state contains the info for two pairs of opposing cardinal directions
void socdCleaner(uint8_t * totalState, uint8_t bit, bool on, uint16_t keyOne, uint16_t keyTwo){

  //  update state with desired bits
  if (on){
    *totalState |= bit;
  } else {
    *totalState &= ~bit;
  }

  //  okay let's break this down, piece by piece
  //  (highNibble << 2) will be 4 IFF we are dealing with the high nibble (pair two)
  //  use the highnibble shenanigans to isolate the bits we are looking at. 
  //  state is the current state of the pressed buttons
  //  start is used to determin the new direction
  //  after shifting over the bit, if it is greater than 0, then it is concerning the high nibble
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
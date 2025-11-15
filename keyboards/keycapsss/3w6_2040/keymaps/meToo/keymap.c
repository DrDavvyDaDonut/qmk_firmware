// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// Copyright 2023 Ben Roe (@keycapsss)
// Copyright 2023 Tom Barnes (@keyboard-magpie)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "socd.c"
/*
*   LAYER NAMES
*/
enum layers {
  _BASE = 0,
  _HOLLOW,
  _ALTER,
  _SYMBOLS,
  _NUM,
  _FUNC,
  _GAMEPAD,
  _FISH,
  _GUITAR,
  _MINECRAFT,
  _FIGHTER,
  _POKEONE,
  _POKETWO
};

layer_state_t red_game_layers = (layer_state_t) (1 << _GAMEPAD) | (1 << _FIGHTER);
layer_state_t green_game_layers = (layer_state_t) (1 << _FISH) | (1 << _GUITAR) | (1 << _MINECRAFT);

enum keycodes {
  //  socd cleaning
  //  mouse
  SOCD_ML = SAFE_RANGE,
  SOCD_MR,
  SOCD_MU,
  SOCD_MD,

  //  hollow knight
  HK_L,
  HK_R,
  HK_U,
  HK_D,

  //  wasd
  LEFT,
  RGHT,
  UPUP,
  DOWN,

  //  arrows
  AR_D,
  AR_L,
  AR_R,
  AR_U,
};

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

//  thumbs right
// #define spcSymb   LT(_SYMBOLS, KC_SPC)
// #define entSymb   LT(_SYMBOLS, KC_ENT)
// #define zeroSym   LT(_SYMBOLS, KC_P0)
#define nmLkSym   LT(_SYMBOLS, KC_NUM)

//  thumbs left
// #define backNum   LT(_NUM, KC_BSPC)
#define quotAlt   LT(_ALTER, KC_QUOT)

//  gamer keys
#define swpG      SH_T(KC_G)
#define swpT      SH_T(KC_3)
#define MS_3      MS_BTN3
#define DROP      C(KC_Q)

bool scrollOrMouse = false;

bool suspended;

uint8_t highest_layer = _BASE;

uint8_t bllSpd = 1;
uint8_t mouseSOCD = 0;
uint8_t gameSOCD = 0;

//  on startup
void keyboard_post_init_user(void){
  suspended = false;
  combo_disable();
  swap_hands_off();
  set_single_persistent_default_layer(_BASE);
  //  effect both leds
  rgblight_set_effect_range(0, 2);  
  rgblight_reload_from_eeprom();
}

//  keyboard power down
void suspend_power_down_user(void) {
  suspended = true;
  gpio_write_pin_low(GP17);
}

//  keyboard power up
void suspend_wakeup_init_user(void) {
  suspended = false;
  scrollOrMouse = false;
}

//  on layer change
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _SYMBOLS, _NUM, _FUNC);

  highest_layer = get_highest_layer(state);

  if (highest_layer == _ALTER){
    register_mods(MOD_LALT);  
  } else {
    unregister_mods(MOD_LALT);
  }

  if (layer_state_cmp(state, _FUNC)){
    combo_enable();
  } else {
    combo_disable();
  }

  if (layer_state_cmp(state, _HOLLOW)){
    rgblight_sethsv(149, 57, 217);
  } else
  if (state & red_game_layers){       //  red gaming layers 
    rgblight_sethsv(0, 210, 176);
  } else
  if (state & ((layer_state_t) 1 << _POKEONE)){
    rgblight_sethsv(15, 230, 195);
  } else 
  if (state & ((layer_state_t) 1 << _POKETWO)){
    rgblight_sethsv(32, 246, 143);
  } else
  if (state & green_game_layers){     //  green gaming layers
    rgblight_sethsv(82, 194, 133);
  } else
  if (state & 1){                     //  base layer active
    rgblight_sethsv(152, 232, 200);
  } else
  {                                   //  default (sad)
    rgblight_sethsv(152, 232, 75);
  }

  return state;
}

bool led_update_user(led_t led_state) {
  if (!suspended){
    gpio_write_pin(GP17, !led_state.num_lock);
  }
  return false;
}

//  process keycode
/*
record structure

keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
*/
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

//  flow tap NO Z (shift)

bool is_flow_tap_key(uint16_t keycode) {
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
      return false; // Disable Flow Tap on hotkeys.
    }
    switch (get_tap_keycode(keycode)) {
      case KC_SPC:
      case KC_B ... KC_Y:
      case KC_DOT:
      case KC_COMM:
      case KC_SCLN:
      case KC_SLSH:
        return true;
    }
    return false;
}

//  numpad override
const key_override_t shiftPlusMult = ko_make_basic(MOD_MASK_SHIFT, KC_PPLS, KC_PAST);
const key_override_t shiftMinusDivide = ko_make_basic(MOD_MASK_SHIFT, KC_PMNS, KC_PSLS);
const key_override_t shiftDotNumlock = ko_make_basic(MOD_MASK_SHIFT, KC_PDOT, KC_NUM);

const key_override_t *key_overrides[] = {
    &shiftPlusMult,
    &shiftMinusDivide,
    &shiftDotNumlock
};

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
                                  NUMPADD,  KC_BSPC,  quotAlt,  KC_ENT,   KC_SPC,   SYM 
  ),
  [_HOLLOW] = LAYOUT_split_3x5_3(
    KC_Q,   KC_W, HK_U, KC_R, KC_T,               KC_Y, KC_U,    KC_I,    KC_O,   KC_P,
    KC_A,   HK_L, HK_D, HK_R, KC_SPC,             KC_H, KC_J,    KC_K,    KC_L,   KC_SCLN,
    KC_ESC, KC_X, KC_C, KC_V, KC_B,               KC_N, KC_SCLN, KC_SCLN, KC_SCLN, KC_SCLN,
                     NUMPADD, HK_U, ALT,  KC_ESC, KC_SPC, BASE
  ),
  [_ALTER] = LAYOUT_split_3x5_3(
    KC_TAB,   XXXXXXX,  KC_UP,    FIGHTER,  HKGAMER,                      XXXXXXX,  XXXXXXX,  KC_VOLU,  XXXXXXX,  XXXXXXX,
    KC_LCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  GAMEPAD,                      XXXXXXX,  KC_MPRV,  KC_VOLD,  KC_MNXT,  XXXXXXX,
    KC_LSFT,  KC_ESC,   KC_LGUI,  GUITARR,  MCGAMER,                      XXXXXXX,  XXXXXXX,  KC_MUTE,  XXXXXXX,  XXXXXXX,
                                  _______,  _______,  _______,  _______,  _______,  _______
  ),
  [_SYMBOLS] = LAYOUT_split_3x5_3(
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_LCTL,  KC_SCLN,  _______,  _______,  _______,                      KC_PGUP,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_BSLS,                      KC_PGDN,  KC_GRV,   KC_COMM,  KC_DOT,   KC_SLSH,
                                  NUMPADD,  KC_BSPC,  KC_DEL,   _______,  _______,  _______
  ),
  [_NUM] = LAYOUT_split_3x5_3(
    KC_TAB,   winLeft,  KC_UP,    winRght,  KC_QUOT,                      KC_CIRC,  KC_P7,    KC_P8,    KC_P9,    KC_PMNS,
    KC_LCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_DOT,                       KC_LPRN,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_LSFT,  KC_ESC,   KC_LGUI,  KC_LALT,  KC_COMM,                      KC_RPRN,  KC_P1,    KC_P2,    KC_P3,    KC_PDOT,
                                  _______,  KC_MPLY,  KC_MPLY,  KC_PENT,  KC_P0,  nmLkSym    
  ),
  [_FUNC] = LAYOUT_split_3x5_3(
    KC_F1,    KC_F2,    KC_F4,    KC_F8,    KC_F16,                       _______,  KC_WH_L,  SOCD_MU,  KC_WH_R,  KC_BTN3,
    KC_LCTL,  KC_CAPS,  _______,  _______,  _______,                      KC_WH_U,  SOCD_ML,  SOCD_MD,  SOCD_MR,  KC_BTN1,
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
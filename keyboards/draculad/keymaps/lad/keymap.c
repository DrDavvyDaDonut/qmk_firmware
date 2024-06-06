/*
Copyright 2021 @mangoiv

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"

enum layer_number {
  _BASE,
  _ALT,
  _RAISE,
  _LOWER,
  _ADJUST,
  _MOUSE,
  _GAME
};

bool scrollOrArrow = true;

//  keycodes
enum draculad_keycodes {
  TOGG = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TOGG:
      if (record->event.pressed){
        scrollOrArrow = !scrollOrArrow;
      }
      return false;
    }
  return true;
}

#define ctrlA     LCTL_T(KC_A)
#define shftZ     LSFT_T(KC_Z)
#define lGuiC     LGUI_T(KC_C)
#define lAltV     LALT_T(KC_V)
#define ctlSemi   RCTL_T(KC_SCLN)
#define shftEnt   RSFT_T(KC_ENT)
#define guiComm   RGUI_T(KC_COMM)
#define rAltM     RALT_T(KC_M)
#define altTabr   LM(_ALT, MOD_LALT)
#define winLeft   S(G(KC_LEFT))
#define winRght   S(G(KC_RGHT))

#define QWERTY    TO(_BASE)
#define RAISE     MO(_RAISE)
#define LOWER     MO(_LOWER)
#define MOUSERR   TO(_MOUSE)
#define GAMEPAD   TO(_GAME)


//  start up  
void keyboard_post_init_user(void){
  rgblight_disable();
  combo_disable();
  set_single_persistent_default_layer(_BASE);
}

//  on layer changes
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  if (layer_state_cmp(state, _ADJUST)){
    combo_enable();
  } else {
    combo_disable();
  }
  return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] =  LAYOUT(
    KC_Q,   KC_W,     KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    ctrlA,  KC_S,     KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    ctlSemi,
    shftZ,  KC_X,     lGuiC,   lAltV,   KC_B,                         KC_N,    rAltM,   guiComm, KC_DOT,  shftEnt,
                                        TOGG,                         TOGG,
                               LOWER,   KC_BSPC, altTabr,    KC_QUOT, KC_SPC,  RAISE
  ),
  /*
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        XXXXXXX,                      XXXXXXX,
                                XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX


    _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______,
                                        _______,                      _______,
                               _______, _______, _______,    _______, _______, _______
  */
  
  [_ALT] = LAYOUT(
    KC_TAB,  XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        XXXXXXX,                      XXXXXXX,
                               XXXXXXX, KC_DEL,  _______,    XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [_RAISE] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_LCTL, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT,                      KC_PGUP, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
    KC_LSFT, KC_ESC,  KC_LGUI, KC_LALT, _______,                      KC_PGDN, KC_GRV,  KC_QUOT, KC_BSLS, KC_SLSH,
                                        _______,                      _______,
                                 LOWER, KC_BSPC, KC_DEL,     _______, _______, _______
  ),
  [_LOWER] = LAYOUT(
    KC_TAB,  winLeft, KC_UP,   winRght, _______,                      _______, KC_GRV,  KC_VOLU, KC_QUOT, _______,
    KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, _______,                      _______, KC_MPRV, KC_MUTE, KC_MNXT, _______,
    KC_LSFT, KC_ESC,  KC_LGUI, KC_LALT, _______,                      _______, KC_SLSH, KC_VOLD, KC_BSLS, KC_ENT,
                                        _______,                      KC_MUTE,
                               _______, KC_MPLY, _______,    _______, KC_MPLY, RAISE
  ),
  [_ADJUST] = LAYOUT(
    KC_F1,   KC_F2,   KC_F4,   KC_F8,   KC_F16,                       _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN3, 
    KC_LCTL, KC_CAPS, _______, _______, GAMEPAD,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, 
    KC_LSFT, KC_ESC,  KC_LGUI, KC_LALT, _______,                      KC_WH_D, MOUSERR, _______, _______, KC_BTN2,
                                        _______,                      _______,
                               _______, _______, _______,    _______, _______, _______
  ),
  [_MOUSE] = LAYOUT(
    KC_BTN3, KC_WH_L, KC_MS_U, KC_WH_R, QWERTY,                       QWERTY,  KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN3,
    KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1,
    KC_BTN2, _______, _______, QWERTY,  KC_WH_D,                      KC_WH_D, QWERTY,  _______, _______, KC_BTN2,
                                        QWERTY,                       QWERTY,
                               KC_ACL0, KC_ACL1, KC_ACL2,    KC_ACL2, KC_ACL1, KC_ACL0
  ),
  [_GAME] = LAYOUT(
    KC_Q, KC_W, KC_E, KC_R, KC_T,                        KC_Y, KC_U, KC_I,    KC_O,   KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G,                        KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,
    KC_Z, KC_X, KC_C, KC_V, KC_B,                        KC_N, KC_M, KC_COMM, KC_DOT, KC_ENT,
                            KC_ESC,                      QWERTY,
                   KC_LSFT, KC_BSPC, KC_LALT,   KC_LGUI, KC_SPC, KC_LCTL
  )

};

#ifdef OLED_ENABLE


oled_rotation_t oled_init_user(oled_rotation_t rotation) {

  if(is_keyboard_left()){
    return OLED_ROTATION_270;
  }
  else {
    return OLED_ROTATION_90;
  }
    
}

static void render_status(void) {
  if (!is_keyboard_master()){
    oled_write_P(PSTR("stoopid\n~~~~~~~~~~\n\n\n\n\n\n\n\n\n\n\n\n\n\\/^._.^\\/"), false);
    return;
  }
  
  oled_write_P(PSTR("smarty\n~~~~~~~~~~"), false);
  if  (scrollOrArrow){
    oled_write_P(PSTR("Scroll"), false);
  } else {
    oled_write_P(PSTR("Arrow"), false);
  }
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("\nCaps: "), false);
  oled_write_P(led_state.caps_lock ? PSTR("on ") : PSTR("off"), false);
  oled_write_P(PSTR("\n"), false);
  switch (get_highest_layer(layer_state)) {
    case _BASE:
      oled_write_P(PSTR("Base  "), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("Raise "), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("Lower "), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("Adjust"), false);
      break;
    case _MOUSE:
      oled_write_P(PSTR("Mouse "), false);
      break;
    case _ALT:
      oled_write_P(PSTR("Alter "), false);
      break;
    case _GAME:
      oled_write_P(PSTR("Gamer "), false);
      break;
    default:
      oled_write_P(PSTR("Unkn  "), false);
      break;
  }

  oled_write_P(PSTR("\n\n\n\n\n\n\n\n\n\n\n\\/^._.^\\/"), false);

}

bool oled_task_user(void) {
  render_status();
  return false;
}

#endif

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (IS_LAYER_ON(_LOWER)){
    if (index == 2) {
      // Volume control
      if (clockwise) {
        tap_code(KC_VOLD);
      } else {
        tap_code(KC_VOLU);
      }
    }
  } else if (IS_LAYER_ON(_MOUSE)){
    if (index == 0){
      if (clockwise){
        tap_code(KC_MS_R);
      } else {
        tap_code(KC_MS_L);
      }
    } else if (index == 2){
      if (clockwise){
        tap_code(KC_MS_D);
      } else {
        tap_code(KC_MS_U);
      }
    }
  } else {
    if (scrollOrArrow){
      if (index == 0){
        if (clockwise){
          tap_code(KC_WH_R);
        } else {
          tap_code(KC_WH_L);
        }
      } else if (index == 2){
        if (clockwise){
          tap_code(KC_WH_D);
        } else {
          tap_code(KC_WH_U);
        }
      }
    } else {
      if (index == 0){
        if (clockwise){
          tap_code(KC_RGHT);
        } else {
          tap_code(KC_LEFT);
        }
      } else if (index == 2){
        if (clockwise){
          tap_code(KC_DOWN);
        } else {
          tap_code(KC_UP);
        }
      }
    }
  }
  return false;
}
#endif


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

float MEGA[][2] = SONG(MEGALOVANIA);

enum preonic_layers {
  _BASE,
  _NUM,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MOUSE,
  _MUSIC
};

void keyboard_post_init_user(void){
  set_single_persistent_default_layer(_BASE);
  rgblight_disable();
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // PLAY_SONG(MEGA);
  switch (get_highest_layer(state)) {
  case _BASE:
    // rgblight_setrgb (0x00,  0x00, 0x00);
    break;
  case _LOWER:
    // rgblight_setrgb (0x00,  0x00, 0x00);
    break;
  case _RAISE:
    // rgblight_setrgb (0x00,  0xFF, 0xFF);
    break;
  case _ADJUST:
    // rgblight_setrgb (0x00,  0xFF, 0xFF);
    break;
  default: //  for any other layers, or the default layer
    // rgblight_setrgb (0x00,  0x00, 0x00);
  break;
  }
  return state;
}

#define QWERTY    TO(_BASE)
#define NUM       TT(_NUM)
#define WINLEFT   SGUI(KC_LEFT)
#define WINRGHT   SGUI(KC_RGHT)
#define TEMPMOS   MO(_MOUSE)
#define MOUSERR   TO(_MOUSE)
#define MUSICSS   TO(_MUSIC)


enum preonic_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,

  SANSUNDERTALE

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
  KC_CAPS, AU_NEXT, AU_NEXT, AU_ON,   AU_OFF,  _______, _______, QWERTY,  _______, MOUSERR, MUSICSS, SANSUNDERTALE,
  _______, _______, MU_NEXT, MU_ON,   MU_OFF,  _______, _______, QK_BOOT, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______
)

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
// [_ADJUST] = LAYOUT_preonic_grid(
//   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
//   _______, QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
//   _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______,
//   _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  QK_BOOT, _______, _______, _______, _______,
//   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// )


};

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
        case SANSUNDERTALE:
          if (record->event.pressed){
            PLAY_SONG(MEGA);
          }
          return false;
          break;
      }
    return true;
};

// bool muse_mode = false;
// uint8_t last_muse_note = 0;
// uint16_t muse_counter = 0;
// uint8_t muse_offset = 70;
// uint16_t muse_tempo = 50;

// bool encoder_update_user(uint8_t index, bool clockwise) {
//   if (muse_mode) {
//     if (IS_LAYER_ON(_RAISE)) {
//       if (clockwise) {
//         muse_offset++;
//       } else {
//         muse_offset--;
//       }
//     } else {
//       if (clockwise) {
//         muse_tempo+=1;
//       } else {
//         muse_tempo-=1;
//       }
//     }
//   } else {
//     if (clockwise) {
//       register_code(KC_PGDN);
//       unregister_code(KC_PGDN);
//     } else {
//       register_code(KC_PGUP);
//       unregister_code(KC_PGUP);
//     }
//   }
//     return true;
// }

// bool dip_switch_update_user(uint8_t index, bool active) {
//     switch (index) {
//         case 0:
//             if (active) {
//                 layer_on(_ADJUST);
//             } else {
//                 layer_off(_ADJUST);
//             }
//             break;
//         case 1:
//             if (active) {
//                 muse_mode = true;
//             } else {
//                 muse_mode = false;
//             }
//     }
//     return true;
// }


// void matrix_scan_user(void) {
// #ifdef AUDIO_ENABLE
//     if (muse_mode) {
//         if (muse_counter == 0) {
//             uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
//             if (muse_note != last_muse_note) {
//                 stop_note(compute_freq_for_midi_note(last_muse_note));
//                 play_note(compute_freq_for_midi_note(muse_note), 0xF);
//                 last_muse_note = muse_note;
//             }
//         }
//         muse_counter = (muse_counter + 1) % muse_tempo;
//     } else {
//         if (muse_counter) {
//             stop_all_notes();
//             muse_counter = 0;
//         }
//     }
// #endif
// }

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

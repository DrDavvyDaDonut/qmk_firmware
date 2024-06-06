/* Copyright 2015-2017 Jack Humbert
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
#define hand_swap_config

//layers
enum preonic_layers {
  _QWERTY,
  _FROG,
  _NUM,
  _MODLAYER,
  //_GAMETIME,
  //_MIDI,
  _LOWER,
  _RAISE,
  _ADJUST
};

/* easier keycode management that i found out a year after i started
#define KC_GAME TO(_GAMETIME)          //changes layer to game layer
#define KC_SHPL LGUI(LALT(KC_G))       //"shadowplay," i.e., clip it
#define GAMEBAR LGUI(KC_G)              //opens the game bar. pretty self explanitory
#define GAMEOVER TO(_QWERTY)
*/
//macro keycodes
enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  // QWENTR,
  FROG,
  LOWER,
  RAISE,
  FN,
  //MIDI,
  TYPE
};

/* songs that won't play because the speaker sucks
float QWERTY_SONG[][2] = SONG(QWERTY_SOUND);
float NEW_WORLD[][2] = SONG(NEW_WORLD_SYMPHONY);
float MEGA[][2] = SONG(MEGALOVANIA);
float midi_on_song[][2] = SONG(PLOVER_SOUND);
float midi_off_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
*/

//macro managment
// bool midi_on_or_not = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            //midi_off();
            set_single_persistent_default_layer(_QWERTY);
            //PLAY_SONG(QWERTY_SONG);
            rgblight_disable();
            combo_disable();
          }
          return false;
          break;
        /*
        case QWENTR:
            if (record->event.pressed) {
                layer_move(_QWERTY);
                set_single_persistent_default_layer(_QWERTY);
                tap_code(KC_ENT);
            }
            return false;
            break;
        */
        case FROG:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_FROG);
            //PLAY_SONG(NEW_WORLD);
            combo_enable();
            rgblight_enable();
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv(64, 230, 255);
          }
          return false;
          break;
        /*
        case MIDI:
          if (record->event.pressed) {
            if (midi_on_or_not == false){
              midi_on();
              midi_on_or_not = true;
              PLAY_SONG(midi_on_song);
              set_single_persistent_default_layer(_MIDI);
            } else {
              midi_off();
              midi_on_or_not = false;
              PLAY_SONG(midi_off_song);
              set_single_persistent_default_layer(_QWERTY);
            }
          }
          return false;
          break;
        */
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
          /*
        case TYPE:
          if (record->event.pressed) {
            //layer_on(_QWERTY);
            //midi_off();
          } else {
            //layer_off(_QWERTY);
            //midi_on();
          }
          return false;
          break;
        */
        case FN:
          if (record->event.pressed) {
            layer_on(_NUM);
          } else {
            layer_off(_NUM);
          }
      }
    //rgblight_disable();   //turns rgb off after a keypress
    return true;
};


//music shit i don't understand but doesn't seem to work
/*
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}
*/

// combo shit
enum combos {
  spaceTab,
  spaceF,
  spaceD,
  spaceN,
  spaceI,
  spaceG,
  spaceS,
  spaceT,
  spaceH,
  spaceE,
  spaceO,
  spaceC,
  spaceW,
  spaceR,
  spaceA,
  spaceU,
  space1,
  space2,
  space3,
  space4,
  space5
};

const uint16_t PROGMEM tab_combo[] = {KC_SPC, KC_TAB, COMBO_END};
const uint16_t PROGMEM f_combo[] = {KC_SPC, KC_F, COMBO_END};
const uint16_t PROGMEM d_combo[] = {KC_SPC, KC_D, COMBO_END};
const uint16_t PROGMEM n_combo[] = {KC_SPC, KC_N, COMBO_END};
const uint16_t PROGMEM i_combo[] = {KC_SPC, KC_I, COMBO_END};
const uint16_t PROGMEM g_combo[] = {KC_SPC, KC_G, COMBO_END};
const uint16_t PROGMEM s_combo[] = {KC_SPC, KC_S, COMBO_END};
const uint16_t PROGMEM t_combo[] = {KC_SPC, KC_T, COMBO_END};
const uint16_t PROGMEM h_combo[] = {KC_SPC, KC_H, COMBO_END};
const uint16_t PROGMEM e_combo[] = {KC_SPC, KC_E, COMBO_END};
const uint16_t PROGMEM o_combo[] = {KC_SPC, KC_O, COMBO_END};
const uint16_t PROGMEM c_combo[] = {KC_SPC, KC_C, COMBO_END};
const uint16_t PROGMEM w_combo[] = {KC_SPC, KC_W, COMBO_END};
const uint16_t PROGMEM r_combo[] = {KC_SPC, KC_R, COMBO_END};
const uint16_t PROGMEM a_combo[] = {KC_SPC, KC_A, COMBO_END};
const uint16_t PROGMEM u_combo[] = {KC_SPC, KC_U, COMBO_END};
const uint16_t PROGMEM one_combo[] = {KC_SPC, KC_1, COMBO_END};
const uint16_t PROGMEM two_combo[] = {KC_SPC, KC_2, COMBO_END};
const uint16_t PROGMEM three_combo[] = {KC_SPC, KC_3, COMBO_END};
const uint16_t PROGMEM four_combo[] = {KC_SPC, KC_4, COMBO_END};
const uint16_t PROGMEM five_combo[] = {KC_SPC, KC_5, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [spaceTab] = COMBO(tab_combo, KC_ENT),
  [spaceF] = COMBO(f_combo, KC_J),
  [spaceD] = COMBO(d_combo, KC_K),
  [spaceN] = COMBO(n_combo, KC_M),
  [spaceI] = COMBO(i_combo, KC_QUOT),
  [spaceG] = COMBO(g_combo, KC_QUES),
  [spaceS] = COMBO(s_combo, KC_Y),
  [spaceT] = COMBO(t_combo, KC_P),
  [spaceH] = COMBO(h_combo, KC_L),
  [spaceE] = COMBO(e_combo, KC_DOT),
  [spaceO] = COMBO(o_combo, KC_Q),
  [spaceC] = COMBO(c_combo, KC_X),
  [spaceW] = COMBO(w_combo, KC_B),
  [spaceR] = COMBO(r_combo, KC_V),
  [spaceA] = COMBO(a_combo, KC_COMM),
  [spaceU] = COMBO(u_combo, KC_Z),
  [space1] = COMBO(one_combo, KC_0),
  [space2] = COMBO(two_combo, KC_9),
  [space3] = COMBO(three_combo, KC_8),
  [space4] = COMBO(four_combo, KC_7),
  [space5] = COMBO(five_combo, KC_6)
};

/*
//unicode shit
enum unicode_names {
    EN,     // –, the en dash (U+2013)
    EM      // —, the em dash (U+2014)
};

const uint32_t PROGMEM unicode_map[] = {
    [EN] = 0x2013,
    [EM] = 0x2014,
};


void unicode_input_start(void) {
    register_code(KC_LALT);
    tap_code(KC_PPLS);
}

void unicode_input_finish(void) {
    unregister_code(KC_LALT);
}

//tap dance testing
enum {
    DASHES
};

void dashes_dance(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count){
        case 1:
            tap_code(KC_MINS);
            break;
        case 2:
            tap_code16(X(EN));
            //unicode_input_start();
            //register_code(KC_LALT);
            //tap_code(KC_PPLS);
            //SEND_STRING("2013");
            //unicode_input_finish();
            break;
        case 3:
            tap_code16(X(EM));
            //unicode_input_start();
            //SEND_STRING("2014");
            //unicode_input_finish();
            break;
    }

}

qk_tap_dance_action_t tap_dance_actions[] = {
    [DASHES] = ACTION_TAP_DANCE_FN(dashes_dance),
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Esc |  FN  | Alt  | Com  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_ESC,  FN,      KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),



/* frog
 * ,-----------------------------------------------------------------------------------.
 * |qwerty|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  tab |   f  |   d  |   n  |   i  |   g  |   -  |   '  |   m  |   k  |   j  |  ent |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | back |   s  |   t  |   h  |   e  |   o  |   q  |   .  |   l  |   p  |   y  | back |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | shift|   c  |   w  |   r  |   a  |   u  |   z  |   ,  |   v  |   b  |   x  | shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | flip |    space    |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FROG] = LAYOUT_preonic_grid(
  QWERTY,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  KC_TAB,     KC_F,    KC_D,    KC_N,    KC_I,    KC_G, KC_SLSH, KC_QUOT, KC_BSLS, KC_RPRN, KC_LPRN, QWERTY,
  KC_BSPC,    KC_S,    KC_T,    KC_H,    KC_E,    KC_O, KC_PGUP, KC_MINS,  KC_EQL, KC_RBRC, KC_LBRC, KC_BSPC,
  KC_LSFT,    KC_C,    KC_W,    KC_R,    KC_A,    KC_U, KC_PGDN,  KC_GRV,  KC_COMM, KC_DOT,  KC_SCLN, KC_LSFT,
  LM(_MODLAYER, MOD_LCTL), _______, LM(_MODLAYER, MOD_LGUI), LM(_MODLAYER, MOD_LALT),  SH_MON, KC_SPC, KC_SPC, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_ESC
 ),

 [_NUM] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_UP,   _______, _______, KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PAST, KC_BSPC,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_LPRN, KC_4,    KC_5,    KC_6,    KC_PPLS, KC_PMNS,
  _______,_______,SGUI(KC_LEFT),_______,SGUI(KC_RGHT),_______,KC_RPRN,KC_1,KC_2,   KC_3,    KC_PSLS, KC_PENT,
  _______, _______, KC_LGUI, KC_LALT,  SH_MON, KC_SPC,  KC_SPC,  KC_0,    KC_0,    KC_DOT,  _______, _______
 ),
/*
[_GAMETIME] = LAYOUT_preonic_grid(
  KC_1,    KC_0,    KC_F3,   KC_F4,   KC_F5,   KC_F6, _______, _______, _______, _______, _______, _______,
  KC_2,    KC_A,    KC_B,    KC_UP,   KC_C,    KC_D,    KC_E,    KC_F,    KC_G,    KC_H,    KC_I,    KC_SHPL,
  KC_LCTL, KC_J,    KC_LEFT, KC_DOWN, KC_RIGHT,KC_P,    KC_L,    KC_M,    KC_N,    KC_O,    KC_K,    GAMEBAR,
  KC_LSFT, KC_Q,    KC_R,    KC_S,    KC_T,    KC_U,    KC_V,    KC_W,    KC_X,    KC_Y,    KC_Z,    KC_ENT,
  KC_ESC,  KC_5,    KC_6,    KC_7,    KC_8,    _______, KC_9,    KC_SPC,  _______, _______, GAMEOVER,QWENTR
 ),
*/
[_MODLAYER] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  _______, FN,   _______, _______,    LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  f1  |  f2  |  f3  |  f4  |  f5  |  f6  |  f7  |  f8  |  f9  |  f10 |  f11 |  f12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |  del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | frog |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Pause    |      | Last | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  FROG,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, KC_MPLY, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  f1  |  f2  |  f3  |  f4  |  f5  |  f6  |  f7  |  f8  |  f9  |  f10 |  f11 |  f12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | caps |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ctrl |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  _______, _______, _______, _______, _______, _______, KC_PGUP, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, _______, _______, _______, _______, _______, KC_PGDN, KC_GRV,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  f1  |  f2  |  f3  |  f4  |  f5  |  f6  |  f7  |  f8  |  f9  |  f10 |  f11 |  f12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | caos |      |musMod| midi |      |      |      |qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |musTog|aud on|audOff|      |      | reset| debug|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_CAPS, _______, _______, _______, _______, _______, _______, QWERTY,  _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, RESET,   DEBUG,   _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* template
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
[layer name] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 ),
*/
/*
[_MIDI] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  XXXXXXX, TYPE,    XXXXXXX, XXXXXXX, LOWER,   XXXXXXX, XXXXXXX,  RAISE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
 ),
*/
};


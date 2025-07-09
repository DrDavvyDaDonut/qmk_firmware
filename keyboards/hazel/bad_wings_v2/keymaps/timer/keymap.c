#include QMK_KEYBOARD_H

void spaceThing(void);

enum layers {
  _BASE = 0,
  
};

enum keycodes {
  leftt = SAFE_RANGE,
  right
};

uint8_t lefttHeld = 0;
uint8_t rightHeld = 0;
bool active = false;

//  process keycode
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
  switch (keycode) {
    case leftt:
      if (record->event.pressed){
        lefttHeld++;
      } else {
        lefttHeld--;
      }
      spaceThing();
      return false;
      break;
    case right:
      if (record->event.pressed){
        rightHeld++;
      } else {
        rightHeld--;
      }
      spaceThing();
      return false;
      break;
    default:
      return true;
      break;
    }
  return true;
}

void spaceThing(void){
  if ((lefttHeld > 0) && (rightHeld > 0) && !active){
    register_code(KC_SPC);
    active = true;
    wait_ms(50);
  }

  if ((lefttHeld == 0) && (rightHeld == 0) && active){
    unregister_code(KC_SPC);
    active = false;
    wait_ms(50);
  }
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
                                  _______,  _______,  _______,  _______,  _______,  _______
*/

  [_BASE] = LAYOUT_split_3x5_3(
    leftt,  leftt,  leftt,  leftt,  leftt,                      right,  right,  right,  right,  right,
    leftt,  leftt,  leftt,  leftt,  leftt,                      right,  right,  right,  right,  right,
    leftt,  leftt,  leftt,  leftt,  leftt,                      right,  right,  right,  right,  right,
                                  leftt,  leftt,  leftt,  right,  right,  right
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


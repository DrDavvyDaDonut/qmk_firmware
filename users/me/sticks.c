uint8_t leftStick = 0;
uint8_t rghtStick = 0;
uint8_t whatStick = 0;
uint8_t dPadStick = 0;
uint8_t hatDaFuck = 0;

uint8_t shift;
uint8_t bit;

uint8_t fullStraight = 127;
uint8_t fullDiagonal = 90;
uint8_t halfSing = 63;
uint8_t halfDiag = 45;

void leftStick(uint16_t keycode, bool pressed){
  shift = keycode - LS_LEFT;
  bit = 0x11 << shift;

  if (pressed){
    leftStick |= bit;
  } else {
    leftStick &= ~bit;
  }

  if (shift < 2) {  //  right left 
    if (leftStick & 0x0C){  //  if up happening
      joystick_set_axis(0, pressed * fullDiagonal);
      joystick_set_axis(0, pressed ? fullDiagonal : fullStraight);
    }
  } else {  //  up down

  }
  
}
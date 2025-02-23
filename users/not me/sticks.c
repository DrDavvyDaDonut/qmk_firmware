uint8_t leftStick = 0;
uint8_t rghtStick = 0;
uint8_t whatStick = 0;
uint8_t dPadStick = 0;
uint8_t hatDaFuck = 0;

uint8_t shift;
uint8_t bit;
uint8_t bothBit;

uint8_t fullStraight = 127;
uint8_t fullDiagonal = 90;
uint8_t halfSing = 63;
uint8_t halfDiag = 45;

void updateLeftStick(uint16_t keycode, bool pressed){
  shift = keycode - LS_RGHT;
  bit = 0x01 << shift;
  bothBit = 0x11 << shift;

  if (pressed){
    leftStick &= ~(0x30 << (2 * (shift >> 1)));

    leftStick |= bothBit;
  } else {
    leftStick &= ~bothBit;

    leftStick |= (0x03 << (2 * (shift >> 1)));
  }

  switch ((leftStick & 0xF0)){
    case 0:
      joystick_set_axis(0, 0);
      joystick_set_axis(1, 0);
      break;
    case 1:
      joystick_set_axis(0, fullStraight);
      joystick_set_axis(1, 0);
      break;
    case 2:
      joystick_set_axis(0, -fullStraight);
      joystick_set_axis(1, 0);
      break;
    case 4:
      joystick_set_axis(0, 0);
      joystick_set_axis(1, fullStraight);
      break;
    case 5:
      joystick_set_axis(0, fullStraight);
      joystick_set_axis(1, fullStraight);
      break;
    case 6:
      joystick_set_axis(0, -fullStraight);
      joystick_set_axis(1, fullStraight);
      break;
    case 8:
      joystick_set_axis(0, 0);
      joystick_set_axis(1, -fullStraight);
      break;
    case 9:
      joystick_set_axis(0, fullStraight);
      joystick_set_axis(1, -fullStraight);
      break;
    case 10:
      joystick_set_axis(0, -fullStraight);
      joystick_set_axis(1, -fullStraight);
      break;
    default:
      joystick_set_axis(0, 0);
      joystick_set_axis(1, 0);
      break;
  }

}
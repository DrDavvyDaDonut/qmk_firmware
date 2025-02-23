#include "socd.h"

//  simulatious opposing cardinal direction cleaning
//  total state contains the info for two pairs of opposing cardinal directions
//  {    high nibble   }{    low nibble    }
//  [ 8 ][ 7 ][ 6 ][ 5 ][ 4 ][ 3 ][ 2 ][ 1 ]
//  { start  }{ state  }{ start  }{ state  }
//  bit is the bit being updated, will be an int with ONE bit active. Will always be in state.
void socdCleaner(uint8_t * totalState, uint8_t bit, bool on, uint16_t keyOne, uint16_t keyTwo){

  //  update state with desired bits
  if (on){
    *totalState |= bit;
  } else {
    *totalState &= ~bit;
  }

  //  okay let's break this down, piece by piece
  //  (highNibble << 2) will be 4 IFF we are dealing with the high nibble (pair two)
  //  use the bitshift shenanigans to isolate the bits we are looking at. 
  //  state is the current state of the pressed buttons
  //  start is used to determin the new direction
  //  after shifting over the bit, if it is greater than 0, then it is concerning the high nibble
  //  ...
  //  what a silly way to write this
  
  bool highNibble = bit >> 4;

  uint8_t shift = highNibble << 2;
  uint8_t state = (0x03 << shift) & *totalState;
  uint8_t start = (0x0C << shift) & *totalState;

  state >>= shift;
  start >>= shift;

  //  if they are not simultaneous
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

    *totalState &= ~(0x0C << shift);
    *totalState |= ((state << 2) << shift);
    return;
  }

  //  ACTUAL THINGS, BABY!!!
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
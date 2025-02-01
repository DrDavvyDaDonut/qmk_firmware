#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum keycodes {
  //  socd codes
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
  AR_L,
  AR_R,
  AR_U,
  AR_D,
  
  //  joystick codes
  #ifdef JOYSTICK_ENABLE

  //  left stick
  LS_LEFT,
  LS_RGHT,
  LS_UPUP,  
  LS_DOWN,
  //  right stick
  RS_LEFT,
  RS_RGHT,
  RS_UPUP,  
  RS_DOWN,
  //  what stick
  WS_LEFT,
  WS_RGHT,
  WS_UPUP,  
  WS_DOWN,

  //  d-pad
  DP_LEFT,
  DP_RGHT,
  DP_UPUP,
  DP_DOWN,
  //  hat????
  HT_LEFT,
  HT_RGHT,
  HT_UPUP,
  HT_DOWN,

  #endif

  USER_RANGE_END
}

#endif
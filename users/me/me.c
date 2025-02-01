#include "me.h"

bool process_record_user_me(uint16_t keycode, keyrecord_t *record) {

  switch (keycode){
    case SOCD_MR:
      socdCleaner(&mouseSOCD, 0x01, record->event.pressed, KC_MS_R, KC_MS_L);
      return false;
      break;
    case SOCD_ML:
      socdCleaner(&mouseSOCD, 0x02, record->event.pressed, KC_MS_R, KC_MS_L);
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
    case HK_R:
      socdCleaner(&gameSOCD, 0x01, record->event.pressed, KC_F, KC_S);
      return false;
      break;
    case HK_L:
      socdCleaner(&gameSOCD, 0x02, record->event.pressed, KC_F, KC_S);
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
    case RGHT:
      socdCleaner(&gameSOCD, 0x01, record->event.pressed, KC_D, KC_A);
      return false;
      break;
    case LEFT:
      socdCleaner(&gameSOCD, 0x02, record->event.pressed, KC_D, KC_A);
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
    case AR_R:
      socdCleaner(&gameSOCD, 0x01, record->event.pressed, KC_RGHT, KC_LEFT);
      return false;
      break;
    case AR_L:
      socdCleaner(&gameSOCD, 0x02, record->event.pressed, KC_RGHT, KC_LEFT);
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

    
    #ifdef JOYSTICK_ENABLE

    case LS_RGHT:
      
      return false;
      break;
    case LS_LEFT:
      
      return false;
      break;
    case LS_UPUP:
      
      return false;
      break;  
    case LS_DOWN:
      
      return false;
      break;
    case RS_RGHT:
      
      return false;
      break;
    case RS_LEFT:
      
      return false;
      break;
    case RS_UPUP:
      
      return false;
      break;  
    case RS_DOWN:
      
      return false;
      break;
    case WS_RGHT:
      
      return false;
      break;
    case WS_LEFT:
      
      return false;
      break;
    case WS_UPUP:
      
      return false;
      break;  
    case WS_DOWN:
      
      return false;
      break;
    case DP_RGHT:
      socdCleaner(&dPadStick, 0x01, record->event.pressed, DP_RGHT, DP_LEFT);
      return false;
      break;
    case DP_LEFT:
      socdCleaner(&dPadStick, 0x02, record->event.pressed, DP_RGHT, DP_LEFT);
      return false;
      break;
    case DP_UPUP:
      socdCleaner(&dPadStick, 0x10, record->event.pressed, DP_UPUP, DP_DOWN);
      return false;
      break;
    case DP_DOWN:
      socdCleaner(&dPadStick, 0x20, record->event.pressed, DP_UPUP, DP_DOWN);
      return false;
      break;
    case HT_RGHT:
      
      return false;
      break;
    case HT_LEFT:
      
      return false;
      break;
    case HT_UPUP:
      
      return false;
      break;
    case HT_DOWN:
      
      return false;
      break;

    #endif


    default:
      return true;
      break;
  } 
  return true;
}
#ifndef _STICKS
#def _STICKS

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
  JOYSTICK_AXIS_VIRTUAL,  // leftx
  JOYSTICK_AXIS_VIRTUAL,  // lefty
  JOYSTICK_AXIS_VIRTUAL,  // rightx
  JOYSTICK_AXIS_VIRTUAL,  // righty
  JOYSTICK_AXIS_VIRTUAL,  // what
  JOYSTICK_AXIS_VIRTUAL,  // huh
};

/*
joystick shit
*/
//  button cluster
#define	BC_DOWN   JS_0
#define	BC_RGHT   JS_1
#define	BC_LEFT   JS_2
#define	BC_UPUP   JS_3

//  bumpers
#define	L1_PRSS   JS_4
#define	R1_PRSS   JS_5
//  triggers
#define	L2_PRSS   JS_6
#define	R2_PRSS   JS_7

#define	GC_SLCT   JS_8   //  select
#define	GC_STRT   JS_9   //  start

//  sticks
#define	LS_PRSS   JS_10
#define	RS_PRSS   JS_11

//  d pad
#define DP_UPUP   JS_12
#define DP_DOWN   JS_13
#define DP_LEFT   JS_14
#define DP_RGHT   JS_15

#define	GC_HOME   JS_16  //  home (xbox button)

#endif
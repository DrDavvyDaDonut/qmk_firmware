SRC += me.c
SRC += socd.c

ifdef JOYSTICK_ENABLE
	SRC += sticks.c
endif

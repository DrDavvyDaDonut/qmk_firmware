# Enable Joystick
JOYSTICK_ENABLE = yes

JOYSTICK_DRIVER = digital

# saving space
TAP_DANCE_ENABLE = no
UNICODEMAP_ENABLE = no
BOOTMAGIC_ENABLE = no
DYNAMIC_MACRO_ENABLE = no
KEY_OVERRIDE_ENABLE = no
RGBLIGHT_ENABLE = no

LTO_ENABLE = no

# mouse
MOUSEKEY_ENABLE = yes

NKRO_ENABLE = yes

SRC += muse.c

AUDIO_ENABLE = yes
AUDIO_DRIVER = dac_additive


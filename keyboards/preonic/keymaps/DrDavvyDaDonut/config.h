#pragma once

#ifdef AUDIO_ENABLE
   #define PITCH_STANDARD_A 440.0f
	//#define TIMBRE_12 0.125f
   #define AUDIO_DAC_SAMPLE_MAX 0512U
   #define AUDIO_PIN A4
   #define AUDIO_PIN_ALT A5
   //#define AUDIO_DISABLE_TONE_MULTIPLEXING
   //#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 1
   //#define AUDIO_VOICES
   #define AUDIO_DAC_SAMPLE_WAVEFORM_SINE

   #define NEW_WORLD_SYMPHONY M__NOTE(_E6, 256-8), M__NOTE(_REST, 8), M__NOTE(_FS6, 128-8), M__NOTE(_REST, 8), M__NOTE(_G6, 128-8), M__NOTE(_REST, 8), M__NOTE(_FS6, 192-8), M__NOTE(_REST, 8), M__NOTE(_E6, 64-8), M__NOTE(_REST, 8), M__NOTE(_E6, 256)
   #define MEGALOVANIA M__NOTE(_D5, 32-8), M__NOTE(_REST, 8), M__NOTE(_D5, 32-8), M__NOTE(_REST, 8), M__NOTE(_D6, 64-8-16), M__NOTE(_REST, 8+16), M__NOTE(_A5, 64)

#endif

// #define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

// #define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

//#define USB_MAX_POWER_CONSUMPTION 100

//#define RGBLIGHT_LAYERS

#define COMBO_COUNT 21
#define COMBO_TERM 60

#define TAPPING_TERM 220
#define TAPPING_TERM_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT
#define RETRO_TAPPING

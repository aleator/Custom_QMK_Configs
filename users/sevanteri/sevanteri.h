#pragma once
#include "keymap_swedish.h"

enum customKeycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    CODEBLK, // `code`
};

enum my_layers {
    BASE = 0, // default layer
    SYMB, // numbers and symbols
    MOUS,
    GAME, // gaming layer
    FUNCL, // function layer
    STUF, // reset and maybe some other stuff
};

// mod taps (no ignore_mod_tap_interrupt)
#define  CTRLESC  LCTL_T(KC_ESC)   // hold esc for ctrl
#define  LGUIESC  LGUI_T(KC_ESC)   // hold esc for super
#define  LGUIBSP  LGUI_T(KC_BSPC)  // hold backspace for super (left hand)
#define  LCTLBSP  LCTL_T(KC_BSPC)  // hold backspace for ctrl (left hand)
#define  LALTSPC  LALT_T(KC_SPC)   // hold space for alt (left hand)
#define  LALTESC  LALT_T(KC_ESC)   // hold thumb esc for alt (left hand)
#define  LSFT_LT  LSFT_T(SE_LABK)  // left shift is ISO/ on tap

// tap mods (ignore_mod_tap_interrupt)
#define FUNCENT LT(FUNCL, KC_ENT) // hold enter for func layer (right hand)
#define SYMBSPC LT(SYMB, KC_SPC) // hold space for symbol layer (right hand)
#define RSFTSPC RSFT_T(KC_SPC) // hold space for shift

#define SYMBENT LT(SYMB, KC_ENT) // hold enter for symbol layer (right hand)

// no permissive hold for top row keys
#define  MT_Q  KC_Q
#define  MT_W  KC_W
#define  MT_E  KC_E
#define  MT_R  KC_R
#define  MT_T  KC_T
#define  MT_Y  KC_Y
#define  MT_U  KC_U
#define  MT_I  KC_I
#define  MT_O  KC_O
#define  MT_P  KC_P

// no permissive hold for homerow keys
#define MT_A  LCTL_T(KC_A)
#define MT_S  LSFT_T(KC_S)
#define MT_D  KC_D
#define MT_F  KC_F
#define MT_G  KC_G
#define MT_H  KC_H
#define MT_J  KC_J
#define MT_K  KC_K
#define MT_L  LALT_T(KC_L)
#define MT_OE RCTL_T(SE_ODIA)

#define MT_AE RGUI_T(SE_ADIA)

// no permissive hold for bottom row keys
#define  MT_Z     KC_Z
#define  MT_X     KC_X
#define  MT_C     KC_C
#define  MT_V     KC_V
#define  MT_B     KC_B
#define  MT_N     KC_N
#define  MT_M     KC_M
#define  MT_COMM  KC_COMM
#define  MT_DOT   KC_DOT
#define  MT_MINS  SE_MINS


// other keys
#define CTRLTAB LCTL(KC_TAB)
#define CSFTTAB LCTL(LSFT(KC_TAB))

#ifdef TAP_DANCE_ENABLE
// tap dances
enum tapdance_buttons {
    TD_HOME_END = 0,
    TD_PSCR_INS,
    TD_HOME_END_MOD,
};
#define HOMEND TD(TD_HOME_END)
#define PSCRINS TD(TD_PSCR_INS)
#define TD_HEMD TD(TD_HOME_END_MOD)
#endif

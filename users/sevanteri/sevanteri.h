#pragma once
#include "keymap_swedish.h"

enum customKeycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    CODEBLK, // `code`
};

enum my_layers {
    BASE = 0, // default layer
    SYMB, // numbers and symbols
    GAME, // gaming layer
    FUNCL, // function layer
    STUF, // reset and maybe some other stuff
};

// mod taps (no ignore_mod_tap_interrupt)
#define CTRLESC LCTL_T(KC_ESC) // hold esc for ctrl
#define LGUIESC LGUI_T(KC_ESC) // hold esc for super
#define LGUIBSP LGUI_T(KC_BSPC) // hold backspace for super (left hand)
#define LCTLBSP LCTL_T(KC_BSPC) // hold backspace for ctrl (left hand)
#define LALTSPC LALT_T(KC_SPC) // hold space for alt (left hand)
#define LSFT_LT LSFT_T(SE_LABK) // left shift is ISO/ on tap

// tap mods (ignore_mod_tap_interrupt)
#define FUNCENT LT(FUNCL, KC_ENT) // hold enter for func layer (right hand)
#define SYMBSPC LT(SYMB, KC_SPC) // hold space for symbol layer (right hand)
#define RSFTSPC RSFT_T(KC_SPC) // hold space for shift

#define SYMBENT LT(SYMB, KC_ENT) // hold enter for symbol layer (right hand)

// no permissive hold for homerow keys
#define MT_A  LCTL_T(KC_A)
#define MT_S  LSFT_T(KC_S)
#define MT_D  LGUI_T(KC_D)
#define MT_F  LSFT_T(KC_F)
#define MT_G  LGUI_T(KC_G)
#define MT_J  RSFT_T(KC_J)
#define MT_K  LGUI_T(KC_K)
#define MT_L  LALT_T(KC_L)
#define MT_OE RCTL_T(SE_ODIA)
#define MT_AE LCTL_T(SE_ADIA)

// other keys
#define CTRLTAB LCTL(KC_TAB)
#define CSFTTAB LCTL(LSFT(KC_TAB))

// tap dances
enum tapdance_buttons {
    TD_HOME_END = 0,
    TD_PSCR_INS,
    TD_HOME_END_MOD,
};
#define HOMEND TD(TD_HOME_END)
#define PSCRINS TD(TD_PSCR_INS)
#define TD_HEMD TD(TD_HOME_END_MOD)

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

// left thumb keys (no ignore_mod_tap_interrupt)
#define  MY_THL1  LT(MOUS, KC_BTN1)
#define  MY_THL2  LALT_T(KC_ESC)
#define  MY_THL3  LGUI_T(KC_BSPC)

// right thumb keys
#define  MY_THR3  LT(FUNCL, KC_ENT)
#define  MY_THR2  RSFT_T(KC_SPC)
#define  MY_THR1  LT(SYMB, KC_TAB)

// basic alpha keys {{{
#define  MY_Q  KC_Q
#define  MY_W  KC_W
#define  MY_E  KC_E
#define  MY_R  KC_R
#define  MY_T  KC_T
#define  MY_Y  KC_Y
#define  MY_U  KC_U
#define  MY_I  KC_I
#define  MY_O  KC_O
#define  MY_P  KC_P

#define MY_A  LCTL_T(KC_A)
#define MY_S  LSFT_T(KC_S)
#define MY_D  KC_D
#define MY_F  KC_F
#define MY_G  KC_G
#define MY_H  KC_H
#define MY_J  KC_J
#define MY_K  KC_K
#define MY_L  LALT_T(KC_L)
#define MY_OE RCTL_T(SE_ODIA)

#define MY_AE RGUI_T(SE_ADIA)

#define  MY_Z     KC_Z
#define  MY_X     KC_X
#define  MY_C     KC_C
#define  MY_V     KC_V
#define  MY_B     KC_B
#define  MY_N     KC_N
#define  MY_M     KC_M
#define  MY_COMM  KC_COMM
#define  MY_DOT   KC_DOT
#define  MY_MINS  LALT_T(SE_MINS)
//}}}

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

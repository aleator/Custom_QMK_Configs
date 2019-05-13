#pragma once

#define LAYOUT_ergodox_pretty_wrapper(...)   LAYOUT_ergodox_pretty(__VA_ARGS__)
#define LAYOUT_gergo_wrapper(...)            LAYOUT_gergo(__VA_ARGS__)

#define _________________QWERTY_L1_________________   KC_Q, KC_W, KC_E, KC_R, KC_T
#define _________________QWERTY_L2_________________   MT_A, MT_S, KC_D, KC_F, MT_G
#define _________________QWERTY_L3_________________   KC_Z, KC_X, KC_C, KC_V, KC_B

#define _________________QWERTY_R1_________________   KC_Y, KC_U, KC_I,    KC_O,   KC_P
#define _________________QWERTY_R2_________________   KC_H, KC_J, KC_K,    KC_L,   MT_OE
#define _________________QWERTY_R3_________________   KC_N, KC_M, KC_COMM, KC_DOT, SE_MINS


#define _________________SYMB_L1___________________   KC_1,       KC_2,       KC_3,       KC_4,       KC_5
#define _________________SYMB_L2___________________   LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5)
#define _________________SYMB_L3___________________   _______,    RALT(KC_2), RALT(KC_3), RALT(KC_4), RALT(KC_5)

#define _________________SYMB_R1___________________   KC_6,       KC_7,       KC_8,       KC_9,       KC_0
#define _________________SYMB_R2___________________   LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0)
#define _________________SYMB_R3___________________   _______,    RALT(KC_7), RALT(KC_8), RALT(KC_9), RALT(KC_0)


#define _________________FUNCL_L1__________________   KC_F1, KC_F2,  KC_F3,  KC_F4,  _______
#define _________________FUNCL_L2__________________   KC_F5, KC_F6,  KC_F7,  KC_F8,  _______
#define _________________FUNCL_L3__________________   KC_F9, KC_F10, KC_F11, KC_F12, _______

#define _________________FUNCL_R1__________________   KC_WBAK, CTRLTAB, CSFTTAB, KC_WFWD, KC_VOLU
#define _________________FUNCL_R2__________________   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD
#define _________________FUNCL_R3__________________   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY

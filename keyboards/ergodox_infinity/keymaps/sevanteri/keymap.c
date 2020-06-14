/* vim: set fdm=marker */
// Nordic layout for Ergodox infinity

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "action.h"
#include "version.h"
#include "keymap_swedish.h"
#include "sevanteri.c"
#include "wrappers.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Basic layer {{{
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  ISO/  |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   +    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Tab   |   Q  |   W  |   E  |   R  |   T  |  ¨^  |           |  Å   |   Y  |   U  |   I  |   O  |   P  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  ESC   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ö  |   Ä    |
 * |--------+------+------+------+------+------| DEL  |           | BSPC |------+------+------+------+------+--------|
 * | LShift<|   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |  -   | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Ctrl |  ´`  |  §½  | RBTN | LBTN |                                       | SYMB | PRSC | INS  | RALT | SWAP |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | HOME | END  |       | PgUp |RCTRL |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 | LATL |      |FUNCL |       | PgDn |  FUNC  | Shift|
 *                                 | Space| BSPC |------|       |------|  Enter | Space|
 *                                 |      |      | LCTRL|       |FUNCL |        |      |
 *                                 `--------------------'       `----------------------'
 */

// layer 0 : default
[BASE] = LAYOUT_ergodox_pretty_wrapper(

    SE_SECT,  _________________SYMB_L1___________________, _______,   /*****/ _______,  _________________SYMB_R1___________________, SE_PLUS,
    KC_TAB,   _________________QWERTY_L1_________________, SE_DIAE,   /*****/ SE_ARNG,  _________________QWERTY_R1_________________, SE_QUOT,
    KC_ESC,   _________________QWERTY_L2_________________, /**/       /*****/ /**/      _________________QWERTY_R2_________________, MY_AE,
    KC_LSFT,  _________________QWERTY_L3_________________, KC_DEL,    /*****/ KC_BSPC,  _________________QWERTY_R3_________________, KC_RSFT,
    KC_NO,   SE_ACUT, _______, ____QWERTY_L4___, /******/ /******/   /*****/ ____QWERTY_R4___, KC_INS, KC_RALT,  KC_NO,

    /******/  /******/ /******/ /******/ /******/ TD_HEMD, KC_END,    /*****/ KC_PGUP,   KC_RCTRL,
    /******/  /******/ /******/ /******/ /******/ /******/ _______,   /*****/ KC_PGDN,
    /******/  /******/ /******/ /******/ _QWERTY_THUMBL__, KC_LCTRL,  /*****/ MO(FUNCL), _QWERTY_THUMBR__

),
// }}}
/* Number and symbol layer {{{
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   §    |  1   |  2   |  3   |  4   |  5   |  ~   |           |      |  6   |  7   |  8   |  9   |  0   |   +    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   ½    |  !   |  "   |  #   |  ¤   |  %   |------|           |------|  &   |  /   |  (   |  )   |  =   |   ?    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |   /    |      |  @   |  £   |  $   |  ‰   |      |           |      |  ‚   |  {   |  [   |  ]   |  }   |   \    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |       |     | CODE |                                       |      |  ´   |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |  .   |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */

// number and symbol layer
[SYMB] = LAYOUT_ergodox_pretty_wrapper(

    _______,       _______, _______, _______, _______, _______, _______,       /*****/ _______, _______, _______, _______, _______, _______, _______,
    SE_SECT,       _________________SYMB_L1___________________, RALT(SE_DIAE), /*****/ _______, _________________SYMB_R1___________________, SE_PLUS,
    LSFT(SE_SECT), _________________SYMB_L2___________________, /******/       /*****/ /******/ _________________SYMB_R2___________________, LSFT(SE_PLUS),
    RALT(SE_SECT), _________________SYMB_L3___________________, _______,       /*****/ _______, _________________SYMB_R3___________________, RALT(SE_PLUS),
    _______,       _______, _______, ____SYMB_L4_____, /******/ /******/       /*****/ /******/ /******/ ____SYMB_R4_____, _______, _______, _______,

    /******/       /******/ /******/ /******/ /******/ _______, _______,       /*****/ _______, _______,
    /******/       /******/ /******/ /******/ /******/ /******/ _______,       /*****/ _______,
    /******/       /******/ /******/ /******/ ___SYMB_THUMBL__, _______,       /*****/ _______, ___SYMB_THUMBR__

),
// }}}
/* Function layer {{{
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |      | GAME |           |      |BRBAK | CTAB |CSTAB |BRFWD |VOLUP |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F5  |  F6  |  F7  |  F8  |      |------|           |------| LEFT | DOWN |  UP  |RIGHT |VOLDN |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F9  |  F10 |  F11 |  F12 |      |      |           |      | MLEFT| MDOWN| MUP  |MRIGHT| PLAY |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |       |     |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |BLTOG |       |      |      |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      | BL+  |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      | BL-  |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */

// layer 1 : functions
[FUNCL] = LAYOUT_ergodox_pretty_wrapper(

    _______, _______, _______, _______, _______, _______, _______,  /*****/ _______, _______, _______, _______, _______, _______, _______,
    _______, _________________FUNCL_L1__________________, TG(GAME), /*****/ _______, _________________FUNCL_R1__________________, _______,
    _______, _________________FUNCL_L2__________________, /******/  /*****/ /******/ _________________FUNCL_R2__________________, _______,
    _______, _________________FUNCL_L3__________________, _______,  /*****/ _______, _________________FUNCL_R3__________________, _______,
    _______, _______, _______, ____FUNC_L4_____, /******/ /******/  /*****/ /******/ /******/ ____FUNC_R4_____, _______,  _______, _______,

    /******/ /******/ /******/ /******/ /******/ _______, BL_TOGG,  /*****/ _______, _______,
    /******/ /******/ /******/ /******/ /******/ /******/ BL_INC,   /*****/ _______,
    /******/ /******/ /******/ /******/ ___FUNC_THUMBL__, BL_DEC,   /*****/ _______, ___FUNC_THUMBR__

),
// }}}
/* Gaming {{{
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |      |      |      |      |      |      |           |      |      |      |      |      |      | RESET  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LCTRL  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |       |     |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 | Space| Space|      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */

// gaming layer
[GAME] = LAYOUT_ergodox_pretty_wrapper(

    KC_ESC,   _______, _______, _______, _______, _______, _______, /*****/ _______, _______, _______, _______, _______, _______, RESET,
    _______,  _______, _______, _______, _______, _______, _______, /*****/ _______, _______, _______, _______, _______, _______, _______,
    KC_LCTRL, _______, _______, _______, _______, _______, /**/     /*****/ /**/     _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, /*****/ _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, /**/     /**/     /*****/ /**/     /**/     _______, _______, _______, _______, _______,

    /**/      /**/     /**/     /**/     /**/     _______, _______, /*****/ _______, _______,
    /**/      /**/     /**/     /**/     /**/     /**/     _______, /*****/ _______,
    /**/      /**/     /**/     /**/     KC_SPC,  KC_SPC,  _______, /*****/ _______, _______, _______

)
// }}}
/* Mouse {{{
 *
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |       |     |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
,[MOUS] = LAYOUT_ergodox_pretty_wrapper(

    _______,  _______, _______, _______, _______, _______, _______, /*****/ _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, _______, /*****/ _______, _______, _______, _______, _______, _______, _______,
    _______,  _______, _______, _______, _______, _______, /**/     /*****/ /**/     _________________MOUS_R2___________________, _______,
    _______,  _______, _______, _______, _______, _______, _______, /*****/ _______, _________________MOUS_R3___________________, _______,
    _______,  _______, _______, _______, _______, /**/     /**/     /*****/ /**/     /**/     ____MOUS_R4_____, _______, _______, _______,

    /**/      /**/     /**/     /**/     /**/     _______, _______, /*****/ _______, _______,
    /**/      /**/     /**/     /**/     /**/     /**/     _______, /*****/ _______,
    /**/      /**/     /**/     /**/     _______, _______, _______, /*****/ _______, ___MOUS_THUMBR__

)
// }}}

};

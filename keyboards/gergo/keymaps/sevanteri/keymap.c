/* vim: set fdm=marker */
/* Good on you for modifying your layout! if you don't have
 * time to read the QMK docs, a list of keycodes can be found at
 *
 * https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
 *
 * There's also a template for adding new layers at the bottom of this file!
 */

#include QMK_KEYBOARD_H
/* #include "sevanteri.h" */
#include "sevanteri.c"
#include "gergo.h"
#include "wrappers.h"
#include "keymap_swedish.h"
#ifdef THUMBSTICK
#include "analog.c"
#include "pointing_device.h"
/* #include "print.h" */
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer {{{
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |  TAB   |   Q  |   W  |   E  |   R  |   T  |                         |   Y  |   U  |   I  |   O  |   P  |   '    |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |Ctrl/ESC|   A  |   S  |  D   |   F  |   G  | ¨^   |           |   Å  |   H  |   J  |   K  |   L  |   Ö  | RGUI/Ä |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * | LShift<|   Z  |   X  |   C  |   V  |   B  | LEAD |           |      |   N  |   M  |   ,  |   .  |   -  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                    .----------.   .-------.                                 .------.   .-------------.
 *                    |  RMB     |MMB|  LMB  |                                 | SYMB |   | PrntScrnIns |
 *                    '----------'   '-------'                                 `------.   '-------------'
 *                                        ,-------.                      ,-------.
 *                                        | HOMEND|                      | LEAD  |
 *                                 ,------|-------|                      |-------|------.
 *                                 | ALT  | Super |                      | FUNCL | Shift|
 *                                 | Space| BSPC  |                      | Enter | Space|
 *                                 |      |       |                      |       |      |
 *                                 `--------------'                      `--------------'
 */
[BASE] = LAYOUT_gergo_wrapper(
    KC_TAB,  _________________QWERTY_L1_________________, /**/     /**/     /**/ /**/     /**/     _________________QWERTY_R1_________________, SE_QUOT,
    CTRLESC, _________________QWERTY_L2_________________, SE_DIAE, /**/     /**/ /**/     SE_ARNG, _________________QWERTY_R2_________________, MT_AE,
    LSFT_LT, _________________QWERTY_L3_________________, KC_LEAD, TD_HEMD,  /**/ KC_LEAD, _______, _________________QWERTY_R3_________________, KC_RSFT,
    /******/ /******/ /******/ /******/ ____QWERTY_L4___, _QWERTY_THUMBL__, /**/  _QWERTY_THUMBR__, ____QWERTY_R4___
    ),
// }}}
/* Keymap 1: numbers and Symbols layer {{{
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |   §    |  1   |  2   |  3   |  4   |  5   |                         |   6  |  7   |  8   |  9   |  10  |   +    |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |   ½    |  !   |  "   |  #   |  4   |  5   |  ~   |           |      |   &  |  /   |  (   |  )   |  =   |   =    |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |   |    |      |  @   |  £   |  $   |  ‰   |      |           |      |      |  {   |  [   |  ]   |  }   |   \    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   | `   |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     |       |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |  .   |       |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[SYMB] = LAYOUT_gergo_wrapper(
    SE_SECT,       _________________SYMB_L1___________________, /******/   /******/ /****/ /******/ /******/ _________________SYMB_R1___________________, SE_PLUS,
    LSFT(SE_SECT), _________________SYMB_L2___________________, RALT(SE_DIAE), /**/ /****/ /******/ _______, _________________SYMB_R2___________________, LSFT(SE_PLUS),
    RALT(SE_LABK), _________________SYMB_L3___________________, _______, _______,   /****/ _______, _______, _________________SYMB_R3___________________, RALT(SE_PLUS),
    /******/       /******/ /******/ /******/ ____SYMB_L4_____, ___SYMB_THUMBL__,   /****/ ___SYMB_THUMBR__, ____SYMB_R4_____
    ),
// }}}
/* Keymap 2: Function layer {{{
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |  STUF  |  F1  | F2   | F3   | F4   |      |                         | WBAK | CTAB |CSTAB | WFWD |      | VolUp  |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--MUTE--|
 * |        |  F5  | F6   | F7   | F8   |      | PGUP |           |      | LEFT | DOWN |  UP  | RIGHT|      | VolDn  |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |  F9  | F10  | F11  | F12  |      | PGDN |           |      | MLFT | MDWN | MUP  | MRGHT|Ply/Pa|  Skip  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .------.
 *                        |      |   |      |                                 |      |   | RALT |
 *                        '------'   '------'                                 `------.   '------'
 *                                        ,-------.                     ,-------.
 *                                        |       |                     |       |
 *                                 ,------|-------|                     |-------|------.
 *                                 |      |       |                     |       |      |
 *                                 |      | DEL   |                     |       |      |
 *                                 |      |       |                     |       |      |
 *                                 `--------------'                     `--------------'
 */
[FUNCL] = LAYOUT_gergo_wrapper(
    MO(STUF), _________________FUNCL_L1__________________, /******/ /******/ /****/ /******/ /******/ _________________FUNCL_R1__________________, _______,
    _______,  _________________FUNCL_L2__________________, KC_PGUP, /******/ /****/ /******/ _______, _________________FUNCL_R2__________________, _______,
    _______,  _________________FUNCL_L3__________________, KC_PGDN, _______, /****/ _______, _______, _________________FUNCL_R3__________________, KC_MNXT,
    /******/  /******/ /******/ /******/ ____FUNC_L4_____, ___FUNC_THUMBL__, /****/ ___FUNC_THUMBR__, ____FUNC_R4_____
    ),
// }}}
/* Keymap 3: stuff {{{
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      | RESET  |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |CMBTOG|      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
 */
[STUF] = LAYOUT_gergo_wrapper(
    KC_TRNS, _________________STUFF_L1__________________,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
    KC_TRNS, _________________STUFF_L2__________________, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, _________________STUFF_L3__________________, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
//}}}
/* Mouse {{{
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
 */
[MOUS] = LAYOUT_gergo_wrapper(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, _________________MOUS_R2___________________, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, _________________MOUS_R3___________________, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         ___MOUS_THUMBR__, ____MOUS_R4_____
    )
//   }}}


};

/* Keymap template {{{
 *
 * ,-------------------------------------------.                         ,-------------------------------------------.
 * |        |      |      |      |      |      |                         |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------.           .------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|------|           |------|------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *                        .------.   .------.                                 .------.   .-----.
 *                        |      |   |      |                                 |      |   |     |
 *                        '------'   '------'                                 `------.   '-----'
 *                                        ,-------.       ,-------.
 *                                        |       |       |       |
 *                                 ,------|-------|       |-------|------.
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 |      |       |       |       |      |
 *                                 `--------------'       `--------------'
 */
/*
,[SYMB] = LAYOUT_gergo(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
//   }}}
 */


// joystick stuff {{{
#ifdef THUMBSTICK
int16_t xOrigin, yOrigin;
int16_t xLast, yLast;

uint8_t xPin  = B4;
uint8_t yPin  = B5;

uint16_t last = 0;
uint16_t timeout = 10;

void matrix_init_keymap(void) {
    // Account for drift
    xOrigin = analogRead(xPin);
    /* yOrigin = analogRead(yPin); */
    /* analogReference(ADC_REF_POWER); */
}

void pointing_device_task(void) {
    report_mouse_t report = pointing_device_get_report();

    int16_t xPosition = analogReadPin(xPin);
    /* int16_t yPosition = analogReadPin(yPin); */

    // the first if is not needed actually
    if (abs(xPosition - xLast) > 5) { // || abs(yPosition - yLast) > 10) {
        if (timer_elapsed(last) > timeout) {
            last = timer_read();
            report.x = 50 - (uint16_t)(((float)xPosition / 1023.0) * 100); 
            /* xprintf("%d:%d\n", xPosition, (uint16_t)(perc*100)); */
        }
        xLast = xPosition;
        /* yLast = yPosition; */
    }

    pointing_device_set_report(report);
    pointing_device_send();
}

#endif
// }}}

LEADER_EXTERNS();
void matrix_scan_user(void) { // {{{
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_B) {
        SEND_STRING("qmk gergo"SS_LSFT(".")"sevanteri"SS_LSFT(".")"dfu");
    }
    SEQ_TWO_KEYS(KC_R, KC_E) {
        reset_keyboard();
    }

    SEQ_ONE_KEY(KC_V) {
        tap_code(KC_HOME);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
    }
    SEQ_ONE_KEY(KC_S) {
        tap_code(KC_HOME);
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        tap_code(KC_BSPC);
    }
    SEQ_ONE_KEY(KC_C) {
        register_code(KC_LSFT);
        tap_code(KC_END);
        unregister_code(KC_LSFT);
        tap_code(KC_BSPC);
    }
  }
}
// }}}

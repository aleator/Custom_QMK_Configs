#include "timer.h"
#include "sevanteri.h"
#include "sendstring_finnish.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { // {{{
    return true;
}
// }}}

static uint16_t code_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record) { // {{{
    switch (keycode) {
        case CODEBLK:
            if (record->event.pressed) {
                code_timer = timer_read();
            } else {
                if (timer_elapsed(code_timer) > TAPPING_TERM) {
                    SEND_STRING(
                        "````````````"
                        SS_TAP(X_LEFT)
                        SS_TAP(X_LEFT)
                        SS_TAP(X_LEFT)
                    );
                } else {
                    SEND_STRING("``" SS_TAP(X_LEFT) "``");
                }
            }
            return false;
        default:
            return process_record_keymap(keycode, record);
    }
} // }}}

bool get_ignore_mod_tap_interrupt(uint16_t keycode) { // {{{
    switch (keycode) {
        case CTRLESC:
        case LGUIBSP:
        case LCTLBSP:
        case LALTSPC:
        case LSFT_LT:
        case RSFTSPC:
            return false;
        default:
            return true;
    }
}
// }}}

uint16_t get_permissive_hold(uint16_t keycode, keyrecord_t *record) { // {{{
    switch (keycode) {
        case MT_A:
        case MT_S:
        case MT_D:
        case MT_F:
        case MT_G:
        case MT_J:
        case MT_K:
        case MT_L:
        case MT_OE:
        case MT_AE:
            return false;
        default:
            return true;
    }
}
// }}}

// custom tapping terms for keys {{{
uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
        case SYMBSPC:
            return TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}
// }}}

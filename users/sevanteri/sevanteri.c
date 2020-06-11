#pragma once
#include "timer.h"
#include "sevanteri.h"
#include "sendstring_finnish.h"

#include "combos.h"

#ifdef TAP_DANCE_ENABLE
#include "tapdance.c"
#endif

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

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) { // {{{
    switch (keycode) {
        case MY_THL1:
        case MY_THL2:
        case MY_THL3:
            return false;
        default:
            return true;
    }
}
// }}}

uint16_t get_permissive_hold(uint16_t keycode, keyrecord_t *record) { // {{{
    switch (keycode) {
        case MY_A:
        case MY_S:
        case MY_D:
        case MY_F:
        case MY_G:
        case MY_J:
        case MY_K:
        case MY_L:
        case MY_OE:
        case MY_AE:
            return false;
        default:
            return true;
    }
}
// }}}

// custom tapping terms for keys {{{
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return TAPPING_TERM;
}
// }}}

// custom combo terms for combos {{{
uint16_t get_combo_term(uint8_t index, combo_t *combo) {
    if (KEYCODE_IS_MOD(combo->keycode)) return COMBO_MOD_TERM;

    switch(index) {
        case C_FUNCL:
            return COMBO_MOD_TERM;
    }

    return COMBO_TERM;
}
// }}}

bool get_combo_must_hold(uint8_t index, combo_t *combo) {
    switch(index) {
        case C_TLCTL:
        case C_TLSFT:
        case C_TLALT:
            return false;
    }

    if (KEYCODE_IS_MOD(combo->keycode)) return true;

    switch(index) {
        case C_FUNCL:
            return true;
    }

    return false;
}

void process_combo_event(uint8_t idx, bool pressed) {
    switch (idx) {
        case C_RESET:
            reset_keyboard();
            break;
        case C_FUNCL:
            if (pressed) {
                layer_on(FUNCL);
            } else {
                layer_off(FUNCL);
            }
            break;
        case C_VIM_V:
            tap_code(KC_HOME);
            register_code(KC_LSFT);
            tap_code(KC_END);
            unregister_code(KC_LSFT);
            break;
        case C_VIM_S:
            tap_code(KC_HOME);
            register_code(KC_LSFT);
            tap_code(KC_END);
            unregister_code(KC_LSFT);
            tap_code(KC_BSPC);
            break;
        case C_VIM_C:
            register_code(KC_LSFT);
            tap_code(KC_END);
            unregister_code(KC_LSFT);
            tap_code(KC_BSPC);
            break;
        default:
            break;
    }
}

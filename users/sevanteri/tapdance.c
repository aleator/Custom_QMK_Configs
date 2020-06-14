#pragma once
#include QMK_KEYBOARD_H
#include "sevanteri.h"
#include "process_tap_dance.h"

enum { REST, HOLD1, HOLD2, HOLD3 };

static int HomeEndMod = REST;
void modFinish(qk_tap_dance_state_t* state, void* user_data) {
	switch (state->count) {
		case 1:
			if (state->pressed) {
				register_code(KC_LCTL);
				HomeEndMod = HOLD1;
			} else {
				tap_code(KC_HOME);
			}
			break;
		case 2:
			if (state->pressed) {
				register_code(KC_LSFT);
				HomeEndMod = HOLD2;
			} else {
				tap_code(KC_END);
			}
			break;
		default:
			reset_tap_dance(state);
			break;
	}
}

void modReset(qk_tap_dance_state_t* state, void* user_data) {
	switch (HomeEndMod) {
		case HOLD1:
			unregister_code(KC_LCTL);
			break;
		case HOLD2:
			unregister_code(KC_LSFT);
			break;
	}
	HomeEndMod = REST;
}


qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_HOME_END]     = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
  [TD_PSCR_INS]     = ACTION_TAP_DANCE_DOUBLE(KC_PSCR, KC_INS),
  [TD_HOME_END_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, modFinish, modReset),
};

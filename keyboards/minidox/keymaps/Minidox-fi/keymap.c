#include QMK_KEYBOARD_H
#include "keymap_finnish.h"
#include <sendstring_finnish.h>

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 300
#define TAPPING_TERM 200

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

//Tap Dance Declarations
enum {
  TD_UP_PGUP = 0,
  TD_DOWN_PGDOWN
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  MOUSE,
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define START LCTL(KC_ESC)
#define TSKMGR LCTL(LSFT(KC_ESC))
#define WINLEFT LGUI((KC_LEFT))
#define WINRGHT LGUI((KC_RIGHT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  | ENT  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   Ä  |   Ö  | LDR  |   
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Ctrl | LOWER|      |    |      | RAISE| Shift|
 *                  `-------------| Space|    |BckSpc|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,  \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    FI_ADIA, FI_ODIA, KC_LEAD, \
                    KC_LCTL, LOWER, KC_SPC,         KC_BSPC, RAISE, OSM(MOD_LSFT)                \
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab | Left | Down |  Up  | Right|           |      |   -  |   =  |   [  |   ]  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Ctrl|   `  |  GUI |  Alt |      |           |      |      |   /  |   \  |   '  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  | Del  | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_RAISE] = LAYOUT( \
  KC_1,    KC_2,    KC_3,           KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    \
  KC_TAB,  KC_LEFT, KC_UP,     KC_UP,   KC_RGHT,      _______, KC_MINS, KC_EQL,  KC_LBRC,  KC_RBRC, \
  KC_LCTL, KC_GRV,  KC_GUI, KC_LALT, _______,      _______, KC_SLSH, KC_PIPE, KC_BSLS,  KC_QUOT, \
                    KC_DEL,         _______, _______,      _______, _______, _______                    \
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Esc |      |      |      |  ~   |           | PgUp |   _  |   +  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|      |      |      |      |           | PgDwn|   ,  |   .  |   |  |   "  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    | Enter|------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_LOWER] = LAYOUT( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC,   KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_ESC,  _______, _______, _______, KC_TILD,      KC_PGUP,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
  KC_CAPS, _______, _______, _______, _______,      KC_PGDOWN, FI_COMM, FI_DOT, KC_PIPE,  KC_DQT,  \
                    _______, _______, _______,      KC_ENT,    _______,   _______                  \
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |      | WLEFT|           |WRIGHT|      |STRT  |Taskmg|caltde|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,------,-------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `-------------|      |    |      |------+------.
 *                                |      |    |      |
 *                                `------'    `------'
 */
[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, \
  KC_F11,  KC_F12,  _______, _______, WINLEFT,      WINRGHT, _______, START,   TSKMGR,  CALTDEL, \
  RESET,   _______, _______, _______, _______,      _______, _______, _______, _______,  _______, \
                    _______, _______, _______,      _______, _______, _______                    \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

// Tap-dancing

qk_tap_dance_action_t tap_dance_actions[] = {
      //Tap once for Esc, twice for Caps Lock
      [TD_UP_PGUP]  	= ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP)
      , [TD_DOWN_PGDOWN]  = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDOWN)
      };

// <# Leader key #>
LEADER_EXTERNS();
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_Q) {
      // When I press KC_LEAD and then Q, this sends ALT-F4 ; _Q_uit
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    }

    SEQ_ONE_KEY(KC_S) {
      // When I press KC_LEAD and then s, this sends Ctrl-s ; _S_ave
      SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
    }
    SEQ_ONE_KEY(KC_X) {
      // When I press KC_LEAD and then x, this sends Ctrl-x ; 
      SEND_STRING(SS_LCTRL(SS_TAP(X_X)));
    }
    SEQ_ONE_KEY(KC_C) {
      // When I press KC_LEAD and then c, this sends Ctrl-c ; _C_opy
      SEND_STRING(SS_LCTRL(SS_TAP(X_C)));
    }
    SEQ_ONE_KEY(KC_V) {
      // When I press KC_LEAD and then c, this sends Ctrl-v ;
      SEND_STRING(SS_LCTRL(SS_TAP(X_V)));
    }
    SEQ_ONE_KEY(KC_A) {
      // When I press KC_LEAD and then a, this sends Ctrl-a ; _A_ll
      SEND_STRING(SS_LCTRL(SS_TAP(X_A)));
    }
    SEQ_TWO_KEYS(KC_D,KC_B) {
      // When I press KC_LEAD and then d b, this sends shift-Ctrl-left, del ; _D_elete _B_ackwards
      SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_LEFT)))SS_TAP(X_DEL));
    }
    SEQ_TWO_KEYS(KC_D,KC_F) {
      // When I press KC_LEAD and then d b, this sends shift-Ctrl-left, del ; _D_elete _F_orwards
      SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_RIGHT)))SS_TAP(X_DEL));
    }
    SEQ_TWO_KEYS(KC_C,KC_A) {
      // When I press KC_LEAD and then d b, this sends shift-Ctrl-left, del ; _C_opy _A_ll
      SEND_STRING(SS_LCTRL(SS_TAP(X_A)SS_TAP(X_C)));
    }
   SEQ_TWO_KEYS(KC_L, KC_S) {
     // When I press KC_LEAD and then L followed by S, this sends CTRL-ALT-DEL (L_ock S_creen)
     SEND_STRING(SS_LCTRL(SS_LALT(SS_TAP(X_DELETE))));
   }
  }
}


/*
 * TODO *
 
 Add auto-off for number layer (currently esc)
 Add haskell shorthands

  */


#include QMK_KEYBOARD_H
#include "keymap_finnish.h"
#include "config.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _RS 1
#define _LW 2
#define _BRACKET 4
#define _EXTEND 5
#define _HASKELL 6

enum custom_keycodes {
 QW = SAFE_RANGE,
 ALT_TAB,
 SHIFT_ALT_TAB,
 MAC_BACKTICK,
 SMART_BSPC, 

 PAR_PARENS,
 PAR_SQUARE,
 PAR_BRACKET,
 PAR_ANGLE,
 PAR_QUOT,
 PAR_DQUOT,
 PAR_BACKTICK,
 
 HS_IMPORT,
 HS_DERIVING,
 HS_MONOID,
 HS_QUALIFIED,
 HS_WHERE,
 HS_LET,
 HS_RETURN,
 HS_EITHER,
 HS_TYPE,
 HS_LANGUAGE,
 HS_BLOCK_COMM,
 HS_INSTANCE,
 HS_DATA,
 HS_PURE,
 HS_MEMPTY,
 HS_TEXT,
 HS_CASE,
 HS_JUST,
 HS_NOTHING,
 HS_MAYBE,
 HS_LEFT,
 HS_RIGHT,

 SYM_COMP_ARR, //*
 SYM_APP_ARR, //*
 SYM_BIND, //*
 SYM_FMAP, //*
 SYM_LFATARR, //*
 SYM_LARR, //*
 SYM_RARR, //*
 SYM_FAP, //*
 SYM_MAPPEND, //*
 SYM_TYPE,
 SYM_LAMBDA,
 SYM_EQ, //*
 SYM_NEQ, //*
 SYM_HOMEDIR, //*
 SYM_EXECHERE, //*
};

#define MAC_LBR S(RALT(KC_8))
#define MAC_RBR S(RALT(KC_9))
#define MAC_SQLBR RALT(KC_8)
#define MAC_SQRBR RALT(KC_9)
#define MAC_LT 53
#define MAC_GT S(53)
#define MAC_SLASH S(36)
#define MAC_PIPE RALT(36)
#define MAC_BACKSLASH S(RALT(36))

#define BACKSHIFTING(KC, CURSOR_POS, SS)                \
    case KC:                                            \
        if (record->event.pressed) {                    \
            SEND_STRING(SS);                            \
            for (size_t i = 0; i < CURSOR_POS; i++) {      \
                tap_code(KC_LEFT);                      \
            }                                           \
            inserted_on_left  = (sizeof SS) - CURSOR_POS-1; \
            inserted_on_right = CURSOR_POS;             \
        }                                               \
        break;

#define SIMPLE(KC, SS)                    \
    case KC:                              \
        if (record->event.pressed) {      \
            SEND_STRING(SS);              \
            inserted_on_left = sizeof SS-1; \
        }                                 \
        break;

#define SURROUND(KC, LEFT, RIGHT)    \
    case KC:                         \
        if (record->event.pressed) { \
            tap_code16(LEFT);        \
            tap_code16(RIGHT);       \
            tap_code(KC_LEFT);       \
            inserted_on_left  = 1;   \
            inserted_on_right = 1;   \
        }                            \
        return false;                \
        break;

enum COMBO_KEYS {semicolon_combo_key,
                 vim_write,
                 vim_quit,
                 vim_split,
                 vim_end_dot,
                 toggle_numbers
                 };

const uint16_t PROGMEM semicolon_combo[]      = {LT(_HASKELL,KC_COMM), KC_DOT, COMBO_END};
const uint16_t PROGMEM comma_colon_w[]        = {LT(_HASKELL,KC_COMM), KC_DOT, KC_W, COMBO_END};
const uint16_t PROGMEM comma_colon_q[]        = {LT(_HASKELL,KC_COMM), KC_DOT, KC_Q, COMBO_END};
const uint16_t PROGMEM comma_colon_e[]        = {LT(_HASKELL,KC_COMM), KC_DOT, KC_E, COMBO_END};
const uint16_t PROGMEM comma_colon_s[]        = {LT(_HASKELL,KC_COMM), KC_DOT, KC_S, COMBO_END};
const uint16_t PROGMEM n_m[]                  = {KC_N, KC_M, COMBO_END};

combo_t key_combos[COMBO_COUNT] = 
    { [semicolon_combo_key]      = COMBO(semicolon_combo, S(KC_DOT))
    , [vim_write]                = COMBO_ACTION(comma_colon_w)
    , [vim_quit]                 = COMBO_ACTION(comma_colon_q)
    , [vim_split]                = COMBO_ACTION(comma_colon_s)
    , [vim_end_dot]              = COMBO_ACTION(comma_colon_e)
    , [toggle_numbers]           = COMBO_ACTION(n_m)
    };

void process_combo_event(uint8_t combo_index, bool pressed) {
    switch (combo_index) {
        case vim_write:
            if (pressed) {
                tap_code(KC_ESC);
                tap_code16(S(KC_DOT));
                tap_code(KC_W);
                tap_code(KC_ENT);
            }
            break;
        case vim_quit:
            if (pressed) {
                tap_code(KC_ESC);
                tap_code16(S(KC_DOT));
                tap_code(KC_Q);
                tap_code(KC_ENT);
            }
            break;
        case vim_split:
            if (pressed) {
                tap_code(KC_ESC);
                tap_code16(S(KC_DOT));
                tap_code(KC_S);
                tap_code(KC_P);
                tap_code(KC_SPC);
            }
            break;
        case vim_end_dot:
            if (pressed) {
                tap_code(KC_ESC);
                tap_code16(S(KC_A));
                tap_code(KC_DOT);
                tap_code(KC_ESC);
            }
            break;
        case toggle_numbers:
            if (pressed) {
                layer_on(_RS);
            }
            break;
    };
}


#undef LAYOUT
#define LAYOUT( \
  k00, k01, k02, k03, k04,           k05, k06, k07, k08, k09, \
  k10, k11, k12, k13, k14,           k15, k16, k17, k18, k19, \
  k20, k21, k22, k23, k24,           k25, k26, k27, k28, k29, \
  k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b \
) \
{ \
	{ k00, k01, k02, k03, k04, ___, k05, k06, k07, k08, k09 }, \
	{ k10, k11, k12, k13, k14, ___, k15, k16, k17, k18, k19 }, \
	{ k20, k21, k22, k23, k24, k36, k25, k26, k27, k28, k29 }, \
	{ k30, k31, k32, k33, k34, k35, k37, k38, k39, k3a, k3b } \
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Qwerty */
    KC_Q              , KC_W   , KC_E              , KC_R                , KC_T  /*,         ,      */                    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    ,
    MT(MOD_LSFT,KC_A) , KC_S   , LT(_BRACKET,KC_D) , LT(_EXTEND,KC_F)    , KC_G  /*,         ,      */                    , KC_H    , KC_J    , KC_K    , KC_L    , MT(MOD_RSFT,FI_ODIA) ,
    KC_Z              , KC_X   , LT(_HASKELL,KC_C) , KC_V                , KC_B  /*,         ,      */                    , KC_N    , KC_M    , LT(_HASKELL,KC_COMM) , KC_DOT  , FI_ADIA ,
    KC_TAB            , MO(_LW) , ALT_TAB          , KC_LCTL , SMART_BSPC  , MT(MOD_HYPR,KC_ESC), KC_RGUI , LT(_RS,KC_SPC)   , KC_ENT  , FI_MINS , MAC_SLASH , S(45)
  ),

  [_EXTEND] = LAYOUT( 
    _______       , SHIFT_ALT_TAB , ALT_TAB       , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
    OSM(MOD_LSFT) , OSM(MOD_LCTL) , OSM(MOD_LGUI) , _______ , _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ ,
    _______       , OSM(MOD_LALT) , LGUI(KC_DOT)  , _______ , _______ , KC_HOME , KC_PGDN , KC_PGUP , KC_END  , _______ ,
    _______       , _______       , _______       , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),
  [_BRACKET] = LAYOUT( 
    _______ , _______ , _______ , FI_QUOT  , S(KC_2)                      , MAC_BACKTICK , FI_LPRN    , MAC_SQLBR  , MAC_LBR     , MAC_LT ,
    _______ , _______ , _______ , PAR_QUOT , PAR_DQUOT                    , PAR_BACKTICK , PAR_PARENS , PAR_SQUARE , PAR_BRACKET , PAR_ANGLE ,
    _______ , _______ , _______ , _______  , KC_NO                        , KC_NO        , FI_RPRN    , MAC_SQRBR  , MAC_RBR     , MAC_GT ,
    _______ , _______ , _______ , _______  , _______  , _______ , _______ , _______      , _______    , _______    , _______     , _______
  ),
  [_HASKELL] = LAYOUT( 
    HS_QUALIFIED , HS_WHERE , HS_EITHER , HS_RETURN , HS_TYPE            , HS_MEMPTY , _______ , HS_IMPORT , HS_MONOID , HS_PURE ,
    HS_LANGUAGE , HS_INSTANCE , HS_DATA , HS_LEFT , HS_RIGHT             , _______ , HS_JUST , _______ , HS_LET , _______ ,
    _______ , HS_TEXT , HS_CASE , HS_DERIVING , SYM_LAMBDA               , HS_NOTHING , HS_MAYBE , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),
  /*
     [_BLANK] = LAYOUT( 
    _______ , _______ , _______ , _______ , _______                      , _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______                      , _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______                      , _______ , _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______  , _______ , _______ , _______ , _______ , _______ , _______ , _______
  ),
  */

  // Missing KC_LCTL, KC_LALT

  /*
   *  !       @     up     {    }        ||     pgup    7     8     9    *
   *  #     left   down  right  $        ||     pgdn    4     5     6    +
   *  [       ]      (     )    &        ||       `     1     2     3    \
   * lower  insert super shift bksp ctrl || alt space   fn    .     0    =
   */
  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_ESC  , HS_BLOCK_COMM , KC_NO    , KC_LCBR      , KC_RCBR     , FI_PLUS , S(KC_7) , S(48)   , S(KC_9) , FI_EQL    ,
    KC_DEL  , SYM_RARR      , SYM_LARR , SYM_COMP_ARR , SYM_APP_ARR , FI_MINS , S(KC_4) , S(KC_5) , S(KC_6) , MAC_SLASH ,
    KC_NO   , SYM_FMAP      , SYM_FAP  , SYM_MAPPEND  , SYM_BIND    , FI_ASTR , S(KC_1) , A(KC_2) , S(KC_3) , FI_TILD   ,
    _______ , _______       , _______  , _______      , _______     , TO(_QW) , _______ , _______ , _______ , KC_DOT    , KC_0 , _______  ) ,
  /*
   * insert home   up  end   pgup       ||      up     F7    F8    F9   F10
   *  del   left  down right pgdn       ||     down    F4    F5    F6   F11
   *       volup             reset      ||             F1    F2    F3   F12
   *       voldn  super shift bksp ctrl || alt space   L0  prtsc scroll pause
   */
  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_INS  , KC_NO        , KC_NO       , KC_NO   , KC_NO   , MAC_SLASH , (KC_7)  , (KC_8) , (KC_9) , MAC_SLASH     ,
    KC_DEL  , SYM_HOMEDIR  , SYM_LFATARR , SYM_NEQ , SYM_EQ  , FI_EQL    , (KC_4)  , (KC_5) , (KC_6) , MAC_PIPE      ,
    KC_NO   , SYM_EXECHERE , KC_NO       , KC_NO   , RESET   , KC_NO     , (KC_1)  , (KC_2) , (KC_3) , MAC_BACKSLASH ,
    _______ , _______      , _______     , _______ , _______ , _______    , _______, _______, KC_0   , KC_0   , KC_0   , _______          )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool     alt_tab_alt       = false;
    static uint16_t backspace_timer   = 0;
    static size_t   inserted_on_left  = 0;
    static size_t   inserted_on_right = 0;
    // If last press was ALT_TAB, and this one isn't, release the left alt
    if (record->event.pressed && keycode != ALT_TAB && keycode != SHIFT_ALT_TAB && alt_tab_alt) {
        unregister_code(KC_LGUI);  // But, it is gui tab on my mac
        alt_tab_alt = false;
        // Ignore the next key
        return false;
    } else if (alt_tab_alt && keycode != ALT_TAB && keycode != SHIFT_ALT_TAB) {
        // released something other than alt_tab → release alt & keep going
        unregister_code(KC_LGUI);  // But, it is gui tab on my mac
        alt_tab_alt = false;
    }
    if (keycode == SMART_BSPC && record->event.pressed) {
        backspace_timer = timer_read();
        layer_on(_LW);
        return false;
    } 
    else if (keycode == SMART_BSPC && !record->event.pressed && timer_elapsed(backspace_timer) < TAPPING_TERM) {
        // release layer
        layer_off(_LW);
        // No current macro, do normal backspace
        if ((inserted_on_left == 0) && (inserted_on_right == 0)) {
            tap_code(KC_BSPC);
        }
        // If there are macro characters, erase, then zero out the character counters
        while (inserted_on_left > 0) {
            tap_code(KC_BSPC);
            inserted_on_left--;
        }
        while (inserted_on_right > 0) {
            tap_code(KC_DEL);
            inserted_on_right--;
        }
        // Stop processing here
        return false;
    }
    else if (keycode == SMART_BSPC && !record->event.pressed) {
        layer_off(_LW);
    }

    // Clear the multi-backspace on all characters here and
    // if there is a macro hit in the switch-case, restore it.
    if (record->event.pressed) {
    inserted_on_right = 0;
    inserted_on_left = 0;
    }

    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!alt_tab_alt) {
                    // first press, start holding alt.
                    register_code(KC_LGUI);
                    alt_tab_alt = true;
                }
                // on all presses, tab alt.
                tap_code(KC_TAB);
            }
            return false;
            break;
        case SHIFT_ALT_TAB:
            if (record->event.pressed) {
                if (!alt_tab_alt) {
                    // first press, start holding alt.
                    register_code(KC_LGUI);
                    alt_tab_alt = true;
                }
                // on all presses, tab alt.
                tap_code16(S(KC_TAB));
            }
            return false;
            break;
        case MAC_BACKTICK:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                tap_code(46);
                unregister_code(KC_LSFT);
                tap_code(44);
            }
            return false;
            break;
            SURROUND(PAR_PARENS, FI_LPRN, FI_RPRN)      // ()←
            SURROUND(PAR_SQUARE, MAC_SQLBR, MAC_SQRBR)  // []←
            SURROUND(PAR_BRACKET, MAC_LBR, MAC_RBR)     // {}←
            SURROUND(PAR_ANGLE, MAC_LT, MAC_GT)         // {}←
            SURROUND(PAR_QUOT, FI_QUOT, FI_QUOT)        // ''←
            SURROUND(PAR_DQUOT, S(KC_2), S(KC_2))       // ""←
        case PAR_BACKTICK:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                tap_code(46);
                unregister_code(KC_LSFT);
                tap_code(44);
                register_code(KC_LSFT);
                tap_code(46);
                unregister_code(KC_LSFT);
                tap_code(44);
                tap_code(KC_LEFT);
                inserted_on_left  = 1;
                inserted_on_right = 1;
            }
            return false;
            break;
            SIMPLE(HS_IMPORT, "import ")
            SIMPLE(HS_DERIVING, "deriving ")
            SIMPLE(HS_MONOID, "Monoid")
            SIMPLE(HS_QUALIFIED, "qualified ")
            SIMPLE(HS_WHERE, "where")
            SIMPLE(HS_LET, "let")
            SIMPLE(HS_RETURN, "return")
            SIMPLE(HS_EITHER, "Either")
            SIMPLE(HS_TYPE, "type")
        case HS_BLOCK_COMM:
            if (record->event.pressed) {
                tap_code16(S(A(KC_8)));
                tap_code16(FI_MINS);
                tap_code16(FI_MINS);
                tap_code16(S(A(KC_9)));
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                inserted_on_left  = 2;
                inserted_on_right = 2;
            }
            break;

        case HS_LANGUAGE:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_RALT);
                tap_code(KC_8);
                unregister_code(KC_RALT);
                unregister_code(KC_LSFT);
                tap_code(FI_MINS);
                register_code(KC_LSFT);
                tap_code(KC_3);
                unregister_code(KC_LSFT);

                SEND_STRING(" LANGUAGE  ");

                register_code(KC_LSFT);
                tap_code(KC_3);
                unregister_code(KC_LSFT);
                tap_code(FI_MINS);

                register_code(KC_LSFT);
                register_code(KC_RALT);
                tap_code(KC_9);
                unregister_code(KC_LSFT);
                unregister_code(KC_RALT);
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                inserted_on_left  = 13;
                inserted_on_right = 4;
            }
            break;
            SIMPLE(HS_INSTANCE, "instance")
            SIMPLE(HS_DATA, "Data.")
            SIMPLE(HS_PURE, "pure")
            SIMPLE(HS_MEMPTY, "mempty")
            SIMPLE(HS_TEXT, "Text")
        case SYM_LAMBDA:
            if (record->event.pressed) {
                tap_code16(MAC_BACKSLASH);
                tap_code(KC_SPC);
                tap_code(FI_MINS);
                tap_code16(MAC_GT);
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                tap_code(KC_LEFT);
                inserted_on_left  = 1;
                inserted_on_right = 3;
            }
            break;
        BACKSHIFTING(HS_CASE,3,"case  of")
        SIMPLE(HS_JUST, "Just")
        SIMPLE(HS_NOTHING, "Nothing")
        SIMPLE(HS_MAYBE, "Maybe")
        SIMPLE(HS_LEFT, "Left")
        SIMPLE(HS_RIGHT, "Right")
        SIMPLE(SYM_LARR, (SS_TAP(38) SS_DOWN(e5) SS_TAP(35) SS_UP(e5)))                                    //"->")
        SIMPLE(SYM_LFATARR, SS_DOWN(e5) SS_TAP(27) SS_TAP(35) SS_UP(e5))                                   //"=>")
        SIMPLE(SYM_RARR, SS_TAP(35) SS_TAP(56))                                                            //"<-")
        SIMPLE(SYM_COMP_ARR, SS_TAP(37) SS_DOWN(e5) SS_TAP(35) SS_UP(e5))                                  //".>")
        SIMPLE(SYM_APP_ARR, SS_DOWN(e6) SS_TAP(24) SS_UP(e6) SS_DOWN(e5) SS_TAP(35) SS_UP(e5))             //"|>"
        SIMPLE(SYM_BIND, SS_DOWN(e5) SS_TAP(35) SS_TAP(35) SS_TAP(27) SS_UP(e5))                           //">>=")
        SIMPLE(SYM_FMAP, SS_TAP(35) SS_DOWN(e6) SS_TAP(21) SS_UP(e6) SS_DOWN(e5) SS_TAP(35) SS_UP(e5))     // "<$>"
        SIMPLE(SYM_FAP, SS_TAP(35) SS_DOWN(e5) SS_TAP(31) SS_TAP(35) SS_UP(e5))                            // "<*>"
        SIMPLE(SYM_MAPPEND, SS_TAP(35) SS_DOWN(e5) SS_TAP(35) SS_UP(e5))                                   // "<>"
        SIMPLE(SYM_TYPE, SS_DOWN(e5) SS_TAP(37) SS_TAP(37) SS_UP(e5))                                      // "::"
        SIMPLE(SYM_EQ, SS_DOWN(e5) SS_TAP(27) SS_TAP(27) SS_UP(e5))                                        // "=="
        SIMPLE(SYM_NEQ, SS_DOWN(e5) SS_TAP(24) SS_TAP(27) SS_UP(e5))                                       // "/="
        SIMPLE(SYM_HOMEDIR, SS_DOWN(e6) SS_TAP(30) SS_UP(e6) SS_TAP(2c) SS_DOWN(e5) SS_TAP(24) SS_UP(e5))  // "~/"
        SIMPLE(SYM_EXECHERE, SS_TAP(2c) SS_DOWN(e5) SS_TAP(24) SS_UP(e5))                                  // "./"
    }
    return true;
}

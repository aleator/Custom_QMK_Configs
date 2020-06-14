/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "keymap_finnish.h"
#include "process_combo.h"
#include "raw_hid.h"

// <# Layer enumeration #>
enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _NAVI,
  _COMMA,
  _QPARENS,
  _HIGH_FS,
  _VIM_ZETTEL,
  //_DVORAK,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST
};

// <# Keycode enumeration #>
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  KC_SPC_TAB,
  ALT_TAB,
  //DVORAK,
  PLOVER,
  BACKLIT,
  EXT_PLV,
  ALE_COLON,
  ADIA_HOLD,
  ODIA_HOLD,
  QUESTION_HOLD,
  MAC_BACKTICK,

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

  SYM_LARR,     //*
  SYM_LFATARR,  //*
  SYM_RARR,    //*
  SYM_COMP_ARR, //*
  SYM_APP_ARR, //*
  SYM_BIND, //*
  SYM_FMAP, //*
  SYM_FAP, //*
  SYM_MAPPEND, //*
  SYM_TYPE,
  SYM_LAMBDA,
  SYM_EQ, //*
  SYM_NEQ, //*
  SYM_HOMEDIR, //*
  SYM_EXECHERE, //*

  PAR_PARENS,
  PAR_SQUARE,
  PAR_BRACKET,
  PAR_ANGLE,
  PAR_QUOT,
  PAR_DQUOT,
  PAR_BACKTICK,
  
  ZETTEL_WIKI,
  ZETTEL_EXT,
  ZETTEL_RESOLVE,
  ZETTEL_THREAD,
  ZETTEL_TEMPORAL,
  ZETTEL_SPLIT,
  ZETTEL_FIND,
  ZETTEL_RECENT,
  ZETTEL_LINK,
  ZETTEL_CREATE,
  ZETTEL_BACKLINKS,
  ZETTEL_NEIGHBOURS
};

// <# Custom keycodes #>
#define LOWER MO(_LOWER)
#define NAVI MO(_NAVI)
#define COMMA MO(_COMMA)
#define RAISE MO(_RAISE)

#define MAC_LBR S(RALT(KC_8))
#define MAC_RBR S(RALT(KC_9))
#define MAC_SQLBR RALT(KC_8)
#define MAC_SQRBR RALT(KC_9)
#define MAC_LT 53
#define MAC_GT S(53)
#define MAC_SLASH S(36)
#define MAC_PIPE RALT(36)
#define MAC_BACKSLASH S(RALT(36))


// <#TAP DANCE#>
enum {
  TD_COPY_CUT = 0,
  TD_SAVE_QUIT,
  TD_PARENTHESES,
  TD_BRACKETS,
  TD_SQUARE_BRACKETS
};

void dance_save_quit (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LGUI); tap_code(KC_S); unregister_code(KC_LGUI);
  }
  else if (state->count == 2) {
    register_code(KC_LGUI); tap_code(KC_W); unregister_code(KC_LGUI);
  } 
  else if (state->count == 3) {
    register_code(KC_LGUI); tap_code(KC_Q); unregister_code(KC_LGUI);
  } 
    reset_tap_dance (state);
}

void dance_copy_cut (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LGUI); tap_code(KC_C); unregister_code(KC_LGUI);
  }
  else if (state->count == 2) {
    register_code(KC_LGUI); tap_code(KC_X); unregister_code(KC_LGUI);
  } 
    reset_tap_dance (state);
}

void dance_parenthesis (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_LSFT);tap_code(KC_8); tap_code(KC_9); unregister_code(KC_LSFT); tap_code(KC_LEFT);
  }
  else if (state->count == 2) {
    register_code(KC_LSFT); tap_code(KC_9); unregister_code(KC_LSFT); 
  } 
  else if (state->count == 3) {
    register_code(KC_LSFT); tap_code(KC_8); unregister_code(KC_LSFT); 
  } 
    reset_tap_dance (state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_COPY_CUT]  = ACTION_TAP_DANCE_FN(dance_copy_cut),
  [TD_SAVE_QUIT]  = ACTION_TAP_DANCE_FN(dance_save_quit),
  [TD_PARENTHESES]  = ACTION_TAP_DANCE_FN(dance_parenthesis)
// Other declarations would go here, separated by commas, if you have them
};


// <# Combos #>
enum COMBO_KEYS {semicolon_combo_key,
                 paren_combo_key,
                 bracket_combo_key,
                 square_bracket_combo_key,
                 hs_either_combo_key,
                 };

const uint16_t PROGMEM semicolon_combo[]      = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM paren_combo[]          = {FI_LPRN, FI_RPRN, COMBO_END};
const uint16_t PROGMEM square_bracket_combo[] = {MAC_SQLBR, MAC_SQRBR, COMBO_END};
const uint16_t PROGMEM bracket_combo[]        = {MAC_LBR, MAC_RBR, COMBO_END};
const uint16_t PROGMEM hs_either_combo[]      = {HS_LET, HS_RETURN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = 
    { [semicolon_combo_key]      = COMBO(semicolon_combo, S(KC_DOT))
    , [paren_combo_key]          = COMBO_ACTION(paren_combo)
    , [bracket_combo_key]        = COMBO_ACTION(bracket_combo)
    , [square_bracket_combo_key] = COMBO_ACTION(square_bracket_combo)
    , [hs_either_combo_key]      = COMBO_ACTION(hs_either_combo)

    };

void process_combo_event(uint8_t combo_index, bool pressed) {

  switch(combo_index) {
	case paren_combo_key:
		if (pressed) {
        register_code(KC_LSFT);tap_code(KC_8); tap_code(KC_9); unregister_code(KC_LSFT); tap_code(KC_LEFT);
		}
	break;
	case bracket_combo_key:
		if (pressed) {
        register_code(KC_RALT);
        register_code(KC_RSFT);
        tap_code(KC_8); tap_code(KC_9); 
        unregister_code(KC_RALT);
        unregister_code(KC_RSFT);
        tap_code(KC_LEFT);
		}
	break;
	case square_bracket_combo_key:
		if (pressed) {
        register_code(KC_RALT);
        tap_code(KC_8); tap_code(KC_9); 
        unregister_code(KC_RALT);
        tap_code(KC_LEFT);
		}
	break;
	case hs_either_combo_key:
		if (pressed) {
            SEND_STRING("Either");
		}
	break;
  };
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* <# Qwerty #>
 * ,-----------------------------------------------------------------------------------.
 * | Q    |  W   |   E  |   R  |   T  |Qs/w/q| Qc/x |   Y  |   U  |   I  |   O  | P    |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | A    |   S  |   D  |F/NAVI|   G  |HYPESC| Q-v  |   H  |   J  |   K  |   L  |  Ä   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Z    |   X  |   C  |   V  |   B  | Q-z  |Ctrl/:|   N  |   M  |   ,  |   .  |  Ö   | <- This could be place for KC_LEAD
 * |------+------+------+------+------+------+------+------+------+------+------+------|    Another would be the ESC in the middle
 * | Brite| Ctrl | Alt  | GUI  |↓↓Bspc| SPACE/ .    |↑↑Ent | GUI  | Alt  | Ctrl | Shift|
 * `-----------------------------------------------------------------------------------'
[_QWERTY] = LAYOUT_planck_grid(
    KC_Q  ,  KC_W,    KC_E,    KC_R,             KC_T,   TD(TD_SAVE_QUIT),  TD(TD_COPY_CUT), KC_Y,    KC_U,    KC_I,    ODIA_HOLD,    KC_P   ,
    KC_A  ,  KC_S,    KC_D,    LT(_NAVI,KC_F),   KC_G,   MT(MOD_HYPR,KC_ESC),      RGUI(KC_V), KC_H,    KC_J,    KC_K,    KC_L   , FI_ADIA ,  // KC_SCLN
    KC_Z   , KC_X,    KC_C,    KC_V,             KC_B,    RGUI(KC_Z), ALE_COLON, KC_N,    KC_M,    LT(COMMA,KC_COMM), QUESTION_HOLD , FI_ODIA ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LT(LOWER,KC_BSPC),   KC_SPC_TAB,  KC_SPC_TAB,  LT(RAISE,KC_ENT),   KC_RGUI, KC_RALT, KC_LCTL, KC_RSFT
),
 */
/* Qwerty ORIG
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |ZETTEL|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |   A  |   S  |D/PARE|F/NAVI|   G  |   H  |   J  |   K  |   L  |   Ä  |  Ö   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | HYPER|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |  ?   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LSFT | Ctrl | Alt  | GUI  |↓↓BKSP|    Space    |↑↑Ent | GUI  | ALT  | CTRL | LSFT |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC    , KC_Q    , KC_W    , KC_E    , KC_R        , KC_T     , KC_Y     , KC_U   , KC_I     , KC_O    , KC_P      , OSL(_VIM_ZETTEL) ,
    LT(_COMMA , KC_TAB) , KC_A    , KC_S    , LT(_QPARENS , KC_D)    , LT(_NAVI , KC_F)  , KC_G     , KC_H    , KC_J      , KC_K    , KC_L    , FI_ODIA , FI_ADIA ,
    KC_HYPR   , KC_Z    , KC_X    , KC_C    , KC_V        , KC_B     , KC_N     , KC_M   , KC_COMM  , KC_DOT  , MAC_SLASH , S(45) ,
    KC_LSFT   , KC_LCTL , KC_LALT , KC_LGUI , LT(LOWER    , KC_BSPC) , KC_SPC   , KC_SPC , LT(RAISE , KC_ENT) , KC_RGUI   , KC_RALT , KC_LCTL , KC_RSFT
),
/* <# Colemak #> 
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
[_DVORAK] = LAYOUT_planck_grid(
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT ,
    BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),
 */

/* <# Lower #>
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |      |      |  /   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  | ~/   |  =>  |  /=  |  ==  |      |      |   _  |   +  |      |      |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  ./  |      |      |      |      |      |  "   |   -  |      |      |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_ESC  , FI_EXLM      , FI_AT       , FI_HASH , FI_DLR  , FI_PERC , FI_CIRC , FI_AMPR , FI_ASTR , _______   , _______   , MAC_SLASH     ,
    KC_DEL  , SYM_HOMEDIR  , SYM_LFATARR , SYM_NEQ , SYM_EQ  , _______ , _______ , FI_UNDS , FI_PLUS , _______   , _______   , MAC_PIPE      ,  
    _______ , SYM_EXECHERE , _______     , _______ , _______ , _______ , _______ , S(KC_2) , FI_MINS , _______   , _______   , MAC_BACKSLASH , 
    _______ , _______      , _______     , _______ , _______ , _______ , _______ , _______ , _______ , _______   , _______   , _______
),
/* Comma mode
 * ,-----------------------------------------------------------------------------------.
 * |      | Qual | Where| lEt  |Return| Type |memptY|      |Import|mOnoid| Pure |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ***  |lAngua|inStan| Data.| LeFt |riGht |      | Just |      | Let  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Text | Case |deriVi|lamBda|Noth  | Maybe|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |             |      |      |      |      |      
 * `-----------------------------------------------------------------------------------'
 */
[_COMMA] = LAYOUT_planck_grid(
    _______ , HS_QUALIFIED , HS_WHERE    , HS_EITHER , HS_RETURN   , HS_TYPE    , HS_MEMPTY  , _______  , HS_IMPORT , HS_MONOID , HS_PURE , _______ ,
    _______ , HS_LANGUAGE  , HS_INSTANCE , HS_DATA   , HS_LEFT     , HS_RIGHT   , _______    , HS_JUST  , _______   , HS_LET    , _______ , _______ ,
    _______ , _______      , HS_TEXT     , HS_CASE   , HS_DERIVING , SYM_LAMBDA , HS_NOTHING , HS_MAYBE , _______   , _______   , _______ , _______ ,
    _______ , _______      , _______     , _______   , _______     , _______    , _______    , _______  , _______   , _______   , _______ , _______
)           ,
/* BLANK
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |  '   |  "   |  `   | (    | [    | {    | <    |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ***  | ''←  | ""←  | ``←  | ()←  | []←  | {}←  | <>←  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | )    | [    | }    | >    |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QPARENS] = LAYOUT_planck_grid(
    _______ , _______ , _______ , _______ , FI_QUOT  , S(KC_2)   , MAC_BACKTICK , FI_LPRN    , MAC_SQLBR  , MAC_LBR     , MAC_LT    , _______ ,
    _______ , _______ , _______ , _______ , PAR_QUOT , PAR_DQUOT , PAR_BACKTICK , PAR_PARENS , PAR_SQUARE , PAR_BRACKET , PAR_ANGLE , _______ ,
    _______ , _______ , _______ , _______ , _______  , _______   , _______      , FI_RPRN    , MAC_SQRBR  , MAC_RBR     , MAC_GT    , _______ ,
    _______ , _______ , _______ , _______ , _______  , _______   , _______      , _______    , _______    , _______     , _______   , _______
),

/* ZETTEL
 * ,-----------------------------------------------------------------------------------.
 * |      | Wiki | Ext  | Reso | Thre |      | temp |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Spli |      | Find |      | Rece |      |      | Link |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Create|      | Back | Neig |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_VIM_ZETTEL] = LAYOUT_planck_grid(
    _______ , _______ , ZETTEL_WIKI  , ZETTEL_EXT    , ZETTEL_RESOLVE , ZETTEL_THREAD    , ZETTEL_TEMPORAL   , _______ , _______ , _______     , _______ , _______ ,
    _______ , _______ , ZETTEL_SPLIT , _______       , ZETTEL_FIND    , _______          , ZETTEL_RECENT     , _______ , _______ , ZETTEL_LINK , _______ , _______ ,
    _______ , _______ , _______      , ZETTEL_CREATE , _______        , ZETTEL_BACKLINKS , ZETTEL_NEIGHBOURS , _______ , _______ , _______     , _______ , _______ ,
    _______ , _______ , _______      , _______       , _______        , _______          , _______           , _______ , _______ , _______     , _______ , _______
),
[_HIGH_FS] = LAYOUT_planck_grid(
    KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_F17 ,  KC_F18 , KC_F19 , KC_F20 , KC_F21 , KC_F22 , KC_F23 , KC_F24 , 
    S( KC_F13 ) , S( KC_F14 ) , S( KC_F15 ) , S( KC_F16 ) , S( KC_F17 ) ,  S( KC_F18 ) , S( KC_F19 ) , S( KC_F20 ) , S( KC_F21 ) , S( KC_F22 ) , S( KC_F23 ) , S( KC_F24 ) , 
    A(S( KC_F13 )) , A(S( KC_F14 )) , A(S( KC_F15 )) , A(S( KC_F16 )) , A(S( KC_F17 )) ,  A(S( KC_F18 )) , A(S( KC_F19 )) , A(S( KC_F20 )) , A(S( KC_F21 )) , A(S( KC_F22 )) , A(S( KC_F23 )) , A(S( KC_F24 )) , 
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______
),
/* BLANK
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
[_BLANK] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______
),
 */

/* <# Navi #>
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |      |      |ALTTAB|      |      |      |      | S-TAB| TAB  |      |      |     
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| Alt  | Ctrl | GUI  | **** |      |      |  ←   |   ↓  |  ↑   |  →   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | HOME | Pg↓  | Pg↑  | END  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVI] = LAYOUT_planck_grid(
    KC_ESC  , _______ , _______ , ALT_TAB , _______ , _______ , _______ , S(KC_TAB) , KC_TAB  , _______ ,_______ , _______ ,
    KC_LSFT , KC_LALT , KC_LCTL , KC_LGUI , _______ , _______ , KC_LEFT , KC_DOWN , KC_UP     , KC_RGHT , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ , KC_HOME , KC_PGDN   , KC_PGUP , KC_END  , _______ , _______ ,
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______   , _______ , _______ , _______
),

/* <# Raise #>                    
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  <-  |  ->  |  .>  |  |>  |      |      |   -  |   =  |   <  |   >  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | <$>  |  <*> |  <>  |  >>= |      |      |ISO # |ISO / |      |   ?  |  ~   | // REPLACE F12 With a layer for F-keys 
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play | 
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_ESC  , KC_1     , KC_2     , KC_3         , KC_4        , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , MAC_BACKTICK ,
    KC_DEL  , SYM_RARR , SYM_LARR , SYM_COMP_ARR , SYM_APP_ARR , _______ , _______ , FI_MINS , FI_EQL  , MAC_LT  , MAC_GT  , FI_QUOT      ,
    _______ , SYM_FMAP , SYM_FAP  , SYM_MAPPEND  , SYM_BIND    , _______ , _______ , KC_NUHS , KC_NUBS , _______ , S(45)   , FI_TILD      ,
    _______ , _______  , _______  , _______      , _______     , _______ , _______ , _______ , KC_MNXT , KC_VOLD , KC_VOLU , KC_MPLY
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK,  _______,  PLOVER,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
// <# PROCESS RECORD MACROS #>
#define SIMPLE(KC,SS) case KC :  if(record->event.pressed) { SEND_STRING(SS); } break;
#define SURROUND(KC,LEFT,RIGHT) case KC :  if(record->event.pressed) {tap_code16(LEFT);tap_code16(RIGHT);tap_code(KC_LEFT);} break;

// <# PROCESS RECORD #>
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t ale_colon_timer;
  static uint16_t space_timer;
  static uint16_t held_char=0;
  static bool alt_tab_alt=false;

  // If last press was ALT_TAB, and this one isn't, release the left alt
  if (record->event.pressed && keycode != ALT_TAB && alt_tab_alt) {
      unregister_code(KC_LGUI); // But, it is gui tab on my mac
      alt_tab_alt = false;
      // Ignore the next key
      return false;
  }
  else  if (alt_tab_alt && keycode != ALT_TAB) {
      // released something other than alt_tab → release alt & keep going
      unregister_code(KC_LGUI); // But, it is gui tab on my mac
      alt_tab_alt = false;
  }

  if (record->event.pressed && held_char != 0) {
      tap_code(held_char);
      held_char = 0;
  }
  switch (keycode) {
    case QUESTION_HOLD:
             if(record->event.pressed) {
                         ale_colon_timer = timer_read();
                         held_char = KC_DOT;
                        } 
             else {
                    if (timer_elapsed(ale_colon_timer) > TAPPING_TERM) {
                       register_code(KC_LSFT); tap_code(45); unregister_code(KC_LSFT);
                       }
                    else {tap_code(KC_DOT);}
                    held_char = 0;
                    }
             return false;
    case ODIA_HOLD:
             if(record->event.pressed) {
                         ale_colon_timer = timer_read();
                         held_char = KC_O;
                        } 
             else {
                    if (timer_elapsed(ale_colon_timer) > TAPPING_TERM) {
                       tap_code(FI_ODIA); 
                       }
                    else {tap_code(KC_O);}
                    held_char = 0;
                    }
             return false;
    case ADIA_HOLD:
             // BUG: This reverses order of the keypresses if they occur during
             // the tapping term.
             if(record->event.pressed) {
                         ale_colon_timer = timer_read();
                         held_char = KC_A;
                        } 
             else {
                    if (timer_elapsed(ale_colon_timer) > TAPPING_TERM) {
                       tap_code(FI_ADIA); 
                       }
                    else {tap_code(KC_A);}
                    held_char = 0;
                    }
             return false;
    case ALT_TAB:
             if(record->event.pressed) {
                if (!alt_tab_alt) {
                    // first press, start holding alt.
                    register_code(KC_LGUI);
                    alt_tab_alt = true;
                } 
                // on all presses, tab alt. 
                tap_code(KC_TAB);
             }
            break;
    case KC_SPC_TAB:
             if(record->event.pressed) {
                         space_timer = timer_read();
                        } 
             else {
                    if (timer_elapsed(space_timer) > TAPPING_TERM) {
                       tap_code(KC_DOT);tap_code(KC_SPC);
                       }
                    else {
                        tap_code(KC_SPC);
                        }
                    }
             return false;
    case MAC_BACKTICK: 
             if(record->event.pressed) {
                register_code(KC_LSFT);tap_code(46);unregister_code(KC_LSFT);tap_code(44);
             }
             return false;
    case ALE_COLON:
             if(record->event.pressed) {
                         ale_colon_timer = timer_read();
                         register_code(KC_RCTL); // Change the key to be held here
                        } 
             else {
                    unregister_code(KC_RCTL); // Change the key that was held here, too!
                    if (timer_elapsed(ale_colon_timer) < TAPPING_TERM) {
                       tap_code(KC_ESC);
                       SEND_STRING(">w"); // Change the character(s) to be sent on tap here
                       tap_code(KC_ENTER);
                       }
                    }
             return false;

  SIMPLE(HS_IMPORT,"import ")
  SIMPLE(HS_DERIVING,"deriving ")
  SIMPLE(HS_MONOID,"Monoid")
  SIMPLE(HS_QUALIFIED,"qualified ")
  SIMPLE(HS_WHERE,"where")
  SIMPLE(HS_LET,"let")
  SIMPLE(HS_RETURN,"return")
  SIMPLE(HS_EITHER,"Either")
  SIMPLE(HS_TYPE,"type")
  case HS_LANGUAGE:
             if(record->event.pressed) {
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
             } 
             break;
  SIMPLE(HS_INSTANCE,"instance")
  SIMPLE(HS_DATA,"Data.")
  SIMPLE(HS_PURE,"pure")
  SIMPLE(HS_MEMPTY,"mempty")
  SIMPLE(HS_TEXT,"Text")
  case SYM_LAMBDA:
             if(record->event.pressed) {
                        tap_code16(MAC_BACKSLASH);
                        tap_code(KC_SPC);
                        tap_code(FI_MINS);
                        tap_code16(MAC_GT);
                        tap_code(KC_LEFT);
                        tap_code(KC_LEFT);
                        tap_code(KC_LEFT);
             } 
             break;
  case HS_CASE:
             if(record->event.pressed) {
                        SEND_STRING("case  of");
                        tap_code(KC_LEFT);
                        tap_code(KC_LEFT);
                        tap_code(KC_LEFT);
             } 
             break;
 SIMPLE(HS_JUST,"Just")
 SIMPLE(HS_NOTHING,"Nothing")
 SIMPLE(HS_MAYBE,"Maybe")
 SIMPLE(HS_LEFT,"Left")
 SIMPLE(HS_RIGHT,"Right")
 SIMPLE(SYM_LARR, (SS_TAP(38)SS_DOWN(e5)SS_TAP(35)SS_UP(e5)))//"->")
 SIMPLE(SYM_LFATARR, SS_DOWN(e5)SS_TAP(27)SS_TAP(35)SS_UP(e5))//"=>")
 SIMPLE(SYM_RARR,SS_TAP(35)SS_TAP(56)) //"<-")
 SIMPLE(SYM_COMP_ARR,SS_TAP(37)SS_DOWN(e5)SS_TAP(35)SS_UP(e5))//".>")
 SIMPLE(SYM_APP_ARR, SS_DOWN(e6)SS_TAP(24)SS_UP(e6)SS_DOWN(e5)SS_TAP(35)SS_UP(e5))//"|>"
 SIMPLE(SYM_BIND, SS_DOWN(e5)SS_TAP(35)SS_TAP(35)SS_TAP(27)SS_UP(e5))//">>=")
 SIMPLE(SYM_FMAP, SS_TAP(35)SS_DOWN(e6)SS_TAP(21)SS_UP(e6)SS_DOWN(e5)SS_TAP(35)SS_UP(e5))// "<$>"
 SIMPLE(SYM_FAP, SS_TAP(35)SS_DOWN(e5)SS_TAP(31)SS_TAP(35)SS_UP(e5))// "<*>"
 SIMPLE(SYM_MAPPEND, SS_TAP(35)SS_DOWN(e5)SS_TAP(35)SS_UP(e5))// "<>"
 SIMPLE(SYM_TYPE, SS_DOWN(e5)SS_TAP(37)SS_TAP(37)SS_UP(e5))// "::"
 SIMPLE(SYM_EQ, SS_DOWN(e5)SS_TAP(27)SS_TAP(27)SS_UP(e5))// "=="
 SIMPLE(SYM_NEQ, SS_DOWN(e5)SS_TAP(24)SS_TAP(27)SS_UP(e5))// "/="
 SIMPLE(SYM_HOMEDIR, SS_DOWN(e6)SS_TAP(30)SS_UP(e6)SS_TAP(2c)SS_DOWN(e5)SS_TAP(24)SS_UP(e5))// "~/"
 SIMPLE(SYM_EXECHERE, SS_TAP(2c)SS_DOWN(e5)SS_TAP(24)SS_UP(e5))// "./"

 SURROUND(PAR_PARENS,FI_LPRN,FI_RPRN) // ()←
 SURROUND(PAR_SQUARE,MAC_SQLBR,MAC_SQRBR) // []←
 SURROUND(PAR_BRACKET,MAC_LBR,MAC_RBR) // {}←
 SURROUND(PAR_ANGLE,MAC_LT,MAC_GT) // {}←

 SURROUND(PAR_QUOT,FI_QUOT,FI_QUOT) // ''←
 SURROUND(PAR_DQUOT,S(KC_2),S(KC_2)) // ""←
    case PAR_BACKTICK:
             if(record->event.pressed) {
                 register_code(KC_LSFT);tap_code(46);unregister_code(KC_LSFT);tap_code(44);
                 register_code(KC_LSFT);tap_code(46);unregister_code(KC_LSFT);tap_code(44);
                 tap_code(KC_LEFT);
             }
             return false;
    break;
  SIMPLE(ZETTEL_WIKI,",zw")
  SIMPLE(ZETTEL_EXT,",ze")
  SIMPLE(ZETTEL_RESOLVE,",zr")
  SIMPLE(ZETTEL_THREAD,",zt")
  SIMPLE(ZETTEL_TEMPORAL,",zT")
  SIMPLE(ZETTEL_SPLIT,",zs")
  SIMPLE(ZETTEL_FIND,",zf")
  SIMPLE(ZETTEL_RECENT,",zr")
  SIMPLE(ZETTEL_LINK,",zl")
  SIMPLE(ZETTEL_CREATE,":Zcre "SS_TAP(49)SS_TAP(49)SS_TAP(X_LEFT))
  SIMPLE(ZETTEL_BACKLINKS,",zb")
  SIMPLE(ZETTEL_NEIGHBOURS,",zn")

    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
   // case DVORAK:
   //   if (record->event.pressed) {
   //     set_single_persistent_default_layer(_DVORAK);
   //   }
   //   return false;
   //   break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // Your code goes here. data is the packet received from host.
    static uint8_t outbound[RAW_EPSIZE] = {0};
    for (int i=0; i<length && i<RAW_EPSIZE; i++)
        outbound[i] = data[i];
    PLAY_SONG(plover_gb_song); 
    raw_hid_send(outbound, length);
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

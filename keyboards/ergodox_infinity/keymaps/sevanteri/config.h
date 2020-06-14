#pragma once

#include "../../config.h"

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define TAPPING_FORCE_HOLD

#ifdef PERMISSIVE_HOLD
#undef PERMISSIVE_HOLD
#endif
#define PERMISSIVE_HOLD_PER_KEY

#ifdef IGNORE_MOD_TAP_INTERRUPT
#undef IGNORE_MOD_TAP_INTERRUPT
#endif
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT

#define COMBO_TERM 35
#define COMBO_MOD_TERM 200
#define COMBO_VARIABLE_LEN
#define COMBO_MUST_HOLD_MODS
#define COMBO_PERMISSIVE_HOLD
/* #define COMBO_TERM_PER_COMBO */
#define COMBO_MUST_HOLD_PER_COMBO

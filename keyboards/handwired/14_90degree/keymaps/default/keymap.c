// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "quantum.h"

#define _Alpha1 0
#define _Alpha2 1
#define _Alpha2U 2
#define _Symbol1 3
#define _Symbol2 4
#define _NumPad 5
#define _System 6
#define _Macro 7

#define SYM2(kc) LT(_Symbol2, kc)
#define SYM1(kc) LT(_Symbol1, kc)
#define SYS(kc) LT(_System, kc)
#define NUM(kc) LT(_NumPad, kc)
#define MAC(kc) LT(_Macro, kc)

#define NONE XXXXXXX

enum {
  FAT_ARROW = SAFE_RANGE,
  SKINNY_ARROW,
  REVERSE_SKINNY_ARROW,
  HASKELL_BIND,
  HASKELL_FMAP,
  HASKELL_AP,
  HOME_DIR,
  VIM_DOWN,
  VIM_UP,
  VIM_SPLIT_VERTICAL,
  VIM_SPLIT_HORIZONTAL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [_Alpha1] = LAYOUT_split_2x3_2(
        NUM(KC_C),  KC_L,       MAC(KC_D),                                  MAC(KC_H), KC_O, NUM(KC_R),
        SYM2(KC_S), SYM1(KC_N), SYS(KC_T), OSL(_Alpha2),   MEH_T(KC_SPACE), SYS(KC_E), SYM1(KC_A), SYM2(KC_I)
    ),

    [_Alpha2] = LAYOUT_split_2x3_2(
        KC_K, KC_V, KC_B,               KC_F, KC_G, KC_U,
        NONE, KC_P, KC_Y, NONE,   NONE, KC_M, KC_J, KC_W
    ),

    [_Symbol1] = LAYOUT_split_2x3_2(
        KC_QUESTION, KC_LCBR, KC_RCBR,                 KC_AMPERSAND, KC_EXCLAIM, KC_PIPE,
        KC_SLASH,    KC_LPRN, KC_RPRN, NONE,     NONE, KC_EQUAL,     KC_MINUS,   KC_SEMICOLON
    ),

    [_Symbol2] = LAYOUT_split_2x3_2(
         KC_AT,        KC_LBRC, KC_RBRC,                KC_CIRCUMFLEX, KC_DOLLAR, KC_PERCENT,
          KC_BACKSLASH, KC_LABK, KC_RABK, NONE,   NONE, KC_MINUS,      KC_UNDS,   KC_COLON
    ),

    [_NumPad] = LAYOUT_split_2x3_2(
        KC_PLUS,     KC_0, KC_1,              KC_2, KC_3, KC_4,
        KC_ASTERISK, KC_5, KC_6, NONE,  NONE, KC_7, KC_8, KC_9
    ),

    [_System] = LAYOUT_split_2x3_2(
         KC_TAB,  KC_UP,   KC_CAPS_LOCK,            OSM(MOD_LGUI), OSM(MOD_LCTL), OSM(MOD_LALT),
         KC_LEFT, KC_DOWN, KC_RIGHT, NONE,    NONE, KC_ESC,        KC_BACKSPACE,  KC_ENTER
    ),

    [_Macro] = LAYOUT_split_2x3_2(
        NONE, NONE, NONE,                NONE, NONE, NONE,
        NONE, NONE, NONE, NONE,    NONE, FAT_ARROW, SKINNY_ARROW, NONE
    )
};


bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_BACKSPACE):
        case RSFT_T(KC_E):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode){
    case FAT_ARROW:
      if (record->event.pressed){
        SEND_STRING("=>");
      }
      break;
      case HOME_DIR:
        if (record->event.pressed){
        SEND_STRING("~/");
      }
      break;
      case SKINNY_ARROW:
        if (record->event.pressed){
          SEND_STRING("->");
        }
        break;
      case REVERSE_SKINNY_ARROW:
        if (record->event.pressed){
          SEND_STRING("<-");
        }
        break;
      case HASKELL_FMAP:
        if (record->event.pressed){
          SEND_STRING("<$>");
        }
        break;
      case HASKELL_AP:
        if (record->event.pressed){
          SEND_STRING("<*>");
        }
        break;
      case HASKELL_BIND:
        if (record->event.pressed){
          SEND_STRING(">>=");
        }
        break;
      case VIM_UP:
        if (record->event.pressed){
          SEND_STRING(SS_LCTL("u"));
        }
        break;
      case VIM_DOWN:
        if(record->event.pressed){
          SEND_STRING(SS_LCTL("d"));
        }
        break;
      case VIM_SPLIT_HORIZONTAL:
        if (record->event.pressed){
          SEND_STRING(SS_LCTL("w"));
          SEND_STRING("s");
        }
        break;
      case VIM_SPLIT_VERTICAL:
        if (record->event.pressed){
          SEND_STRING(SS_LCTL("w"));
          SEND_STRING("v");
        }
        break;
  }
  return true;
}

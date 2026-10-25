// Copyright 2026 Sumio Koseki (JA7RHK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "nicola.h" // NICOLA親指シフト
#include "keymap_japanese.h"
#include "twpair_on_jis.h" // us -> jis変換
#include <timer.h>

// IMEを監視する"observe_ime"を使用する場合、Num Lockでnicola on/offする。
// キーボード単体でnicola on/offを制御する場合はコメントアウトする。
#define USE_OBSERVE_IME

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum keymap_layers {
    _QWERTY = 0,
    // NICOLA親指シフト入力レイヤー
    _NICOLA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*

           ,-------------------. ,-------------------. ,-------------------.
           | F13| F14| F15| F16| | F17| F18| F19| F20| | F21| F22| F23| F24|
   ,---.   |-------------------| |-------------------| |-------------------|  ,--------------.
   | Esc|  |  F1|  F2|  F3|  F4| |  F5|  F6|  F7|  F8| |  F9| F10| F11| F12|  | PS | SL | PA |
   `----'  `-------------------' '-------------------' `-------------------'  `--------------'
   ,----------------------------------------------------+-------------------. ,--------------. ,-------------------.
   |  `~|  1!|  2@|  3#|  4$|  5%|  6^|  7&|  8*|  9(|  0)|  -_|  =+|  Bspc | | In | Hm | PU | |  Nl|  P/|  P*|  P-|
   |------+----+----+----+----+----+----+----+----+----+----+----+----+-----| |----+----+----| |----+----+----+----|
   |   Tab| Q  |  W |  E |  R  |  T |  Y |  U |  I |  O |  P |  [{|  ]}| \| | | Dl | Ed | PD | |  P7|  P8|  P9|    |
   |--------+----+----+----+----+----+----+----+----+----+----+----+--------| `--------------' |----+----+----+  P+|
   |   CAP  |  A |  S |  D |  F |  G |  H |  J |  K |  L |  ;: |  '"| Enter |                  |  P4|  P5|  P6|    |
   |----------+----+----+----+----+----+----+----+----+----+----+-----------|      ,----.      |----+----+----+----|
   |    LSH   |  Z |  X  |  C |  V |  B |  N |  M | ,< |  .>|  /? |   RSH   |      | Up |      |  P1|  P2|  P3|    |
   |-----+-----+-----+------------------------------+-----+-----+-----+-----| ,----+----+----. +---------+----+  PE|
   | LC  | LG  | LA  |                              | RA  | RG  | WIN | RC  | | Lf | Dn |  Rt| |    P0   |  P.|    |
   `------------------------------------------------------------------------' `--------------' `-------------------'

   */

    // QMK converter の場合は入力するHIDに依存するので、Mo()キーやFnキーは存在しない

    [_QWERTY] = LAYOUT_68_ansi(
                          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,

        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                                   KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT
    ),

    [_NICOLA] = LAYOUT_68_ansi(
                          KC_F13, NG_SHFTL, KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,

        KC_GRV,  NG_1,    NG_2,    NG_3,    NG_4,    NG_5,    NG_6,    NG_7,    NG_8,    NG_9,    NG_0,    NG_MINS, NG_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,    KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,    NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,    NG_LBRC, NG_RBRC, NG_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS, NG_A,    NG_S,    NG_D,    NG_F,    NG_G,    NG_H,    NG_J,    NG_K,    NG_L,    NG_SCLN, KC_BSPC,          KC_ENT,                                   KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,          NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,    NG_N,    NG_M,    NG_COMM, NG_DOT,  NG_SLSH,          KC_RSFT,             KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LGUI, KC_LALT,                            NG_SHFTR,                           KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT
    )
};


void matrix_init_user(void) {
    // NICOLA親指シフト
    set_nicola(_NICOLA);
    // NICOLA親指シフト
}

void keyboard_post_init_user(void) {
    gpio_set_pin_output(RED_LED);
    gpio_write_pin_low(RED_LED);

    gpio_set_pin_output(_5V_EN);
    gpio_write_pin_high(_5V_EN);

    nicola_off();
}


static bool is_capslock = false;    // CapsLockがオンかオフか
#ifdef USE_OBSERVE_IME
static bool is_numlock = false;     // NumLockがオンかオフか
// This functions will be called when one of those 5 LEDs changes state.
// Num Lock, Caps Lock, Scroll Lock, Compose, Kan
bool led_update_kb(led_t led_state) {

    bool res = led_update_user(led_state);
    if(res) {
        if (led_state.num_lock != is_numlock) {
            if (led_state.num_lock)
                nicola_on();
            else
                nicola_off();
            is_numlock = led_state.num_lock;
        }
        is_capslock = led_state.caps_lock;
    }
    return res;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        // 英数キー(Caps Lock)で nicola mode オフ
        case KC_LNG2:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG2));
                //send_string(SS_LSFT(SS_TAP(X_CAPS_LOCK)));
            #ifndef USE_OBSERVE_IME
                nicola_off();
            #endif
            }
            return false;
        // 英数モードのとき左親指キーで nicola mode オン
        case KC_LNG1:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG1));
                //send_string(SS_TAP(X_F14));
            #ifndef USE_OBSERVE_IME
                nicola_on();
            #endif
            }
            return false;
    }

    // NICOLA親指シフト
    bool a = true;
    if (nicola_state()) {
        nicola_mode(keycode, record);
        a = process_nicola(keycode, record);
    }
    if (a == false) return false;

    // ANSI配列の記号キーをJIS配列に変換
    // _NICOLAレイヤーの場合は変換しない
    bool b = true;
    if (get_highest_layer(layer_state) != _NICOLA) {
        b = twpair_on_jis(keycode, record);
    }
    if (b == false) return false;

    return true;
}

// This function gets called at every matrix scan.
void matrix_scan_user(void) {

	uint32_t now = timer_read32();
	timer_tick(now);	// drive nicola state-machine.
}


void suspend_power_down_user(void) {
    // スリープに入ったときの処理（LEDの完全消灯など）
    gpio_write_pin_low(_5V_EN);
    gpio_write_pin_low(RED_LED);
}

void suspend_wakeup_init_user(void) {
    // スリープから復帰したときの処理
    gpio_write_pin_high(_5V_EN);

	if (nicola_state())
	    gpio_write_pin_high(RED_LED);
	else
	    gpio_write_pin_low(RED_LED);
}

// NeoPixcelはPICO-PIO-USBドライバと競合するので使えない


// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later
// 西巻裕改造@2024
//^Mがほぼ完全に動くようになったバージョン10be7391e7 西巻GK61_Ver4.M

#include QMK_KEYBOARD_H
#include "nicola.h" // NICOLA親指シフト
#include <timer.h>
#include "rgb_config.h" // RGB LEDの定義

// Ctrl編集モードフラグ（グローバル）
static bool ctrl_edit_mode = true;

// 各レイヤー名
enum keymap_layers {
    _QWERTY = 0,
    _NICOLA,
    _FUNC
};

// カスタムキーコード
enum custom_keycodes {
    MY_M = NG_BOTTOM + 1,  // NG_* 系の最後に +1
    CTRL_TOGGLE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_all(
        KC_ESC,    KC_1,   KC_2,    KC_3,     KC_4,     KC_5,      KC_6,     KC_7,    KC_8,    KC_9,      KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,    KC_Q,   KC_W,   KC_E,     KC_R,     KC_T,    KC_Y,     KC_U,    KC_I,     KC_O,      KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_LCTL,   KC_A,   KC_S,    KC_D,     KC_F,     KC_G,    KC_H,     KC_J,    KC_K,    KC_L,      KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,   KC_Z,   KC_X,    KC_C,     KC_V,     KC_B,     KC_N,     MY_M,    KC_COMM,  KC_DOT,       KC_SLSH,    KC_UP,
        KC_PSCR,  KC_LALT, KC_LGUI,      KC_SPC,  _______,KC_F14,   MO(_FUNC), KC_LEFT,  KC_DOWN,            KC_RIGHT
    ),

    [_NICOLA] = LAYOUT_all(
        KC_ESC,    NG_1,   NG_2,   NG_3,   NG_4,   NG_5,      NG_6,     NG_7,     NG_8,     NG_9,      NG_0,     NG_MINS,  NG_EQL,   KC_BSPC,
        KC_TAB,    NG_Q,   NG_W,  NG_E,   NG_R,   NG_T,      NG_Y,     NG_U,     NG_I,     NG_O,      NG_P,     NG_LBRC,  NG_RBRC,  NG_BSLS,
        KC_LCTL,  NG_A,   NG_S,   NG_D,   NG_F,   NG_G,      NG_H,     NG_J,     NG_K,     NG_L,      NG_SCLN,  NG_QUOT,            KC_ENT,
        KC_LSFT,   NG_Z,   NG_X,   NG_C,   NG_V,   NG_B,      NG_N,     MY_M,     NG_COMM,  NG_DOT,    NG_SLSH,            KC_UP,
        KC_PSCR,  KC_LALT,  KC_LGUI,    NG_SHFTL,  _______,       NG_SHFTR, MO(_FUNC), KC_LEFT,  KC_DOWN,            KC_RIGHT
    ),

    [_FUNC] = LAYOUT_all(
        KC_GRV,  KC_F1,  KC_F2,    KC_F3,    KC_F4,     KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,     KC_F10,   KC_F11,   KC_F12,   KC_DEL,
        _______,  QK_RGB_MATRIX_TOGGLE, _______, KC_UP, _______,  _______,  _______, KC_PSCR, _______, _______,  _______, _______, _______, _______,
        KC_LCTL, _______,  KC_LEFT,  KC_RIGHT,  _______,   _______,   _______,  _______,  KC_HOME,  KC_END,   _______,  _______,            _______,
        _______,      _______,  KC_DOWN,  _______,  _______,   _______,   _______,  _______,  KC_PGUP,  KC_PGDN,   _______,     KC_RSFT,    
        KC_PSCR,      _______,  _______,     KC_DEL,    _______,       KC_ESC,   _______,   KC_LNG1,  KC_CAPS_LOCK,             CTRL_TOGGLE
    )
};

// -------------------- 初期化 --------------------
void matrix_init_user(void) {
    set_nicola(_NICOLA); // NICOLA親指シフト初期化
}

void keyboard_post_init_user(void) {
    nicola_off();
}

#ifdef USE_OBSERVE_IME
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        if (led_state.num_lock)
            nicola_on();
        else
            nicola_off();
    }
    return res;
}
#endif

// -------------------- キー入力処理 --------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    uint8_t mods = get_mods();
    bool ctrl = mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL));

    // ----------------- switch 文開始 -----------------
    switch (keycode) {

        // Ctrlモードトグルスイッチ
        case CTRL_TOGGLE:
            if (record->event.pressed) {
                ctrl_edit_mode = !ctrl_edit_mode;
            }
            return false;

        // 英数キー
        case KC_PSCR:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG2));
#ifndef USE_OBSERVE_IME
                nicola_off();
#endif
            }
            return false;

        // NICOLAモード切替
        case KC_F14:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG1));
#ifndef USE_OBSERVE_IME
                nicola_on();
#endif
            }
            return false;

        // MY_M（親指シフト含む Ctrl+M）
        case MY_M: {
            bool is_nicola = nicola_state();
            bool shift = mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

            if (record->event.pressed) {
                if (ctrl && ctrl_edit_mode) {
                    unregister_mods(mods);
                    tap_code(KC_ENT);
                    register_mods(mods);
                    return false;
                }
                if (!is_nicola || shift) {
                    tap_code(KC_M);
                    return false;
                }
            }

            if (is_nicola) {
                process_nicola(NG_M, record);
            }
            return false;
        }

        // Ctrl編集モード ON のときのみ特殊キー横取り
        case KC_H: case NG_H:
        case KC_G: case NG_G:
        case KC_E: case NG_E:
        case KC_S: case NG_S:
        case KC_D: case NG_D:
        case KC_X: case NG_X:
        case KC_I: case NG_I:
            if (record->event.pressed && ctrl && ctrl_edit_mode) {
                unregister_mods(mods);
                switch (keycode) {
                    case KC_H: case NG_H: tap_code(KC_BSPC); break;
                    case KC_G: case NG_G: tap_code(KC_DEL); break;
                    case KC_E: case NG_E: tap_code(KC_UP); break;
                    case KC_S: case NG_S: tap_code(KC_LEFT); break;
                    case KC_D: case NG_D: tap_code(KC_RIGHT); break;
                    case KC_X: case NG_X: tap_code(KC_DOWN); break;
                    case KC_I: case NG_I: tap_code(KC_TAB); break;
                }
                register_mods(mods);
                return false;
            }
            break;

        // ここに他のキー追加可能
    }

    // ----------------- 親指シフト処理 -----------------
    bool a = true;
    if (nicola_state()) {
        nicola_mode(keycode, record);
        a = process_nicola(keycode, record);
    }

    if (!a) return false;
    return true;
}

// -------------------- NICOLA状態マシン駆動 --------------------
void matrix_scan_user(void) {
    uint32_t now = timer_read32();
    timer_tick(now);
}

    // -------------------- RGB LEDインジケータ --------------------
    
    bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
                                                                                for (uint8_t i = led_min; i < led_max; i++)
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        
        // 255.255.255：白
        // 255.255.0：黄
        // 255.0.0：赤
        // 0.255.0：緑
        // 0.255.255：水色
        // 255.0.255：ピンク
        // 0, 0, 255   : 青
        
        switch (get_highest_layer(layer_state)) {
          case _QWERTY:
//        RGB_MATRIX_INDICATOR_SET_COLOR(0, 255, 0, 255); // ピンクのエスケープ
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_CENTER_INDEX, 0, 255, 0); // 
            break;
          case _NICOLA:
//         RGB_MATRIX_INDICATOR_SET_COLOR(OYA_LEFT_INDEX, 0, 0, 255);
            RGB_MATRIX_INDICATOR_SET_COLOR(56, 0, 0, 255);
//         RGB_MATRIX_INDICATOR_SET_COLOR(OYA_RIGHT_INDEX, 0, 0, 255);
            break;
          case _FUNC:
//         RGB_MATRIX_INDICATOR_SET_COLOR(OYA_LEFT_INDEX, 255, 0, 0); // 赤
//         RGB_MATRIX_INDICATOR_SET_COLOR(FN_BS_INDEX, 255, 0, 0);  // 赤
           RGB_MATRIX_INDICATOR_SET_COLOR(56, 255, 0, 0);
//        RGB_MATRIX_INDICATOR_SET_COLOR(FN_PS_INDEX, 0, 0, 255); // 青
//        RGB_MATRIX_INDICATOR_SET_COLOR(FN_HOME_INDEX, 0, 0, 255); // 青
//        RGB_MATRIX_INDICATOR_SET_COLOR(FN_PU_INDEX, 0, 0, 255); // 青
//        RGB_MATRIX_INDICATOR_SET_COLOR(FN_PD_INDEX, 0, 0, 255); // 青
//         RGB_MATRIX_INDICATOR_SET_COLOR(FN_UP_INDEX, 255, 255, 0); // 黄（実は緑）
//         RGB_MATRIX_INDICATOR_SET_COLOR(FN_LEFT_INDEX, 255, 0, 0);// 赤
//         RGB_MATRIX_INDICATOR_SET_COLOR(FN_DOWN_INDEX, 255, 0, 0);// 赤
//         RGB_MATRIX_INDICATOR_SET_COLOR(FN_RIGHT_INDEX, 255, 0, 0);// 赤
            break;
        }
        
        if (ctrl_edit_mode) {
//         RGB_MATRIX_INDICATOR_SET_COLOR(27, 255, 0, 255); // ピンク
//         RGB_MATRIX_INDICATOR_SET_COLOR(17, 0, 0, 255); // 青
//         RGB_MATRIX_INDICATOR_SET_COLOR(30, 0, 0, 255); // 青
//         RGB_MATRIX_INDICATOR_SET_COLOR(31, 0, 0, 255); // 青
//         RGB_MATRIX_INDICATOR_SET_COLOR(43, 0, 0, 255); // 青
//         RGB_MATRIX_INDICATOR_SET_COLOR(FN_LEFT_INDEX, 0, 255, 0);
//         RGB_MATRIX_INDICATOR_SET_COLOR(FN_DOWN_INDEX, 0, 255, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_RIGHT_INDEX, 255, 0, 255);
        }
        
        return false;
    }
// Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later
// T@2024x[X͏ւ񂌍

#include QMK_KEYBOARD_H

#include "nicola.h" // NICOLAewVtg
#include <timer.h>
#include "rgb_config.h" // RGB LED̒苠

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum keymap_layers {
    _QWERTY = 0,
// NICOLAewVtg̓C[
    _NICOLA,
// FUNCTION
    _FUNC
//    _FUNC,
// CONTROL
//    _LCTL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*    
     * 
     * Esc   1   2   3   4   5   6   7   8   9   0   -   =    Bsp    
     * 
     *  Tab      Q   W   E   R   T   Y   U   I   O   P   [   ]    \  
     * 
     *   Ctl       A   S   D   F   G   H   J   K   L   ;   '    Ent    
     * 
     *   Sft         Z   X   C   V   B   N   M   ,   .   /             
     * 
     *   CaL   GUI   Alt        Spc            Spc      Fun            
     * 
     *  Capslock͎g\邌ō￠���Eɂ񂾂ǁAB񌳂ɖ߂
     */


// 낢돑Ă܂B̂ŁAsȐꍇ̓IWi￹���Ƃ邱ƍ
// GK61 Prox[XȂ̂ŁAẼXy[X̊Ԃɂ¤ꂂ@\蓖Ă鍊
    [_QWERTY] = LAYOUT_all(
        KC_ESC,    KC_1,    KC_2,    KC_3,   KC_4,    KC_5,   KC_6,      KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC,
        KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,   KC_Y,      KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_LCTL,   KC_A,    KC_S,    KC_D,   KC_F,    KC_G,   KC_H,      KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,            KC_ENT,
//      MO(_LCTL),
        KC_LSFT,   KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,   KC_N,      KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,
     KC_CAPS_LOCK, KC_LALT, KC_LGUI, KC_SPC, _______, KC_F14, MO(_FUNC), KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    [_NICOLA] = LAYOUT_all(
        KC_ESC,    NG_1,    NG_2,    NG_3,    NG_4,   NG_5,    NG_6,     NG_7,    NG_8,    NG_9,     NG_0,    NG_MINS, NG_EQL,   KC_BSPC,
        KC_TAB,    NG_Q,    NG_W,    NG_E,    NG_R,   NG_T,    NG_Y,     NG_U,    NG_I,    NG_O,     NG_P,    NG_LBRC, NG_RBRC,  NG_BSLS,
        KC_LCTL,   NG_A,    NG_S,    NG_D,    NG_F,   NG_G,    NG_H,     NG_J,    NG_K,    NG_L,     NG_SCLN, NG_QUOT,           KC_ENT,  // obNXy[X￸���QUOTɂ
        KC_LSFT,   NG_Z,    NG_X,    NG_C,    NG_V,   NG_B,    NG_N,     NG_M,    NG_COMM, NG_DOT,   NG_SLSH, KC_UP,
     KC_CAPS_LOCK, KC_LALT, KC_LGUI, NG_SHFTL,_______,NG_SHFTR,MO(_FUNC),KC_LEFT, KC_DOWN, KC_RSFT
    ),

    [_FUNC] = LAYOUT_all(
        KC_GRV,    KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,   KC_F6,    KC_F7,    KC_F8,  KC_F9,    KC_F10,  KC_F11,   KC_F12,   KC_DEL,
        _______,   RGB_TOG, _______, _______, _______,_______, _______,  KC_PSCR,  _______,_______,  _______, _______,  _______,  _______,
        _______,   _______, _______, _______, _______,_______, _______,  _______,  _______,KC_PGUP,  _______, _______,  _______,
        _______,   _______, _______, _______, _______,_______, _______,  _______,  _______,KC_PGDN,  _______, KC_RSFT,
     KC_CAPS_LOCK, _______, _______,          KC_DEL, _______,           KC_RALT,  _______,KC_F15,   KC_APP,  KC_RCTL
//   ),
//   Rg[L[ł̃L[산L[{[hxŎ悤ƂĎs₂FL[w興OAt@xbg͂ɂȂBĂ܂B
//    [_LCTL] = LAYOUT_all(
//        _______,     _______,  _______,  _______,  _______,   _______,   _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,
//        _______,     _______,  _______,  KC_UP,    _______,   _______,   _______,  _______,  KC_TAB,  _______,   _______,  _______,  _______,  _______,
//        _______,     _______,  KC_LEFT, KC_RIGHT,  _______,   _______,   KC_BSPC,  _______,  _______,  _______,   _______,  _______,  _______,
//        _______,     _______,  KC_DOWN,  _______,  _______,   _______,   _______,  KC_ENT,  _______,  _______,   _______,  _______,
//        _______,     _______,  _______,            _______,    _______,             _______,  _______,  _______,    _______,   _______
   )

};

// Fn+QFƖ̏NOFFEFn+CapslockFCapslock

void matrix_init_user(void) {
    // NICOLAewVtg
    set_nicola(_NICOLA);
    // NICOLAewVtg
}

// ɞM[h𓼂ꂪ΂̂ȁH

// Initialize the 13th LED
void keyboard_post_init_user(void) {
    nicola_off();
}

// This functions will be called when one of those 5 LEDs changes state.
// Num Lock, Caps Lock, Scroll Lock, Compose, Kan
#ifdef USE_OBSERVE_IME // ꂪRgAEgɂȂBĂȂB̂ŃRgAEg
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    //    CTRL動作

// ================================
// Ctrl + M/H/D の特別動作 ChatGPTに作ってもらった
// ================================
if (record->event.pressed) {

    // 左右どちらの Ctrl でも OK
    uint8_t mods = get_mods() | get_weak_mods() | get_oneshot_mods();
    bool ctrl = mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL));

    if (ctrl) {

        // Ctrl + M → Enter
        if (keycode == KC_M) {
            tap_code(KC_ENTER);
            return false;
        }

        // Ctrl + H → Backspace
        if (keycode == KC_H) {
            tap_code(KC_BSPC);
            return false;
        }

        // Ctrl + D → Right Arrow
        if (keycode == KC_D) {
            tap_code(KC_RIGHT);
            return false;
        }
    }
}

// ܂ō

    switch (keycode) {
        // pL[(Caps Lock)Anicola mode It
        case KC_CAPS_LOCK:
        // case KC_HOME:      // Capslock￺���ꍇ̂߂ɎgBoȂHOMEL[￴���pB񌳂ɖ߂
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG2));
                //send_string(SS_LSFT(SS_TAP(X_CAPS_LOCK))); //windows
            #ifndef USE_OBSERVE_IME
                nicola_off();
            #endif
            }
            return false;
        // p[ĥƂewL[(F14)ŁAnicola mode IEewɕύXBŕϊAEŮicolaI
        case KC_F14:
            if (record->event.pressed) {
                send_string(SS_TAP(X_LNG1)); // Mac
                // send_string(SS_TAP(X_F14)); //windows
            #ifndef USE_OBSERVE_IME
                nicola_on();
            #endif
            }
            return false;
    }

    // NICOLAewVtg
    bool a = true;
    if (nicola_state()) {
        nicola_mode(keycode, record);
        a = process_nicola(keycode, record);
    }
    if (a == false) return false;

    return true;
}

// This function gets called at every matrix scan.
void matrix_scan_user(void) {

	uint32_t now = timer_read32();
	timer_tick(now);	// drive nicola state-machine.
}

// This function switches the LED pattern for each layer.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    //rgb_matrix_set_color_all(0, 0, 0);
    for (uint8_t i = led_min; i < led_max; i++)
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);

// Ȃ񂾂킩񂈂ȂBႁ̂Ōɖ߂

    //rgb_matrix_set_color_all(0, 0, 0);
    for (uint8_t i = led_min; i < led_max; i++)
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
        
        // 255.255.0F^255.255.255F^255.0.0Fԁ^0.255.0F΁^0.255.255FF^255.0.255FsN

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 0); // nicola : off 
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_CENTER_INDEX, 0, 63, 0); // nicola : on ΍
            break;
        case _NICOLA:
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_LEFT_INDEX, 255, 255, 0); // nicola : on 
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_CENTER_INDEX, 127, 127, 0); // nicola : on yF
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_RIGHT_INDEX, 255, 255, 0); // nicola : on
            break;
        case _FUNC:
            RGB_MATRIX_INDICATOR_SET_COLOR(OYA_LEFT_INDEX, 255, 0, 0); // Left Oyayubi key : DEL
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_BS_INDEX, 255, 0, 0); // function key : DEL
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_PS_INDEX, 0, 0, 255); // function key : PS : 
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_HOME_INDEX, 0, 0, 255); // function key : HOME
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_PU_INDEX, 0, 0, 255); // function key : PU
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_PD_INDEX, 0, 0, 255); // function key : PD
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_UP_INDEX, 255, 255, 0); //  function key : 
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_LEFT_INDEX, 255, 255, 0); // function key : 
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_DOWN_INDEX, 255, 255, 0); // function key : 
            RGB_MATRIX_INDICATOR_SET_COLOR(FN_RIGHT_INDEX, 255, 255, 0); // function key : 
            break;
    }
    return false;
}

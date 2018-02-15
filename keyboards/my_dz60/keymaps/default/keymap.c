#include "dz60.h"
#include "mousekey.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

#undef _______
#define _______ KC_NO

#undef KEYMAP
#define KEYMAP KEYMAP_2_SHIFTS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	KEYMAP(F(0),    KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,  KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, KC_BSPC,
         KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,  KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
         KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,  KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
         KC_LSPO, _______, KC_Z,    KC_X,    KC_C,  KC_V,   KC_B,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_UP, KC_DEL,
         _______, _______, KC_LALT, KC_LGUI, MO(1), KC_SPC, MO(2), KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT),


  KEYMAP(_______, _______,    _______,    _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______,    KC_MS_UP,   _______,     _______, _______, _______, _______, _______, _______, KC_UP, _______, _______, _______,
         KC_LCTL, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_RIGHT, _______, _______, KC_MS_BTN1, KC_MS_BTN2, _______, _______, _______, _______,
         KC_LSPO, _______,    F(1),       _______,     _______, _______, KC_LEFT, KC_DOWN, _______, _______, _______, _______, KC_RSPC, _______, _______,
         _______, _______,    _______,    _______,     _______, _______, _______, _______, _______, _______, _______),

	KEYMAP(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_DEL,
         _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, RESET, F(2),
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, _______, BL_DEC, BL_TOGG, BL_INC, BL_STEP, _______, _______, _______, _______, _______, _______, _______,
         _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

enum function_id {
  SHIFT_ESC,
  MOUSE_SLOW,
  PROGRAM_GLOW
};

const uint16_t PROGMEM fn_actions[] = {
  [0] = ACTION_FUNCTION(SHIFT_ESC),
  [1] = ACTION_FUNCTION(MOUSE_SLOW),
  [2] = ACTION_FUNCTION(PROGRAM_GLOW)
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;

  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  case MOUSE_SLOW:
    if (record->event.pressed) {
      if (mk_max_speed == MOUSEKEY_MAX_SPEED) {
        mk_max_speed = MOUSEKEY_MAX_SPEED/2;
      } else {
        mk_max_speed = MOUSEKEY_MAX_SPEED;
      }
    }
    break;
  case PROGRAM_GLOW:
    rgblight_enable_noeeprom();
    rgblight_setrgb(200, 0, 0);
    reset_keyboard();
    break;
  }
}

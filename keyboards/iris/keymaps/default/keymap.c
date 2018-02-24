#include "action_layer.h"
#include "action_tapping.h"
#include "iris.h"
#include "eeconfig.h"
#include "timer.h"


#define MODS_SHIFT_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

extern keymap_config_t keymap_config;

enum custom_keycodes {
  KC_SESC = SAFE_RANGE,
  KC_LT_LPRN,
  KC_LT_RPRN,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_MO MO
#define KC_LALTK(CODE) LALT_T(KC_##CODE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  KC_KEYMAP(
  //,----+----+----+----+----+----.                  ,----+----+----+----+----+----.
     SESC, 1  , 2  , 3  , 4  , 5  ,                    6  , 7  , 8  , 9  , 0  ,BSPC,
  //|----+----+----+----+----+----|                  |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,                    Y  , U  , I  , O  , P , BSLS,
  //|----+----+----+----+----+----|                  |----+----+----+----+----+----|
     LCTL, A  , S  , D  , F  , G  ,                    H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.        ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B ,LT_LPRN,     LT_RPRN,N  , M  ,COMM,DOT ,SLSH, ENT,
  //`----+----+----+--+-+----+----+----/        \----+----+----+----+----+----+----'
                     MO(2),LALTK(EQL),LGUI,       SPC, MINS, MO(1)
  //                  `----+----+----'            `----+----+----'
  ),

  KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 , F10, F11,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
          ,   ,    ,    ,    ,    ,                   ,    , UP ,    ,    , F12,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,LEFT,DOWN,RIGHT,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,     LCBR,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                            ,    ,    ,       LBRC,   ,
  //                  `----+----+----'        `----+----+----'
  ),

  KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,UNDS,PLUS,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,LCBR,RCBR,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,RCBR,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                            ,    ,RBRC,           ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
          ,   ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                            ,    ,    ,           ,    ,
  //                  `----+----+----'        `----+----+----'
  ),
};

static bool layer_interrupted = false;
static uint16_t lt_pressed = 0;

// A version of LT that lets you use shifted keys
bool better_lt(keyrecord_t *record, uint8_t layer, uint16_t keycode) {
  if (record->event.pressed) {
    layer_interrupted = false;
    lt_pressed = record->event.time;
    layer_on(layer);
  } else {
    if (!layer_interrupted &&
        TIMER_DIFF_16(record->event.time, lt_pressed) < TAPPING_TERM) {

      if (keycode & MODS_SHIFT_MASK) {
        register_code(KC_LSFT);
      }
      register_code((uint8_t) keycode);
      unregister_code((uint8_t) keycode);
      if (keycode & MODS_SHIFT_MASK) {
        unregister_code(KC_LSFT);
      }
    }
    layer_off(layer);
  }
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t shift_esc_shift_mask;
  switch (keycode) {
  case KC_SESC:
    shift_esc_shift_mask = get_mods() & MODS_SHIFT_MASK;
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
  case KC_LT_LPRN:
    return better_lt(record, 1, KC_LPRN);
  case KC_LT_RPRN:
    return better_lt(record, 2, KC_RPRN);
  default:
    layer_interrupted = true;
  }
  return true;
}

void matrix_init_user() {
  DDRD &= ~(1<<5);
  PORTD &= ~(1<<5);

  DDRB &= ~(1<<0);
  PORTB &= ~(1<<0);
}

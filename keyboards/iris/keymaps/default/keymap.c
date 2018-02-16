#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

extern keymap_config_t keymap_config;

enum custom_keycodes {
  KC_SESC = SAFE_RANGE,
  /* KC_ALT_MIN */
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
#define KC_LT1(CODE) LT(1, KC_##CODE)
#define KC_LT2(CODE) LT(2, KC_##CODE)
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
     LSFT, Z  , X  , C  , V  , B,LT1(LPRN),  LT2(RPRN),N  , M  ,COMM,DOT ,SLSH, ENT,
  //`----+----+----+--+-+----+----+----/        \----+----+----+----+----+----+----'
                     MO(2),LALTK(MINS),LGUI,      SPC , EQL, MO(1)
  //                  `----+----+----'            `----+----+----'
  ),

  KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     GRV , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,MINS, EQL,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
          ,   ,    ,    ,    ,    ,                   ,    , UP ,    ,LBRC,RBRC,
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

/* bool is_hold(keyrecord_t *record) { */
/*   return (record->tap.count <= 0 || record->tap.interrupted); */
/* }; */

/* void cadet_function(keyrecord_t *record, uint16_t hold_mod, uint16_t tap_key) { */
/*   // Generalised space cadet */
/*   if (record->event.pressed) { */
/*     if (is_hold(record)) { */
/*       register_code(hold_mod); */
/*     } */
/*   } */
/*   else { */
/*     if (is_hold(record)) { */
/*       unregister_code(hold_mod); */
/*     } */
/*     else { */
/*       register_code(tap_key); */
/*       unregister_code(tap_key); */
/*     } */
/*   } */
/* }; */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t shift_esc_shift_mask;

  switch (keycode) {
  case KC_SESC:
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
  /* case KC_ALT_MIN: */
  /*   cadet_function(keycode, KC_LALT, KC_MINS); */
  /*   break; */
  }
  return true;
}

/* 
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
                        _______,
      KC_F13,  KC_MUTE, KC_MSTP,
      KC_F14,  KC_NO,   KC_MPRV,
      KC_F15,  KC_NO,   KC_MNXT,
      KC_F16,  KC_LGUI, KC_MPLY
  ),
  [1] = LAYOUT(
                        _______,
      _______, _______, _______,
      _______, _______, _______,
      _______, _______, _______,
      _______, _______, _______
  ),
  [2] = LAYOUT(
                        _______,
      _______, _______, _______,
      _______, _______, _______,
      _______, _______, _______,
      _______, _______, _______
  ),
  [3] = LAYOUT(
                        _______,
      _______, _______, _______,
      _______, _______, _______,
      _______, _______, _______,
      _______, _______, QK_BOOT
  ),
};

#define HIGHEST_LAYER 3 //replace X with your highest layer

static uint8_t current_layer = 0;

enum custom_keycodes {
    KC_LUP = SAFE_RANGE, //cycle layers in up direction
    KC_LDN //cycle layers in down direction
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_LUP:
    if(record->event.pressed) {
      if (current_layer == HIGHEST_LAYER){
        for (int i=1; i<=HIGHEST_LAYER; i++){
          layer_off(i);
        }
        current_layer=0;
      } else { 
        current_layer++;
        layer_on(current_layer);
      }
    }
    return false;
  case KC_LDN:
    if(record->event.pressed) {
      if (current_layer == 0){
        for (int i=1; i<=HIGHEST_LAYER; i++){
          layer_on(i);
        }
        current_layer=HIGHEST_LAYER;
      } else {
        layer_off(current_layer);
        current_layer--;
      }
    }
    return false;
  default:
    return true;
  }
}  

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
  [0] = { ENCODER_CCW_CW(KC_LDN, KC_LUP) },
  [1] = { ENCODER_CCW_CW(_______, _______) },
  [2] = { ENCODER_CCW_CW(_______, _______) },
  [3] = { ENCODER_CCW_CW(_______, _______) }
};
#endif

#ifdef RGB_MATRIX_ENABLE
// different layer will have different backlight, capslock only light up on base layer, winlock will light up in all all layers
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
  switch (get_highest_layer(layer_state))
  {
  case 0:
    rgb_matrix_set_color_all(0, 0, 0);
    break;
  case 1:
    rgb_matrix_set_color_all(0, 0, 0);
    rgb_matrix_set_color(0, 0, 255, 255);
    break;
  case 2:
    rgb_matrix_set_color_all(0, 0, 0);
    rgb_matrix_set_color(1, 255, 165, 0);
    break;
  case 3:
    rgb_matrix_set_color_all(0, 0, 0);
    rgb_matrix_set_color(2, 238, 130, 238);
    break;
  default:
    break;
  }
  return false;
};
#endif


#ifdef OLED_ENABLE
bool oled_task_user(void) {
  switch (get_highest_layer(layer_state)) {
        case 1:
            oled_write_P(PSTR("||\n||\n||\n||\n||\n||\n||\n||\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("|||\n|||\n|||\n|||\n|||\n|||\n|||\n|||\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("||||\n||||\n||||\n||||\n||||\n||||\n||||\n||||\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_P(PSTR("|\n|\n|\n|\n|\n|\n|\n|\n"), false);
    }
  return false;
}

#endif


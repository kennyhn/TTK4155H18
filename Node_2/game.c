#include "game.h"
#include "adc_arduino.h"
#include "uart.h"
#include "pwm.h"
#include "can.h"
#include <util/delay.h>



int8_t check_game_over(void){
  uint16_t data = adc_read();
  if (data < 20){
    adc_read();
    return 1;
  }
  return 0;
}

void play_game(void){
  joystick_direction joystick_dir;
  joystick_raw_data joystick_data;
  slider_raw_data slider;
  receive_console_message(&joystick_data,&joystick_dir, &slider);
  pwm_driver(joystick_data.X_value);
  position_reference=slider.right_slider_value;
  solenoid_control(joystick_data.button_pressed);
  if(check_game_over()){
    can_message empty_message;
    empty_message.id = 1;
    empty_message.length = 0;
    if (can_allowed_to_send_flag){
      can_message_send(&empty_message);
      can_allowed_to_send_flag=0;
    }
  }
}

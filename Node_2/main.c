#include "uart.h"
#include "mcp2515.h"
#include "can.h"
#include "pwm.h"
#include "adc_arduino.h"
#include "TWI_Master.h"
#include "motor.h"
#include "game.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

int main(){
  USART_Init(MYUBRR);
  can_interrupt_init();
  position_reference=0;
  can_message_received = 0;
  motor_set = 0;
  K_p = 1;
  K_i = 1;
  printf("\n\n\n\n\n\n\n");

  cli();
  adc_init();
  can_normal_init();
  pwm_init();
  TWI_Master_Initialise();
  motor_init();
  sei();

  timer_interrupt_init();
  set_motor_start_point();
  joystick_direction jd;
  joystick_raw_data jrd;
  slider_raw_data srd;
  adc_read(); //To prevent first read to be zero
  _delay_ms(4); //To prevent first read to be zero
  can_data_receive();
  while(1){
    if(can_message_received){
        printf("Can message received\n");
        receive_console_message(&jrd,&jd, &srd);
        pwm_driver(jrd.X_value);
        position_reference=srd.right_slider_value;
        solenoid_control(jrd.button_pressed);
        if(check_game_over()){
          can_message smsg;
          smsg.id = 1;
          smsg.length = 0;
          if (can_allowed_to_send_flag){
            can_message_send(&smsg);
            can_allowed_to_send_flag=0;
          }
        }
    }
  }
  return 0;
}

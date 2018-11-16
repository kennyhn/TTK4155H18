#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "mcp2515.h"
#include "can.h"
#include "pwm.h"
#include "adc_arduino.h"
#include "TWI_Master.h"
#include "motor.h"
#include "game.h"

int main(){
  USART_Init(MYUBRR);
  interrupt_pcint6_init();
  position_reference=0;
  total_e = 0;
  can_message_received = 0;
  motor_set = 0;
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
  printf("before while\n");
  /*while(can_message_received){
    can_data_receive();
    printf("can flag: %d", can_message_received);
  }*/
  //can_message_received=0;
  printf("kommer hit\n");
  adc_read(); //To prevent first read to be zero
  _delay_ms(4); //To prevent first read to be zero
  can_data_receive();
  while(1){

    if(can_message_received){
        printf("Can message received\n");
        //Let CAN be driven outside this function
        receive_console_message(&jrd,&jd, &srd);
        //TBD
        //må fikse tidsforsinkelse for ADC. Heller bruke en interrupt enn delay
        pwm_driver(jrd.X_value);
        position_reference=srd.right_slider_value;
        solenoid_control(jrd.button_pressed);
        int i = 0;
        if(check_game_over()){
          printf("high score: %d\n", high_score);
          can_message smsg;
          smsg.id = 1;
          smsg.length = 2;
          smsg.data[i] = (uint8_t)(high_score/50); //divide by 50 to get seconds
          printf("high score divided %d\n", smsg.data[i]);
          if (can_allowed_to_send_flag){
            can_message_send(&smsg);
            can_allowed_to_send_flag=0;
          }
          high_score=0;
          //TBD
        }
    }
  }
  return 0;
}

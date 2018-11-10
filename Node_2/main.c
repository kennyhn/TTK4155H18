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
  printf("\n\n\n\n\n\n\n");
  cli();
  adc_init();
  can_normal_init();
  pwm_init();
  TWI_Master_Initialise();
  motor_init();
  sei();
  timer_interrupt_init();
  joystick_direction jd;
  joystick_raw_data jrd;
  slider_raw_data srd;
  reset_encoder();
  adc_read(); //To prevent first read to be zero
  _delay_ms(4); //To prevent first read to be zero
  high_score=0;
  while(1){
    if(can_message_received){
        can_message_received = 0;
        //Let CAN be driven outside this function
        receive_console_message(&jrd,&jd, &srd);
        //TBD
        //må fikse tidsforsinkelse for ADC. Heller bruke en interrupt enn delay
        pwm_driver(jrd.X_value);
        position_reference=srd.right_slider_value;
        solenoid_control(jrd.button_pressed);
        //printf("%d\n", jrd.button_pressed);
        int i = 0;
        if(check_game_over()){
          printf("high score: %d\n", high_score/50);
          can_message smsg;
          smsg.id = 1;
          smsg.length = 2;
          smsg.data[i] = (uint8_t)high_score/50; //divide by 50 to get seconds
          can_message_send(&smsg);
          high_score=0;
          //TBD
          //Vi må fikse interrupt for spillet.
        }
    }
  }
  return 0;
}

// Må løse at data<20 fra adc to++ ganger, noe skaper problemer både i node 1 og 2. Løsningen vi har nå funker
// men er ikke optimal.

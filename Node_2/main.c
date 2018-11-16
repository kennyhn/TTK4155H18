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

  cli();
  adc_init();
  can_normal_init();
  pwm_init();
  TWI_Master_Initialise();
  motor_init();
  sei();

  timer_interrupt_init();
  set_motor_start_point();
  adc_read(); //To prevent first read to be zero
  _delay_ms(4); //To prevent first read to be zero
  can_data_receive();
  while(1){
    if(can_message_received){
      play_game();
    }
  }
  return 0;
}

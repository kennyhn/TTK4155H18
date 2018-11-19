#include "uart_node2.h"
#include "mcp2515_node2.h"
#include "can_node2.h"
#include "pwm_node2.h"
#include "adc_node2.h"
#include "TWI_Master_node2.h"
#include "motor_node2.h"
#include "game_node2.h"
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

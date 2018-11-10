#define F_CPU 4915200
#include <util/delay.h>

#include "game.h"
#include "adc_arduino.h"
#include "uart.h"



int8_t check_game_over(void){
  //_delay_ms(30);
  uint16_t data = adc_read();
  printf("Data = %d \n", data);
  if (data < 20){
    adc_read();
    return 1;
  }
  return 0;
}

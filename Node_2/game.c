#include "game.h"
#include "adc_arduino.h"

int8_t check_game_over(){
  uint16_t data = adc_read();
  printf("Data = %d \n", data);
  if (data < 20){
    return 1;
  }
  return 0;
}

#include "game.h"
#include "adc.h"
#include "timer.h"

int8_t score_count(uint16_t data, time_t start){
  if (data<20){
    return stop_timer(start);
  }
}

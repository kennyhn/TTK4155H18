#include "timer.h"
#include "game.h"
#include "uart.h"
#include "can.h"
#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 4915200
#define PERIOD 1/60
#define PRESCALER 1024

//int=F_CPU/PRESCALER*period
void timer_interrupt_init(void){
  cli();
  TCCR0 |= (1<<WGM01);//Want to use CTC mode so the timer is cleared on comparison
  TCCR0 |= (1<<CS02) | (1<<CS00);//Sets 1024
  OCR0 = (F_CPU/PRESCALER)*PERIOD;//Setting top value
  TIMSK |= (1<<OCIE0);//Enable interrupt
  sei();
  can_allowed_to_send_flag=0;
  timer_flag=0;
  frame_rate_flag=1;
}


ISR(TIMER0_COMP_vect){
  static uint32_t counter = 0;

  frame_rate_flag=1; //Flag is set with a frequency of 60 Hz

  //Flag is set every 50ms
  if ((counter%3)==0){
    can_allowed_to_send_flag = 1;
  }
  //flag is set every 100 ms
  if ((counter%6)==0){ //10 Hz
    timer_flag=1;
  }

  //flag is set every second
  if ((counter%60) == 0){
    highscore++;
  }
  counter++;
}

#include "timer.h"
#include "game.h"
#include "uart.h"
#include "can.h"
#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 4915200
#define PERIOD 1/60 //frekvensen 1/Hz
#define PRESCALER 1024

//int=F_CPU/PRESCALER*period
void timer_interrupt_init(void){
  cli();
  //Want to use CTC mode so the timer is cleared on comparison
  TCCR0 |= (1<<WGM01);

  //Sets 1024
  TCCR0 |= (1<<CS02) | (1<<CS00);

  //Setter top value
  OCR0 = (F_CPU/PRESCALER)*PERIOD;

  //Enable interrupt
  TIMSK |= (1<<OCIE0);

  //TCNT0 = 0;
  sei();
  can_allowed_to_send_flag=0;
}


ISR(TIMER0_COMP_vect){
  static int counter = 0;

  //Flag is set every 50ms
  if ((counter%3)==0){
    can_allowed_to_send_flag = 1;
  }
  //flag is set every 100 ms
  if ((counter%6)==0){
  }

  //flag is set every second
  if ((counter%60) == 0){
    highscore++;
  }
  //printf("counter %d\n", counter);
  //if (counter == 255)counter=0; //To prevent overflow of coutner
  counter++;

  //TCNT0 = 0;
}

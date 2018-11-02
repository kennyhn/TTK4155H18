#include "pwm.h"
#include <avr/io.h>
#include "../Node_1/adc.h"
#include "can.h"
#define F_CPU 16000000
#define PRESCALER 8

//need to find top value for it to be 20 ms:
//N=F_CPU/(f_osc*(1+TOP))
//f_osc is the frequency when the duty cycle is 20 ms which becomes 50 hz.
//This gives us the TOP value to be 39999

void pwm_init(void){

  DDRB |= (1<<PB5);

  TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS11); //TCCR0B setting to mode 14, fast PWM
  TCCR1B &= ~(1<<CS12) & ~(1<<CS10);
  TCCR1A &= ~(1<<WGM10) & ~(1<<COM1A0); //set the mode to non inverted "duty cycle"
  TCCR1A |= (1<<WGM11)|(1<<COM1A1);

  //COM sets the PWM-signal low when comparison match
  //WGM sets operation mode
  //CS selects internal clock source

  //må sette OCR for å velge duty cyclen
  //OCR1A = 1999;
  ICR1 = 39999;

}

void pwm_driver(void){
  joystick_direction jd;
  joystick_raw_data jrd;
  //Let CAN be driven outside this function
  receive_joystick_message(&jrd,&jd);
  double placement = (double)jrd.X_value/255.0+1;

  if (placement>=1 && placement<=2){
    int number = placement*0.001*F_CPU/PRESCALER;
    //printf("number should be between 2000 and 4000: %d\n",number);
    OCR1A=number; //kun for testing foreløpig
  }
  else{
    OCR1A=3000;
  }
}

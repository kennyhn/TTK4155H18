#include "pwm.h"
#include <avr/io.h>
#include "../Node_1/adc.h"
#include "can.h"
#include "motor.h"
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

void timer_interrupt_init(){
  cli(); // Disable global interrupts
  TIMSK1 |= (1<<TOIE1); //Enabling OVERFLOW INTERRUPT
  sei(); //Enable global interrupts
}

ISR(TIMER1_OVF_vect){
  high_score++;
  int16_t reference=position_reference; // kan settes til 128 for testing
  int16_t position=transform_encoder_to_position(read_encoder());
  //printf("R %d \n", position_reference);
  //printf("P %d \n", position);
  int16_t e = reference - position;
  total_e += e;
  if (abs(total_e)>1000 || abs(e) < 1){
    total_e = e;
  }
  //printf("%d",total_e);
  int16_t u = 1*e+0.020*1*total_e;
  motor_driver(u); // this is our input
}

void pwm_driver(double x_value_raw){
  double placement = x_value_raw/255.0+1;
  if (placement>=1 && placement<=2){
    int number = placement*0.001*F_CPU/PRESCALER;
    //printf("number should be between 2000 and 4000: %d\n",number);
    OCR1A=number;
  }
  else{
    OCR1A=3000;
  }
}

void solenoid_control(uint8_t jrd_button_pressed){
  //TBD: Finne ut hvordan vi kan styre spenningen/verdien ut av en port

  DDRB |= (1<<PB4);//Setter port C pinne 3 til write

  if(jrd_button_pressed){
    PORTB |= (1<<PB4);
  }
  else{
    PORTB &= ~(1<<PB4);
  }
}

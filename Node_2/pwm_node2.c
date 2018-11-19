#define F_CPU 16000000
#define PRESCALER 8
#include "pwm_node2.h"
#include "../Node_1/adc.h"
#include "can_node2.h"
#include "motor_node2.h"
#include <avr/io.h>

void pwm_init(void){

  DDRB |= (1<<PB5);

  TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS11); //TCCR0B setting to mode 14, fast PWM
  TCCR1B &= ~(1<<CS12) & ~(1<<CS10);
  TCCR1A &= ~(1<<WGM10) & ~(1<<COM1A0); //set the mode to non inverted "duty cycle"
  TCCR1A |= (1<<WGM11)|(1<<COM1A1);

  //COM sets the PWM-signal low when comparison match
  //WGM sets operation mode
  //CS selects internal clock source

  //N=F_CPU/(f_osc*(1+TOP))
  ICR1 = 39999;
}

void timer_interrupt_init(){
  cli(); // Disable global interrupts
  TIMSK1 |= (1<<TOIE1); //Enabling OVERFLOW INTERRUPT
  sei(); //Enable global interrupts

  can_allowed_to_send_flag = 0;
  K_p = 1;
  K_i = 1;
  motor_set = 0;
  position_reference=0;
}

ISR(TIMER1_OVF_vect){
  static int counter = 0;
  static int16_t total_e = 0;
  if (counter%5 == 0){
    //Sets the flag every 100ms (10Hz)
    can_allowed_to_send_flag = 1;
  }

  if (motor_set){
    int16_t reference=position_reference; // kan settes til 128 for testing
    int16_t position=transform_encoder_to_position(read_encoder());
    //printf("R %d \n", position_reference);
    //printf("P %d \n", position);
    int16_t e = reference - position;
    total_e += e;
    if (abs(total_e)>1000 || abs(e) < 1){
      total_e = e;
    }
    int16_t u = K_p*e+0.020*K_i*total_e;
    motor_driver(u); // this is our input
  }
    counter++;
}

void pwm_driver(double x_value_raw){
  double placement = x_value_raw/255.0+1;
  if (placement>=1 && placement<=2){
    int number = placement*0.001*F_CPU/PRESCALER;
    OCR1A=number;
  }
  else{
    OCR1A=3000;
  }
}

void solenoid_control(uint8_t jrd_button_pressed){
  DDRB |= (1<<PB4);//Setter port C pinne 3 til write

  if(jrd_button_pressed){
    PORTB |= (1<<PB4); //setter porten høy
  }
  else{
    PORTB &= ~(1<<PB4); //setter porten lavs
  }
}

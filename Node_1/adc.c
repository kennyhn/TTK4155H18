#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include "adc.h"
#include <avr/interrupt.h>



void joystick_y_axis(volatile uint8_t *adc){
    _delay_ms(1);
    *adc = 0x04;
    while(!adc_is_ready_flag);
    adc_is_ready_flag=0;
     //printf("%d\n",*adc);
}

void joystick_x_axis(volatile uint8_t *adc){
      _delay_ms(1);
      *adc = 0x05;
      while(!adc_is_ready_flag);
      adc_is_ready_flag=0;
     //printf("%d\n",*adc);
}

// L-slider midten nede
//l-button er midten oppe
void l_slider(volatile uint8_t *adc){
      _delay_ms(1);
      *adc = 0x06;
      while(!adc_is_ready_flag);
      adc_is_ready_flag=0;

    //printf("%d\n",*adc);
}

// R-slider oppe til ventre
//r-button er under r-slider
void r_slider(volatile uint8_t *adc){
      _delay_ms(1);
      *adc = 0x07;
      while(!adc_is_ready_flag);
      adc_is_ready_flag=0;
    //printf("%d\n",*adc);
}

joystick_perc_angle get_perc_angle(volatile uint8_t *adc){
    joystick_perc_angle jpa;
    double neutral = 255/2;
    joystick_x_axis(adc);
    jpa.X_value = ((double)*adc - neutral)/(255 - neutral)*100;
    joystick_y_axis(adc);
    jpa.Y_value = ((double)*adc - neutral)/(255 - neutral)*100;
    return jpa;
}



joystick_direction check_joystick_direction(volatile uint8_t *adc){
    joystick_perc_angle jpa = get_perc_angle(adc);
    //printf("X-value: %d \n Y-value: %d \n", jpa.X_value, jpa.Y_value);
    if(abs(jpa.X_value) < 10 && abs(jpa.Y_value) < 10 ){
        return NEUTRAL;
    }
    else{
        if(abs(jpa.X_value) < abs(jpa.Y_value)){
            if (jpa.Y_value > 0){
                return UP;
            }
            else{
                return DOWN;
            }
        }
        else{
            if (jpa.X_value > 0){
                return RIGHT;
            }
            else{
                return LEFT;
            }
        }
    }
}


void adc_interrupt_init(void){
  // Set pin to input
  DDRE &= ~(1<<PE0);
  // Disable global interrupts
  cli();
  GICR &= ~(1<<INT2);
  //Interrupt on falling edge PD2
  EMCUCR &= ~(1<<ISC2);
  //MCUCR |= (1<<ISC11);
  //MCUCR &= ~(1<<ISC10);
  //Enable interrupt on PD2
  GICR |= (1<<INT2);
  GIFR |= (1<<INTF2);
  //Enable global interrupts
  sei();
  adc_is_ready_flag=0;

}



ISR(INT2_vect){
  adc_is_ready_flag = 1;
}

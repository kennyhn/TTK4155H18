#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include "adc.h"

typedef enum Joystick_direction{LEFT, RIGHT, UP, DOWN,NEUTRAL}joystick_direction;
typedef struct Joystick_perc_angle{
    int8_t X_value;
    int8_t Y_value;
}joystick_perc_angle;

void joystick_y_axis(uint8_t *adc){
    _delay_ms(1);
    *adc = 0x04;
    _delay_ms(60);
     printf("%d\n",*adc);
}

void joystick_x_axis(uint8_t *adc){
    _delay_ms(1);
    *adc = 0x05;
    _delay_ms(60);
     printf("%d\n",*adc);
}

// L-slider midten nede
//l-button er midten oppe
void l_slider(uint8_t *adc){
    _delay_ms(1);
    *adc = 0x06;
    _delay_ms(60);
     printf("%d\n",*adc);
}

// R-slider oppe til ventre
//r-button er under r-slider
void r_slider(uint8_t *adc){
    _delay_ms(1);
    *adc = 0x07;
    _delay_ms(60);
     printf("%d\n",*adc);
}

void run_joystick(){
    MCUCR = MCUCR|(1<<SRE); //activate XMEM
    volatile uint8_t *adc = (uint8_t*) 0x1400;
    //joystick_y_axis(adc);
    //joystick_x_axis(adc);
    //r_slider(adc);
    //l_slider(adc);

}

joystick_perc_angle get_perc_angle(uint8_t *adc){
    joystick_perc_angle jpa;
    double neutral = 255/2;


    joystick_x_axis(adc);
    jpa.X_value = ((double)*adc - neutral)/(255 - neutral)*100;
    joystick_y_axis(adc);
    jpa.Y_value = ((double)*adc - neutral)/(255 - neutral)*100;
    return jpa;
}

joystick_direction check_joystick_direction(uint8_t *adc){
    joystick_perc_angle jpa = get_perc_angle(adc);
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

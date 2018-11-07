#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include "adc.h"

void joystick_y_axis(volatile uint8_t *adc){
    _delay_ms(1);
    *adc = 0x04;
    _delay_ms(60);
     //printf("%d\n",*adc);
}

void joystick_x_axis(volatile uint8_t *adc){
    _delay_ms(1);
    *adc = 0x05;
    _delay_ms(60);
     //printf("%d\n",*adc);
}

// L-slider midten nede
//l-button er midten oppe
void l_slider(volatile uint8_t *adc){
    _delay_ms(1);
    *adc = 0x06;
    _delay_ms(60);
}

// R-slider oppe til ventre
//r-button er under r-slider
void r_slider(volatile uint8_t *adc){
    _delay_ms(1);
    *adc = 0x07;
    _delay_ms(60);
}


void run_joystick(){
    MCUCR = MCUCR|(1<<SRE); //activate XMEM
    volatile uint8_t *adc = (uint8_t*) 0x1400;
    //joystick_y_axis(adc);
    //joystick_x_axis(adc);
    r_slider(adc);
    //l_slider(adc);
    /*joystick_direction test = check_joystick_direction(adc);
    if (test == 0){
        printf("left\n");
    }
    else if (test == 1){
        printf("right\n");
    }
    else if (test == 2){
        printf("up\n");
    }
    else if (test == 3){
        printf("down\n");
    }
    else{
        printf("neutral\n");
    }*/
    //printf("%d\n", check_joystick_direction(adc));

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

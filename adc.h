#ifndef _ADC_H_
#define _ADC_H_

#include <stdlib.h>
#include <stdio.h>

typedef enum Joystick_direction{LEFT, RIGHT, UP, DOWN,NEUTRAL}joystick_direction;
typedef struct Joystick_perc_angle{
    int8_t X_value;
    int8_t Y_value;
}joystick_perc_angle;

void joystick_y_axis(uint8_t *adc);

void joystick_x_axis(uint8_t *adc);

void r_slider(uint8_t *adc);

void l_slider(uint8_t *adc);

void run_joystick();

joystick_perc_angle get_perc_angle(uint8_t *adc);

joystick_direction check_joystick_direction(uint8_t *adc);

#endif

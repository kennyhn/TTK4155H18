#ifndef _ADC_H_
#define _ADC_H_

#include <stdlib.h>
#include <stdio.h>

void joystick_y_axis(uint8_t *adc);

void joystick_x_axis(uint8_t *adc);

void r_slider(uint8_t *adc);

void l_slider(uint8_t *adc);


void run_joystick();


#endif

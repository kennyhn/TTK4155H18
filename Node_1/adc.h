/**@file adc.h
 * @brief Functions for reading the different controls.
 */
#ifndef ADC_H_
#define ADC_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

volatile uint8_t adc_is_ready_flag;

typedef enum Joystick_direction{LEFT, RIGHT, UP, DOWN,NEUTRAL}joystick_direction;
typedef struct Joystick_perc_angle{
    int8_t X_value;
    int8_t Y_value;
}joystick_perc_angle;

typedef struct Joystick_raw_data{
    uint8_t X_value;
    uint8_t Y_value;
    uint8_t button_pressed; //0 or 1
}joystick_raw_data;

typedef struct Slider_raw_data{
    uint8_t right_slider_value;
    uint8_t left_slider_value;
}slider_raw_data;

/**@brief Read the value in y direction of joystick.
 */
void joystick_y_axis(volatile uint8_t *adc);

/**@brief Read the value in x direction of joystick.
 */
void joystick_x_axis(volatile uint8_t *adc);

void r_slider(volatile uint8_t *adc);

void l_slider(volatile uint8_t *adc);

joystick_perc_angle get_perc_angle(volatile uint8_t *adc);

joystick_direction check_joystick_direction(volatile uint8_t *adc);

void adc_interrupt_init(void);

#endif

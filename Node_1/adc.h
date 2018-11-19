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
 *@param adc the address of the chip in MCU
 *@return uint8_t which is a value between 0-255
 */
uint8_t joystick_y_axis(volatile uint8_t *adc);

/**@brief Read the value in x direction of joystick.
 *@param adc the address of the chip in MCU
 *@return uint8_t which is a value between 0-255
 */
uint8_t joystick_x_axis(volatile uint8_t *adc);

/**@brief Read the value of the right slider
 *@param adc the address of the chip in MCU
 *@return uint8_t which is a value between 0-255
 */
uint8_t r_slider(volatile uint8_t *adc);

/**@brief Read the value of the left slider
 *@param adc the address of the chip in MCU
 *@return uint8_t which is a value between 0-255
 */
uint8_t l_slider(volatile uint8_t *adc);

/**@brief Convert the analogue value between 0-255 to a value between 0-100
 *@return joystick_perc_angle which is a struct containing the x- and y-value of the joystick between 0 and 100
 */
joystick_perc_angle get_perc_angle(volatile uint8_t *adc);

/**@brief Convert the x- and y-value of the joystick to a direction
 *@return joystick_direction which is an enum showing which direction the joystick is in
 */
joystick_direction check_joystick_direction(volatile uint8_t *adc);

/**@brief Initialize external interrupt for the ADC
 */
void adc_interrupt_init(void);

#endif

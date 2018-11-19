/**@file pwm_node2.h
 * @brief Functions controlling the timer in Node 2, and the PWM signal.
 */
#ifndef PWM_NODE2_H_
#define PWM_NODE2_H_
#include <stdint.h>

volatile int16_t position_reference;
volatile int8_t can_allowed_to_send_flag;
volatile uint8_t K_p;
volatile uint8_t K_i;

/**@brief Initialising the PWM signal.
 */
void pwm_init(void);

/**@brief The function that creates the pwm signal.
 */
void pwm_driver(double x_value_raw);

/**@brief Setting up for the use of a timer interrupt.
 */
void timer_interrupt_init();

/**@brief Function controlling the solenoid.
 */
void solenoid_control(uint8_t jrd_button_pressed);
#endif

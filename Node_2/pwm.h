#ifndef PWM_H_
#define PWM_H_
#include <stdint.h>

volatile int16_t position_reference;
volatile int16_t total_e;
volatile int32_t high_score;

void pwm_init(void);
void pwm_driver(double x_value_raw);
void timer_interrupt_init();
void solenoid_control(uint8_t jrd_button_pressed);
#endif

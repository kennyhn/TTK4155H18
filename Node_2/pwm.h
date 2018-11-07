#ifndef PWM_H_
#define PWM_H_
#include <stdint.h>

volatile uint8_t position_reference;
volatile int16_t total_e;

void pwm_init(void);
void pwm_driver(double x_value_raw);
void timer_interrupt_init();
#endif

/**@file timer.h
 * @brief Initializing different timer interrupts and also declare global flags/variables
 */
#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

volatile uint8_t timer_flag;

/**@brief Initialize the timer interrupt for node 1
 *
 *Sets the register neccessary to get an interrupt every 1/60 seconds (60Hz)
 */
void timer_interrupt_init(void);
#endif

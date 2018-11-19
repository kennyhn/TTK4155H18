/**@file timer.h
 * @brief Initializing different timer interrupts and also declare global flags/variables
 */
#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

volatile uint8_t timer_flag;

void timer_interrupt_init(void);
#endif

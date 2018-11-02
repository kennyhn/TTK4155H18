#ifndef ADC_ARDUINO_H_
#define ADC_ARDUINO_H_

#include <avr/io.h>
#include <stdint.h>

void adc_init(void);
uint16_t adc_read(void);

#endif

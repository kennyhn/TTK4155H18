/**@file adc_node2.h
 * @brief Functions for reading the IR-sensors.
 */

#ifndef ADC_NODE2_H_
#define ADC_NODE2_H_

#include <avr/io.h>
#include <stdint.h>

/**@brief Initialising the adc.
 */
void adc_init(void);

/**@brief Reading the digital value from the adc.
 *
 * @return uint16_t the non-negative value from the IR-sensor.
 */
uint16_t adc_read(void);

#endif

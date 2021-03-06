/**@file spi.h
 * @brief Functions for initializing, sending and recieving data on SPI-bus
 */
#ifndef SPI_H_
#define SPI_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

/**@brief Initialize the SPI bus
 */
void SPI_master_init(void);

/**@brief Transmits data using SPI bus
 */
void SPI_master_transmit(char cData);

/**@brief Recieves data using SPI bus
 */
char SPI_master_receive(void);

#endif

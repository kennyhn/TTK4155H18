/**@file spi_node2.h
 * @brief Functions controlling the SPI communication.
 */
#ifndef SPI_NODE2_H_
#define SPI_NODE2_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

/** @brief Initialising the mcu as the master.
 */
void SPI_master_init(void);

/** @brief Function that is transmitting data from the SPI master.
 *
 * @param cData The data being transmitted.
 */
void SPI_master_transmit(char cData);

/** @brief Function that lets the master receive a message from the SPI bus.
 *
 * @return char The value that is received.
 */
char SPI_master_receive(void);
#endif

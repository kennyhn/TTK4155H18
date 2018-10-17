#ifndef _SPI_H_
#define _SPI_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>

void SPI_master_init(void);
void SPI_master_transmit(char cData);
char SPI_master_receive(void);

#endif

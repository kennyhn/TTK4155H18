/**@file sram.h
 * @brief Functions for doing write and read operations to the SRAM
 */
#ifndef SRAM_H_
#define SRAM_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void SRAM_OLED_reset();
void SRAM_write_to_mem(uint8_t page, uint8_t column, uint8_t screen_data);
void SRAM_writes_to_screen();
uint8_t SRAM_read_oled_data(uint8_t page, uint8_t column);

void SRAM_test(void);
#endif

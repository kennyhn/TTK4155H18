#ifndef _SRAM_H_
#define _SRAM_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void SRAM_OLED_reset();
void SRAM_write(uint8_t page, uint8_t column, uint8_t screen_data);
void SRAM_writes_to_screen();
uint8_t SRAM_read(uint8_t page, uint8_t column);


void SRAM_test(void);

//void LATCH_test(void);

void GAL_test(void);

#endif

/**@file sram.h
 * @brief Functions for doing write and read operations to the SRAM
 */
#ifndef SRAM_H_
#define SRAM_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/**@brief Empties the OLED part of the SRAM.
 *
 *Sets all bits in this part of the SRAM to 0
 */
void SRAM_OLED_reset();

/**@brief Writes the data we want to write to the screen to the SRAM.
 *
 *This function makes it possible to use the SRAM as a buffer to write to the screen.
 *This is so we can change pixels on the screen without losing earlier written pixels on the screen.
 */
void SRAM_write_to_mem(uint8_t page, uint8_t column, uint8_t screen_data);

/**@brief Writes everything on the SRAM to the screen
 *
 *Writes all the data in the SRAM to the screen
 */
void SRAM_writes_to_screen();

/**@brief Reads the screen data from SRAM
 */
uint8_t SRAM_read_oled_data(uint8_t page, uint8_t column);

/**@brief Test to check if no data is lost during transmission to and from SRAM
 */
void SRAM_test(void);
#endif

/**@file oled.h
 * @brief Functions for initializing, and do write operations to the OLED screen on the multiboard.
 * Also has some functions for drawing different shapes on the screen
 */
#ifndef OLED_H_
#define OLED_H_
#include <stdint.h>

/**@brief Writes to the command given in as data.
 *
 *@param data is the command we want to give to the OLED used to set up the screen.
 */
void write_c(char data);

/**@brief Empties the screen.
 *
 *Sets every pixel on the screen to OFF.
 */
void oled_reset(void);

/**@brief Sets up the screen for normal operations.
 *
 *Sends the necessary commands to set up the screen for our desired operations.
 */
void oled_init();

/**@brief Goes to the row on the screen that needs to be changed.
 *
 *Moves the "pointer" to the row on the screen that is going to be changed.
 *The pointer is still on the same column as before this operation.
 *@param line is a value between 0-7.
 */
void oled_goto_line(uint8_t line);

/**@brief Goes to the column on the screen that we want to change.
 *
 *Moves the "pointer" to the column on the screen that is going to be changed.
 *The pointer is still on the same row as before this operation.
 *@param column is a value between 0-127.
 */
void oled_goto_column(uint8_t column);

/**@brief clear a row on the screen.
 *
 *Sets a row (containing 8 vertical pixels) to OFF.
 *@param line is a value between 0-7.
 */
void oled_clear_line(uint8_t line);

/**@brief Goes to the position (row, column) on the screen that we want to change.
 *
 *Moves the pointer to the row containing 8 vertical bits and column with 1 horizontal bit that we wants to change.
 *To change the uint8_t bit on this position we write to the address to oled_data. 1 means pixel ON and 0 means pixel OFF.
 *@param row is a value between 0-7.
 *@param column is a value between 0-127.
 */
void oled_pos(uint8_t row, uint8_t column);

/**@brief Writes a c-string to the screen.
 *
 */
void oled_print4(char* word);

/**@brief Writes a c-string to the screen.
 *
 */
void oled_print5(char* word);

/**@brief Writes a c-string to the screen.
 *
 */
void oled_print8(char* word);

/**@brief Draws a circle.
 *
 *@param x0 x value of the center of the circle.
 *@param y0 y value of the center of the circle.
 *@param r radius of the circle.
 */
void draw_circle(uint8_t x0, uint8_t y0, uint8_t r);

/**@brief Draws a line
 *
 *draws a line from a pixel to another pixel on the screen
 *@param x1 Start column of the line. x1 is less than x2
 *@param x2 End column of the line. x2 is greater than x1
 *@param y1 Start row (in terms of pixel) of the line. y1 is less than y2
 *@param y2 End row (in terms pixels) of the line.
 */
void draw_line(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);

/**@brief sets a specific pixel on the screen to on.
 *
 *This operation writes to SRAM
 */
void print_pixel(uint8_t x, uint8_t y);

/**@brief Draws a half circle
 *
 */
void draw_half_circle(uint8_t x0, uint8_t y0, uint8_t r, int dir);

/**@brief Draws a smiley with radius r
 */
void draw_smiley(uint8_t x0, uint8_t y0, uint8_t r);

/**@brief Writes a letter to the screen using the SRAM
 */
void SRAM_oled_write_character_font4(uint8_t line, uint8_t column, char letter);

/**@brief Writes a letter to the screen using the SRAM
 */
void SRAM_oled_write_character_font5(uint8_t line, uint8_t column, char letter);

/**@brief Writes a letter to the screen using the SRAM
 */
void SRAM_oled_write_character_font8(uint8_t line, uint8_t column, char letter);

/**@brief Writes a c-string to the screen using the SRAM
 */
void SRAM_oled_print8(uint8_t line, uint8_t column, char* word);

/**@brief Writes a c-string to the screen using the SRAM
 */
void SRAM_oled_print5(uint8_t line, uint8_t column, char* word);

/**@brief Writes a c-string to the screen using the SRAM
 */
void SRAM_oled_print4(uint8_t line, uint8_t column, char* word);


#endif

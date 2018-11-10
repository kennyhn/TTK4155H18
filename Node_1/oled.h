#ifndef OLED_H_
#define OLED_H_
#include <stdint.h>


void write_c(char data);
void oled_reset(void);
void oled_init();
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_clear_line(uint8_t line);
void oled_pos(uint8_t row, uint8_t column);
void oled_print4(char* word);
void oled_print5(char* word);
void oled_print8(char* word);
void draw_circle(uint8_t x0, uint8_t y0, uint8_t r);
void draw_line(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
void print_pixel(uint8_t x, uint8_t y);
void draw_half_circle(uint8_t x0, uint8_t y0, uint8_t r, int dir);
void draw_smiley(uint8_t x0, uint8_t y0, uint8_t r);


void SRAM_oled_write_character_font4(uint8_t line, uint8_t column, char letter);
void SRAM_oled_write_character_font5(uint8_t line, uint8_t column, char letter);
void SRAM_oled_write_character_font8(uint8_t line, uint8_t column, char letter);
void SRAM_oled_print8(uint8_t line, uint8_t column, char* word);
void SRAM_oled_print5(uint8_t line, uint8_t column, char* word);
void SRAM_oled_print4(uint8_t line, uint8_t column, char* word);


#endif

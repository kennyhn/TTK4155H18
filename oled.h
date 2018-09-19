#ifndef _OLED_H_
#define _OLED_H_

void write_c(char data);
void oled_reset(void);
void oled_init();
void oled_write_character_font8(char letter);
void oled_home();
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_clear_line(uint8_t line);
void oled_pos(uint8_t row, uint8_t column);
void oled_print(char* word);
void oled_driver(void);


#endif

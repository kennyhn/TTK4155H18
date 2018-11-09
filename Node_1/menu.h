#ifndef MENU_H_
#define MENU_H_

#include <stdint.h>
#include "adc.h"

typedef struct Menu_element{
    char* name;
    uint8_t line;
    struct Menu_element* up;
    struct Menu_element* down;
    struct Menu_element* choose;
    struct Menu_element* back;
    //void (*function_peker) (int,char);
}menu_element;

void menu_driver(joystick_direction dir, menu_element** menu_choice, volatile uint8_t* adc);
menu_element* create_menu();
void print_page(menu_element* node);
void print_score(void);
void print_marker(uint8_t line);

#endif

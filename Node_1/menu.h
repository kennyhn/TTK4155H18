/**@file menu.h
 * @brief Functions for running the menu
 *
 * This contains the menu element and the functions needed to make the
 * menu and navitgate through it
 */

#ifndef MENU_H_
#define MENU_H_

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

/** @brief The menu menu_driver
 *
 * The function that makes navigating through the menu possible.
 *
 * @param K_p tuning constant
 * @param K_i tuning constant
 * @param dir joystick direction
 * @param menu_choice the current menu element chosen
 * @param adc mcu address of the adc
 */
void menu_driver(uint8_t* K_p,uint8_t* K_i,joystick_direction* dir, menu_element** menu_choice, volatile uint8_t* adc);

/** @brief Creates the menu grid
 *
 * This function creates all the menu elements and link them together
 *
 * @return menu_element* the root node
 */
menu_element* create_menu();

/** @brief Print the current page
 *
 * This function creates all the different pages of the menu
 *
 * @param node the current menu element
 */
void print_page(menu_element* node);

/** @brief Print the marker
 *
 * This function prints the marker at the current page
 */
void print_marker(uint8_t line);
#endif

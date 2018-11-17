#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "menu.h"
#include "oled.h"
#include "spi.h"
#include "mcp2515.h"
#include "can.h"
#include "game.h"
#include "timer.h"

int main(){
    cli();
    USART_Init(MYUBRR);
    MCUCR |= (1<<SRE); //activate XMEM
    //SRAM_test();
    printf("\n\n\n\n\n\n\n");
    can_normal_init();
    oled_init();
    high_score_init();
    sei();
    timer_interrupt_init();
    adc_interrupt_init();
    can_receive_interrupt();

    //Set up menu
    volatile uint8_t* adc = (uint8_t*) 0x1400;
    joystick_direction dir;
    uint8_t K_p;
    uint8_t K_i;
    menu_element* menu_choice = create_menu(); //creating the menu
    printf("#############\n");
    while(1){
      menu_driver(&K_p, &K_i,&dir, &menu_choice,adc); //Updating the menu
    }
    return 0;
}

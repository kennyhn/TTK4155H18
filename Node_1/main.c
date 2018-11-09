#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "menu.h"
#include "oled.h"
#include "spi.h"
#include "mcp2515.h"
#include "can.h"


int main(){
    cli();
    USART_Init(MYUBRR);
    MCUCR |= (1<<SRE); //activate XMEM
    can_normal_init();
    oled_init();
    sei();

    interrupt_int0_init();
    can_message_received = 0;

    //Set up menu
    volatile uint8_t* adc = (uint8_t*) 0x1400;
    joystick_direction dir;
    menu_element* menu_choice = create_menu(); //creating the menu

    //SRAM_test();

    while(1){
      menu_driver(dir, &menu_choice,adc); //Updating the menu
      
      /*if(can_message_received){
          can_message_received = 0;
          rmsg=can_data_receive();
          printf("Message id %d\nMessage length %d \nMessage data %c\n",rmsg.id,rmsg.length,rmsg.data[0]);
      }*/
    }
    return 0;
}

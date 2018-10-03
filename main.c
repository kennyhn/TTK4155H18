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


int main(){
    USART_Init(MYUBRR);
    MCUCR = MCUCR|(1<<SRE); //activate XMEM
    oled_init();
    //menu_driver();
    //SPI_master_init();
    //while(1){
      //SPI_master_transmit('a');
    //}
    mcp2515_init();
    /*SRAM_OLED_reset();
    SRAM_oled_print8(0,0,"Main menu");
    SRAM_writes_to_screen();*/
    return 0;
}

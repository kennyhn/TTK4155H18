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
    //SRAM_test();
    //oled_init();
    //menu_driver();
    //SPI_master_init();
    //while(1){
      //SPI_master_transmit('a');
    //}



    mcp2515_init();
    /*SPI_master_init(); // Initialize SPI
    while(1){
        printf("0x%x\r\n",mcp2515_read(MCP_CANSTAT));
        //mcp2515_reset(); // Send reset-command
        _delay_ms(100);
    }
    /*SRAM_OLED_reset();
    SRAM_oled_print8(0,0,"Main menu");
    SRAM_writes_to_screen();*/
    return 0;
}

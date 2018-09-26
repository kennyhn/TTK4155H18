#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "menu.h"
#include "oled.h"

int main(){
    USART_Init(MYUBRR);
    MCUCR = MCUCR|(1<<SRE); //activate XMEM
    oled_init();
    menu_driver();
    //draw_circle(50,25,20);
    //draw_line(30,30,10,30);
    return 0;
}

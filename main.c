#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "sram.h"
#include "adc.h"


int main(){
    /*DDRA =  0xFF; //Konfig port

    while(1){
        PORTA = 1;
        _delay_ms(2);
        PORTA = 0;
        _delay_ms(2);

    }*/
    //USART_test();
    USART_Init(MYUBRR);
    while(1){
        run_joystick();
    }

    //SRAM_test();
    //GAL_test();
    return 0;
}

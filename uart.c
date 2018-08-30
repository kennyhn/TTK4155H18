#define F_CPU 4915200
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


#include "uart.h"
#include <avr/io.h> 
#include <util/delay.h>


void USART_Init(unsigned int ubrr){ 
    // Set baud rate
    UBRR0H = (unsigned char) (ubrr>>8); 
    UBRR0L = (unsigned char)ubrr;
    // Activate transmitter and receiver
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    // Set frame format: set number of stopbit to 2 and character size to 8 bit 
    UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00); 
}

void USART_Transmit(unsigned char data){
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;

}

unsigned char USART_Receive(void){
    while (!(UCSR0A & (1<<RXC0)));
    return UDR0; 
}

void USART_test(){
    USART_Init(MYUBRR); 
    //_delay_ms(10000);
    while(1){
        USART_Transmit('k');
        //unsigned char k = USART_Receive();
        _delay_ms(2);
    }
    
}
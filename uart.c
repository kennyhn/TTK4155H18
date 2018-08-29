#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


#include "uart.h"
#include <avr/io.h> 

void USART_Init(unsigned int ubrr){
    UBRR0H = (unsigned char) (ubrr>>8); 
    UBRR0L = (unsigned char)ubrr;

    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00); 
}

void USART_Transmit (unsigned char data){
    while (!(UCSRA & (1<<UDRE)));
}

unsigned char USART_Receive(void){
    while (!(UCSRA & (1<<RXC)));
    return UDR; 
}
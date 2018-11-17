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
    UCSR0C = (1<<USBS0) | (3<<UCSZ00); //URSEL MÅ ENDRES

    fdevopen(USART_Transmit,USART_Receive); //For it to work with putty
}

int USART_Transmit(char data, FILE* _notused){
    (void) _notused;
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;

    if (data == '\n'){
        USART_Transmit('\r', NULL);
    }
    return 0;
}

int USART_Receive(FILE* _notused){
    (void) _notused;
    while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
}



void USART_test(){
    USART_Init(MYUBRR);
    //_delay_ms(10000);
    USART_Transmit('A',NULL);
    printf("hei\r\n");
    while(1){
        USART_Transmit(USART_Receive(NULL),NULL);
        //unsigned char k = USART_Receive();
        _delay_ms(2);
    }
}

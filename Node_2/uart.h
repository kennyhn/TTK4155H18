#ifndef UART_H_
#define UART_H_
#include <stdio.h>

#define F_CPU 16000000
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_test();



#endif

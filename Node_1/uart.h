#ifndef UART_H_
#define UART_H_
#include <stdio.h>

#define F_CPU 4915200
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_test();



#endif

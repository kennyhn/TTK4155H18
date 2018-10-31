#ifndef UART_H_
#define UART_H_
#include <stdio.h>

#define F_CPU 4915200
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


void USART_Init(unsigned int ubrr);
int USART_Transmit(char data, FILE* _notused);
int USART_Receive(FILE* _notused);
void USART_test();



#endif

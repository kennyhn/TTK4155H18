#ifndef UART_H_
#define UART_H_
#define F_CPU 16000000
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include <stdio.h>




void USART_Init(unsigned int ubrr);
int USART_Transmit(char data, FILE* _notused);
int USART_Receive(FILE* _notused);
void USART_test();



#endif

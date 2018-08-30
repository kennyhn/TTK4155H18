#ifndef _UART_H_
#define _UART_H_



void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data); 
unsigned char USART_Receive(void);
void USART_test();



#endif
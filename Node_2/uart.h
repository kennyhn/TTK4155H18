/**@file uart.h
 * @brief Functions used to control the use of the USART.
 */
#ifndef UART_H_
#define UART_H_
#define F_CPU 16000000
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
#include <stdio.h>

/** @brief Initiating the USART communication and defining printf.
 */
void USART_Init(unsigned int ubrr);

/** @brief Function that uses USART to transmit from MCU.
 * 
 * @param data Data being transmitted.
 * @param _notused A parameter that is included to get rid of an error occuring when defining the printf.
 */
int USART_Transmit(char data, FILE* _notused);

/** @brief Function that makes the MCU use USART to receive a message.
 * 
 * @param _notused A parameter that is included to get rid of an error occuring when defining the printf.
 * @return int The data received.
 */
int USART_Receive(FILE* _notused);

/** @brief A function used to test if the USART works.
 */
void USART_test();



#endif

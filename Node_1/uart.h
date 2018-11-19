/**@file uart.h
 * @brief functions for initializing, and using UART communication
 */
#ifndef USART_H_
#define USART_H_
#include <stdio.h>

#define F_CPU 4915200
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

/**@brief Initialize the UART
 *
 * Sets the register neccessary to use UART in node 1
 */
void USART_Init(unsigned int ubrr);

/**@brief Transmits the data using UART
 *
 *The data sent can be seen using PuTTy
 */
int USART_Transmit(char data, FILE* _notused);

/**@brief Recieves the data using UART
 *
 *Can send data from PuTTy which node 1 registers.
 */
int USART_Receive(FILE* _notused);

/**@brief A function for testing the UART
 *
 * Using the UART by sending the data back to PuTTy so we see what we have written.
 */
void USART_test();



#endif

/**@file can.h
 * @brief Functions for initializing, sending and recieving data on CAN-bus
 */
#ifndef CAN_H_
#define CAN_H_
#include "mcp2515.h"
#include "spi.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int can_message_received;
int can_allowed_to_send_flag;
typedef struct Can_message{
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
}can_message;

int can_loopback_init();
int can_normal_init();
void can_message_send(can_message* msg);
can_message can_data_receive(void);
void send_console_message(uint8_t K_p,uint8_t K_i);
//void can_error();
uint8_t can_int_vect();
//int can_transmit_complete();

void can_receive_interrupt(void);


#endif

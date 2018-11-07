#ifndef CAN_H_
#define CAN_H_
#include "mcp2515.h"
#include "spi.h"
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int can_message_received;

typedef struct Can_message{
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
}can_message;

int can_loopback_init();
int can_normal_init();
void can_message_send(can_message* msg);
can_message can_data_receive(void);
void send_console_message();
//void can_error();
uint8_t can_int_vect();
//int can_transmit_complete();

void interrupt_int0_init();



#endif

#ifndef _CAN_H_
#define _CAN_H_
#include "mcp2515.h"
#include "spi.h"
#include <avr/io.h>
#include <stdint.h>

typedef struct Can_message{
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
}can_message;

int can_init();
void can_message_send(can_message* msg);
can_message can_data_receive(void);
void can_error();
uint8_t can_int_vect();
int can_transmit_complete();


#endif

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

void can_init();
void can_message_send(can_message* msg);
uint8_t can_data_receive(uint8_t address);
void can_error();
void can_int_vect();
void can_transmit_complete();


#endif

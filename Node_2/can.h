#ifndef CAN_H_
#define CAN_H_
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "../Node_1/adc.h"

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
void receive_console_message(joystick_raw_data* jrd, joystick_direction* jd, slider_raw_data* srd);
//void can_error();
uint8_t can_int_vect();
//int can_transmit_complete();
void interrupt_pcint6_init();



#endif

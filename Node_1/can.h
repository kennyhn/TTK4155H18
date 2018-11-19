/**@file can.h
 * @brief Functions for initializing, sending and recieving data on CAN-bus
 */
#ifndef CAN_H_
#define CAN_H_

#include "spi.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int can_message_received;
int can_allowed_to_send_flag;
typedef struct Can_message{
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
}can_message;

/**@brief Initialize the CAN in loopback mode
 *
 *The message that is sent is "bounced" back. This is used to see if the SPI-bus between the CAN-controller and CAN-tranceiver is correctly setup
 *@return int which is a boolean value saying if the mode is successfully intialized.
 */
int can_loopback_init();

/**@brief Initialize the CAN in normal mode
 *@return int which is a boolean value saying if the mode is successfully intialized.
 */
int can_normal_init();

/**@brief Read the value of the right slider
 *@param msg The can message that is going to be sent over the bus.
 */
void can_message_send(can_message* msg);

/**@brief Function for recieving the data on the CAN-bus
 *@return can_message which is the struct with structure of what information the can message needs to be sent
 */
can_message can_data_receive(void);

/**@brief Function for sending multiboard data to node 2
 *
 *In this function the message containing the x-axis of the joystick data, right slider data and information if the joystick button is pressed.
 *The can-message is made and sent over the bus with a frequency of 20Hz.
 *@param K_p the gain for P-part of the regulator
 *@param K_i the gain for I-part of the regulator
 */
void send_console_message(uint8_t K_p,uint8_t K_i);

/**@brief Check if the interrupt flag is set for the CAN-bus
 */
uint8_t can_int_vect();

/**@brief Set up external interrupt for the CAN-bus.
 *
 *In this function we set up the external interrupt such that we get an interrupt when the CAN-tranceiver gets an incoming message.
 */
void can_receive_interrupt_init(void);


#endif

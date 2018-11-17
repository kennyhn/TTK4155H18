/**@file can.h
 * @brief Functions running and operating this can node.
 */
#ifndef CAN_H_
#define CAN_H_
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "../Node_1/adc.h"

int can_message_received;

/**@brief The can message struct that contain ID, data and the number of data elements.
 */
typedef struct Can_message{
    unsigned int id;
    uint8_t length;
    uint8_t data[8];
}can_message;


/**@brief Initialising the can controller to loopback mode.
 */
int can_loopback_init();

/**@brief Initialising the can controller to normal mode.
 */
int can_normal_init();

/**@brief Transmit the can message @param msg.
 *
 * @param msg Message that is being sent.
 */
void can_message_send(can_message* msg);

/**@brief Receives a can message and clears interrupt flag.
 *
 * @return can_message The can message received.
 */
can_message can_data_receive(void);

/**@brief Receives the can message and splits it up to usable formats.
 *
 * The values are returned through the parameter pointers.
 */
void receive_console_message(joystick_raw_data* jrd, joystick_direction* jd, slider_raw_data* srd);

/**@brief Functu\ion that returns all the can interrupt flags.
 *
 * @return uint8_t the 8 different interupt flags.
 */
uint8_t can_int_vect();

/**@brief Function that initialises the receive interupt we are using.
 */
void can_interrupt_init();
#endif

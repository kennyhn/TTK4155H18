/**@file motor.h
 * @brief Functions controlling the motor and the encoder.
 */
#ifndef MOTOR_H_
#define MOTOR_H_
#include "../Node_1/adc.h"

uint8_t motor_set;

/**@brief Initiating the motor and the encoder.
 */
void motor_init(void);

/**@brief Function setting the motor velocity and direction.
 */
void motor_driver(int16_t motor_value);

/**@brief Setting the encoder absolute zero to the current placement of the motor.
 */
void reset_encoder();

/**@brief Reads the current encoder value.
 */
int16_t read_encoder();

/**@brief Function transforming encoder data to number in the area of 0 to 255.
 */
int16_t transform_encoder_to_position(int16_t encoder_data);

/**@brief Function used in the start up, to ensure zero to the left of motor board.
 */
void set_motor_start_point();
#endif

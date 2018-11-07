#ifndef MOTOR_H_
#define MOTOR_H_
#include "../Node_1/adc.h"



void motor_init(void);
void motor_driver(int8_t motor_value);
void reset_encoder();
int16_t read_encoder();
uint8_t transform_encoder_to_position(int16_t encoder_data);
#endif

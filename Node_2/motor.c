#include "motor.h"
#include "TWI_Master.h"
#include "uart.h"
#include <util/delay.h>
#include <avr/io.h>

void motor_init(void){
  DDRH |= (1<<DDH1); //setting PH1-motor direction to output
  DDRH |= (1<<DDH4); //setting PH4 - motorenable to output
  PORTH |= (1<<PH4); //enables motor
  //Encoder init
  DDRH |= (1<<DDH6); //setting PH6 - !RST to output
  PORTH |= (1<<PH6); //enables the encoder to count (not reseting)
  DDRH |= (1<<DDH5); //setting PH5 - !OE to output
  //PORTH &= ~(1<<PH5); //enabling output by setting low
  DDRH |= (1<<DDH3); //setting PH3 - SEL to output
  DDRK = 0x00;//Setting the encoder input pins to input
  /*DDRK &= ~(1<<DDK0);
  DDRK &= ~(1<<DDK1);
  DDRK &= ~(1<<DDK2);
  DDRK &= ~(1<<DDK3);
  DDRK &= ~(1<<DDK4);
  DDRK &= ~(1<<DDK5);
  DDRK &= ~(1<<DDK6);
  DDRK &= ~(1<<DDK7);*/
}

void reset_encoder(){ // can possibly use this in the start-up
  PORTH &= ~(1<<DDH6); //reseting encoder
  _delay_us(20);
  PORTH |= (1<<DDH6); //enables the encoder to count (not reseting)
}

int16_t transform_encoder_to_position(int16_t encoder_data){
  //printf("Encoder data: %d\n",encoder_data);
  int16_t data = encoder_data/(-8000.0)*255;
  return data;
}

int16_t read_encoder(){
  int16_t data = 0x0000;
  PORTH &= ~(1<<PH5); //enable output !OE
  PORTH &= ~(1<<PH3); //setting SEL low (MSB)
  _delay_us(20);
  data |= (PINK << 8);

  PORTH |= (1<<PH3); //setting SEL high (LSB)
  _delay_us(20);
  data |= PINK;
  PORTH |= (1<<PH5); //disable output !OE
  return data;
}

void motor_driver(int16_t motor_value){
  if(motor_value>0){
      PORTH |= (1<<PH1); //setting motor direction right
  }
  else if (motor_value<0){
      PORTH &= ~(1<<PH1); //setting motor direction left
  }
  unsigned char address = 0x50; //01010000 selecting MAX520
  unsigned char command = 0x00; //selecting DAC0
  unsigned char output = (unsigned char)abs(motor_value);
  unsigned char msg[3]={address,command,output};
  TWI_Start_Transceiver_With_Data(msg,3);
}

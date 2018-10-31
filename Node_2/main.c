#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "mcp2515.h"
#include "can.h"

int main(){
  //can_message_received = 0;
  USART_Init(MYUBRR);
  interrupt_pcint6_init();
  can_message_received = 0;
  printf("%d",can_message_received);
  //printf("Hei\n");
  //SPI_master_init();
  //while(1){
    //SPI_master_transmit('a');
  //}

  /*SPI_master_init(); // Initialize SPI
  while(1){
      printf("0x%x\r\n",mcp2515_read(MCP_CANSTAT));
      //mcp2515_reset(); // Send reset-command
      _delay_ms(100);
  }
  */
  mcp2515_init();
  can_normal_init();
  //can_message message;
  can_message rmsg;
  /*message.id = 1;
  message.length = 1;
  message.data[0] = (uint8_t)'K';
  can_message_send(&message);
  while(1){
    _delay_ms(10);
    rmsg=can_data_receive();
    printf("Message id %d\nMessage length %d \nMessage data %c\n",rmsg.id,rmsg.length,rmsg.data[0]);
  }*/

  joystick_direction jd;
  joystick_perc_angle jpa;

  while(1){
    if(can_message_received){
        can_message_received = 0;
        receive_joystick_message(&jpa,&jd);
        //printf("Message id %d\nMessage length %d \nMessage data %c\n", rmsg.id,rmsg.length,rmsg.data[0]);
    }
    printf("Joystick percent angle X %d\nJoystick percent angle Y%d\nJoystick direction%d", jpa.X_value, jpa.Y_value, jd);
  }
  return 0;
}

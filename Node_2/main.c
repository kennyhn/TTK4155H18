#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "mcp2515.h"
#include "can.h"
#include "pwm.h"
#include "adc_arduino.h"
#include "TWI_Master.h"
#include "motor.h"


int main(){
  USART_Init(MYUBRR);

  interrupt_pcint6_init();
  position_reference=0;
  total_e = 0;
  can_message_received = 0;
  cli();
  adc_init();
  can_normal_init();
  pwm_init();
  TWI_Master_Initialise();
  motor_init();
  sei();
  timer_interrupt_init();
  //printf("%d",can_message_received);
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
  joystick_raw_data jrd;
  slider_raw_data srd;

  reset_encoder();

  while(1){

    if(can_message_received){
        can_message_received = 0;
        //Let CAN be driven outside this function
        receive_console_message(&jrd,&jd, &srd);
        //TBD
        //Mottar joystick-meldingen i main. Sender kun inn X_value til pwm_driver og ikke hele meldingen
        pwm_driver(jrd.X_value);
        position_reference=srd.right_slider_value;
        //printf("Position reference: %d \n", position_reference);
        solenoid_control(jrd.button_pressed);
        printf("%d\n", jrd.button_pressed);
        //motor_driver(jrd.X_value-128);
        //receive_joystick_message(&jpa,&jd);
        //printf("Message id %d\nMessage length %d \nMessage data %c\n", rmsg.id,rmsg.length,rmsg.data[0]);
    }
    uint16_t data = adc_read();
    //printf("Data = %d \n", data);
  }
  return 0;
}

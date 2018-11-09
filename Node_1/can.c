#include "can.h"
#include "mcp2515.h"
#include "adc.h"

int can_loopback_init(){
  if (mcp2515_init()){ //Setup mcp while checking if it is set up right
    return 1; //If mcp2515 is not set up right
  } //mulig vi må legge inn en while løkke her
  mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK); //Changing CAN to loopback mode
  if (!(mcp2515_read(MCP_CANSTAT) & MODE_LOOPBACK)){
    printf("The CAN is NOT in loopback mode\n");
    return 1;
  }
  printf("The CAN is in loopback mode\n");

  //Enable interrupts must be cleared by MCU to reset interrupt condition
  //mcp2515_write(MCP_CANINTE, MCP_TX_INT); //Enable transmit interrupts pin
  mcp2515_write(MCP_CANINTE, MCP_RX_INT); //enable recieve interrupts

  mcp2515_write(MCP_TXB0CTRL,0); //Make channel 0-2 ready to transmit message, setting all the transmit message flags to 0
  mcp2515_write(MCP_TXB1CTRL,0);
  mcp2515_write(MCP_TXB2CTRL,0);
  return 0;
}

int can_normal_init(){
  if (mcp2515_init()) //Setup mcp while checking if it is set up right
    return 1; //If mcp2515 is not set up right
  mcp2515_write(MCP_CNF1, 0x03);
  mcp2515_write(MCP_CNF2, 0x9A);
  mcp2515_write(MCP_CNF3, 0x07);

  mcp2515_write(MCP_CANCTRL, MODE_NORMAL); //Changing CAN to normal mode
  if ((mcp2515_read(MCP_CANSTAT) & MODE_MASK) != MODE_NORMAL){
    printf("The CAN is NOT in normal mode\n");
    return 1;
  }
  printf("The CAN is in normal mode\n");

  //Enable interrupts must be cleared by MCU to reset interrupt condition
  mcp2515_write(MCP_CANINTE, MCP_RX_INT); //enable recieve interrupts

  mcp2515_write(MCP_TXB0CTRL,0); //Make channel 0-2 ready to transmit message, setting all the transmit message flags to 0
  mcp2515_write(MCP_TXB1CTRL,0);
  mcp2515_write(MCP_TXB2CTRL,0);
  return 0;
}

void can_message_send(can_message* message){
  //while (!can_transmit_complete());

  //Splitting id into higher and lower MSBs/LSBs
  unsigned id_high = message->id & 0b11111111000;
  unsigned id_low = message->id & 0b00000000111;
  id_low = id_low << 5;
  id_high = id_high >> 3;
  mcp2515_write(MCP_TXB0SIDH, id_high); //writing to TXB0SIDH, setting higher part address
  mcp2515_write(MCP_TXB0SIDL, id_low); //writing to TXB0SIDL, setting lower part address

  //Setting the data length, 4 lowest is 1
  mcp2515_write(MCP_TXB0DLC, message->length);

  //Sending data
  for(uint8_t i = 0; i < message->length; i++){
    mcp2515_write(MCP_TXB0D0+i, message->data[i]);
  }
  //Initiate transmission
  mcp2515_request_to_send(0x01);
  int i=0;
  //Interrupt check
  while(!(mcp2515_read_status() & MCP_TX0IF));
}


can_message can_data_receive(void){
  can_message message;
  while(!(mcp2515_read_status() & MCP_RX0IF));
  if(mcp2515_read_status() & MCP_RX0IF){
    message.id = (mcp2515_read(MCP_RXB0SIDH) << 3 | mcp2515_read(MCP_RXB0SIDL) >> 5);
    message.length = (0x0F) & mcp2515_read(MCP_RXB0DLC);

    for(uint8_t i = 0; i < message.length; i++){
      message.data[i] = mcp2515_read(MCP_RXB0D0+i);
    }
    mcp2515_write(MCP_CANINTF, mcp2515_read_status() & 0xFE); //disable interrupt flag
    return message;
  }
  message.id = 0;
  return message;
}

void send_console_message(){
  //send joystick joystick direction
  MCUCR = MCUCR|(1<<SRE); //activate XMEM
  volatile uint8_t* adc = (uint8_t*)0x1400;
  joystick_direction jd = check_joystick_direction(adc);
  //joystick_perc_angle jpa = get_perc_angle(adc);
  /*using raw data for greater resolution*/
  joystick_raw_data jrd;
  slider_raw_data srd;
  joystick_x_axis(adc);
  jrd.X_value = *adc;
  joystick_y_axis(adc);
  jrd.Y_value = *adc;
  l_slider(adc);
  srd.left_slider_value = *adc;
  r_slider(adc);
  srd.right_slider_value = *adc;

  jrd.button_pressed = (PINB & (1<<PB2));

  can_message msg;
  msg.id = 10;
  msg.length = 6; //6 når vi får med knappen
  msg.data[0]=jrd.X_value;
  msg.data[1]=jrd.Y_value;
  msg.data[2]=jrd.button_pressed;
  msg.data[3]=(uint8_t)jd;
  msg.data[4]=srd.left_slider_value;
  msg.data[5]=srd.right_slider_value;
  //printf("her er x-value %d \n", (int8_t)msg.data[0]);
  can_message_send(&msg);
}

//Check if there is an interrupt in CAN-controller
uint8_t can_int_vect(){
  return mcp2515_read(MCP_CANINTF);
}
/*
int can_transmit_complete(uint8_t buffer){
  return ;//return 1 when the transmit is complete
}*/

void interrupt_int0_init(void){
  //  Set pin to input
  DDRD &= ~(1<<PD2);
  // Disable global interrupts
  cli();
  //Interrupt on rising edge PD2
  MCUCR |= (1<<ISC01);
  MCUCR &= ~(1<<ISC00);
  //Enable interrupt on PD2
  GICR |= (1<<INT0);

  //Enable global interrupts
  sei();

}

ISR(INT0_vect){
  can_message_received = 1;
}

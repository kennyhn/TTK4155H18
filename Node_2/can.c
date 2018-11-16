#include "can.h"
#include "mcp2515.h"
#include "spi.h"
#include "pwm.h"

int can_loopback_init(){
  mcp2515_init(); //setup mcp
  mcp2515_write(MCP_CANCTRL, MODE_LOOPBACK); //Changing CAN to loopback mode
  while(!(mcp2515_read(MCP_CANSTAT) & MODE_LOOPBACK));
  printf("The CAN is in loopback mode\n");

  //Enable interrupts must be cleared by MCU to reset interrupt condition
  mcp2515_write(MCP_CANINTE, MCP_RX_INT); //enable recieve interrupts

  mcp2515_write(MCP_TXB0CTRL,0); //Make channel 0-2 ready to transmit message, setting all the transmit message flags to 0
  mcp2515_write(MCP_TXB1CTRL,0);
  mcp2515_write(MCP_TXB2CTRL,0);
  return 0;
}

int can_normal_init(){
  mcp2515_init(); //setup mcp
  mcp2515_write(MCP_CNF1, 0x03);
  mcp2515_write(MCP_CNF2, 0x9A);
  mcp2515_write(MCP_CNF3, 0x07);
  mcp2515_bit_modify(MCP_RXB0CTRL, 0x60, 0x00);
  mcp2515_write(MCP_CANCTRL, MODE_NORMAL); //Changing CAN to loopback mode
  while((mcp2515_read(MCP_CANSTAT) & MODE_MASK) != MODE_NORMAL);
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
  while(!(can_int_vect() & MCP_RX0IF));
  can_message_received=0;
  if(mcp2515_read_status() & MCP_RX0IF){
    message.id = (mcp2515_read(MCP_RXB0SIDH) << 3 | mcp2515_read(MCP_RXB0SIDL) >> 5);
    message.length = (0x0F) & mcp2515_read(MCP_RXB0DLC);

    for(uint8_t i = 0; i < message.length; i++){
      message.data[i] = mcp2515_read(MCP_RXB0D0+i);
    }
    mcp2515_write(MCP_CANINTF, mcp2515_read_status() & 0xFE); //clear interrupt flag
    return message;
  }
  message.id = 0;
  return message;
}


void receive_console_message(joystick_raw_data* joystick_data, joystick_direction* joystick_dir, slider_raw_data* slider ){
  can_message console_message;
  console_message=can_data_receive();
  joystick_data->X_value=console_message.data[0];
  joystick_data->button_pressed=console_message.data[1];
  slider->right_slider_value=console_message.data[2];
  K_p = console_message.data[3];
  K_i = console_message.data[4];
}

//Check if there is an interrupt in CAN-controller
uint8_t can_int_vect(){
  return mcp2515_read(MCP_CANINTF);
}

void can_interrupt_init(void){
  //  Set pin to input
  DDRB &= ~(1<<PB6);
  // Disable global interrupts
  cli();

  //Enable interrupt on PB6, both lines needed since this is an external interrupt
  PCMSK0 |= (1<<PCINT6);
  PCICR |= (1<<PCIE0);

  //Enable global interrupts
  sei();

  can_message_received = 0;
}

ISR(PCINT0_vect){
  can_message_received = 1;
}

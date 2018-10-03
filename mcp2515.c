#include "mcp2515.h"
#include "spi.h"
#include <avr/io.h>

uint8_t mcp2515_init(){
  uint8_t value;
  SPI_master_init(); // Initialize SPI
  mcp2515_reset(); // Send reset-command
  // Self-test
  value = mcp2515_read(MCP_CANSTAT);
  if ((value & MODE_MASK) != MODE_CONFIG) {
    printf("MCP2515 is NOT in configuration mode after reset!\n");
    return 1;
  }
  // More initialization
  return 0;
}

void mcp2515_reset(){
  PORTB &= ~(1<<4); //Select CAN-controller
  SPI_master_transmit(MCP_RESET);
  PORTB |= (1<<4); //deselect CAN-controller
}

uint8_t mcp2515_read(uint8_t address){
  uint8_t result;
  PORTB &= ~(1<<4); //CAN_CS // Select CAN-controller
  SPI_master_transmit(MCP_READ); // Send read instruction
  SPI_master_transmit(address); // Send address
  result = SPI_receive(); // Read result
  PORTB |= (1<<4); // Deselect CAN-controller
  return result;
}




void mcp2515_write(uint8_t address, uint8_t data){
  PORTB &= ~(1<<4); //select CAN-controller
  SPI_master_transmit(MCP_WRITE); //Send write instruction
  SPI_master_transmit(address); //send addresses
  SPI_master_transmit(data); //send data
  PORTB |= (1<<4); // Deselect CAN-controller

}

void mcp2515_request_to_send(uint8_t command){
  command|=(1<<8); //These two lines are setting 10000xxx
  command&= ~(0xF<<3); //The tree lsb indicate which transmit buffers are enabled to send
  PORTB&=~(1<<4); //Select CAN-controller
  SPI_master_transmit(command);
  PORTB |= (1<<4); //deselect CAN-controller?

}
uint8_t mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
  PORTB&= ~(1<<4);//select can-controller
  SPI_master_transmit(MCP_BITMOD);
  SPI_master_transmit(address);
  SPI_master_transmit(mask);
  SPI_master_transmit(data);
  PORTB|=(1<<4); //Deselect can-controller
  return mcp2515_read(address); //returnerer resultatet fra bitmodifiseringen
}

uint8_t mcp2515_read_status(){
  uint8_t result;
  PORTB&=~(1<<4);
  SPI_master_transmit(MCP_READ_STATUS);
  result=SPI_receive();
  PORTB|=(1<<4);
  return result;
}

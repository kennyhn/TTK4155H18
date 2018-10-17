#include "spi.h"

void SPI_master_init(void){
  /* Set MOSI and SCK output and slave select to output, all others input */
  DDRB = (1<<DDB5)|(1<<DDB7) | (1<<DDB4);
  //Set MISO as input pin
  DDRB &= ~(1<<DDB6);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
  //SPCR |= ;

  PORTB |= (1<<4); //SS high
}

//Spi_write
void SPI_master_transmit(char cData){
  /* Start transmission */
  SPDR = cData;
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));
}

//Spi_read
char SPI_master_receive(void){
  SPI_master_transmit(0);
  /* Wait for reception complete */
  while(!(SPSR & (1<<SPIF)));
  /* Return data register */
  return SPDR;
}

#include "adc_node2.h"

void adc_init(void){
  //Using channel 0 (Clear MUX0 - MUX4 bits)
  ADMUX &= ~(0x1F);
  ADCSRB &= ~(0x08);
  //Enable adc
  ADCSRA |= (1<<ADEN);

  //Set prescale to 128 (arduino ADC-standard)
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

  //Set voltage reference to AVCC
  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<REFS1);
}

uint16_t adc_read(void){
    //Starting conversion
    ADCSRA |= (1<<ADSC);
    //Check if the conversion is complete
    while(!(ADCSRA&(1<<ADIF)));
    //Read the conversion
    uint16_t data_low = ADCL;
    uint16_t data_high = (ADCH<<8);
    uint16_t data = data_high | data_low;
    return data;
}

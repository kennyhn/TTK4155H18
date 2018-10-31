#include "adc.h"

void adc_init(){
//Using channel 0 (Clear MUX0 - MUX4 bits)
ADMUX &= ~(0x1F);
//Enable adc
ADCSRA |= (1<<ADEN);

//Set prescale to 128 (arduino ADC-standard)
//ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

//Set voltage reference to AVCC

ADMUX |= (1<<REFS0);
ADMUX &= ~(1<<REFS1);


}

uint16_t adc_read(){


    //ADMUX |= (1<<MUX0);
    //Starting conversion
    ADCSRA |= (1<<ADSC);
    ADMUX |= (1<<REFS0);
    //Check if the conversion is complete (feilsøk denne først, mulig det må endres til et annet register/fjernes)
    while(!(ADCSRA&(1<<ADIF)));
    //Read the conversion
    uint16_t data_low = ADCL;
    uint16_t data_high = (ADCH<<8);
    uint16_t data = data_high | data_low;
    return data;
}

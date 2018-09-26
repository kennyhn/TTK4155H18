#define F_CPU 4915200
#include <util/delay.h>

#include "sram.h"
#include <avr/io.h>



void SRAM_test(void){
    volatile char *ext_ram = (char *) 0x1800; //Start adress for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    //MCUCR = MCUCR|(1<<SRE); //activate XMEM
    printf("Starting SRAM test... \n");

    uint16_t seed = rand();
    // Write phase: immediately check that the correct value was stored
    // Rand - different seeds each time
    srand(seed);
    for (uint16_t i = 0; i < ext_ram_size; i++){
        uint8_t some_value = rand();
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value){
            printf("\nWrite phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
            write_errors++;
        }
    }
    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed); //Reset the PRNG to the state it had before the write phase
    for (uint16_t i = 0; i < ext_ram_size; i++){
        uint8_t some_value = rand();
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value){
            printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i, retreived_value, some_value);
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase \n\n", write_errors, retrieval_errors);
}


/*void LATCH_test(void){
    DDRE = 0x02; //For å sette dde1, som er latch enable
    DDRA =  0xFF; //Port A data register - må sette alle til 1 for write-modus
    PORTE = 0x00;
    PORTA = 0xBF;
    //PORTA = 0x00;
    _delay_ms(1000);
    PORTE = 0x2;
    _delay_ms(1000);
    PORTE = 0x00;
    PORTA = 0x00;

*/



    /*while(1){
        PORTA = 1;
        _delay_ms(2);
        PORTA = 0;
        _delay_ms(2);

    }
}*/

void GAL_test(void){
    DDRC |= (0b111<<DDC1); //Setter DDC1-3 til write-modus
    PORTC &= (!(1<<PORTC3));
    PORTC |= (1<<PORTC2);
    DDRD |= (1 << DDD7);
    PORTD &= (!(1<<PORTD7));

}

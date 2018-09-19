#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>

#include "oled.h"
#include "fonts.h"

volatile char *oled_command = (char*) 0x1000;
volatile char *oled_data = (char*) 0x1200;

void write_c(char data){
    *oled_command = data;
}

void oled_reset(void){
    *oled_command=0x00;//setting lower start column
    *oled_command=0x10;//setting upper start column
    //*oled_command=0x40; //setinng display start line
    for (int i = 0; i <8;i++){
        *oled_command=0xb0+i;//setting start page0
        for(int j = 0; j<128;j++){
            *oled_data = 0x00;
        }
    }

}

void oled_init(){
    MCUCR = MCUCR|(1<<SRE); //activate XMEM

    write_c(0xae);        //  display  off
    write_c(0xa1);        //segment  remap
    write_c(0xda);        //common  pads  hardware:  alternative
    write_c(0x12);
    write_c(0xc8);        //common  output scan direction:com63~com0
    write_c(0xa8);        //multiplex  ration  mode:63
    write_c(0x3f);
    write_c(0xd5);        //display divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81);        //contrast  control
    write_c(0x50);
    write_c(0xd9);        //set  pre-charge  period
    write_c(0x21);
    write_c(0x20);        //Set  Memory  Addressing  Mode
    write_c(0x02);
    write_c(0xdb);        //VCOM  deselect  level  mode
    write_c(0x30);
    write_c(0xad);        //master  configuration
    write_c(0x00);
    write_c(0xa4);        //out  follows  RAM  content
    write_c(0xa6);        //set  normal  display
    write_c(0xaf);        //  display  on

    oled_reset();
}

void oled_write_character_font8(char letter){
    char letterline = letter - ' ';
    for(int i = 0; i<8; i++){
        *oled_data=pgm_read_byte(&font8[letterline][i]);
    }
}

void oled_home();
void oled_goto_line(uint8_t line){
    *oled_command=0xb0+line;//setting start page to line
}
void oled_goto_column(uint8_t column){
    *oled_command=(0x0F&column);
    *oled_command=(0x10|(column>>4));
}

void oled_clear_line(uint8_t line){
    *oled_command=0x00;//setting lower start column
    *oled_command=0x10;//setting upper start column
    //*oled_command=0x40;//setting display start line
    *oled_command=0xb0+line;//setting start page0
    for(int j = 0; j<128;j++){
        *oled_data = 0x00;
    }
}

void oled_pos(uint8_t row, uint8_t column) {
    oled_goto_column(column);
    oled_goto_line(row);
}

void oled_print(char* word){
    char letterline = letter - ' ';
    for(int i = 0; i<8; i++){
        *oled_data=pgm_read_byte(&font8[letterline][i]);
    }

}

void oled_driver(void){
    oled_init();
    oled_reset();
    *oled_command=0x00;//setting lower start column
    *oled_command=0x10;//setting upper start column
    //*oled_command=0x40;//setting display start line
    oled_goto_column(63);
    oled_goto_line(5);//setting start page0
    oled_write_character_font8('a');
}

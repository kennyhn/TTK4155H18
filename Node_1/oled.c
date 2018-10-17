#define F_CPU 4915200
#include <util/delay.h>
#include <avr/io.h>
#include <math.h>

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


/*void oled_write_character_font8(char letter){
    char letterline = letter - ' ';
    for(int i = 0; i<8; i++){
        *oled_data=pgm_read_byte(&font8[letterline][i]);
    }
}*/

void SRAM_oled_write_character_font8(uint8_t line, uint8_t column, char letter){
    char letterline = letter - ' ';
    for(int i = 0; i<8; i++){
        SRAM_write_to_mem(line,column+i,pgm_read_byte(&font8[letterline][i]));
    }
}

/*void oled_write_character_font5(char letter){
    char letterline = letter - ' ';
    for(int i = 0; i<5; i++){
        *oled_data=pgm_read_byte(&font5[letterline][i]);
    }
}*/


void SRAM_oled_write_character_font5(uint8_t line, uint8_t column, char letter){
    char letterline = letter - ' ';
    for(int i = 0; i<5; i++){
        SRAM_write_to_mem(line,column+i,pgm_read_byte(&font5[letterline][i]));
    }
}

/*void oled_write_character_font4(char letter){
    char letterline = letter - ' ';
    for(int i = 0; i<4; i++){
        *oled_data=pgm_read_byte(&font4[letterline][i]);
    }
}*/


void SRAM_oled_write_character_font4(uint8_t line, uint8_t column, char letter){
    char letterline = letter - ' ';
    for(int i = 0; i<4; i++){
        SRAM_write_to_mem(line,column+i,pgm_read_byte(&font4[letterline][i]));
    }
}
// Må lage nye write funksjoner for SRAM her som funker til menyen


void oled_goto_line(uint8_t line){ //0-7 lines/pages
    *oled_command=0xb0+line;//setting start page to line
}
void oled_goto_column(uint8_t column){ //0-127 columns
    *oled_command=(0x0F&column); //setting lower column to the column number
    *oled_command=(0x10|(column>>4)); //setting upper column to the column number
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

/*void oled_print4(char* word){
    for(int i = 0; word[i]!='\0';i++){
        oled_write_character_font4(word[i]);
    }
}*/


void SRAM_oled_print4(uint8_t line, uint8_t column, char* word){
    for(int i = 0; word[i]!='\0';i++){
        SRAM_oled_write_character_font4(line, column+i*4, word[i]);
    }
}

/*void oled_print5(char* word){
    for(int i = 0; word[i]!='\0';i++){
        oled_write_character_font5(word[i]);
    }
}*/


void SRAM_oled_print5(uint8_t line, uint8_t column, char* word){
    for(int i = 0; word[i]!='\0';i++){
        SRAM_oled_write_character_font5(line, column+i*5, word[i]);
    }
}

/*void oled_print8(char* word){
    for(int i = 0; word[i]!='\0';i++){
        oled_write_character_font8(word[i]);
    }
}*/

void SRAM_oled_print8(uint8_t line, uint8_t column,char* word){
    for(int i = 0; word[i]!='\0';i++){
        SRAM_oled_write_character_font8(line, column+i*8, word[i]);
    }
}
void draw_circle(uint8_t x0, uint8_t y0, uint8_t r){
    for(uint8_t x = x0-r; x<= x0 + r; x++){
        uint8_t y = sqrt(pow(r,2)-pow((x-x0),2)) + y0;
        print_pixel(x,y);
        y = -sqrt(pow(r,2)-pow((x-x0),2)) + y0;
        print_pixel(x,y);

    }
    for(uint8_t y = y0-r; y<= y0 + r; y++){
        uint8_t x = sqrt(pow(r,2)-pow((y-y0),2)) + x0;
        print_pixel(x,y);
        x = -sqrt(pow(r,2)-pow((y-y0),2)) + x0;
        print_pixel(x,y);
    }
    SRAM_writes_to_screen();
}

void draw_line(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2){
    double a = (y2-y1) / (double)(x2-x1);
    if(a < 1){
        for (int x = x1; x<x2 +1; x++){
            int y = a*(x-x1) + y1;
            print_pixel(x,y);
        }
    }
    else{
        for (int y = y1; y<y2 +1; y++){
            int x = 1/a*(y-y1) + x1;
            print_pixel(x,y);
        }
    }
    SRAM_writes_to_screen();
}

void print_pixel(uint8_t x, uint8_t y){
    uint8_t row = y/8;
    uint8_t column = x;
    //oled_pos(row,column);
    //*oled_data |=(1<<(y%8));
    SRAM_write_to_mem(row,column,SRAM_read_oled_data(row,column)|(1<<(y%8)));
}

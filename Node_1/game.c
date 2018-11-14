#include "game.h"
#include "can.h"
#include "oled.h"
#include "uart.h"
#include "sram.h"
#include <util/delay.h>


#define HIGH_SCORE_LENGTH 3 //CONSTANT

uint8_t play_game(void){
  uint8_t x0 = 8;
  uint8_t y0 = 8;
  uint8_t r0 = 8;

  uint8_t x1 = 24;
  uint8_t y1 = 24;
  uint8_t r1 = 6;

  uint8_t x2 = 40;
  uint8_t y2 = 40;
  uint8_t r2 = 6;

  uint8_t x3 = 56;
  uint8_t y3 = 56;
  uint8_t r3 = 6;
  uint8_t high_score;
  while(1){

    //Dette gjøres for å ikke få uforventet brudd pga game-over verdien blir liggende igjen.
    if (can_message_received){

      can_message_received = 0;
      can_message rmsg = can_data_receive();
      printf("melding mottatt\n");
      high_score = rmsg.data[0];
      printf("Highscore play game: %d\n",high_score);
      _delay_ms(600); //this might possibly need to be bigger or smaller
      if (can_message_received){
        printf("reset flag \n");
        can_message_received = 0;
        can_data_receive();
      }
      printf("Everything's good\n");
      return high_score;
    }
    SRAM_OLED_reset();

    draw_circle(x0,y0,r0);
    draw_line(x0-2,x0+2, y0+2, y0+2);
    draw_line(x0+1,x0+2, y0-2,y0-2);
    draw_line(x0-2,x0-1, y0-2,y0-2);
    draw_circle(x1,y1,r1);
    draw_circle(x2,y2,r2);
    draw_circle(x3,y3,r3);
    printf("spiller\n");
    send_console_message();
    x0+=3;
    x1+=3;
    x2+=3;
    x3+=3;
    if (x0 >= 120){
      x0 = 8;
    }
    if (x1 >= 120){
      x1 = 8;
    }
    if (x2 >= 120){
      x2 = 8;
    }
    if (x3 >= 120){
      x3 = 8;
    }
  }
  return 0;
}


void high_score_init(void){
  volatile char *ext_ram = (char *) 0x1800;
  for (int i = 0; i<HIGH_SCORE_LENGTH; i++){
    ext_ram[i]=0;
  }
}

void save_high_score(uint8_t value){
  volatile char *ext_ram = (char *) 0x1800; //Start adress for the SRAM
  /*using address space 0x1800 to 0x1809*/
  uint8_t temp_high_score[HIGH_SCORE_LENGTH];
  uint8_t is_value_added = 0;
  //uint8_t temp;
  for (int i = 0; i<HIGH_SCORE_LENGTH; i++) {
    if((uint8_t)ext_ram[i]>=value || is_value_added){
      if (!is_value_added){
        temp_high_score[i]=(uint8_t)ext_ram[i]; //adding the highest score first
      }
      else {
        temp_high_score[i]=(uint8_t)ext_ram[i-1]; //after the value is added, we need to add the rest of the high scores
      }
    }
    else if ((uint8_t)ext_ram[i]<value && !is_value_added){
        //temp = ext_mem[i];
        temp_high_score[i]=value; //when the value is higher than the other high scores it is added
        //value = temp;
        is_value_added=1;
    }
  }
  for (int i = 0; i<HIGH_SCORE_LENGTH; i++){
    ext_ram[i]=temp_high_score[i]; //update high score in SRAM
    printf("temp high: %d\n", temp_high_score[i]);
  }

}

void print_high_score(void){
  volatile char* ext_ram = (char *) 0x1800; //Start address of SRAM
  SRAM_oled_print8(0,0,"High score");
  draw_line(0,127,10,10);

  for (int i = 0; i<HIGH_SCORE_LENGTH; i++){
    char highscore[4];
    char placement = '1'+i;
    uint8_t highscore_value = (uint8_t)ext_ram[i];
    snprintf(highscore,4,"%d",highscore_value);

    /******************Create the C-string**************/
    char print_to_screen[7];
    print_to_screen[0]=placement;
    print_to_screen[1]='.';
    print_to_screen[2]=' ';
    for (int j=0;j<3;j++){
      print_to_screen[j+3]=highscore[j];
    }
    print_to_screen[6]='\0';
    /**************Create the C-string****************/


    SRAM_oled_print5(2+i,0,print_to_screen);
  }
  SRAM_writes_to_screen();
}

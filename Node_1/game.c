#include "game.h"
#include "can.h"
#include "oled.h"
#include "uart.h"
#include "sram.h"
#include <util/delay.h>


#define HIGH_SCORE_LENGTH 3 //CONSTANT

uint8_t play_game(uint8_t K_p,uint8_t K_i){
  highscore = 0;
  while(1){
    if (can_message_received){
      can_message_received = 0;
      can_data_receive();
      _delay_ms(100); //this might possibly need to be bigger or smaller
      if (can_message_received){
        can_message_received = 0;
        can_data_receive();
      }
      return highscore;
    }
    send_console_message(K_p,K_i);
    print_game_screen();
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
        temp_high_score[i]=value; //when the value is higher than the other high scores it is added
        is_value_added=1;
    }
  }
  for (int i = 0; i<HIGH_SCORE_LENGTH; i++){
    ext_ram[i]=temp_high_score[i]; //update high score in SRAM
  }

}

void print_score(void){
  SRAM_oled_print8(0,0,"Score");
  //SRAM_oled_print8(5,3, highscore); need to convert uint8_t to char*
  char gamescore[4];
  snprintf(gamescore,4,"%d",highscore);
  SRAM_oled_print8(3,60,gamescore);
  SRAM_oled_print5(5,0,"Skriv inn navn i putty: ");

  if(highscore>40){
    SRAM_oled_print8(7,0,"You're a nerd!");
  }
  else if (highscore>20){
    SRAM_oled_print8(7,0, "You're average!");
  }
  else{
      SRAM_oled_print8(7,0, "You're trash!");
  }
  SRAM_writes_to_screen();
  printf("Tast inn navn:(Enter for ferdig) ");
  char user_input=0;
  char user_name[10];
  int counter = 0;
  while (user_input!='\n' || counter!=9){
    user_input = USART_Receive(NULL);
    USART_Transmit(user_input,NULL);
    user_name[counter]=user_input;
    counter++;
  }
  user_name[counter]='\0';

}

void print_high_score(void){
  volatile char* ext_ram = (char *) 0x1800; //Start address of SRAM
  SRAM_oled_print8(0,0,"High score");
  draw_line(0,127,10,10);

  for (int i = 0; i<HIGH_SCORE_LENGTH; i++){
    char highscore_array[4];
    char placement = '1'+i;
    uint8_t highscore_value = (uint8_t)ext_ram[i];
    snprintf(highscore_array,4,"%d",highscore_value);

    /******************Create the C-string**************/
    char print_to_screen[7];
    print_to_screen[0]=placement;
    print_to_screen[1]='.';
    print_to_screen[2]=' ';
    for (int j=0;j<3;j++){
      print_to_screen[j+3]=highscore_array[j];
    }
    print_to_screen[6]='\0';
    /**************Create the C-string****************/


    SRAM_oled_print5(2+i,0,print_to_screen);
  }
  SRAM_writes_to_screen();
}

void print_game_screen(void){
  static uint8_t x1 = 24;
  uint8_t y1 = 24;
  uint8_t r1 = 6;

  static uint8_t x2 = 40;
  uint8_t y2 = 40;
  uint8_t r2 = 6;

  static uint8_t x3 = 56;
  uint8_t y3 = 56;
  uint8_t r3 = 6;
  static int8_t k0 = 3;
  static int8_t k1 = 3;
  static int8_t k2 = 3;
  static int8_t k3 = 3;

  SRAM_OLED_reset();
  char current_game_score[4];
  snprintf(current_game_score,4,"%d",highscore);
  SRAM_oled_print5(0,112,current_game_score);
  SRAM_oled_print8(0,0,"Current score:");
  draw_smiley(x1,y1,r1);
  draw_smiley(x2,y2,r2);
  draw_smiley(x3,y3,r3);
  SRAM_writes_to_screen();
  x1+=k1;
  x2+=k2;
  x3+=k3;
  if (x1 >= 120){
    k1=-3;
  }
  else if (x1<8){
    k1=3;
  }
  if (x2 >= 120){
    k2=-3;
  }
  else if (x2<=8){
    k2=3;
  }
  if (x3 >= 120){
    k3=-3;
  }
  else if (x3<=8){
    k3=3;
  }
}

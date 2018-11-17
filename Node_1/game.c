#include "game.h"
#include "can.h"
#include "oled.h"
#include "uart.h"
#include "sram.h"
#include <util/delay.h>


#define HIGH_SCORE_LENGTH 3 //CONSTANT
#define MAX_NAME_LENGTH 6 //CONSTANT

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


void high_score_init(void){ //empties the SRAM
  volatile char *ext_ram = (char *) 0x1800;
  for (int i = 0; i<HIGH_SCORE_LENGTH*8; i++){
    ext_ram[i]=0;
  }
}

void save_user_data_to_SRAM(user_score user_data, int position){
  volatile char *ext_ram = (char*) 0x1800;  //Start address for the SRAM
  int j=0;
  for (int i=(MAX_NAME_LENGTH+2)*position;i<(MAX_NAME_LENGTH+2)*position+(MAX_NAME_LENGTH+2);i++){
    if(j<7){
      ext_ram[i]=user_data.user_name[j];
    }else{
      ext_ram[i]=user_data.score;
    }
    j++;
  }
}

user_score load_user_data_from_SRAM(int position){
  volatile char *ext_ram = (char*) 0x1800;  //Start address for the SRAM
  user_score user_data;
  int j = 0;
  for (int i=(MAX_NAME_LENGTH+2)*position;i<(MAX_NAME_LENGTH+2)*position+(MAX_NAME_LENGTH+2);i++){
    if (j<(MAX_NAME_LENGTH+1)){
      user_data.user_name[j]=ext_ram[i];
    } else{
      user_data.score = ext_ram[i];
    }
    j++;
  }
  return user_data;
}

user_score create_user(uint8_t score_value){
  user_score user_data;
  user_data.score = score_value;
  for (int i = 0; i<MAX_NAME_LENGTH+1;i++){
    user_data.user_name[i]='\0'; //empties the array first
  }
  printf("Enter name and . when finished: (Max. 6 letter) ");
  char user_input=0;
  int counter = 0;

  //Receive data from putty if user hasn't reached maximum letters or used ENTER
  while (user_input!='.' && counter!=MAX_NAME_LENGTH){
    user_input=USART_Receive(NULL);
    USART_Transmit(user_input,NULL);
    if (user_input!='.'){
      user_data.user_name[counter] = user_input;
      counter++;
    }
  }
  user_data.user_name[counter]='\0';
  return user_data;
}

void save_high_score(uint8_t value){
  user_score temp_high_score[HIGH_SCORE_LENGTH];
  uint8_t is_value_added = 0;
  for (int i = 0; i<HIGH_SCORE_LENGTH; i++){
    if (is_value_added){
      temp_high_score[i]=load_user_data_from_SRAM(i-1);
    }else{
      user_score user_from_SRAM=load_user_data_from_SRAM(i);
      if (user_from_SRAM.score>=value){
        temp_high_score[i]=user_from_SRAM;
      } else {
        temp_high_score[i]=create_user(value);
        is_value_added=1; //sets flag to say if the new value is added
      }
    }
  }
  for (int i = 0; i<HIGH_SCORE_LENGTH; i++){
    save_user_data_to_SRAM(temp_high_score[i],i);
  }
}

void print_score(void){
  SRAM_oled_print8(0,0,"Score");

  //prints the score value
  char gamescore[4];
  uint8_t score = highscore;
  snprintf(gamescore,4,"%d",score);
  SRAM_oled_print8(3,60,gamescore);

  //print text
  SRAM_oled_print5(5,0,"Write your name?");
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

  save_high_score(score);
  printf("\n");
}

void print_high_score(void){
  volatile char* ext_ram = (char *) 0x1800;
  SRAM_oled_print8(0,0,"High score");
  draw_line(0,127,10,10);

  for (int i = 0; i<HIGH_SCORE_LENGTH;i++){
    user_score user_from_SRAM = load_user_data_from_SRAM(i);

    //Dynamic position
    char position = '1'+i;

    //Change the type for high score to char
    char highscore_array[4];
    uint8_t highscore_value = user_from_SRAM.score;
    snprintf(highscore_array,4,"%d",highscore_value);

    char print_to_screen[MAX_NAME_LENGTH+4];
    print_to_screen[0]=position;
    print_to_screen[1]='.';
    print_to_screen[2] =' ';
    for (int j=0; j<MAX_NAME_LENGTH;j++){
      print_to_screen[j+3]=user_from_SRAM.user_name[j];
    }
    print_to_screen[MAX_NAME_LENGTH+3] = '\0';
    SRAM_oled_print5(2+i,0,print_to_screen); //print the placement and name
    SRAM_oled_print5(2+i,112,highscore_array); //print the score after
  }
  SRAM_writes_to_screen();


}

/*
void print_high_score(void){
  volatile char* ext_ram = (char *) 0x1800; //Start address of SRAM
  SRAM_oled_print8(0,0,"High score");
  draw_line(0,127,10,10);

  for (int i = 0; i<HIGH_SCORE_LENGTH; i++){
    char highscore_array[4];
    char placement = '1'+i;
    uint8_t highscore_value = (uint8_t)ext_ram[i];
    snprintf(highscore_array,4,"%d",highscore_value);

    char print_to_screen[7];
    print_to_screen[0]=placement;
    print_to_screen[1]='.';
    print_to_screen[2]=' ';
    for (int j=0;j<3;j++){
      print_to_screen[j+3]=highscore_array[j];
    }
    print_to_screen[6]='\0';



    SRAM_oled_print5(2+i,0,print_to_screen);
  }
  SRAM_writes_to_screen();
}
*/

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

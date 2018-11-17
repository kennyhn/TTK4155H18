#include "menu.h"
#include "oled.h"
#include "sram.h"
#include "game.h"
#include "can.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>


void menu_driver(uint8_t* K_p,uint8_t* K_i,joystick_direction* dir, menu_element** menu_choice,volatile uint8_t* adc){
  joystick_direction prev_dir = *dir;
  *dir = check_joystick_direction(adc);
  if (prev_dir == NEUTRAL){
    if (*dir == UP && (*menu_choice)->up!=NULL){
        *menu_choice=(*menu_choice)->up;
    }
    else if (*dir == DOWN && (*menu_choice)->down!=NULL){
        *menu_choice=(*menu_choice)->down;
    }
    else if(*dir == RIGHT && (*menu_choice)->choose!=NULL){
        *menu_choice=(*menu_choice)->choose;
        if ((*menu_choice)->name == "Game"){
          play_game(*K_p, *K_i);
          *menu_choice=(*menu_choice)->choose; //score
        }
        print_page(*menu_choice);
    }
    else if(*dir==LEFT && (*menu_choice)->back!=NULL){
        *menu_choice=(*menu_choice)->back;
        print_page(*menu_choice);
    }

    //when to print marker
    if ((*menu_choice)->name != "Score" && (*menu_choice)->name != "Highscore table"){
      print_marker((*menu_choice)->line);
    }
    if ((*menu_choice)->name == "Easy"){
      *K_p = 1;
      *K_i = 1;
    }
    else if ((*menu_choice)->name == "Hard"){
      *K_p = 4;
      *K_i = 4;
    }
  }
}

menu_element* create_menu_element(char* name,uint8_t line, menu_element* up, menu_element* down, menu_element* choose, menu_element* back){
    menu_element* e = malloc(sizeof(*e));
    e->name=name;
    e->line=line;
    e->up=up;
    e->down=down;
    e->choose=choose;
    e->back=back;
    //e->function_peker=
    return e;
}

//bruker sram
void print_page(menu_element* node){
  SRAM_OLED_reset();
  if (node->name == "Score"){
    print_score();
  }
  else if (node->name == "Highscore table"){
    print_high_score();
  }
  else{
    menu_element* temp = node;
    if(node->back==NULL){
        SRAM_oled_print8(0,0,"Main menu");
    }
    else{
        SRAM_oled_print8(0,0,node->back->name);
    }
    draw_line(0,127,10,10);

    int i = node->line+2;//i offset
    SRAM_oled_print5(i,5,node->name);
    while (node->down != NULL){
        node = node->down;
        SRAM_oled_print5(++i,5, node->name);
    }
    i = temp->line+2;//i offset
    while (temp->up != NULL){
        temp = temp->up;
        SRAM_oled_print5(--i, 5, temp->name);
    }
  }
}

//bruker SRAM
void print_marker(uint8_t line){
  for (int i = 2; i <8;i++){ //changed i to not clear i first lines
      for(int j = 0; j<5;j++){
          SRAM_write_to_mem(i,j,0x00);
      }
  }
  SRAM_oled_write_character_font5(line+2,0,'>');
  SRAM_writes_to_screen();
}




menu_element* create_menu(){ //return first element in menu
  menu_element* play_game = create_menu_element("Play game",0, NULL, NULL, NULL,NULL);
  menu_element* highscore = create_menu_element("Highscore", 1,play_game, NULL, NULL, NULL);
  menu_element* highscore_table = create_menu_element("Highscore table", 0, NULL, NULL, NULL, highscore);
  menu_element* score = create_menu_element("Score", 0, NULL, NULL, highscore_table, NULL);
  menu_element* game = create_menu_element("Game",0, NULL, NULL, score,NULL);

  menu_element* easy = create_menu_element("Easy",0, NULL, NULL, game,play_game);
  menu_element* hard = create_menu_element("Hard",1, easy, NULL, game,play_game);

  menu_element* credits = create_menu_element("Credits", 2,highscore, NULL, NULL, NULL);
  menu_element* iver = create_menu_element("Iver", 0,NULL, NULL, NULL, credits);
  menu_element* kenny = create_menu_element("Kenny", 1,iver, NULL, NULL, credits);
  menu_element* jorgen = create_menu_element("Jorgen", 2,kenny, NULL, NULL, credits);

  play_game->down=highscore;
  play_game->choose=easy;
  easy->down = hard;
  highscore->choose = highscore_table;
  highscore->down = credits;
  credits->choose = iver;
  iver->down = kenny;
  kenny->down = jorgen;
  print_page(play_game);
  print_marker(play_game->line);
  return play_game;
}

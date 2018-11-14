#include "menu.h"
#include "oled.h"
#include "sram.h"
#include "game.h"
#include "can.h"
#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t high_score = 0;

void menu_driver(joystick_direction* dir, menu_element** menu_choice,volatile uint8_t* adc){
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
            high_score = play_game();
            printf("%d", high_score);
            save_high_score(high_score);
            *menu_choice=(*menu_choice)->choose; //score
          }
          print_page(*menu_choice);
      }
      else if(*dir==LEFT && (*menu_choice)->back!=NULL){
          *menu_choice=(*menu_choice)->back;
          print_page(*menu_choice);
      }
      if ((*menu_choice)->name != "Score" && (*menu_choice)->name != "Highscore table"){
        print_marker((*menu_choice)->line);
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
    SRAM_oled_print8(0,0,"Score");
    //SRAM_oled_print8(5,3, highscore); need to convert uint8_t to char*
    if (high_score > 20){
      SRAM_oled_print8(5,4, "Nice!");
    }
    else{
        SRAM_oled_print8(5,4, "Hopeless!");
    }
    SRAM_writes_to_screen();
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
  menu_element* test1 = create_menu_element("Test1", 2,highscore, NULL, NULL, NULL);
  menu_element* test2 = create_menu_element("Test2", 0,NULL, NULL, NULL, test1);
  menu_element* test3 = create_menu_element("Test3", 1,test2, NULL, NULL, test1);
  menu_element* test4 = create_menu_element("Test4", 0,NULL, NULL, NULL, test3);

  play_game->down=highscore;
  play_game->choose=game;
  highscore->choose = highscore_table;
  highscore->down = test1;
  test1->choose = test2;
  test2->down = test3;
  test3->choose = test4;
  print_page(play_game);
  print_marker(play_game->line);
  return play_game;
}

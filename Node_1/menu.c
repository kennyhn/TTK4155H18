#include "menu.h"
#include "oled.h"
#include "sram.h"
#include "game.h"
#include "can.h"
#include <avr/io.h>
#include <util/delay.h>

volatile int32_t high_score = 0;

void menu_driver(joystick_direction dir, menu_element** menu_choice,volatile uint8_t* adc){
    dir = check_joystick_direction(adc);
    if (dir == UP && (*menu_choice)->up!=NULL){
        *menu_choice=(*menu_choice)->up;
    }
    else if (dir == DOWN && (*menu_choice)->down!=NULL){
        *menu_choice=(*menu_choice)->down;
    }
    else if(dir == RIGHT && (*menu_choice)->choose!=NULL){
        *menu_choice=(*menu_choice)->choose;
        if ((*menu_choice)->name == "Game"){
          //int8_t first = 1;
          high_score = play_game();
          *menu_choice=(*menu_choice)->back;
          print_score();
          /*_delay_ms(1000);
          printf("Reset flag\n");
          can_message_received = 0;*/
        }
        else{
            print_page(*menu_choice);
        }

    }
    else if(dir==LEFT && (*menu_choice)->back!=NULL){
        *menu_choice=(*menu_choice)->back;
        print_page(*menu_choice);
    }
    print_marker((*menu_choice)->line);
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

void print_score(void){
  SRAM_OLED_reset();
  SRAM_oled_print8(0,0,"Score");
  if (high_score > 100){
    SRAM_oled_print8(3,3, "Bra");
  }
  else{
      SRAM_oled_print8(3,3, "Hopeless");
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

menu_element* create_menu(){ //returnerer første element i menyen
    menu_element* play_game = create_menu_element("Play game",0, NULL, NULL, NULL,NULL);
    menu_element* game = create_menu_element("Game",0, NULL, NULL, NULL,NULL);
    menu_element* score = create_menu_element("Score", 0, NULL, NULL, play_game, NULL);
    menu_element* highscore = create_menu_element("Highscore", 1,play_game, NULL, NULL, play_game);
    menu_element* test1 = create_menu_element("Test1", 0,NULL, NULL, NULL, highscore);
    menu_element* test2 = create_menu_element("Test2", 1,test1, NULL, NULL, highscore);
    menu_element* test3 = create_menu_element("Test3", 2,test2, NULL, NULL, highscore);

    menu_element* test4 = create_menu_element("Test4", 0,NULL, NULL, NULL, test2);
    game->back=score;
    score->back=highscore;
    play_game->down=highscore;
    play_game->choose=game;
    highscore->choose = test1;
    test1->down = test2;
    test2->down = test3;
    test2->choose = test4;
    print_page(play_game);
    print_marker(play_game->line);
    return play_game;
}

#ifndef GAME_H_
#define GAME_H_

#define F_CPU 4915200

#include <stdint.h>
volatile uint8_t highscore;

typedef struct User_score{
    char user_name[7]; //Max 6 letter for user_name
    uint8_t score;
}user_score;

uint8_t play_game(uint8_t K_p,uint8_t K_i);
void high_score_init(void);
void save_high_score(uint8_t value);
void print_score(void);
void print_high_score(void);
void print_game_screen(void);
#endif

#ifndef GAME_H_
#define GAME_H_

#define F_CPU 4915200

#include <stdint.h>
volatile uint8_t highscore;


uint8_t play_game(uint8_t K_p,uint8_t K_i);
void high_score_init(void);
void save_high_score(uint8_t value);
void print_high_score(void);
#endif

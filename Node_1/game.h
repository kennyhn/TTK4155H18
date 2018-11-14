#ifndef GAME_H_
#define GAME_H_

#define F_CPU 4915200

#include <stdint.h>


uint8_t play_game(void);
void high_score_init(void);
void save_high_score(uint8_t value);
void print_high_score(void);
#endif

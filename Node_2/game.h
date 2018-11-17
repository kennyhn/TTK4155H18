/**@file game.h
 * @brief Functions controlling the game experience
 */
#ifndef GAME_H_
#define GAME_H_
#include <stdint.h>

/**@brief Functions returning true if the IR sensor signal goes to low
 */
int8_t check_game_over(void);

/**@brief Function runnig the game and making the game experience
 */
void play_game(void);
#endif

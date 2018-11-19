/**@file game_node2.h
 * @brief Functions controlling the game experience
 */
#ifndef GAME_NODE2_H_
#define GAME_NODE2_H_
#include <stdint.h>

/**@brief Functions returning true if the IR sensor signal goes to low
 */
int8_t check_game_over(void);

/**@brief Function running the game and making the game experience
 */
void play_game(void);
#endif

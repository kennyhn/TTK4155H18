/**@file game.h
 * @brief Functions for game functions including high score
 */
#ifndef GAME_H_
#define GAME_H_

#define F_CPU 4915200

#include <stdint.h>
volatile uint8_t highscore;

typedef struct User_score{
    char user_name[7]; //Max 6 letter for user_name
    uint8_t score;
}user_score;

/**@brief The function for game-operation
 *
 *In this function the logic for the game is setup. This function sends the necessary data to node 2 to control the motor box.
 *@return uint8_t initially used to return the high score value from the game. Is only used to break while loop.
 */
uint8_t play_game(uint8_t K_p,uint8_t K_i);

/**@brief Initialize the high score in SRAM
 *
 *This function empties the SRAM for the memory spaces where the highscore data is stored
 */
void high_score_init(void);

/**@brief Saves the high score to the SRAM
 *
 * This function creates the user with name and saves the high score to the SRAM
 */
void save_high_score(uint8_t value);

/**@brief prints out the score screen in OLED
 *
 *The message that is sent is "bounced" back. This is used to see if the SPI-bus between the CAN-controller and CAN-tranceiver is correctly setup
 *@return int which is a boolean value saying if the mode is successfully intialized.
 */
void print_score(void);

/**@brief Initialize the CAN in loopback mode
 *
 *The message that is sent is "bounced" back. This is used to see if the SPI-bus between the CAN-controller and CAN-tranceiver is correctly setup
 *@return int which is a boolean value saying if the mode is successfully intialized.
 */
void print_high_score(void);

/**@brief Initialize the CAN in loopback mode
 *
 *The message that is sent is "bounced" back. This is used to see if the SPI-bus between the CAN-controller and CAN-tranceiver is correctly setup
 *@return int which is a boolean value saying if the mode is successfully intialized.
 */
void print_game_screen(void);
#endif

/**
 * @file game_aux.h
 * @author Taraxtix (taraxtix.github.io)
 * @brief Auxiliary Game Functions.
 * @copyright Copyright (c) 2022
 **/

#ifndef __GAME_AUX_H__
#define __GAME_AUX_H__
#include <stdbool.h>

#include "game.h"

/**
 * @brief Prints a game as text on the standard output stream.
 * @details The different squares are respectively displayed as text, based on a
 * square-character mapping table, as described in @ref index.
 * @param g the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_print(c_game g);

/**
 * @brief Creates the default game.
 * @details See the description of the default game in @ref index.
 * @return the created game
 **/
game game_default(void);

#endif // __GAME_AUX_H__

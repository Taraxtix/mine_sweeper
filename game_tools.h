/**
 * @file game_tools.h
 * @brief Game Tools.
 * @author Taraxtix (taraxtix.github.io)
 * @copyright Copyright (c) 2022
 **/

#ifndef __GAME_TOOLS_H__
#define __GAME_TOOLS_H__
#include <stdbool.h>
#include <stdio.h>

#include "game.h"

/**
 * @name Game Tools
 * @{
 */

/**
 * @brief Creates a game by loading its description in a text file.
 * @details See the file format description in @ref index.
 * @param filename
 * @return the loaded game
 **/
game game_load(char *filename);

/**
 * @brief Saves a game in a text file.
 * @details See the file format description in @ref index.
 * @param g game to save
 * @param filename output file
 **/
void game_save(c_game g, char *filename);

#endif // __GAME_TOOLS_H__
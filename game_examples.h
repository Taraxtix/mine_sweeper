/**
 * @file game_examples.h
 * @author Taraxtix (taraxtix.github.io)
 * @brief Game Examples.
 * @copyright Copyright (c) 2022
 **/

#ifndef __GAME_EXAMPLES_H__
#define __GAME_EXAMPLES_H__

#include "game.h"

/* ************************************************************************** */
/*                                  MISC                                      */
/* ************************************************************************** */

#define BLANK_D (BLANK | DISCOVERED)
#define BLANK_F (BLANK | FLAGED)
#define MINE_D (MINE | DISCOVERED)
#define MINE_F (MINE | FLAGED)

/* ************************************************************************** */
/*                               GAME EXAMPLES                                */
/* ************************************************************************** */

extern square dflt_squares[];
extern square dflt_br_disco[];
extern square won_2x2[];
extern square lost_2x2[];
extern square other_squares[];

#endif // __GAME_EXAMPLES_H__
/**
 * @file game_examples.c
 * @author Taraxtix (taraxtix.github.io)
 * @brief Game Examples.
 * @copyright Copyright (c) 2022
 **/

#include "game_examples.h"
#include "game.h"
#include "game_private.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ************************************************************************** */
/*                               BASIC GAMES                                  */
/* ************************************************************************** */

square dflt_squares[DFLT_SIZE * DFLT_SIZE] = {
    BLANK, BLANK, BLANK, BLANK, MINE,  BLANK, BLANK, MINE,  BLANK, // row 0
    MINE,  BLANK, BLANK, BLANK, BLANK, BLANK, MINE,  MINE,  BLANK, // row 1
    BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // row 2
    BLANK, MINE,  BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // row 3
    BLANK, BLANK, MINE,  BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // row 4
    BLANK, BLANK, MINE,  BLANK, MINE,  BLANK, BLANK, BLANK, BLANK, // row 5
    BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // row 6
    BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // row 7
    BLANK, BLANK, BLANK, BLANK, BLANK, MINE,  BLANK, BLANK, BLANK  // row 8
};

/* ************************************************************************** */
// clang-format off

// The default game after we've discovered the bottom_right square (8, 8)
square dflt_br_disco[DFLT_SIZE * DFLT_SIZE] = {
//  col 0  col 1  col 2  col 3    col 4    col 5    col 6    col 7    col 8
    BLANK, BLANK_D, BLANK_D, BLANK_D, MINE,    BLANK,   BLANK,   MINE,    BLANK, // row 0
    MINE,  BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, MINE,    MINE,    BLANK, // row 1
    BLANK, BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, // row 2
    BLANK, MINE,    BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, // row 3
    BLANK, BLANK,   MINE,    BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, BLANK_D, // row 4
    BLANK, BLANK,   MINE,    BLANK,   MINE,    BLANK_D, BLANK_D, BLANK_D, BLANK_D, // row 5
    BLANK, BLANK,   BLANK,   BLANK,   BLANK,   BLANK_D, BLANK_D, BLANK_D, BLANK_D, // row 6
    BLANK, BLANK,   BLANK,   BLANK,   BLANK,   BLANK_D, BLANK_D, BLANK_D, BLANK_D, // row 7
    BLANK, BLANK,   BLANK,   BLANK,   BLANK,   MINE,    BLANK_D, BLANK_D, BLANK_D // row 8
};
// clang-format on
/* ************************************************************************** */

square won_2x2[2 * 2] = {
    MINE_F, BLANK_D, // row 0
    BLANK_D, MINE_F  // row 1
};

/* ************************************************************************** */

square lost_2x2[2 * 2] = {
    MINE_D, BLANK_D, // row 0
    BLANK_D, MINE_F  // row 1
};

/* ************************************************************************** */

square other_squares[2 * 3] = {
    BLANK, BLANK_D, BLANK_F, // row 0
    MINE,  MINE_D,  MINE_F   // row 1
};
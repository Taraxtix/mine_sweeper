/**
 * @file game_private.h
 * @author Taraxtix (taraxtix.github.io)
 * @brief Internal header file
 * @copyright Copyright (c) 2022
 */

#ifndef __GAME_PRIVATE_H__
#define __GAME_PRIVATE_H__

#include "game.h"

/* *********************************************** */
/*                   DATA TYPES                    */
/* *********************************************** */

/**
 * @brief Game structure
 * @details This is an opaque structure
 */
struct game_s
{
    uint nb_cols;    /**< Number of columns in the game */
    uint nb_rows;    /**< Number of rows in the game */
    square *squares; /**< The array containing the square values of the game */
};

/**
 * @brief Enum representing all different directions from a square
 * @details The 4 first one are the "previous" directions
 */
typedef enum _dir
{
    UP,
    LEFT,
    UP_LEFT,
    UP_RIGHT,
    RIGHT,
    DOWN,
    DOWN_LEFT,
    DOWN_RIGHT
} dir;

/* *********************************************** */
/*                      MACRO                      */
/* *********************************************** */

// clang-format off
#define DEFAULT_SIZE 9
#define NB_PREV_DIR 4
#define NB_DIR 8

#define INDEX(g, i, j) ((i) * ((g)->nb_cols) + (j))
#define SQUARE(g, i, j) ((g)->squares[(INDEX(g, i, j))])
#define STATE(g, i, j) (SQUARE(g, i, j) & S_MASK)
#define FLAGS(g, i, j) (SQUARE(g, i, j) & F_MASK)
#define _FLAG(g, i, j) (FLAGS(g, i, j) & FLAGED)
#define _DISCO(g, i, j) (FLAGS(g, i, j) & DISCOVERED)
#define INSIDE(g, i, j) ((int)i >= 0 || (int)j >= 0 || i < g->nb_cols || j < g->nb_cols)
#define FREE(g) do { free(g->squares); free(g); } while (0)
#define PRINT_LINE(g, c) do { printf("   "); for (uint j = 0; j < (g->nb_cols); j++) { printf(c); } printf("\n"); } while (0)
#define BLANK_0_MINED_NEIGH(g, i, j) (game_is_blank(g, i, j) && _DISCO(g, i, j) && !game_get_blank_nb(g, i, j))
// clang-format on

/* *********************************************** */
/*               GAME PRIVATE ROUTINES             */
/* *********************************************** */

/**
 * @brief convert a square into a character
 *
 * @param s a square
 * @return the corresponding character, '?' otherwise
 */
char _square2char(c_game g, uint i, uint j);

/**
 * @brief Discover all the neighboors of the (i, j) squares in the game, then
 * update the previous adjacent squares's flags
 *
 * @param g the game
 * @param i the row index of the square
 * @param j the col index of the square
 */
void _disco_all_neigh(game g, uint i, uint j);

#endif
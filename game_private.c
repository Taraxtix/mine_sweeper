/**
 * @file game_private.c
 * @author Taraxtix (taraxtix.github.io)
 * @brief Internal file
 * @copyright Copyright (c) 2022
 */

#include "game_private.h"

/* *********************************************** */
/*               PRIVATE STATEMENTS                */
/* *********************************************** */

// clang-format off
static const char square2char[0xFF] = {
    [BLANK] = ' ', [MINE] = ' ',
    [BLANK | DISCOVERED] = '0', '1', '2', '3', '4', '5', '6', '7', '8',
    [MINE | DISCOVERED] = '*', [BLANK | FLAGED] = 'F', [MINE | FLAGED] = 'F' };
// clang-format on

const int i_offset[NB_DIR] = {
    [UP] = -1,      [DOWN] = 1,      [LEFT] = 0,      [RIGHT] = 0,
    [UP_LEFT] = -1, [UP_RIGHT] = -1, [DOWN_LEFT] = 1, [DOWN_RIGHT] = 1};

const int j_offset[NB_DIR] = {
    [UP] = 0,       [DOWN] = 0,     [LEFT] = -1,      [RIGHT] = 1,
    [UP_LEFT] = -1, [UP_RIGHT] = 1, [DOWN_LEFT] = -1, [DOWN_RIGHT] = 1};

/* *********************************************** */
/*               GAME PRIVATE ROUTINES             */
/* *********************************************** */

char _square2char(c_game g, uint i, uint j)
{
    square s = game_get_square(g, i, j);
    if (s == (BLANK | DISCOVERED))
    {
        return square2char[(BLANK | DISCOVERED) + game_get_blank_nb(g, i, j)];
    }
    else
        return square2char[s];
}

static void _update_prev_neigh(game g, uint i, uint j)
{
    for (uint x = 0; x < NB_PREV_DIR; x++)
    {
        if (BLANK_0_MINED_NEIGH(g, i, j)) { _disco_all_neigh(g, i, j); }
    }
}

void _disco_all_neigh(game g, uint i, uint j)
{
    for (uint x = 0; x < NB_DIR; x++)
    {
        game_play_move(g, i + i_offset[x], j + j_offset[x], DISCOVERED);
    }
    _update_prev_neigh(g, i, j);
}
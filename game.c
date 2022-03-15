/**
 * @file game.c
 * @author Taraxtix (taraxtix.github.io)
 * @brief Implements the basics game functions
 * @copyright Copyright (c) 2022
 */

#include "game.h"
#include "game_private.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ********************************************************************** */
/*                             GAME ROUTINES                              */
/* ********************************************************************** */

game game_new_empty(uint nb_rows, uint nb_cols)
{
    game g = (game)malloc(sizeof(struct game_s));
    assert(g);
    g->nb_rows = nb_rows;
    g->nb_cols = nb_cols;

    square *squares = (square *)malloc(nb_cols * nb_rows * sizeof(square));
    assert(squares);

    for (uint i = 0; i < nb_rows * nb_cols; i++)
        squares[i] = BLANK;
    g->squares = squares;

    return g;
}

/* **************************************************************** */

game game_new(uint nb_rows, uint nb_cols, square *squares)
{
    game g = game_new_empty(nb_rows, nb_cols);
    for (uint i = 0; i < nb_cols * nb_rows; i++)
    {
        g->squares[i] = squares[i];
    }
    return g;
}

/* **************************************************************** */

game game_copy(c_game g)
{
    return game_new(g->nb_rows, g->nb_cols, g->squares);
}

/* **************************************************************** */

bool game_equal(c_game g1, c_game g2)
{
    if (g1->nb_cols != g2->nb_cols) { return false; }
    if (g1->nb_rows != g2->nb_rows) { return false; }
    for (uint i = 0; i < g1->nb_cols * g1->nb_rows; i++)
    {
        if (g1->squares[i] != g2->squares[i]) { return false; }
    }
    return true;
}

/* **************************************************************** */

void game_delete(game g) { FREE(g); }

/* **************************************************************** */

void game_set_square(game g, uint i, uint j, square s) { SQUARE(g, i, j) = s; }

/* **************************************************************** */

uint game_nb_cols(c_game g) { return g->nb_cols; }

/* **************************************************************** */

uint game_nb_rows(c_game g) { return g->nb_rows; }

/* **************************************************************** */

square game_get_square(c_game g, uint i, uint j) { return SQUARE(g, i, j); }

/* **************************************************************** */

square game_get_state(c_game g, uint i, uint j) { return STATE(g, i, j); }

/* **************************************************************** */

square game_get_flags(c_game g, uint i, uint j) { return FLAGS(g, i, j); }

/* **************************************************************** */

bool game_is_blank(c_game g, uint i, uint j) { return STATE(g, i, j) == BLANK; }

/* **************************************************************** */

bool game_is_mined(c_game g, uint i, uint j) { return STATE(g, i, j) == MINE; }

/* **************************************************************** */

int game_get_blank_nb(c_game g, uint i, uint j)
{
    uint cpt = 0;
    for (int i_offset = -1; i_offset <= 1; i_offset++)
        for (int j_offset = -1; j_offset <= 1; j_offset++)
        {
            if (!INSIDE(g, (i_offset + i), (j_offset + j))) { continue; }
            if (game_is_mined(g, i_offset + i, j_offset + j)) { cpt++; }
        }
    return cpt;
}

/* **************************************************************** */

bool game_is_flaged(c_game g, uint i, uint j) { return _FLAG(g, i, j); }

/* **************************************************************** */

bool game_is_discovered(c_game g, uint i, uint j) { return _DISCO(g, i, j); }

/* **************************************************************** */

bool game_check_move(c_game g, uint i, uint j, square f)
{
    return INSIDE(g, i, j) && !_DISCO(g, i, j) && !(f & S_MASK) &&
           !(f == DISCOVERED && _FLAG(g, i, j));
}

/* **************************************************************** */

void game_play_move(game g, uint i, uint j, square f)
{
    if (!game_check_move(g, i, j, f)) return;
    if (_FLAG(g, i, j)) f = 0x00;
    SQUARE(g, i, j) = (STATE(g, i, j) | f);
    game_update_flags(g);
}

/* **************************************************************** */

bool game_is_won(c_game g)
{
    for (uint i = 0; i < game_nb_rows(g); i++)
        for (uint j = 0; j < game_nb_cols(g); j++)
        {
            if (game_is_mined(g, i, j))
            {
                if (game_is_discovered(g, i, j)) { return false; }
                if (!game_is_flaged(g, i, j)) { return false; }
            }
            else if (!game_is_discovered(g, i, j))
            {
                return false;
            }
        }
    return true;
}

/* **************************************************************** */

bool game_is_lost(c_game g)
{
    for (uint i = 0; i < game_nb_rows(g); i++)
        for (uint j = 0; j < game_nb_cols(g); j++)
            if (game_is_mined(g, i, j) && game_is_discovered(g, i, j))
                return true;
    return false;
}

/* **************************************************************** */

bool game_is_over(c_game g) { return game_is_won(g) || game_is_lost(g); }

/* **************************************************************** */

void game_restart(game g)
{
    for (uint i = 0; i < game_nb_rows(g); i++)
        for (uint j = 0; j < game_nb_cols(g); j++)
            SQUARE(g, i, j) = STATE(g, i, j);
}

/* **************************************************************** */

void game_update_flags(game g)
{
    for (uint i = 0; i < game_nb_rows(g); i++)
        for (uint j = 0; j < game_nb_cols(g); j++)
            if (BLANK_0_MINED_NEIGH(g, i, j)) { _disco_all_neigh(g, i, j); }
}

/**
 * @file game_aux.c
 * @author Taraxtix (taraxtix.github.io)
 * @brief Implements the auxiliary game functions
 * @copyright Copyright (c) 2022
 */

#include "game_aux.h"
#include "game.h"
#include "game_private.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ************************************************************************ */
/*                            AUXILIARY ROUTINES                            */
/* ************************************************************************ */

void game_print(c_game g)
{
    assert(g);
    PRINT_LINE(g, ("%d", j));
    PRINT_LINE(g, ("-"));

    for (uint i = 0; i < game_nb_rows(g); i++)
    {
        printf("%d |", i);
        for (uint j = 0; j < game_nb_cols(g); j++)
        {
            printf("%c", _square2char(g, i, j));
        }
        printf("|\n");
    }
    PRINT_LINE(g, ("-"));
}

/* ************************************************************************** */

game game_default()
{
    square squares[DEFAULT_SIZE * DEFAULT_SIZE] = {
        BLANK, BLANK, BLANK, BLANK, MINE,  BLANK, BLANK, MINE,  BLANK, // line 0
        MINE,  BLANK, BLANK, BLANK, BLANK, BLANK, MINE,  MINE,  BLANK, // line 1
        BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // line 2
        BLANK, MINE,  BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // line 3
        BLANK, BLANK, MINE,  BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // line 4
        BLANK, BLANK, MINE,  BLANK, MINE,  BLANK, BLANK, BLANK, BLANK, // line 5
        BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // line 6
        BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, // line 7
        BLANK, BLANK, BLANK, BLANK, BLANK, MINE,  BLANK, BLANK, BLANK  // line 8
    };
    return game_new(DEFAULT_SIZE, DEFAULT_SIZE, squares);
}
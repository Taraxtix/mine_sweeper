/**
 * @file game_aux.c
 * @author Taraxtix (taraxtix.github.io)
 * @brief Implements the auxiliary game functions
 * @copyright Copyright (c) 2022
 */

#include "game_aux.h"
#include "game.h"
#include "game_examples.h"
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
    printf("   ");
    for (uint j = 0; j < (g->nb_cols); j++)
    {
        printf("%d", j);
    }
    printf("\n");

    printf("   ");
    for (uint j = 0; j < (g->nb_cols); j++)
    {
        printf("-");
    }
    printf("\n");

    for (uint i = 0; i < game_nb_rows(g); i++)
    {
        printf("%d |", i);
        for (uint j = 0; j < game_nb_cols(g); j++)
        {
            printf("%c", _square2char(g, i, j));
        }
        printf("|\n");
    }

    printf("   ");
    for (uint j = 0; j < (g->nb_cols); j++)
    {
        printf("-");
    }
    printf("\n");
}

/* ************************************************************************** */

game game_default() { return game_new(DFLT_SIZE, DFLT_SIZE, dflt_squares); }
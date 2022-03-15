/**
 * @file game_text.c
 * @author Taraxtix (taraxtix.github.io)
 * @brief Text version of the game
 * @copyright Copyright (c) 2022
 *
 */

#include "game.h"
#include "game_aux.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ************************************************************************** */

static bool game_step(game g)
{
    printf("> ? [h for help]\n");
    // <action> [<row> <col>]
    char c = '?';
    int r = scanf(" %c", &c); // don't forget the space ' ' before %c
    if (r == EOF || r < 0) { return false; }
    if (r != 1)
    {
        printf("Error: invalid user input!\n");
        return true; // but continue to play
    }

    if (c == 'h')
    { // help
        printf("> action: help\n");
        printf("- press 'd <i> <j>' to discover the square (i,j)\n");
        printf("- press 'f <i> <j>' to put a flag at square (i,j)\n");
        // printf("- press 'w' <filename> to save\n");
        printf("- press 'r' to restart\n");
        printf("- press 'q' to quit\n");
    }
    else if (c == 'r')
    { // restart
        printf("> action: restart\n");
        game_restart(g);
        return true;
    }
    else if (c == 'q')
    { // quit
        printf("> action: quit\n");
        return false; // exit
    }
    else if (c == 'd' || c == 'f')
    { // play move
        uint i, j;
        int ret = scanf(" %u %u", &i, &j);
        if (ret != 2)
        {
            printf("Error: invalid user input!\n");
            return true;
        }
        printf("> action: play move '%c' into square (%d,%d)\n", c, i, j);
        square m;
        if (c == 'd') m = DISCOVERED;
        if (c == 'f') m = FLAGED;
        bool check = game_check_move(g, i, j, m);
        if (!check)
        {
            printf("Error: illegal move on square (%d,%d)!\n", i, j);
            return true;
        }
        game_play_move(g, i, j, m);
        return true; // continue to play
    }
    // else if (c == 'w')
    // { // save
    //     char file_name[10];
    //     int ret = scanf("%s", file_name);
    //     if (ret != 1)
    //     {
    //         printf("Error: invalid user input!\n");
    //         return true;
    //     }
    //     printf("> action: save game\n");
    //     game_save(g, file_name);
    //     return true;
    // }
    else
    {
        printf("Error: invalid user input!\n");
        return true;
    }

    return true; // continue...
}

/* ************************************************************************** */

int main(int argc, char *argv[])
{
    game g = NULL;
    g = game_default();
    // if (argc == 1)
    //     g = game_default();
    // else
    //     g = game_load(argv[1]);

    game_print(g);
    bool over = game_is_over(g);
    bool cont = true;
    while (!over && cont)
    {
        cont = game_step(g);
        over = game_is_over(g);
        if (cont) game_print(g);
    }
    bool won = game_is_won(g);
    bool lost = game_is_lost(g);
    if (won)
        printf("Congratulation, you won ! :-)\n");
    else if (lost)
        printf("Ouch a bomb just blown you up ! X(\n");
    else
        printf("You quit the game ! :-(\n");
    game_delete(g);

    return EXIT_SUCCESS;
}
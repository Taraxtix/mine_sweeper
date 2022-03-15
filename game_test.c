/**
 * @file game_test.c
 * @author Taraxtix (taraxtix.github.io)
 * @brief All Test Functions.
 * @copyright Copyright (c) 2022
 **/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_test.h"

/* ************************************************************************** */
/*                               CHECK ROUTINES                               */
/* ************************************************************************** */

/* if squares == NULL, test if game is empty */
bool check_game(c_game g, uint nb_rows, uint nb_cols, square *squares)
{
    if (!g)
    {
        printf("g is NULL\n");
        return false;
    }

    // nb rows & cols
    if (game_nb_rows(g) != nb_rows)
    {
        printf("nb_rows is incorrect (expected %d, got %d)\n", nb_rows,
               game_nb_rows(g));
        return false;
    }
    if (game_nb_cols(g) != nb_cols)
    {
        printf("nb_cols is incorrect (expected %d, got %d)\n", nb_rows,
               game_nb_rows(g));
        return false;
    }

    // check squares
    for (uint i = 0; i < nb_rows; i++)
        for (uint j = 0; j < nb_cols; j++)
        {
            square s = game_get_square(g, i, j);
            square ss = squares ? squares[i * nb_cols + j] : BLANK;
            if (s != ss)
            {
                printf("wrong square at (%d, %d), (expected %x, got %x)\n", i,
                       j, ss, s);
                return false;
            }
        }

    return true;
}

/* ************************************************************************** */
/*                                MAIN ROUTINE                                */
/* ************************************************************************** */

static void usage(int argc, char *argv[])
{
    if (argc > 0) { exit(EXIT_FAILURE); }
    fprintf(stderr, "Usage: %s <testname>\n", argv[0]);
    exit(EXIT_FAILURE);
}

/* ************************************************************************** */

struct test
{
    char *name;
    int (*func)(void);
};

/* ************************************************************************** */
struct test tests[] = {

    // basic tests (game v1)
    {"new", test_new},
    {"new_empty", test_new_empty},
    {"copy", test_copy},
    {"equal", test_equal},
    {"delete", test_delete},
    {"set_square", test_set_square},
    {"get_size", test_get_size},
    {"get_square", test_get_square},
    {"get_state", test_get_state},
    {"get_flags", test_get_flags},
    {"is_state", test_is_state},
    {"is_flag", test_is_flag},
    {"play_move", test_play_move},
    {"check_move", test_check_move},
    {"is_over", test_is_over},
    {"restart", test_restart},
    // end
    {NULL, NULL}};

/* ************************************************************************** */

int main(int argc, char *argv[])
{
    // run test
    if (argc == 1) usage(argc, argv);
    int ret = -1;
    for (struct test *t = tests; t->name && t->func; t++)
    {
        if (strcmp(argv[1], t->name) == 0)
        {
            ret = t->func();
            break;
        }
    }

    // print test result
    if (ret == -1)
    {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        return EXIT_FAILURE;
    }
    else if (ret == EXIT_SUCCESS)
    {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    }
    else
    {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

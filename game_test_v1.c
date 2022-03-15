/**
 * @file game_test_v1.c
 * @author Taraxtix (taraxtix.github.io)
 * @brief Game Tests V1.
 * @copyright Copyright (c) 2022
 **/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_examples.h"
#include "game_private.h"
#include "game_test.h"

/* ************************************************************************** */
/*                            BASIC TESTS (V1)                                */
/* ************************************************************************** */

int test_new(void)
{
    game g = game_new(DFLT_SIZE, DFLT_SIZE, dflt_squares);
    bool test0 = check_game(g, DFLT_SIZE, DFLT_SIZE, dflt_squares);
    game_delete(g);

    return test0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* ************************************************************************** */

int test_new_empty(void)
{
    game g = game_new_empty(DFLT_SIZE, DFLT_SIZE);
    bool test0 = check_game(g, DFLT_SIZE, DFLT_SIZE, NULL);
    game_delete(g);

    return test0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* ************************************************************************** */

int test_copy(void)
{
    // game empty
    game g1 = game_new_empty(DFLT_SIZE, DFLT_SIZE);
    game g2 = game_copy(g1);
    bool test0 = check_game(g2, DFLT_SIZE, DFLT_SIZE, NULL);
    game_delete(g1);
    game_delete(g2);

    // game default
    game g3 = game_default();
    game g4 = game_copy(g3);
    bool test1 = check_game(g4, DFLT_SIZE, DFLT_SIZE, dflt_squares);
    game_delete(g3);
    game_delete(g4);

    // game other
    game g7 = game_new(2, 3, other_squares);
    game g8 = game_copy(g7);
    bool test2 = check_game(g8, 2, 3, other_squares);
    game_delete(g7);
    game_delete(g8);

    if (test0 && test1 && test2) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_equal(void)
{
    game g1 = game_default();
    game g2 = game_default();
    game g3 = game_default();
    game g4 = game_default();

    bool test1 = (game_equal(g1, g2) == true);

    game_play_move(g3, 0, 0, DISCOVERED);
    bool test2 = (game_equal(g1, g3) == false);

    game_set_square(g4, 0, 0, FLAGED);
    bool test3 = (game_equal(g1, g4) == false);

    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    game_delete(g4);

    if (test1 && test2 && test3) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_delete(void)
{
    game g = game_new_empty(DFLT_SIZE, DFLT_SIZE);
    game_delete(g); // nothing else to do...
    return EXIT_SUCCESS;
}

/* ************************************************************************** */

int test_set_square(void)
{
    game g = game_new_empty(2, 3);
    game_set_square(g, 0, 0, BLANK);
    game_set_square(g, 0, 1, BLANK_D);
    game_set_square(g, 0, 2, BLANK_F);
    game_set_square(g, 1, 0, MINE);
    game_set_square(g, 1, 1, MINE_D);
    game_set_square(g, 1, 2, MINE_F);
    bool test1 = (game_get_square(g, 0, 0) == BLANK);
    bool test2 = (game_get_square(g, 0, 1) == BLANK_D);
    bool test3 = (game_get_square(g, 0, 2) == BLANK_F);
    bool test4 = (game_get_square(g, 1, 0) == MINE);
    bool test5 = (game_get_square(g, 1, 1) == MINE_D);
    bool test6 = (game_get_square(g, 1, 2) == MINE_F);
    if (test1 && test2 && test3 && test4 && test5 && test6) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_get_size(void)
{
    game g1 = game_default();
    bool test1 = game_nb_cols(g1) == DFLT_SIZE && game_nb_rows(g1) == DFLT_SIZE;
    game_delete(g1);

    game g2 = game_new_empty(4, 9);
    bool test2 = game_nb_rows(g2) == 4 && game_nb_cols(g2) == 9;
    game_delete(g2);

    return (test1 && test2) ? EXIT_SUCCESS : EXIT_FAILURE;
}

/* ************************************************************************** */

int test_get_square(void)
{
    game g = game_new(2, 3, other_squares);
    bool test1 = (game_get_square(g, 0, 0) == BLANK);
    bool test2 = (game_get_square(g, 0, 1) == BLANK_D);
    bool test3 = (game_get_square(g, 0, 2) == BLANK_F);
    bool test4 = (game_get_square(g, 1, 0) == MINE);
    bool test5 = (game_get_square(g, 1, 1) == MINE_D);
    bool test6 = (game_get_square(g, 1, 2) == MINE_F);
    game_delete(g);
    if (test1 && test2 && test3 && test4 && test5 && test6) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_get_state(void)
{
    game g = game_new(2, 3, other_squares);
    bool test1 = (game_get_state(g, 0, 0) == BLANK);
    bool test2 = (game_get_state(g, 0, 1) == BLANK);
    bool test3 = (game_get_state(g, 0, 2) == BLANK);
    bool test4 = (game_get_state(g, 1, 0) == MINE);
    bool test5 = (game_get_state(g, 1, 1) == MINE);
    bool test6 = (game_get_state(g, 1, 2) == MINE);
    game_delete(g);
    if (test1 && test2 && test3 && test4 && test5 && test6) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_get_flags(void)
{
    game g = game_new(2, 3, other_squares);
    bool test1 = (game_get_flags(g, 0, 0) == false);
    bool test2 = (game_get_flags(g, 0, 1) == DISCOVERED);
    bool test3 = (game_get_flags(g, 0, 2) == FLAGED);
    bool test4 = (game_get_flags(g, 1, 0) == false);
    bool test5 = (game_get_flags(g, 1, 1) == DISCOVERED);
    bool test6 = (game_get_flags(g, 1, 2) == FLAGED);
    game_delete(g);
    if (test1 && test2 && test3 && test4 && test5 && test6) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_is_state(void)
{
    game g = game_new(2, 3, other_squares);
    bool test1 = game_is_blank(g, 0, 0) && !game_is_blank(g, 1, 0);
    bool test2 = game_is_mined(g, 1, 0) && !game_is_mined(g, 0, 1);
    bool test3 =
        game_get_blank_nb(g, 0, 0) == 2 && game_get_blank_nb(g, 0, 1) == 3;
    game_delete(g);
    if (test1 && test2 && test3) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_is_flag(void)
{
    game g = game_new(2, 3, other_squares);
    bool test1 = game_is_flaged(g, 0, 2) && game_is_flaged(g, 1, 2) &&
                 !game_is_flaged(g, 0, 1) && !game_is_flaged(g, 1, 1);
    bool test2 = game_is_discovered(g, 0, 1) && game_is_discovered(g, 1, 1) &&
                 !game_is_discovered(g, 0, 2) && !game_is_discovered(g, 1, 2);
    game_delete(g);
    if (test1 && test2) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_play_move(void)
{
    // testing chained discover (Test update_flags)
    game g0 = game_default();
    game_play_move(g0, 8, 8, DISCOVERED);
    bool test0 = check_game(g0, DFLT_SIZE, DFLT_SIZE, dflt_br_disco);
    game_delete(g0);

    // Testing the 3 different move possible
    game g1 = game_new(2, 2, won_2x2);
    game_play_move(g1, 0, 0, FLAGED);
    game_play_move(g1, 0, 0, DISCOVERED);
    bool test1 = check_game(g1, 2, 2, lost_2x2);
    if (!test1) printf("test1 failed \n");

    if (test0 && test1) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

/* This function checks that it is possible to play a move at a given position
in the grid. More precisely, a move is said to be legal: 1) if the coordinates
(i,j) are inside the grid, 2) if s is either a blank, light bulb or mark square,
and 3) if the current square at (i,j) is not a black square. */

int test_check_move(void)
{
    game g0 = game_new(2, 3, other_squares);

    // all legal moves
    bool test0 = game_check_move(g0, 0, 0, DISCOVERED) && //
                 game_check_move(g0, 1, 0, DISCOVERED) && //
                 game_check_move(g0, 0, 0, FLAGED) &&     //
                 game_check_move(g0, 1, 0, FLAGED) &&     //
                 game_check_move(g0, 0, 2, FLAGED) &&     //
                 game_check_move(g0, 1, 2, FLAGED);

    // no states
    bool test1 = !game_check_move(g0, 0, 0, BLANK) &&   //
                 !game_check_move(g0, 0, 0, BLANK_D) && //
                 !game_check_move(g0, 0, 0, BLANK_F) && //
                 !game_check_move(g0, 0, 0, MINE) &&    //
                 !game_check_move(g0, 0, 0, MINE_D) &&  //
                 !game_check_move(g0, 0, 0, MINE_F);

    // try to flag a discovered square
    // try to discover an already one
    // try to discover a flaged square
    bool test2 = !game_check_move(g0, 0, 1, FLAGED) &&     //
                 !game_check_move(g0, 0, 2, DISCOVERED) && //
                 !game_check_move(g0, 0, 1, DISCOVERED);

    // invalid coordinates
    bool test3 = !game_check_move(g0, 7, 7, FLAGED) && //
                 !game_check_move(g0, 0, 10, DISCOVERED);

    game_delete(g0);
    if (test0 && test1 && test2 && test3) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_is_over(void)
{
    // default game
    game g1 = game_default();
    bool test1 = !game_is_over(g1);
    game_delete(g1);

    // won game
    game g2 = game_new(2, 2, won_2x2);
    bool test2 = game_is_over(g2) && game_is_won(g2) && !game_is_lost(g2);
    game_delete(g2);

    // lost game
    game g3 = game_new(2, 2, lost_2x2);
    bool test3 = game_is_over(g3) && !game_is_won(g3) && game_is_lost(g3);
    game_delete(g3);

    // empty game
    game g4 = game_new_empty(4, 4);
    bool test4 = !game_is_over(g4);
    game_play_move(g4, 0, 0, DISCOVERED);
    bool test5 = game_is_over(g4) && game_is_won(g4) && !game_is_lost(g4);
    game_delete(g4);

    if (test1 && test2 && test3 && test4 && test5) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

int test_restart(void)
{
    // default game with one random flaged move
    game g1 = game_default();
    game_play_move(g1, 0, 0, FLAGED);
    game_restart(g1);
    bool test1 = check_game(g1, DFLT_SIZE, DFLT_SIZE, dflt_squares);
    game_delete(g1);

    // default after discover the bottom_right square
    game g2 = game_new(DFLT_SIZE, DFLT_SIZE, dflt_br_disco);
    game_restart(g2);
    bool test2 = check_game(g2, DFLT_SIZE, DFLT_SIZE, dflt_squares);
    game_delete(g2);

    if (test1 && test2) return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

/* ************************************************************************** */

/**
 * @file game_test.h
 * @brief All Test Functions.
 * @copyright University of Bordeaux. All rights reserved, 2021.
 **/

#ifndef __GAME_TEST_H__
#define __GAME_TEST_H__

#include "game.h"

/* ************************************************************************** */
/*                               CHECK ROUTINES                               */
/* ************************************************************************** */

bool check_game(c_game g, uint nb_rows, uint nb_cols, square *squares);

/* ************************************************************************** */
/*                                AUX TESTS                                   */
/* ************************************************************************** */

int test_print(void);
int test_default(void);

/* ************************************************************************** */
/*                            BASIC TESTS (V1)                                */
/* ************************************************************************** */

int test_new(void);
int test_new_empty(void);
int test_copy(void);
int test_equal(void);
int test_delete(void);
int test_nb_cols(void);
int test_nb_rows(void);
int test_set_square(void);
int test_get_square(void);
int test_get_state(void);
int test_get_flags(void);
int test_is_state(void);
int test_has_flag(void);
int test_play_move(void);
int test_check_move(void);
int test_is_over(void);
int test_restart(void);
int test_update_flags(void);

#endif // __GAME_TEST_H__
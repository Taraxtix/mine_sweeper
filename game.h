/**
 * @file game.h
 * @author Taraxtix (taraxtix.github.io)
 * @brief Basics game functions
 * @copyright Copyright (c) 2022
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>

/**
 * @brief Different values that a square can have
 * @details Each square of the game have exactly one state
 * and can have any number of flags
 */
typedef enum Square
{
    /* STATES */
    BLANK,       /**< an blank square */
    MINE = 0x09, /**< a square with a mine on it */

    /* FLAGS */
    FLAGED = 0x10,
    DISCOVERED = 0x20,
} square;

/** State mask used in Square enum */
#define S_MASK 0x0F

/** Flag mask used in Square enum */
#define F_MASK 0xF0

/**
 * @brief The structure pointer that stores the game state.
 **/
typedef struct game_s *game;

/**
 * @brief The structure constant pointer that stores the game state.
 * @details That means that it is not possible to modify the game using this
 * pointer.
 **/
typedef const struct game_s *c_game;

typedef unsigned int uint;

/**
 * @brief Creates a new empty game with defaut size.
 * @param nb_cols the number of columns in the game grid.
 * @param nb_rows the number of rows in the game grid.
 * @details All squares are initialized with blank squares.
 * @return the created game
 **/
game game_new_empty(uint nb_cols, uint nb_rows);

/**
 * @brief Creates a new game with default size and initializes it.
 * @param nb_cols the number of columns in the game grid.
 * @param nb_rows the number of rows in the game grid.
 * @param squares an array describing the initial square values (<a
 * href="https://en.wikipedia.org/wiki/row-_and_column-major_order">row-major
 * storage</a>)
 * @pre @p squares must be an initialized array of size (nb_cols * nb_rows).
 * @return the created game
 **/
game game_new(uint nb_cols, uint nb_rows, square *squares);

/**
 * @brief Duplicates a game.
 * @param g the game to copy
 * @return the copy of the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
game game_copy(c_game g);

/**
 * @brief Tests if two games are equal (same states and same flags).
 * @param g1 the first game
 * @param g2 the second game
 * @return true if the two games are equal, false otherwise
 * @pre @p g1 must be a valid pointer toward a game structure.
 * @pre @p g2 must be a valid pointer toward a game structure.
 **/
bool game_equal(c_game g1, c_game g2);

/**
 * @brief Deletes the game and frees the allocated memory.
 * @param g the game to delete
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_delete(game g);

/**
 * @brief Sets the value of a given square.
 * @details This function is useful for initializing the squares of an blank
 * game.
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @pre @p s must be a valid square value.
 **/
void game_set_square(game g, uint i, uint j, square s);

/**
 * @brief Get the numbers of columns in the game.
 * @param g the game
 * @return the numbers of columns in the game
 */
uint game_nb_cols(c_game g);

/**
 * @brief Get the numbers of rows in the game.
 * @param g the game
 * @return the numbers of rows in the game
 */
uint game_nb_rows(c_game g);

/**
 * @brief Gets the raw value of a given square.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return the square value
 **/
square game_get_square(c_game g, uint i, uint j);

/**
 * @brief Gets the state of a given square.
 * @details See description of enum square.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return the square state
 **/
square game_get_state(c_game g, uint i, uint j);

/**
 * @brief Gets the flags of a given square.
 * @details See description of enum square.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return the square flags
 **/
square game_get_flags(c_game g, uint i, uint j);

/**
 * @brief Test if a given square is blank.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return true if the square is blank
 **/
bool game_is_blank(c_game g, uint i, uint j);

/**
 * @brief Test if a given square is a mine.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return true if the square is a mine
 **/
bool game_is_mined(c_game g, uint i, uint j);

/**
 * @brief Get the number of mine neighbooring a blank square.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @pre The square at position (i,j) must be a blank square
 * @return the blank square number
 **/
int game_get_blank_nb(c_game g, uint i, uint j);

/**
 * @brief Test if a given square is flaged (as being a mine).
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return true if the square is flaged
 **/
bool game_is_flaged(c_game g, uint i, uint j);

/**
 * @brief Test if a given square is discovered.
 * @param g the game
 * @param i row index
 * @param j column index
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @return true if the square is discovered
 **/
bool game_is_discovered(c_game g, uint i, uint j);

/**
 * @brief Checks if a given move is legal.
 * @details A move is said legal if:
 * 1) The coordinates (i, j) are inside the grid
 * 2) If m is DISCOVER, the square at (i, j) must not be discovered yet
 * 3) If m is ADD_FLAG, the square at (i, j) must not be flaged yet
 * 4) If m is RM_FLAG, the square at (i, j) must be flaged already
 * @param g the game
 * @param i row index
 * @param j column index
 * @param m the move value
 * @pre @p g must be a valid pointer toward a game structure.
 * @return false if the move is not legal.
 **/
bool game_check_move(c_game g, uint i, uint j, square s);

/**
 * @brief Plays a move in a given square.
 * @details The grid flags are updated consequently after each move.
 * @param g the game
 * @param i row index
 * @param j column index
 * @param s the square value
 * @pre @p g must be a valid pointer toward a game structure.
 * @pre @p i < game height
 * @pre @p j < game width
 * @pre @p m must be either DISCOVER, ADD_FLAG or RM_FLAG.
 * @pre The game square at position (i,j) must not be a black square.
 **/
void game_play_move(game g, uint i, uint j, square s);

/**
 * @brief Update the game's flags
 * @param g the game
 * @details In particular, if a BLANK square with no mined neighboor is
 * discoverd, then discover all his neighboors
 */
void game_update_flags(game g);

/**
 * @brief Checks if the game is won.
 * @param g the game
 * @details This function checks that all the BLANK squares are DISCOVERED
 * and that all MINED squares are FLAGED
 * @return true if the game ended successfully, false otherwise
 * @pre @p g must be a valid pointer toward a game structure.
 **/
bool game_is_won(c_game g);

/**
 * @brief Checks if the game is lost.
 * @param g the game
 * @details This function checks if any of the MINED squares is DISCOVERED
 * @return true if the game is lost, false otherwise
 */
bool game_is_lost(c_game g);

/**
 * @brief Check if the game is over
 * @param g the game
 * @details This function checks if the is game is either won or lost.
 * @return true if the game is over, false otherwise
 */
bool game_is_over(c_game g);

/**
 * @brief Restarts a game.
 * @details All the game is reset to its initial state.
 * In particular all flags are cleared.
 * @param g the game
 * @pre @p g must be a valid pointer toward a game structure.
 **/
void game_restart(game g);

#endif // __GAME_H__
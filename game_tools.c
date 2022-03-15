/**
 * @file game_tools.c
 * @brief Game Tools.
 * @author Taraxtix (taraxtix.github.io)
 * @copyright Copyright (c) 2022
 **/

#include "game_tools.h"
#include "game_private.h"

#include <assert.h>

game game_load(char *filename)
{
    FILE *f = fopen(filename, "r");
    assert(f);

    int ret;
    uint nb_rows, nb_cols;
    char img;

    ret = fscanf(f, "%d %d\n", &nb_rows, &nb_cols);
    assert(ret == 2);

    square squares[nb_rows * nb_cols];
    for (uint i = 0; i < nb_rows; i++)
    {
        for (uint j = 0; j < nb_cols; j++)
        {
            ret = fscanf(f, "%c", &img);
            assert(ret == 1);
            squares[i * nb_cols + j] = _img2square(img);
        }
        fgetc(f);
    }

    fclose(f);
    return game_new(nb_rows, nb_cols, squares);
}

void game_save(c_game g, char *filename)
{
    FILE *f = fopen(filename, "w");
    assert(f);

    fprintf(f, "%d %d\n", game_nb_rows(g), game_nb_cols(g));
    for (uint i = 0; i < game_nb_rows(g); i++)
    {
        for (uint j = 0; j < game_nb_cols(g); j++)
        {
            fprintf(f, "%c", _square2img(SQUARE(g, i, j)));
        }
        fprintf(f, "\n");
    }

    fclose(f);
}
# Mine Sweeper Project
# Copyright University of Bordeaux. All rights reserved, 2021.

cmake_minimum_required(VERSION 3.0)

project("MineSweeper" C)

set(CMAKE_C_FLAGS "-std=c99 -Wall -pthread -Wextra -Wunused-parameter")
set(CMAKE_C_FLAGS_DEBUG "-g -O0 --coverage")    # use CMake option: -DCMAKE_BUILD_TYPE=DEBUG
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")   # use CMake option: -DCMAKE_BUILD_TYPE=RELEASE

############################# SRC #############################

# game library
add_library(game game.c game_aux.c game_private.c)

# game text
add_executable(game_text game_text.c)
target_link_libraries(game_text game)

# EOF
#pragma once

#include "types.h"
#include "term.h"

#define ALIVECHAR L'█'
// #define ALIVECHAR L'#'
#define DEADCHAR L' '

void fillBlock(i32 row, i32 col);
void update_game(buffer_t buffer);
void makePlane(i32 r, i32 c);

void game_init(i32 rows, i32 cols);
void game_end();

#pragma once

#include "types.h"
#include "term.h"

#define BLOCKCHAR L'█'

void fillBlock(u32 row, u32 col);
void update_game(buffer_t buffer);
void makePlane(u32 r, u32 c);

void game_init(u32 rows, u32 cols);
void game_end();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wchar.h>
#include <locale.h>
#include <assert.h>


#include "draw.h"


extern buffer_t screen_buf;


void fillBlock(i32 row, i32 col)
{
	assert(row > -1);
	assert(col > -1);
	i32 index = row * screen_buf.size.cols + col;
	screen_buf.data[index] = ALIVE;
}


cell_state* data_copy;

void game_init(i32 rows, i32 cols) {
	data_copy = malloc(rows * cols * sizeof(cell_state));
}

void game_end() { free(data_copy); }


void update_game(buffer_t buffer)
{
	i32 rows = buffer.size.rows;
	i32 cols = buffer.size.cols;
	cell_state* data = buffer.data;
	// using a new buffer coz over writting in real time will make further computation unreliable.


	for (i32 r = 0; r < rows; ++r)
	{
		for (i32 c = 0; c < cols; ++c)
		{
			i32 offset = r * cols + c;
			cell_state cell = data[offset];

			i32 neighbors_offsets[8][2] = {
				{r + 1, c},
				{r - 1, c},
				{r, c + 1},
				{r, c - 1},
				{r + 1, c + 1},
				{r + 1, c - 1},
				{r - 1, c + 1},
				{r - 1, c - 1}
			};

			i32 neighbors_alive = 0;
			for (i32 i = 0; i < 8; ++i)
			{
				// checking for invalid row, col and offset outside the data indexes
				i32 row = neighbors_offsets[i][0];
				// if (row > rows || row < 0) continue;
				if (row >= rows) row = 0;
				if (row < 0) row = rows - 1;

				i32 col = neighbors_offsets[i][1];
				// if (col > cols || col < 0) continue;
				if (col >= cols) col = 0;
				if (col < 0) col = cols - 1;

				i32 off = row * cols + col;
				if (off > ((rows * cols) - 1) || off < 0)
				{
					continue;
				}

				if (data[off] == ALIVE) neighbors_alive++;
			}

			// GAME RULES
			if (cell == ALIVE)
			{
				// fprintf(stderr, "%d, %d\n", r, c);

				// For a space that is populated:
				// 		Each cell with one or no neighbors dies, as if by solitude.
				if (neighbors_alive < 2) {
					data_copy[offset] = DEAD;
				}

				// 		Each cell with four or more neighbors dies, as if by overpopulation.
				else if (neighbors_alive > 3) {
					data_copy[offset] = DEAD;
				}
				else {
					// Each cell with two or three neighbors survives.
					data_copy[offset] = ALIVE;
				}

			} else {
				// For a space that is empty or unpopulated:
				// 		Each cell with three neighbors becomes populated.
				if (neighbors_alive == 3) {
					data_copy[offset] = ALIVE;
				} else {
					data_copy[offset] = DEAD;
				}
			}
		}
	}
	// fprintf(stderr, "\n");

	memcpy(data, data_copy, rows * cols * sizeof(cell_state));
}

void makePlane(i32 r, i32 c)
{
	i32 block[9][2] = {
		{r - 1, c - 1},
		{r - 1, c},
		{r - 1, c + 1},
		{r, c - 1},
		{r, c},							// the col itself
		{r, c + 1},
		{r + 1, c - 1},
		{r + 1, c},
		{r + 1, c + 1},
	};

	i32 cell_indexes[5] = {1, 5, 6, 7, 8};

	// looping over the indexes of blocks required to be filled;
	for (i32 i = 0; i < 5; i++)
	{
		i32 cell_index = cell_indexes[i];
		i32 row = block[cell_index][0],
				col = block[cell_index][1];
		assert(row > -1 && col > -1 && "INVALID BLOCK !");
		fillBlock(row, col);
	}
	
};

/*

34, 34
35, 35
35, 36
36, 34
36, 35

x - -
- x x
x x -

34, 35
35, 36
36, 34
36, 35
36, 36

- x -
- - x
x x x

35, 34
35, 36
36, 35
36, 36

- - -
x - x
- x x
*/
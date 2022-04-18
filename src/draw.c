#include <stdio.h>
#include <stdlib.h>

#include <wchar.h>
#include <locale.h>



#include "draw.h"


extern buffer_t screen_buf;


void fillBlock(u32 row, u32 col)
{
	u32 index = row * screen_buf.size.cols + col;
	screen_buf.data[index] = BLOCKCHAR;
}

wchar_t* data_copy;

void game_init(u32 rows, u32 cols) {
	data_copy = malloc(rows * cols * sizeof(wchar_t));
}
void game_end() {free(data_copy);}


void update_game(buffer_t buffer)
{
	u32 rows = buffer.size.rows;
	u32 cols = buffer.size.cols;
	wchar_t* data = buffer.data;
	// using a new buffer coz over writting in real time will make further computation unreliable.


	for (u32 r = 0; r < rows; ++r)
	{
		for (u32 c = 0; c < cols; ++c)
		{
			u32 offset = r * cols + c;
			wchar_t cell = data[offset];

			u32 neighbors_offsets[8][2] = {
				{r + 1, c},
				{r - 1, c},
				{r, c + 1},
				{r, c - 1},
				{r + 1, c + 1},
				{r + 1, c - 1},
				{r - 1, c + 1},
				{r - 1, c - 1}
			};

			u32 neighbors_alive = 0;
			for (u32 i = 0; i < 8; ++i)
			{
				// checking for invalid row, col and offset outside the data indexes
				u32 row = neighbors_offsets[i][0];
				if (row > rows || row < 0) continue;
				// if (row > rows) row = 0;
				// if (row < 0) row = rows;

				u32 col = neighbors_offsets[i][1];
				if (col > cols || col < 0) continue;
				// if (col > cols) col = 0;
				// if (col < 0) col = cols;

				u32 off = row * cols + col;
				if (off > ((rows * cols) - 1) || off < 0)
				{
					continue;
				}

				if (data[off] == BLOCKCHAR) neighbors_alive++;
			}

			// GAME RULES
			if (cell == BLOCKCHAR)
			{
				// For a space that is populated:
				// 		Each cell with one or no neighbors dies, as if by solitude.
				if (neighbors_alive < 2) {
					data_copy[offset] = L' ';
				}

				// 		Each cell with four or more neighbors dies, as if by overpopulation.
				else if (neighbors_alive > 3) {
					data_copy[offset] = L' ';
				}
				else {
					// Each cell with two or three neighbors survives.
					data_copy[offset] = BLOCKCHAR;
				}

			} else {
				// For a space that is empty or unpopulated:
				// 		Each cell with three neighbors becomes populated.
				if (neighbors_alive == 3) {
					data_copy[offset] = BLOCKCHAR;
				} else {
					data_copy[offset] = L' ';
				}
			}
		}
	}

	memcpy(data, data_copy, rows * cols * sizeof(wchar_t));
}

void makePlane(u32 r, u32 c)
{
	u32 block[9][2] = {
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

	u32 cell_indexes[5] = {1, 5, 6, 7, 8};

	for (u32 i = 0; i < 5; i++)
	{
		u32 cell_index = cell_indexes[i];
		u32 row = block[cell_index][0],
				col = block[cell_index][1];
		fillBlock(row, col);
	}
	
};

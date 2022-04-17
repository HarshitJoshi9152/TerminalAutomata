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


void update_game(buffer_t buffer)
{
	u32 rows = buffer.size.rows;
	u32 cols = buffer.size.cols;
	wchar_t* data = buffer.data;

	for (u32 r = 0; r < rows; ++r)
	{
		for (u32 c = 0; c < cols; ++c)
		{
			u32 offset = r * cols + c;
			wchar_t cell = data[offset];

			u32 neighbors_offsets[8] = {
				(r + 1) * cols + c,
				(r - 1) * cols + c,
				r * cols + (c + 1),
				r * cols + (c - 1),
				(r + 1) * cols + (c + 1),
				(r + 1) * cols + (c - 1),
				(r - 1) * cols + (c + 1),
				(r - 1) * cols + (c - 1),
			};

			u32 neighbors_alive = 0;
			for (u32 i = 0; i < 8; ++i)
			{
				u32 offset = neighbors_offsets[i];
				if (offset > (rows * cols - 1) || offset < 0)
				{
					// invalid offset, outside the data indexes
					continue;
				}
				if (data[offset] == BLOCKCHAR) neighbors_alive++;
			}

			if (cell == BLOCKCHAR)
			{
				// For a space that is populated:
				// 		Each cell with one or no neighbors dies, as if by solitude.
				if (neighbors_alive < 2) {
					data[offset] = ' ';
				}

				// 		Each cell with four or more neighbors dies, as if by overpopulation.
				if (neighbors_alive > 3) {
					data[offset] = ' ';
				}

				// 		Each cell with two or three neighbors survives.

			} else {
				// For a space that is empty or unpopulated:
				// 		Each cell with three neighbors becomes populated.
				if (neighbors_alive > 2) {
					data[offset] = BLOCKCHAR;
				}
			}
		}
	}
}

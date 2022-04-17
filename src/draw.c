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
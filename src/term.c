#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "types.h"
#include "term.h"

#define COLS_CMD "tput cols"
#define ROWS_CMD "tput lines"
#define MAX_RES_DIGITS 5


term_res_t get_resolution()
{
	term_res_t res = {0};
	
	// because we need the count of elements in the row/col !
	// FILE* rows_s = popen(COLS_CMD, "r");
	// FILE* cols_s = popen(ROWS_CMD, "r");
	FILE* cols_s = popen(COLS_CMD, "r");
	FILE* rows_s = popen(ROWS_CMD, "r");

	// 1 is NULL char so we can accept 4 digits should be pretty safe ....hmmm
	char col_count_str[MAX_RES_DIGITS] = {0};
	char row_count_str[MAX_RES_DIGITS] = {0};

	// reading output of commands.
	fgets(col_count_str, MAX_RES_DIGITS, cols_s);
	fgets(row_count_str, MAX_RES_DIGITS, rows_s);

	// sscanf(col_count_str, "%lu", &cols);
	// sscanf(row_count_str, "%lu", &rows);
	res.cols = atol(col_count_str);
	res.rows = atol(row_count_str);

	pclose(cols_s);
	pclose(rows_s);
	
	return res;
}

buffer_t get_term_buffer(term_res_t res)
{
	u64 size = res.cols * res.rows;

	buffer_t buffer = {
		.data = (char*)malloc(size),
		.prev_data = (char*)malloc(size),
		.size = res
	};
	// printf("size :%ld\n", size);

	// memset(buffer.data, 65, size);

	// 10 Print
	for (int r = 0; r < res.rows; ++r) {
		for (int c = 0; c < res.cols; ++c) {
			u32 offset = r * res.cols + c;
			// printf("offset: %d\n", offset);
			buffer.data[offset] = (offset % 2 == 0) ? '/' : '\\';
			buffer.prev_data[offset] = (offset % 2 == 0) ? '/' : '\\';   // if we use this line first render will be blank!
		}
	}

	// memset(buffer.prev_data, 0, size); // if we use this line first render will not be blank!
	
	return buffer;
}

void free_term_buffer(buffer_t buffer) {
	free(buffer.data);
	free(buffer.prev_data);
}

// inline works differently in c and cpp
void set_cursor(u32 row, u32 col) {
	printf("\x1b[%d;%dH", row, col);
}


void render_term_buffer_FORCE(buffer_t buffer) {

	printf("\x1b[1;1H"); // resetting the cursor position on each render

	u32 rows = buffer.size.rows;
	u32 cols = buffer.size.cols;
	char* data = buffer.data;

	for (u32 r = 0; r < rows; ++r) {
		for (u32 c = 0; c < cols; ++c) {
			u32 offset = r * cols + c;
			printf("%c", data[offset]);
		}
	}
}


// todo minimise the no of printf calls
void render_term_buffer(buffer_t buffer)
{
	printf("\x1b[1;1H"); // resetting the cursor position on each render

	u32 rows = buffer.size.rows;
	u32 cols = buffer.size.cols;
	char* data = buffer.data;
	char* prev_data = buffer.prev_data;

	bool is_data_same = true;

	bool cursor_updated = true;

	for (u32 r = 0; r < rows; ++r) {
		for (u32 c = 0; c < cols; ++c) {
			u32 offset = r * cols + c;
			// check if the char is new/unique
			if (prev_data[offset] != data[offset])
			{
				// updating cursor
				if (!cursor_updated) {
					set_cursor(r+1, c+1);			// maybe this is causing the screen to shift below
					cursor_updated = true;
				}

				// actually rendering
				printf("%c", data[offset]);


				// if (is_data_same) is_data_same = false;
				// copying main buffer's data to prev_buffers
				prev_data[offset] = data[offset];
			}
			else {
				// we are not rendering the same characters !
				// but skipping them causes the cursor to lag behind so we have to update is later when we encounter a unique char
				cursor_updated = false;
			}
			// usleep(1);
		}
	}
}

char Elements[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75};

void random_buffers_mut(buffer_t buffer)
{	
	u32 rows = buffer.size.rows;
	u32 cols = buffer.size.cols;
	char* data = buffer.data;
	// char* prev_data = buffer.prev_data;

	// r=0; coz rows * cols + c would overflow ! (size is rows * cols)
	for (u32 r = 0; r < rows; ++r) {
		for (u32 c = 0; c < cols; ++c) {
			u32 offset = r * cols + c;
			if (rand() % 100 < 10)
			{
				data[offset] = Elements[rand() % (sizeof(Elements)/sizeof(Elements[0]))];
			}
		}
	}
}

// tput civis
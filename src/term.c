#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "term.h"

#define COLS_CMD "tput cols"
#define ROWS_CMD "tput lines"
#define MAX_RES_DIGITS 5


term_res_t get_resolution()
{
	term_res_t res = {0};
	
	// because we need the count of elements in the row/col !
	FILE* rows_s = popen(COLS_CMD, "r");
	FILE* cols_s = popen(ROWS_CMD, "r");

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
		.size = res
	};
	memset(buffer.data, 65, size);
	return buffer;
}

void free_term_buffer(buffer_t buffer) {
	free(buffer.data);
}

void render_term_buffer(buffer_t buffer)
{
	u32 rows = buffer.size.rows;
	u32 cols = buffer.size.cols;
	char* data = buffer.data;

	u64 count = 0;

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			u32 offset = r * cols + c;
			// printf("%d", count % 10);
			printf("%c", data[offset]);
			count++;
		}
	}
	// printf("COutner %d\n", count); = 5328
}
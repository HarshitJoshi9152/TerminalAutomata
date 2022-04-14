#include <stdlib.h>
#include <stdio.h>

#include "types.h"


#define COLS_CMD "tput cols"
#define ROWS_CMD "tput lines"
#define MAX_RES_DIGITS 5


term_res_t get_resolution() {

	term_res_t res = {0};
	
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
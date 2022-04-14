// started at 23:23

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "types.h"
#include "term.h"

int main(int argc, char **argv)
{
	system("clear");
	term_res_t term_res = get_resolution();
	// printf("cols: %d\n", term_res.cols);
	// printf("rows: %d\n", term_res.rows);

	buffer_t screen_buf = get_term_buffer(term_res);
	render_term_buffer(screen_buf);

	free_term_buffer(screen_buf);

	return EXIT_SUCCESS;
}
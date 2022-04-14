// started at 23:

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include <unistd.h>

#include "types.h"
#include "term.h"

// https://hackingcpp.com/cpp/beginners_guide.html

int main(int argc, char **argv)
{

	term_res_t term_res = get_resolution();

	printf("cols: %d\n", term_res.cols);
	printf("rows: %d\n", term_res.rows);

	return EXIT_SUCCESS;
}
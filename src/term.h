#pragma once

#include "types.h"

typedef struct term_res_s {
	u32 cols;
	u32 rows;
} term_res_t;

typedef struct buffer_s {
	char *data;
	term_res_t size;
} buffer_t;

term_res_t get_resolution();
buffer_t get_term_buffer(term_res_t res);
void free_term_buffer(buffer_t buffer);

void render_term_buffer(buffer_t buffer);
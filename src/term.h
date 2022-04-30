#pragma once

#include <wchar.h>

#include "types.h"
typedef struct term_res_s {
	i32 cols;
	i32 rows;
} term_res_t;

// wish i could make this take up just 1 bit
typedef enum {
	DEAD,
	ALIVE
} cell_state;

// wchar_t PRINT_CHARACTERS[2] = {
// 	[ALIVE] = L'█',
// 	[DEAD] = L' '
// };

typedef struct buffer_s {
	cell_state *data;
	cell_state *prev_data;
	term_res_t size;
} buffer_t;

term_res_t get_resolution();
buffer_t get_term_buffer(term_res_t res);
void free_term_buffer(buffer_t buffer);

void render_term_buffer(buffer_t buffer);
void render_term_buffer_FORCE(buffer_t buffer);
void set_cursor(i32 row, i32 col);

void random_buffers_mut(buffer_t buffer);

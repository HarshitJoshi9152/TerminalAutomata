// started at 23:23

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <locale.h>
#include <wchar.h>

#include "types.h"
#include "term.h"
#include "draw.h"


#define MEMSAFE 1
#define DELTA_TIME 100

// to be freed if we have any error so it needs to be a global
buffer_t screen_buf = {0};
bool rendering = true;
extern u32 mismatch_count;

// cleanup function
void cleanup(void) {
	free_term_buffer(screen_buf);
	// set_cursor(screen_buf.size.rows, screen_buf.size.cols);
	system("tput cnorm"); // makes the cursor reappear
	// system("tput rmcup");	// restore the screen
}

void sig_handler(int signo)
{
  if (signo == SIGINT) {
		rendering = false;
	}
}

int main(int argc, char **argv)
{
	atexit(&cleanup); // wtf, was this error
	system("tput civis"); // makes the cursor disappear
	// system("tput smcup");			// save the screen
	system("clear");				// todo instead of clearing do tput smcup;
	setlocale(LC_CTYPE, "");

	term_res_t term_res = get_resolution();
	screen_buf = get_term_buffer(term_res);

	// ctrl+c sets rendering to false
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	{
		fprintf(stderr, "could not attach signal_handler %m");
#ifdef MEMSAFE
		exit(1);
#endif
	}

	// main game loop
	u64 frame_count = 0;
	while (rendering)
	{
		// update loop
		update_game(screen_buf);

		// manually change the buffer value to SOME STRING to inspect the issue
		// render_term_buffer(screen_buf);
		render_term_buffer_FORCE(screen_buf); // hmm just using this wont work we have to measure the time between each frame or fps
		// there is some error in render_term_buffer_FORCE too it is making the screen switch downwards by a lot !

		frame_count++;
		if (frame_count == 2) {
			random_buffers_mut(screen_buf);
		}
		usleep(DELTA_TIME * 1000); // usleep takes microseconds. 1000micros = 1millis
	}

	// free_term_buffer(screen_buf);
	set_cursor(screen_buf.size.rows, 0);
	wprintf(L"\n\n");
	wprintf(L"frame_count : %lu\n", frame_count);

	return EXIT_SUCCESS;
}
// signal, sigaction

// from: https://www.linuxcommand.org/lc3_adv_tput.php
// # Save screen contents and make cursor invisible
// tput smcup; tput civis
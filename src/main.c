// started at 23:23

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#include "types.h"
#include "term.h"


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
	set_cursor(screen_buf.size.rows, 0);
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
	system("clear");

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
		// manually change the buffer value to SOME STRING to inspect the issue
		render_term_buffer(screen_buf);
		// render_term_buffer_FORCE(screen_buf); // hmm just using this wont work we have to measure the time between each frame or fps

		random_buffers_mut(screen_buf);


		frame_count++;
		// if (frame_count > 0) rendering = false;
		usleep(DELTA_TIME * 1000); // usleep takes microseconds. 1000micros = 1millis
	}

	// free_term_buffer(screen_buf);
	printf("\n\n");
	printf("frame_count : %lu\n", frame_count);

	return EXIT_SUCCESS;
}
// signal, sigaction
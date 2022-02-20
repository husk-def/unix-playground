#include <sys/param.h>

/* ... */
/* 
 * goes through file descriptors
 * STDIN_FILENO
 * STDOUT_FILENO
 * STDERR_FILENO
 * ...
 * until it hits an end (NOFILE)
 * and closes all of them
 */
for (i = 0; i < NOFILE; ++i) {
	close(i);
}
/* ... */

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
/*
 * its inportant to know that UNIX kernel closes
 * all open file descriptors in a process when
 * that process terminates
 */


/* ... */

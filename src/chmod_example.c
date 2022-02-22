#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>

int
main(void)
{
	/* variables */
	struct stat		statbuf;	
	/* implementation */
	/* update the foo permisions: turn on set-group-ID and turn off group-execute of file foo */
	assert(stat("foo", &statbuf) >= 0);
	assert(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) >= 0);
	/* set absolute mode of file bar to "rw-r--r--" */
	assert(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) >= 0);
	exit(0);
}

/* 
after running umask_example.c
$ ls -l foo bar
-rw-r--r--	1	sar		0 date bar
-rw-rwS-rw- 1	sar		0 date foo

ls command lists the group-execute permission of foo to S to signify that
the set-group-ID bit is set without the group-execute bit being set.
*/

#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int
main(void)
{
	umask(0); /* any permission can be set */
	assert(creat("foo", RWRWRW) >= 0);
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); /* group read/write and other read/write cannot be set */
	assert(creat("bar", RWRWRW) >= 0);
	exit(0);
}

/*
$ umask
002
$ ls -l foo bar
-rw------- 1 sar 		0 date bar
-rw-rw-rw- 1 sar 		0 date foo
$ umask
002

changing the file mode creation mask of a process
doesn't affect the mask of its parent(often a shell)
*/

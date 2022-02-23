#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

int
main(void)
{
	assert(open("tempfile", O_RDWR) >= 0);
	assert(unlink("tempfile") >= 0);
	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	exit(0);
}

/*
the property of unlink is often used by a pogrm to ensure
that a temporary file it creates won't be left around in
case the program crashes. The process creates a fil using
either open or creat and the immediately calls unlink.
The file is not deleted, because it's still open. Only when
the process either closes the file or terminates, which
causes the kernel to close all its open files, is the file
deleted.
*/

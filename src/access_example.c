#include <fcntl.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	assert(argc == 2);
	assert(access(argv[1], R_OK) >= 0); /* test for read permission */
	printf("read access OK\n");
	exit(0);
}

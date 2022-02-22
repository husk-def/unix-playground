#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int
main(int argc, char *argv[])
{
    /* variables */
    int    val;
    /* implementation */
    assert(argc == 2); 
    assert((val = fcntl(atoi(argv[1]), F_GETFL, 0)) >= 0);
    switch (val & O_ACCMODE) {
    case O_RDONLY:
    	printf("read only");
    	break;
    case O_WRONLY:
    	printf("write only");
    	break;
    case O_RDWR:
    	printf("read write");
    	break;
    default:
    	perror("unknown access mode");
    }
    if (val & O_APPEND)
    	printf(", append");
    if (val & O_NONBLOCK)
    	printf(", nonblocking");
    if (val & O_SYNC)
    	printf(", synchronous writes");
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if (val & O_FSYNC)
		printf(", synchonous writes");
#endif
	putchar('\n');
	exit(0);
}

/*
$ ./a.out 0 </dev/tty
read only
$ ./a.out 1 >temp.foo
$ cat temp.foo
write only
$ ./a.out 2 2>>temp.foo
write only, append
$ ./a.out 5 5<>temp.foo
read write

the clause 5<>temp.foo opens the file temp.foo for reading and writing on fd 5
*/

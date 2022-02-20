#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    errno = ENOENT;
    fprintf(stderr, "enoent: %s\n", strerror(errno));
    /* 
    * dobra praksa je proslediti ime programa (argv[0])
    * zato sto ukoliko bismo koristili pipe ili slicno,
    * znacemo koji program je uzrokovao gresku 
    */
    perror(argv[0]);
    exit(0);
}

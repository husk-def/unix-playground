#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (int argc, char **argv)
{
    /* variables */
    char    instruction[100];
    char    file[20];
    char    executable[18];
    /* implementation */
    if (argc != 2) {
        printf ("compile [anyfile.c]\n");
        exit (-1);
    }
    strncpy(file, argv[1], 19);
    sscanf(file, "%[^.]s", executable);

    sprintf(instruction, "gcc -ansi %s -o %s", file, executable);
    puts(instruction);
    system(instruction);
    sprintf(instruction, "mv %s bin/", executable);
    puts(instruction);
    system(instruction);

    exit(0);
}

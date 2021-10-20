#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s [--hello | --hi]\n", argv[0]);
        exit(1);
    }
    if (!strcmp(argv[1], "--hello"))
    {
        printf("Hello!\n");
    }
    else if (!strcmp(argv[1], "--hi"))
    {
        printf("Hi!\n");
    }
    return 0;
}
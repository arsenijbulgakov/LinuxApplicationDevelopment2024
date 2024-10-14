#include <stdio.h>
#include <stdlib.h>

void print_range(int start, int stop, int step)
{
    for (int i = start; i < stop; i += step) {
        printf("%d\n", i);
    }
}


int main(int argc, char **argv)
{
    int start = 0;
    int stop = 0;
    int step = 1;


    if (argc == 1) {
        printf("There are no arguments specifying the range\n");
        return 0;
    }
    
    if (argc == 2) {
        stop = atoi(argv[1]);
    } else if (argc == 3) {
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
    } else if (argc == 4) {
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
        step = atoi(argv[3]);
    } else {
        printf("There are too many arguments\n");
        return 0;
    }

    print_range(start, stop, step);
}
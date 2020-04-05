#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{
    int i,x,y = 0;
    int size = atoi(argv[1]);
    int max_range = atoi(argv[2]);

    if (argc < 3)
    {
        printf("Error: Please provide an integer number of a data size followed by maximum range of the data as arguments.\n");
        printf("Example: ./a.out 10 100\n");
        exit(EXIT_FAILURE);
    }

    printf("%d\n",size);
    for(i = 0; i < size; i++)
    {
        x = rand() % max_range;
        y = rand() % max_range;
        printf("%d %d\n",x,y);
    }
}


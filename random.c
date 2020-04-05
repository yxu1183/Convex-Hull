/* 
    Name: Yunika Upadhayaya
    Student ID: 1001631183

    Generated random coordinates:
        -> Any number and range of random coordinates can be         generated.
        -> Generated coordinates are then written onto the file.
*/

#include <stdio.h>
#include <stdlib.h>

void generate_random_file(int size,int max_range);

int main (int argc, char *argv[])
{
    int size = atoi(argv[1]);
    int max_range = atoi(argv[2]);

    if (argc < 3)
    {
        printf("Error: Please provide an integer number of a data size followed by maximum range of the data as arguments.\n");
        printf("Example: ./a.out 10 100\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        generate_random_file(size,max_range);  
        printf("Writing to the file successful!\n");
    }
    
    return 0;
}

void generate_random_file(int size, int max_range)
{
    int i,x,y = 0;
    FILE *fp;
    fp = fopen("random.txt","w");

    // if(fp == NULL)
    // {
    //     printf("Error\n");
    //     exit(EXIT_FAILURE);
    // }

    fprintf(fp, "%d\n",size);

    for(i = 0; i < size; i++)
    {
        x = rand() % max_range;
        y = rand() % max_range;
        fprintf(fp,"%d %d\n",x,y);
    }

    fclose(fp);    
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point
{
    int x;
    int y;
};

int main()
{
    int i = 0;
    int total_points = 0;;
    printf("\nEnter total points you want to check for: ");
    scanf("%d",&total_points);
    struct Point arr_points[total_points];
    printf("\nEnter two numbers separated by a space for (e.g.: 10 15):\nStop with: 0 0\n");
    for(i = 0; i < total_points; i++)
    {
        scanf("%d %d",&arr_points[i].x,&arr_points[i].y);

        if(arr_points[i].x == 0 && arr_points[i].y == 0)
        {
            break;
        }
        else
        {

        }
        
    }

    printf("Printing all the points to compute convex hall.\n");
    printf(" x\t y\n");
    for(i = 0; i < total_points; i++)
    {
        printf("%d\t%d\n",arr_points[i].x,arr_points[i].y);
    }
    return 0;
}


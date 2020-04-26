#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
    -> We are usng graham's scan to solve the convex hall problem, 
       graham's scan solves it by mainting a stack of  S of all the points.
    -> It pushes each point of the input set onto the stack one time,
       and then pops from the stack each point which is not a vertex. 
    -> When, the function finishes stack contains exactly the vertices of 
       all the convex hull in counterclocl wise direction from their appearance
       of the boundary.
*/
typedef struct Point
{
    int x;
    int y;
}Point;

//Point P0;

int minimum_index = 1;

void swap_bottom(int total, Point points[total], int first_index, int second_index)
{
    Point temp = points[first_index];
    points[first_index] = points[second_index];
    points[second_index] = temp;
}
/*
    This function returns true if there are two tie y-values.
*/
bool tie_case(int y_min, int y, int x, int x_min)
{
    bool flag = false;

    if(y_min == y)
    {
        if(x < x_min)
        {
            flag = true;
        }
    }
    return flag;
}

/*
    Find the point with minimum y-coordinate.
*/
int min_y(int total_points, Point points[total_points])
{
    int bottom_y = points[0].y;
    int i = 1;
    while(i < total_points)
    {
        int point_y = points[i].y;
        /*
            Takes into consideration the tie-case: if there are same minimum y-value, 
            it will return the left-most one.
        */
        bool tie = tie_case(bottom_y,point_y,points[i].x,points[minimum_index].x);
        if((point_y < bottom_y) || (tie == true))
        {
            bottom_y = points[i].y;
            minimum_index = i;
        }
        i++;
    }
    return bottom_y;
}

/*

*/
void convexHull(int total_points, Point points[total_points])
{
    int bottom_y = min_y(total_points,points);
    swap_bottom(total_points, points,0,minimum_index);
}

int main()
{
    int i = 0;
    int total_points = 0;;
    printf("\nEnter total points you want to check for: ");
    scanf("%d",&total_points);
    Point arr_points[total_points];
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

    // printf("Printing all the points to compute convex hall.\n");
    // printf(" x\t y\n");
    // for(i = 0; i < total_points; i++)
    // {
    //     printf("%d\t%d\n",arr_points[i].x,arr_points[i].y);
    // }

    convexHull(total_points,arr_points);

    // printf(" x\t y\n");
    // for(i = 0; i < total_points; i++)
    // {
    //     printf("%d\t%d\n",arr_points[i].x,arr_points[i].y);
    // }
    // return 0;
}


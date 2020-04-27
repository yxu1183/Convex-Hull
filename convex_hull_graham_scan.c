/*
    Name: Yunika Upadhayaya
    Student ID: 1001631183
*/

/*
    -> We are usng graham's scan to solve the convex hall problem, 
       graham's scan solves it by mainting a stack of  S of all the points.
    -> It pushes each point of the input set onto the stack one time,
       and then pops from the stack each point which is not a vertex. 
    -> When, the function finishes stack contains exactly the vertices of 
       all the convex hull in counterclock wise direction from their appearance
       of the boundary.
*/

//My header files for the code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

//Maximum number of convex hall points that can be computed.
#define MAX_POINTS  1000

//Minimum index for the minimum y value.
int minimum_index = 1;

//Size of my stack 
int size = -1;

//A struct for my coordinates
typedef struct Point
{
    int x;
    int y;
}Point;

//A global P0 to later find the orientation with respect to this point.
Point P0;

//My struct point stack to push and pop the points.
struct Point stack[MAX_POINTS];

//This function returns true if there are two tie y-values.
bool tie_case(int y_min, int y, int x, int x_min)
{
    bool flag = false;

    if (y_min == y)
    {
        if (x < x_min)
        {
            flag = true;
        }
    }
    return flag;
}

//Finds the point with minimum y-coordinate.
int min_y(int total_points, Point points[total_points])
{
    int bottom_y = points[0].y;
    int i = 1;
    while (i < total_points)
    {
        int point_y = points[i].y;
        /*
            Takes into consideration the tie-case: if there are same minimum y-value, 
            it will return the left-most one.
        */
        bool tie = tie_case(bottom_y, point_y, points[i].x, points[minimum_index].x);
        if ((point_y < bottom_y) || (tie == true))
        {
            bottom_y = points[i].y;
            minimum_index = i;
        }
        i++;
    }
    return bottom_y;
}

/*
    Swaps the bottom most point to the first position
*/
void swap_bottom(int total, Point points[total], int first_index, int second_index)
{
    Point temp = points[first_index];
    points[first_index] = points[second_index];
    points[second_index] = temp;
}

/*
    Inorder to find the orientation, we calculate the 
    cross product of the ordered triplets(p0,p1,p2).
*/
int find_orientation(Point p0, Point p1, Point p2)
{
    /*
        -> Used formula: (p1 - p0) * (p2 - p1)
        -> if it returns postive (1), and our current vector is p0p1,
           then the segement p0p1 lies clockwise from p0p2 
        -> if it returns negative (-1), and our current vector is p0p1,
           then the segment p0p1 lies counterclockwise from p0p2
        -> it it returns 0, then they are collinear.
    */
    int cross_product = (p1.y - p0.y) * (p2.x - p1.x) -
                        (p1.x - p0.x) * (p2.y - p1.y);
    if (cross_product == 0)
    {
        return 0;
    }
    else if (cross_product > 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

/*
    This function finds the distance between two points, lets
    say if point p1 is fixed, then it computes distances p1p2 & p1p3
    Returns:
    -> -1 for the highest distance.
    -> 1 for shortest distance.
*/
int greater_distance(Point p1, Point p2, Point p3)
{
    int first_distance = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    int second_distance = (p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y);
    if (first_distance >= second_distance)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

/*
    This is a compare function used by qsort function to sort an array with respect to the first point (P0).
*/
int compare_coordinates(const void *p, const void *q)
{
    Point *P1 = (Point *)p;
    Point *P2 = (Point *)q;

    int orint = find_orientation(P0, *P1, *P2);
    if (orint == 0)
    {
        return greater_distance(P0, *P2, *P1);
    }
    if (orint == -1)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

/*
    This function checks if more than one point has 
    same orientation,so that we could get the farthest point.
    It also updates the size of the array.
*/
int check_orientation(int total, Point points[total])
{
    //Initialize the new size of our array
    int new_size = 1;
    int counter = 1;
    while (counter < total)
    {
        //Go through all the points until we find the points in same angle
        //w.r.t PO and keep the farthest one
        while (counter < total - 1 && find_orientation(P0, points[counter], points[counter + 1]) == 0)
        {
            counter++;
        }
        points[new_size] = points[counter];
        //Update the new size of our array 
        new_size = new_size + 1;
        counter = counter + 1;
    }
    return new_size;
}

//Push the points onto the stack
void push(Point P)
{
    size = size + 1;
    stack[size] = P;
}

//Pop the points out of the stack
void pop()
{
    size = size - 1;
}

//Display all my convex hull points.
void print()
{
    int i = 0;
    for(i = 0; i <= size; i++)
    {
        printf("%d\t%d\n",stack[i].x,stack[i].y);
    }
}
void convexHull(int total_points, Point points[total_points])
{
    //Finds the coordinate with minimum y-value.
    int bottom_y = min_y(total_points, points);
    //Swap the coordinate with minimum y-value to the first place.
    swap_bottom(total_points, points, 0, minimum_index);

    //Sort (total_points-1) with respect to the first point.
    //We are sorting the points in counterclockwise direction,
    //i.e if point P2 has larger polar angle than the point p1, point p1 comes before pont P2
    P0 = points[0];
    qsort(&points[1], total_points - 1, sizeof(Point), compare_coordinates);

    //Next we check if one or more have same orientation (polar anggle) with P0.
    //We remove all and keep the one that is farthest from P0.
    //Then, we update the size of our array.
    int updated_size = check_orientation(total_points, points);

    //If our new size is less than 3, then we cannot find the convex hall for given points
    if(updated_size < 3)
    {
        return;
    }

    //We push our first three points onto the stack created before.
    push(points[0]);
    push(points[1]);
    push(points[2]);

    //We will keep removing the top if the angle formed by the points:
    //after-top, top and points[i] makes a right turn.
    int i = 1;
    for(i = 3; i <updated_size; i++)
    {
        while(find_orientation(stack[size-1],stack[size],points[i])>-1)
        {
            pop();
        }
        push(points[i]);
    }

    //Display my convex hall points.
    printf("\n");
    printf("Following vertices form the convex hull.\n");
    printf(" x\t y\n");
    print();
}

int main()
{
    int i = 0;
    int total_points = 0;
    //Takes the input from the file as well as user inputed points
    printf("\nEnter total points you want to check for: ");
    scanf("%d", &total_points);
    Point arr_points[total_points];
    printf("\nEnter two numbers separated by a space for (e.g: 10 15):\n");
    for (i = 0; i < total_points; i++)
    {
        scanf("%d %d", &arr_points[i].x, &arr_points[i].y);
    }
    //Print all original points.
    printf("\nPrinting all the points to compute convex hall.\n");
    printf(" x\t y\n");
    for (i = 0; i < total_points; i++)
    {
        printf("%d\t%d\n", arr_points[i].x, arr_points[i].y);
    }

    //Compute all the vertices for convex hall.
    convexHull(total_points, arr_points);
    return 0;
}

#include "memcheck.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void update(int * line, int * row, int length)
/* This function updates the values in the array. If the current cell we 
 * are looking to update is empty (has a value of 0) and one of the two 
 * cells next to it, but not both, are full (has a value of 1) update 
 * value of the cell to be full. Anything else, and we will set the cell
 * to be empty */
{
    int i;
    int * previous;
    int * current;
    int * next;
    int * new;
    
    previous = line;
    current = line + 1;
    next = line + 2;
    new = row + 1;
    
    for (i = 1; i < length - 1; i++) 
    {
        if (*current == 0 && (*previous + *next == 1))
        {
            *new = 1;
        }
        else 
        {
            *new = 0;
        }
        previous++;
        current++;
        next++;
        new++;
    }
    
    current = line;
    
    for (i = 1; i < length - 1; i++)
    {
        *line = *row;
        line++;
        row++;
    }
}

void print_array(int * row, int length)
/* This function prints the array as a list of either "*" or ".". A "*"
 * will be printed if the value is a 1 and if the value is a 0, a "." 
 * will be printed. */
{
    int i;
    printf(".");
    for (i = 1; i < length - 1; i++)
    {
        if (*row == 1)
        {
            printf("*");
        }
        else 
        {
            printf(".");
        }
        row++;
    }
    printf(".");
    printf("\n");
}

int main(int argc, char * argv[])
{
    int i;
    int cells;
    int generations;
    int * row;
    int * row1;
    
    if (argc != 3 || atoi(argv[1]) < 1 || atoi(argv[2]) < 1)
    /* Usage message if user inputs program incorrectly */
    {
        fprintf(stderr, "Usage: %s number1 (number of cells) number2 \
        (number of generations)", argv[0]);
        exit (1);
    }
    
    cells = atoi(argv[1]);
    generations = atoi(argv[2]);
    row = (int *) calloc(cells, sizeof(int));
    row1 = (int *) calloc(cells, sizeof(int));
    
    if (row == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed\n");
        exit (1);
    }
    
     if (row1 == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed\n");
        exit (1);
    }
    
    srand(time(0));
    
    for (i = 1; i < cells - 1; i++)
    {
        int ran;
        ran = rand();
        if (ran % 2 == 0)
        {
            row[i] = 0;
        }
        else
        {
            row[i] = 1;
        }
    }
    while (generations > 1)
    {
        print_array(row, cells);
        update(row, row1, cells);
        generations--;
    }
    print_array(row, cells);
    free(row);
    free(row1);
    
    print_memory_leaks();
    
    return 0;
}

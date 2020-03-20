#include "memcheck.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void update(int * line, int * row, int length)
/* 
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board 
 * passed in. Once a solution is found, print the boards making up the 
 * solution in reverse order. 
 */
{
    int i;
    
    for (i = 1; i < length - 1; i++) 
    {
        if (line[i] == 0 && (line[i - 1] + line[i + 1] == 1))
        {
            row[i] = 1;
        }
        else 
        {
            row[i] = 0;
        }
    }
    for (i = 0; i < length; i++)
    {
        line[i] = row[i];
    }
}

void print_array(int * row, int length)
/* 
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board 
 * passed in. Once a solution is found, print the boards making up the 
 * solution in reverse order. 
 */
{
    int i;
    for (i = 0; i < length; i++)
        {
            if (row[i] == 1)
            {
                printf("*");
            }
            else 
            {
                printf(".");
            }
        }
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
    /* Usage message if user tries to run program incorrectly */
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
        fprintf(stderr, "Error! Error! Memory allocation failed\n");
        exit (1);
    }
    
     if (row1 == NULL)
    {
        fprintf(stderr, "Error! Error! Memory allocation failed\n");
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
    
    
    
    
    
    
    
    
        

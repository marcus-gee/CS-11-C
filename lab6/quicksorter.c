#include <stdio.h>
#include <stdlib.h>
#include "memcheck.h"
#include "linked_list.h"
#include <assert.h>
#include <string.h>

void usage(char *program) 
/* Usage message if user tries to run program incorrectly. */
{
    fprintf(stderr, "Usage: %s [-q] number1 number2....\n", program);
    exit(1);
}

node* quicksort(node* list)
/* This function will sort all the values that the user inputs. */
{
    node* lower;
    node* higher;
    node* temp;
    node* pivot;
    node* creator;
    node* first_append;
    node* last_append;
    
    lower = NULL;
    higher = NULL;
    
    if (list == NULL || list->next == NULL)
    /* Base case */
    {
        temp = copy_list(list);
        free_list(list);
        return temp;
    }
    
    pivot = create_node(list->data, NULL);
    
    for (temp = list->next; temp != NULL; temp = temp->next)
    {
        if (temp->data < pivot->data)
        /* Create new node for all values less than the pivot */
        {
            creator = create_node(temp->data, lower);
            lower = creator;
        }
        else
        /* Create new node for all values greater than the pivot */
        {
            creator = create_node(temp->data, higher);
            higher = creator;
        }
    }
    
    lower = quicksort(lower); /* Recursive step */
    higher = quicksort(higher); /* Recursive step */
    first_append = append_lists(lower, pivot); 
    last_append = append_lists(first_append, higher);
    
    free_list(lower);
    free_list(higher);
    free_list(pivot);
    free_list(first_append);
    free_list(list);
    
    assert(is_sorted(last_append));
    
    return last_append;
}

int main(int argc, char* argv[])
{
    int i;
    int quiet;
    int legal;
    node* list;
    node* sorted_list;
    node* temp;
    int data;
    
    list = NULL;
    quiet = 0;
    legal = 0;
    
    if (argc <= 1)
    {
        usage(argv[0]);
    }
    
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-q") != 0)
        {
            legal = 1;
        }
    }
    
    if (legal == 0)
    {
        usage(argv[0]);
    }
    
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-q") == 0)
        {
            quiet = 1;
        }
        else 
        {
            data = atoi(argv[i]);
            temp = create_node(data, list);
            list = temp;
        }
    }
    
    sorted_list = quicksort(list);
    
    if (quiet == 0)
    {
        print_list(sorted_list);
    }
    
    free_list(sorted_list);
    print_memory_leaks();
    return 0;
}

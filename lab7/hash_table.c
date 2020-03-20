/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s) {
    int i;
    int letter;
    int sum;
    int index;
    
    sum = 0;
    
    for (i = 0; i < strlen(s); i++)
    {
        letter = s[i];
        sum += letter;
    }
    
    index = (sum % NSLOTS);
    return index;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value) {
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    new_node->key = key;  /* Fill in the new node with the given value. */
    new_node->next = NULL;
    new_node->value = value;

    return new_node;
}


/* Free all the nodes of a linked list. */
void free_list(node *list) {
     node *n;     /* a single node of the list */

    while (list != NULL)
    {
        n = list;
        list = list->next;

        /*
         * 'n' now points to the first element of the list, while
         * 'list' now points to everything but the first element.
         * Since nothing points to 'n', it can be freed.
         */

        free(n->key);
        free(n);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table() {
    int i;
    hash_table * ht;
    
    ht = (hash_table*)malloc(sizeof(hash_table));
    
    if (ht == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }
    
    ht->slot = (node**)malloc(NSLOTS * sizeof(node*));
    
    if (ht->slot == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }
    
    for (i = 0; i < NSLOTS; i++)
    {
        ht->slot[i] = NULL;
    }
    
    return ht;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht) {
    int i;
    
    for (i = 0; i < NSLOTS; i++)
    {
        free_list(ht->slot[i]);
    }
    
    free(ht->slot);
    free(ht);
    
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key) {
    int hash_value;
    int value;
    node* list;
    node* finder;
    
    hash_value = hash(key);
    list = ht->slot[hash_value];
    
    if (list == NULL)
    {
        return 0;
    }
    
    for (finder = list; finder != NULL; finder = finder->next)
    {
        if (strcmp(finder->key, key) == 0)
        {
            value = finder->value;
            return value;
        }
    }
    
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value) {
    node* list;
    node* finder;
    int hash_value;
    node* node;
    
    hash_value = hash(key);
    list = ht->slot[hash_value];

    if (get_value(ht, key) == 0)
    {
        node = create_node(key, value);
        ht->slot[hash_value] = node;
        node->next = list;
    }
    else
    {
        for (finder = list; finder != NULL; finder = finder->next)
        {
            if (strcmp(finder->key, key) == 0)
            {
                finder->value = value;
                free(key);
                break;
            }
        }
    }
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht) {
    int i;
    node* list;
    node* finder;
    
    for (i = 0; i < NSLOTS; i++)
    {
        list = ht->slot[i];
        
        if (list != NULL)
        {
            for (finder = list; finder != NULL; finder = finder->next)
            {
                printf("%s %d\n", finder->key, finder->value);
            }
        }
    }
}



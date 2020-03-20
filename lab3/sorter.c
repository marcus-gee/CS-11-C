#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define ARRAY_SIZE 32

/* This program will take an array of ARRAY_SIZE (in this case 32), and 
 * sort the numbers in the array from least to greatest. */
 
void bubble_sort(int array[], int size_of_array);
void minimum_element(int array[], int size_of_array);
void usage_message(char * s);

/* This function iterates through the array and checks if the next 
 * element is smaller. If so, the two elements are switched until we are
 * left with an array of elements sorted from least to greatest. */
void bubble_sort(int array[], int size_of_array) {
    int temp;
    int number_of_elements;
    int i;
    number_of_elements = size_of_array;
    
    while (number_of_elements > 1) {
        for (i = 0; i < number_of_elements - 1; i++) {
            if (array[i] > array[i + 1]) {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
        number_of_elements--;
    }
    
    for (i = 0; i < size_of_array - 1; i++ ) {
        assert (array[i] <= array[i + 1]);
    }
} 
        
/* This function iterates through the entire array to find the smallest 
 * element. Once that element is found, it is switched with the element 
 * in the front of the array. This process is continued until we are
 * left with a sorted array. */

void minimum_element(int array[], int size_of_array) {
    int start;
    int smallest;
    int index;
    int num_elements;
    int temp;
    
    start = 0;
    num_elements = size_of_array;
    while (start < num_elements) {
        smallest = start;
        for (index = start; index < num_elements; index++) {
            if (array[index] < array[smallest]) {
                smallest = index;
            }
        }
        temp = array[smallest];
        array[smallest] = array[start];
        array[start] = temp;
        start++;
    }
    
    for (index = 0; index < size_of_array - 1; index++ ) {
        assert (array[index] <= array[index + 1]);
    }
}

/* If there is a problem arising from the number of elements in the 
 * array and the maximum array size allowed, this function will print an
 * error message along with how to resolve the issue. */
void usage_message(char * s) {
     fprintf(stderr, "usage: %s [-b] [-q] number1 [number2 ... ] \
     (maximum %d numbers)", s, ARRAY_SIZE);
     exit (1);
 }
 

int main(int argc, char ** argv) {
    int quiet = 0;
    int bubble = 0;
    int i;
    int element;
    int count = 0;
    int array[ARRAY_SIZE];
    
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-q") == 0) {
            quiet = 1;
        } else if (strcmp(argv[i], "-b") == 0) {
            bubble = 1;
        } else {
            element = atoi (argv[i]);
            count++; 
            if (count > ARRAY_SIZE) {
                usage_message(argv[0]);
                return 1;
            }
            array[count - 1] = element;
        }
    }
    
    if (count == 0) {
        usage_message(argv[0]);
        return 1;
    }
    
    if (bubble == 1) {
        bubble_sort(array, count);
        if (quiet == 0) {
            for (i = 0; i < count; i++) {
                printf("%d\n", array[i]);
            }
        }
        return 0;
    } else {
        minimum_element(array, count);
        if (quiet == 0) {
            for (i = 0; i < count; i++) {
                printf("%d\n", array[i]);
            }
        }
        return 0;
    }
}

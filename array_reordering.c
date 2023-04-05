#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


/*
 * For this program I'm using memcpy/memmove to manipulate the array.
 * Doing time benchmark on my linux system with an array that contains 47,000 array elements
 * and 47,000 operations on those elements it takes this amount of time to run: 
 * real	0m2.356s
 * user	0m2.293s
 * sys	0m0.009s
 * 
 * The linked list version that simulates an array with nodes (using this same data set) takes this amount of time to run:
 * real	0m8.118s
 * user	0m7.992s
 * sys	0m0.005s
 * 
 * Array much faster using memcpy/memmove.
 * 
 */

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char *ch = " ", *tmp_str = NULL;
    int array_size = 0;
    long int query_type, f_element, r_element, abs_value; 
    long int *array, *swap_array;
    size_t len = 20;

    FILE *fd = fopen("input405.txt", "r");
    
    tmp_str = calloc(len, sizeof(char));
    // first line from stdin: size of array and number of queries to process.
    //getline(&tmp_str, &len, stdin);
    getline(&tmp_str, &len, fd); 
    array_size = strtol(strtok(tmp_str, ch), NULL, 10);

    // second line from stdin: array elements, break up string to store into integer array
    array = calloc(array_size, sizeof(long int));
    swap_array = calloc(array_size, sizeof(long int));
    //getline(&tmp_str, &len, stdin);
    getline(&tmp_str, &len, fd);
    array[0] = strtol(strtok(tmp_str, ch), NULL, 10);
    for (int i = 1; i < array_size; i++) {
        array[i] = strtol(strtok(NULL, ch), NULL, 10);
    }

    // start processing queries, use dynamic allocated temp array to transition elements 
    //while ((getline(&tmp_str, &len, stdin)) != -1) {
    while ((getline(&tmp_str, &len, fd)) != -1) {
        query_type = strtol(strtok(tmp_str, ch), NULL, 10);
        f_element = strtol(strtok(NULL, ch), NULL, 10)-1;
        r_element = strtol(strtok(NULL, "\n"), NULL, 10)-1;

        if (query_type == 1) { // removing range of elements from array and adding to front (in same order)
            memset(swap_array, 0, sizeof(long int)*array_size);
            memcpy(swap_array, array, sizeof(long int)*array_size);
            memmove(array, array+f_element, sizeof(long int)*((r_element-f_element)+1));
            memmove(array+(r_element-f_element+1), swap_array, sizeof(long int)*f_element);
        } else { // query_type == 2; removing range of elements from array and adding to the back (in the same order)
            memset(swap_array, 0, sizeof(long int)*array_size);
            memcpy(swap_array, array, sizeof(long int)*array_size);
            memmove(array+((array_size-1) - ((r_element-f_element))), array+f_element, sizeof(long int)*((r_element-f_element)+1));
            memmove(array+(f_element), swap_array+(r_element+1), sizeof(long int)*(((array_size-1)-r_element)));
        }
    }
    
    // get the absolute value of abs(array[0] - array[N]) and print to stdout
    abs_value = abs((int)array[0]- (int)array[array_size-1]);

    // print values to stdout
    printf("%ld\n", abs_value);
    for (int i = 0; i < array_size; i++)
        printf("%ld ", array[i]);

    // free dynamically allocated memory
    free(tmp_str);
    free(array);
    fclose(fd);

    return 0;
}

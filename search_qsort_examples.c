#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Change this value to:
* 1 if test integer array is storted ascending (low to high)
* 0 if test integer array is storted descending (high to low)
*/
#define ASCENDING_DECENDING 1

/* Comparison function for integer array items */
int compare_integers(const void *a, const void *b) 
{
    if (ASCENDING_DECENDING)
        return (*(int*)a - *(int*)b);
    else
        return (*(int*)b - *(int*)a);
}

int main()
{
    int my_array[] = {10, 5, 25, 20, 30};

    fprintf(stderr, "Array pre-sort: ");
    for (int i = 0; i < (int)(sizeof(my_array)/sizeof(my_array[0])); i++)
        fprintf(stderr, "%d ", my_array[i]);
    fprintf(stderr, "\n");

    qsort(my_array, sizeof(my_array)/sizeof(my_array[0]),
            sizeof(int), compare_integers);

    fprintf(stderr, "Array post-sort: ");
    for (int i = 0; i < (int)(sizeof(my_array)/sizeof(my_array[0])); i++)
        fprintf(stderr, "%d ", my_array[i]);
    fprintf(stderr, "\n");

    return 0;
}
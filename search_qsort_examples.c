#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int compare_integers(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
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
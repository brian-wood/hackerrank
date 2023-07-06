#include <stdio.h>
#include <stdlib.h>



int main()
{

    int r = 3;
    int c = 3;
    int index = 0;

    int arr_1d[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *arr_2d[r]; // allocate 1d array of rows
    
    // allocate 2d array of columns
    for (int i = 0; i < r; i++)
        arr_2d[i] = (int*)malloc(c * sizeof(int));

    for (int i = 0; i < r; i++) { // rows of array
        for (int j = 0; j < c; j++, index++) // columns of array
            arr_2d[i][j] = arr_1d[index];
    }

    // print 1d array
    fprintf(stderr, "1d Array: \n");
    for (int i = 0; i < index; i++)
        fprintf(stderr, "%d ", arr_1d[i]);
    fprintf(stderr, "\n\n");

    // print 2d array
    fprintf(stderr, "2d Array:\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            fprintf(stderr, "%d ", arr_2d[i][j]);
    fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");

    // free the 2d array
    // NOTE: skip this if returning a pointer to the 2d array, hopefully
    //       the calling function deallocates the memory properly
    for (int i = 0; i < r; i++)
        free(arr_2d[i]);

    return 0;
}
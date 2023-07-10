#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Change this value to:
* 1 if test integer array is storted ascending (low to high)
* 0 if test integer array is storted descending (high to low)
*/
#define ASCENDING_DECENDING 0

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

    /****** Integer Array Search ******/
    /* already sorted array otherwise use qsort with it's helper function */
    //int array[] = { 10, 20, 40, 40, 50, 100, 100 };
    int array[] = {100, 100, 50, 40, 40, 20, 10};

    int *item;
    int search_value;

    fprintf(stderr, "Enter an integer/number as search key (valid values: 1 to 100): ");
    scanf("%d", &search_value);

    /* search for the item using bsearch() */
    item = (int*)bsearch(&search_value, array, sizeof(array)/sizeof(array[0]),
                        sizeof(int), compare_integers);
    
    if (item != NULL)
        fprintf(stderr, "%d is found in the array.\n", *item);
    else
        fprintf(stderr, "%d is not found in the array\n", search_value);
    
    /****** End Integer Array Search ******/

    /****** String Array Search ******/
    char str_array[][20] = {"aa", "cc", "bb", "jj", "ss", "ll", "zz", "ww"};
    char *str_item;
    char search_string[20];

    fprintf(stderr, "Enter a two letter search string as search key "
                "(i.e., \"aa\", \"jj\", etc...: ");
    scanf("%s", search_string);

    /* Qsort the elements of the array */
    qsort(str_array, sizeof(str_array)/sizeof(str_array[0]), 20,
            (int(*)(const void*, const void*))strcmp);
    
    /* Search for the user supplied string using bsearch() */
    str_item = (char*)bsearch(search_string, str_array,
                     sizeof(str_array)/sizeof(str_array[0]), 20,
                     (int(*)(const void*, const void*))strcmp);
    
    if (str_item != NULL)
        fprintf(stderr, "%s found in the array.\n", str_item);
    else
        fprintf(stderr, "%s not found in the array.\n", search_string);

    /****** End String Array Search ******/

    return 0;

}
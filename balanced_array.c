#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int balanced_array(int array[], int count) 
{
    int sum_left, sum_right;

    // start with 2nd element of array so something on left & right of array element
    // that might be balanaced position of array.
    for (int i = 1; i < count; i++) {
        sum_left = 0;
        sum_right = 0;
        // add up left side of test array element up to element 'i'
        for (int x = i - 1; x >= 0; x--) {
            sum_left += array[x];
        }

        // add up right side of test array element after element 'i'
        for (int y = i+1; y < count; y++) {
            sum_right += array[y];
        }

        if (sum_left == sum_right)
            return array[i];
    }

    return -1; // No element position found in array where left == right.
}

int main()
{
    // Case 1
    int arr1[] = { 1, 4, 2, 5 };
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", balanced_array(arr1, n1));
 
    // Case 2
    int arr2[] = { 2, 3, 4, 1, 4, 5 };
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", balanced_array(arr2, n2));

    // Case 2
    int arr3[] = { 4, 2, 1, 3, 3 };
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", balanced_array(arr3, n3));
    return 0;
}
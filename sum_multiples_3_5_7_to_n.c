#include <stdio.h>
#include <stdlib.h>


int main()
{
    int sum = 0;
    int n = 0;
    fprintf(stderr, "Enter number to sum multiples of 3, 5, and 7 up to: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0)
            sum += i;
    }

    fprintf(stderr, "Sum of the multiples: %d\n", sum);

    return 0;
}
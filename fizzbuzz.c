#include <stdio.h>
#include <stdlib.h>


int main (void)
{

    for (int i = 1; i <= 100; i++) {
        if (!(i%3) && !(i%5))
            printf("%s\n", "FizzBuzz");
        else if (!(i%3))
            printf("%s\n", "Fizz");
        else if (!(i%5))
            printf("%s\n", "Buzz");
        else
            printf("%d\n", i);
    }
    return 0; 
}
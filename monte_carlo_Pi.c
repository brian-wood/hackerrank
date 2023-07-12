#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define CALCULATIONS 100000

int main()
{
    double x, y;    // points x and y
    double d;       // point location from origin
    double pi = 0;  // stores the value for pi
    int in = 0, out = 0; // point is inside or outside radius of circle

    srand(time(NULL)); // initialize the random number generator

    for (int i = 0; i < CALCULATIONS; i++) {
        // random x and y values
        x = (double)(rand() / (RAND_MAX + 1.0));
        y = (double)(rand() / (RAND_MAX + 1.0));

        fprintf(stderr, "rand x: %f, rand y: %f\n", x, y);

        d = ((x * x) + (y * y));

        if (d <= 1)
            in++; // add 1 to value since it lies inside the radius of circle

        out++; // add 1 to values since all points are inside square

        fprintf(stderr, "location from origin: %f\npoints inside radius: %d\n"
                        "points inside square: %d\n", d, in, out);

        pi = 4.0 * ((double)in / (double)out);

        fprintf(stderr, "pi: %.10f\n\n", pi);
    }
}
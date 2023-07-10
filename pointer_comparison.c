#include <stdlib.h>
#include <stdio.h>

int main()
{

    int *a;
    int *b;
    int c = 1;
    int d = 1;

    a = &c;
    b = &d;

    printf("variable values:    integer ptr a: %d   integer ptr b: %d   integer var c: %d,  integer var d: %d\n", *a, *b, c, d);
    printf("variable addresses: a: %p  b: %p  c: %p  d: %p\n\n",
            (void *)a, (void *)b, (void *)&c, (void *)&d);
    
    printf("compare addresses:  a == b  -->  %s\n", a == b ? "True  (1)": "False (0)");

    printf("compare values:    *a == *b -->  %s\n", *a == *b ? "True  (1)": "False (0)");
    
    printf("cmp addr to value:  a == c  -->  %s\n", a == c ? "True  (1)": "False (0)");

    printf("compare addresses:  a == &c -->  %s\n", a == &c ? "True  (1)": "False (0)");

    printf("compare values:    *a == c  -->  %s\n", *a == c ? "True  (1)": "False (0)");

    printf("compare values:    *b == c  -->  %s\n", *b == c ? "True  (1)": "False (0)");

    printf("cmp addr to value:  b == d  -->  %s\n", b == d ? "True  (1)": "False (0)");

    printf("compare values:    *b == d  -->  %s\n", *b == d ? "True  (1)": "False (0)");

    printf("compare addresses:  b == &d -->  %s\n", b == &d ? "True  (1)": "False (0)");

    printf("compare values:     c == d  -->  %s\n", c == d ? "True  (1)": "False (0)");

    printf("compare addresses: &c == &d -->  %s\n", &c == &d ? "True  (1)": "False (0)");

    return 0;
}
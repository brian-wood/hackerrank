#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
long swapCount(char *chars)
{
    int swap = 0;
    int len = strlen(chars);

    for(int i = 0; i < len; i++){
        if(chars[i] == '('){
            swap++;
        } 
        else if(swap) {
            swap--;
        }
    }
    return (swap + 1) / 2; // The number of opening & closing parens are len / 2, so adjust final value to account for that.
}
 
// Driver code 
int main()
{
    //char *s = "[]][][";
    char *s = "())()(";
    printf("%ld\n", swapCount(s));
 
    //s = "[[][]]";
    s = "(()())";
    printf("%ld\n", swapCount(s));

    s = ")(())()(";
    printf("%ld\n", swapCount(s));
 
    //char *s = "][][";
    s = ")()(";
    printf("%ld\n", swapCount(s));
 
    //s = "]]][[[";
    s = ")))(((";
    printf("%ld\n", swapCount(s));

    //s = "[]";
    s = "()";
    printf("%ld\n", swapCount(s));

    return 0;
}
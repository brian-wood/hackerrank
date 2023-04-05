#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
long swapCount(char *chars)
{
    int len = strlen(chars);
    int swap = 0 , balance = 0, last = len-1;
    char tmp_ch;
    char *tmp_str = calloc(len, sizeof(char));
    strncpy(tmp_str, chars, len);

    for(int i = 0; i < len; i++)
    {
        if (tmp_str[i] == '(')
            balance++; // left paren
        else
            balance--; // right paren

        if (balance < 0) { // check if we've seen more right paren than left...
            for (; (i < last) && (tmp_str[last] != '('); last--) {} // loop to find next left paren '('

            // swap left paren '(' with right paren ')'
            tmp_ch = tmp_str[i];
            tmp_str[i] = tmp_str[last];
            tmp_str[last] = tmp_ch;

            // record swap and reset balance
            swap++;
            balance = 1;
        }
    }
    return swap;
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
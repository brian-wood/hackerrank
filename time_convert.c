#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* timeConversion(char* s) {

    char *time = malloc(11 * sizeof(char));
    char *tmp;
    long hour;
    bool pm;
    
    strncpy(time, s, strlen(s));
    //printf("s: %s, time: %s\n", s, time);
    
    // check if we're am or pm
    if ((tmp = strstr(time, "PM"))) {
        //printf("PM found: %s\n", tmp);
        *tmp = '\0';
        pm = 1;
    } else {
        tmp = strstr(time, "AM");
        //printf("AM found: %s\n", tmp);
        *tmp = '\0'; // remove the 'AM' for military time
        pm = 0;
    }
    
    //printf("s: %s, time: %s\n", s, time);
    
    if (pm) { // convert 12-hour to 24-hr 
        hour = strtol(time, &tmp, 10);
        if (hour != 12) { // check if it's 12:xx:PM, no change needed, otherwise adapt to military time.
            //printf("hour: %ld\n", hour);
            hour += 12;
            //printf("hour: %ld\n", hour);
            sprintf(time, "%ld%s", hour, time+2);
            //printf("time: %s", time);
        }
    } else {
        if (time[1] == '2') { // its 12:xx:AM, replace with 00:MM:SS
            strncpy(time, "00", 2);
            //printf("time: %s", time);
        }
        //printf("time: %s", time);
    }
    
    return time;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = timeConversion(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

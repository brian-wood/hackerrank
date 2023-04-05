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
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/* cmp_ints() returns an integer indicating the result of the comparison, as follows:      
 *      - a negative value if s1 is less than s2;
 *      - a positive value if s1 is greater than s2.
 *      - 0, if the s1 and s2 are equal;
 * This detail was from the man page for strcmp() and uses same return values.
 */

int cmp_ints(const void *s1, const void *s2)
{
    int a = *(const int*)s1;
    int b = *(const int*)s2;
    
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
        return 0;
}

/*
 * Complete the 'lonelyinteger' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */
int lonelyinteger(int a_count, int* a) {
    
    int lonely_int = 0;
    // create duplicate array so as to not modify original
    int *sorted_ints = calloc(a_count, sizeof(int));
    
    printf("\ndebug: input array: ");
    for (int i = 0; i < a_count; i++)
        printf("%d ", a[i]);
    printf("\n");

    // Check if only one element, then it is unique.
    if (a_count == 1)
        return a[0];
    
    // copy array elements
    for (int i = 0; i < a_count; i++)
        sorted_ints[i] = a[i]; 
    
    // sort array elements so easier to find unique member
    qsort(sorted_ints, a_count, sizeof(int), cmp_ints);
    printf("\ndebug: sorted array: ");
    for (int i = 0; i < a_count; i++)
        printf("%d ", sorted_ints[i]);
    printf("\n");
    
    for (int i = 0; i < a_count; i++) {
        if ((sorted_ints[i] != sorted_ints[i+1]) && (i % 2)) {
            lonely_int = sorted_ints[i+1];
        }
    }
    
    return lonely_int;
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** a_temp = split_string(rtrim(readline()));

    int* a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int a_item = parse_int(*(a_temp + i));

        *(a + i) = a_item;
    }

    int result = lonelyinteger(n, a);

    fprintf(fptr, "%d\n", result);

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

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

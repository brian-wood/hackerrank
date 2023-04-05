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
FILE *fd;

/*
 * Complete the 'twoStacks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER maxSum
 *  2. INTEGER_ARRAY a
 *  3. INTEGER_ARRAY b
 */

int twoStacks(int maxSum, int a_count, int* a, int b_count, int* b) {

    int a_plus[a_count], b_plus[b_count];
    int sum,stack_a, stack_b;
    
    memset(a_plus, 0, sizeof(a_plus));
    memset(b_plus, 0, sizeof(b_plus));

    // Check the 'sum' values from both arrays (with increasing indexes of array) and store the unmodified values
    // in secondary array up until you have a sum value > maxSum. This gives you two minimal arrays to work with
    // in the next step.   
    sum = 0;
    for (stack_a = 0; stack_a < a_count && ((sum += a[stack_a]) <= maxSum); stack_a++) {
        a_plus[stack_a] = a[stack_a];
    }
    sum = 0;
    for (stack_b = 0; stack_b < b_count && ((sum += b[stack_b]) <= maxSum); stack_b++) {
        b_plus[stack_b] = b[stack_b];
    }

    // Work your way through both arrays to find a summation of values what will be less-than or equal to the maxSum value.
    // if you hit a value in the second array you can pop off the last element (from first array) to take in one from second array
    // that will give you a higher move count and possibly allow for additional moves (keeping you under the maxSum) 
    sum = 0;
    for (int i = 0; i < stack_a; i++)
        sum += a_plus[i];
    for (int i = 0; i < stack_b; i++) {
        sum += b_plus[i];
        if ((sum > maxSum) && (stack_a > 0)) {
            sum -= a_plus[stack_a-1];
            stack_a--;
        }
    }
   
    return (stack_a + stack_b);
}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    fd = fopen("input407.txt", "r");
    
    int g = parse_int(ltrim(rtrim(readline())));

    for (int g_itr = 0; g_itr < g; g_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        int maxSum = parse_int(*(first_multiple_input + 2));

        char** a_temp = split_string(rtrim(readline()));

        int* a = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            int a_item = parse_int(*(a_temp + i));

            *(a + i) = a_item;
        }

        char** b_temp = split_string(rtrim(readline()));

        int* b = malloc(m * sizeof(int));

        for (int i = 0; i < m; i++) {
            int b_item = parse_int(*(b_temp + i));

            *(b + i) = b_item;
        }

        int result = twoStacks(maxSum, n, a, m, b);

        //fprintf(fptr, "%d\n", result);
        fprintf(stdout, "%d\n", result);
    }

    //fclose(fptr);
    fclose(fd);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        //char* line = fgets(cursor, alloc_length - data_length, stdin);
        char* line = fgets(cursor, alloc_length - data_length, fd);

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

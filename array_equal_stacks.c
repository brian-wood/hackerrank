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
 * Complete the 'equalStacks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY h1
 *  2. INTEGER_ARRAY h2
 *  3. INTEGER_ARRAY h3
 */

int equalStacks(int h1_count, int* h1, int h2_count, int* h2, int h3_count, int* h3) {

    int h1_total=0, h2_total=0, h3_total=0;
    int *h1_pop, *h2_pop, *h3_pop;
    
    //printf("h1_count: %d, h2_count: %d, h3_count: %d\n", h1_count, h2_count, h3_count);
    
    // find total for each stack
    for (int i = 0; i < h1_count; i++)
        h1_total += h1[i];
    for (int i = 0; i < h2_count; i++)
        h2_total += h2[i];
    for (int i = 0; i < h3_count; i++)
        h3_total += h3[i];
    //printf("h1_total: %d, h2_total: %d, h3_total: %d\n", h1_total, h2_total, h3_total);
    
    // start looking for max value where stack heights match
    h1_pop = h1;
    h2_pop = h2;
    h3_pop = h3;
    
    while ((h1_total != h2_total) || (h1_total != h3_total) || (h2_total != h3_total)) {
        //printf("h1_pop: %d, h2_pop: %d, h3_pop: %d\n", *(h1_pop), *(h2_pop), *(h3_pop));
        
        // h1 pop
        while ((h1_total > h2_total) || (h1_total > h3_total) ) {
            h1_total -= *(h1_pop);
            if (h1_total < 1)
                return 0;
            h1_pop++;
        }
        // h2 pop
        while ((h2_total > h1_total) || (h2_total > h3_total)) {
            h2_total -= *(h2_pop);
            if (h2_total < 1)
                return 0;
            h2_pop++;
        }
        // h3 pop
        while ((h3_total > h2_total) || (h3_total > h1_total)) {
            h3_total -= *(h3_pop);
            if (h3_total < 1)
                return 0;
            h3_pop++;
        }
    }

    //printf("max stack height: %d\n", h1_total);
    return h1_total;
}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    fd = fopen("input406.txt", "r");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n1 = parse_int(*(first_multiple_input + 0));

    int n2 = parse_int(*(first_multiple_input + 1));

    int n3 = parse_int(*(first_multiple_input + 2));

    char** h1_temp = split_string(rtrim(readline()));

    int* h1 = malloc(n1 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        int h1_item = parse_int(*(h1_temp + i));

        *(h1 + i) = h1_item;
    }

    char** h2_temp = split_string(rtrim(readline()));

    int* h2 = malloc(n2 * sizeof(int));

    for (int i = 0; i < n2; i++) {
        int h2_item = parse_int(*(h2_temp + i));

        *(h2 + i) = h2_item;
    }

    char** h3_temp = split_string(rtrim(readline()));

    int* h3 = malloc(n3 * sizeof(int));

    for (int i = 0; i < n3; i++) {
        int h3_item = parse_int(*(h3_temp + i));

        *(h3 + i) = h3_item;
    }

    int result = equalStacks(n1, h1, n2, h2, n3, h3);

    //fprintf(fptr, "%d\n", result);
    fprintf(stdout, "%d\n", result);

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

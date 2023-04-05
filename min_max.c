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

/*
 * Complete the 'miniMaxSum' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void miniMaxSum(int arr_count, int* arr) {

    long min_sum = 0, max_sum = 0;
    long sort_array[arr_count];
    long temp;
    
    // zero out array, memset() wasn't working to zero, very strange. 
    for (int i = 0; i < arr_count; i++) {
        sort_array[i] = 0;
        printf("sort_array[%d]=%ld\n", i, sort_array[i]);
    }
    
    // Sort from low to high in secondary array
    for (int i = 0; i < arr_count; i++) {
        sort_array[i] = arr[i];
        printf("sort_array[%d]=%ld\n", i, sort_array[i]);
        for (int j = i; j < arr_count; j++) {
            if (arr[j] < sort_array[i]) {
                temp = sort_array[i];
                sort_array[i] = arr[j];
                arr[j] = temp;
            }
            printf("sort_array[%d]=%ld\n", i, sort_array[i]);
        }
    }
    
    // take lowest 4 and sum
    for (int i = 0; i < 4; i++) {
        min_sum += sort_array[i];
        printf("min sort_array[%d]=%ld ", i, sort_array[i]);
    }
    printf("\n");

    // take highest 4 and sum
    for (int i = 1; i < 5; i++) {
        max_sum += sort_array[i];
        printf("max sort_array[%d]=%ld ", i, sort_array[i]);
    }
    printf("\n");
  
        
    printf("%ld %ld", min_sum, max_sum);

}

int main()
{

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++) {
        int arr_item = parse_int(*(arr_temp + i));

        *(arr + i) = arr_item;
    }

    miniMaxSum(5, arr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);
    FILE *fd = fopen("minmax.txt","r");

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

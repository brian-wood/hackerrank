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
 * Complete the 'flippingMatrix' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY matrix as parameter.
 */
int max(int a, int b)
{
    return ((a > b) ? a : b);
}

int flippingMatrix(int matrix_rows, int matrix_columns, int** matrix) {

    int sub_matrix_total = 0;
    int size = matrix_rows -1; // -1 for starting at 0 in arrays

    for (int i = 0; i < matrix_rows/2; i++) { // rows (1st/last, 2nd/last-1, 3rd/last-2, etc...)
        for (int j = 0; j < matrix_rows/2; j++) { // cols (1st/last, 2nd/last-1, 3rd/last-2, etc...)
           sub_matrix_total += max(max(matrix[i][j], matrix[i][size-j]), max(matrix[size-i][j], matrix[size-i][size-j]));
        }
    }

    return sub_matrix_total;
}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    //fd = fopen("input007.txt", "r");
    fd = fopen("input0071.txt", "r");
    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        int** matrix = malloc((2 * n) * sizeof(int*));

        for (int i = 0; i < 2 * n; i++) {
            *(matrix + i) = malloc((2 * n) * (sizeof(int)));

            char** matrix_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2 * n; j++) {
                int matrix_item = parse_int(*(matrix_item_temp + j));

                *(*(matrix + i) + j) = matrix_item;
            }
        }

        int result = flippingMatrix(2 * n, 2 * n, matrix);

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

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
 * Complete the 'arrayManipulation' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY queries
 */

long arrayManipulation(int n, int queries_rows, int queries_columns, int** queries) {

/////////////////////////////// Brute Force Way: changes each element /////////////////////////////////
/*    
    size_t max_value = 0;
    size_t add_value = 0;
    size_t *array = calloc(n, sizeof(size_t));
    
    //printf("n: %d, queries_rows: %d, queries_columns: %d\n", n, queries_rows, queries_columns);


    for (int i = 0; i < queries_rows; i++) {
        add_value = queries[i][2];
        //printf("add_value: %ld\n", add_value);
        
        for (int j = queries[i][0]-1, k = queries[i][1]-1; j <= k; j++) {
            array[j] += add_value;
            if (array[j] > max_value) {
                max_value = array[j];
                //printf("max_value: %ld\n", max_value);
            }
        }
   }
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////// Optimized Way: changing select elements ///////////////////////////////

   
    long long int max_value = 0;
    long long int add_value = 0;
    long long int *array = calloc(n+2, sizeof(long long int));
    
    for (int i = 0; i < queries_rows; i++) {
        add_value = queries[i][2]; 
        //printf("add_value: %ld\n", add_value);
        
        array[queries[i][0]-1] += add_value;
        array[queries[i][1]] -= add_value;
        /*
        printf("array: ");
        for (int j = 0; j <= n; j++) {
            printf("%lld ", array[j]);
        }
        printf("\n");
        */ 
    }
    /*
    printf("Frray: ");
    for (int j = 0; j <= n; j++) {
        printf("%lld ", array[j]);
    }
    printf("\n"); 
    */

    for (int j = 1; j <= n; j++) {
        array[j] += array[j-1];
        //printf("array[%d]: %lld, max_value: %lld\n", j, array[j], max_value);
        if (array[j] > max_value)
            max_value = array[j];
        //printf("max_value: %lld\n", max_value);
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////

    free(array);

    return max_value;
}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    fd = fopen("input404.txt", "r");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int m = parse_int(*(first_multiple_input + 1));

    int** queries = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        *(queries + i) = malloc(3 * (sizeof(int)));

        char** queries_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 3; j++) {
            int queries_item = parse_int(*(queries_item_temp + j));

            *(*(queries + i) + j) = queries_item;
        }
    }

    long result = arrayManipulation(n, m, 3, queries);

    //fprintf(fptr, "%ld\n", result);
    fprintf(stdout, "%ld\n", result);

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

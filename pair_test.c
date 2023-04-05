#include <assert.h>
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

#define FILENAME "input.txt"

char* readline(FILE *stream);
char* ltrim(char*);
char* rtrim(char*);

float parse_float(char*);
int parse_int(char*);


/*
 * Complete the 'efficientJanitor' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts FLOAT_ARRAY weight as parameter.
 */

int efficientJanitor(int weight_count, float* weight) {
    int trips = 0; // set to max number of trips initially
    int i = 0;
    float *bag = weight;
    float *next;
    
    fprintf(stdout, "number of bags: %d\n", weight_count);

    /* find and eliminate heavy bags that must be carried alone */    
    while (i < weight_count) {
        if ((*bag + 1.01) > 3.0) {
            printf("heavy bag: %.2f\n", *bag);
            *bag = 0; // remove bag from list
            trips++;
        }
        bag++;
        i++;
    }

    /* Find bags to pair under 3.0 lbs*/
    bag = weight; // reset to head of list
    i = 1;
    while (i < weight_count) {
        next = bag + 1;
        for (int j = i; j < weight_count; j++, next++) {
            if (*bag < 1) { // skip this as it used to be bag but has been removed
                bag++;
                break;
            } else if (!(*next)) {
                i++;
            } else if ((*bag + *next) <= 3.0) {
                printf("bag pair: %.2f %.2f\n", *bag, *next);
                trips++;
                *bag = 0; // part of pair, remove from list
                *next = 0; // part of pair, remove from list
                bag++;
                i += 2;
                break;
            }
         }
    }
    if (*bag) { // If true we've got one bag left to haul out without a partner that's <= 3.0
        printf("final bag without pair: %.2f\n", *bag);
        *bag = 0;
        trips++;
    }

    /* Final check if any unpaired bags, */
    // DEBUG
    printf("bags left in list (zero means accounted for):\n");
    for (i = 0; i < weight_count; i++)
        printf("%.2f\n", weight[i]);
    // DEBUG

    return trips; 
}


int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    FILE *fd;

    // adding in opening file for input instead of stdin
    if ((fd = fopen(FILENAME, "r")) == NULL) {
        fprintf(stderr, "Cannot open file %s\n", FILENAME);
        exit(EXIT_FAILURE);
    }
    int weight_count = parse_int(ltrim(rtrim(readline(fd))));

    float* weight = malloc(weight_count * sizeof(float));

    for (int i = 0; i < weight_count; i++) {
        float weight_item = parse_float(ltrim(rtrim(readline(fd))));

        *(weight + i) = weight_item;
    }

    int result = efficientJanitor(weight_count, weight);

    fprintf(stdout, "%d\n", result);

    //fclose(fptr);

    return 0;
}

char* readline(FILE *stream) {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);
    

    while (true) {
        char* cursor = data + data_length;
        //char* line = fgets(cursor, alloc_length - data_length, stdin);
        char* line = fgets(cursor, alloc_length - data_length, stream);

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

float parse_float(char* str) {
    char* endptr;
    float value = strtof(str, &endptr);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
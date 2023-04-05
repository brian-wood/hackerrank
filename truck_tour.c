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
 * Complete the 'truckTour' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY petrolpumps as parameter.
 */

int truckTour(int petrolpumps_rows, int petrolpumps_columns, int** petrolpumps) {


    size_t max_litre = 0;
    size_t max_litre_index = 0;
    size_t max_np_dist = 0;
    size_t max_np_dist_index = 0;

    printf("petrolpumps_rows: %d\n", petrolpumps_rows);
    printf("petrolpumps_columns: %d\n", petrolpumps_columns);
    
    // lets find the highest litre count, we know this would be trick/end case check
    // so won't just use blindly, but will be something for decision criteria.
    for (int i = 0; i < petrolpumps_rows; i++) {
        printf("pump has litres: %d, next pump distance: %d\n", petrolpumps[i][0], petrolpumps[i][1]);
        if (petrolpumps[i][0] > (int)max_litre) {
            max_litre = petrolpumps[i][0];
            max_litre_index = i;
            printf("max_litre: %zd, max_litre_index: %zd\n", max_litre, max_litre_index);
        }
        
        // so the key is finding the first index with a large enough number from which we can start our pump journey.
        // this will be: (litres at pump) - (distance/fuel-burn-rate). Let try the below and submit to see what happens.
        if ((petrolpumps[i][0] - petrolpumps[i][1]) > (int)max_np_dist) {
            max_np_dist = (petrolpumps[i][0] - petrolpumps[i][1]);
            max_np_dist_index = i;
            printf("max_np_dist: %zd, max_np_dist_index: %zd\n", max_np_dist, max_np_dist_index);
        }
    }
    
    if (max_litre_index == max_np_dist_index) {
        printf("The pump with the most capacity (pump %zd with %zd litres of fuel) gives most distance to next pump\n",
                max_np_dist_index, max_litre);
    }



    return max_np_dist_index;
}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    //fd = fopen("input007.txt", "r");
    fd = fopen("input402.txt", "r");

    int n = parse_int(ltrim(rtrim(readline())));

    int** petrolpumps = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        *(petrolpumps + i) = malloc(2 * (sizeof(int)));

        char** petrolpumps_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int petrolpumps_item = parse_int(*(petrolpumps_item_temp + j));

            *(*(petrolpumps + i) + j) = petrolpumps_item;
        }
    }

    int result = truckTour(n, 2, petrolpumps);

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

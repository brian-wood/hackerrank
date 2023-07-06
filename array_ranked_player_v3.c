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
 * Complete the 'climbingLeaderboard' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY ranked
 *  2. INTEGER_ARRAY player
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */

/* Change this value to:
* 1 if test integer array is storted ascending (low to high)
* 0 if test integer array is storted descending (high to low)
*/
#define ASCENDING_DECENDING 0
static const int *loc1, *loc2;

/* Comparison function for integer array items */
int compare_integers(const void *a, const void *b) 
{
    loc1 = a;
    loc2 = b;
    if (ASCENDING_DECENDING)
        return (*(int*)a - *(int*)b);
    else
        return (*(int*)b - *(int*)a);
}

// creates new array with duplicates removed, returns new array size.
int dups_removed(int *base, int* modified, int size)
{
    int count = 0;

    modified[0] = base[0]; // save first element as initial trigger
    for (int i = 0; i < size; i++) {
        if (*(modified+count) != *(base+i)) {
            count++;
            *(modified+count) = *(base+i);
        }
    }

    return ++count;
}

int* climbingLeaderboard(int ranked_count, int* ranked, int player_count, int* player, int* result_count) {

    int rank;
    int *n_rank = malloc(player_count * sizeof(int));
    int *mod_ranked = malloc(ranked_count * sizeof(int));
    const int *item;
    int mod_ranked_cnt = 0;

    *result_count = player_count;
    memset(n_rank, 0, player_count);
    memset(mod_ranked, 0, ranked_count);
    
    mod_ranked_cnt = dups_removed(ranked, mod_ranked, ranked_count);

    for (int i = 0; i < player_count; i++) {
        /* search for the item using bsearch(), if found leave alone else
         * set to pointer for item where this is before in ranking array. */
        item = (int*)bsearch((player+i), mod_ranked, mod_ranked_cnt,
                            sizeof(int), compare_integers);
        if (item == NULL && ASCENDING_DECENDING == 0)
            item = loc2;
        else if (item == NULL && ASCENDING_DECENDING == 1)
            item = loc1;

        rank = item - mod_ranked; // find index into array
        if (*(player+i) < *item) // player is next rank after current item pointer 
            *(n_rank+i) = rank+2;
        else
            *(n_rank+i) = rank+1; // player takes rank from current item pointer
    }

    free(mod_ranked);

    return n_rank;
}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    fd = fopen("input411.txt", "r");

    int ranked_count = parse_int(ltrim(rtrim(readline())));

    char** ranked_temp = split_string(rtrim(readline()));

    int* ranked = malloc(ranked_count * sizeof(int));

    for (int i = 0; i < ranked_count; i++) {
        int ranked_item = parse_int(*(ranked_temp + i));

        *(ranked + i) = ranked_item;
    }

    int player_count = parse_int(ltrim(rtrim(readline())));

    char** player_temp = split_string(rtrim(readline()));

    int* player = malloc(player_count * sizeof(int));

    for (int i = 0; i < player_count; i++) {
        int player_item = parse_int(*(player_temp + i));

        *(player + i) = player_item;
    }

    int result_count;
    int* result = climbingLeaderboard(ranked_count, ranked, player_count, player, &result_count);

    for (int i = 0; i < result_count; i++) {
        //fprintf(fptr, "%d", *(result + i));
        fprintf(stdout, "%d", *(result + i));

        if (i != result_count - 1) {
            //fprintf(fptr, "\n");
            fprintf(stdout, "\n");
        }
    }

    //fprintf(fptr, "\n");
    fprintf(stdout, "\n");
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

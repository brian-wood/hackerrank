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
 * Complete the 'towerBreakers' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n: the number of towers
 *  2. INTEGER m: the height of each tower
 * 
 * In each turn, a player can choose a tower of height x and
 * reduce its height to y, where 1 <= y < x and y evenly divides x.
 * -Note: player 1 always goes first
 */

int towerBreakers(int n, int m) {

    bool p1, p2;       // inc/dec values after each successful turn
    int num_tower = n; // may not need, easier to remember than n
    int tower_ht = m;  // may not need, easier to remember than m
    int turn = 0;      // number of rounds < number of towers; players hit all towers optimally,
                       // before resorting to clearing towers so they eq == 1
    int towers[num_tower]; // track tower heights for each player turn
    
    // Fill the towers array
    for (int i = 0; i < num_tower; i++)
        towers[i] = tower_ht;

    while (num_tower) {
        // p1 goes first, then p2
        p1 = 0; // set to false 
        if (turn < num_tower) { // hit unchanged towers first
            for (int i = 1; i < towers[turn]; i++) {
                if (!(towers[turn] % i)) {
                    towers[turn] -= (towers[turn] - i);
                    p1 = 1; // p1 found highest move possible for given tower, true.
                }
            }
        } else { // All towers have had first optimal moves completed, now comes the slog of battle.
            for (int j = 0; j < num_tower; j++) { // search array of towers for a move
                if (towers[j] == 1) // tower is done, skip to next
                    continue;
                for (int i = 1; i < towers[j]; i++) {
                    if (!(towers[j] % i)) {
                        towers[j] -= (towers[j] - i);
                        p1 = 1; // p1 found highest move possible for given tower, true.
                    }
                }
            }
        }
        turn++; // p1 turn complete
        if (p1 == 0) // break if no moves found
            break; 
            
        // p2 turn
        p2 = 0; // set to false 
        if (turn < num_tower) { // hit unchanged towers first
            for (int i = 1; i < towers[turn]; i++) {
                if (!(towers[turn] % i)) {
                    towers[turn] -= (towers[turn] - i);
                    p2 = 1; // p2 found highest move possible for given tower, true.
                }
            }
        } else { // All towers have had first optimal moves completed, now comes the slog of battle.
            for (int j = 0; j < num_tower; j++) { // search array of towers for a move
                if (towers[j] == 1) // tower is done, skip to next
                    continue;
                for (int i = 1; i < towers[j]; i++) {
                    if (!(towers[j] % i)) {
                        towers[j] -= (towers[j] - i);
                        p2 = 1; // p2 found highest move possible for given tower, true.
                    }
                }
            }
        }
        turn++; // p2 turn complete
        if (p2 == 0) // break if no moves found
            break;   
    } // end while()

    if (p1)
        return 1;
    else
        return 2;
}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    //fd = fopen("input007.txt", "r");
    fd = fopen("input010.txt", "r");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        int result = towerBreakers(n, m);

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

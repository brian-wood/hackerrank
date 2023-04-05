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

int parse_int(char*);
FILE *fd;

/*
 * Complete the 'palindromeIndex' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int palindromeIndex(char* s) {

    int palin;              // record if start point is palindrome
    int len = strlen(s);    // string length tracker
    int p1_len, p2_len;     // modified string length trackers 
    char *str_mod;          // store modified string

    str_mod = malloc(len * sizeof(char));
    
    // reverse the mod string to check if its palindrome without mods.
    for (int i = 0; i < len; i++) {
        str_mod[i] = s[(len-1)-i];
    }
    if (!(strncmp(s, str_mod, len))) {
        palin = -1;
        goto exit;
    }

    for (int i = 0; i < len; i++){ // loop over the length of original string
        palin = i; // record potential character that is removed to make palindrome
        // make copy of string without palin character
        for (int j = 0, p = 0; j < len-1; j++) {
            if (j == palin) { // skip copying the palin test character
                p++;
            }
            str_mod[j] = s[p++];
        }
        str_mod[len-1] = '\0';

        p1_len = p2_len = strlen(str_mod)-1;
        for (int j = 0; j < (p1_len-1); j++) { // search through up to mid-point of string to compare for palindrome
                if (str_mod[j] == str_mod[p2_len--])
                    continue;
                else {
                    palin = -1;
                    break; // not a palindrome, try removing next character, re-run check 
                }
        }
        if (palin > -1)
            goto exit;
    }

exit:
    free(str_mod);
    return palin;

}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    //fd = fopen("input007.txt", "r");
    fd = fopen("input300.txt", "r");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char* s = readline();

        int result = palindromeIndex(s);

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}

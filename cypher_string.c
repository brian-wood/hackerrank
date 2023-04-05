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
 * Complete the 'caesarCipher' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER k
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* caesarCipher(char* s, int k) {
    char *A_Z = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *a_z = "abcdefghijklmnopqrstuvwxyz";
    char *enc_str = malloc(strlen(s) * sizeof(char)); // return string that's been encrypted
    strncpy(enc_str, s, strlen(s)); 
    char *index;
    int cypher_index;
    
    //printf("A_Z: %s\n", A_Z);
    //printf("a_z: %s\n", a_z);
    //printf("string char (strlen=%ld, k=%d): ", strlen(s), k);
    for (int i = 0; i < (int)strlen(enc_str); i++) {
        //printf("<%c ", *(enc_str + i));
        if ((index = strchr(A_Z, *(enc_str + i)))) {
            cypher_index = (int)(index - A_Z);
            cypher_index = (cypher_index + k) % 26;
            *(enc_str + i) = A_Z[cypher_index];
        } else if ((index = strchr(a_z, *(enc_str + i)))) {
            cypher_index = (int)(index - a_z);
            cypher_index = (cypher_index + k) % 26;
            *(enc_str + i) = a_z[cypher_index];
        }
        //printf("%c> ", *(enc_str + i));
    }
    //printf("\n");
    return enc_str;
}

int main()
{
    //FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");
    //fd = fopen("input007.txt", "r");
    fd = fopen("input100.txt", "r");

    int n = parse_int(ltrim(rtrim(readline())));

    char* s = readline();

    int k = parse_int(ltrim(rtrim(readline())));

    char* result = caesarCipher(s, k);

    //fprintf(fptr, "%s\n", result);
    fprintf(stdout, "%s\n", result);

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

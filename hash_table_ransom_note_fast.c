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
 * Complete the 'checkMagazine' function below.
 *
 * The function accepts following parameters:
 *  1. STRING_ARRAY magazine
 *  2. STRING_ARRAY note
 */

#define COLLISION_AVOIDANCE_SKEW 2 // Multiple of hash size to help avoid collisions

struct string_hash {
    int count_value;
    uint32_t key;
} *hash;

/* Generate hash code index using "%" remainder operator
 * (according to C11 spec. "%" is not a true euclidian modulo)
 *      key:    hash key to be used
 *      count:  number of items in the hash table
 */
int hash_code(uint32_t key, int count) {
    return key % count;
}

/*
 * Using Paul Hsieh's super fast hash algorithm for this hackerrank challenge;
 * why not use something used by many others as reinventing the
 * mathmatical preverbial hash algorithm "wheel" seems like wasting time
 * (and would result in sub-optimal hash algorithm overall)  
*/
#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

// data: String to generate hash value from
// len:  Length of string used to generate hash key/index value
uint32_t SuperFastHash (const char * data, int len) {
uint32_t hash = len, tmp;
int rem;

    if (len <= 0 || data == NULL) return 0;

    rem = len & 3;
    len >>= 2;

    /* Main loop */
    for (;len > 0; len--) {
        hash  += get16bits (data);
        tmp    = (get16bits (data+2) << 11) ^ hash;
        hash   = (hash << 16) ^ tmp;
        data  += 2*sizeof (uint16_t);
        hash  += hash >> 11;
    }

    /* Handle end cases */
    switch (rem) {
        case 3: hash += get16bits (data);
                hash ^= hash << 16;
                hash ^= ((signed char)data[sizeof (uint16_t)]) << 18;
                hash += hash >> 11;
                break;
        case 2: hash += get16bits (data);
                hash ^= hash << 11;
                hash += hash >> 17;
                break;
        case 1: hash += (signed char)*data;
                hash ^= hash << 10;
                hash += hash >> 1;
    }

    /* Force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

/*
 * Create the hash table for dictionary
 *      dictionary: array of string containing the words to add to hash table dictionary
 *      count:      number of words that will be in the dictionary
*/
void init_hash_table(char ** dictionary, int count) {

    int index;
    uint32_t hash_value;

    // Allocating dictionary hash table
    hash = calloc(count*COLLISION_AVOIDANCE_SKEW, sizeof(struct string_hash));
    for (int i = 0; i < count*COLLISION_AVOIDANCE_SKEW; i++) {
        hash[i].count_value = 0;
        hash[i].key = 0;
    }

    // Setup hash table for quick lookups of strings 
    for (int i = 0; i < count; i++) {
        
        hash_value = SuperFastHash(dictionary[i], strlen(dictionary[i]));

        index = hash_code(hash_value, count*COLLISION_AVOIDANCE_SKEW);

        // Record we've seen this string and number of times in dictionary, also save hash value of string
        hash[index].count_value++;
        hash[index].key = hash_value;
    }
}

void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {

    int note_match = 0; // Save number of matched words, if equal to note_count we can generate note
    int index = 0;
    int hash_count = magazine_count;

    // Generate hash table dictionary of words from magazine 
    init_hash_table(magazine, hash_count);

    // Check note can be generated from available dictionary of words
    for (int i = 0; i < note_count; i++) {
        index = hash_code(SuperFastHash(note[i], strlen(note[i])),
                            hash_count*COLLISION_AVOIDANCE_SKEW);

        if (hash[index].count_value) { // Word from note found in dictionary of magazine words
            hash[index].count_value--;
            note_match++;
            continue;
        } else { // No word found to help complete note
            break;
        }
    }

    if (note_match == note_count)
        printf("Yes");
    else
        printf("No");

}

int main()
{
    fd = fopen("input410.txt", "r");

    char** first_multiple_input = split_string(rtrim(readline()));

    int m = parse_int(*(first_multiple_input + 0));

    int n = parse_int(*(first_multiple_input + 1));

    char** magazine_temp = split_string(rtrim(readline()));

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    char** note_temp = split_string(rtrim(readline()));

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    checkMagazine(m, magazine, n, note);

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

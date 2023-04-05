#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    long int data;
    struct node *next;
};

/*
 * For this program I'm using a linked list to simulate an array.
 * Doing time benchmark on my linux system with an array that contains 47,000 array elements
 * and 47,000 operations on those elements it takes this amount of time to run: 
 * real	0m8.118s
 * user	0m7.992s
 * sys	0m0.005s
 * 
 * The array version using this same data set takes this amount of time to run:
 * real	0m2.356s
 * user	0m2.293s
 * sys	0m0.009s
 * 
 * Array much faster using memcpy/memmove.
 * 
 */

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char *ch = " ", *tmp_str = NULL;
    int array_size = 0;
    long int query_type, f_element, r_element, abs_value; 
    struct node *head_node, *tail_node, *ptr_i_prev, *ptr_i, *ptr_j_prev, *ptr_j, *prev_node, *node;
    size_t len = 20;

    FILE *fd = fopen("input405.txt", "r");
    
    tmp_str = calloc(len, sizeof(char));
    // first line from stdin: size of array and number of queries to process.
    //getline(&tmp_str, &len, stdin);
    getline(&tmp_str, &len, fd); 
    array_size = strtol(strtok(tmp_str, ch), NULL, 10);

    // second line from stdin: array elements, break up string to store into integer node array
    head_node = calloc(1, sizeof(struct node));
    head_node->next = NULL;
    //getline(&tmp_str, &len, stdin);
    getline(&tmp_str, &len, fd);
    head_node->data = strtol(strtok(tmp_str, ch), NULL, 10);
    tail_node = head_node;
    for (int i = 1; i < array_size; i++) {
        tail_node->next = calloc(1, sizeof(struct node));
        tail_node = tail_node->next;
        tail_node->data = strtol(strtok(NULL, ch), NULL, 10);
    }
    tail_node->next = NULL;

    // start processing queries, use dynamic allocated linked list to move "array" elements 
    //while ((getline(&tmp_str, &len, stdin)) != -1) {
    while ((getline(&tmp_str, &len, fd)) != -1) {
        query_type = strtol(strtok(tmp_str, ch), NULL, 10);
        f_element = strtol(strtok(NULL, ch), NULL, 10);
        r_element = strtol(strtok(NULL, "\n"), NULL, 10);
        // set ptr1 and pt2 to correct f_element/r_element nodes
        node = head_node;
        prev_node = NULL;
        ptr_i_prev = ptr_i = ptr_j_prev = ptr_j = NULL;
        for (int i = 1; i < array_size; i++) {
            if (i == f_element) {
                ptr_i_prev = prev_node;
                ptr_i = node;
            }
            if (i == r_element) {
                ptr_j_prev = prev_node;
                ptr_j = node;
            }

            if (ptr_i && ptr_j)
                break;
            
            prev_node = node;
            if ((node = node->next) == NULL) { // we should never hit this, but wanted to give example of error handling.
                printf("NODE ARRAY ERROR: node == NULL\n");
                goto err;
            }
        }
        
        if (query_type == 1) { // removing range of elements from array and adding to front (in same order)
            if (ptr_i_prev == NULL) {// someone is trying to make busywork by moving front of list to front of lists...nope!
                continue;
            } else if (ptr_j->next == NULL) { // we're pulling end of list to front
                ptr_i_prev->next = NULL;
                tail_node = ptr_i_prev;
            } else {
                ptr_i_prev->next = ptr_j->next;
            }
            ptr_j->next = head_node;
            head_node = ptr_i;
        } else { // query_type == 2; removing range of elements from array and adding to the back (in the same order)
            if (ptr_i_prev == NULL) {
                head_node = ptr_j->next;
            } else {
                ptr_i_prev->next = ptr_j->next;
            }
            tail_node->next = ptr_i;
            ptr_j->next = NULL;
            tail_node = ptr_j;
        }
        
    }
 
    // get the absolute value of abs(array[0] - array[N]) and print to stdout
    abs_value = abs((int)head_node->data - (int)tail_node->data);
    printf("%ld\n", abs_value);

    // print array to stdout
    node = head_node;
    for (int i = 0; i < array_size; i++) {
        printf("%ld ", node->data);
        node = node->next;
    }

err:
    // free dynamically allocated memory
    free(tmp_str);
    ptr_i = head_node;
    for (int i = 0; i < array_size; i++) {
        ptr_j = ptr_i->next;
        free(ptr_i);
        ptr_i = ptr_j;
    }

    fclose(fd);
    return 0;
}
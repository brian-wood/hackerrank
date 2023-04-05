#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

typedef struct SinglyLinkedListNode SinglyLinkedListNode;
typedef struct SinglyLinkedList SinglyLinkedList;

struct SinglyLinkedListNode {
    int data;
    SinglyLinkedListNode* next;
};

struct SinglyLinkedList {
    SinglyLinkedListNode* head;
    SinglyLinkedListNode* tail;
};

SinglyLinkedListNode* create_singly_linked_list_node(int node_data) {
    SinglyLinkedListNode* node = malloc(sizeof(SinglyLinkedListNode));

    node->data = node_data;
    node->next = NULL;

    return node;
}

void insert_node_into_singly_linked_list(SinglyLinkedList** singly_linked_list, int node_data) {
    SinglyLinkedListNode* node = create_singly_linked_list_node(node_data);

    if (!(*singly_linked_list)->head) {
        (*singly_linked_list)->head = node;
    } else {
        (*singly_linked_list)->tail->next = node;
    }

    (*singly_linked_list)->tail = node;
}

void print_singly_linked_list(SinglyLinkedListNode* node, char* sep, FILE* fptr) {
    while (node) {
        fprintf(fptr, "%d", node->data);

        node = node->next;

        if (node) {
            fprintf(fptr, "%s", sep);
        }
    }
}

void free_singly_linked_list(SinglyLinkedListNode* node) {
    while (node) {
        SinglyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

// Complete the findMergeNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

    struct SinglyLinkedListNode *list1 = head1;
    struct SinglyLinkedListNode *list2 = head2;
    int num_nodes_list1 = 0, num_nodes_list2 = 0;
    int list_diff = 0;
    
    // Find length of both linked lists
    while (1) {
        if (list1) {
            num_nodes_list1++;
            printf("list1: %p\n", list1);
            list1 = list1->next;    
        }
        if (list2) {
            num_nodes_list2++;
            printf("list2: %p\n", list2);
            list2 = list2->next;
        }
        if (!list1 && !list2)
            break;
    }
    printf("list1 num nodes: %d\nlist2 num nodes: %d\n", num_nodes_list1, num_nodes_list2);    
    // find linked list diff.
    list_diff = abs(num_nodes_list1 - num_nodes_list2);
    printf("list diff: %d\n", list_diff);
    
    // make both linked lists same starting point distance search equal so we can search 
    list1 = head1;
    list2 = head2;
    if (num_nodes_list1 > num_nodes_list2) {
        for (int i = 0; i < list_diff; i++)
            list1 = list1->next;
    } else if (num_nodes_list2 > num_nodes_list1)
        for (int i = 0; i < list_diff; i++)
            list2 = list2->next;

    // start list comparisons to find merge node where pointer matches (using pointer address to match
    // off of and not the underlying integer data value since it's not called out that the nodes contain 
    // data values that are exclusive (i.e., they could be same values of all 1's, etc... or repeated
    // values on different lists before merging). 
    while (list1 != NULL) {
        printf("compare. list1: %p, list2: %p\n", list1, list2);
        if (list1 == list2) {
            printf("match found! list1: %p, list2: %p\n", list1, list2);
            return list1->data;
        }
        else {
            list1 = list1->next;
            list2 = list2->next;
        }
    }

    return 0;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* tests_endptr;
    char* tests_str = readline();
    int tests = strtol(tests_str, &tests_endptr, 10);

    if (tests_endptr == tests_str || *tests_endptr != '\0') { exit(EXIT_FAILURE); }

    for (int tests_itr = 0; tests_itr < tests; tests_itr++) {
        char* index_endptr;
        char* index_str = readline();
        int index = strtol(index_str, &index_endptr, 10);

        if (index_endptr == index_str || *index_endptr != '\0') { exit(EXIT_FAILURE); }

        SinglyLinkedList* llist1 = malloc(sizeof(SinglyLinkedList));
        llist1->head = NULL;
        llist1->tail = NULL;

        char* llist1_count_endptr;
        char* llist1_count_str = readline();
        int llist1_count = strtol(llist1_count_str, &llist1_count_endptr, 10);

        if (llist1_count_endptr == llist1_count_str || *llist1_count_endptr != '\0') { exit(EXIT_FAILURE); }

        for (int i = 0; i < llist1_count; i++) {
            char* llist1_item_endptr;
            char* llist1_item_str = readline();
            int llist1_item = strtol(llist1_item_str, &llist1_item_endptr, 10);

            if (llist1_item_endptr == llist1_item_str || *llist1_item_endptr != '\0') { exit(EXIT_FAILURE); }

            insert_node_into_singly_linked_list(&llist1, llist1_item);
        }
      
      	SinglyLinkedList* llist2 = malloc(sizeof(SinglyLinkedList));
        llist2->head = NULL;
        llist2->tail = NULL;

        char* llist2_count_endptr;
        char* llist2_count_str = readline();
        int llist2_count = strtol(llist2_count_str, &llist2_count_endptr, 10);

        if (llist2_count_endptr == llist2_count_str || *llist2_count_endptr != '\0') { exit(EXIT_FAILURE); }

        for (int i = 0; i < llist2_count; i++) {
            char* llist2_item_endptr;
            char* llist2_item_str = readline();
            int llist2_item = strtol(llist2_item_str, &llist2_item_endptr, 10);

            if (llist2_item_endptr == llist2_item_str || *llist2_item_endptr != '\0') { exit(EXIT_FAILURE); }

            insert_node_into_singly_linked_list(&llist2, llist2_item);
        }
      
      	SinglyLinkedListNode* ptr1 = llist1->head;
      	SinglyLinkedListNode* ptr2 = llist2->head;
      
      	for (int i = 0; i < llist1_count; i++) {
            if (i < index) {
          		ptr1 = ptr1->next;
            }
        }
      
      	for (int i = 0; i < llist2_count; i++) {
          	if (i != llist2_count-1) {
          		ptr2 = ptr2->next;
            }
        }
      
      	ptr2->next = ptr1;

        int result = findMergeNode(llist1->head, llist2->head);

        fprintf(fptr, "%d\n", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

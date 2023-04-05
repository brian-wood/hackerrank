#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "binary_tree_advanced.h"


struct node *root = NULL;

// Calls itself recursively to position node in correct location in tree
static struct node *add_node(struct node* node, int value)
{

    if (node == NULL) {
        node = (struct node *)malloc(sizeof(struct node));
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
    } else if (value == node->value) {
        goto ret; // we don't want duplicates in our binary search tree
    } else if (value < node->value) {
        node->left = add_node(node->left, value);
        node->left->parent = node;
    } else {
        node->right = add_node(node->right, value);
        node->right->parent = node;
    }

ret:
    return node;
}

/* Find the lowest value node that is in the order of succession
 *(i.e., what is next node in numerical succession from node value being deleted,
 * example: deleting node with value 4, so trace down tree to find node value possibly with 5, 6, 7, etc...
 * to use as its replacement value for node being removed)
 */
struct node *min_value_node(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Delete a node and add it's left/right nodes back into binary tree (if not null)
struct node *del_node(struct node *root, int value)
{
    struct node *tmp;

    if (root == NULL)
        return root;

    if (value < root->value)
        root->left = del_node(root->left, value);
    else if (value > root->value)
        root->right = del_node(root->right, value);
    else { // we have found our node
        if (root->left == NULL) { // If true replace our node with right child
            tmp = root->right;
            tmp->parent = root->parent;
            free(root);
            return tmp;
        }
        else if (root->right == NULL) { // If true replace our node with left child
            tmp = root->left;
            tmp->parent = root->parent;
            free(root);
            return tmp;
        }

        // We have left and right children, trace down the right path to find replacement node 
        tmp = min_value_node(root->right);
        // Replace our node's value that is "being deleted" with the value of next node 
        // that is in the order of succession (i.e., if value is 4 to be deleted replace with found
        // value that will be something like 5, 6, 7, etc...)
        root->value = tmp->value;
        // Go and delete the node with the value we just placed into the node that was to be deleted
        // (this is our clean-up recursion)
        root->right = del_node(root->right, tmp->value);

    }
    // Returning root back up recursive calls to rebuild parent->child linking after deletion
    return root;
}

/*
 * Find a value in a binary search tree
 */
struct node *find_node(struct node *ptr, int value)
{
    struct node *fnd_l = NULL, *fnd_r = NULL;

    if (ptr == NULL) // hit leaf node without finding, return 0
        goto ret;

    if (ptr->value == value) {
        return ptr;
    }
    else {
        fnd_l = find_node(ptr->left, value);
        fnd_r = find_node(ptr->right, value);
        if (fnd_l)
            return fnd_l;
        else if(fnd_r)
            return fnd_r;
    }

ret:
    return NULL;
}

/*
 * Find the sum of binary search tree values for a provided subtree node
 */
static int max_sum = 0;
int find_sum(struct node *root) {
    int tmp1 = 0;
    int tmp2 = 0;

    if (root) { 
        tmp1 = find_sum(root->left);
        tmp2 = find_sum(root->right);

        return max_sum + tmp1 + tmp2 + root->value;
    } else { // at a leaf node left/right pointer that is null
        return 0;
    }
}

int main (void)
{

    char *ch = " ", *token, *tmp_str;
    int opt = 0, value = 0;
    size_t num_nodes = 0;

    while(1) {
    /*
     * Usage: 
     * 
     */
        printf("Please provide option along with necessary data (h for help): ");
        opt = fgetc(stdin);
            switch (opt)
            {
            case 'a':
                num_nodes = 1;
                tmp_str = calloc(num_nodes, sizeof(char));
                getline(&tmp_str, &num_nodes, stdin); // getline will realloc() the tmp_str to the size needed for entire string
                printf("strlen is: %zd\n", num_nodes);
                value = strtol(strtok(tmp_str, ch), NULL, 10);
                root = add_node(root, value);
                free(tmp_str);
                break;
            case 'c':
                num_nodes = 1;
                tmp_str = calloc(num_nodes, sizeof(char));
                getline(&tmp_str, &num_nodes, stdin); // getline will realloc() the tmp_str to the size needed for entire string
                printf("strlen is: %zd\n", num_nodes);
                token = strtok(tmp_str, ch);
                for (int i = 0; i < (int)num_nodes; i++) {
                    if (token == NULL) {
                        break;
                    }
                    root = add_node(root, strtol(token, NULL, 10));
                    token = strtok(NULL, ch);
                }
                free(tmp_str);
                break;
            case 'd':
                tmp_str = calloc(num_nodes, sizeof(char));
                getline(&tmp_str, &num_nodes, stdin); // getline will realloc() the tmp_str to the size needed for entire string
                printf("strlen is: %zd\n", num_nodes);
                value = strtol(strtok(tmp_str, ch), NULL, 10);

                if (!(del_node(root, value)))
                    printf("The value \"%d\" has been removed from the binary tree\n", value);
                else
                    printf("The value \"%d\" is NOT currently in the binary tree\n", value);
                break;
            case 'f':
                num_nodes = 1;
                tmp_str = calloc(num_nodes, sizeof(char));
                getline(&tmp_str, &num_nodes, stdin); // getline will realloc() the tmp_str to the size needed for entire string
                value = strtol(strtok(tmp_str, ch), NULL, 10);
                if(find_node(root, value))
                    printf("The value \"%d\" is currently in the binary tree\n", value);
                else
                    printf("The value \"%d\" is NOT currently in the binary tree\n", value);
                break;
            case 'q':
// TODO: add clean-up of tree nodes to free the malloc'd memory
                printf("Good-bye!\n");
                return 0;
            case 'h':
            default:
                printf("Usage:\n" 
                "a - Add a new node with value provided (if value already exists will not be added).\n"
                "    Example: a <integer value>\n"
                "             a 10\n"
                "c - Creates a new binary search tree with provided list of integers\n"
                "    Example: c [number of nodes] <list of integers: 1 2 4 9..[n]>\n"
                "             c 5 1 2 3 4 5\n"
                "d - Delete a node with a value, if present.\n"
                "    Example: d <integer value>\n"
                "             d 5\n"
                "f - Find if an integer value is already in binary search tree.\n"
                "    Example: f <integer value>\n"
                "             f 5\n"
                "h - Help menu\n"
                "q - Quit program\n");
            }
    }

    return 0;
}
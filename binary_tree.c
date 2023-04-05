#include <stdio.h>
#include <stdlib.h>


struct node {
    // node value
    int value;
    // pointers to nodes below on left and right
    struct node *left;
    struct node *right;
};

// Calls itself recursively to position node in correct location in tree
struct node *add_node(struct node* node, int value)
{

    if (node == NULL) {
        node = (struct node *)malloc(sizeof(struct node));
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    } else if (value == node->value) {
        goto ret; // we don't want duplicates in our binary search tree
    } else if (value < node->value) {
        node->left = add_node(node->left, value);
    } else {
        node->right = add_node(node->right, value);
    }

ret:
    return node;
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

int main (int argc, char *argv[])
{

    // Get user input for number of nodes to create from argc
    if ((argc != 3) && (atoi(argv[1]) != (argc-2))) {
        printf("Usage: %s [number of nodes] <list of integers: 1 2 4 9..[n]>\n"
                "Example: %s 5 1 2 3 4 5\n", argv[0], argv[0]);
        return 1;
    }

    // Create root node, gather number of nodes, and create the binary search tree
    struct node *root;
    int num_nodes = atoi(argv[1]);
    for (int i = 0; i < num_nodes; i++) {
        root = add_node(root, atoi(argv[i+2]));
    }

    // find the subtree with the maximum sum and return that value.
    int sub_left, sub_right;

    sub_left = find_sum(root->left);
    sub_right = find_sum(root->right);

    printf("%s sub tree is larger, sum=%d\n", sub_left > sub_right ? "Left": "Right", sub_left > sub_right ? sub_left: sub_right);

    return 0;
}
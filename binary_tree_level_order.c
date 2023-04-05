#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

FILE *fd;

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

struct node* insert( struct node* root, int data ) {
		
	if(root == NULL) {
	
        struct node* node = (struct node*)malloc(sizeof(struct node));

        node->data = data;

        node->left = NULL;
        node->right = NULL;
        return node;
	  
	} else {
      
		struct node* cur;
		
		if(data <= root->data) {
            cur = insert(root->left, data);
            root->left = cur;
		} else {
            cur = insert(root->right, data);
            root->right = cur;
		}
	
		return root;
	}
}

/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};
*/

/* Using 2 functions: levelOrder() is going to be parent to do initial setup, final printing of node values in 
 *                    level order and clean up operations.
 *                    node_level() is where we'll do our recursion and the bulk of work.
 */ 
#define MAX_NODES 500 // this is max number of nodes set by hackerrank test constraints, could be modified

int max_depth = 0;
int all_levels[MAX_NODES];
char *level_array[MAX_NODES];

void node_level(struct node *root, int level) {
    int len = 0;
    char *tmp;

    if (root) {
        all_levels[level]++;
        if (all_levels[level] > 1) { // node values already present at this level, get string length and realloc to append new value
            // Get length of data so we know how much space to allocate
            len = snprintf(NULL, 0, "%d ", root->data); 
            // Allocate new buffer to hold current string + new string
            tmp = calloc(len + strlen(level_array[level]) + 1, sizeof(char));
            // Copy current string + new string into place 
            len = snprintf(tmp, len + strlen(level_array[level]) + 1, "%s%d ", level_array[level], root->data);
            free(level_array[level]); // Free the current string 
            level_array[level] = tmp; // Attach the new string to pointer
        } else { // First time adding node to this level
            level_array[level] = calloc(10, sizeof(char));
            snprintf(level_array[level], 10, "%d ", root->data);
        }

        // Move to next level of nodes
        level++;
        if (level > max_depth)
            max_depth = level;
        node_level(root->left, level);
        node_level(root->right, level);
    }
}

void levelOrder( struct node *root) {
    int level = 0;
    
    // Initialize helper array for number of nodes per level
    memset(all_levels, 0, sizeof(int));

    if (root) { // Start with root node set things up and begin recursion through tree
        all_levels[level]++;
        level_array[level] = calloc(10, sizeof(char));
        snprintf(level_array[level], 10, "%d ", root->data);
        level++;
        node_level(root->left, level);
        node_level(root->right, level);
    } else { // No root node, basic check
        return;
    }
    
    // Print the final level order node values
    for (int i = 0; i < max_depth; i++) {
        printf("%s", level_array[i]);
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < max_depth; i++)
        free(level_array[i]);
}


int main() {
  
    struct node* root = NULL;
    fd = fopen("input408.txt", "r");

    int t;
    int data;

    //scanf("%d", &t);
    fscanf(fd, "%d", &t);

    while(t-- > 0) {
        //scanf("%d", &data);
        fscanf(fd, "%d", &data);
        root = insert(root, data);
    }
  
	levelOrder(root);

    fclose(fd);
    
    return 0;
}

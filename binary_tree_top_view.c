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

#define COLS 2
int max_node = 0;

void node_count(struct node *root) {
    if (root) {
        max_node++;
        node_count(root->left);
        node_count(root->right);
    }
}

void tree_parse(struct node *root, int top_v, int depth, int arr[][COLS]) {
    if (root) {
        depth++;
        //printf("node data: %d, depth: %d, top_v: %d\n", root->data, depth, top_v);


        // Check if this is top view node we need to store.
        if ((arr[top_v + max_node][0] == -(max_node+1)) || (arr[top_v + max_node][1] > depth)) {
            arr[top_v + max_node][0] = root->data;
            arr[top_v + max_node][1] = depth;
        }
        // Move to next top_v of nodes
        tree_parse(root->left, top_v-1, depth, arr);
        tree_parse(root->right, top_v+1, depth, arr);
    }
}

void topView(struct node *root) {
    int top_v = 0;
    int depth = 0;

    if (root) {
        // Get number of nodes in binary tree
        node_count(root);
        //printf("Node Count: %d\n", max_node);
        
       /* Allocate storage array for ordering the top view nodes
       * and set array size to value that could be max-left nodes or max-right nodes of center.
       * Example: with max_nodes as a value of 15 we'll need to have the ability
       * to store all left of root/center=0 up to -15 as the left-most node if only
       * left nodes present. In the opposite case you could also end up with a tree having all
       * right tree nodes up to +15, so to account for this we'll
       * store into an array that is 15*2=30, this will allow for -15...0...15 nodes all 
       * stored into array starting with 0...N...31 (where N=15 will be our center/zero node). Then
       * when we print the array at the end all the top-view nodes will be in correct
       * order from left to right. 
       */
       int top_v_arr[(max_node*2)+1][COLS];
        
        for (int i = 0; i < (max_node*2)+1; i++) {
            top_v_arr[i][0] = -(max_node+1);
            top_v_arr[i][1] = -(max_node+1);
        }

        // Set our first member of top view array as root will always be present
        top_v_arr[top_v + max_node][0] = root->data;
        top_v_arr[top_v + max_node][1] = depth;
        //printf("node data: %d, depth: %d, top_v: %d\n", root->data, depth, top_v);

        // Start recursive tree parse to add in top view nodes
        tree_parse(root->left, top_v-1, depth, top_v_arr);
        tree_parse(root->right, top_v+1, depth, top_v_arr);


        for (int i = 0; i < (max_node*2)+1; i++) {
            if (top_v_arr[i][0] != -(max_node+1))
                printf("%d ", top_v_arr[i][0]);
        }
    }
}


int main() {
  
    struct node* root = NULL;
    fd = fopen("input409.txt", "r");

    int t;
    int data;

    //scanf("%d", &t);
    fscanf(fd, "%d", &t);

    while(t-- > 0) {
        //scanf("%d", &data);
        fscanf(fd, "%d", &data);
        root = insert(root, data);
    }
  
	topView(root);

    fclose(fd);
    return 0;
}

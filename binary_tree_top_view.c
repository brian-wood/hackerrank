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
int max_node = 0;

int mod(int a, int b) {
  int m = a % b;
  if (m < 0) {
    m = (b < 0) ? m - b : m + b;
  }
  return m;
}

void node_count(struct node *root) {
    if (root) {
        max_node++;
        node_count(root->left);
        node_count(root->right);
    }
}

void tree_parse(struct node *root, int top_v, int depth, int *arr) {
    if (root) {
        depth++;
        printf("node data: %d, depth: %d, top_v: %d\n", root->data, depth, top_v);


        // Check if this is top view node we need to store.
        if (arr[mod(top_v, max_node)] == -(max_node+1)) {
            arr[mod(top_v, max_node)] = root->data;
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
        printf("Node Count: %d\n", max_node);
        
        // Allocate storage array for ordering the top view nodes
        // and set array to default value that cannot be possible
        // based on number of nodes in tree
        int *top_v_arr = calloc(max_node, sizeof(int));
        if (top_v_arr == NULL)
            return; // memory allocation failed, exit
        
        for (int i = 0; i < max_node; i++)
            top_v_arr[i] = -(max_node+1);

        // Set our first member of top view array as root will always be present
        top_v_arr[mod(top_v, max_node)] = root->data;
        printf("node data: %d, depth: %d, top_v: %d\n", root->data, depth, top_v);

        // Start recursive tree parse to add in top view nodes
        tree_parse(root->left, top_v-1, depth, top_v_arr);
        tree_parse(root->right, top_v+1, depth, top_v_arr);

        /*
        for (int i = 0; i < max_node; i++) {
            if (top_v_arr[mod(top_v, max_node)] != -(max_node+1))
                printf("%d ", top_v_arr[mod(top_v, max_node)]);
        }
        */
        free(top_v_arr);
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

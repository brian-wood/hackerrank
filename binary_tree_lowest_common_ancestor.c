#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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

/* Find the lowest common ancestor (LCA) for 2 values in a binary search tree,
 * say we need to find the LCA for 2 and 7 in the following tree. We can see
 * that the LCA would be 4.
 *         8
 *        / \
 *       4   9
 *      / \
 *     /   \ 
 *    1     6
 *     \    /\  
 *      2* 5  7*
 *       \
 *        3
 */
static struct node *lca_node = NULL;

struct node *lca( struct node *root, int v1, int v2 ) {

    // check if either v1 or v2 are equal to one of the passed in root node left/right data values.
    // If so, we've found the tree to track back up and down
    struct node *n1 = NULL;
    struct node *n2 = NULL;

    if (root == NULL) {
        return NULL;
    }
    n1 = lca(root->left, v1, v2);
    n2 = lca(root->right, v1, v2);
    if (root->data == v1 || root->data == v2) {
       return root;
    } else if ((n1 == NULL) && (n2 == NULL)) {
        return NULL;
    }

    if (n1 && n2) // we've found out LCA, set to current root node.
        lca_node = root;
    else if (n1) // we've found one side of our v1/v2, propagate that up
        return n1;
    else if (n2) // we've found another side of our v1/v2, propagate that up
        return n2;

    return (lca_node);
}


int main() {
  
    struct node* root = NULL;
    FILE *fd;
    int t;
    int data;

    fd = fopen("input400.txt", "r");

    fscanf(fd, "%d", &t);

    while(t-- > 0) {
        fscanf(fd, "%d", &data);
        root = insert(root, data);
    }
  	int v1;
  	int v2;
  
  	fscanf(fd, "%d%d", &v1, &v2);
	struct node *ans = lca(root, v1, v2);
  	printf("%d\n", ans->data);
  	
    fclose(fd);
    return 0;
}

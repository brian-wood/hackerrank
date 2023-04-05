
#define MAXINT 1024

struct node {
    // node value
    int value;
    // pointers to nodes below on left and right (parent is for easier delete of nodes)
    struct node *left;
    struct node *right;
    struct node *parent; // keeping track of parent since it could come in handy and isn't much overhead.
};

static struct node *add_node(struct node* node, int value);

struct node *find_node(struct node *ptr, int value);

struct node *del_node(struct node *root, int value);

int find_sum(struct node *root);

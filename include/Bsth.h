struct bst{
    char * key;
    int value;
    struct bst * left;
    struct bst * right;
};

//Initialize the basic bst tree
struct bst* init_bst(struct bst*, const char *, int value);

//insert a tree node in appropriate place and return root
struct bst * insert_bst(struct bst* bst_root, const char * key, int value);

//delete a tree node and return root
struct bst * delete_bst(struct bst* bst_root, const char * key);

//perform preorder traversal
void preorder_traversal(struct bst* bst_root,
                           void (*process_node)(struct bst* bst_node));

//perform postorder traversal
void postorder_traversal(struct bst* bst_root,
                           void (*process_node)(struct bst* bst_node));

//perform inorder traversal
void inorder_traversal(struct bst* bst_root,
                         void (*process_node)(struct bst* bst_node));

void test_complex_bst();

void test_simple_bst();



struct bst{
    char * key;
    //int value;
    struct bst * left;
    struct bst * right;
    file_descriptor filedescriptor;
};

void delete_bst(struct bst *bst_node , file_descriptor filedescriptor ,struct bst*position );


file_descriptor search_bst( struct bst* bst_node , char* file_name);
//Initialize the basic bst tree
//struct bst* init_bst(struct bst*, file_descriptor filedescriptor);

//insert a tree node in appropriate place and return root
struct bst * insert_bst(struct bst* bst_root, file_descriptor filedescriptor);

//delete a tree node and return root


//perform preorder traversal
void preorder_traversal(struct bst* bst_root,
                           void (*process_node)(struct bst* bst_node));

//perform postorder traversal
struct bst* postorder_traversal(struct bst* bst_root);


//perform inorder traversal
void inorder_traversal(struct bst* bst_root,
                         void (*process_node)(struct bst* bst_node));

//perform search and return file descriptor
file_descriptor search_bst( struct bst* bst_node , char* file_name);


//Test cases for bst
void test_complex_bst();
void test_simple_bst();

void displaybst(struct bst *bst_node);


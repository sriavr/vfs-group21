#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

typedef struct bst_n{
    //char * key;
    //int value;
    int is_deleted;
    struct bst_n * left;
    struct bst_n * right;
    file_descriptor filedescriptor;
} bst;

int delete_bst(bst *bst_tree, char * node_path);

//Initialize the basic bst tree
//struct bst* init_bst(struct bst*, file_descriptor filedescriptor);

//insert a tree node in appropriate place and return root
bst * insert_bst(bst* bst_root, file_descriptor filedescriptor);

//delete a tree node and return root


//perform preorder traversal
void preorder_traversal(bst* bst_root,
                           void (*process_node)(bst* bst_node));

//perform postorder traversal
bst* postorder_traversal(bst* bst_root);


//perform inorder traversal
void inorder_traversal(bst* bst_root,
                         void (*process_node)(bst* bst_node));

//perform search and return file descriptor
file_descriptor search_bst(bst* bst_node, char* file_name,
                           char* location_full_path);

//perform search and return bst node
bst * search_bst_node(bst* bst_node, char* file_name,
                           char* location_full_path);

//perform search based on filename with full path
file_descriptor search_bst_full(bst* bst_node,
                                char* filename_with_full_path);

//perform search and return bst node
bst * search_bst_full_node(bst* bst_node,
                           char* filename_with_full_path);

//Test cases for bst
void test_complex_bst();
void test_simple_bst();

void displaybst( bst *bst_node);

#endif

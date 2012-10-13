#include <stdio.h>
#include "../include/Filesystem.h"
#include "../include/LinkedList.h"
#include "../include/Hashtable.h"
#include "../include/Bst.h"
#include "../include/nAry.h"

struct node * create_linkedlist(file_descriptor * file_descriptor_list, long int file_descriptor_list_size)
{
    //TODO
}

struct bst* create_bst(file_descriptor * file_descriptor_list, long int file_descriptor_list_size)
{
    if(file_descriptor_list_size <=0)
        return NULL;

    struct bst * tree = NULL;
    tree = init_bst(tree, file_descriptor_list[0]);

    long int i;
    for(i=1; i < file_descriptor_list_size; i ++)
    {
        insert_bst(tree, file_descriptor_list[i]);
    }

    return tree;
}

void test_create_bst()
{
    long int size = 5;
    file_descriptor* fd_array = NULL;
    fd_array = create_test_fd_data(fd_array, size);
    struct bst * bst_tree = create_bst(fd_array, size);

    printf("\nInorder traversal\n");
    inorder_traversal(bst_tree, &displaybst);

    printf("\nPreorder traversal\n");
    preorder_traversal(bst_tree, &displaybst);

    printf("\nPostorder traversal\n");
    postorder_traversal(bst_tree, &displaybst);
}



void fill_hashtable(struct node * hashtable[], file_descriptor * file_descriptor_list, long int file_descriptor_list_size)
{
    //TODO
}

nNode * create_nAry_tree(file_descriptor * file_descriptor_list, long int file_descriptor_list_size)
{
    //TODO
}

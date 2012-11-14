#include <stdio.h>
#include <string.h>
#include "../include/Filesystem.h"
#include "../include/LinkedList.h"
#include "../include/Hashtable.h"
#include "../include/Bst.h"
#include "../include/nAry.h"

void process_file_desc(nNode* node);
extern header *hdr;
extern meta_header *mh;

//THIS FUNCTION MAY BE SOON DROPPED
struct node * create_linkedlist()
{
    struct node *start=NULL;
    /*
    file_descriptor *file_descriptor_list;
    long int file_descriptor_list_size;
    file_descriptor_list = hdr -> fd_array;
    file_descriptor_list_size = mh -> file_descriptors_used;


    int i;
    if(file_descriptor_list_size<=0)
        return NULL;

    for(i=0; i<file_descriptor_list_size ; i++)
    {
        start= insert_linkedlist(start , file_descriptor_list[i]);
    }
    */
    return start;
}

//TODO check if filedescriptor is directory and then only add
bst* create_bst()
{
    file_descriptor *file_descriptor_list;
    long int file_descriptor_list_size;
    file_descriptor_list = hdr -> fd_array;
    file_descriptor_list_size = mh -> file_descriptors_used;

    if(file_descriptor_list_size <=0)
        return NULL;

    bst * tree = NULL;
    //tree = init_bst(tree, file_descriptor_list[0]);

    long int i;
    for(i=0; i < file_descriptor_list_size; i ++)
    {
        tree = insert_bst(tree, file_descriptor_list[i]);
    }

    return tree;
}

void test_create_bst()
{
    file_descriptor *file_descriptor_list;
    long int file_descriptor_list_size;
    file_descriptor_list = hdr -> fd_array;
    file_descriptor_list_size = mh -> file_descriptors_used;

    long int size = 5;
    file_descriptor* fd_array = NULL;
    fd_array = create_test_fd_data(fd_array, size);
    bst * bst_tree = create_bst(fd_array, size);

    printf("\nInorder traversal\n");
    inorder_traversal(bst_tree, &displaybst);

    printf("\nPreorder traversal\n");
    preorder_traversal(bst_tree, &displaybst);

    printf("\nPostorder traversal\n");
    postorder_traversal(bst_tree);
}

struct node* fill_hashtable(struct node * hashtable[])
{
    file_descriptor *file_descriptor_list;
    long int file_descriptor_list_size;
    file_descriptor_list = hdr -> fd_array;
    file_descriptor_list_size = mh -> file_descriptors_used;

    struct node * test=NULL;
    int i=0;

    for(i=0; i<file_descriptor_list_size ; i++)
    {
        test=insert_hashtable(hashtable, file_descriptor_list[i]);
    }

    return test;
}

nNode * create_nAry_tree()
{
    nNode *nAryTree = NULL;
    file_descriptor *file_descriptor_list;
    long int file_descriptor_list_size;
    file_descriptor_list = hdr -> fd_array;
    file_descriptor_list_size = mh -> file_descriptors_used;

    if(file_descriptor_list_size <=0)
        return NULL;

    long int i;
    for(i=0; i < file_descriptor_list_size; i ++)
    {
        if(strcmp(file_descriptor_list[i].file_type, "file"))
        {
           // nAryTree = add_file_nary(nAryTree, file_descriptor_list[i].file_name,
            //                         file_descriptor_list[i].location_full_path);
        }
        else if(strcmp(file_descriptor_list[i].file_type, "dir"))
        {
           // nAryTree = add_dir_nary(nAryTree,
           //                          file_descriptor_list[i].location_full_path);
        }

    }

    return nAryTree;
}

int arr_index = 0;
file_descriptor *file_descriptor_list;
long int file_descriptor_list_size;

void update_fd_list(nNode* root)
{
    file_descriptor_list = hdr -> fd_array;
    file_descriptor_list_size = mh -> file_descriptors_used;

    //create an empty file descriptor
    file_descriptor empty_file_desc;
    strcpy(empty_file_desc.file_name, "");
    strcpy(empty_file_desc.location_full_path, "");
    strcpy(empty_file_desc.file_type, "");
    empty_file_desc.file_size = 0;
    empty_file_desc.location_block_num = -1;

    //clear existing file_descriptor array
    int i;
    for(i = 0; i< file_descriptor_list_size; i++)
    {
        file_descriptor_list[i] = empty_file_desc;
    }

    //traverse each node of nary tree and add a file descriptor for each node
    traverse_nary(root, process_file_desc);

    //update the number of file descriptors used
    mh -> file_descriptors_used = arr_index;
}

void process_file_desc(nNode* node)
{
    //add to a file descriptor array
    //file_descriptor_list[arr_index++] = node -> filedescriptor;
}

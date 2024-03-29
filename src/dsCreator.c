#include <stdio.h>
#include <string.h>
#include "../include/Filesystem.h"
#include "../include/nAry.h"
#include "../include/Bst.h"
#include "../include/LinkedList.h"
#include "../include/Hashtable.h"
#include "../include/dsCreator.h"
#include "../include/Commons.h"

void update_filedes(bst *bst_node);
extern header *hdr;
extern meta_header *mh;
extern nNode * nAry_tree;
extern bst   * bst_tree;
extern struct node * hashtable[HASHSIZE];

int arr_index = 0;
file_descriptor *file_descriptor_list;
long int file_descriptor_list_size;
file_descriptor empty_file_desc;
int fd_count = 0;

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
    file_descriptor_list_size = mh -> VFS_FILE_SIZE;

    if(file_descriptor_list_size <=0)
        return NULL;

    bst * tree = NULL;
    //tree = init_bst(tree, file_descriptor_list[0]);

    long int i;
    for(i=0; i < file_descriptor_list_size; i ++)
    {
        if((strcmp(file_descriptor_list[i].file_type,"file") ==0)
                || (strcmp(file_descriptor_list[i].file_type,"dir") == 0))
            tree = insert_bst(tree, file_descriptor_list[i]);
    }

    return tree;
}

//void test_create_bst()
//{
////    file_descriptor *file_descriptor_list;
////    long int file_descriptor_list_size;
//    file_descriptor_list = hdr -> fd_array;
//    file_descriptor_list_size = mh -> file_descriptors_used;
//
//    long int size = 5;
//    file_descriptor* fd_array = NULL;
//    fd_array = create_test_fd_data(fd_array, size);
//    bst * bst_tree = create_bst(fd_array, size);
//
//    printf("\nInorder traversal\n");
//    inorder_traversal(bst_tree, &displaybst);
//
//    printf("\nPreorder traversal\n");
//    preorder_traversal(bst_tree, &displaybst);
//
//    printf("\nPostorder traversal\n");
//    postorder_traversal(bst_tree);
//}

struct node* fill_hashtable(struct node * hashtable[])
{
    file_descriptor *file_descriptor_list;
    long int file_descriptor_list_size;
    file_descriptor_list = hdr -> fd_array;
    file_descriptor_list_size = mh -> VFS_FILE_SIZE;

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
    file_descriptor_list_size = mh -> VFS_FILE_SIZE;

    //if(file_descriptor_list_size <=0)
    nAryTree = insertNode(nAryTree,"","/");

    char node_with_path[FULLPATH_MAX_SIZE];

    long int i;
    for(i=0; i < file_descriptor_list_size; i ++)
    {
//        join_name_path(node_with_path, file_descriptor_list[i].location_full_path, file_descriptor_list[i].file_name);
//        if(is_vfs_node(node_with_path))
//        {
//           continue;
//        }

        if(strcmp(file_descriptor_list[i].file_type, "file") == 0)
        {
            nAryTree = insertNode_filedesc(nAryTree, file_descriptor_list[i]);
            //nAryTree = add_file_nary(nAryTree, file_descriptor_list[i].file_name,
            //                        file_descriptor_list[i].location_full_path);
        }
        else if(strcmp(file_descriptor_list[i].file_type, "dir") == 0)
        {
            join_name_path(node_with_path, file_descriptor_list[i].location_full_path, file_descriptor_list[i].file_name);

            if(strcmp(file_descriptor_list[i].location_full_path, "/") !=0)
            {
                nAryTree = add_dir_nary(nAryTree,
                                        node_with_path);
            }
        }

    }

    return nAryTree;
}

void update_fd_list(bst* bst_root)
{
    file_descriptor_list = hdr -> fd_array;
    file_descriptor_list_size = mh -> VFS_FILE_SIZE;

    //create an empty file descriptor
    strcpy(empty_file_desc.file_name, "0");
    strcpy(empty_file_desc.location_full_path, "0");
    strcpy(empty_file_desc.file_type, "0");
    empty_file_desc.file_size = 0;
    empty_file_desc.location_block_num = -1;
    //clear all the file descriptors
    clear_file_desc_list();
    inorder_traversal(bst_tree, update_filedes);

//    //clear existing file_descriptor array
//    for(i = 0; i< file_descriptor_list_size; i++)
//    {
//        file_descriptor_list[i] = empty_file_desc;
//    }

    //traverse each node of nary tree and add a file descriptor for each node
    //traverse_nary(root, process_file_desc);

    //update the number of file descriptors used
    //mh -> file_descriptors_used = arr_index;
}

void update_filedes(bst *bst_node)
{
    if (bst_node -> is_deleted != 1)
    {
        if(fd_count < (mh->VFS_FILE_SIZE))
        {
            file_descriptor_list[fd_count] = bst_node -> filedescriptor;
            fd_count++;
            mh -> file_descriptors_used  = fd_count;
        }
    }
}

void clear_file_desc_list()
{
    int j;
    for(j = 0; j < (mh->VFS_FILE_SIZE); j++)
    {
        file_descriptor_list[j] = empty_file_desc;
    }
    mh -> file_descriptors_used = 0;
}

void print_ds()
{
    display_nary(nAry_tree, 1);
    inorder_traversal(bst_tree, displaybst);
}

void bst_to_hashtable_update()
{
    init_hashtable(hashtable);
    inorder_traversal(bst_tree, update_fd_hashtable);
}

void update_fd_hashtable(bst *bst_node)
{
    if(bst_node -> is_deleted != 1)
    {
        insert_hashtable(hashtable, bst_node -> filedescriptor);
    }
}

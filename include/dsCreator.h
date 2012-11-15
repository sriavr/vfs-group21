#ifndef DSCREATOR_H_INCLUDED
#define DSCREATOR_H_INCLUDED

//used by file system to create a linked list containing free list of blocks
//THIS FUNCTION MAY BE SOON DROPPED
struct node * create_linkedlist();

//used by file system to create a binary search tree with filenames with absolute path
bst* create_bst(file_descriptor * file_descriptor_list, long int file_descriptor_list_size);

//used by filesystem to create an empty hash table and fill it with directory info
struct node* fill_hashtable(struct node * hashtable[], file_descriptor * file_descriptor_list, long int file_descriptor_list_size);

//nAry Tree representing directory structure
nNode * create_nAry_tree(file_descriptor * file_descriptor_list, long int file_descriptor_list_size);

//open the nary tree and save the nodes of nary tree into fd list
void update_fd_list();
#endif

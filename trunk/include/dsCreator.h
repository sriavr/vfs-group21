#ifndef DSCREATOR_H_INCLUDED
#define DSCREATOR_H_INCLUDED

//used by file system to create a linked list containing free list of blocks
//THIS FUNCTION MAY BE SOON DROPPED
struct node * create_linkedlist();

//open the nary tree and save the nodes of nary tree into fd list
void update_fd_list();

void print_ds();

//used by file system to create a binary search tree with filenames with absolute path
bst* create_bst();

//nAry Tree representing directory structure
nNode * create_nAry_tree();

//used by filesystem to create an empty hash table and fill it with directory info
struct node* fill_hashtable(struct node * hashtable[]);
#endif

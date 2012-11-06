#include <stdio.h>
#include <stdlib.h>
#include "../include/Filesystem.h"
#include "../include/nary_tree.h"

//returns all the sub-directories & files inside a specified directory
//in form of a linkedlist of file_descriptors (not recursive)
file_descriptor *listall_nary(nNode * root, char * dir_path, int is_recursive)
{

}

/* add a file_descriptor node to existing nary tree.
If root is null, create the root node. Check if the node currently added is dir or file.
If dir and parents don't exist, create filedescriptors for each of nonexistant parents */
nNode* add_nary(nNode * root, file_descriptor filedescriptor)
{

}

//check if node is file or dir, if dir, and it contains subdir or files,
//don't allow deletion and throw the error
nNode* delete_nary(nNode * root, file_descriptor filedescriptor)
{

}

//move a directory from source to destination, all the contents of subtree should
//also be moved
nNode * movedir_nary(nNode * root, char * src_dir_path, char * dest_dir_path)
{

}

//print all the contents (dir, files) on console (in indented format)
nNode * display_nary(nNode * root)
{
    printf("Filepath: %s\t Filename: %s\t Filetype: %s\t Block No: %d\n",
            root -> filedescriptor.location_full_path, root -> filedescriptor.file_name,
            root -> filedescriptor.file_type, root -> filedescriptor.location_block_num);
}

//similar to traversal in BST
nNode * traverse_nary(nNode *root, void (*process_nary_node)(nNode * node))
{

}


//returns 0 if the directory doesn't exist, returns 1 if directory exists
int directory_exists(nNode * root, char * dir_path)
{

}


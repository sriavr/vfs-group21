#ifndef NARY_TREE_H_INCLUDED
#define NARY_TREE_H_INCLUDED

typedef struct nAryNode
{
    struct nAryNode *child;
    struct nAryNode *sibling;
    file_descriptor filedescriptor;
} nNode;

typedef struct lst{
    char ** dirnames;
    int size;
} node_list;

//returns all the sub-directories & files inside a specified directory
//in form of a linkedlist of file_descriptors (not recursive)
node_list listall_nary(nNode * root, char * dir_path, int is_recursive);

/* add a file_descriptor node to existing nary tree.
If root is null, create the root node. Check if the node currently added is dir or file.
If dir and parents don't exist, create filedescriptors for each of nonexistant parents */
nNode* add_file_nary(nNode * root, char * filename , char * filepath);

nNode* add_dir_nary(nNode * root, char * node_path);

//check if node is file or dir, if dir, and it contains subdir or files,
//don't allow deletion and throw the error
nNode* delete_file_nary(nNode * root, char * node_path);

nNode* delete_dir_nary(nNode * root, char * node_path);

//move a directory from source to destination, all the contents of subtree should
//also be moved
nNode * move_dir_nary(nNode * root, char * src_dir_path, char * dest_dir_path);

nNode * move_file_nary(nNode * root, char * srcfile_with_dir_path, char * dest_dir_path);

//print all the contents (dir, files) on console (in indented format)
nNode * display_nary(nNode * root);

//similar to traversal in BST
nNode * traverse_nary(nNode *root, void (*process_nary_node)(nNode * node));

//returns 0 if the directory doesn't exist, returns 1 if directory exists
int directory_exists(nNode * root, char * dir_path);

int file_exists(nNode * root, char * file_path);

#endif // NARY_TREE_H_INCLUDED

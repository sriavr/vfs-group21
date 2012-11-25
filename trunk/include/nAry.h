#ifndef NARY_H_INCLUDED
#define NARY_H_INCLUDED

#define MAX_LEVELS 20
#define MAX_LENGTH 50

#define SUCCESS 0
#define FAILED 1

typedef struct nAryTree
{
    struct nAryTree * child;
    struct nAryTree * sibling;
    char name[10];
    file_descriptor *fd;
}nNode;

void display_nary( nNode * root , int level );
nNode * find( nNode * root , char nPath[] );
nNode * removeLinkFromList( nNode * list , char * nodeName );

nNode* createNode(char name[]);

int indexOf( char str[] , char searchChr , int startPos );

char * substring( char * str , int startIndex , int endIndex );

int splitPath(  char nPath[] , char nName[][MAX_LENGTH] );

char* splitstringPath(  char nPath[] );

nNode * searchForNodeInAllSiblings( nNode * t , char name[] );

nNode * insertAtEnd( nNode * t , char name[] );

nNode* insertNode( nNode * root , char nPath[] , char name[] );
//nNode* insertNode( nNode * root , file_descriptor filedescriptor );

void changeLevel( int level, FILE * fp );

void print( char str[][MAX_LENGTH], int count );

void testSplit();



typedef struct lst{
    char ** dirnames;
    int size;
} node_list;

//returns all the sub-directories & files inside a specified directory
//in form of a linkedlist of file_descriptors (not recursive)
void listall_nary(nNode * root, char * dir_path, int flag, FILE * fp);

/* add a file_descriptor node to existing nary tree.
If root is null, create the root node. Check if the node currently added is dir or file.
If dir and parents don't exist, create filedescriptors for each of nonexistant parents */
nNode* add_file_nary(nNode * root, char * filename , char * filepath);

nNode* add_dir_nary(nNode * root, char * dirpath);

//check if node is file or dir, if dir, and it contains subdir or files,
//don't allow deletion and throw the error
nNode* delete_file_nary(nNode * root, char * node_path);

nNode* delete_dir_nary(nNode * root, char * node_path);

//move a directory from source to destination, all the contents of subtree should
//also be moved
nNode * move_dir_nary(nNode * root, char * src_dir_path, char * dest_dir_path);

nNode * move_file_nary(nNode * root, char * srcfile_with_dir_path, char * dest_dir_path);

//print all the contents (dir, files) on console (in indented format)
nNode * display(nNode * root);

//similar to traversal in BST
nNode * traverse_nary(nNode *root, void (*process_nary_node)(nNode * node));

//returns 0 if the node doesn't exist, returns 1 if node exists. Node can be file or directory
int node_exists(nNode * root, char * nPath);

//int file_exists(nNode * root, char * file_path);
#endif

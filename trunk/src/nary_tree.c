#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/Filesystem.h"
#include "../include/nary_tree.h"
#define MAX_LENGTH 50
char dir_name[][MAX_LENGTH];

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

int indexOf( char str[] , char searchChr , int startPos )
{
    int length = strlen( str );
    int i = -1;
    for( i = startPos ; i < length ; i++ )
        if( str[i] == searchChr )
            return i;
    return -1;
}

char * substring( char * str , int startIndex , int endIndex )
{
    int length = endIndex - startIndex;
    char * copy;
    int index,k=0;
    if( length <= 0 )
        return NULL;
    copy = (char *)malloc(sizeof(char) * (length+1) );

    for( index = startIndex ; index < endIndex ; index++ )
    {
        copy[k] = str[index];
        k++;
    }
    copy[k] = '\0';
    return copy;
}


char* splitstringPath(char nPath[])
{
    int startIndex = 0;
    int endIndex = -1;
    int length = strlen( nPath );
    int count = 0;
    do
    {
        endIndex = indexOf( nPath , '/' , startIndex + 1 );
        if( endIndex == -1 )
            endIndex = length;

        char * substr = substring( nPath, startIndex + 1 , endIndex );
        if( substr != NULL )
        {
            strcpy( dir_name[count] , substr );
            count++;
        }

        startIndex = endIndex ;
    }
    while( endIndex != length );

    return dir_name[count-1];
}

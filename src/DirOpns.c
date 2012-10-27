#include <string.h>
#include <stdio.h>
#include "../include/DirOpns.h"
#include "../include/Filesystem.h"
#include "../include/nAry.h"
extern nNode * nAry_tree;
void make_dir(char *parent_path, char *dir_name)
{
    /*
        1) Add a node to NaryTree with directory name

    */
    //nAry_tree = insertNode(nAry_tree,parent_path,dir_name);
    file_descriptor filedescriptor;
    strcpy(filedescriptor.location_full_path, dir_name);

//    nAryNode = insertNode(nAry_tree, filedescriptor);
    printf("makedir_SUCCESS\n");
}

void displaynary(){
    display_nary( nAry_tree , 0 );
    printf("display_SUCCESS\n");
}

void delete_dir(char *dir_path)
{
    /*
        1) Delete the node from nAryTree
        2) Physically delete from the hard disk
    */
    printf("deletedir_FAILURE\n");
}

void move_dir(char * src_path, char * dest_path)
{
    /*
        1) Update the node from nAryTree
        2) Physically update from the hard disk
    */
    printf("movedir_FAILURE\n");
}

void list_dir(char *dir_path, int flag, char * txt_file_path)
{
    printf("listdir_FAILURE\n");
}

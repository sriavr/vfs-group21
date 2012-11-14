#include <string.h>
#include <stdio.h>
#include "../include/DirOpns.h"
#include "../include/Filesystem.h"
#include "../include/Bst.h"
#include "../include/nAry.h"
#include "../include/vfs_errorcodes.h"

extern nNode * nAry_tree;
extern bst   * bst_tree;
extern header *hdr;


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

void delete_dir(char *dir_path)
{
    /*
    Delete a node in nary tree (see nary tree documentation)
    If a directory contains files, don’t delete, throw error
    Delete directory from bst
    */

    file_descriptor filedescriptor;
    int is_exists = directory_exists(nAry_tree, dir_path);
    if(is_exists ==1)
    {
        delete_dir_nary(nAry_tree, dir_path);
        //delete_bst(bst_tree, filedescriptor);
    }

    else
    {
        //PRINT ERROR FOR DELETE NOT ALLOWED
    }
    printf("deletedir_FAILURE\n");
}

void move_dir(char * src_path, char * dest_path)
{
    /*
    Perform move directory operation in nary tree (see nary tree documentation)
    Abort operation if source directory or destination directory is missing.
    Update datastructures
    BST (need to write a function to update the filepaths of existing files)
    Hashtable (need to write a function to update the filepaths of existing files)    */

    move_dir_nary(nAry_tree, src_path, dest_path);

    //TODO UPDATE DATA STRUCTURES
    printf("movedir_SUCCESS\n");
}

void list_dir(char *dir_path, int flag, char * txt_file_path)
{
//    printf("listdir_FAILURE\n");
//    node_list nlist = listall_nary(nAry_tree, dir_path, flag);
//
//    FILE *fp;
//    fp = fopen(txt_file_path,"w+");
//
//    int i;
//    for(i=0; i<nlist.size; i++)
//    {
//        fprintf(fp, "Output of list directory\n");
//        fprintf(fp, "list_dir %s %d %s\n", dir_path, flag, txt_file_path);
//        fprintf(fp, "%s\n", nlist.dirnames[i]);
//    }
//    fclose(fp);
//    printf("listdir_SUCCESS\n");
}

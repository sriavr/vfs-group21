#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/DirOpns.h"
#include "../include/Filesystem.h"
#include "../include/Bst.h"
#include "../include/nAry.h"
#include "../include/freelist.h"
#include "../include/vfs_errorcodes.h"

extern nNode * nAry_tree;
extern bst   * bst_tree;
extern header *hdr;

int make_dir(char *parent_path, char *dir_name)
{
    if(!is_mounted())
    {
        printf("\nmakedir_FAILURE "ERR_VFS_MAKEDIR_05);
        return 1;
    }

    nNode * dir_exists;
    long int block_num = next_free_block();
    if(block_num == -1)
    {
        printf("\nmakedir_FAILURE "ERR_VFS_MAKEDIR_01);
        return 1;
    }

    if(!is_valid_name(dir_name))
    {
        printf("\nmakedir_FAILURE "ERR_VFS_MAKEDIR_02);
        return 1;
    }
    //dir_exists = find(nAry_tree,parent_path);
    int fullpath_length = strlen(parent_path);
    int filename_length = strlen(dir_name);
    int length = 0;
    char * key = NULL;

    if(parent_path[fullpath_length - 1] == '/')
    {
        length = fullpath_length + filename_length;
        key = calloc((length+1),sizeof(char));
        strcat(key, parent_path);
        strcat(key, dir_name);
    }
    else
    {
        length = fullpath_length + filename_length;
        key = calloc((length+2),sizeof(char));
        strcat(key, parent_path);
        strcat(key, "/");
        strcat(key, dir_name);
    }

    if(node_exists(nAry_tree, key))
    {
        printf("\nmakedir_FAILURE "ERR_VFS_MAKEDIR_03);
        return 1;
    }

    nAry_tree = insertNode(nAry_tree, parent_path, dir_name);

//    file_descriptor filedescriptor;
//    filedescriptor.file_size = 0;
//    bst_tree = insert_bst(bst_tree, filedescriptor);
//    strcpy(filedescriptor.location_full_path, parent_path);
//    strcpy(filedescriptor.file_name, dir_name);
    printf("makedir_SUCCESS\n");
    return 0;
}

int delete_dir(char *dir_path)
{
    /*
    Delete a node in nary tree (see nary tree documentation)
    If a directory contains files, don’t delete, throw error
    Delete directory from bst
    */

    if(!is_mounted())
    {
        printf("\ndeletedir_FAILURE "ERR_VFS_DELETEDIR_04);
        return 1;
    }

    nNode * dir_exists;
    int is_exists = node_exists(nAry_tree, dir_path);

    dir_exists = find(nAry_tree,dir_path);

    if(dir_exists->child != NULL)
    {
        printf("\ndeletedir_FAILURE "ERR_VFS_DELETEDIR_02);
        return 1;
    }

    if(is_exists ==1)
    {
        delete_dir_nary(nAry_tree, dir_path);
        delete_bst(bst_tree, dir_path);
        printf("deletedir_SUCCESS\n");
    }
    else
    {
        printf("\ndeletedir_FAILURE "ERR_VFS_DELETEDIR_01);
        //PRINT ERROR FOR DELETE NOT ALLOWED
        return 1;
    }
    return 0;
}

int move_dir(char * src_path, char * dest_path)
{
    /*
    Perform move directory operation in nary tree (see nary tree documentation)
    Abort operation if source directory or destination directory is missing.
    Update datastructures
    BST (need to write a function to update the filepaths of existing files)
    Hashtable (need to write a function to update the filepaths of existing files)    */

    if(!is_mounted())
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_08);
        return 1;
    }

    nNode * dir_exists , * dest_dir;

    //dir_exists = find(nAry_tree,src_path);

    if(!node_exists(nAry_tree, src_path))
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_01);
        return 1;
    }

    //dir_exists = find(nAry_tree,dest_path);

    if(!node_exists(nAry_tree, dest_path))
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_02);
        return 1;
    }

    if(is_file(src_path))
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_04);
        return 1;
    }
// TODO DESTINATION_ALREADY_HAVE_SOURCE_DIR
//    dir_exists = find(nAry_tree,src_path);
//    dest_dir   = find(nAry_tree,dest_path);
//
//    if(strcmp(dir_exists->name,dest_dir->name) == 0)
//    {
//        printf(ERR_VFS_MOVEDIR_05);
//    }
//
    if(is_file(dest_path) == 1)
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_07);
        return 1;
    }

    if(strncmp(src_path,dest_path,strlen(src_path))!=0)
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_07);
        return 1;
    }

    move_dir_nary(nAry_tree, src_path, dest_path);

    //TODO UPDATE DATA STRUCTURES
    //printf("\nmovedir_SUCCESS");
    return 0;
}

int list_dir(char *dir_path, int flag, char * txt_file_path)
{
    if(!is_mounted())
    {
        printf("\nlistdir_FAILURE "ERR_VFS_LISTDIR_03);
        return 1;
    }

    FILE *fp;
    fp = fopen(txt_file_path,"w+");

    if(flag == 0 || flag == 1)
    {
        listall_nary(nAry_tree, dir_path, flag, fp);
        fclose(fp);
        printf("listdir_SUCCESS\n");
    }
    else
    {
        printf("\nlistdir_FAILURE "ERR_VFS_LISTDIR_02);
        return 1;
    }
    return 0;
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


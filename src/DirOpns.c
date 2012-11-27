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
       //filesystem full
    nNode * dir_exists;
    long int block_num = next_free_block();
    if(block_num == -1)
    {
        printf(ERR_VFS_MAKEDIR_01);
        return 1;
    }

    if(!is_valid_name(dir_name))
    {
        printf(ERR_VFS_MAKEDIR_02);
        return 1;
    }
    dir_exists = find(nAry_tree,parent_path);

    if(strcmp(dir_exists->name,dir_name) == 0)
    {
        printf(ERR_VFS_MAKEDIR_03);
    }

    if(!is_mounted())
    {
        printf(ERR_VFS_MAKEDIR_05);
        return 1;
    }

    nAry_tree = insertNode(nAry_tree, parent_path, dir_name);

//    file_descriptor filedescriptor;
//    filedescriptor.file_size = 0;
//    bst_tree = insert_bst(bst_tree, filedescriptor);
//    strcpy(filedescriptor.location_full_path, parent_path);
//    strcpy(filedescriptor.file_name, dir_name);
    printf("makedir_SUCCESS\n");
}

void delete_dir(char *dir_path)
{
    /*
    Delete a node in nary tree (see nary tree documentation)
    If a directory contains files, don’t delete, throw error
    Delete directory from bst
    */
    nNode * dir_exists;
    int is_exists = node_exists(nAry_tree, dir_path);

    dir_exists = find(nAry_tree,dir_path);

    if(dir_exists->child != NULL)
    {
        printf(ERR_VFS_DELETEDIR_02);
        return;
    }

    if(!is_mounted())
    {
        printf(ERR_VFS_DELETEDIR_04);
        return;
    }

    if(is_exists ==1)
    {
        delete_dir_nary(nAry_tree, dir_path);
        delete_bst(bst_tree, dir_path);
        printf("deletedir_SUCCESS\n");
    }
    else
    {
        printf(ERR_VFS_DELETEDIR_01);
        //PRINT ERROR FOR DELETE NOT ALLOWED
    }
}

void move_dir(char * src_path, char * dest_path)
{
    /*
    Perform move directory operation in nary tree (see nary tree documentation)
    Abort operation if source directory or destination directory is missing.
    Update datastructures
    BST (need to write a function to update the filepaths of existing files)
    Hashtable (need to write a function to update the filepaths of existing files)    */

    nNode * dir_exists , * dest_dir;

    dir_exists = find(nAry_tree,src_path);

    if(dir_exists->child == NULL)
    {
        printf(ERR_VFS_MOVEDIR_01);
        return;
    }

    dir_exists = find(nAry_tree,dest_path);

    if(dir_exists->child == NULL)
    {
        printf(ERR_VFS_MOVEDIR_02);
        return;
    }

    if(is_file(src_path) == 1)
    {
        printf(ERR_VFS_MOVEDIR_04);
        return;
    }

    dir_exists = find(nAry_tree,src_path);
    dest_dir   = find(nAry_tree,dest_path);

    if(strcmp(dir_exists->name,dest_dir->name) == 0)
    {
        printf(ERR_VFS_MOVEDIR_05);
    }

    if(is_file(dest_path) == 1)
    {
        printf(ERR_VFS_MOVEDIR_07);
        return;
    }

    if(strncmp(src_path,dest_path,strlen(src_path))!=0)
    {
        printf(ERR_VFS_MOVEDIR_07);
        return;
    }

    if(!is_mounted())
    {
        printf(ERR_VFS_MOVEDIR_08);
        return;
    }

    move_dir_nary(nAry_tree, src_path, dest_path);

    //TODO UPDATE DATA STRUCTURES
    printf("movedir_SUCCESS\n");
}

void list_dir(char *dir_path, int flag, char * txt_file_path)
{
    if(!is_mounted())
    {
        printf(ERR_VFS_LISTDIR_03);
        return;
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
        printf(ERR_VFS_LISTDIR_02);
        return;
    }

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

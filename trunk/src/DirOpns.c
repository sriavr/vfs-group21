#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/DirOpns.h"
#include "../include/Filesystem.h"
#include "../include/Bst.h"
#include "../include/nAry.h"
#include "../include/freelist.h"
#include "../include/Commons.h"
#include "../include/dsCreator.h"
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

    if(!is_valid_name(dir_name))
    {
        printf("\nmakedir_FAILURE "ERR_VFS_MAKEDIR_02);
        return 1;
    }

    correct_dir_path(parent_path);

    //nNode * dir_exists;
    //dir_exists = find(nAry_tree,parent_path);
//    int fullpath_length = strlen(temp_path);
//    int filename_length = strlen(dir_name);
//    int length = 0;
//    char * key = NULL;
//
//    if(temp_path[fullpath_length - 1] == '/')
//    {
//        length = fullpath_length + filename_length;
//        key = calloc((length+1),sizeof(char));
//        strcat(key, temp_path);
//        strcat(key, dir_name);
//    }
//    else
//    {
//        length = fullpath_length + filename_length;
//        key = calloc((length+2),sizeof(char));
//        strcat(key, temp_path);
//        strcat(key, "/");
//        strcat(key, dir_name);
//    }
    char key[FULLPATH_MAX_SIZE];
    join_name_path(key, parent_path, dir_name);

    if(is_dir(key))
    {
        printf("\nmakedir_FAILURE "ERR_VFS_MAKEDIR_03);
        return 1;
    }

    long int block_num = next_free_block();
    if(block_num == -1)
    {
        printf("\nmakedir_FAILURE "ERR_VFS_MAKEDIR_01);
        return 1;
    }

    nAry_tree = insertNode(nAry_tree, parent_path, dir_name);
    //UPDATE HASHTABLE AFTER BST IS CHANGED
    bst_to_hashtable_update();

//    file_descriptor filedescriptor;
//    filedescriptor.file_size = 0;
//    bst_tree = insert_bst(bst_tree, filedescriptor);
//    strcpy(filedescriptor.location_full_path, parent_path);
//    strcpy(filedescriptor.file_name, dir_name);
    //printf("makedir_SUCCESS\n");
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

    if(!is_dir(dir_path))
    {
        printf("\ndeletedir_FAILURE "ERR_VFS_DELETEDIR_01);
        //PRINT ERROR FOR DELETE NOT ALLOWED
        return 1;
    }

    //    int is_exists = node_exists(nAry_tree, dir_path);
    nNode * dir_exists;
    dir_exists = find(nAry_tree,dir_path);

    if((dir_exists != NULL) && (dir_exists->child != NULL))
    {
        printf("\ndeletedir_FAILURE "ERR_VFS_DELETEDIR_02);
        return 1;
    }

    correct_dir_path(dir_path);
    delete_dir_nary(nAry_tree, dir_path);
    delete_bst(bst_tree, dir_path);
    //UPDATE HASHTABLE AFTER BST IS CHANGED
    bst_to_hashtable_update();
    //delete_hashtable(hashtable, dir_path);

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

    if(is_file(src_path) == 1)
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_04);
        return 1;
    }

    if(is_file(dest_path) == 1)
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_07);
        return 1;
    }

    //nNode * dir_exists , * dest_dir;
    //dir_exists = find(nAry_tree,src_path);

    if(!is_dir(src_path))
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_01);
        return 1;
    }

    //dir_exists = find(nAry_tree,dest_path);

    if(!is_dir(dest_path))
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_02);
        return 1;
    }

    correct_dir_path(src_path);
    correct_dir_path(dest_path);

    // /a/b/c/d/  /a/b/c/d/e/f
    int k;
    int length, tmp_flag = 0;
    if(strlen(dest_path) < strlen(src_path))
    {
        length = strlen(dest_path);
    }
    else
    {
        length = strlen(src_path);
    }

    for(k = 0; k < length; k++)
    {
        if(dest_path[k] != src_path[k])
        {
            tmp_flag = 1;
            break;
        }
        else
        {
            tmp_flag = 0;
        }
    }

    if(tmp_flag == 0)
    {
        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_06);
        return 1;
    }


// TODO DESTINATION_ALREADY_HAVE_SOURCE_DIR, CANNOT_MOVE_PARENT_TO_CHILD_DIR
//    dir_exists = find(nAry_tree,src_path);
//    dest_dir   = find(nAry_tree,dest_path);
//
//    if(strcmp(dir_exists->name,dest_dir->name) == 0)
//    {
//        printf(ERR_VFS_MOVEDIR_05);
//    }
//
//    if(strncmp(src_path,dest_path,strlen(src_path))!=0)
//    {
//        printf("\nmovedir_FAILURE "ERR_VFS_MOVEDIR_06);
//        return 1;
//    }

    move_dir_nary(nAry_tree, src_path, dest_path);

    //UPDATE HASHTABLE AFTER BST IS CHANGED
    bst_to_hashtable_update();
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

    if(!is_dir(dir_path))
    {
        printf("\nlistdir_FAILURE "ERR_VFS_LISTDIR_01);
        return 1;
    }

    if(!physical_file_canwrite(txt_file_path))
    {
        printf("\nlistdir_FAILURE "ERR_VFS_LISTDIR_04);
        return 1;
    }

    if(flag == 0 || flag == 1)
    {
        FILE *fp;
        fp = fopen(txt_file_path,"w+");
        correct_dir_path(dir_path);
        listall_nary(nAry_tree, dir_path, flag, fp);
        fclose(fp);
        return 0;
    }
    else
    {
        printf("\nlistdir_FAILURE "ERR_VFS_LISTDIR_02);
        return 1;
    }
    return 0;
}


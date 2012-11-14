#include <string.h>
#include <stdio.h>
#include "../include/DirOpns.h"
#include "../include/Filesystem.h"
#include "../include/Bst.h"
#include "../include/nAry.h"

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

//void delete_dir(char *dir_path)
//{
//    /*
//        1) Delete the node from nAryTree
//        2) Physically delete from the hard disk
//    */
//    file_descriptor filedescriptor;
//    int is_exists = directory_exists(nAry_tree, dir_path);
//    if(is_exists ==1)
//    {
//             char *file_name = delete_dir_nary(nAry_tree, filedescriptor);
//            //if it is dir then nary logic will throw error n should return 'f' to indiate that it is file n should return 0 as char
//            //else if it is file then should return filename
//            if(strcmp(file_name , "0")!=0)
//            {
//                strcat(dest_path ,"/");
//                strcat(dest_path ,file_name);
//                for(int i=0;i<MAX_NUM_OF_BLOCKS;i++)
//                {
//
//                    if(strcmp(dest_path)
//                }
//                delete_hashtable(hashtable , filedescriptor);
//                delete_bst(bst_tree , filedescriptor , position)
//
//            }
//    }
//    printf("deletedir_FAILURE\n");
//}

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

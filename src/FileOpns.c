#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/Filesystem.h"
#include "../include/LinkedList.h"
#include "../include/Hashtable.h"
#include "../include/nAry.h"
#include "../include/Bst.h"
#include "../include/freelist.h"
#include "../include/Commons.h"
#include "../include/FileOpns.h"
#include "../include/dsCreator.h"
#include "../include/DirOpns.h"
#include "../include/vfs_errorcodes.h"

extern nNode * nAry_tree;
extern bst *bst_tree;
extern struct node *hashtable[HASHSIZE];
extern header *hdr;

//1)CHECK IF DIRECTORY EXISTS IN NARY
//3)ADD THE FILE TO BST & HASH TABLE
//4)Save to disk
//5)UPDATE FILEDESCRIPTOR DURING UNMOUNT
int add_file(char *dest_dir_path , char* file_name , char* data_file_path)
{
    if(!is_mounted())
    {
        printf("addfile_FAILURE "ERR_VFS_ADDFILE_07"\n");
        return 1;
    }

    if(!physical_file_exists(data_file_path))
    {
        printf("addfile_FAILURE "ERR_VFS_LISTFILE_01"\n");
        return 1;
    }

    //if filename is not a valid name
    if(!is_valid_name(file_name))
    {
        printf("addfile_FAILURE "ERR_VFS_ADDFILE_02"\n");
        return 1;
    }

    //if file already exists
    //char temp[FULLPATH_MAX_SIZE];
//    strcpy(temp, dest_dir_path);
//    strcat(temp, file_name);
    char full_path[FULLPATH_MAX_SIZE];
    join_name_path(full_path, dest_dir_path, file_name);

    if(is_file(full_path))
    {
        printf("addfile_FAILURE "ERR_VFS_ADDFILE_03"\n");
        return 1;
    }

    //filesystem full
    long int block_num = next_free_block();
    if(block_num == -1)
    {
        printf("addfile_FAILURE "ERR_VFS_ADDFILE_04"\n");
        return 1;
    }

    if(!is_dir(dest_dir_path))
    {
        printf("addfile_FAILURE\n");
        return 1;
    }

//    if(physical_file_canwrite(data_file_path))
//    {
//        printf(ERR_VFS_ADDFILE_05);
//        return 1;
//    }

    FILE *fp_data_file = fopen(data_file_path, "rb");
    fseek(fp_data_file, 0L, SEEK_END);
    long int size = ftell(fp_data_file);
    fclose(fp_data_file);

    if(size > BLOCK_SIZE)
    {
        printf("addfile_FAILURE "ERR_VFS_ADDFILE_06"\n");
        return 1;
    }

    //printf("block_num ::%d\n",block_num);
    //printf("updated_value ::%d\n",i);
    //update_flist_deallocate(long int block_num);
    if(write_to_block(block_num, data_file_path, size) < 0)
    {
        printf("addfile_FAILURE "ERR_VFS_ADDFILE_05"\n");
        return 1;
    }

    file_descriptor filedescriptor;
    strcpy(filedescriptor.file_name, file_name);
    strcpy(filedescriptor.location_full_path, dest_dir_path);
    strcpy(filedescriptor.file_type, "file");
    filedescriptor.file_size = size;
    filedescriptor.location_block_num = block_num;

    //create a directory if doesn't exist and modify data structures
    //add_file_nary(nAry_tree, filedescriptor.file_name, filedescriptor.location_full_path);
    bst_tree = insert_bst(bst_tree, filedescriptor);
    insertNode_filedesc(nAry_tree, filedescriptor);
    //search_hashtable(hashtable, file_name )  ;        //pass filedescriptor file_name in this
    insert_hashtable(hashtable, filedescriptor);
    //UPDATE HASHTABLE AFTER BST IS CHANGED
    bst_to_hashtable_update();

    //display_file_descriptor(filedescriptor);

    //printf("addfile_SUCCESS\n");
    return 0;
}

int list_file(char * file_path , char* output_file)
{
    if(!is_mounted())
    {
        printf("listfile_FAILURE "ERR_VFS_LISTFILE_04"\n");
        return 1;
    }

    int flag = 1;
    int block_number = -1;
    long int filesize;

    if(!is_file(file_path))
    {
        printf("listfile_FAILURE "ERR_VFS_LISTFILE_01"\n");
        return 1;
    }

    char * found = strstr(file_path , ".txt");
    if(found == NULL)
    {
        printf("listfile_FAILURE "ERR_VFS_LISTFILE_02"\n");
        return 1;
    }

    if(!physical_file_canwrite(output_file))
    {
        printf("listfile_FAILURE "ERR_VFS_LISTFILE_03"\n");
        return 1;
    }

    block *read_block;
    file_descriptor filedescriptor;
    filedescriptor = search_bst_full(bst_tree, file_path);
    block_number = filedescriptor.location_block_num;
    filesize = filedescriptor.file_size;
    read_block = read_from_block(block_number, filesize , flag);

    FILE *fp;
    fp = fopen(output_file , "w+");
    fwrite(read_block,filesize,1,fp);
    fclose(fp);
    //printf("listfile_SUCCESS\n");
    return 0;
}

/* Priya's code

int list_file(char * file_path , char* output_file)
{
    int block_num =0;
    file_descriptor  filedescriptor;
    filedescriptor = search_bst(bst_tree ,file_path );
    block_num = filedescriptor.location_block_num ;
    FILE *output , *fp;
    output = fopen(output_file ,"w+b");
    fp = fopen(full_path_file_name ,"r+b");

    long int size = filedescriptor.file_size;

    block *get_content =(block*) malloc(sizeof(block));
    if(fseek(fp, sizeof(meta_header) + sizeof(header) + sizeof(block) * (block_num), SEEK_SET) != 0)
    {
        return 1;
    }

    if(fread(get_content,size,1,fp)!=1)
    {
        return 1;
    }

    if(fwrite(get_content, size, 1 ,output)!=1)
    {
        return 1;
    }
    printf("listfile_SUCCESS\n");
    return 0;
}


*/

//implementation for search_file operation
/*int search_file(char *filename, char *outputfile)
{
    struct node *match = NULL;
    match = search_hashtable(hashtable,filename);

    FILE *fp;
    fp = fopen(outputfile,"w+");

    fprintf(fp, "%10s %4s %150s %8s\n", "Filename", "Filetype", "Filepath", "Filesize");
    while(match!=NULL)
    {
        fprintf(fp, "%10s %4s %150s %8ld\n", match->filedescriptor.file_name, match->filedescriptor.file_type, match->filedescriptor.location_full_path, match->filedescriptor.file_size);
        match =  match->next;
    }

    fclose(fp);
    printf("searchfile_SUCCESS\n");
    return 0;
}*/

int search_file(char *filename, char *outputfile)
{
    if(!is_mounted())
    {
        printf("searchfile_FAILURE "ERR_VFS_SEARCHFILE_02"\n");
        return 1;
    }

    struct node *match = NULL;
    match = search_hashtable(hashtable,filename);

    FILE *fp;
    fp = fopen(outputfile,"w+");
    if(fp == NULL)
    {
        printf("searchfile_FAILURE\n");
        return 1;
    }

    fprintf(fp, "%s %s %s %s\n", "Filename", "Filetype", "Filepath", "Filesize");
    int x = 0;
    while(match!=NULL)
    {
        x ++;
        fprintf(fp, "%s %s %s %ld\n", match->filedescriptor.file_name, match->filedescriptor.file_type, match->filedescriptor.location_full_path, match->filedescriptor.file_size);
        match =  match->next;
    }

    fclose(fp);
    //printf("searchfile_SUCCESS\n");
    return x;
}


int remove_file(char *file_path)
{
    if(!is_mounted())
    {
        printf("removefile_FAILURE "ERR_VFS_REMOVEFILE_02"\n");
        return 1;
    }

    file_descriptor filedescriptor;
    filedescriptor = search_bst_full(bst_tree,file_path);

    if(is_file(file_path))
    {
        printf("removefile_FAILURE "ERR_VFS_REMOVEFILE_01"\n");
        return 1;
    }

    char temp_node_path[FULLPATH_MAX_SIZE];
    join_name_path(temp_node_path, filedescriptor.location_full_path, filedescriptor.file_name);

    delete_bst(bst_tree, temp_node_path);
    delete_file_nary(nAry_tree, file_path);
    //delete_hashtable(hashtable, filedescriptor);
    //UPDATE HASHTABLE AFTER BST IS CHANGED
    bst_to_hashtable_update();

    update_flist_deallocate(filedescriptor.location_block_num);
//    int full_path_length = strlen(filedescriptor.location_full_path);
//    int file_name_length = strlen(filedescriptor.file_name);
//    char * temp_node_path = NULL;
//    if(filedescriptor.location_full_path[full_path_length - 1] == '/')
//    {
//        temp_node_path = (char *) malloc(sizeof(char) * (full_path_length + file_name_length));
//        strcat(temp_node_path, filedescriptor.location_full_path);
//        strcat(temp_node_path, filedescriptor.file_name);
//    }
//    else
//    {
//        temp_node_path = (char *) malloc(sizeof(char) * (full_path_length + file_name_length + 1));
//        strcat(temp_node_path, filedescriptor.location_full_path);
//        strcat(temp_node_path, "/");
//        strcat(temp_node_path, filedescriptor.file_name);
//    }
    /*        strcpy(filedescriptor.file_name,"");
            strcpy(filedescriptor.location_full_path,"");
            strcpy(filedescriptor.file_type,"");
            filedescriptor.file_size = 0;
            filedescriptor.location_block_num = 0;
    */

    return 0;
}

int export_file(char *source_file_path, char *destination_file_path)
{
    //vfs is not mounted
    if(!is_mounted())
    {
        printf("exportfile_FAILURE "ERR_VFS_EXPORTFILE_04"\n");
        return 1;
    }

    //can't export directory
    if(is_dir(source_file_path))
    {
        printf("exportfile_FAILURE "ERR_VFS_EXPORTFILE_03"\n");
        return 1;
    }

    //source file not found
    if(!is_file(source_file_path))
    {
        printf("exportfile_FAILURE "ERR_VFS_EXPORTFILE_01"\n");
        return 1;
    }

    //can't create output file
    if(!physical_file_canwrite(destination_file_path))
    {
        printf("exportfile_FAILURE "ERR_VFS_EXPORTFILE_02"\n");
        return 1;
    }

    int flag = 0;
    int block_number = -1;
    long int filesize;
    block *read_block;
    file_descriptor filedescriptor;
    filedescriptor = search_bst_full(bst_tree, source_file_path);

    block_number = filedescriptor.location_block_num;
    filesize = filedescriptor.file_size;
    read_block = read_from_block(block_number, filesize , flag);

    FILE *fp;
    fp = fopen(destination_file_path , "wb+");
    fwrite(read_block,filesize,1,fp);
    //printf("exportfile_SUCCESS\n");
    fclose(fp);
    return 0;
}


int copy_file(char *source_file_with_path , char *destination_file_path)
{
//    if(strcmp(filedescriptor.location_full_path ,"0")==0 || strcmp(filedescriptor.file_type,"file")!=0)
//    {
//        printf("copyfile_FAILURE "ERR_VFS_COPYFILE_01);
//        return 1;
//    }

//    if(strcmp(filedescriptor.file_type,"dir")==0)
//    {
//        printf("copyfile_FAILURE "ERR_VFS_COPYFILE_03);
//        return 1;
//    }
//    char nName[MAX_LEVELS][MAX_LENGTH],
//    dirname[MAX_LENGTH];
//    int count = splitPath(destination_file_path, nName);
//    strcpy(dirname,nName[count-1]);
//    int full_path_length = strlen(dirname);
//    if(dirname[full_path_length - 1] != '/')
//    {
//        strcat(dirname, "/");
//    }

//    if(!node_exists(nAry_tree, filedescriptor.location_full_path))
//    {
//        printf("copyfile_FAILURE "ERR_VFS_COPYFILE_02);
//        return 1;
//    }
    //adding to datastructures except nAry
    //add_file_nary(nAry_tree, filedescriptor.file_name, filedescriptor.location_full_path);


    if(!is_mounted())
    {
        printf("copyfile_FAILURE "ERR_VFS_COPYFILE_05"\n");
        return 1;
    }

    if(is_dir(source_file_with_path))
    {
        printf("copyfile_FAILURE "ERR_VFS_COPYFILE_03"\n");
        return 1;
    }

    if(!is_file(source_file_with_path))
    {
        printf("copyfile_FAILURE "ERR_VFS_COPYFILE_01"\n");
        return 1;
    }

    char dest_parent_path[FULLPATH_MAX_SIZE], dest_name[FILENAME_MAX_SIZE];
    split_name_path(destination_file_path, dest_parent_path, dest_name);

    if(!is_dir(dest_parent_path))
    {
        printf("copyfile_FAILURE "ERR_VFS_COPYFILE_02"\n");
        return 1;
    }

    int dest_block_num = -1;
    dest_block_num = next_free_block();
    if(dest_block_num == -1)
    {
        printf("copyfile_FAILURE "ERR_VFS_COPYFILE_04"\n");
        return 1;
    }

    file_descriptor src_filedescriptor , dest_filedescriptor;
    src_filedescriptor = search_bst_full(bst_tree, source_file_with_path);

    strcpy(dest_filedescriptor.file_name , dest_name);
    strcpy(dest_filedescriptor.location_full_path , dest_parent_path);
    strcpy(dest_filedescriptor.file_type, src_filedescriptor.file_type);
    dest_filedescriptor.file_size = src_filedescriptor.file_size;
    dest_filedescriptor.location_block_num = dest_block_num;

    if(copy_block_to_block(dest_block_num,
                           src_filedescriptor.location_block_num,
                           src_filedescriptor.file_size) < 0)
    {
        printf("copyfile_FAILURE\n");
        return 1;
    }

    insertNode_filedesc(nAry_tree, dest_filedescriptor);
    insert_bst(bst_tree, dest_filedescriptor);
    //UPDATE HASHTABLE AFTER BST IS CHANGED
    bst_to_hashtable_update();

    //insert_hashtable(hashtable, dest_filedescriptor);
    return 0;
}

int move_file(char *source_file_with_path , char *destination_with_path )
{
//    block_num = next_free_block();
//    char nName[MAX_LEVELS][MAX_LENGTH],
//    dirname[MAX_LENGTH];
//    int count = splitPath(destination_with_path, nName);
//    strcpy(dirname,nName[count-1]);
//    int full_path_length = strlen(dirname);
//    if(dirname[full_path_length - 1] != '/')
//    {
//        strcat(dirname, "/");
//    }
//    if(!node_exists(nAry_tree, filedescriptor.location_full_path))
//    {
//        printf("movefile_FAILURE "ERR_VFS_MOVEFILE_02);
//        return 1;
//    }
//    full_path_length = strlen(filedescriptor.location_full_path);
//    int file_name_length = strlen(filedescriptor.file_name);
//    char * temp_node_path = NULL;
//    if(filedescriptor.location_full_path[full_path_length - 1] == '/')
//    {
//        temp_node_path = (char *) malloc(sizeof(char) * (full_path_length + file_name_length));
//        strcat(temp_node_path, filedescriptor.location_full_path);
//        strcat(temp_node_path, filedescriptor.file_name);
//    }
//    else
//    {
//        temp_node_path = (char *) malloc(sizeof(char) * (full_path_length + file_name_length + 1));
//        strcat(temp_node_path, filedescriptor.location_full_path);
//        strcat(temp_node_path, "/");
//        strcat(temp_node_path, filedescriptor.file_name);
//    }

    if(!is_mounted())
    {
        printf("movefile_FAILURE "ERR_VFS_MOVEFILE_06"\n");
        return 1;
    }

    if(!is_file(source_file_with_path))
    {
        printf("movefile_FAILURE "ERR_VFS_MOVEFILE_01"\n");
        return 1;
    }

    char dest_parent_path[FULLPATH_MAX_SIZE], dest_name[FILENAME_MAX_SIZE];
    split_name_path(destination_with_path, dest_parent_path, dest_name);

    if(!is_dir(dest_parent_path))
    {
        printf("movefile_FAILURE "ERR_VFS_MOVEFILE_02"\n");
        return 1;
    }

    file_descriptor src_filedescriptor, dest_filedescriptor;
    src_filedescriptor = search_bst_full(bst_tree, source_file_with_path);

    strcpy(dest_filedescriptor.file_name, dest_name);
    strcpy(dest_filedescriptor.location_full_path, dest_parent_path);
    strcpy(dest_filedescriptor.file_type, src_filedescriptor.file_type);
    dest_filedescriptor.file_size = src_filedescriptor.file_size;
    dest_filedescriptor.location_block_num = src_filedescriptor.location_block_num;

    //insertNode_filedesc(nAry_tree, dest_filedescriptor);
    //insert_bst(bst_tree, dest_filedescriptor);

    insertNode_filedesc(nAry_tree, dest_filedescriptor);
    insert_bst(bst_tree, dest_filedescriptor);
    insert_hashtable(hashtable, dest_filedescriptor);

    delete_file_nary(nAry_tree, source_file_with_path);
    delete_bst(bst_tree, source_file_with_path);
    //delete_hashtable(hashtable, src_filedescriptor);

    //UPDATE HASHTABLE AFTER BST IS CHANGED
    bst_to_hashtable_update();

    return 0;
}
/*int i,k;
i = copy_file(source_file_with_path , destination_with_path);
k = remove_file(source_file_with_path);
if(i != 0 || k != 0)
{
    return 1;
}
else
{
    return 0;
}
*/


/*void test()
{
    char * dest_dir_path ="/home/priya/Desktop";
    char * file_name ="graphics.txt";
    char * data_file_path ="/home/priya/Desktop/graphics.txt";
    char * destination_file_path="/home/priya/Desktop/destined.txt";
    char * outputfile = "output.txt";
    char * exportfile ="/home/priya/Desktop/export.txt";
    char * destination2_with_path ="/home/priya/Desktop/destined2.txt";
    add_file(dest_dir_path ,file_name ,data_file_path);

    int receive = search_file(file_name,outputfile);

    export_file(data_file_path, exportfile);

    copy_file(data_file_path ,destination_file_path);

 //   move_file(data_file_path ,destination2_with_path );

    int received = search_file(file_name,outputfile);

}

int  main()
{
    test();
    return 0;
}
*/

int update_file( char *source_file_with_path, char *data_file)
{
    if(!is_mounted())
    {
        printf("updatefile_FAILURE "ERR_VFS_UPDATEFILE_04"\n");
        return 1;
    }

    file_descriptor filedescriptor;
    filedescriptor = search_bst_full(bst_tree,source_file_with_path);
    if(strcmp(filedescriptor.file_type ,"file")!=0)
    {
        printf("updatefile_FAILURE "ERR_VFS_UPDATEFILE_01"\n");
        return 1;
    }

    FILE *fp_data_file = fopen(data_file, "rb");
    if(!physical_file_exists(data_file))
    {
        printf("updatefile_FAILURE "ERR_VFS_UPDATEFILE_02"\n");
        return 1;
    }
    /*
        if(fp_data_file== NULL){
            printf(ERR_VFS_UPDATEFILE_02);
            return 1;
        }
    */
    fseek(fp_data_file, 0L, SEEK_END);
    long int size = ftell(fp_data_file);

    if(size > BLOCK_SIZE)
    {
        printf("updatefile_FAILURE "ERR_VFS_UPDATEFILE_03"\n");
        return 1;
    }

    long int block_num = filedescriptor.location_block_num;
    if(write_to_block(block_num, data_file, size) < 0)
        return 1;

    filedescriptor.file_size = size;
    fclose(fp_data_file);
    return 0;
}

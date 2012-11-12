#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/DirOpns.h"
#include "../include/FileOpns.h"
#include "../include/Filesystem.h"
#include "../include/nary_tree.h"
#include "../include/Bst.h"
#include "../include/Hashtable.h"
#include "../include/LinkedList.h"
#include "../include/freelist.h"

extern nNode * nAry_tree;
extern struct bst *bst_tree;
extern struct node *hashtable[HASHSIZE];
extern header *hdr;
extern char full_path_file_name[150];

int add_file(char *dest_dir_path , char* file_name , char* data_file_path)
{
    //1)CHECK IF DIRECTORY EXISTS IN NARY

    //3)ADD THE FILE TO BST & HASH TABLE
    //4)Save to disk
    //5)UPDATE FILEDESCRIPTOR DURING UNMOUNT


    FILE *fp_data_file = fopen(data_file_path, "rb");
    long int size = fseek(fp_data_file, 0L, SEEK_CUR);
    size = ftell(fp_data_file);
    fclose(fp_data_file);
//    int i, block_num = -1;
//    for(i=0; i<MAX_NUM_OF_BLOCKS; i++)
//    {
//        if(hdr->list[i].allocated == 0)
//        {
//            block_num = i;
//            break;
//        }
//    }

    long int block_num = next_free_block();
    write_to_block(block_num, data_file_path, size);

    file_descriptor filedescriptor;
    strcpy(filedescriptor.file_name, file_name);
    strcpy(filedescriptor.location_full_path, dest_dir_path);
    strcpy(filedescriptor.file_type, "file");
    filedescriptor.file_size = size;
    filedescriptor.location_block_num = block_num;

    //create a directory if doesn't exist and modify data structures
    //char *name = splitstringPath(dest_dir_path);
    //make_dir(dest_dir_path, name);
    add_nary(nAry_tree,filedescriptor);
    bst_tree = insert_bst(bst_tree, filedescriptor);
    insert_hashtable(hashtable, filedescriptor);
    printf("addfile_SUCCESS\n");
    return 0;
}

int list_file(char * file_path , char* output_file)
{
    int flag = 1;
    int block_number ;
    long int filesize;
    block *read_block;
    file_descriptor filedescriptor;
    filedescriptor = search_bst(bst_tree , file_path);
    block_number = filedescriptor.location_block_num;
    filesize = filedescriptor.file_size;
    read_block = read_from_block(block_number, filesize , flag);

    FILE *fp;
    fp = fopen(output_file , "w+");
    fwrite(read_block,filesize,1,fp);
    fclose(fp);
    printf("listfile_SUCCESS\n");
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
int search_file(char *filename, char *outputfile)
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
}

void remove_file(char *file_path)
{
    //TODO

}

void export_file(char *source_file_path, char *destination_file_path)
{
    int flag = 0;
    int block_number ;
    long int filesize;
    block *read_block;
    file_descriptor filedescriptor;
    filedescriptor = search_bst(bst_tree , source_file_path);
    //TODO
    // implement searh_bst in Bst.c

    block_number = filedescriptor.location_block_num;
    filesize = filedescriptor.file_size;
    read_block = read_from_block(block_number, filesize , flag);

    FILE *fp;
    fp = fopen(destination_file_path , "wb+");
    fwrite(read_block,filesize,1,fp);
    printf("exportfile_SUCCESS\n");
    fclose(fp);
}

void copy_file(char *source_file_with_path , char *destination_file_path)
{
    int block_num = -1;
    file_descriptor filedescriptor , new_filedescriptor;
    filedescriptor = search_bst(bst_tree , source_file_with_path);

    /*
    for(i=0; i<MAX_NUM_OF_BLOCKS; i++)
    {
        if(hdr->list[i].allocated == 0)
        {
            block_num = i;
            break;// returns the first free block number
        }
    }*/
    block_num = next_free_block();

    strcpy(new_filedescriptor.file_name , filedescriptor.file_name);
    strcpy(new_filedescriptor.location_full_path , destination_file_path);
    //assuming location_file_path is containing only file path and not file name
    strcpy(new_filedescriptor.file_type , filedescriptor.file_type);
    new_filedescriptor.file_size = filedescriptor.file_size;
    new_filedescriptor.location_block_num = block_num;

    //adding to datastructures except nAry
    insert_bst(bst_tree, new_filedescriptor);
    insert_hashtable(hashtable, new_filedescriptor);
    printf("copyfile_SUCCESS\n");
}

void move_file(char *source_file_with_path , char *destination_with_path )
{
    copy_file(source_file_with_path , destination_with_path);
    remove_file(source_file_with_path);
    //TODO
    // implement remove_file
    printf("searchfile_FAILURE\n");
}

void test()
{
    char * dest_dir_path ="/home/priya/Desktop";
    char * file_name ="graphics.txt";
    char * data_file_path ="/home/priya/Desktop/graphics.txt";
    char * destination_file_path="/home/priya/Desktop/destined.txt";
    char * outputfile = "output.txt";
    char * export_file ="/home/priya/Desktop/export.txt";
    char * destination2_with_path ="/home/priya/Desktop/destined2.txt";
    add_file(dest_dir_path ,file_name ,data_file_path);

    int receive = search_file(file_name,outputfile);

    export_file(data_file_path, export_file);

    copy_file(data_file_path ,destination_file_path);

    move_file(data_file_path ,destination2_with_path );

    int received = search_file(file_name,outputfile);

}

void main()
{
    test();
}

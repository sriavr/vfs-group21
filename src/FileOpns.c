#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/DirOpns.h"
#include "../include/FileOpns.h"
#include "../include/Filesystem.h"
#include "../include/nAry.h"
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
    //2)IF IT DOES NOT EXISTS THEN CALL MAKE_DIR()
    //3)ADD THE FILE TO BST & HASH TABLE
    //4)Save to disk
    //5)UPDATE FILEDESCRIPTOR DURING UNMOUNT

    //find file size
//    struct stat buf;
//    stat(file_name, &buf);
//    int size = buf.st_size;
      FILE *fp_data_file = fopen(data_file_path, "rb");
      long int size = fseek(fp_data_file, 0L, SEEK_END);
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
    char *name = splitstringPath(dest_dir_path);
    make_dir(dest_dir_path, name);
    bst_tree = insert_bst(bst_tree, filedescriptor);
    insert_hashtable(hashtable, filedescriptor);
    printf("addfile_SUCCESS\n");
    return 0;
}

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

int search_hash(char *filename, char *outputfile){
    struct node *match = NULL;
    match = search_hashtable(hashtable,filename);

    FILE *fp;
    fp = fopen(outputfile,"w+");

    fprintf(fp, "%10s %4s %150s %8s\n", "Filename", "Filetype", "Filepath", "Filesize");
    while(match!=NULL){
        fprintf(fp, "%10s %4s %150s %8ld\n", match->filedescriptor.file_name, match->filedescriptor.file_type, match->filedescriptor.location_full_path, match->filedescriptor.file_size);
        match =  match->next;
    }

    fclose(fp);
    printf("searchfile_SUCCESS\n");
    return 0;
}


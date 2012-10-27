#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#include "../include/DirOpns.h"
#include "../include/FileOpns.h"
#include "../include/Filesystem.h"
#include "../include/nAry.h"
#include "../include/Bst.h"
#include "../include/Hashtable.h"
#include "../include/LinkedList.h"

extern nNode * nAry_tree;
extern struct bst *bst_tree;
extern struct node *hashtable[HASHSIZE];
extern header *hdr;

void add_file(char *dest_dir_path , char* file_name , char* data_file_path)
{
    //1)CHECK IF DIRECTORY EXISTS IN NARY
    //2)IF IT DOES NOT EXISTS THEN CALL MAKE_DIR()
    //3)ADD THE FILE TO BST & HASH TABLE
    //4)Save to disk
    //5)UPDATE FILEDESCRIPTOR DURING UNMOUNT

    //find file size
    struct stat buf;
    stat(file_name, &buf);
    int size = buf.st_size;

    int i, block_num = -1;
    for(i=0; i<MAX_NUM_OF_BLOCKS; i++)
    {
        if(hdr->list[i].allocated == 0)
        {
            block_num = i;
            break;
        }
    }

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
    insert_bst(bst_tree, filedescriptor);
    insert_hashtable(hashtable, filedescriptor);
}


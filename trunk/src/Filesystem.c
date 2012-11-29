#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/Filesystem.h"
#include "../include/LinkedList.h"
#include "../include/Hashtable.h"
#include "../include/nAry.h"
#include "../include/Bst.h"
#include "../include/dsCreator.h"
#include "../include/Commons.h"
#include "../include/freelist.h"
#include "../include/vfs_errorcodes.h"

header *hdr =NULL;
meta_header *mh =NULL;
//block *block_array; //NO NEED TO READ BLOCK ARRAY

nNode * nAry_tree = NULL;
bst * bst_tree = NULL;
struct node * hashtable[HASHSIZE];
char vfs_label_global[FILE_SYSTEM_LABEL_MAX_SIZE];

int create_vfs(char vfs_label[150], int size)
{
    FILE *fp;

    //will find whether size is less then required size
    if(size < 0 || size > 1024)
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_04);
        return 1;
    }

    size  = size * 1024;

    int no_of_characters = strlen(vfs_label);
    if(no_of_characters > FILE_SYSTEM_LABEL_MAX_SIZE)
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_05);
        return 1;
    }

    if(!is_valid_name(vfs_label))
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_03);
        return 1;
    }

    if(physical_file_exists(vfs_label))
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_01);
        return 1;
    }

    if(!physical_file_canwrite(vfs_label))
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_02 );
        return 1;
    }

    fp=fopen(vfs_label,"w+b");
    //allocates memory for the file system
    char *memory=(char*) malloc(size + sizeof(header) + sizeof(meta_header));

    //save the created memory to disk
    if(fwrite(memory,size,1,fp) != 1)
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_02 );
        return 1;
    }

    fclose(fp);

    fp=fopen(vfs_label,"r+b");

    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    //copy filesystem label with full path to the meta header field
    strcpy(mh->file_system_label, vfs_label);

    mh->file_descriptors_used = 0;

    //write meta header to the file
    if(fwrite(mh,sizeof(meta_header),1,fp) != 1)
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_02 );
        return 1;
    }

    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    //strcpy(hdr -> HEADER_TEST_FIELD, "TEST HEADER OK");

    //initialize the allocated flag to 0 in free list
    init_free_list();

    //create_test_fd_data(hdr -> fd_array, size);

    //write header to the files
    if(fwrite(hdr,sizeof(header),1,fp) != 1)
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_02 );
        return 1;
    }

    block *block_array;
    //allocate memory for block_array
    //block_array = calloc(MAX_NUM_OF_BLOCKS, sizeof(block));
    block_array = malloc(size);

    //write the block_array into disk
    if(fwrite(block_array,size,1,fp) != 1)
    {
        printf("\ncreatevfs_FAILURE "ERR_VFS_CREATE_02 );
        return 1;
    }

    fclose(fp);
    free(hdr);
    free(mh);
    hdr = NULL;
    mh = NULL;

    return 0;
}

/**
    Traverse all the file descriptors and create
    1) nAry Tree representing directory structure
    2) Hashtable storing all the file names without path (for search based on file name without path)
    // ~~~ NOT NEEDED 3) Linkedlist storing list of the free blocks into which new files can be written
    4) BST storing all the file names with absolute path of file (for search based on absolute path of file)
*/
int mount_vfs(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE])
{
    file_descriptor *file_descriptor_list;
    long int file_descriptor_used;

    strcpy(vfs_label_global, vfs_label);

    if(is_mounted())
    {
        printf("\nmountvfs_FAILURE "ERR_VFS_MOUNT_03);
        return 1;
    }

    //read meta header, header
    if(!is_mounted())
    {
        if(!physical_file_exists(vfs_label))
        {
            printf("\nmountvfs_FAILURE "ERR_VFS_MOUNT_01);
            return 1;
        }

        mh = read_meta_header(vfs_label);
        hdr = read_header(vfs_label);

        if(mh == NULL || hdr == NULL)
        {
            printf("\nmountvfs_FAILURE "ERR_VFS_MOUNT_02);
            return 1;
        }

        file_descriptor_list = hdr -> fd_array;
        file_descriptor_used = mh -> file_descriptors_used;

        //BST storing all the file names with absolute path of file (for search based on absolute path of file)
        bst_tree = create_bst();

        //Create nAry Tree representing directory structure
        nAry_tree = (nNode *) create_nAry_tree();

        //Create Hashtable storing all the file names without path (for search based on file name without path)
        //init_hashtable(hashtable);
        //fill_hashtable(hashtable);
        bst_to_hashtable_update();
    }
    return 0;
}

int unmount_vfs(char filepath[FILE_SYSTEM_LABEL_MAX_SIZE])
{
    //if vfs is not mounted
    if(!is_mounted())
    {
        printf("\nunmountvfs_FAILURE "ERR_VFS_UNMOUNT_03);
        return 1;
    }

    if(strcmp(filepath, vfs_label_global) != 0)
    {
        printf("\nunmountvfs_FAILURE "ERR_VFS_UNMOUNT_01);
        return 1;
    }

    //update the fd_list using the nary tree
    update_fd_list(bst_tree);

    //if vfs file is not found
    if(!physical_file_exists(filepath))
    {
        printf("\nunmountvfs_FAILURE "ERR_VFS_UNMOUNT_01);
        return 1;
    }

    //if vfs file can't be written to
    if(!physical_file_canwrite(filepath))
    {
        printf("\nunmountvfs_FAILURE "ERR_VFS_UNMOUNT_02);
        return 1;
    }

    FILE *fp;
    fp=fopen(vfs_label_global, "r+b");

    if((fwrite(mh,sizeof(meta_header),1,fp))!=1)
    {
        printf("\nunmountvfs_FAILURE "ERR_VFS_UNMOUNT_02 );
        return 1;
    }
    //printf("successfully unmount meta_header");

    if((fwrite(hdr,sizeof(header),1,fp))!=1)
    {
        printf("\nunmountvfs_FAILURE "ERR_VFS_UNMOUNT_02 );
        return 1;
    }

    fclose(fp);
    free(mh);
    free(hdr);

    mh = NULL;
    hdr = NULL;
    free(nAry_tree);
    nAry_tree = NULL;
    free(bst_tree);
    bst_tree = NULL;
    strcpy(vfs_label_global, "");
    //clear hash table
    //hashtable
    //printf("unmountvfs_SUCCESS\n");
    return 0;
}

int write_to_block(long int block_num, char * filename_with_path, int size)
{
    FILE *fp;
    //fp is file pointer to VFS
    fp = fopen(vfs_label_global,"r+b");

    //Set the position indicator of file pointer to the end of header by offsetting sizeof(meta_header) + sizeof(header) bytes
    if(fseek(fp, sizeof(meta_header) + sizeof(header) + sizeof(block) * (block_num), SEEK_SET) != 0)
    {
        fclose(fp);
        return 1;
    }

    //create an empty block that has to be saved
    block *newfile_block;
    newfile_block = (block *)malloc(sizeof(block));
    newfile_block->next_block_num = 0;

    //copy the contents of file into block structure
    FILE *newfile;
    newfile = fopen(filename_with_path, "rb");
    if(newfile == NULL)
    {
        return 1;
    }

    if(fread(newfile_block, size, 1, newfile)!=1)
    {
        return 1;
    }
    fclose(newfile);

    //write the new block into the vfs (hard disk)
    if(fwrite(newfile_block, size, 1, fp)!=1)
    {
        return 1;
    }

    fclose(fp);
    return 1;
}

//if flag is 1 it is text file, else if flag is 0, it is binary file
block* read_from_block(long int block_num, int size , int flag)
{
    FILE *fp;
    //fp is file pointer to VFS
    if(flag==1)
    {
        fp = fopen(vfs_label_global,"r");
    }
    else if(flag==0)
    {
        fp = fopen(vfs_label_global,"rb");
    }
    //Set the position indicator of file pointer to the end of header by offsetting sizeof(meta_header) + sizeof(header) bytes
    if(fseek(fp, sizeof(meta_header) + sizeof(header) + sizeof(block) * (block_num), SEEK_SET) != 0)
    {
        //printf("\nFailed to read block array");
        fclose(fp);
        return NULL;
    }

    //create an empty block that has to be saved
    block *newfile_block;
    newfile_block = (block *)malloc(sizeof(block));
    newfile_block->next_block_num = 0;

    //write the new block into the vfs
    if(fread(newfile_block, size, 1, fp)!=1)
    {
        return NULL;
    }
    fclose(fp);
    return newfile_block;
}

int copy_block_to_block(long int dest_block_num, long int src_block_num, int size)
{
    block * src_block;
    src_block = read_from_block(src_block_num, size, 0);

    FILE *fp;
    //fp is file pointer to VFS
    fp = fopen(vfs_label_global,"r+b");

    //Set the position indicator of file pointer to the end of header by offsetting sizeof(meta_header) + sizeof(header) bytes
    if(fseek(fp, sizeof(meta_header) + sizeof(header) + sizeof(block) * (dest_block_num), SEEK_SET) != 0)
    {
        fclose(fp);
        return 1;
    }

    //write the new block into the vfs (hard disk)
    if(fwrite(src_block, size, 1, fp)!=1)
    {
        return 1;
    }

    fclose(fp);
    return 1;
}

meta_header * read_meta_header(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE])
{
    FILE *fp;
    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    if(!physical_file_exists(vfs_label))
    {
        //printf(ERR_VFS_MOUNT_01);
        return NULL;
    }

    fp = fopen(vfs_label, "rb");
    //read and copy the meta header to mh
    if(fread(mh, sizeof(meta_header), 1, fp) != 1)
    {
        //printf(ERR_VFS_UNMOUNT_02);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return mh;
}

header * read_header(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE])
{
    FILE *fp;

    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));

    if(!physical_file_exists(vfs_label))
    {
        //printf(ERR_VFS_MOUNT_01);
        return NULL;
    }

    fp = fopen(vfs_label, "rb");
    //Set the position indicator of file pointer to the header by offsetting sizeof(meta_header) bytes
    if(fseek(fp, sizeof(meta_header), SEEK_SET) != 0)
    {
        //printf("CANNOT SEEK INTO FILE");
        fclose(fp);
        return NULL;
    }

    //read and copy the header to hdr
    if(fread(hdr, sizeof(header), 1, fp) != 1)
    {
        //printf(ERR_VFS_MOUNT_02);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return hdr;
}

block *read_block_array(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE])
{
    FILE *fp;
    block *block_array;

    //allocate memory for header
    block_array = calloc(MAX_NUM_OF_BLOCKS, sizeof(block));

    fp = fopen(vfs_label,"r+b");
    if(fp ==NULL)
        printf("\nmountvfs_FAILURE "ERR_VFS_MOUNT_01);

    //Set the position indicator of file pointer to the end of header by offsetting sizeof(meta_header) + sizeof(header) bytes
    if(fseek(fp, (sizeof(meta_header) + sizeof(header)), SEEK_SET) != 0)
    {
        printf("CANNOT SEEK INTO FILE");
        fclose(fp);
        return NULL;
    }

    //read and copy the block_array to array
    if(fread(block_array, sizeof(MAX_NUM_OF_BLOCKS), 1, fp) != 1)
    {
        printf("\nmountvfs_FAILURE "ERR_VFS_MOUNT_02);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return block_array;
}

//returns 1 if mounted else returns 0
int is_mounted()
{
    if(hdr != NULL && mh != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//if file exists, return 1 or return 0
int physical_file_exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "rb")) != NULL)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

//if we can write return 1, else return 0
int physical_file_canwrite(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "ab")) != NULL)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

//returns 1 if the vfs dir_path is a directory, else 0
int is_dir(char * dir_path)
{
    file_descriptor filedescriptor = search_bst_full(bst_tree, dir_path);
    if(strcmp(filedescriptor.file_type, "dir") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//returns 1 if vfs file_path is a file, else 0
int is_file(char * file_path)
{
    file_descriptor filedescriptor = search_bst_full(bst_tree, file_path);
    if(strcmp(filedescriptor.file_type, "file") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//returns 1 if vfs file_path is a node, else 0
int is_vfs_node(char * file_path)
{
    file_descriptor filedescriptor = search_bst_full(bst_tree, file_path);
    if((strcmp(filedescriptor.file_type, "file") == 0) || (strcmp(filedescriptor.file_type, "dir") == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//returns 1 if valid, 0 if invalid
int is_valid_name( char * file_name )
{
    int no_of_characters = strlen(file_name);
    int i;
    for( i=0 ; i< no_of_characters ; i++)
    {
        if((file_name[i] == '/') ||
                (file_name[i] == '\\')||
                (file_name[i] == '\0'))
        {
            return 0;
        }
    }
    return 1;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
char full_path_file_name[150];

void fsystem_ui()
{
    char full_path_file_name[150];
    int file_length,ret=0;

    printf("\nEnter the file name with full path: ");
    scanf("%s",full_path_file_name);

    printf("\nEnter size of file in Bytes: ");
    scanf("%d",&file_length);

    //create a virtual file system
    ret=create_vfs(full_path_file_name,file_length);

    if(ret==0)
    {
        printf("\nSuccessfully created the file system\n");
    }
    else
    {
        printf("\nError while creating the file system\n");
    }

    //test the newly created file system
    test_vfs(full_path_file_name);

    //test case for read_meta_header() function
    test_read_meta_header(full_path_file_name);

    //test case for read_header() function
    test_read_header(full_path_file_name);

    //test case for read_block_array
    //test_read_block_array(full_path_file_name);

    //check if mount is working
    mount_vfs(full_path_file_name);

    unmount_vfs(full_path_file_name);
}

int create_vfs(char fullpath[150], int size)
{
    FILE *fp;
    int i=0;

    //will find whether size is less then required size
    if(size < 0 && size > 1024)
    {
        printf(ERR_VFS_CREATE_04);
        return 0;
    }

    size  = size * 1024;

    int no_of_characters = strlen(fullpath);
    if(no_of_characters > 30)
    {
        printf(ERR_VFS_CREATE_05);
        return 0;
    }

    for(i=0 ; i<no_of_characters ; i++)
    {
        int i=0;
        if(fullpath[i] == '/')
        {
            printf(ERR_VFS_CREATE_03);
            return 0;
        }
    }

    if(physical_file_exists(fullpath))
    {
        printf(ERR_VFS_CREATE_01);
        return 1;
    }


    if(!physical_file_canwrite(fullpath))
    {
        printf( ERR_VFS_CREATE_02 );
        return 1;
    }

    fp=fopen(fullpath,"w+b");
    //allocates memory for the file system
    char *memory=(char*) malloc(size + sizeof(header) + sizeof(meta_header));

    //save the created memory to disk
    if(fwrite(memory,size,1,fp) != 1)
    {
        printf( ERR_VFS_CREATE_02 );
        return 1;
    }

    fclose(fp);

    fp=fopen(fullpath,"r+b");

    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    //copy filesystem label with full path to the meta header field
    strcpy(mh->file_system_label, fullpath);

    mh->file_descriptors_used = 0;

    //write meta header to the file
    if(fwrite(mh,sizeof(meta_header),1,fp) != 1)
    {
        printf( ERR_VFS_CREATE_02 );
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
        printf( ERR_VFS_CREATE_02 );
        return 1;
    }

    block *block_array;
    //allocate memory for block_array
    //block_array = calloc(MAX_NUM_OF_BLOCKS, sizeof(block));
    block_array = malloc(size);

    //write the block_array into disk
    if(fwrite(block_array,size,1,fp) != 1)
    {
        printf( ERR_VFS_CREATE_02 );
        return 1;
    }

    fclose(fp);
    free(hdr);
    free(mh);
    hdr = NULL;
    mh = NULL;

    printf("createvfs_SUCCESS\n");

    return(0);
}

/**
    Traverse all the file descriptors and create
    1) nAry Tree representing directory structure
    2) Hashtable storing all the file names without path (for search based on file name without path)
    // ~~~ NOT NEEDED 3) Linkedlist storing list of the free blocks into which new files can be written
    4) BST storing all the file names with absolute path of file (for search based on absolute path of file)
*/
int mount_vfs(char fullpath[150])
{
    file_descriptor *file_descriptor_list;
    long int file_descriptor_used;

    strcpy(full_path_file_name, fullpath);

    if(is_mounted())
    {
        printf(ERR_VFS_MOUNT_03);
        return 0;
    }

    //read meta header, header
    if(!is_mounted())
    {
        mh = read_meta_header(fullpath);
        hdr = read_header(fullpath);
    }
    //block_array = read_block_array(fullpath); //DONT READ BLOCK ARRAY INTO RAM

    file_descriptor_list = hdr -> fd_array;
    file_descriptor_used = mh -> file_descriptors_used;

    //Create nAry Tree representing directory structure
    nAry_tree = (nNode *) create_nAry_tree(file_descriptor_list, file_descriptor_used);

    //Create Hashtable storing all the file names without path (for search based on file name without path)
    init_hashtable(hashtable);
    fill_hashtable(hashtable);

    //BST storing all the file names with absolute path of file (for search based on absolute path of file)
    bst_tree = create_bst(file_descriptor_list, file_descriptor_used);

    //printf("\nInorder traversal\n");
    //inorder_traversal(bst_tree, &displaybst);

    //Linkedlist storing list of the free blocks into which new files can be written
    //struct node *free_blocks_llist = NULL;
    //DOUBTFUL SHOULD GET FREE LIST
    //free_blocks_llist = (struct node *) create_linkedlist(file_descriptor_list, file_descriptor_list_size);

    printf("mountvfs_SUCCESS\n");
    return 0;
}

int unmount_vfs(char filepath[150])
{
    //update the fd_list using the nary tree
    update_fd_list(bst_tree);

    //if vfs file is not found
    if(!physical_file_exists(filepath))
    {
        printf(ERR_VFS_UNMOUNT_01);
        return 1;
    }

    //if vfs file can't be written to
    if(!physical_file_canwrite(filepath))
    {
        printf(ERR_VFS_UNMOUNT_02);
        return 1;
    }

    //if vfs is not mounted
    if(!is_mounted())
    {
        printf(ERR_VFS_UNMOUNT_03);
        return 1;
    }

    FILE *fp;
    fp=fopen(full_path_file_name, "r+b");

    if((fwrite(mh,sizeof(meta_header),1,fp))!=1)
    {
        printf(ERR_VFS_UNMOUNT_02 );
        return 1;
    }
    //printf("successfully unmount meta_header");

    if((fwrite(hdr,sizeof(header),1,fp))!=1)
    {
        printf(ERR_VFS_UNMOUNT_02 );
        return 1;
    }
    //printf("successfully unmount header");
    //WE ARE NOT GOING TO SAVE THE BLOCK ARRAY IN HARD DISK
    /*if(fwrite(block_array,sizeof(BLOCK_SIZE * MAX_NUM_OF_BLOCKS),1,fp)!=1)
    {
        printf("unmountvfs_FAILURE\n");
        return 1;
    }*/
    fclose(fp);
    free(mh);
    free(hdr);
    mh = NULL;
    hdr = NULL;
    free(nAry_tree);
    nAry_tree = NULL;
    free(bst_tree);
    bst_tree = NULL;
    //clear hash table
    //hashtable
    printf("unmountvfs_SUCCESS\n");
    return 0;
}

int write_to_block(long int block_num, char * filename_with_path, int size)
{
    FILE *fp;
    //fp is file pointer to VFS
    fp = fopen(full_path_file_name,"r+b");

    //Set the position indicator of file pointer to the end of header by offsetting sizeof(meta_header) + sizeof(header) bytes
    if(fseek(fp, sizeof(meta_header) + sizeof(header) + sizeof(block) * (block_num), SEEK_SET) != 0)
    {
        fclose(fp);
        return -1;
    }

    //create an empty block that has to be saved
    block *newfile_block;
    newfile_block = (block *)malloc(sizeof(block));
    newfile_block->next_block_num = 0;

    //check the size of the file, if it is more than size of block
    //print error and return 1
//    if(size <= sizeof(block))
//    {
    //copy the contents of file into block structure
    FILE *newfile;
    newfile = fopen(filename_with_path, "rb");
    if(newfile == NULL)
    {
        return -1;
    }

    if(fread(newfile_block, size, 1, newfile)!=1)
    {
        return -1;
    }
    fclose(newfile);

    //write the new block into the vfs (hard disk)
    if(fwrite(newfile_block, size, 1, fp)!=1)
    {
        return -1;
    }
//    }
//    else
//    {
//        return -1;
//    }

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
        fp = fopen(full_path_file_name,"r");
    }
    else if(flag==0)
    {
        fp = fopen(full_path_file_name,"rb");
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

void test_vfs(char fullpath[150])
{
    /*  FILE *fp;
      meta_header *mh;
      header *hdr;*/
    FILE *fp;
    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    fp = fopen(fullpath,"r+b");
    //read and copy the meta header to mh
    if(fread(mh, sizeof(meta_header), 1, fp) != 1)
    {
        printf("Failed to read meta header");
        fclose(fp);
        return;
    }

    print_meta_header_info(mh);

    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    //read and copy the header to hdr
    if(fread(hdr, sizeof(header), 1, fp) != 1)
    {
        printf("\nFailed to read header");
        fclose(fp);
        return;
    }
}

meta_header * read_meta_header(char fullpath[150])
{
    FILE *fp;
    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    fp = fopen(fullpath,"rb");
    if(fp ==NULL)
        printf(ERR_VFS_MOUNT_01);

    //read and copy the meta header to mh
    if(fread(mh, sizeof(meta_header), 1, fp) != 1)
    {
        printf(ERR_VFS_UNMOUNT_02);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return mh;
}

header * read_header(char fullpath[150])
{
    FILE *fp;

    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    fp = fopen(fullpath,"rb");
    if(fp==NULL)
        printf(ERR_VFS_MOUNT_01);
    //Set the position indicator of file pointer to the header by offsetting sizeof(meta_header) bytes
    if(fseek(fp, sizeof(meta_header), SEEK_SET) != 0)
    {
        printf("CANNOT SEEK INTO FILE");
        fclose(fp);
        return NULL;
    }

    //read and copy the header to hdr
    if(fread(hdr, sizeof(header), 1, fp) != 1)
    {
        printf(ERR_VFS_MOUNT_02);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return hdr;
}

block *read_block_array(char fullpath[150])
{
    FILE *fp;
    block *block_array;

    //allocate memory for header
    block_array = calloc(MAX_NUM_OF_BLOCKS, sizeof(block));

    fp = fopen(fullpath,"r+b");
    if(fp ==NULL)
        printf(ERR_VFS_MOUNT_01);

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
        printf(ERR_VFS_MOUNT_02);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return block_array;
}

void test_read_meta_header(char fullpath[150])
{
    mh =  read_meta_header(fullpath);
    if(mh!=NULL)
    {
        print_meta_header_info(mh);
    }
    else
    {
        printf("\n read_meta_header() function failed");
    }
}

void test_read_header(char fullpath[150])
{
    hdr = read_header(fullpath);
    if(hdr!=NULL)
    {
        print_header_info(hdr);
    }
    else
    {
        printf("\n read_header() function failed");
    }
}

void test_read_block_array(char fullpath[150])
{
    block *block_array;
    block_array = read_block_array(fullpath);
    int i;
    if(block_array !=NULL)
    {
        for(i=0; i< MAX_NUM_OF_BLOCKS; i++)
        {
            print_block(block_array[i]);
        }
        printf("\n number of blocks printed: %d", MAX_NUM_OF_BLOCKS);
    }
    else
    {
        printf("\n read_block_array() function failed");
    }

}

void print_block(block blk)
{
    int i;
    printf("\nStart of block\n");
    for(i=0; i< BLOCK_SIZE; i++)
    {
        printf("%d",blk.data[i]);
    }
    printf("\nEnd of block\n");
}


void print_meta_header_info(meta_header * mh)
{
    printf("\ninformation in meta header:");
    printf("\nfile_system_label: %s", mh -> file_system_label);
    //printf("\nmax_num_file_descriptors: %ld", mh -> max_num_file_descriptors);
    printf("\nfile_descriptors_used: %ld", mh -> file_descriptors_used);
}

void print_header_info(header * hdr)
{
    printf("\ninformation in header:");
    //printf("\nHEADER_TEST_FIELD: %s", hdr -> HEADER_TEST_FIELD);
}

file_descriptor * create_test_fd_data(file_descriptor * fd_array, long int size)
{
    if(fd_array == NULL)
    {
        fd_array = calloc(size, sizeof(file_descriptor));
    }
    char *temp_file_path;
    temp_file_path = calloc(150, sizeof(char));

    char * file_type[2] = {"file","dir"};
    long int i;
    for(i =0; i < size; i++)
    {
        temp_file_path = calloc(150, sizeof(char));

        strcpy(fd_array[i].file_name, generate_rand_string());

        strcat(temp_file_path, "/");
        strcat(temp_file_path, generate_rand_string());
        strcat(temp_file_path, "/");
        strcat(temp_file_path, generate_rand_string());
        strcat(temp_file_path, "/");
        strcat(temp_file_path, generate_rand_string());
        strcpy(fd_array[i].location_full_path, temp_file_path);

        strcpy(fd_array[i].file_type, file_type[rand()%2]);
        fd_array[i].file_size = rand();
        fd_array[i].location_block_num = rand();
    }

    return fd_array;
}


void display_file_descriptor(file_descriptor output)
{

    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);

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

//returns 1 if valid, 0 if invalid
int is_valid_name( char * file_name )
{
    int no_of_characters = strlen(file_name);
    int i;
    for( i=0 ; i< no_of_characters ; i++)
    {
        if(file_name[i] == '/')
        {
            return 0;
        }
    }
    return 1;
}

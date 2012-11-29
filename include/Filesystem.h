#ifndef FILESYSTEM_H_INCLUDED
#define FILESYSTEM_H_INCLUDED

#define MAX_NUM_OF_BLOCKS 100 //assuming one block has one file
#define FILE_SYSTEM_LABEL_MAX_SIZE 30
#define FILETYPE_MAX_SIZE 10
#define FILENAME_MAX_SIZE 128
#define FULLPATH_MAX_SIZE 256
#define BLOCK_SIZE 10240


/*
## structure for File descriptor##
 * File name
 * Location of the file
 * Type of file (directory/file)
 * Size of file
 * Location block number of the file
*/
typedef struct fDes
{
    //ensure that strings are ending with '\0'
    char file_name[FILENAME_MAX_SIZE];
    char location_full_path[FULLPATH_MAX_SIZE];
    char file_type[FILETYPE_MAX_SIZE ];
    long int file_size;
    int location_block_num;
} file_descriptor;


/*
## structure for storing the free list ##
 * Contains the pointer to the next free block
  block numbering starts from 0
*/
//WE SHOULD INITIALIZE NEXT_FREE_BLOCK TO -1 IN ALL BLOCKS BY DEFAULT
typedef struct fLst
{
    //int block_num;
    //if allocated store 1, not allocated store 0
    int allocated:1;
} free_list;

/*
## structure for meta header ##
 * Name of file system
 * Number of used file descriptors
*/
typedef struct mHdr
{
    char file_system_label[FILE_SYSTEM_LABEL_MAX_SIZE];
    long unsigned int file_descriptors_used;
} meta_header;

/*
## structure for header ##
 * File descriptor list
 * Free list
*/
typedef struct head
{
    //considering one file is stored in one file, MAX_NUM_OF_BLOCKS = FILE_DESCRIPTOR_MAX_LIMIT
    file_descriptor fd_array[MAX_NUM_OF_BLOCKS];
    free_list list[MAX_NUM_OF_BLOCKS];
    //char HEADER_TEST_FIELD[50]; //only for testing purpose, should be deleted in release time
} header;

typedef struct max_block_size
{
    char data[BLOCK_SIZE];
    long int next_block_num;
} block;


//create a Virtual File System. <vfs_label> is the name of VFS
int create_vfs(char *,int );

//Mount a Virtual File System. <vfs_label> is the name of VFS
int mount_vfs(char *);

//does a quick test by reading the header and meta header info from vfs
void test_vfs(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE]);

//returns the meta header structure from the vfs
meta_header * read_meta_header(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE]);

//returns the header structure from the vfs
header * read_header(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE]);

//returns the block_array an array of block structures from vfs
block *read_block_array(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE]);

//prints information of given meta header structure
void print_meta_header_info(meta_header * mh);

//prints information of given header structure
void print_header_info(header * hdr);

//script for user interaction
void fsystem_ui();

//test case for read_meta_header() function
void test_read_meta_header(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE]);

//test case for read_header() function
void test_read_header(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE]);

//test case for read_block_array() function
void test_read_block_array(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE]);

//generate test file descriptor array of given size
file_descriptor * create_test_fd_data(file_descriptor * fd_array, long int size);

//print a block
void print_block(block blk);

//unmounting meta_header,header n blocks of disk
int unmount_vfs(char vfs_label[FILE_SYSTEM_LABEL_MAX_SIZE]);

//write contents of a file to a block
int write_to_block(long int block_num, char * filename_with_path, int size);

//read the file from vfs block and return a new block
block* read_from_block(long int block_num, int size , int flag);

int copy_block_to_block(long int dest_block_num, long int src_block_num, int size);

void display_file_descriptor(file_descriptor output);

//returns 1 if mounted, else returns 0
int is_mounted();

//returns 1 if file exists or 0 if file does not exists
int physical_file_exists(const char *fname);

//if we can write return 1, else return 0
int physical_file_canwrite(const char *fname);

int is_dir(char * dir_path);

int is_file(char * file_path);

int is_vfs_node(char * file_path);

int is_valid_name( char * file_name );
#endif

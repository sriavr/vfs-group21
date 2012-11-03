#define FILE_DESCRIPTOR_MAX_LIMIT 10000
#define MAX_NUM_OF_BLOCKS 10000 //assuming one block has one file
#define FREE_LIST_MAX_LIMIT 500000
#define FILE_SYSTEM_LABEL_MAX_SIZE 150
#define FILENAME_MAX_SIZE 50
#define FULLPATH_WITH_FILENAME_MAX_SIZE 150
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
    char location_full_path[FULLPATH_WITH_FILENAME_MAX_SIZE];
    char file_type[10];
    long int file_size;
    int location_block_num;
} file_descriptor;


/*
## structure for storing the free list ##
 * Contains the pointer to the next free block
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
    char HEADER_TEST_FIELD[50]; //only for testing purpose, should be deleted in release time
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
void test_vfs(char fullpath[150]);

//returns the meta header structure from the vfs
meta_header * read_meta_header(char fullpath[150]);

//returns the header structure from the vfs
header * read_header(char fullpath[150]);

//returns the block_array an array of block structures from vfs
block *read_block_array(char fullpath[150]);

//prints information of given meta header structure
void print_meta_header_info(meta_header * mh);

//prints information of given header structure
void print_header_info(header * hdr);

//script for user interaction
void fsystem_ui();

//test case for read_meta_header() function
void test_read_meta_header(char fullpath[150]);

//test case for read_header() function
void test_read_header(char fullpath[150]);

//test case for read_block_array() function
void test_read_block_array(char fullpath[150]);

//generate test file descriptor array of given size
file_descriptor * create_test_fd_data(file_descriptor * fd_array, long int size);

//print a block
void print_block(block blk);

//unmounting meta_header,header n blocks of disk
int unmount_vfs(char  full_file_path_name[150]);

//write contents of a file to a block
int write_to_block(long int block_num, char * filename_with_path, int size);

//read the file from vfs block and return a new block
block* read_from_block(long int block_num, int size , int flag);

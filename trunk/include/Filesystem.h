#define FILE_DESCRIPTOR_MAX_LIMIT 1000000
#define FREE_LIST_MAX_LIMIT 500000
#define FILE_SYSTEM_LABEL_MAX_SIZE 150
#define FILENAME_MAX_SIZE 50
#define FULLPATH_WITH_FILENAME_MAX_SIZE 150

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
typedef struct fLst
{
    int block_num;
    struct fLst *next_free_block;
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
    file_descriptor desc[FILE_DESCRIPTOR_MAX_LIMIT];
    free_list list[FREE_LIST_MAX_LIMIT];
    char HEADER_TEST_FIELD[50]; //only for testing purpose, should be deleted in release time
} header;

typedef struct max_block_size
{
    int block_size;
} mBsz;


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

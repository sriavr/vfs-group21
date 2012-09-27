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
    char file_name[50];
    char location_full_path[150];
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
    char file_system_label[60];
    long int max_num_file_descriptors;
    int file_descriptors_used;
} meta_header;

/*
## structure for header ##
 * File descriptor list
 * Free list
*/
typedef struct head
{
    file_descriptor desc[1000000];
    free_list list[500000];
} header;

typedef struct max_block_size
{
    int block_size;
} mBsz;


//create a Virtual File System. <vfs_label> is the name of VFS
int create_vfs(char *,int );

void test_fsystem();

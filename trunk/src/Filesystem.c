#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Filesystem.h"
#include "../include/LinkedList.h"
#include "../include/Hashtable.h"
#include "../include/nAry.h"
#include "../include/Bst.h"
#include "../include/dsCreator.h"
#include "../include/Commons.h"

header *hdr;
meta_header *mh;
block *block_array;
FILE *fp;
nNode * nAry_tree = NULL;

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
    // FILE *fp;
    //  meta_header *mh;
    //  header *hdr;
    // block *block_array;

    // creates the fileSystem file
    fp=fopen(fullpath,"w+b");

    //allocates memory for the file system
    char *memory=(char*) malloc(size + sizeof(header) + sizeof(meta_header));

    //save the created memory to disk
    if(fwrite(memory,size,1,fp) != 1)
    {
        printf("createvfs_FAILURE\n");
        return 1;
    }
    fclose(fp);


    fp=fopen(fullpath,"r+b");

    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    //copy filesystem label with full path to the meta header field
    strcpy(mh->file_system_label, fullpath);

    mh->file_descriptors_used = 0;
    //mh->max_num_file_descriptors=1000000;
    //write meta header to the file
    fwrite(mh,sizeof(meta_header),1,fp);

    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    strcpy(hdr -> HEADER_TEST_FIELD, "TEST HEADER OK");

    //create_test_fd_data(hdr -> fd_array, size);

    //write header to the files
    fwrite(hdr,sizeof(header),1,fp);

    //allocate memory for block_array
    //block_array = calloc(MAX_NUM_OF_BLOCKS, sizeof(block));
    block_array = malloc(size);

    //write the block_array into disk
    fwrite(block_array,sizeof(MAX_NUM_OF_BLOCKS),1,fp);

    fclose(fp);

    printf("createvfs_SUCCESS\n");

    return(0);
}

int mount_vfs(char fullpath[150])
{
//   meta_header *mh = NULL;
    mh = read_meta_header(fullpath);

//    header *hdr = NULL;
    hdr = read_header(fullpath);

//    block* block_array = NULL;
    block_array = read_block_array(fullpath);

    file_descriptor *file_descriptor_list = hdr -> fd_array;
    long int file_descriptor_list_size = mh -> file_descriptors_used;

    /*
        Traverse all the file descriptors and create
        1) nAry Tree representing directory structure
        2) Hashtable storing all the file names without path (for search based on file name without path)
        3) Linkedlist storing list of the free blocks into which new files can be written
        4) BST storing all the file names with absolute path of file (for search based on absolute path of file)

        NEED CONCEPTUAL CLARITY IN IMPLEMENTATION OF FREE LIST AND SAVING OF FILES IN BLOCKS

        TODO
        1) modify all the node declarations in Linkedlist, Hashtable, nAry tree to accomodate a file descriptor
        2) Create test data for header and meta header info
        3) Test the creation of each data structure using the test data
    */

    //Create nAry Tree representing directory structure
    //nAry_tree = (nNode *) create_nAry_tree(file_descriptor_list, file_descriptor_list_size);

    //Create Hashtable storing all the file names without path (for search based on file name without path)
    struct node * hashtable[HASHSIZE];
    init_hashtable(hashtable);
    fill_hashtable(hashtable, file_descriptor_list, file_descriptor_list_size);

    //Linkedlist storing list of the free blocks into which new files can be written
    struct node *free_blocks_llist = NULL;
    //DOUBTFUL SHOULD GET FREE LIST
    free_blocks_llist = (struct node *) create_linkedlist(file_descriptor_list, file_descriptor_list_size);

    //BST storing all the file names with absolute path of file (for search based on absolute path of file)
    struct bst * bst_tree = NULL;
    bst_tree = create_bst(file_descriptor_list, file_descriptor_list_size);

//    printf("\nInorder traversal\n");
//    inorder_traversal(bst_tree, &displaybst);

    printf("mountvfs_SUCCESS\n");
    return 0;
}


int unmount_vfs(char  full_file_path_name[150])
{
    fp=fopen(full_file_path_name , "r+b");
    if(fwrite(mh,sizeof(meta_header),1,fp)!=1)
    {
        printf("not able to unmount meta_header");
        return 1;

    }
    //printf("successfully unmount meta_header");
    if(fwrite(hdr,sizeof(header),1,fp)!=1)
    {
        printf("unmountvfs_FAILURE\n");
        return 1;
    }
    //printf("successfully unmount header");
    if(fwrite(block_array,sizeof(BLOCK_SIZE * MAX_NUM_OF_BLOCKS),1,fp)!=1)
    {
        printf("unmountvfs_FAILURE\n");
        return 1;
    }

    printf("unmountvfs_SUCCESS\n");
    return 0;
}

void test_vfs(char fullpath[150])
{
    /*  FILE *fp;
      meta_header *mh;
      header *hdr;*/

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
    /*    FILE *fp;
        meta_header *mh;
    */
    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    fp = fopen(fullpath,"r+b");

    //read and copy the meta header to mh
    if(fread(mh, sizeof(meta_header), 1, fp) != 1)
    {
        printf("Failed to read meta header");
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return mh;
}

header * read_header(char fullpath[150])
{
    /*  FILE *fp;
      header *hdr;
    */
    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    fp = fopen(fullpath,"r+b");
    //Set the position indicator of file pointer to the header by offsetting sizeof(meta_header) bytes
    if(fseek(fp, sizeof(meta_header), SEEK_SET) != 0)
    {
        printf("\nFailed to read header");
        fclose(fp);
        return NULL;
    }

    //read and copy the header to hdr
    if(fread(hdr, sizeof(header), 1, fp) != 1)
    {
        printf("\nFailed to read header");
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return hdr;
}

block *read_block_array(char fullpath[150])
{
    /*  FILE *fp;
      block *block_array;
    */
    //allocate memory for header
    block_array = calloc(MAX_NUM_OF_BLOCKS, sizeof(block));

    fp = fopen(fullpath,"r+b");

    //Set the position indicator of file pointer to the end of header by offsetting sizeof(meta_header) + sizeof(header) bytes
    if(fseek(fp, (sizeof(meta_header) + sizeof(header)), SEEK_SET) != 0)
    {
        printf("\nFailed to read block array");
        fclose(fp);
        return NULL;
    }

    //read and copy the block_array to array
    if(fread(block_array, sizeof(MAX_NUM_OF_BLOCKS), 1, fp) != 1)
    {
        printf("\nFailed to read block_array");
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
    printf("\nHEADER_TEST_FIELD: %s", hdr -> HEADER_TEST_FIELD);
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

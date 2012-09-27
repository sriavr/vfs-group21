#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Filesystem.h"

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
}

int create_vfs(char fullpath[150], int file_length)
{
    FILE *fp;
    meta_header *mh;
    header *hdr;

    // creates the fileSystem file
    fp=fopen(fullpath,"w+b");

    //allocates memory for the file system
    char *memory=(char*) malloc(file_length);

    //save the created memory to disk
    if(fwrite(memory,file_length,1,fp) != 1)
    {
        printf("\nFatal error while creating VFS file system.\n");
        return 1;
    }
    fclose(fp);


    fp=fopen(fullpath,"r+b");

    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    //copy filesystem label with full path to the meta header field
    strcpy(mh->file_system_label, fullpath);
    mh->file_descriptors_used=0;
    mh->max_num_file_descriptors=1000000;
    //write meta header to the file
    fwrite(mh,sizeof(meta_header),1,fp);


    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    strcpy(hdr -> HEADER_TEST_FIELD, "TEST HEADER OK");
    //write header to the files
    fwrite(hdr,sizeof(header),1,fp);
    fclose(fp);

    return(0);
}

void test_vfs(char fullpath[150])
{
    FILE *fp;
    meta_header *mh;
    header *hdr;

    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    fp = fopen(fullpath,"r+b");
    //read and copy the meta header to mh
    if(fread(mh, sizeof(meta_header), 1, fp) != 1)
    {
        printf("Failed to read meta header");
        return;
    }

    print_meta_header_info(mh);

    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    //read and copy the header to hdr
    if(fread(hdr, sizeof(header), 1, fp) != 1)
    {
        printf("\nFailed to read header");
        return;
    }

}

meta_header * read_meta_header(char fullpath[150])
{
    FILE *fp;
    meta_header *mh;

    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    fp = fopen(fullpath,"r+b");

    //read and copy the meta header to mh
    if(fread(mh, sizeof(meta_header), 1, fp) != 1)
    {
        printf("Failed to read meta header");
        return NULL;
    }

    fclose(fp);
    return mh;
}

header * read_header(char fullpath[150])
{
    FILE *fp;
    header *hdr;

    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    fp = fopen(fullpath,"r+b");
    //Set the position indicator of file pointer to the header by offsetting sizeof(meta_header) bytes
    if(fseek(fp, sizeof(meta_header), SEEK_SET) != 0)
    {
        return NULL;
    }

    //read and copy the header to hdr
    if(fread(hdr, sizeof(header), 1, fp) != 1)
    {
        printf("\nFailed to read header");
        return NULL;
    }

    fclose(fp);
    return hdr;
}

void test_read_meta_header(char fullpath[150])
{
    meta_header * mh =  read_meta_header(fullpath);
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
    header * hdr = read_header(fullpath);
    if(hdr!=NULL)
    {
        print_header_info(hdr);
    }
    else
    {
        printf("\n read_header() function failed");
    }
}

void print_meta_header_info(meta_header * mh)
{
    printf("\ninformation in meta header:");
    printf("\nfile_system_label: %s", mh -> file_system_label);
    printf("\nmax_num_file_descriptors: %ld", mh -> max_num_file_descriptors);
    printf("\nfile_descriptors_used: %d", mh -> file_descriptors_used);
}

void print_header_info(header * hdr)
{
    printf("\ninformation in header:");
    printf("\nHEADER_TEST_FIELD: %s", hdr -> HEADER_TEST_FIELD);
}

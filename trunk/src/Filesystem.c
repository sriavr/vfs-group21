#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Filesystem.h"

void test_fsystem()
{
    char file_name[50];
    int file_length,ret=0;

    printf("Enter the file name with full path: ");
    scanf("%s",file_name);

    printf("Enter size of file in Kilo Bytes: ");
    scanf("%d",&file_length);

    //create a virtual file system
    ret=create_vfs(file_name,file_length);

    if(ret==0)
        printf("File system created");
}

int create_vfs(char file_name[50],int file_length)
{
    FILE *fp,*cpos;
    meta_header *mh;
    header *hdr;
    int pLen,fpLen,i=0,j=0;
    char fullpath[60],path[21]="/home/sridhar/Desktop/";//giving the path to where the file will be created

    mBsz mb ;
    mb.block_size=1024;

    //append file name to file path
    for(i=0; path[i]!='\0'; i++)
    {
        fullpath[i]=path[i];
        printf(" %c%d ",fullpath[i],i);
    }

    fullpath[i]='\0';
    printf("%d",i);
    printf("\nfile %s \n",fullpath);

    for(j=0; file_name[j]!='\0'; i++,j++)
    {
        fullpath[i]=file_name[j];
    }

    fpLen=i+1;
    fullpath[fpLen]='\0';
    printf("file %s \n",fullpath);

    // creates the fileSystem file
    fp=fopen(fullpath,"w+b");
    //allocates memory for the file system
    char *memory=(char*) malloc(file_length);
    //save the created memory to disk
    fwrite(memory,file_length,1,fp);
    fclose(fp);

    //allocate memory for meta header
    mh=(meta_header*) malloc(sizeof(meta_header));

    //copy filesystem label with full path to the meta header field
    for(i=0; fullpath[i]!='\0'; i++)
    {
        mh->file_system_label[i]=fullpath[i];
    }

    mh->file_system_label[i]='\0';
    printf("file %s \n",mh->file_system_label);
    mh->file_descriptors_used=0;
    mh->max_num_file_descriptors=1000000;

    fp=fopen(fullpath,"r+b");
    fwrite(mh,sizeof(mh),1,fp);

    cpos=ftell(fp);
    fclose(fp);

    //allocate memory for header
    hdr=(header*) malloc(sizeof(header));
    fp=fopen(fullpath,"r+b");
//	fp = fp + cpos;
    fwrite(hdr,sizeof(hdr),1,fp);
    fclose(fp);

    return(0);
}

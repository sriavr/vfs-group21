#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct fileDescriptor
{
	char fileName[50];
	char locationFullPath[50];
	char fileType[10];
	long int fileSize;
	int locationBlockNo;
}fDes;

typedef struct freeList
{
	int blockNo;
	struct freeList *nextFreeBlockNo;
}fLst;

typedef struct mainHeader{
	char fileSystemLabel[60];
//	struct fileDescriptors fd[20];
	long int maxNoOfFileDescriptors;
	int fileDescriptorsUsed;
//	struct freeList *fl;
}mHdr;

typedef struct header
{
	fDes desc[1000000];
	fLst list[500000];
}head;

typedef struct maxBlockSize
{
	int blockSize;
}mBsz;

int createFsystem(char *,int );

void testFsystem()
{
	char fileName[10];
	int fileLength,ret=0;
	printf("Enter the file name: ");
	scanf("%s",fileName);
	printf("Enter size of file in Kilo Bytes: ");
	scanf("%d",&fileLength);
	ret=createFsystem(fileName,fileLength);
	if(ret==0)
		printf("file created...");

}

int createFsystem(char fileName[10],int fileLength)
{
	FILE *fp,*cpos;
	mHdr *mh;
	head *hdr;
	int pLen,fpLen,i=0,j=0;
	char fullpath[60],path[21]="/home/pawan/Desktop/";//giving the path to where the file will be created

	mBsz mb ;
	mb.blockSize=1024;
	for(i=0;path[i]!='\0';i++)
	{
		fullpath[i]=path[i];
		printf(" %c%d ",fullpath[i],i);
	}
	//i=i+1;
	fullpath[i]='\0';
	printf("%d",i);
	printf("\nfile %s \n",fullpath);
	for(j=0;fileName[j]!='\0';i++,j++)
	{
		fullpath[i]=fileName[j];
		//printf("%c  ",fullpath[i]);
	}
	fpLen=i+1;
	fullpath[fpLen]='\0';
	printf("file %s \n",fullpath);
	//for(i=0;i<fpLen;i++)h[i]
	//	printf("%c",fullpath[i]);
	fp=fopen(fullpath,"w+b"); // creates the fileSystem file
	char *memory=(char*) malloc(fileLength);
	fwrite(memory,fileLength,1,fp); // allocates the size specified to the file
	fclose(fp);
	mh=(mHdr*) malloc(sizeof(mHdr));
	for(i=0;fullpath[i]!='\0';i++)
	{
		mh->fileSystemLabel[i]=fullpath[i];
		//fullpath[i]=fileName[j];
		//printf("%c  ",fullpath[i]);
       	}
	mh->fileSystemLabel[i]='\0';
	printf("file %s \n",mh->fileSystemLabel);
	mh->fileDescriptorsUsed=0;
	mh->maxNoOfFileDescriptors=1000000;
	fp=fopen(fullpath,"r+b");
	fwrite(mh,sizeof(mh),1,fp);
	cpos=ftell(fp);
	fclose(fp);
	hdr=(head*) malloc(sizeof(head));
	fp=fopen(fullpath,"r+b");
//	fp = fp + cpos;
	fwrite(hdr,sizeof(hdr),1,fp);
	fclose(fp);

	return(0);
}

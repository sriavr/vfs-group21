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

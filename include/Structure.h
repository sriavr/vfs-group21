struct filedescriptor{
char fileName[50];
char locationFullPath[50];

char fileType[20];
 unsigned long int fileSize;
int locationBlockNo;
};

struct mainHeader{

char fileSystemLabel[20];
struct fileDescriptors fd[20];
long int maxNoOfFileDescriptor;
long int fileDescriptorsUsed;
struct freeList fl;
};

struct freeList{
int blockNo;
struct freeList *nextFreeBlockNo;
};

struct  block{
long int fixedSize;

};





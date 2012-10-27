
#define MAX_LEVELS 20
#define MAX_LENGTH 10

/**
     1) Change char name[] to char *
     2) Add an additional field int value to nAryNode
     3) Write unit test cases adding 1000 random test nodes
**/

typedef struct nAryNode{
	struct nAryNode *child;
	struct nAryNode *sibling;
	char name[];
}nNode;

//nNode* createNode(char name[]);
nNode* createNode(char name[]);

int indexOf( char str[] , char searchChr , int startPos );

char * substring( char * str , int startIndex , int endIndex );

int splitPath(  char nPath[] , char nName[][MAX_LENGTH] );

char* splitstringPath(  char nPath[] );

nNode * searchForNodeInAllSiblings( nNode * t , char name[] );

nNode * insertAtEnd( nNode * t , char name[] );

nNode* insertNode( nNode * root , char nPath[] , char name[] );
//nNode* insertNode( nNode * root , file_descriptor filedescriptor );

void changeLevel( int level );

void print( char str[][MAX_LENGTH], int count );

void testSplit();



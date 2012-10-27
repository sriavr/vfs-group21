#define MAX_LEVELS 20
#define MAX_LENGTH 50

#define SUCCESS 0
#define FAILED 1

typedef struct nAryNode{
	struct nAryNode *child;
	struct nAryNode *sibling;
	file_descriptor filedescriptor;
}nNode;

void display_nary( nNode * root , int level );
nNode * find( nNode * root , char nPath[] );
nNode * removeLinkFromList( nNode * list , char * nodeName );

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



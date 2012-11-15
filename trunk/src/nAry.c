#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "../include/Filesystem.h"
#include "../include/Commons.h"
#include "../include/nAry.h"

#define MAX_LEVELS 20
#define MAX_LENGTH 50

#define SUCCESS 0
#define FAILED 1

void display_nary( nNode * root , int level );
nNode * find( nNode * root , char nPath[] );
nNode * removeLinkFromList( nNode * list , char * nodeName );
/*
* Creates a node and returns a pointer to it.
* name -  Name to be set as the node name.
* return - Returns a pointer to the created node.
*/
nNode* createNode(char name[]) {
	nNode *node=(nNode *)malloc(sizeof(nNode));

	if(node == NULL) {
	   fprintf(stderr,"Cannot allocate memory please free some amount of memory if possible");
	   return NULL;
	}

	strcpy( node->name, name );
        node->child = NULL;
	node->sibling = NULL;

	return node;
}

int indexOf( char str[] , char searchChr , int startPos ) {
    int length = strlen( str );
    int i = -1;
    for( i = startPos ; i < length ; i++ )
       if( str[i] == searchChr )
           return i;
    return -1;
}

char * substring( char * str , int startIndex , int endIndex ) {
    int length = endIndex - startIndex;
    char * copy;
    int index,k=0;
    if( length <= 0 )
         return NULL;
    copy = (char *)malloc(sizeof(char) * (length+1) );

    for( index = startIndex ; index < endIndex ; index++ ) {
          copy[k] = str[index];
          k++;
    }
    copy[k] = '\0';
    return copy;
}


/*
 Note: Path should start with /
 e.g. "/" or "/home"
*/
int splitPath(  char nPath[] , char nName[][MAX_LENGTH] ) {
     int startIndex = 0;
     int endIndex = -1;
     int length = strlen( nPath );
     int count = 0;
     do {
        endIndex = indexOf( nPath , '/' , startIndex + 1 );
        if( endIndex == -1 )
            endIndex = length;

        char * substr = substring( nPath, startIndex + 1 , endIndex );
        if( substr != NULL ) {
           strcpy( nName[count] , substr );
           count++;
	}

        startIndex = endIndex ;
     }while( endIndex != length );

     return count;
}

nNode * searchForNodeInAllSiblings( nNode * t , char name[] ) {

   if( t == NULL )
   	return NULL;

   while( t != NULL ) {
   	if( strcmp( t->name , name ) == 0 )
   		return t;
   	t = t->sibling;
   }
    return NULL;
}

nNode * insertAtEnd( nNode * t , char name[] ) {

   if( t == NULL ) {
   	t = createNode( name );
   	return t;
   }
//Could you please think on the integration of this module with our project?

   nNode * q = t; // save root pointer

   // child node exists
   while( t->sibling != NULL )  //move to last child.
  	   t = t->sibling;

   t->sibling = createNode( name );

   return q;
}

/*
*  Usecase 1 :-   root = insertNode( root , "/", "a" );    ---> nNames count = 0
*  Usecase 2 :-   root = insertNode( root , "/home" , "b" ); ---> nNames count = 1 i.e. "home"
*  Usecase 3 :-   root = insertNode( root , "/home/Desktop", "c" );  --> nNames count = 2 i.e. "home","Desktop"
*
*/
nNode* insertNode( nNode * root , char nPath[] , char name[] )
{
    int length = strlen(nPath);
    if(nPath[length - 1] == '/')
    {
        nPath[length - 1] = '\0';
    }

	nNode *ins;
	char nName[MAX_LEVELS][MAX_LENGTH];
	int count = splitPath( nPath, nName );
	int i = 0;
	nNode * t, * matchedNode = NULL;

	if( count != 0 && root == NULL ) {
	  	fprintf(stderr,"Invalid Path");
	  	return NULL;
	}

	// When root is null then create node as root.
	if( count == 0 && root == NULL ) {
		ins = createNode( name ); // expecting root node name is "/"
		return ins;
	}

	// Path is empty then node should be created under root.
	if( count == 0 && root != NULL ) {

	    	// should be last child under root.
	    	root->child = insertAtEnd( root->child , name );

	    	return root;
	}

	// Must be inserted in the given path.
	t = root;
	for( i = 0; i < count ; i++ ) {
	    // Identify the matching node in all the siblings
	    matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
	    if( matchedNode == NULL ) {
	        t->child = insertAtEnd( t->child , nName[i] );
	        matchedNode = searchForNodeInAllSiblings( t->child , nName[i] ); // efficient sol required.
	     }
	    t = matchedNode;
	}

	matchedNode->child = insertAtEnd( matchedNode->child , name );

	return root;

}

void changeLevel( int level ) {
  int i;
  for( i = 1; i <= level ; i++ )
     printf("         ");
}

/* Initial call
   display_nary( root , 1 );
 */
void display_nary( nNode * root , int level ) {

  nNode * t;

  if( root == NULL ) {
     return;
  }

  changeLevel( level );
  printf("%s \n", root->name );

  if( root->child != NULL ) { // condition not required.
    // for each child node
    for( t = root->child ; t != NULL ; t = t->sibling )
        display_nary( t , level + 1 );
  }
}

// Should come inside only when dest is not null.
// Return 0 : on success
//        1 : incase of failure.
int addChild(nNode * src, nNode * dest)
{
	if( dest == NULL || src == NULL ) {
	    return FAILED;
	}
	nNode * t , * q;
  	t = dest->child;
	if( t == NULL)
	{
		dest->child = src;
	}
	else
	{
		for( ; t != NULL ; t = t->sibling)
		        q = t;

		// q points to last sibling( in the child nodes )
		q->sibling = src;
	}
	return SUCCESS;
}

nNode * removeLink( nNode * root , char * srcPath ) {
	char nName[MAX_LEVELS][MAX_LENGTH];
	int count = splitPath( srcPath, nName );
	int i;
	nNode * t, * matchedNode = NULL;

	if( count <= 0 || root == NULL ) {
	  	fprintf(stderr,"Invalid Path");
	  	return root;
	}

	t = root;
	// search till one level up.
	for( i = 0; i < count - 1 ; i++ ) {
	    matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
	    if( matchedNode == NULL ) {
	    	fprintf( stderr, "Invalid path");
	    	return root;
	    }
	    t = matchedNode;
	}

	// t points to the parent node

	t->child = removeLinkFromList( t->child , nName[i] );

	return root;
}

nNode * removeLinkFromList( nNode * list , char * nodeName ) {

    if( list == NULL )
        return NULL;

    nNode *t, *p;

    t = list;
    while( t != NULL ) {

         if( strcmp( t->name, nodeName )  == 0 ) { // found

             if( t == list ) {  // first node
                 list = list->sibling;
             } else {
                 p->sibling = t->sibling ;
             }

             break;
         }

         p = t;
         t = t->sibling;
    }

    return list;
}


/*
E.g. :-
   srcDir = "/root/sub";
   destDir = "/root/sub1";

   Here entire directory sub must be copied to sub1 i.e. sub will form the child node of sub1.

   if( ! equals( srcPath , destPath ) { // Can not move a directory to itself.

	   nNode * src = find( root , srcPath );  // will give a pointer to sub
	   nNode * dest = find( root , destPath ); // will give a pointer to sub1

	   if( src != null && dest != null ) { // both src and dest exist.
	     addChild( dest , src );   // add src node to dest list of child nodes.
	     root = removeLink( root , srcDir );  // remove only link ( i.e. do not free memory )
	   }
   }

*/
nNode * moveDir(nNode * root ,char * src_path, char * dest_path)
{
    nNode * src, *dest;
    int retCode = FAILED;
    src = find( root, src_path );
    if ( src == NULL )
    {
        printf("Invalid Source Path");
        return root;
    }

    dest = find( root, dest_path );
    if ( dest == NULL )
    {
        printf("Invalid Destination Path");
        return root;
    }

    if( src != NULL && dest != NULL ) { // both src and dest exist.
	  retCode = addChild( src , dest );   // add src node to dest list of child nodes.
	  if( retCode == SUCCESS ) { // Only if successfully added
	     root = removeLink( root , src_path );  // remove only link ( i.e. do not free memory )
	     src->sibling = NULL; // remove link to next sibling
	  }
    }

    return root;
}

nNode * move_dir_nary(nNode * root, char * src_dir_path, char * dest_dir_path)
{
    return moveDir(root , src_dir_path, dest_dir_path);
}

nNode * move_file_nary(nNode * root, char * srcfile_with_dir_path, char * dest_dir_path)
{
    return moveDir(root , srcfile_with_dir_path, dest_dir_path);
}


nNode * find( nNode * root , char nPath[] )//, char name[] )
{
	char nName[MAX_LEVELS][MAX_LENGTH];
	int count = splitPath( nPath, nName );
	int i;
	nNode * t, * matchedNode = NULL;

	if( count != 0 && root == NULL ) {
	  	fprintf(stderr,"Invalid Path");
	  	return 0;
	}

	t = root;
	for( i = 0; i < count ; i++ ) {
	    matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
	    if( matchedNode == NULL ) {
	    	fprintf( stderr, "Invalid path");
	    	return NULL;
	    }
	    t = matchedNode;
	}

	return matchedNode;
}
int directory_exists(nNode * root, char * nPath)
{
	char nName[MAX_LEVELS][MAX_LENGTH];
	int count = splitPath( nPath, nName );
	int i;
	nNode * t, * matchedNode = NULL;

	if( count != 0 && root == NULL ) {
	  	fprintf(stderr,"Invalid Path");
	  	return 0;
	}

	t = root;
	for( i = 0; i < count ; i++ ) {
	    matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
	    if( matchedNode == NULL ) {
	    	fprintf( stderr, "Invalid path");
	    	return FAILED;
	    }
	    t = matchedNode;
	}

	return SUCCESS;
}

int file_exists(nNode * root, char * nPath)
{
	char nName[MAX_LEVELS][MAX_LENGTH];
	int count = splitPath( nPath, nName );
	int i;
	nNode * t, * matchedNode = NULL;

	if( count != 0 && root == NULL ) {
	  	fprintf(stderr,"Invalid Path");
	  	return 0;
	}

	t = root;
	for( i = 0; i < count ; i++ ) {
	    matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
	    if( matchedNode == NULL ) {
	    	fprintf( stderr, "Invalid path");
	    	return FAILED;
	    }
	    t = matchedNode;
	}

	return SUCCESS;
}
int freeNode( nNode * root, int level )
{
	nNode * t;

  if( root == NULL ) {
     return FAILED;
  }

  changeLevel( level );
  //printf("%s \n", root->name );


  if( root->child != NULL ) { // condition not required.
    // for each child node
    for( t = root->child ; t != NULL ; t = t->sibling )
        freeNode( t , level + 1 );
  }
  //printf("Freed node %s : \n", root->name);
  free(root);
  return SUCCESS;
}

nNode * deleteDir(nNode * root,char path[])
{
	nNode * delPathNode;
	int retCode;
	delPathNode = find( root,path );
	if ( delPathNode == NULL )
    	{
        	printf("Invalid Path");
        	return root;
    	}
    	if (delPathNode->child == NULL)
    	{
		root = removeLink( root , path );
		retCode = freeNode(delPathNode,0);
	}
	else
	{
		printf("Cannot delete node ");
	}
	//retCode = freeNode(delPathNode,0);
	if (retCode == FAILED)
	{
		fprintf(stderr,"ERROR IN FREEING OF NODES");
		return root;
	}
	return root;
}

nNode* delete_file_nary(nNode * root, char * node_path)
{
    return deleteDir(root, node_path);
}

nNode* delete_dir_nary(nNode * root, char * node_path)
{
    return deleteDir(root, node_path);
}

nNode* add_file_nary(nNode * root, char * filename , char * filepath)
{
	return insertNode( root , filepath , filename );
}
nNode* add_dir_nary(nNode * root, char * dirpath)
{
	char nName[MAX_LEVELS][MAX_LENGTH],dirname[MAX_LENGTH],*dirpath_insert;
	int count = splitPath(  dirpath , nName ),length,length_name,i;
	//printf("-------- %s",nName[count-1]);
	strcpy(dirname,nName[count-1]);
	length_name = strlen(nName[count-1]);
	length = strlen(dirpath);
	length = length - length_name;
	dirpath_insert = malloc(sizeof(char)*(length+1));
	for(i=0;i<length;i++)
	{
		dirpath_insert[i] = dirpath[i];
	}
	dirpath_insert[i] = '\0';
	//printf("--------> %s",dirpath_insert);
	root = insertNode( root , dirpath_insert , dirname );
	return root;
}

void print( char str[][MAX_LENGTH], int count ) {
   int i;
   printf(" Values \n" );
   for( i = 0 ; i < count ; i++ ) {
          printf("%s \n" , str[i] );
   }
}

void testSplit() {
   char path1[] = "/home/abc";
   char path2[] = "/";
   char path3[] = "";
   char path4[] = "/home/abc/xyz/";
   char path5[] = "/home//abc";

   char names[MAX_LEVELS][MAX_LENGTH];
   int count;

   count = splitPath( path1 , names );
   print( names , count );

   count = splitPath( path2 , names );
   print( names , count );

   count = splitPath( path3 , names );
   print( names , count );

   count = splitPath( path4 , names );
   print( names , count );

   count = splitPath( path5 , names );
   print( names , count );
}

void mainr(){
   //testSplit();
   nNode * root = NULL;
   root = insertNode(root,"","/");
   root = insertNode(root,"/","a");
   root = insertNode(root,"/","home");
   root = insertNode(root,"/home","b");
   root = insertNode(root,"/home","xyz");
   root = insertNode(root,"/home/xyz","doc");
   root = insertNode(root,"/","otherInRoot");
   root = insertNode(root,"/home/demo","test"); // expecting invalid path
   root = add_dir_nary(root,"/home/demo/Pavan");
   root = add_dir_nary(root,"/home/demo/Sridhar");
   root = add_file_nary(root,"yele","/home/demo/Pavan");
   root = deleteDir(root,"/home/demo/Pavan");
   printf("\n");
   display_nary( root , 1 );
}


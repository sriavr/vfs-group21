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
	nNode *ins;
	char nName[MAX_LEVELS][MAX_LENGTH];
	int count = splitPath( nPath, nName );
	int i,temp = 0;
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
	nNode *ins;
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

nNode * find( nNode * root , char nPath[] )//, char name[] )
{
	nNode *ins;
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

int freeNode( nNode * root, int level )
{
	nNode * t;

  if( root == NULL ) {
     return;
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
	root = removeLink( root , path );
	retCode = freeNode(delPathNode,0);
	if (retCode == FAILED)
	{
		fprintf(stderr,"ERROR IN FREEING OF NODES");
		return root;
	}
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

void test_main(){
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
   //root = insertNode(root,"/home/sdf/jkl/hjk","test1"); // expecting invalid path
   //root = insertNode(root,"/home/sdf/jkl/hjk/iop/mno","test2"); // expecting invalid path
   //  root = moveDir(root, "/home/xyz" , "/home/demo");
   //root = insertNode(root,"/home/klo/opl","poi");
   //   root = insertNode(root,"/home/klo/opl/iop/lop","poi");
  // root = insertNode(root,"/home/demo/tyu/123/098","test098"); // expecting invalid path
   root = insertNode(root,"/123/456/789/098","1011");
 // root = insertNode(root,"/home/demo/klp/oiu","1089");
  // root = insertNode(root,"/home/demo/kpop/ouu","1000");
   root = insertNode(root,"/123/456/987/890","1110");
   root = moveDir(root, "/123/456/789","/123/456/987");
   root = deleteDir(root,"/123/456/987");
   printf("\n");
   display_nary( root , 1 );
}

//returns all the sub-directories & files inside a specified directory
//in form of a linkedlist of file_descriptors (not recursive)
//file_descriptor *listall_nary(nNode * root, char * dir_path, int is_recursive)
/*
node_list listall_nary(nNode * root, char * dir_path, int is_recursive)
{
    nNode * dir,*temp;
    char dir_names[20][20];
    int count=0,i=0,length=0;
    dir = find( root, dir_path );
    if(is_recursive == 0)
    {
        temp = dir->child;
        while( temp->sibling != NULL )
        {
          //move to last child.
            count = count + 1;
            //printf("%s ",dir->name);
            strcpy(dir_names[count-1],temp->name);
            temp = temp->sibling;
        }
        node_list.dirnames = (char **) calloc(count, sizeof(char *));
        for(i = 0 ; i<count ;i++)
        {
            length = strlen(dir_names[i]);
            dirnames[i] = (char *) calloc(length, sizeof(char));for i = 1 to num_nodes
	    length = strlen(narynode -> path)
	    dirnames[i] = (char *) calloc(length, sizeof(char));
            strcpy(dirnames[i], narynode -> path);
            strcpy(node_list.dirnames[i], dir_names[i]);
        }
        node_list.size = count;
    }
    else if (is_recursive == 1)
    {
        temp = dir->child;
        while( temp->sibling != NULL )
        {
          //move to last child.
            count = count + 1;
            //printf("%s ",dir->name);
            strcpy(dir_names[count-1],temp->name)
            temp = temp->sibling;
        }
        node_list.dirnames = (char **) calloc(count, sizeof(char *));
        for(i = 0 ; i<count ;i++)
        {
            length = strlen(dir_names[i]);
            dirnames[i] = (char *) calloc(length, sizeof(char));
            strcpy(node_list.dirnames[i], dir_names[i]);
        }
        node_list.size = count;
    }
    return node_list;
}
*/

/* add a file_descriptor node to existing nary tree.
If root is null, create the root node. Check if the node currently added is dir or file.
If dir and parents don't exist, create filedescriptors for each of nonexistant parents */
//nNode* add_nary(nNode * root, file_descriptor filedescriptor)
nNode* add_file_nary(nNode * root, char * filename , char * filepath)
{
	return insertNode( root , filepath , filename );
}

//add_dir_nary(root, "/home/sridhar")
nNode* add_dir_nary(nNode * root, char * dirpath)
{
    nNode * temp;
    //temp = find(root,path);

	//return insertNode(root, dirpath , );
}


//check if node is file or dir, if dir, and it contains subdir or files,
//don't allow deletion and throw the error
nNode* delete_file_nary(nNode * root, char * node_path)
{
         root=deleteDir(root,node_path);
         return root;
}

nNode* delete_dir_nary(nNode * root, char * node_path)
{
	root=deleteDir(root,node_path);
	return root;
}

//move a directory from source to destination, all the contents of subtree should
//also be moved
nNode * move_dir_nary(nNode * root, char * src_dir_path, char * dest_dir_path)
{
	root=moveDir(root ,src_dir_path, dest_dir_path);
	return root;
}

nNode * move_file_nary(nNode * root, char * srcfile_with_dir_path, char * dest_dir_path)
{
	root=moveDir(root ,srcfile_with_dir_path, dest_dir_path);
	return root;
}

//print all the contents (dir, files) on console (in indented format)
nNode * displaynary(nNode * root)
{
    //printf("Filepath: %s\t Filename: %s\t Filetype: %s\t Block No: %d\n",
      //      root -> filedescriptor.location_full_path, root -> filedescriptor.file_name,
      //      root -> filedescriptor.file_type, root -> filedescriptor.location_block_num);
    display_nary(root,0);
}

//similar to traversal in BST
nNode * traverse_nary(nNode *root, void (*process_nary_node)(nNode * node))
{

}


//returns 0 if the directory doesn't exist, returns 1 if directory exists
int directory_exists(nNode * root, char * dir_path)
{

}

int file_exists(nNode * root, char * file_path)
{

}

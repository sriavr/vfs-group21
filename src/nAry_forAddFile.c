//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//#include "../include/nAry.h"
//
//void display_nary( nNode * root , int level );
//
///*
//* Creates a node and returns a pointer to it.
//* name -  Name to be set as the node name.
//* return - Returns a pointer to the created node.
//*/
///*nNode* createNode(char name[]) {
//	nNode *node=(nNode *)malloc(sizeof(nNode));
//
//	if(node == NULL) {
//	   fprintf(stderr,"Cannot allocate memory please free some amount of memory if possible");
//	   return NULL;
//	}
//
//	strcpy( node->name, name );
//        node->child = NULL;
//	node->sibling = NULL;
//
//	return node;
//}
//
//int indexOf( char str[] , char searchChr , int startPos ) {
//    int length = strlen( str );
//    int i = -1;
//    for( i = startPos ; i < length ; i++ )
//       if( str[i] == searchChr )
//           return i;
//    return -1;
//}
//
//char * substring( char * str , int startIndex , int endIndex ) {
//    int length = endIndex - startIndex;
//    char * copy;
//    int index,k=0;
//    if( length <= 0 )
//         return NULL;
//    copy = (char *)malloc(sizeof(char) * (length+1) );
//
//    for( index = startIndex ; index < endIndex ; index++ ) {
//          copy[k] = str[index];
//          k++;
//    }
//    copy[k] = '\0';
//    return copy;
//}
//
//
//
// Note: Path should start with /
// e.g. "/" or "/home"
//
//
//char* splitPath(  char nPath[] ) {
//     int startIndex = 0;
//     int endIndex = -1;
//     int length = strlen( nPath );
//     int count = 0;
//     do {
//        endIndex = indexOf( nPath , '/' , startIndex + 1 );
//        if( endIndex == -1 )
//            endIndex = length;
//
//        char * substr = substring( nPath, startIndex + 1 , endIndex );
//        if( substr != NULL ) {
//           strcpy( nName[count] , substr );
//           count++;
//	}
//
//        startIndex = endIndex ;
//     }while( endIndex != length );
//
//     return nName;
//}
//
//
//
//nNode * searchForNodeInAllSiblings( nNode * t , char name[] ) {
//
//   if( t == NULL )
//   	return NULL;
//
//   while( t != NULL ) {
//   	if( strcmp( t->name , name ) == 0 )
//   		return t;
//   	t = t->sibling;
//   }
//    return NULL;
//}
//
//nNode * insertAtEnd( nNode * t , char name[] ) {
//
//   if( t == NULL ) {
//   	t = createNode( name );
//   	return t;
//   }
//
//   nNode * q = t; // save root pointer
//
//   // child node exists
//   while( t->sibling != NULL )  //move to last child.
//  	   t = t->sibling;
//
//   t->sibling = createNode( name );
//
//   return q;
//}
//
//
//  Usecase 1 :-   root = insertNode( root , "/", "a" );    ---> nNames count = 0
//  Usecase 2 :-   root = insertNode( root , "/home" , "b" ); ---> nNames count = 1 i.e. "home"
//  Usecase 3 :-   root = insertNode( root , "/home/Desktop", "c" );  --> nNames count = 2 i.e. "home","Desktop"
//
//
//
//
//nNode* insertNode( nNode * root , char nPath[] , char name[] )
//{
//	nNode *ins;
//	char nName[MAX_LEVELS][MAX_LENGTH];
//	int count = splitPath( nPath, nName );
//	int i;
//	nNode * t, * matchedNode = NULL;
//
//	if( count != 0 && root == NULL ) {
//	  	fprintf(stderr,"Invalid Path");
//	  	return NULL;
//	}
//
//	// When root is null then create node as root.
//	if( count == 0 && root == NULL ) {
//		ins = createNode( name ); // expecting root node name is "/"
//		return ins;
//	}
//
//	// Path is empty then node should be created under root.
//	if( count == 0 && root != NULL ) {
//
//	    	// should be last child under root.
//	    	root->child = insertAtEnd( root->child , name );
//
//	    	return root;
//	}
//
//	// Must be inserted in the given path.
//	t = root;
//	for( i = 0; i < count ; i++ ) {
//	    // Identify the matching node in all the siblings
//	    matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
//	    if( matchedNode == NULL ) {
//	    	fprintf( stderr, "Invalid path");
//	    	return root;
//	    }
//	    t = matchedNode;
//	}
//
//	// condition check not required.
//	if( matchedNode != NULL ) {
//		matchedNode->child = insertAtEnd( matchedNode->child , name );
//	}
//
//	return root;
//
//}
//
//void changeLevel( int level ) {
//  int i;
//  for( i = 1; i <= level ; i++ )
//     printf("  ");
//}
//
// /*Initial call
//   display_nary( root , 1 );
//*/
///*
//void display_nary( nNode * root , int level ) {
//
//  nNode * t;
//
//  if( root == NULL ) {
//     return;
//  }
//
//  changeLevel( level );
//  printf("%s \n", root->name );
//
//  if( root->child != NULL ) { // condition not required.
//    // for each child node
//    for( t = root->child ; t != NULL ; t = t->sibling )
//        display_nary( t , level + 1 );
//  }
//}
//
//
//void print( char str[][MAX_LENGTH], int count ) {
//   int i;
//   printf(" Values \n" );
//   for( i = 0 ; i < count ; i++ ) {
//          printf("%s \n" , str[i] );
//   }
//}
//
///*void testSplit() {
//   char path1[] = "/home/abc";
//   char path2[] = "/";
//   char path3[] = "";
//   char path4[] = "/home/abc/xyz/";
//   char path5[] = "/home//abc";
//
//   char names[MAX_LEVELS][MAX_LENGTH];
//   int count;
//
//   count = splitPath( path1 , names );
//   print( names , count );
//
//   count = splitPath( path2 , names );
//   print( names , count );
//
//   count = splitPath( path3 , names );
//   print( names , count );
//
//   count = splitPath( path4 , names );
//   print( names , count );
//
//   count = splitPath( path5 , names );
//   print( names , count );
//}*/
///*
//void test_nary(){
//   //testSplit();
//   nNode * root = NULL;
//   root = insertNode(root,"","/");
//   root = insertNode(root,"/","a");
//   root = insertNode(root,"/","home");
//   root = insertNode(root,"/home","b");
//   root = insertNode(root,"/home","xyz");
//   root = insertNode(root,"/home/xyz","doc");
//   root = insertNode(root,"/","otherInRoot");
//   root = insertNode(root,"/home/demo","test"); // expecting invalid path
//   printf("\n");
//   display_nary( root , 1 );
//}*/
//

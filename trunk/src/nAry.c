#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "../include/Filesystem.h"
#include "../include/Commons.h"
#include "../include/Bst.h"
#include "../include/nAry.h"

#define MAX_LEVELS 20
#define MAX_LENGTH 50

#define SUCCESS 0
#define FAILED 1
extern bst   * bst_tree;
extern header *hdr;
void display_nary( nNode * root , int level );
nNode * find( nNode * root , char nPath[] );
nNode * removeLinkFromList( nNode * list , char * nodeName );
void update_fd_bst(bst* bst_node);
/*
* Creates a node and returns a pointer to it.
* name -  Name to be set as the node name.
* return - Returns a pointer to the created node.
*/
nNode* createNode(char name[])
{
    nNode *node=(nNode *)malloc(sizeof(nNode));

    if(node == NULL)
    {
        //fprintf(stderr,"Cannot allocate memory please free some amount of memory if possible");
        return NULL;
    }

    strcpy( node->name, name );
    //strcpy(node->fd->file_name,name);
    node->child = NULL;
    node->sibling = NULL;

    return node;
}

int indexOf( char str[] , char searchChr , int startPos )
{
    int length = strlen( str );
    int i = -1;
    for( i = startPos ; i < length ; i++ )
        if( str[i] == searchChr )
            return i;
    return -1;
}

char * substring( char * str , int startIndex , int endIndex )
{
    int length = endIndex - startIndex;
    char * copy;
    int index,k=0;
    if( length <= 0 )
        return NULL;
    copy = (char *)malloc(sizeof(char) * (length+1) );

    for( index = startIndex ; index < endIndex ; index++ )
    {
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
int splitPath(  char nPath[] , char nName[][MAX_LENGTH] )
{
    int startIndex = 0;
    int endIndex = -1;
    int length = strlen( nPath );
    int count = 0;
    do
    {
        endIndex = indexOf( nPath , '/' , startIndex + 1 );
        if( endIndex == -1 )
            endIndex = length;

        char * substr = substring( nPath, startIndex + 1 , endIndex );
        if( substr != NULL )
        {
            strcpy( nName[count] , substr );
            count++;
        }

        startIndex = endIndex ;
    }
    while( endIndex != length );

    return count;
}

nNode * searchForNodeInAllSiblings( nNode * t , char name[] )
{

    if( t == NULL )
        return NULL;

    while( t != NULL )
    {
        if( strcmp( t->name , name ) == 0 )
            return t;
        t = t->sibling;
    }
    return NULL;
}

nNode * insertAtEnd( nNode * t , char name[] )
{

    if( t == NULL )
    {
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
/*
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

    if( count != 0 && root == NULL )
    {
        //fprintf(stderr,"Invalid Path");
        return NULL;
    }

    // When root is null then create node as root.
    if( count == 0 && root == NULL )
    {
        ins = createNode( name ); // expecting root node name is "/"

        file_descriptor filedescriptor;
        filedescriptor.file_size = BLOCK_SIZE;
        strcpy(filedescriptor.file_type,"dir");
        strcpy(filedescriptor.location_full_path, "/");
        strcpy(filedescriptor.file_name, "maaroot");
        filedescriptor.location_block_num = 0;
        //add this newly created node to bst
        bst_tree = insert_bst(bst_tree, filedescriptor);
        //Point to the newly created filedescriptor
        ins -> fd = &filedescriptor;

        return ins;
    }

    // Path is empty then node should be created under root.
    if( count == 0 && root != NULL )
    {
        // should be last child under root.
        root->child = insertAtEnd( root->child , name );

        file_descriptor filedescriptor;
        filedescriptor.file_size = BLOCK_SIZE;
        strcpy(filedescriptor.file_type,"dir");
        if(nPath[length - 1] == '\0')
        {
            strcpy(filedescriptor.location_full_path, "/");
        }
        else
        {
            strcpy(filedescriptor.location_full_path, nPath);
            strcat(filedescriptor.location_full_path, "/");
        }

        strcpy(filedescriptor.file_name, name);
        filedescriptor.location_block_num = 0;
        //add this newly created node to bst
        bst_tree = insert_bst(bst_tree, filedescriptor);
        //Point to the newly created filedescriptor
        root->child -> fd = &filedescriptor;
        return root;
    }

    // Must be inserted in the given path.
    t = root;
    char path[FULLPATH_MAX_SIZE] = "/";
    file_descriptor filedescriptors[count];
    for( i = 0; i < count ; i++ )
    {
        // Identify the matching node in all the siblings
        matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );

        if( matchedNode == NULL )
        {
            t->child = insertAtEnd( t->child , nName[i] );
            filedescriptors[i].file_size = BLOCK_SIZE;
            strcpy(filedescriptors[i].file_type,"dir");
            strcpy(filedescriptors[i].location_full_path, path);
            strcpy(filedescriptors[i].file_name, nName[i]);
            filedescriptors[i].location_block_num = -3;
            //add this newly created node to bst
            bst_tree = insert_bst(bst_tree, filedescriptors[i]);
            //Point to the newly created filedescriptor
            t -> child -> fd = &filedescriptors[i];
            matchedNode = searchForNodeInAllSiblings( t->child , nName[i] ); // efficient sol required.
        }

        strcat(path,nName[i]);
        strcat(path, "/");

        t = matchedNode;
    }

    matchedNode->child = insertAtEnd( matchedNode->child , name );

    file_descriptor filedescriptor;
    filedescriptor.file_size = BLOCK_SIZE;
    strcpy(filedescriptor.file_type,"dir");
    strcpy(filedescriptor.location_full_path, path );
    //strcat(filedescriptor.location_full_path, "/");
    strcpy(filedescriptor.file_name, name);
    filedescriptor.location_block_num = 0;
    //add this newly created node to bst
    bst_tree = insert_bst(bst_tree, filedescriptor);
    //Point to the newly created filedescriptor
    matchedNode -> child -> fd = &filedescriptor;

    return root;

}
*/

//nNode* insertNode( nNode * root , char nPath[] , char name[] )
nNode* insertNode_filedesc(nNode * root , file_descriptor filedescriptor)
{
//    if(is_vfs_node(filedescriptor.location_full_path))
//    {
//        return NULL;
//    }

    char nPath[FULLPATH_MAX_SIZE];
    char name[FILENAME_MAX_SIZE];
    strcpy(nPath, filedescriptor.location_full_path);
    strcpy(name, filedescriptor.file_name);

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

    if( count != 0 && root == NULL )
    {
        //fprintf(stderr,"Invalid Path");
        return NULL;
    }

    // When root is null then create node as root.
    if( count == 0 && root == NULL )
    {
        ins = createNode( name ); // expecting root node name is "/"
        filedescriptor.file_size = BLOCK_SIZE;
        strcpy(filedescriptor.file_type,"dir");
        strcpy(filedescriptor.location_full_path, "/");
        strcpy(filedescriptor.file_name, "maaroot");
        filedescriptor.location_block_num = -1;
        //add this newly created node to bst
        bst_tree = insert_bst(bst_tree, filedescriptor);
        //Point to the newly created filedescriptor
        ins -> fd = &filedescriptor;
        return ins;
    }

    // Path is empty then node should be created under root.
    if( count == 0 && root != NULL )
    {
        // should be last child under root.
        root->child = insertAtEnd( root->child , name );

//        file_descriptor filedescriptor;
//        filedescriptor.file_size = 0;
//        strcpy(filedescriptor.file_type,"dir");
        if(nPath[length - 1] == '\0')
        {
            strcpy(filedescriptor.location_full_path, "/");
        }
        else
        {
            strcpy(filedescriptor.location_full_path, nPath);
            strcat(filedescriptor.location_full_path, "/");
        }
        //strcpy(filedescriptor.file_name, name);
        //filedescriptor.location_block_num = 0;
        //add this newly created node to bst
        bst_tree = insert_bst(bst_tree, filedescriptor);
        //Point to the newly created filedescriptor
        root -> child -> fd = &filedescriptor;
        return root;
    }

    // Must be inserted in the given path.
    t = root;
    char path[FULLPATH_MAX_SIZE] = "/";
    file_descriptor filedescriptors[count];
    for( i = 0; i < count ; i++ )
    {
        // Identify the matching node in all the siblings
        matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );

        if( matchedNode == NULL )
        {
            t->child = insertAtEnd( t->child , nName[i] );
            filedescriptors[i].file_size = BLOCK_SIZE;
            strcpy(filedescriptors[i].file_type,"dir");
            strcpy(filedescriptors[i].location_full_path, path);
            strcpy(filedescriptors[i].file_name, nName[i]);
            filedescriptors[i].location_block_num = -2;
            //add this newly created node to bst
            bst_tree = insert_bst(bst_tree, filedescriptors[i]);
            //Point to the newly created filedescriptor
            t -> child -> fd = &filedescriptors[i];
            matchedNode = searchForNodeInAllSiblings( t->child , nName[i] ); // efficient sol required.
        }

        strcat(path,nName[i]);
        strcat(path, "/");

        t = matchedNode;
    }

    matchedNode = searchForNodeInAllSiblings( t->child , name);

    t->child = insertAtEnd( t->child , name );
    //matchedNode->child = insertAtEnd( matchedNode->child , name );

    file_descriptor filedescriptor1;
    if(strcmp(filedescriptor.file_type, "dir") == 0)
    {
        filedescriptor1.file_size = BLOCK_SIZE;
    }
    else
    {
        filedescriptor1.file_size = filedescriptor.file_size;
    }

    strcpy(filedescriptor1.file_type, filedescriptor.file_type);
    strcpy(filedescriptor1.location_full_path, path );
    //strcat(filedescriptor.location_full_path, "/");
    strcpy(filedescriptor1.file_name, name);
    filedescriptor1.location_block_num = filedescriptor.location_block_num;
    //add this newly created node to bst
    bst_tree = insert_bst(bst_tree, filedescriptor1);
    //Point to the newly created filedescriptor
    t -> child -> fd = &filedescriptor1;

    return root;

}


nNode* insertNode( nNode * root , char nPath[] , char name[] )
{
    int nPath_len = strlen(nPath);

    file_descriptor filedescriptor;
    filedescriptor.file_size = BLOCK_SIZE;
    strcpy(filedescriptor.file_type,"dir");
    strcpy(filedescriptor.location_full_path, nPath );
    if(nPath[nPath_len - 1] != '/')
    {
        strcat(filedescriptor.location_full_path,"/");
    }
    strcpy(filedescriptor.file_name, name);
    filedescriptor.location_block_num = -1;

    return insertNode_filedesc(root, filedescriptor);
}


void changeLevel( int level, FILE * fp )
{
    int i;
    for( i = 1; i <= level ; i++ )
    {
        fprintf(fp,"  ");
        //printf("  ");
    }

}

void changeLevel_dis( int level )
{
    int i;
    for( i = 1; i <= level ; i++ )
    {
        //fprintf(fp,"  ");
        printf("  ");
    }

}

/* Initial call
   display_nary( root , 1 );
 */
void display_nary( nNode * root , int level )
{
    nNode * t;

    if( root == NULL )
    {
        return;
    }

    changeLevel_dis(level);//( level,fp );
    printf("%s \n", root->name );

    if( root->child != NULL )   // condition not required.
    {
        // for each child node
        for( t = root->child ; t != NULL ; t = t->sibling )
            display_nary( t , level + 1 );
    }
}

void listall_nary_child(nNode * root , int level , FILE * fp)
{
    nNode * t;

    if( root == NULL )
    {
        return;
    }
    if( root->child != NULL )   // condition not required.
    {
        t = root;
        fprintf(fp,"%s\n",t->name);
        for(t = t->child; t != NULL; t = t->sibling)
            fprintf(fp,"%s\t\t",t->name);
    }
}
void listall_nary_recur(nNode * root,int level, FILE * fp)
{
    nNode * t;

    if( root == NULL )
    {
        return;
    }

    changeLevel( level,fp );
    fprintf(fp,"%s \n", root->name );

    if( root->child != NULL )   // condition not required.
    {
        // for each child node
        for( t = root->child ; t != NULL ; t = t->sibling )
            listall_nary_recur( t , level + 1, fp );
    }
}

// Should come inside only when dest is not null.
// Return 0 : on success
//        1 : incase of failure.
int addChild(nNode * src, nNode * dest)
{
    if( dest == NULL || src == NULL )
    {
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

nNode * removeLink( nNode * root , char * srcPath )
{
    char nName[MAX_LEVELS][MAX_LENGTH];
    int count = splitPath( srcPath, nName );
    int i;
    nNode * t, * matchedNode = NULL;

    if( count <= 0 || root == NULL )
    {
        //fprintf(stderr,"Invalid Path");
        return root;
    }

    t = root;
    // search till one level up.
    for( i = 0; i < count - 1 ; i++ )
    {
        matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
        if( matchedNode == NULL )
        {
            //fprintf( stderr, "Invalid path");
            return root;
        }
        t = matchedNode;
    }

    // t points to the parent node

    t->child = removeLinkFromList( t->child , nName[i] );

    return root;
}

nNode * removeLinkFromList( nNode * list , char * nodeName )
{

    if( list == NULL )
        return NULL;

    nNode *t, *p;

    t = list;
    while( t != NULL )
    {

        if( strcmp( t->name, nodeName )  == 0 )   // found
        {

            if( t == list )    // first node
            {
                list = list->sibling;
            }
            else
            {
                p->sibling = t->sibling ;
            }

            break;
        }

        p = t;
        t = t->sibling;
    }

    return list;
}

char *dest_path_temp, *src_path_temp;
int length_src;
void change_path_fd(nNode * root, nNode * src, char src_path[], char * dest_path, int level)//,file_descriptor fd)
{
    dest_path_temp = dest_path;
    src_path_temp = src_path;
   // nNode *src_node,*t;
    //file_descriptor fd;
    //int count,i,length_dest;
    //char src_npath[30];
//    file_descriptor temp;
    //src = find(root,src_path);

    if( root == NULL  || src == NULL)
    {
        return;
    }
//    length_src = strlen(src_path);
//    length_dest = strlen(dest_path);
//    printf("%p fd->",hdr);
//    for(i=0; i<MAX_NUM_OF_BLOCKS; i++)
//    {
//        if(strncmp(src_path,  hdr->fd_array[i].location_full_path,length_src)==0)
//        {
//            strncpy(hdr->fd_array[i].location_full_path,dest_path,length_src);
//        }
//    }

    inorder_traversal(bst_tree, update_fd_bst);

//    changeLevel( level );
//    fd = search_bst_full(bst_tree,src_path);
//    temp = fd;
//    strcpy(fd.location_full_path,dest_path);
//    //strncmp(source,dest,n);
//    //{
//    //strncpy(source,destdest_path,n);
//    //fdescopy
//    insert_bst(bst_tree,fd);
//    //deletebst(bst_tree,temp);
//    //printf("%s \n", root->name );
//    strcpy(src_npath,src_path);
//
//    if( src->child != NULL )   // condition not required.
//    {
//        // for each child node
//        for( t = src->child ; t != NULL ; t = t->sibling )
//        {
//            src_node = find(root,src_path);
//            strcat(src_path,src_node->name);
//            strcat(dest_path,src_node->name);
//            change_path_fd( root, t , src_path, dest_path , level + 1 );
//        }
//
//    }

}

void update_fd_bst(bst *bst_node)
{
    if(strncmp(src_path_temp, bst_node -> filedescriptor.location_full_path, length_src)==0)
    {
        strncpy(bst_node -> filedescriptor.location_full_path, dest_path_temp, length_src);
    }
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
    char new_path[30],nName[20][50],new_node[10];
    int count = splitPath( src_path, nName );
    int retCode = FAILED;
    src = find( root, src_path );

    if ( src == NULL )
    {
        //printf("Invalid Source Path");
        return root;
    }

    dest = find( root, dest_path );
    if ( dest == NULL )
    {
        //printf("Invalid Destination Path");
        return root;
    }

    if( src != NULL && dest != NULL )   // both src and dest exist.
    {
        //src->fd = search_bst_full(bst_tree,src_path);
        retCode = addChild( src , dest );   // add src node to dest list of child nodes.
        change_path_fd(root,src,src_path,dest_path,count);//src->fd);
        if( retCode == SUCCESS )   // Only if successfully added
        {
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

    if( count != 0 && root == NULL )
    {
        //fprintf(stderr,"Invalid Path");
        return NULL;
    }

    t = root;
    if( strcmp(nPath, "/") == 0 )
    {
        matchedNode = searchForNodeInAllSiblings( t , nPath );
    }

    for( i = 0; i < count ; i++ )
    {
        matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
        if( matchedNode == NULL )
        {
            //fprintf( stderr, "Invalid path");
            return NULL;
        }
        t = matchedNode;
    }

    return matchedNode;
}

//returns 1 if node path exists in nary tree, else returns 0
int node_exists(nNode * root, char * nPath)
{
    char nName[MAX_LEVELS][MAX_LENGTH];
    int count = splitPath( nPath, nName );
    int i;
    nNode * t, * matchedNode = NULL;

    if( count != 0 && root == NULL )
    {
        //fprintf(stderr,"Invalid Path");
        return 0;
    }

    t = root;
    for( i = 0; i < count ; i++ )
    {
        matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
        if( matchedNode == NULL )
        {
            //fprintf( stderr, "Invalid path");
            return 0;
        }
        t = matchedNode;
    }

    return 1;
}


//file_exists and dir_exists
//int file_exists(nNode * root, char * nPath)
//{
//    char nName[MAX_LEVELS][MAX_LENGTH];
//    int count = splitPath( nPath, nName );
//    int i;
//    nNode * t, * matchedNode = NULL;
//
//    if( count != 0 && root == NULL )
//    {
//        fprintf(stderr,"Invalid Path");
//        return 0;
//    }
//
//    t = root;
//    for( i = 0; i < count ; i++ )
//    {
//        matchedNode = searchForNodeInAllSiblings( t->child , nName[i] );
//        if( matchedNode == NULL )
//        {
//            fprintf( stderr, "Invalid path");
//            return FAILED;
//        }
//        t = matchedNode;
//    }
//
//    return SUCCESS;
//}


int freeNode( nNode * root, int level )
{
    nNode * t;

    if( root == NULL )
    {
        return FAILED;
    }

//    changeLevel( level );
    //printf("%s \n", root->name );


    if( root->child != NULL )   // condition not required.
    {
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
        //printf("Invalid Path");
        return root;
    }
    if (delPathNode->child == NULL)
    {
        root = removeLink( root , path );
        retCode = freeNode(delPathNode,0);
    }
    else
    {
        ////printf("Cannot delete node ");
    }
    //retCode = freeNode(delPathNode,0);
    if (retCode == FAILED)
    {
        //f//printf(stderr,"ERROR IN FREEING OF NODES");
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

nNode* add_dir_nary(nNode * root, char * dir_path)
{
//    char nName[MAX_LEVELS][MAX_LENGTH],dirname[MAX_LENGTH],*dirpath_insert;
//    int count = splitPath(  dirpath , nName ),length,length_name,i;
//    //printf("-------- %s",nName[count-1]);
//    strcpy(dirname,nName[count-1]);
//    length_name = strlen(nName[count-1]);
//    length = strlen(dirpath);
//    length = length - length_name;
//    dirpath_insert = malloc(sizeof(char)*(length+1));
//    for(i=0; i<length; i++)
//    {
//        dirpath_insert[i] = dirpath[i];
//    }
//    dirpath_insert[i] = '\0';
//    //printf("--------> %s",dirpath_insert);
    char parent_path[FULLPATH_MAX_SIZE],dir_name[FILENAME_MAX_SIZE];
    split_name_path(dir_path, parent_path, dir_name);
    root = insertNode(root , parent_path , dir_name);
    return root;
}

void listall_nary(nNode * root, char * dir_path, int flag, FILE * fp)
{
    // printf("%s fd->",header.fd_array[3].location_full_path);
    root = find(root,dir_path);
    if (flag == 0)
        listall_nary_child(root,0,fp);
    else if (flag == 1)
        listall_nary_recur(root,1,fp);
}

void print( char str[][MAX_LENGTH], int count )
{
    int i;
    printf(" Values \n" );
    for( i = 0 ; i < count ; i++ )
    {
        printf("%s \n" , str[i] );
    }
}

void testSplit()
{
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

void mainr()
{
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
    //printf("\n");
    display_nary( root , 1 );
}

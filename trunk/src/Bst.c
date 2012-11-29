#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Commons.h"
#include "../include/Filesystem.h"
#include "../include/nAry.h"
#include "../include/Bst.h"

char * generate_key (bst * bst_node)
{
    int length = 0;
    int fullpath_length;
    int filename_length;
    char * key;
    file_descriptor filedescriptor;
    if(bst_node!=NULL)
    {
        filedescriptor = bst_node -> filedescriptor;
        fullpath_length = strlen(filedescriptor.location_full_path);
        filename_length = strlen(filedescriptor.file_name);
        length = fullpath_length + filename_length;
        key = calloc((length+1),sizeof(char));
        strcat(key, filedescriptor.location_full_path);
        strcat(key, filedescriptor.file_name);
        return key;
    }
    else
    {
        return NULL;
    }
}

bst * insert_bst(bst* bst_root, file_descriptor filedescriptor)
{
    bst *fresh=NULL, *temp=NULL;

    //create a new_node
    fresh = malloc(sizeof(bst));
    fresh -> right = NULL;
    fresh -> left = NULL;
    fresh -> is_deleted = 0;
    //int length = strlen(filedescriptor.location_full_path) + strlen(filedescriptor.file_name);
    //int length = 0;
    int fullpath_length = strlen(filedescriptor.location_full_path);
    //int filename_length = strlen(filedescriptor.file_name);

    //fresh -> key = calloc((length+2),sizeof(char));

    if(filedescriptor.location_full_path[fullpath_length - 1] == '/')
    {
//        length = fullpath_length + filename_length;
//        fresh -> key = calloc((length+1),sizeof(char));
//        strcat(fresh -> key, filedescriptor.location_full_path);
//        strcat(fresh -> key, filedescriptor.file_name);
    }
    else
    {
//        length = fullpath_length + filename_length;
//        fresh -> key = calloc((length+2),sizeof(char));
//        strcat(fresh -> key, filedescriptor.location_full_path);
//        strcat(fresh -> key, "/");
//        strcat(fresh -> key, filedescriptor.file_name);
        //CORRECT THE FILE DESCRIPTOR LOCATION
        strcat(filedescriptor.location_full_path, "/");
        //CORRECT THE FILE DESCRIPTOR LOCATION
    }
//    strcat(fresh -> key, filedescriptor.location_full_path);
//    strcat(fresh -> key, "/");
//    strcat(fresh -> key, filedescriptor.file_name);


    fresh -> filedescriptor = filedescriptor;

    if(bst_root == NULL)
    {
        bst_root = fresh;
    }
    else
    {
        temp = bst_root;

        while(1)
        {
            if(strcmp(generate_key(fresh), generate_key(temp)) < 0 )
            {
                if(temp -> left == NULL)
                {
                    temp -> left = fresh;
                    break;
                }
                else
                {
                    temp = temp -> left;
                }
            }
            else if(strcmp(generate_key(fresh), generate_key(temp)) > 0)
            {
                if(temp -> right == NULL)
                {
                    temp -> right = fresh;
                    break;
                }
                else
                {
                    temp = temp -> right;
                }
            }
            else if(strcmp(generate_key(fresh), generate_key(temp)) == 0)
            {
                //fprintf(stderr, "Duplicate key insertion is not allowed.");
                break;
            }
        }
    }

    return bst_root;
}

//Array last element is not getting displayed(corner case problem)
bst* search_bst_node(bst* bst_node, char* file_name,
                     char* location_full_path)
{
    int fullpath_length = strlen(location_full_path);
    int filename_length = strlen(file_name);
    int length = 0;
    char * key = NULL;
    if(location_full_path[fullpath_length - 1] == '/')
    {
        length = fullpath_length + filename_length;
        key = calloc((length+1),sizeof(char));
        strcat(key, location_full_path);
        strcat(key, file_name);
    }
    else
    {
        length = fullpath_length + filename_length;
        key = calloc((length+2),sizeof(char));
        strcat(key, location_full_path);
        strcat(key, "/");
        strcat(key, file_name);
    }

    while(1)
    {
        if(strcmp(generate_key(bst_node), key) > 0)
        {
            if(bst_node -> left == NULL)
            {
                return NULL ;
            }
            else
            {
                bst_node = bst_node -> left;
            }
        }
        else if(strcmp(generate_key(bst_node), key) < 0)
        {
            if(bst_node -> right == NULL)
            {
                return NULL;
            }
            else
            {
                bst_node = bst_node-> right;
            }
        }
        else if ((strcmp(generate_key(bst_node), key) ==  0) &&
                 (bst_node -> is_deleted != 1))
        {
            return bst_node;
        }
        else
        {
            return NULL;
        }
    }
}

//Array last element is not getting displayed(corner case problem)
file_descriptor search_bst(bst* bst_node, char* file_name,
                           char* location_full_path)
{
    file_descriptor file;
    strcpy(file.location_full_path ,"0");
    strcpy(file.file_type ,"0");
    file.file_size =0;
    strcpy(file.file_name ,"0");
    file.location_block_num =0;

    bst * matched_node = search_bst_node(bst_node, file_name, location_full_path);

    if(matched_node == NULL)
    {
        return file;
    }
    else
    {
        return matched_node -> filedescriptor;
    }
}

file_descriptor search_bst_full(bst* bst_node,
                                char* filename_with_full_path)
{
//    char nName[MAX_LEVELS][MAX_LENGTH],
//    dirname[MAX_LENGTH],
//    *dirpath_insert;
//    int count = splitPath(filename_with_full_path, nName),
//                length,
//                length_name,
//                i;
//    strcpy(dirname,nName[count-1]);
//    length_name = strlen(nName[count-1]);
//    length = strlen(filename_with_full_path);
//    length = length - length_name;
//    dirpath_insert = malloc(sizeof(char)*(length+1));
//    for(i=0; i<length; i++)
//    {
//        dirpath_insert[i] = filename_with_full_path[i];
//    }
//    dirpath_insert[i] = '\0';
    //printf("dirname:%s, dirpath_insert:%s",dirname, dirpath_insert);
    char parent_path[FULLPATH_MAX_SIZE],name[FILENAME_MAX_SIZE];
    split_name_path(filename_with_full_path, parent_path, name);
    if(strcmp(filename_with_full_path, "/") == 0)
    {
        strcpy(name, "maaroot");
        strcpy(parent_path, "/");
    }
    file_descriptor fd = search_bst(bst_node, name, parent_path);
    return fd;
}

bst * search_bst_full_node(bst* bst_node,
                           char* filename_with_full_path)
{
//    char nName[MAX_LEVELS][MAX_LENGTH],
//    dirname[MAX_LENGTH],
//    *dirpath_insert;
//    int count = splitPath(filename_with_full_path, nName),
//                length,
//                length_name,
//                i;
//    strcpy(dirname,nName[count-1]);
//    length_name = strlen(nName[count-1]);
//    length = strlen(filename_with_full_path);
//    length = length - length_name;
//    dirpath_insert = malloc(sizeof(char)*(length+1));
//    for(i=0; i<length; i++)
//    {
//        dirpath_insert[i] = filename_with_full_path[i];
//    }
//    dirpath_insert[i] = '\0';
    //printf("dirname:%s, dirpath_insert:%s",dirname, dirpath_insert);

    char parent_path[FULLPATH_MAX_SIZE],name[FILENAME_MAX_SIZE];
    split_name_path(filename_with_full_path, parent_path, name);
    bst * matched_node = search_bst_node(bst_node, name, parent_path);
    return matched_node;
}


void inorder_traversal(bst* bst_node,
                       void (*process_node)(bst* bst_node))
{
    if (bst_node == NULL)
    {
        return;
    }
    inorder_traversal( bst_node -> left, process_node);
    process_node(bst_node);
    inorder_traversal( bst_node -> right, process_node );
}

void preorder_traversal(bst* bst_node,
                        void (*process_node)(bst* bst_node))
{
    if (bst_node == NULL)
    {
        return;
    }
    process_node(bst_node);
    preorder_traversal( bst_node -> left, process_node);
    preorder_traversal( bst_node -> right, process_node );
}

bst* postorder_traversal(bst* bst_node)
{
    if (bst_node == NULL)
    {
        return NULL;
    }

    postorder_traversal( bst_node -> left );
    postorder_traversal( bst_node -> right);
    //process_node(bst_node);
    return bst_node;
}

void displaybst(bst *bst_node)
{
    if(bst_node -> is_deleted != 1)
    {
        printf("Key: %s\t Filetype: %s\t File size: %ld\t  Filename:%s\t Filepath:%s\n", generate_key(bst_node),
               bst_node -> filedescriptor.file_type,
               bst_node -> filedescriptor.file_size,
               bst_node -> filedescriptor.file_name,
               bst_node -> filedescriptor.location_full_path);
    }
}

int delete_bst (bst * bst_tree, char * node_path)
{
    if((bst_tree==NULL))
    {
        //printf("BST IS EMPTY");
        return 1;
    }
    else
    {
        bst * matched_node = NULL;
        matched_node = search_bst_full_node(bst_tree, node_path);
        if(matched_node == NULL)
        {
            return 1;
        }
        else
        {
            matched_node -> is_deleted = 1;
        }
    }
    return 0;
}
//int delete_bst(bst *bst_node, const char * node_path)
//{
//    bst *parent_node = NULL;
//    int length = 0;
//    char * key = NULL;
//    int node_path_length = strlen(node_path);
//
//    //remove trailing /
//    if(node_path[node_path_length - 1] == '/')
//    {
//        node_path[node_path_length - 1] == '\0';
//    }
//
//    node_path_length = strlen(node_path);
//    key = calloc(node_path_length, sizeof(char));
//    strcpy(key, node_path);
//
//    while(1)
//    {
//        if(strcmp(bst_node -> key, key) > 0)
//        {
//            if(bst_node -> left == NULL)
//            {
//                return 1;
//            }
//            else
//            {
//                parent_node = bst_node;
//                bst_node = bst_node -> left;
//            }
//        }
//        else if(strcmp(bst_node -> key, key) < 0)
//        {
//            if(bst_node -> right == NULL)
//            {
//                return 1;
//            }
//            else
//            {
//                parent_node = bst_node;
//                bst_node = bst_node-> right;
//            }
//        }
//        else
//        {
//            if((bst_node -> left == NULL) && (bst_node -> right == NULL))
//            {
//                free(bst_node);
//            }
//            else if ((bst_node -> left != NULL) && (bst_node -> right == NULL))
//            {
//                if(parent_node -> left == bst_node)
//                {
//                    parent_node -> left = bst_node -> left;
//                    free(bst_node);
//                }
//                else (parent_node -> right == bst_node)
//                {
//                    parent_node -> right = bst_node -> left;
//                    free(bst_node);
//                }
//                else
//                {
//                    return 1;
//                }
//            }
//            else if((bst_node -> left == NULL) && (bst_node -> right != NULL))
//            {
//                if(parent_node -> left == bst_node)
//                {
//                    parent_node -> left = bst_node -> right;
//                    free(bst_node);
//                }
//                else (parent_node -> right == bst_node)
//                {
//                    parent_node -> right = bst_node -> right;
//                    free(bst_node);
//                }
//                else
//                {
//                    return 1;
//                }
//            }
//            else if((bst_node -> left != NULL) && (bst_node -> right != NULL))
//            {
//
//
//            }
//            else
//            {
//                return 1;
//            }
//
//            return bst_node;
//        }
//    }

//    if((bst_tree==NULL))
//    {
//        //printf("BST IS EMPTY");
//        return 1;
//    }
//    else
//    {
//        bst * matched_node = NULL;
//        matched_node = search_bst_full_node(bst_tree, node_path);
//        if(matched_node == NULL)
//        {
//            return 1;
//        }
//        else{
//            free(matched_node);
//        }
//    }
//    return 0;
//}

//void delete_bst(bst *bst_node , file_descriptor filedescriptor ,bst *position )
//{           //here bst_node is the parent of node to be deleted
//            // n position is the left/right pointer of node to be deleted
//
//            bst * child ,*temp;
//            if(child->left == NULL && child->right == NULL)
//            {
//                free(child);
//                position=NULL;
//            }
//            else if(child->left !=NULL && child->right == NULL)
//            {
//                    position =child->left;
//                    free(child);
//
//            }
//            else if(child->right !=NULL && child->left == NULL)
//            {
//                    position =child->right;
//                    free(child);
//
//            }
//            else
//            {
//
//                child = postorder_traversal(position);
//                temp=position;
//                position = child;
//                child = temp->left;
//                free(temp);
//            }
//}

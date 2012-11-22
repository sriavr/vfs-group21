#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Filesystem.h"
#include "../include/Commons.h"
#include "../include/Bst.h"
#include "../include/nAry.h"
export bst * bst_tree;
extern header *hdr;

bst * insert_bst(bst* bst_root, file_descriptor filedescriptor)
{
    bst *fresh=NULL, *temp=NULL;

    //create a new_node
    fresh = malloc(sizeof(bst));
    fresh -> right = NULL;
    fresh -> left = NULL;
    int length = strlen(filedescriptor.location_full_path) + strlen(filedescriptor.file_name);
    fresh -> key = calloc((length+2),sizeof(char));
    strcat(fresh -> key, filedescriptor.location_full_path);
    strcat(fresh -> key, "/");
    strcat(fresh -> key, filedescriptor.file_name);
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
            if(strcmp(fresh -> key, temp -> key) < 0)
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
            else if(strcmp(fresh -> key, temp -> key) > 0)
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
            else if(strcmp(fresh -> key, temp -> key) == 0)
            {
                //fprintf(stderr, "Duplicate key insertion is not allowed.");
                break;
            }
        }
    }

    return bst_root;
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
        if(strcmp(bst_node -> key, key) > 0)
        {
            if(bst_node -> left == NULL)
            {
                return file ;
            }
            else
            {
                bst_node = bst_node -> left;
            }
        }
        else if(strcmp(bst_node -> key, key) < 0)
        {
            if(bst_node -> right == NULL)
            {
                return file;
            }
            else
            {
                bst_node = bst_node-> right;
            }
        }
        else
        {
            return bst_node -> filedescriptor;
        }
    }
}


bst *search_bst(bst* bst_node, char* file_name,
                           char* location_full_path)
{
    file_descriptor file;
    strcpy(file.location_full_path ,"0");
    strcpy(file.file_type ,"0");
    file.file_size =0;
    strcpy(file.file_name ,"0");
    file.location_block_num =0;
    int fullpath_length = strlen(location_full_path);
    int filename_length = strlen(file_name);
    int length = 0;
    char * key = NULL;
    bst * temp_bst=NULL;
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
    bst *left , *right;
    temp_bst = NULL;
    while(1)
    {
        if(strcmp(bst_node -> key, key) > 0)
        {
            if(bst_node -> left == NULL)
            {
                return bst_node ->left;
            }
            else
            {
                temp_bst =bst_node;
                bst_node = bst_node -> left;
            }
        }
        else if(strcmp(bst_node -> key, key) < 0)
        {
            if(bst_node -> right == NULL)
            {
                return bst_node->right;
            }
            else
            {
                temp_bst =bst_node;
                bst_node = bst_node-> right;
            }
        }
        else
        {
            return temp_bst;
        }
    }
}

int search_bst(bst* bst_node, char* file_name,
                           char* location_full_path)
{
    int left =0;
    int right=1;
    file_descriptor file;
    strcpy(file.location_full_path ,"0");
    strcpy(file.file_type ,"0");
    file.file_size =0;
    strcpy(file.file_name ,"0");
    file.location_block_num =0;
    int fullpath_length = strlen(location_full_path);
    int filename_length = strlen(file_name);
    int length = 0;
    char * key = NULL;
    bst * temp_bst=NULL;
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

    temp_bst = NULL;
    while(1)
    {
        if(strcmp(bst_node -> key, key) > 0)
        {
            if(bst_node -> left == NULL)
            {
                return left;
            }
            else
            {
                temp_bst =bst_node;
                bst_node = bst_node -> left;
            }
        }
        else if(strcmp(bst_node -> key, key) < 0)
        {
            if(bst_node -> right == NULL)
            {
                return right;
            }
            else
            {
                temp_bst =bst_node;
                bst_node = bst_node-> right;
            }
        }

    }
}




























file_descriptor search_bst_full(bst* bst_node,
                                char* filename_with_full_path)
{
    char nName[MAX_LEVELS][MAX_LENGTH],
    dirname[MAX_LENGTH],
    *dirpath_insert;
    int count = splitPath(filename_with_full_path, nName),
                length,
                length_name,
                i;
    strcpy(dirname,nName[count-1]);
    length_name = strlen(nName[count-1]);
    length = strlen(filename_with_full_path);
    length = length - length_name;
    dirpath_insert = malloc(sizeof(char)*(length+1));
    for(i=0; i<length; i++)
    {
        dirpath_insert[i] = filename_with_full_path[i];
    }
    dirpath_insert[i] = '\0';
    //printf("dirname:%s, dirpath_insert:%s",dirname, dirpath_insert);
    file_descriptor fd = search_bst(bst_node, dirname, dirpath_insert);
    return fd;
}


void inorder_traversal(bst* bst_node,
                       void (*process_node)(bst* bst_node))
{
    if (bst_node == NULL)
    {
        return 0;
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
    printf("Key: %s\t Filetype: %s\t Block No: %d\n", bst_node -> key, bst_node -> filedescriptor.file_type, bst_node -> filedescriptor.location_block_num);

}


void delete_bst(bst *bst_tree, char * node_path)
{

   char nName[][MAX_LENGTH];
   file_descriptor filedescriptor;
    char * file_name;
   if((bst_tree==NULL))
   {
       printf("BST IS EMPTY");
   }
   else
   {
//       for(i=0;i< MAX_UM_OF_BLOCKS;i++)
//        {
//            if(strcmp(node_path , hdr->fd_array[i].location_full_path) ==0)
//               {
//
//                   filedescriptor =fd_array[i];
//                }
//        }
        int position =0;
        file_name = splitPath(node_path,nName[][MAX_LENGTH]);

        //search_bst_full(bst_node,filename_with_full_path);
        filedescriptor=search_bst(bst_tree,file_name,node_path);
        temp_tree = search_bst(bst_node,file_name,location_full_path);
        strcpy(bst_tree.key , node_path);
        position = search_bst(bst_node,file_name,location_full_path);

        if(bst_tree->left ==NULl && bst_tree->right ==NULL)
        {

             if(position ==0)
             {

                temp_tree->left =NULL;
                delete bst_tree;

             }
             else if(position ==1)
             {

                temp_tree->right =NULL;
                delete bst_tree;

             }
        }else if(bst_tree ->left ==NULL && bst_tree->right !=NULL)
        {

          if(position ==0)
             {

                temp_tree->left = bst_tree->right;
                delete bst_tree;

             }
             else if(position ==1)
             {

                temp_tree->right =bst_tree->right;
                delete bst_tree;

             }
        }else if(bst_tree ->left!=NULL && bst_tree->right==NULL)
        {

          if(position ==0)
             {

                temp_tree->left = bst_tree->left;
                delete bst_tree;

             }
             else if(position ==1)
             {

                temp_tree->right =bst_tree->left;
                delete bst_tree;

             }
        }
        else //how to implement inorder in bst
        {
            if(position ==0)
             {
                inorder_traversal(bst_tree,
                       void (*process_node)(bst* bst_node))
                temp_tree->left = bst_tree->left;
                delete bst_tree;

             }
             else if(position ==1)
             {

                temp_tree->right =bst_tree->left;
                delete bst_tree;

             }
        }
    }

}



/*void delete_bst(bst *bst_node , file_descriptor filedescriptor)
{

      if(value < this->value) {

            if (left != NULL)

                  return left->remove(value, this);

            else

                  return NULL;

      } else if (value > this->value) {

            if (right != NULL)

                  return right->remove(value, this);

            else

                  return NULL;

      } else {

            if (left != NULL && right != NULL) {

                  this->value = right->minValue();

                  return right->remove(this->value, this);

            } else if (parent->left == this) {

                  parent->left = (left != NULL) ? left : right;

                  return this;

            } else if (parent->right == this) {

                  parent->right = (left != NULL) ? left : right;

                  return this;

            }

      }

}



int BSTNode::minValue() {

      if (left == NULL)

            return value;

      else

            return left->minValue();

}
*/

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

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Filesystem.h"
#include "../include/Commons.h"
#include "../include/Bst.h"
#include "../include/nary_tree.h"

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

    int length = strlen(location_full_path)
                 + strlen(file_name);
    char * key = calloc((length+2),sizeof(char));
    strcat(key, location_full_path);
    strcat(key, "/");
    strcat(key, file_name);

    while(1)
    {
        if(strcmp(bst_node -> key, key) < 0)
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
        else if(strcmp(bst_node -> key, key) > 0)
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

file_descriptor search_bst_full(bst* bst_node,
                                char* filename_with_full_path)
{
//    char *temp = NULL, *file_name = NULL;
//    do {
//        file_name = temp;
//        temp = strtok(filename_with_full_path, "/");
//    } while (temp!=NULL);
//
//    char * ptr = strstr(filename_with_full_path, file_name);
//    ptr = ptr - 2;


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
    printf("Key: %s\t Filetype: %s\t Block No: %d\n", bst_node -> key, bst_node -> filedescriptor.file_type, bst_node -> filedescriptor.location_block_num);
}

//void delete_bst(bst *bst_node, char * node_path)
//{
//    //here bst_node is the parent of node to be deleted
//    // n position is the left/right pointer of node to be deleted
//
//    bst * child,*temp;
//    if(child->left == NULL && child->right == NULL)
//    {
//        free(child);
//        position=NULL;
//    }
//    else if(child->left !=NULL && child->right == NULL)
//    {
//        position =child->left;
//        free(child);
//
//    }
//    else if(child->right !=NULL && child->left == NULL)
//    {
//        position =child->right;
//        free(child);
//
//    }
//    else
//    {
//
//        child = postorder_traversal(position);
//        temp=position;
//        position = child;
//        child = temp->left;
//        free(temp);
//    }
//}

void test_simple_bst()
{
    char *a[2]= {"file" ,"dir"};
    char temp_string[5];
    bst *start=NULL;
    //int i=0 , j=0;
    file_descriptor arr , output;


    //for(i=0; i<10; i++)
    //{
    strcpy(arr.file_name,"pinnacle" );
    strcpy(arr.location_full_path, "/home/desktop");
    strcpy(temp_string, a[rand()%2]);
    strcpy(arr.file_type, temp_string);
    arr.file_size =rand();
    arr.location_block_num=rand();
    //}

    //for(j=0; j<10; j++)
    start = insert_bst(start, arr);
    if(start!=NULL)
    {
        printf("sucessfull  inserted");
    }
    else
    {
        printf(" UNsuccessful inserted");
    }

    displaybst(start);
    inorder_traversal(start, displaybst);
    output= search_bst(start, arr.location_full_path, arr.file_name);
    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);
}

/*
void test_complex_bst()
{
    bst * tree = NULL;
    tree = init_bst(tree, "ROOT", 100);
    char * random_str;
    int i;
    for(i =0; i<10000; i++)
    {
        random_str = (char *) generate_rand_string();
        insert_bst(tree, random_str, rand()%100);
        free(random_str);
    }

    printf("\nInorder traversal\n");
    inorder_traversal(tree, &displaybst);

    printf("\nPreorder traversal\n");
    preorder_traversal(tree, &displaybst);

    printf("\nPostorder traversal\n");
    postorder_traversal(tree, &displaybst);

}
*/


/*int main()
{
    test_simple_bst();
    //test_complex_bst();
    return 0;
}*/

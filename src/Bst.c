#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Filesystem.h"
#include "../include/Commons.h"
#include "../include/Bst.h"

/*
struct bst* init_bst(struct bst* bst_root, file_descriptor filedescriptor)
{
    bst_root = malloc(sizeof(struct bst));
    if(bst_root == NULL)
    {
        return NULL;
    }

    bst_root -> right = NULL;
    bst_root -> left = NULL;

    // /root/home/sridhar + '/' + abc.dat + '\0'
    int length = strlen(filedescriptor.location_full_path) + strlen(filedescriptor.file_name);
    bst_root -> key = calloc((length+2),sizeof(char));
    strcat(bst_root -> key, filedescriptor.location_full_path);
    strcat(bst_root -> key, "/");
    strcat(bst_root -> key, filedescriptor.file_name);

    bst_root -> filedescriptor = filedescriptor;                      //reqirement of this???????????????/

    return bst_root;
}*/

struct bst * insert_bst(struct bst* bst_root, file_descriptor filedescriptor)
{
    struct bst *fresh=NULL, *temp=NULL;

    //create a new_node
    fresh = malloc(sizeof(struct bst));
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
file_descriptor search_bst(struct bst* bst_node, char* file_name)
{
    file_descriptor file;
    strcpy(file.location_full_path ,"0");
    strcpy(file.file_type ,"0");
    file.file_size =0;
    strcpy(file.file_name ,"0");
    file.location_block_num =0;

    while(1)
    {
        if(strcmp(bst_node -> filedescriptor.file_name, file_name) < 0)
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
        else if(strcmp(bst_node -> filedescriptor.file_name, file_name) > 0)
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

    /*if(bst_node ==NULL)
    return file;
    else if(strcmp(bst_node->filedescriptor .file_name , file_name)==0)
    return bst_node ->filedescriptor;
    else if(strcmp(bst_node->filedescriptor .file_name , file_name) < 0)
    return search_bst(bst_node ->left , file_name);
    else
    return search_bst(bst_node ->right , file_name);
    */
}

void inorder_traversal(struct bst* bst_node,
                       void (*process_node)(struct bst* bst_node))
{
    if (bst_node == NULL)
    {
        return;
    }
    inorder_traversal( bst_node -> left, process_node);
    process_node(bst_node);
    inorder_traversal( bst_node -> right, process_node );
}

void preorder_traversal(struct bst* bst_node,
                        void (*process_node)(struct bst* bst_node))
{
    if (bst_node == NULL)
    {
        return;
    }
    process_node(bst_node);
    preorder_traversal( bst_node -> left, process_node);
    preorder_traversal( bst_node -> right, process_node );
}

void postorder_traversal(struct bst* bst_node,
                         void (*process_node)(struct bst* bst_node))
{
    if (bst_node == NULL)
    {
        return;
    }

    postorder_traversal( bst_node -> left, process_node);
    postorder_traversal( bst_node -> right, process_node );
    process_node(bst_node);
}

void displaybst(struct bst *bst_node)
{
    printf("Key: %s\t Filetype: %s\t Block No: %d\n", bst_node -> key, bst_node -> filedescriptor.file_type, bst_node -> filedescriptor.location_block_num);
}

void test_simple_bst()
{
    char *a[2]= {"file" ,"dir"};
    char temp_string[5], string_full_path[30];
    struct bst *start=NULL;
    int i=0 , j=0;
    file_descriptor arr[10] , output;

    for(i=0; i<10; i++)
    {
        strcpy(string_full_path, generate_rand_string());
        strcpy(arr[i].location_full_path, string_full_path);
        strcpy(temp_string, a[rand()%2]);
        strcpy(arr[i].file_type, temp_string);
        arr[i].file_size =rand();
        arr[i].location_block_num=rand();
    }

    for(j=0; j<10; j++)
        start = insert_bst(start, arr[j]);
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
    output= search_bst(start , arr[9].file_name);
    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);
}

/*
void test_complex_bst()
{
    struct bst * tree = NULL;
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
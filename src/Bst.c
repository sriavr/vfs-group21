#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Filesystem.h"
#include "../include/Commons.h"
#include "../include/Bst.h"


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
}

struct bst * insert_bst(struct bst* bst_root, file_descriptor filedescriptor)
{
    struct bst * temp = bst_root;
    //create a new_node
    struct bst * new_node  = malloc(sizeof(struct bst));
    new_node -> right = NULL;
    new_node -> left = NULL;

    int length = strlen(filedescriptor.location_full_path) + strlen(filedescriptor.file_name);
    new_node -> key = calloc((length+2),sizeof(char));
    strcat(new_node -> key, filedescriptor.location_full_path);
    strcat(new_node -> key, "/");
    strcat(new_node -> key, filedescriptor.file_name);
    new_node -> filedescriptor = filedescriptor;

    while(1)
    {
        if(strcmp(new_node -> key, temp -> key) < 0)
        {
            if(temp -> left == NULL)
            {
                temp -> left = new_node;
                break;
            }
            else
            {
                temp = temp -> left;
            }
        }
        else if(strcmp(new_node -> key, temp -> key) > 0)
        {
            if(temp -> right == NULL)
            {
                temp -> right = new_node;
                break;
            }
            else
            {
                temp = temp -> right;
            }
        }
        else if(strcmp(new_node -> key, temp -> key) == 0)
        {
            fprintf(stderr, "Duplicate key insertion is not allowed.");
            break;
        }
    }

    return bst_root;
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





     char *a[2]={"file" ,"dir"};
     char *temp_string =NULL , *string_full_path =NULL;
     int len=0, length ;
     struct bst * del=NULL , *start=NULL;
     int i=0 , j=0 , k=0;
     file_descriptor arr[10];

     for(i=0;i<10;i++)
     {

        string_full_path = generate_rand_string();
        for(k=0;k<length;k++)
        arr[i].location_full_path[k] =string_full_path[k];
        temp_string=*a[rand()%2];
        len=strlen(temp_string);
        for(j=0;j<len;j++)
        arr[i].file_type[j]= a[j];
        arr[i].file_size =rand();
        arr[i].location_block_num=rand();


    }

        del=init_bst(start , arr[0]);
        for(j=1;j<10;j++)
       del= insert_bst(start, arr[j]);
       if(del!=NULL)
       {
            printf("sucessfull  inserted");

       }
       else
       {
            printf(" UNsuccessful inserted");
       }


        displaybst(start);
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

/*
int main()
{
    test_simple_bst();
    //test_complex_bst();
    return 0;
}*/



/*
{
    struct tree *p,*root;
    int m,x;
    char s;
    root=(struct tree *)malloc(sizeof(struct tree));
    printf("\nenter the value of the main root");
    scanf("%d",&m);
    root->data=m;
    root->left=NULL;
    root->right=NULL;
    printf("\nenter n to stop creation of the binary search tree");
    fflush(stdin);
    scanf("%c",&s);
    while(s!='n')
    {
        p=root;
        printf("\nenter the value of the newnode");
        fflush(stdin);
        scanf("%d",&x);
        while(1)
        {
            if(x<p->data)
            {
                if(p->left==NULL)
                {
                    p->left=(struct tree *)malloc(sizeof(struct tree));
                    p=p->left;
                    p->data=x;
                    p->right=NULL;
                    p->left=NULL;
                    break;
                }
                else
                p=p->left;
            }
            else
            {
                if(p->right==NULL)
                {
                    p->right=(struct tree *)malloc(sizeof(struct tree));
                    p=p->right;
                    p->data=x;
                    p->right=NULL;
                    p->left=NULL;
                    break;
                }
                else
                p=p->right;
            }
        }
        printf("\nwant to continue");
        fflush(stdin);
        scanf("%c",&s);
    }
    return(root);
}

*/


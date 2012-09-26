#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Bsth.h"
#include "../include/Commons.h"

struct bst* init_bst(struct bst* bst_root, const char *key_string, int value)
{
    bst_root = malloc(sizeof(struct bst));
    if(bst_root == NULL)
    {
        return NULL;
    }

    bst_root -> right = NULL;
    bst_root -> left = NULL;

    int length = strlen(key_string);
    bst_root -> key = malloc((length+1)*sizeof(char));
    strcpy(bst_root -> key, key_string);
    bst_root -> value = value;
    return bst_root;
}

struct bst * insert_bst(struct bst* bst_node, const char * key, int value)
{
    struct bst * temp  = bst_node;
    int length = strlen(key);
    while(1)
    {
        if(strcmp(key, temp -> key) < 0)
        {
            if(temp -> left == NULL)
            {
                temp -> left = (struct bst *) malloc(sizeof(struct bst));
                temp = temp -> left;
                temp -> right = NULL;
                temp -> left = NULL;
                temp -> key = (char *) malloc((length+1)*sizeof(char));
                strcpy(temp -> key, key);
                temp -> value = value;
                break;
            }
            else
            {
                temp = temp -> left;
            }
        }
        else if(strcmp(key, temp -> key) > 0)
        {
            if(temp -> right == NULL)
            {
                temp -> right = (struct bst *) malloc(sizeof(struct bst));
                temp = temp -> right;
                temp -> right = NULL;
                temp -> left = NULL;
                temp -> key = (char *) malloc((length+1)*sizeof(char));
                strcpy(temp -> key, key);
                temp -> value = value;
                break;
            }
            else
            {
                temp = temp -> right;
            }
        }
        else if(strcmp(key, temp -> key) == 0)
        {
            fprintf(stderr, "Duplicate key insertion is not allowed");
            break;
        }
    }

    return bst_node;
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
    process_node(bst_node);
    postorder_traversal( bst_node -> left, process_node);
    postorder_traversal( bst_node -> right, process_node );
}

void displaybst(struct bst *bst_node)
{
    printf("%s\n", bst_node -> key);
}

void test_simple_bst()
{
    struct bst * tree = NULL;
    tree = init_bst(tree, "Sridhar", 100);

    insert_bst(tree, "Pavan", 50);
    insert_bst(tree, "Lakshya", 500);
    insert_bst(tree, "Ruchi", 520);
    insert_bst(tree, "Priya", 620);

    printf("\nInorder traversal\n");
    inorder_traversal(tree, &displaybst);

    printf("\nPreorder traversal\n");
    preorder_traversal(tree, &displaybst);

    printf("\nPostorder traversal\n");
    postorder_traversal(tree, &displaybst);

}
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

int main()
{
    //test_simple_bst();
    test_complex_bst();
    return 0;
}


/*        bst_node = malloc(sizeof(struct bst));
    int length = strlen(key);
    bst_node -> key = malloc((length+1)*sizeof(char));
    strcpy(bst_node -> key, key);
    bst_node -> value = value;
    */
/*
struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
};
struct tree *create();
void preorder(struct tree *);
void inorder(struct tree *);
void postorder(struct tree *);
struct tree *create()
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
void preorder(struct tree *p)
{
    if(p!=NULL)
    {
        printf("%d ",p->data);
        preorder(p->left);
        preorder(p->right);
    }
}
void inorder(struct tree *p)
{
    if(p!=NULL)
    {
        inorder(p->left);
        printf("\t%d",p->data);
        inorder(p->right);
    }
}
void postorder(struct tree *p)
{
    if(p!=NULL)
    {
        postorder(p->left);
        postorder(p->right);
        printf("\t%d",p->data);
    }
}
void main()
{
    int h;
    struct tree *root;
    while(1)
    {
        printf("\nenter 1. for creation of the binary search tree");
        printf("\nenter 2. for preorder traversal");
        printf("\nenter 3. for inorder traversal");
        printf("\nenter 4. for postorder traversal");
        printf("\nenter 5. for exit");
        printf("\nenter your choice");
        scanf("%d",&h);
        switch(h)
        {
            case 1:
            root=create();
            break;
            case 2:
            preorder(root);
            break;
            case 3:
            inorder(root);
            break;
            case 4:
            postorder(root);
            break;
            case 5:
            exit(0);
            default:
            printf("\nentered a wrong choice");
        }
    }
}*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/Bst.h"
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

    postorder_traversal( bst_node -> left, process_node);
    postorder_traversal( bst_node -> right, process_node );
    process_node(bst_node);
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

/*
int main()
{
    test_simple_bst();
    //test_complex_bst();
    return 0;
}
*/


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


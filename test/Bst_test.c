#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Filesystem.h"
#include "../include/Commons.h"
#include "../include/Bst.h"

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


//void test_complex_bst()
//{
//    bst * tree = NULL;
//    tree = init_bst(tree, "ROOT", 100);
//    char * random_str;
//    int i;
//    for(i =0; i<10000; i++)
//    {
//        random_str = (char *) generate_rand_string();
//        insert_bst(tree, random_str, rand()%100);
//        free(random_str);
//    }
//
//    printf("\nInorder traversal\n");
//    inorder_traversal(tree, &displaybst);
//
//    printf("\nPreorder traversal\n");
//    preorder_traversal(tree, &displaybst);
//
//    printf("\nPostorder traversal\n");
//    postorder_traversal(tree, &displaybst);
//
//}



int Bst_main()
{
    test_simple_bst();
    //test_complex_bst();
    return 0;
}

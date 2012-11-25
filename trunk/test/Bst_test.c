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
    file_descriptor arr , output;

    strcpy(arr.file_name,"pinnacle" );
    strcpy(arr.location_full_path, "/home/desktop");
    strcpy(temp_string, a[rand()%2]);
    strcpy(arr.file_type, temp_string);
    arr.file_size =rand();
    arr.location_block_num=rand();

    start = insert_bst(start, arr);
    if(start!=NULL)
    {
        printf("sucessfull  inserted");
    }
    else
    {
        printf(" UNsuccessful inserted");
    }

    strcpy(arr.file_name,"srikanth" );
    strcpy(arr.location_full_path, "/home/desktop/new_folder/");
    strcpy(temp_string, a[rand()%2]);
    strcpy(arr.file_type, temp_string);
    arr.file_size =rand();
    arr.location_block_num=rand();

    start = insert_bst(start, arr);
    if(start!=NULL)
    {
        printf("sucessfull  inserted");
    }
    else
    {
        printf(" Unsuccessful inserted");
    }

    strcpy(arr.file_name,"superduper" );
    strcpy(arr.location_full_path, "/home/hello/vfs/works/");
    strcpy(temp_string, a[rand()%2]);
    strcpy(arr.file_type, temp_string);
    arr.file_size =rand();
    arr.location_block_num=rand();

    start = insert_bst(start, arr);
    if(start!=NULL)
    {
        printf("sucessfull  inserted");
    }
    else
    {
        printf(" UNsuccessful inserted");
    }

    inorder_traversal(start, displaybst);

    output= search_bst(start, "superduper" , "/home/hello/vfs/works/");
    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);

    output= search_bst(start, "superduper" , "/home/hello/vfs/works");
    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);

    output= search_bst_full(start , "/home/hello/vfs/works/superduper");
    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);

    output= search_bst_full(start , "/home/desktop/pinnacle");
    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);

    printf("deleting node /home/desktop/pinnacle\n");
    delete_bst(start, "/home/desktop/pinnacle");

    output= search_bst_full(start , "/home/desktop/pinnacle");
    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);

    printf("deleting node /home/hello/vfs/works/superduper/\n");
    delete_bst(start, "/home/hello/vfs/works/superduper/");
    output= search_bst_full(start , "/home/hello/vfs/works/superduper");
    printf("Filename: %s\n" , output.file_name);
    printf("Location: %s\n" , output.location_full_path);
    printf("Filetype: %s\n" , output.file_type);
    printf("Block Num: %d\n" , output.location_block_num);
    printf("Size: %ld\n" , output.file_size);

    inorder_traversal(start, displaybst);
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



int bst_test_main()
{
    test_simple_bst();
    //test_complex_bst();
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/Filesystem.h"
#include "../include/LinkedList.h"
#include "../include/Hashtable.h"
#include "../include/Commons.h"

void test_simple_search_hashtable()
{
    file_descriptor arr[7];
    strcpy(arr[0].file_name, "cat");
    strcpy(arr[0].location_full_path, "/home/sri/");
    strcpy(arr[0].file_type, "file");
    arr[0].file_size = 1024;
    arr[0].location_block_num = 2543;

    strcpy(arr[1].file_name, "zat");
    strcpy(arr[1].location_full_path, "/home/ruchi/");
    strcpy(arr[1].file_type, "dir");
    arr[1].file_size = 10;
    arr[1].location_block_num = 253;

    strcpy(arr[2].file_name, "12cat.txt");
    strcpy(arr[2].location_full_path, "/home/priya/");
    strcpy(arr[2].file_type, "file");
    arr[2].file_size = 1024;
    arr[2].location_block_num = 25;

    strcpy(arr[3].file_name, "%%rat.txt");
    strcpy(arr[3].location_full_path, "/home/pavan/");
    strcpy(arr[3].file_type, "file");
    arr[3].file_size = 1024;
    arr[3].location_block_num = 2643;

    strcpy(arr[4].file_name, "Rattle");
    strcpy(arr[4].location_full_path, "/home/mohan/");
    strcpy(arr[4].file_type, "file");
    arr[4].file_size = 1024;
    arr[4].location_block_num = 2763;

    strcpy(arr[5].file_name, "cattle");
    strcpy(arr[5].location_full_path, "/home/jsp/");
    strcpy(arr[5].file_type, "file");
    arr[5].file_size = 1024;
    arr[5].location_block_num = 2763;

    strcpy(arr[6].file_name, "catman");
    strcpy(arr[6].location_full_path, "/home/abbas/");
    strcpy(arr[6].file_type, "dir");
    arr[6].file_size = 1024;
    arr[6].location_block_num = 2763;

    struct node * hashtable[HASHSIZE];
    init_hashtable(hashtable);

    int i;
    for(i=0; i<7; i++)
    {
        insert_hashtable(hashtable, arr[i]);
    }

    struct node * temp;
    temp = search_hashtable(hashtable, "cat");

    if(temp!=NULL)
    {
        display_linkedlist(temp);
        //printf("\nMatch found. Key:%s\n",temp->filedescriptor.file_name);
    }
    else
    {
        printf("\nNo Match found\n");
    }


    /*file_descriptor arr[5];
    char *name[2]={"file","dir"};
    int i;
    for(i=0;i<5;i++)
    {
        strcpy(arr[i].file_name , generate_rand_string());
        strcpy(arr[i].location_full_path, generate_rand_string());
        strcpy(arr[i].file_type , name[rand()%2]);
        arr[i].file_size = rand();
        arr[i].location_block_num =rand();

    }

    struct node * hashtable[HASHSIZE];
    init_hashtable(hashtable);
    for(i=0;i<5;i++)
    insert_hashtable(hashtable, arr[i]);

    display_hashtable(hashtable);

    struct node * temp;
    temp = search_hashtable(hashtable, arr[4].file_name);

    if(temp!=NULL)
    {
        printf("\nMatch found. Key:%s\n",temp->filedescriptor.file_name);
    }
    else
    {
        printf("\nNo Match found\n");
    }

       temp= delete_hashtable(hashtable, temp->filedescriptor);

    if(temp!=NULL)
    {
        printf("\nDELETED SUCCESSFULY");
    }
    else
    {
        printf("\nNOT DELETED\n");
    }
    display_hashtable(hashtable); */
}

void test_complex_search_hashtable()
{
    int size = 5000, i, j;
    file_descriptor arr[size];
    for(j=0; j<size; j++)
    {
        strcpy(arr[j].file_name, generate_rand_string());
        strcpy(arr[j].location_full_path, generate_rand_string());
        strcpy(arr[j].file_type, "file");
        arr[j].file_size = rand()%30;
        arr[j].location_block_num = rand()%1000;
    }

    struct node * hashtable[HASHSIZE];
    init_hashtable(hashtable);

    for(i=0; i<size; i++)
    {
        insert_hashtable(hashtable, arr[i]);
    }

    display_hashtable(hashtable);

    struct node * tempr;
    tempr = search_hashtable(hashtable, "as");
    printf("\n\nprinting matches\n");
    display_linkedlist(tempr);
}


void test_complex_hashtable()
{
    struct node * hashtable[HASHSIZE], *temp = NULL;
    init_hashtable(hashtable);
    char * tempStr;
    tempStr = (char *) generate_rand_string();
    free(tempStr);
    int i;
    file_descriptor fd;
    for(i=0; i<5000; i++)
    {
        tempStr = (char *) generate_rand_string();
        strcpy(fd.file_name, tempStr);
        strcpy(fd.location_full_path, tempStr);
        fd.file_size = rand()%20;
        strcpy(fd.file_type , "dir");

        insert_hashtable(hashtable, fd);
        free(tempStr);
    }
    //display_hashtable(hashtable);

    for(i=0; i<HASHSIZE; i++)
    {
        temp = hashtable[i];
        while(temp != NULL)

        {
            if(search_hashtable(hashtable, temp -> filedescriptor.file_name ) == NULL)
            {
                //If the element is not found
                printf("\nThere is a problem in the search function or creation of node\n");
                return;
            }
            temp = temp -> next;
        }
    }
    printf("\nSearch function and creation of node working fine\n");
}

int test_main()
{
    //test_complex_hashtable();
    test_simple_search_hashtable();
    test_complex_search_hashtable();
    return 0;
}

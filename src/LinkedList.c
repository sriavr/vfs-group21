#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include "../include/Filesystem.h"
#include "../include/LinkedList.h"
#include "../include/Commons.h"

struct node *insert_linkedlist(struct node *start, file_descriptor new_node)
{
    //int len = strlen(new_node.file_name);
    struct node *fresh=NULL, *temp=NULL;

    //allocate memory for fresh node
    fresh=(struct node*)malloc(sizeof(struct node));

    //allocate memory for the node string TENTATIVE
    //fresh->filedescriptor.file_name = (char *) malloc(sizeof(char)* (len+1));

    //copy the input filedescriptor into the newly created filedescriptor
    fresh->filedescriptor = new_node;

    //point newly added node to NULL
    fresh->next=NULL;

    //if linked list is empty, make the start node as fresh
    if(start == NULL)
    {
        start=fresh;
    }
    else
    {
        temp=start;

        //iterate to the last node
        while((temp->next) != NULL)
        {
            temp=temp->next;
        }

        //assign the last node as fresh
        temp -> next = fresh;
    }

    return start;
}

void display_linkedlist(struct node *print)
{
    struct node *temp=NULL;
    temp=print;
    //iterate to the last node
    while(temp)
    {
        printf("filename:%s, filepath:%s\n",
               temp->filedescriptor.file_name, temp->filedescriptor.location_full_path);
        temp=temp->next;
    }

}

struct node * search_linkedlist(struct node *first, file_descriptor filedescriptor)
{
    struct node *temp=NULL,*matched_node=NULL;
    int found=0;

    //iterate till the last node
    temp=first;
    while(temp)
    {
        if(strcmp(temp->filedescriptor.file_name, filedescriptor.file_name) == 0)
        {
            found =1;
        }
        else
        {
            found = 0;
        }

        //if a match is found, return matched_node
        if(found)
        {
            matched_node = temp;
            return matched_node;
        }

        //traverse to next node
        temp=temp->next;
    }

    //return NULL if nothing found
    return NULL;
}

struct node *delete_linkedlist(struct node *first, file_descriptor filedescriptor)
{
    struct node *temp=NULL, *previous = NULL, *del =NULL;

    if(strcmp(first->filedescriptor.file_name, filedescriptor.file_name) == 0)
    {
        del=first;
        first = first -> next;
        free(del);
        return first;
    }

    //iterate till the last node
    temp=first;
    while(temp)
    {
        if(temp->next != NULL)
        {
            if(strcmp((temp->next)-> filedescriptor.file_name, filedescriptor.file_name) == 0)
            {
                del=temp -> next;
                temp -> next = temp -> next -> next;
                free(del);
                return first;
            }
        }
        else
        {

            if(strcmp(temp-> filedescriptor.file_name, filedescriptor.file_name) == 0)
            {

                //temp -> next = temp -> next -> next;
                free(temp);
                previous->next=NULL;
                return first;
            }


        }

        //traverse to next node
        previous =temp;
        temp=temp->next;
    }
    return NULL;
}

void test_simple_linkedlist()
{
    char *a[2]= {"file" ,"dir"};
    char *string_full_path =NULL;
    struct node * del=NULL;
    int i=0;
    file_descriptor arr[10];
    for(i=0; i<10; i++)
    {
        strcpy(string_full_path, generate_rand_string());
        //for(k=0; k<length; k++)
        strcpy(arr[i].location_full_path, string_full_path);
        strcpy(arr[i].file_type, a[rand()%2]);
        //len=strlen(temp_string);
        //for(j=0; j<len; j++)
        //    arr[i].file_type[j]= a[j];
        arr[i].file_size =rand();
        arr[i].location_block_num=rand();
    }

    struct node *start = NULL;
    start = insert_linkedlist(start, arr[0]);
    insert_linkedlist(start, arr[1]);
    insert_linkedlist(start, arr[2]);
    insert_linkedlist(start, arr[3]);
    insert_linkedlist(start, arr[4]);
    insert_linkedlist(start, arr[5]);
    insert_linkedlist(start, arr[6]);
    insert_linkedlist(start, arr[7]);
    insert_linkedlist(start, arr[8]);
    insert_linkedlist(start, arr[9]);

    //print the entire list
    display_linkedlist(start);
    printf("\n\n\n-------------------------------------------------");

    struct node * temp;
    //search for a node
    temp = search_linkedlist(start, arr[7]);

    if(temp!=NULL)
    {
        printf("\nFound match: %s",temp->filedescriptor.file_name);
    }
    else
    {
        printf("No search found");
    }

    del = delete_linkedlist(start,arr[4]);
    if(del !=NULL)
    {
        printf("\nFound match: %s",temp->filedescriptor.file_name);
    }
    else
    {
        printf("cannot be  deleted");
    }

    printf("\n\n\n-------------------------------------------------");
    display_linkedlist(start);

}

/*
void test_complex_linkedlist()
{
    struct node *start = NULL;
    start = insert_linkedlist(start, "FIRST NODE",23);

    int i;
    //Insert 1000 random nodes
    generate_rand_string(); //STRANGE BUG, has to be called at least once
    for(i =0; i< 10000; i++)
    {
        insert_linkedlist(start, generate_rand_string(), rand()%1000);
    }
    insert_linkedlist(start, "LAST NODE",25);

    struct node *temp = NULL, *matched_node = NULL;
    temp = start;
    //Iterating till the last node and searching all the nodes
    while(temp->next!=NULL)
    {
        matched_node = search_linkedlist(start, temp -> name);
        if(matched_node == NULL)
        {
            printf("\nProblem in the linked list implementation or search function\n");
            return;
        }
        temp = temp -> next;
    }

    printf("\nLinkedlist implementation, search function OK\n");
    //display_linkedlist(start);
}*/


/*
int main()
{
    test_simple_linkedlist();
    return 0;
}*/


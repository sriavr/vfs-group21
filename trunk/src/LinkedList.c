#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include "../include/LinkedListh.h"

struct linkedlist *insertlinkedlist(struct linkedlist *start, const char* key, int value)
{
    int len = strlen(key);
    struct linkedlist *fresh=NULL,*temp=NULL;

    //allocate memory for fresh node
    fresh=(struct linkedlist*)malloc(sizeof(struct linkedlist));

    //allocate memory for the node string
    fresh->name = (char *) malloc(sizeof(char)*len);
    fresh->value = 0;
    //copy the input string into the newly created node
    strcpy(fresh->name,key);
    fresh->value = value;

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

void displaylinkedlist(struct linkedlist *print)
{
    struct linkedlist *temp=NULL;
    temp=print;
    //iterate to the last node
    while(temp)
    {
        printf("key:%s value:%s",temp->name,temp->value);
        temp=temp->next;
    }
}

struct linkedlist * searchlinkedlist(struct linkedlist *first, const char *key)
{
    int len = strlen(key);
    struct linkedlist *temp=NULL,*matched_node=NULL;
    int i, found=0;

    //iterate till the last node
    temp=first;
    while(temp)
    {
        //if a match is not found, continue iteration
        for(i=0; i<len; i++)
        {
            if(temp->name[i]!=key[i])
            {
                break;
            }
            found = 1;
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

void test_linked_list()
{
    struct linkedlist *start = NULL;
    start = insertlinkedlist(start, "ruchi",23);
    insertlinkedlist(start, "priya",34);
    insertlinkedlist(start, "sridhar",35);
    insertlinkedlist(start, "pavan",53);
    displaylinkedlist(start);
    struct linkedlist *temp = NULL;
    temp = searchlinkedlist(start, "priya");
    if(temp!=NULL)
    {
        printf("\nFound match: %s",temp->name);
    }
    else
    {
        printf("No search found");
    }
}

/*int main()
{
    test_linked_list();
    return 0;
}*/

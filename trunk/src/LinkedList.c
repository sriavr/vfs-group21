#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include "../include/Filesystem.h"
#include "../include/LinkedList.h"
#include "../include/Commons.h"

struct node *insert_linkedlist(struct node *start, file_descriptor  filedescriptor, int value)
{
    int len = strlen(filedescriptor.file_name);
    struct node *fresh=NULL,*temp=NULL;

    //allocate memory for fresh node
    fresh=(struct node*)malloc(sizeof(struct node));

    //allocate memory for the node string
    fresh->name = (char *) malloc(sizeof(char)* (len+1));
    fresh->value = 0;
    //copy the input string into the newly created node
    strcpy(fresh->name,filedescriptor.file_name);
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
    
    fresh->filedescriptor = filedescriptor;
    return start;
}

void display_linkedlist(struct node *print)
{
    struct node *temp=NULL;
    temp=print;
    //iterate to the last node
    while(temp)
    {
        printf("key:%s value:%d\n",temp->name,temp->value);
        temp=temp->next;
    }

}

struct node * search_linkedlist(struct node *first, file_descriptor filedescriptor)
{
    int len = strlen(filedescriptor.file_name);
    struct node *temp=NULL,*matched_node=NULL;
    int i, found=0;

    //iterate till the last node
    temp=first;
    while(temp)
    {
        //if a match is not found, continue iteration
        for(i=0; i<len; i++)
        {
            if(temp->name[i]!=filedescriptor.file_name[i])
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

void delete_linkedlist(struct node *hashtable,int index,struct node *temp);
{
	
	struct node *del , *traverse;
	if(hashtable[index]->next == temp)
	hashtable[index] ->next = hashtable[index] ->next ->next;
	else
	{
		traverse = hashtable[index] ->next;
		while(traverse!=NULL)
		{
			if(traverse ->next ==temp)
			{
				del=traverse->next;
				traverse->next = traverse->next->next;
				delete(del);		
			}
		}
	traverse = traverse->next;
	
	
	}



}



void test_simple_linkedlist()
{
    struct node *start = NULL;
    start = insert_linkedlist(start, "ruchi",23);
    insert_linkedlist(start, "priya",34);
    insert_linkedlist(start, "sridhar",35);
    insert_linkedlist(start, "pavan",53);

    //print the entire list
    display_linkedlist(start);

    struct node * temp;
    //search for a node
    temp = search_linkedlist(start, "priya");

    if(temp!=NULL)
    {
        printf("\nFound match: %s",temp->name);
    }
    else
    {
        printf("No search found");
    }
}

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
}


/*
int main()
{
    test_complex_linkedlist();
    return 0;
}
*/

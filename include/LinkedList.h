#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

//TODO make the node in LinkedList generic
//so that we can reuse code for FreeList and HashTable of file descriptors
struct node
{
    struct node *next;
    file_descriptor filedescriptor;
};

//Insert a new node (with key, value) into the linked list
struct node *insert_linkedlist(struct node *start,file_descriptor filedescriptor);

//Search the linked list based on the input string, and return matching node, else return NULL
struct node * search_linkedlist(struct node *first, file_descriptor filedescriptor);

//TODO
//Search the linked list based on the input string, and return matching node, else return NULL
struct node *delete_linkedlist(struct node *first, file_descriptor filedescriptor);

//Prints the linkedlist from the input node to end
void display_linkedlist(struct node *);

//Test cases for linkedlist
void test_complex_linkedlist();
void test_simple_linkedlist();

#endif

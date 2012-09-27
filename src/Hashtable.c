#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/LinkedList.h"
#include "../include/Hashtable.h"
#include "../include/Commons.h"

//By default a local variable of hashtable[] has junk values
//This function clears junk and allocates NULL
void init_hashtable(struct node * hashtable[])
{
    int i=0;
    for(i=0; i<HASHSIZE; i++)
    {
        hashtable[i] = NULL;
    }
}

//Insert a string of length len into the HashTable,
// and return node where it was inserted
struct node * insert_hashtable(
    struct node * hashtable[], const char* key, int value)
{
    int index = 0;
    // Makes sure the key is not already present in the hashtable.
    int hash_code = get_hash_code(key);
    index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct node *temp = NULL;
    temp = hashtable[index];
    while(temp!= NULL)
    {
        if((get_hash_code(temp -> name)) == hash_code
                && (strcmp(temp -> name, key)==0))
        {
            return temp;
        }
        temp = temp -> next;
    }

    //Go to the index calculated
    temp = hashtable[index];
    //Add the node to linked list
    hashtable[index] = insert_linkedlist(temp, key, value);
    return temp;
}

/**
 * Returns a hash code for this string. The hash code for a
 * char array is computed as
 * s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
 * using int arithmetic, where s[i] is the
 * ith character of the string, n is the length of
 * the string, and ^ indicates exponentiation.
 * (The hash value of the empty string is zero.)
 *
 * @return  a hash code value for this object.
 */

int get_hash_code(const char *str)
{
    int len = strlen(str);
    int hash = 0, i = 0;
    if (len > 0)
    {
        int off = 0;

        for (i = 0; i < len; i++)
        {
            //hash = 31*hash + str[off++];
            hash = 31*hash + str[off++];
        }
    }
    return hash;
}

struct node * search_hashtable(struct node * hashtable[], char * key)
{
    int hash_code = get_hash_code(key);
    int index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct node *temp = NULL;
    temp = hashtable[index];
    while(temp!= NULL)
    {
        if((get_hash_code(temp -> name)) == hash_code
                && (strcmp(temp -> name, key)==0))
        {
            return temp;
        }
        temp = temp -> next;
    }
    return NULL;
}

void display_hashtable(struct node * hashtable[])
{
    int i;
    for(i=0; i<HASHSIZE; i++)
    {
        display_linkedlist(hashtable[i]);
        printf("\n");
    }
}

/*
void displayhashlist(struct node *print)
{
    struct node *temp=NULL;
    temp=print;
    //iterate to the last node
    while(temp != NULL)
    {
        printf("key:%s  value:%d\t",temp->name, temp->value);
        temp=temp->next;
    }
}*/

void test_complex_hashtable()
{
    struct node * hashtable[HASHSIZE], *temp = NULL;
    init_hashtable(hashtable);
    char * tempStr;
    tempStr = (char *) generate_rand_string();
    free(tempStr);
    int i;
    for(i=0; i<5000; i++)
    {
        tempStr = (char *) generate_rand_string();
        insert_hashtable(hashtable, tempStr, rand());
        free(tempStr);
    }
    //display_hashtable(hashtable);

    for(i=0; i<HASHSIZE; i++)
    {
        temp = hashtable[i];
        while(temp != NULL)
        {
            if(search_hashtable(hashtable, temp -> name) == NULL)
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

void test_simple_hashtable()
{
    struct node * hashtable[HASHSIZE];
    init_hashtable(hashtable);
    insert_hashtable(hashtable, "Sridhar", 138);
    insert_hashtable(hashtable, "Priya", 42);
    insert_hashtable(hashtable, "Ruchi", 55);
    insert_hashtable(hashtable, "Pavan", 63);
    insert_hashtable(hashtable, "Lakshya", 72);
    display_hashtable(hashtable);

    struct node * temp;
    temp = search_hashtable(hashtable, "Sridhar");

    if(temp!=NULL)
    {
        printf("\nMatch found. Key:%s, Value:%d\n",temp->name, temp->value);
    }
    else
    {
        printf("\nNo Match found\n");
    }
}
/*
int main()
{
    test_complex_hashtable();
    //test_simple_hashtable();
    return 0;
}
*/

/*

void delete()                                                           // DELETING SOME VALUE FROM HASH TABLE AT A PARTICULAR LOCATION
{
    char *filename=NULL,*temp=NULL;
    int h=0;
    struct node *found=NULL,*first=NULL;
    printf("enter the filename that you want to delete");
    scanf("%s",filename);
//	for(i=0;i<HASHSIZE;i++){
//		if(*filename==hash[i].*name){
//			break;
//		}
//		}


    h=hash(filename);
//	if(hash[i].*name==*filename){
//	temp=hash[i].*name;
    for(; *filename; filename++)
    {
        if((hashtable[h].(*name))==*filename)
            (hashtable[h].name)++;
    }

    if(((hashtable[h].(*name)) != *filename)|| ((hashtable[h].(*name)) =='\0'&& *filename!='\0')  ||  ((hashtable[h].(*name)) !='\0'&& *filename=='\0'))
    {
        if(hashtable[h].next==NULL)
        {
            printf("not found");
        }
        else
        {
            first=hashtable[h].next;
            found=searchnode(first,filename);
            found->next=found->next->next;
            free(found);
        }

        //struct linkedlist *start=HASHSIZE[i];
        //	deletion(start);

    }
}
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/Filesystem.h"
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
    struct node * hashtable[], file_descriptor filedescriptor)
{
    int index = 0;
    // Makes sure the key is not already present in the hashtable.
    int hash_code = get_hash_code(filedescriptor.file_name);
    index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct node *temp = NULL;
    temp = hashtable[index];
    while(temp!= NULL)
    {
        if((get_hash_code(temp -> filedescriptor.file_name)) == hash_code                  //requirement of this???
                && (strcmp(temp -> filedescriptor.file_name, filedescriptor.file_name)==0))
        {
            return temp;
        }
        temp = temp -> next;
    }

    //Go to the index calculated
    temp = hashtable[index];
    //Add the node to linked list
    hashtable[index] = insert_linkedlist(temp, filedescriptor);


    return temp;
}



struct node * delete_hashtable(
    struct node * hashtable[], file_descriptor filedescriptor)
{
    int index = 0;
    // Makes sure the key is not already present in the hashtable.
    int hash_code = get_hash_code(filedescriptor.file_name);
    index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct node *temp = NULL;
    temp = hashtable[index];
    while(temp!= NULL)
    {
        if((get_hash_code(temp -> filedescriptor.file_name)) == hash_code                  //requirement of this???
                && (strcmp(temp -> filedescriptor.file_name , filedescriptor.file_name)==0))
        {
            delete_linkedlist(temp, filedescriptor);
        }
        temp = temp -> next;
    }


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

struct node * search_hashtable(struct node * hashtable[], file_descriptor filedescriptor )          //pass filedescriptor file_name in this
{
    int hash_code = get_hash_code(filedescriptor.file_name);
    int index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct node *temp = NULL;
    temp = hashtable[index];
    while(temp!= NULL)
    {
        if((get_hash_code(temp -> filedescriptor.file_name)) == hash_code
                && (strcmp(temp -> filedescriptor.file_name, filedescriptor.file_name)==0))
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

/*void test_complex_hashtable()
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
}*/

 
void test_simple_hashtable()
{

    filedescriptor arr[5];
    char *name[2]={"file","dir"};

    for(i=0;i<5;i++)
    {
        strcpy(arr[i].file_name , generate_rand_string());
        strcpy(arr[i].location_full_path, generate_rand_string());
        strcpy(arr[i].file_type , *name[rand()%2]);
        arr[i].fileSize = rand();
        arr[i].location_block_num =rand();

    }
    struct node * hashtable[HASHSIZE];
    init_hashtable(hashtable);
    for(i=0;i<10;i++)
    insert_hashtable(hashtable, arr[i]);

    display_hashtable(hashtable);

    struct node * temp;
    temp = search_hashtable(hashtable, arr[4]);

    if(temp!=NULL)
    {
        printf("\nMatch found. Key:%s, Value:%d\n",temp->name);
    }
    else
    {
        printf("\nNo Match found\n");
    }

   temp= delete_hashtable(hashtable, filedescriptor);

    if(temp!=NULL)
    {
        printf("\nDELETED SUCCESSFULY");
    }
    else
    {
        printf("\nNOT DELETED\n");
    }


    display_hashtable(hashtable);
}

int main()
{
    //test_complex_hashtable();
    test_simple_hashtable();
    return 0;
}


/*

void delete()                                                           // DELETING SOME VALUE FROM HASH TABLE AT A PARTICULAR LOCATION
{
    char *file_name=NULL,*temp=NULL;
    int h=0;
    struct node *found=NULL,*first=NULL;
    printf("enter the file_name that you want to delete");
    scanf("%s",file_name);
//	for(i=0;i<HASHSIZE;i++){
//		if(*file_name==hash[i].*name){
//			break;
//		}
//		}


    h=hash(file_name);
//	if(hash[i].*name==*file_name){
//	temp=hash[i].*name;
    for(; *file_name; file_name++)
    {
        if((hashtable[h].(*name))==*file_name)
            (hashtable[h].name)++;
    }

    if(((hashtable[h].(*name)) != *file_name)|| ((hashtable[h].(*name)) =='\0'&& *file_name!='\0')  ||  ((hashtable[h].(*name)) !='\0'&& *file_name=='\0'))
    {
        if(hashtable[h].next==NULL)
        {
            printf("not found");
        }
        else
        {
            first=hashtable[h].next;
            found=searchnode(first,file_name);
            found->next=found->next->next;
            free(found);
        }

        //struct linkedlist *start=HASHSIZE[i];
        //	deletion(start);

    }
}
*/

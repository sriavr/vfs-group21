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
                && (strcmp(temp -> filedescriptor.file_name, filedescriptor.file_name)==0)
                && (strcmp(temp->filedescriptor.location_full_path, filedescriptor.location_full_path)==0))
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
        if((get_hash_code(temp -> filedescriptor.file_name)) == hash_code
                && (strcmp(temp -> filedescriptor.location_full_path , filedescriptor.location_full_path)==0))
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

struct node * search_hashtable(struct node * hashtable[], char *filename )          //pass filedescriptor file_name in this
{
    int hash_code = get_hash_code(filename);
    int index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct node *start = NULL;
    struct node *temp = NULL;
    temp = hashtable[index];
    while(temp!= NULL)
    {
        if((get_hash_code(temp -> filedescriptor.file_name)) == hash_code
                && (strcmp(temp -> filedescriptor.file_name, filename)==0))
        {
            start = insert_linkedlist(start, temp -> filedescriptor);
        }
        temp = temp -> next;
    }

    return start;
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


void test_simple_search_hashtable()
{
    file_descriptor arr[5];
    strcpy(arr[0].file_name, "cat.txt");
    strcpy(arr[0].location_full_path, "/home/sri/");
    strcpy(arr[0].file_type, "file");
    arr[0].file_size = 1024;
    arr[0].location_block_num = 2543;

    strcpy(arr[1].file_name, "cat.txt");
    strcpy(arr[1].location_full_path, "/home/ruchi/");
    strcpy(arr[1].file_type, "file");
    arr[1].file_size = 10;
    arr[1].location_block_num = 253;

    strcpy(arr[2].file_name, "cat.txt");
    strcpy(arr[2].location_full_path, "/home/priya/");
    strcpy(arr[2].file_type, "file");
    arr[2].file_size = 1024;
    arr[2].location_block_num = 25;

    strcpy(arr[3].file_name, "rat.txt");
    strcpy(arr[3].location_full_path, "/home/pavan/");
    strcpy(arr[3].file_type, "file");
    arr[3].file_size = 1024;
    arr[3].location_block_num = 2643;

    strcpy(arr[4].file_name, "rat.txt");
    strcpy(arr[4].location_full_path, "/home/mohan/");
    strcpy(arr[4].file_type, "file");
    arr[4].file_size = 1024;
    arr[4].location_block_num = 2763;

    struct node * hashtable[HASHSIZE];
    init_hashtable(hashtable);

    int i;
    for(i=0; i<5; i++)
    {
        insert_hashtable(hashtable, arr[i]);
    }

    struct node * temp;
    temp = search_hashtable(hashtable, "cat.txt");

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
    display_hashtable(hashtable);*/
}

void test_complex_search_hashtable()
{
    int size = 5000, i,j;
    file_descriptor arr[size];
    char temp[20];
    for(i=0; i<size; i++)
    {
        strcpy(temp, generate_rand_string());
        for(j=i; (j < (rand()%15)+10) && (j <size); j++)
        {
            strcpy(arr[j].file_name, temp);
            strcpy(arr[j].location_full_path, generate_rand_string());
            strcpy(arr[j].file_type, "file");
            arr[j].file_size = rand()%30;
            arr[j].location_block_num = rand()%1000;
        }
        i = j;
    }

    struct node * hashtable[HASHSIZE];
    init_hashtable(hashtable);

    for(i=0; i<size; i++)
    {
        insert_hashtable(hashtable, arr[i]);
    }

    display_hashtable(hashtable);

    struct node * tempr;
    tempr = search_hashtable(hashtable, "wlrbbmqb");
    printf("printing matches\n");
    display_linkedlist(tempr);
}


/*int main()
{
    //test_complex_hashtable();
    //test_simple_search_hashtable();
    test_complex_search_hashtable();
    return 0;
}*/


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

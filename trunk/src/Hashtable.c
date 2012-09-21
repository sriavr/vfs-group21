#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../include/LinkedListh.h"
#include "../include/Hashh.h"


//By default a local variable of hashtable[] has junk values
//This function clears junk and allocates NULL
void init_hash(struct linkedlist * hashtable[])
{
    int i=0;
    for(i=0; i<HASHSIZE; i++)
    {
        hashtable[i] = NULL;
    }
}

//Insert a string of length len into the HashTable,
// and return node where it was inserted
struct linkedlist * insert_hashtable(
    struct linkedlist * hashtable[], const char* key, int value)
{
    int index = 0;
    int len = strlen(key);
    // Makes sure the key is not already present in the hashtable.
    int hash_code = hashCode(key);
    index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct linkedlist *temp = NULL;
    temp = hashtable[index];
    while(temp!= NULL)
    {
        if((hashCode(temp -> name)) == hash_code
                && (strcmp(temp -> name, key)==0))
        {
            return temp;
        }
        temp = temp -> next;
    }

    //Go to the index calculated
    temp = hashtable[index];
    //Add the node to linked list
    hashtable[index] = insertlinkedlist(temp, key, value);
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

int hashCode(const char *str)
{
    int len = strlen(str);
    int hash = 0, i = 0;
    if (len > 0)
    {
        int off = 0;

        for (i = 0; i < len; i++)
        {
            hash = 31*hash + str[off++];
        }
    }
    return hash;
}

struct linkedlist * search(struct linkedlist * hashtable[], char * key)
{
    int hash_code = hashCode(key);
    int index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct linkedlist *temp = NULL;
    temp = hashtable[index];
    while(temp!= NULL)
    {
        if((hashCode(temp -> name)) == hash_code
                && (strcmp(temp -> name, key)==0))
        {
            return temp;
        }
        temp = temp -> next;
    }
    return NULL;
}

void display(struct linkedlist * hashtable[])
{
    int i;
    for(i=0; i<HASHSIZE; i++)
    {
        displayhashlist(hashtable[i]);
        printf("\n");
    }
}

void displayhashlist(struct linkedlist *print)
{
    struct linkedlist *temp=NULL;
    temp=print;
    //iterate to the last node
    while(temp)
    {
        printf("key:%s  value:%d\t",temp->name, temp->value);
        temp=temp->next;
    }
}

void test_hash_table()
{
    struct linkedlist * hashtable[HASHSIZE];
    init_hash(hashtable);
    insert_hashtable(hashtable, "Sridhar", 138);
    insert_hashtable(hashtable, "Priya", 42);
    insert_hashtable(hashtable, "Ruchi", 55);
    insert_hashtable(hashtable, "Pavan", 63);
    insert_hashtable(hashtable, "Lakshya", 72);
    int i;
    for(i=0; i<100; i++)
    {
        insert_hashtable(hashtable, generate_rand_string(), rand()%300);
    }
    display(hashtable);
}

void test_hash_search(){
    struct linkedlist * hashtable[HASHSIZE];
    init_hash(hashtable);
    insert_hashtable(hashtable, "Sridhar", 138);
    insert_hashtable(hashtable, "Priya", 42);
    insert_hashtable(hashtable, "Ruchi", 55);
    insert_hashtable(hashtable, "Pavan", 63);
    insert_hashtable(hashtable, "Lakshya", 72);
    display(hashtable);
    struct linkedlist * temp;
    temp = search(hashtable, "Sridhar");
    if(temp!=NULL){
        printf("Match found. Key:%s, Value:%d",temp->name, temp->value);
    }
    else{
        printf("No Match found");
    }
}

const char * generate_rand_string()
{
    int length = rand()%15;
    char * str = (char *) malloc(sizeof(char)*length);
    int i;
    for(i=0; i<length -1; i++)
    {
        str[i] = 'a' + rand()%26;
    }
    str[i] = '\0';
    return str;
}


int main()
{
    //test_hash_table();
    test_hash_search();
    return 0;
}


/*

void delete()                                                           // DELETING SOME VALUE FROM HASH TABLE AT A PARTICULAR LOCATION
{
    char *filename=NULL,*temp=NULL;
    int h=0;
    struct linkedlist *found=NULL,*first=NULL;
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
            found=searchlinkedlist(first,filename);
            found->next=found->next->next;
            free(found);
        }

        //struct linkedlist *start=HASHSIZE[i];
        //	deletion(start);

    }



}
*/


/*void usermenu()
{
    int choice=0;
    while(1)
    {
        printf("which operation you want to don in hash table \n Enter choice \n 1)Insert \n2)Delete \n 3)Search");

        scanf("%d",&choice);
        switch(choice)
        {

        case 1:
            insert();
            break;

        case 2:
            delete();
            break;

        case 3:
            search();
            break;

        }
    }
}*/

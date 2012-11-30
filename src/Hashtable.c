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
//    int index = 0;
    // Makes sure the key is not already present in the hashtable.
    int hash_code = get_hash_code(filedescriptor.file_name);
    int full_path_length = strlen(filedescriptor.location_full_path);
    if(filedescriptor.location_full_path[full_path_length - 1] != '/')
    {
        strcat(filedescriptor.location_full_path, "/");
    }
//    index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct node *temp = NULL;
    temp = hashtable[hash_code];
    while(temp!= NULL)
    {
        if((get_hash_code(temp -> filedescriptor.file_name)) == hash_code                  //requirement of this???
                && (strcmp(temp -> filedescriptor.file_name, filedescriptor.file_name)==0)
                && (strcmp(temp -> filedescriptor.location_full_path, filedescriptor.location_full_path)==0))
        {
            return temp;
        }
        temp = temp -> next;
    }

    //Go to the index calculated
    temp = hashtable[hash_code];
    //Add the node to linked list
    hashtable[hash_code] = insert_linkedlist(temp, filedescriptor);


    return temp;
}

struct node * delete_hashtable(
    struct node * hashtable[], file_descriptor filedescriptor)
{
//    int index = 0;
    // Makes sure the key is not already present in the hashtable.
    int hash_code = get_hash_code(filedescriptor.file_name);
//    index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    struct node *temp = NULL;
    temp = hashtable[hash_code];
    while((temp != NULL) || (temp -> filedescriptor.file_name != NULL))
    {
        if((get_hash_code(temp -> filedescriptor.file_name)) == hash_code
                && (strcmp(temp -> filedescriptor.location_full_path , filedescriptor.location_full_path)==0))
        {
           hashtable[hash_code] = delete_linkedlist(temp, filedescriptor);
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
//    int hash = 0, i = 0;
    if (len > 0)
    {
        if (str[0] >= 'A' && str[0] <= 'Z')
        {
            return str[0]-'A';
        }
        else if(str[0] >= 'a' && str[0] <= 'z')
        {
            return str[0] - 'a';
        }
        else if(str[0] >= '0' && str[0] <= '9')
        {
            return str[0] - '0' + 26;
        }
        else
        {
            return 36;
        }
    }
    return 36;
}

struct node * search_hashtable(struct node * hashtable[], char *filename )          //pass filedescriptor file_name in this
{
//    int index = (hash_code & 0x7FFFFFFF) % HASHSIZE;
    file_descriptor root_fd;
    strcpy(root_fd.file_name, "/");
    strcpy(root_fd.location_full_path, "/");
    root_fd.file_size = BLOCK_SIZE;
    strcpy(root_fd.file_type, "dir");
    struct node *start = NULL;
    struct node *temp = NULL;
    if(strcmp(filename, "/") == 0)
    {
        start = insert_linkedlist(start, root_fd);
        return start;
    }

    int hash_code = get_hash_code(filename);
    temp = hashtable[hash_code];

    while(temp!= NULL)
    {
        if((get_hash_code(temp -> filedescriptor.file_name)) == hash_code
                && (strncmp(temp -> filedescriptor.file_name, filename, strlen(filename))==0))
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






#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#define HASHSIZE 37

/*By default a local variable of hashtable[] has junk values
This function clears junk and allocates NULL*/
void init_hashtable(struct node * hashtable[]);

//get a unique predictable hash code for a string
int get_hash_code(const char *str);

//insert a node (key, value pair) into the hash table
struct node * insert_hashtable(
        struct node * hashtable[], file_descriptor filedescriptor);

//search for a particular key and return that node
struct node * search_hashtable(struct node * hashtable[], char *filename );

//delete a particular node in a hash table. TODO
struct node * delete_hashtable(
    struct node * hashtable[], file_descriptor filedescriptor);

//print the linkedlist
//void displayhashlist(struct node *print);

//display the contents of the hash table
void display_hashtable(struct node * hashtable[]);

//Test cases for hashtable
void test_complex_hashtable();
void test_simple_hashtable();

#endif

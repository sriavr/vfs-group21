#define HASHSIZE 20

/*By default a local variable of hashtable[] has junk values
This function clears junk and allocates NULL*/
void init_hash(struct node * hashtable[]);
//get a unique predictable hash code for a string
int get_hash_code(const char *str);
//insert a node (key, value pair) into the hash table
struct node * insert_hashtable(
        struct node * hashtable[], const char* key, int value);
//search for a particular key and return that node
struct node * search(struct node * hashtable[], char * key);
//display the contents of the hash table
void display(struct node * hashtable[]);
//print the linkedlist
void displayhashlist(struct node *print);
void test_complex_hashtable();
void test_simple_hashtable();

struct linkedlist
{
    char * name;
    int value;
    struct linkedlist *next;
};

//Insert a new node (with key, value) into the linked list
struct linkedlist *insertlinkedlist(struct linkedlist *start, const char* key, int value);

//Search the linked list based on the input string, and return matching node, else return NULL
struct linkedlist * searchlinkedlist(struct linkedlist *first, const char *key);

//Prints the linkedlist from the input node to end
void displaylinkedlist(struct linkedlist *);


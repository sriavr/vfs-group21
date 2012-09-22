struct node
{
    char * name;
    int value;
    struct node *next;
};

//Insert a new node (with key, value) into the linked list
struct node *insertlinkedlist(struct node *start, const char* key, int value);

//Search the linked list based on the input string, and return matching node, else return NULL
struct node *searchlinkedlist(struct node *first, const char *key);

//Search the linked list based on the input string, and return matching node, else return NULL
struct node *deletelinkedlist(struct node *first, const char *key);

//Prints the linkedlist from the input node to end
void displaylinkedlist(struct node *);


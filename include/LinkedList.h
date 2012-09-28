struct node
{
    char * name;
    int value;
    struct node *next;
};

//Insert a new node (with key, value) into the linked list
struct node *insert_linkedlist(struct node *start, const char* key, int value);

//Search the linked list based on the input string, and return matching node, else return NULL
struct node *search_linkedlist(struct node *first, const char *key);

//TODO
//Search the linked list based on the input string, and return matching node, else return NULL
struct node *delete_linkedlist(struct node *first, const char *key);

//Prints the linkedlist from the input node to end
void display_linkedlist(struct node *);

//Test cases for linkedlist
void test_complex_linkedlist();
void test_simple_linkedlist();


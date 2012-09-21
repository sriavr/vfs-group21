#define HASHSIZE 26


void init_hash(struct linkedlist * hashtable[]);
int hashCode(const char *str);
struct linkedlist * insert_hashtable(
        struct linkedlist * hashtable[], const char* key, int value);
void display(struct linkedlist * hashtable[]);
struct linkedlist * search(struct linkedlist * hashtable[], char * key);
const char * generate_rand_string();


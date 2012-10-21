//used by file system to create a linked list containing free list of blocks
struct node * create_linkedlist(file_descriptor * file_descriptor_list, long int file_descriptor_list_size);

//used by file system to create a binary search tree with filenames with absolute path
struct bst* create_bst(file_descriptor * file_descriptor_list, long int file_descriptor_list_size);

//used by filesystem to create an empty hash table and fill it with directory info
void fill_hashtable(struct node * hashtable[], file_descriptor * file_descriptor_list, long int file_descriptor_list_size);

//nAry Tree representing directory structure
//nNode * create_nAry_tree(file_descriptor * file_descriptor_list, long int file_descriptor_list_size);

#ifndef FREELIST_H_INCLUDED
#define FREELIST_H_INCLUDED

//initialize the free list allocated to 0
void init_free_list();

//to allocate 1 to the bit in freelist whose index is block_num - 1
//used when a block is allocated, return -1 if failed
int update_flist_allocate(long int block_num);

//to allocate 0 to the bit in freelist whose index is block_num - 1
//used when a block is deallocated, return -1 if failed
int update_flist_deallocate(long int block_num);

//gives the next available free block
long int next_free_block();

#endif // FREELIST_H_INCLUDED

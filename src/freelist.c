#include <stdio.h>
#include "../include/freelist.h"
#include "../include/Filesystem.h"

extern meta_header *mh ;
extern header *hdr;


//block numbering starts from 0
void init_free_list()
{
    //initialize the next_block_num to -1 for all free list items
    mh  -> file_descriptors_used = 0;
    long int i;
    for(i=0; i<(mh->VFS_FILE_SIZE); i++)
    {
        hdr -> list[i].allocated = 0;
    }
}

//to allocate 1 to the bit in freelist whose index is block_num - 1
//used when a block is allocated
int update_flist_allocate(long int block_num)
{
    mh  -> file_descriptors_used = mh  -> file_descriptors_used + 1;
    if(block_num >=0 && block_num < (mh->VFS_FILE_SIZE))
    {
        hdr->list[block_num].allocated = 1;
        return 0;
    }
    return -1;
}

//to allocate 0 to the bit in freelist whose index is block_num - 1
//used when a block is deallocated
int update_flist_deallocate(long int block_num)
{
    mh  -> file_descriptors_used = mh  -> file_descriptors_used - 1;
    if(block_num >=0 && block_num < (mh->VFS_FILE_SIZE))
    {
        hdr->list[block_num].allocated = 0;
        return 0;
    }
    return -1;
}

//gives the next available free block
long int next_free_block()
{
    long int i=0;
    for(i =0 ; i < (mh->VFS_FILE_SIZE); i++)
    {
        if(hdr->list[i].allocated == 0)
        {
            update_flist_allocate(i);
            return i;
        }
    }
    return -1;
}

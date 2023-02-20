#ifndef __HEAP_EXT
#define __HEAP_EXT

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* Define the linked list structure.  This is used to link free blocks in order
of their memory address. */
typedef struct A_BLOCK_LINK
{
    struct A_BLOCK_LINK *pxNextFreeBlock; /*<< The next free block in the list. */
    size_t xBlockSize;                    /*<< The size of the free block. */
 } BlockLink_t;

extern void* pvPortRealloc(void *pv, size_t size);

#ifdef __cplusplus
}
#endif
#endif
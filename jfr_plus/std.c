#ifndef _STDDEF_H
#define _STDDEF_H
typedef unsigned int size_t;
#define BCM2835_SYSTEM_TIMER_BASE 0x20003000
#ifndef NULL
#define NULL ((void*)0)
#endif
#endif

#include "fb.h"

// Define the heap

extern unsigned char _end[];
// unsigned char *HEAP_START = &_end[0]; // End of kernel

unsigned char *HEAP_START = (unsigned char *)0x400000; // Top of stack
unsigned int   HEAP_SIZE  = 0x30000000; // Max heap size is 768Mb
unsigned char *HEAP_END;

// Set up some static globals

// static unsigned char *freeptr;
// static unsigned int bytes_allocated = 0;

// void mem_init()
// {
//    // Align the start of heap to an 8-byte boundary

//    if ((long)HEAP_START % 8 != 0) {
//       HEAP_START += 8 - ((long)HEAP_START % 8);
//    }
//    HEAP_END = (unsigned char *)(HEAP_START + HEAP_SIZE);

//    freeptr = HEAP_START;
// }

typedef enum memory_tag {
    block_free = 0,
    block_allocated = 1,
} memory_tag;

typedef struct Block {
    // Whether the block is free
    memory_tag tag;
    // Allocated block size when the block is created, will not change once created
    size_t allocated_memory;
    // Pointer to the next chunk of memory, NULL if last block in memory
    struct Block* next;
} Block;

typedef struct Heap_Metadata {
    // Total memory available
    size_t total_memory_left;
    // Pointer to the start of the heap, not including this
    // Always goes up to advance in memory
    Block *block_start;
} Heap_Metadata;

Block create_block(void);
Block *get_next_free_block(Block *current);
Block *get_free_block_with_requested_size(size_t requested_size, Block *block_start);
void *return_allocated_block(Block *block);
Block *map_address_to_block(void *);
Block *get_last_allocated_block(Block *block);
void empty_block(Block *block);

static Heap_Metadata *metadata = NULL;

void mem_init(void) {
    // clear the heap
    // Set the metadata to the total heap
    metadata = (Heap_Metadata *)HEAP_START;
    // Update the total memory left
    metadata->total_memory_left = HEAP_SIZE - sizeof(Heap_Metadata);
    
    // Set the available heap to the address of the first block
    metadata->block_start = (Block *)HEAP_START + sizeof(Heap_Metadata);
    
    // Create a free block at the start of the memory
    Block *first_block = metadata->block_start;
    // Allocate MIN_BLOCK_SIZE bytes
    first_block->allocated_memory = sizeof(Block);
    first_block->tag = block_free;
    first_block->next = NULL;
    
    // A block with MIN_BLOCK_SIZE bytes has been allocated, and the metadata on the heap
    metadata->total_memory_left = HEAP_SIZE - sizeof(Block) - sizeof(Heap_Metadata) * 2;
}

void *malloc(size_t requested_size) {
    // Fail if not enough memory is requested.
    if (requested_size == 0) {
        drawString(500, 200, "block size 0 was requested. Not doing anything.", 0x0f);
        return NULL;
    }
    // Fail if not enough memory is left.
    if (metadata->total_memory_left <= requested_size) {
        drawString(500, 200, "Not enough memory left for allocation. Not doing anything.", 0x0f);
        return NULL;
    }
    
    // Get next free block with a similar size
    Block *next_free_block = get_free_block_with_requested_size(requested_size, metadata->block_start);
    if (next_free_block != NULL) {
        // Found a block with a compatible size, mark it allocated again
        next_free_block->tag = block_allocated;
        return return_allocated_block(next_free_block);
    }
    // No compatible blocks were found, create a new block with the requested size, and return it
    Block *last_block = get_last_allocated_block(metadata->block_start);
    // Allocate the memory for the newly created block
    
    Block *new_block = (Block *)last_block + sizeof(Block) + last_block->allocated_memory;
    
    new_block->tag = block_allocated;
    new_block->allocated_memory = requested_size;
    
    last_block->next = new_block;
    
    // Update global metadata to keep track of memory allocated
    metadata->total_memory_left -= (sizeof(Block) + requested_size);
    
    return return_allocated_block(new_block);
}


void free(void *ptr) {
    Block *block = map_address_to_block(ptr);
    if (block->tag == block_allocated) {
        block->tag = block_free;
    } else {
        drawString(500, 200, "Invalid address passed to free, or trying to double free. Not doing anything.", 0x0f);
    }
}

void *return_allocated_block(Block *block) {
    void *memory = block;
    // Return the allocated memory block, with an offset of the block size and tag to avoid overwriting them
    memory += sizeof(Block);
    return memory;
}

Block *map_address_to_block(void *memory_chunk) {
    // Offset back the memory chunk with the tag and allocated memory, and hope memory hasn't been overwritten
    void *copy = memory_chunk - sizeof(Block);
    return (Block *)copy;
}

Block *get_last_allocated_block(Block *block) {
    Block *copy = block;
    if (copy->next == NULL) {
        return copy;
    }
    while (copy->next != NULL) {
        copy = copy->next;
    }
    return copy;
}

Block *get_free_block_with_requested_size(size_t requested_size, Block *block_start) {
    if (block_start == NULL) {
        return NULL;
    }
    Block *start_copy = block_start;
    if (start_copy->tag == block_free && start_copy->allocated_memory >= requested_size) {
        return start_copy;
    }
    Block *next_free_block = get_next_free_block(start_copy);
    if (next_free_block == start_copy) {
        next_free_block = next_free_block->next;
    }
    if (next_free_block != NULL) {
        if (next_free_block->allocated_memory >= requested_size) {
            return next_free_block;
        }
        return get_free_block_with_requested_size(requested_size, next_free_block);
    }
    
    return NULL;
}

Block *get_next_free_block(Block *current) {
    if (current->tag == block_free) {
        return current;
    }
    Block *copy = current;
    while (copy->next != NULL) {
        if (copy->tag == block_free) {
            return copy;
        }
        copy = copy->next;
    }
    return NULL;
}

void wait_nsec(unsigned int n)
{
    register unsigned long f, t, r;
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    t+=((f/1000)*n)/1000; // Exp of the counter
    do{asm volatile ("mrs %0, cntpct_el0" : "=r"(r));}while(r<t);
}


int rand() {
    register unsigned long f, t, r;
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    
    // Use the timer value as a seed to generate a random number
    r = t % f;

    return (int)r;
}


// unsigned long state0 = 1;
// unsigned long state1 = 2;

// unsigned long rand(void)
// {
//     unsigned long s1 = state0;
//     unsigned long s0 = state1;

//     state0 = s0;
//     s1 ^= s1 << 23;
//     s1 ^= s1 >> 17;
//     s1 ^= s0;
//     s1 ^= s0 >> 26;
//     state1 = s1;

//     return state0 + state1;
// }
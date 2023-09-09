#ifndef _STDDEF_H
#define _STDDEF_H
typedef unsigned int size_t;
#ifndef NULL
#define NULL ((void*)0)
#endif
#endif

#define HEAP_SIZE 1024 * 1024  // 1 MB
#define MIN_BLOCK_SIZE sizeof(Block)

typedef struct Block {
    size_t size;
    struct Block* next;
} Block;

static char heap[HEAP_SIZE];
static Block* free_list = NULL;

void initialize_heap() {
    free_list = (Block*)heap;
    free_list->size = HEAP_SIZE - sizeof(Block);
    free_list->next = NULL;
}

void* malloc(size_t size) {
    // Ensure that size is at least the size of a Block
    if (size < MIN_BLOCK_SIZE) {
        size = MIN_BLOCK_SIZE;
    }

    Block* prev = NULL;
    Block* current = free_list;

    while (current) {
        if (current->size >= size) {
            if (current->size >= size + sizeof(Block)) {
                // Split the block if it's large enough
                Block* new_block = (Block*)((char*)current + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->next = current->next;
                current->size = size;
                current->next = new_block;
            }

            if (prev) {
                prev->next = current->next;
            } else {
                free_list = current->next;
            }

            return (void*)(current + 1); // Return a pointer to the data part
        }

        prev = current;
        current = current->next;
    }

    // No suitable free block found
    return NULL;
}

void free(void* ptr) {
    if (ptr) {
        // Convert the data pointer back to a Block pointer
        Block* block = ((Block*)ptr) - 1;
        block->next = free_list;
        free_list = block;
    }
}
#ifndef _STDDEF_H
#define _STDDEF_H
typedef unsigned int size_t;
#define BCM2835_SYSTEM_TIMER_BASE 0x20003000
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


// Define a pointer to the system timer registers
volatile unsigned int* system_timer_regs = (unsigned int*)BCM2835_SYSTEM_TIMER_BASE;

// Define a function to get the current time in seconds
unsigned int get_system_timer_seconds() {
    // Read the lower 32 bits of the system timer counter
    unsigned int counter_low = system_timer_regs[1];
    // Read the upper 32 bits of the system timer counter
    unsigned int counter_high = system_timer_regs[3];

    // Combine the upper and lower bits to get the full 64-bit value
    unsigned long long counter_value = ((unsigned long long)counter_high << 32) | counter_low;

    // The system timer runs at 1 MHz, so divide by 1,000,000 to get seconds
    return (unsigned int)(counter_value / 1000000);
}
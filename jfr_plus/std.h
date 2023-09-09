#ifndef _STDDEF_H
#define _STDDEF_H
typedef unsigned int size_t;
#ifndef NULL
#define NULL ((void*)0)
#endif
#endif

void initialize_heap();
void* malloc(size_t size);
void free(void* ptr);
#ifndef _STDDEF_H
#define _STDDEF_H
typedef unsigned int size_t;
#ifndef NULL
#define NULL ((void*)0)
#endif
#endif

void mem_init();
void *malloc(unsigned int size);
void free(void *ptr);
void wait_nsec(unsigned int n);
unsigned long rand(void);


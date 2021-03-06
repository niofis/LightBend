#if !defined(MEMORY)
#define MEMORY

#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#endif

extern void* aligned_malloc16(int size);
extern void* aligned_realloc16(void* mem, int size);

extern void* aligned_malloc(int aligment, int size);
extern void aligned_free(void* mem);
extern void* aligned_realloc(void* mem, int aligment, int size);

#endif
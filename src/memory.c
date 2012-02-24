#include "memory.h"


//When allocating memory, aligment bytes plus the size of a memory pointer are added to the
//memory allocation

void* aligned_malloc(int aligment, int size)
{
	int total;
	void* ptr;
	int pad;
	void* final;
	int t;

	pad=aligment+sizeof(size_t);
	total=size+pad;

#ifdef WIN32
	ptr=HeapAlloc(GetProcessHeap(),HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY,total);
#else
	ptr=malloc(total);
#endif
	if(ptr==NULL)
		return NULL;
	
	t=aligment - (size_t)ptr%aligment;
	final= (void*)((size_t)ptr + t);

	*((size_t*)final-1)=(size_t)ptr;

	return (void*)final;
}


void aligned_free(void* mem)
{
	void* original;

	original=(void*)*((size_t*)mem-1);

#ifdef WIN32
	HeapFree(GetProcessHeap(),0,original);
#else
	free(original);
#endif
	
}
#include "memory.h"



void* aligned_malloc16(int size)
{
	return aligned_malloc(16, size);
}

void* aligned_realloc16(void* mem, int size)
{
	return aligned_realloc(mem,16, size);
}

//When allocating memory, aligment bytes plus the size of a memory pointer are added to the
//memory allocation

void* aligned_malloc(int aligment, int size)
{
	size_t total;
	void* ptr;
	size_t pad;
	void* final;
	size_t t;

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

//void* aligned_malloc(int aligment, int size)
//{
//	return aligned_realloc(NULL,aligment,size);
//}

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

void* aligned_realloc(void* mem, int aligment, int size)
{
	void* original;
	size_t total;
	void* ptr;
	size_t pad;
	void* final;
	size_t t;
	
	pad=aligment+sizeof(size_t);
	total=size+pad;

	if(mem!=NULL)
		original=(void*)*((size_t*)mem-1);
	else
		original=NULL;

#ifdef WIN32
	ptr=HeapReAlloc(GetProcessHeap(),HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY,original,size);
#else
	ptr=realloc(original,size);
#endif

	if(ptr==NULL)
		return NULL;

	t=aligment - (size_t)ptr%aligment;
	final= (void*)((size_t)ptr + t);

	*((size_t*)final-1)=(size_t)ptr;

	return (void*)final;

}
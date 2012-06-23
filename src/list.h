#if !defined(LIST)
#define LIST

#include "globals.h"
#include "memory.h"

align(ALIGMENT)
struct ListElement
{
	struct ListElement* previous;
	struct ListElement* next;
	void* data;
};

align(ALIGMENT)
typedef struct
{
	int count;
	struct ListElement* head;
	struct ListElement* tail;
} List;

List* list_create();
void list_add(List* list,void* aligned_data);
void list_delete(List* list,int index,int delete_data);
void* list_get(List* list,int index);
void list_destroy(List* list,int delete_data);
void list_append(List* to, List* from);

#endif

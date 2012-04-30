#include "list.h"

List* list_create()
{
	List* list;
	list=(List*)aligned_malloc(ALIGMENT,sizeof(List));

	list->count=0;
	list->head=NULL;
	list->tail=NULL;

	return list;
}

void list_append(List* list,void* aligned_data)
{
	struct ListElement* el;
	if(list!=NULL)
	{
		el=(struct ListElement*)aligned_malloc(ALIGMENT,sizeof(struct ListElement));
		if(list->head==NULL)
		{
			list->head=el;
			list->tail=el;
			el->data=aligned_data;
			el->previous=NULL;
			el->next=NULL;
		}
		else
		{
			el->next=NULL;
			list->tail->next=el;
			el->previous=list->tail;
			list->tail=el;
		}
		list->count++;
	}
}

void list_delete(List* list,int index)
{
	int i;
	struct ListElement* el;
	if(list!=NULL)
	{
		i=0;
		el=list->head;
		while(i<index && el!=NULL)
		{
			el=el->next;
			++i;
		}

		if(el!=NULL)
		{		
			if(el->previous!=NULL)
			{
				el->previous->next=el->next;
			}
			if(el->next!=NULL)
			{
				el->next->previous=el->previous;
			}

			if(el==list->head)
			{
				list->head=el->next;
			}

			if(el==list->tail)
			{
				list->tail=el->previous;
			}

			aligned_free(el->data);
			aligned_free(el);

			list->count--;
		}
	}
}

void* list_get(List* list,int index)
{
	int i;
	struct ListElement* el;
	if(list!=NULL)
	{
		i=0;
		el=list->head;
		while(i<index && el!=NULL)
		{
			el=el->next;
			++i;
		}
		if(el!=NULL)
			return el->data;
	}
	return NULL;
}

void list_destroy(List* list)
{
	struct ListElement* el;
	if(list!=NULL)
	{
		while(list->head!=NULL)
		{
			el=list->head;
            list->head=el->next;
            if(el->data!=NULL)
                aligned_free(el->data);
			aligned_free(el);
		}
		aligned_free(list);
	}
	
}

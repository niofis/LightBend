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

void list_add(List* list,void* aligned_data)
{
	struct ListElement* el;
	if(list!=NULL)
	{
		el=(struct ListElement*)aligned_malloc(ALIGMENT,sizeof(struct ListElement));
		el->data=aligned_data;
		if(list->head==NULL)
		{
			list->head=el;
			list->tail=el;
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

void list_remove(List* list,int index, bool delete_data)
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

			if(delete_data==TRUE)
			{
				aligned_free(el->data);
                el->data=NULL;
			}
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

void list_delete(List* list,bool delete_data)
{
	struct ListElement* el;
	if(list!=NULL)
	{
		while(list->head!=NULL)
		{
			el=list->head;
            list->head=el->next;
            if(el->data!=NULL && delete_data==TRUE)
            {
                aligned_free(el->data);
                el->data=NULL;
            }
			aligned_free(el);
		}
		aligned_free(list);
	}
	
}

void list_append(List* to, List* from)
{
	int i;
	for(i=0;i<from->count;++i)
	{
		list_add(to,list_get(from,i));
	}
}

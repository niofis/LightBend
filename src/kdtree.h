//
//  kdtree.h
//  LightBend
//
//  Created by Enrique on 10/7/12.
//
//

#ifndef KDTREE
#define KDTREE
#include "globals.h"
#include "list.h"


align(ALIGMENT)
typedef struct
{
    int axis;
    float value;
    struct KDNode* left;
    struct KDNode* right;
    List* elements;    
} KDNode;

align(ALIGMENT)
typedef struct
{
	struct ListElement* root;
} KDTree;

align(ALIGMENT)
KDNode kd_leaf = {.axis=0,.value=0,.left=NULL,.right=NULL,.elements=NULL};

List* list_new();
void list_add(List* list,void* aligned_data);
void list_remove(List* list,int index,bool delete_data);
void* list_get(List* list,int index);
void list_delete(List* list,bool delete_data);
void list_append(List* to, List* from);

#endif

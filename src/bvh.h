#if !defined(BVH)
#define BVH

#define BOX_OBJ_CAP 4
#define CHILD_QTY 2

//Heap
#define LEFT(id)(id<<1)+1
#define RIGHT(id)(id<<1)+2
#define PARENT(id)(id-1)>>1

#define ROOT_NODE 0
#define LEAF_NODE 1
#define NULL_NODE 2

align(ALIGMENT)
typedef struct
{
	float min[3];
	float max[3];
} Box;

//float *cajas_min_x,*cajas_min_y,*cajas_min_z;
//float *cajas_max_x,*cajas_max_y,*cajas_max_z;

align(ALIGMENT)
typedef struct
{
	int type;//0 nodo raiz, 1 nodo hoja, 2 nodo deshabilitado
	int objs_num;
	int objs[BOX_OBJ_CAP];
} BoundingVolume;

align(ALIGMENT)
typedef struct
{
	Box box;
	int objs[BOX_OBJ_CAP];
	int type;//0 nodo raiz, 1 nodo hoja, 2 nodo deshabilitado
	int cant_objs;
	int hijos[CHILD_QTY];
	
}BoundingVolumeEx;

BoundingVolume* hierarchy;
int boxes_num;
//int depth;
Box* boxes;
int idx_traverse;
int* v_traverse;
int idx_skip;
int* skip_ptrs;


void BuildBVH();
void CleanBVH();
int BoxHit(int box_id,Ray *ray);
void TraverseBVH(int bv_id, Ray* ray);

#endif
#if !defined(BVH)
#define BVH

#define CANT_OBJ_CAJA 4
#define CANT_HIJOS 2

//Heap
#define LEFT(id)(id<<1)+1
#define RIGHT(id)(id<<1)+2
#define PARENT(id)(id-1)>>1

#define NODO_RAIZ 0
#define NODO_HOJA 1
#define NODO_INVALIDO 2

align(16)
typedef struct
{
	float min[3];
	float max[3];
} Caja;

float *cajas_min_x,*cajas_min_y,*cajas_min_z;
float *cajas_max_x,*cajas_max_y,*cajas_max_z;

align(16)
typedef struct
{
	int type;//0 nodo raiz, 1 nodo hoja, 2 nodo deshabilitado
	int cant_objs;
	int objs[CANT_OBJ_CAJA];
} BoundingVolume;

align(16)
typedef struct
{
	Caja caja;
	int objs[CANT_OBJ_CAJA];
	int type;//0 nodo raiz, 1 nodo hoja, 2 nodo deshabilitado
	int cant_objs;
	int hijos[CANT_HIJOS];
	
}BoundingVolumeEx;

BoundingVolume* hierarchy;
int num_cajas;
//int depth;
Caja* cajas;
int idx_traverse;
int* v_traverse;
int idx_skip;
int* skip_ptrs;


void BuildBVH();
void CleanBVH();
int BoxHit(int box_id,Ray *ray);
void TraverseBVH(int bv_id, Ray* ray);

#endif
#include <math.h>
#include "globals.h"
#include "renderer.h"
#include "bvh.h"

align(ALIGMENT)
typedef struct
{
    float* min_x;
    float* min_y;
    float* min_z;
    float* max_x;
    float* max_y;
    float* max_z;
    int count;
} BoxData;

int next_node;
int node_stop;
int stop;
BoxData boxdata;

int BoxHit(int box_id,Ray *ray)
{
	/*
	*
	*      Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
	*      "An Efficient and Robust Ray-Box Intersection Algorithm"
	*      Journal of graphics tools, 10(1):49-54, 2005
	*	   http://jgt.akpeters.com/papers/WilliamsEtAl05/
	* 
	*/
	float inv_direccion[4];
	int signo[4];
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	float* parameters[2];
	Box *box=&boxes[box_id];

	parameters[0]=box->min;
	parameters[1]=box->max;

	V_REC(inv_direccion,ray->direccion);
    signo[0] = (inv_direccion[0] < 0);
    signo[1] = (inv_direccion[1] < 0);
    signo[2] = (inv_direccion[2] < 0);

	  

	tmin = (parameters[signo[0]][0] - ray->origen[0]) * inv_direccion[0];
	tmax = (parameters[1-signo[0]][0] - ray->origen[0]) * inv_direccion[0];
	tymin = (parameters[signo[1]][1] - ray->origen[1]) * inv_direccion[1];
	tymax = (parameters[1-signo[1]][1] - ray->origen[1]) * inv_direccion[1];
	if ( (tmin > tymax) || (tymin > tmax) ) 
		return 0;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (parameters[signo[2]][2] - ray->origen[2]) * inv_direccion[2];
	tzmax = (parameters[1-signo[2]][2] - ray->origen[2]) * inv_direccion[2];
	if ( (tmin > tzmax) || (tzmin > tmax) ) 
		return 0;
	//if (tzmin > tmin)
	//	tmin = tzmin;
	//if (tzmax < tmax)
	//	tmax = tzmax;

	//if( (tmin < t1) && (tmax > t0) )
	//return NULL;

	return 1;
}

void BuildTraverseVector(int node)
{
	int l=LEFT(node);
	int r=RIGHT(node);

	v_traverse[idx_traverse]=node;
	idx_traverse++;

	if(l<boxes_num && hierarchy[l].type!=NULL_NODE)
		BuildTraverseVector(l);
	if(r<boxes_num && hierarchy[r].type!=NULL_NODE)
		BuildTraverseVector(r);	
}


void TraverseStop(int node)
{
	int l=LEFT(node);
	int r=RIGHT(node);
	
	if(next_node!=-1)
		return;
	if(stop)
		next_node=node;

	if(!stop)
	{
		if(l<boxes_num && hierarchy[l].type!=NULL_NODE)
			TraverseStop(l);
		if(r<boxes_num && hierarchy[r].type!=NULL_NODE)
			TraverseStop(r);	
	}
	else
		next_node=node;
	


	stop=stop || node==node_stop;
}

int Partition(int p, int r,int eje)
{
	int i,j,k;
	float x;
    Triangle t;
	//Randomized Partition
	k=rand()%(r-p);
	k+=p;
	//t=numeros[r];
	//numeros[r]=numeros[k];
	//numeros[k]=t;
    memcpy(&t,&escena.objects[r],sizeof(Triangle));
    memcpy(&escena.objects[r],&escena.objects[k],sizeof(Triangle));
    memcpy(&escena.objects[k],&t,sizeof(Triangle));
	/////////////
	x=escena.objects[r].v1[eje];
	i=p-1;
	for(j=p;j<r;j++)
	{
		if(escena.objects[j].v1[eje]<x)
		{
			i++;
            memcpy(&t,&escena.objects[i],sizeof(Triangle));
            memcpy(&escena.objects[i],&escena.objects[j],sizeof(Triangle));
            memcpy(&escena.objects[j],&t,sizeof(Triangle));
		}
	}
	i++;
    memcpy(&t,&escena.objects[i],sizeof(Triangle));
    memcpy(&escena.objects[i],&escena.objects[j],sizeof(Triangle));
    memcpy(&escena.objects[j],&t,sizeof(Triangle));
	return i;
}

void QuickS(int p, int r,int eje)
{
	int q;
	if(p<r)
	{
		q=Partition(p,r,eje);
		QuickS(p,q-1,eje);
		QuickS(q+1,r,eje);
	}
}

void QuickSort(int eje)
{
	QuickS(0,escena.num_objects-1,eje);
}

void GetDistances()
{
	int i;
	float centroide[4];
	for(i=0;i<escena.num_objects;i++)
	{
		//obtener el centroide
		centroide[0]=(escena.objects[i].v1[0] + escena.objects[i].v2[0] + escena.objects[i].v3[0])/3;
		centroide[1]=(escena.objects[i].v1[1] + escena.objects[i].v2[1] + escena.objects[i].v3[1])/3;
		centroide[2]=(escena.objects[i].v1[2] + escena.objects[i].v2[2] + escena.objects[i].v3[2])/3;
	}
}


void Cosa()
{

}


void GenerateLeaves(int num_leaves,int num_boxes)
{
	int x, y, i;
	int obj_id=0;
	int l_id=0;
    Triangle *objeto;

	//GetDistances();
	//ordenar los objects, por el eje x, luego el y y por ultimo el z
	//QuickSort(0);
	//QuickSort(1);
	//QuickSort(2);

	l_id=num_boxes-num_leaves;
	//Ir metiendo los objects a las hojas e ir aumentando el tamao de las raicez
	for(x=0;x<num_leaves;x++)
	{
		if(obj_id>=escena.num_objects)
		{
			//si ya no hay objects para las cajas, se deshabilita para que no 
			//se gaste tiempo revisando un hit en ella
			hierarchy[l_id].type=NULL_NODE;
			l_id++;
			continue;
		}
		hierarchy[l_id].type=LEAF_NODE;
		for(i=0;i<3;i++)
			boxes[l_id].min[i]=boxes[l_id].max[i]=escena.objects[obj_id].v1[i];

		for(y=0;y<BOX_OBJ_CAP && obj_id<escena.num_objects;y++)
		{
			for(i=0;i<3;i++){
				objeto=&escena.objects[obj_id];
                //if(objeto->type==OBJ_TRIANGLE)
                //{
					boxes[l_id].min[i]=min(boxes[l_id].min[i],objeto->v1[i]);
					boxes[l_id].max[i]=max(boxes[l_id].max[i],objeto->v1[i]);

					boxes[l_id].min[i]=min(boxes[l_id].min[i],objeto->v2[i]);
					boxes[l_id].max[i]=max(boxes[l_id].max[i],objeto->v2[i]);

					boxes[l_id].min[i]=min(boxes[l_id].min[i],objeto->v3[i]);
					boxes[l_id].max[i]=max(boxes[l_id].max[i],objeto->v3[i]);
                //}
                /*
                else if(objeto->type==OBJ_SPHERE)
				{
					cajas[l_id].min[i]=min(cajas[l_id].min[i],objeto->v1[i]-objeto->radious);
					cajas[l_id].max[i]=max(cajas[l_id].max[i],objeto->v1[i]+objeto->radious);

					cajas[l_id].min[i]=min(cajas[l_id].min[i],objeto->v2[i]-objeto->radious);
					cajas[l_id].max[i]=max(cajas[l_id].max[i],objeto->v2[i]+objeto->radious);

					cajas[l_id].min[i]=min(cajas[l_id].min[i],objeto->v3[i]-objeto->radious);
					cajas[l_id].max[i]=max(cajas[l_id].max[i],objeto->v3[i]+objeto->radious);
				}
                */
			}

			hierarchy[l_id].objs[y]=obj_id;
			obj_id++;
		}
		hierarchy[l_id].objs_num=y;
		l_id++;
	}
}

//Crece las cajas de la jerarquia recursivamente, para aumentar una raiz
//primero crece los nodos izquierdo y derecho, si encuentra hojas en ellos
//no hace nada y solo se sale de la funcion.
void GrowHierarchy(int node_id)
{
	int l,r;

	//Si no es un nodo raiz, no hay que crecerlo
	if(hierarchy[node_id].type!=ROOT_NODE)
		return;

	l=LEFT(node_id);
	r=RIGHT(node_id);
	GrowHierarchy(l);
	GrowHierarchy(r);

	//Revisa si alguno de los nodos hijos esta deshabilitado
	//si es el caso, utiliza las dimensiones del nodo que si esta habilitado
	//si ambos estan deshabilitados, deshabilita el nodo actual
	if(hierarchy[l].type!=NULL_NODE && hierarchy[r].type==NULL_NODE)
	{
		boxes[node_id].min[0]=boxes[l].min[0];
		boxes[node_id].min[1]=boxes[l].min[1];
		boxes[node_id].min[2]=boxes[l].min[2];
		boxes[node_id].max[0]=boxes[l].max[0];
		boxes[node_id].max[1]=boxes[l].max[1];
		boxes[node_id].max[2]=boxes[l].max[2];
	}
	else if(hierarchy[l].type==NULL_NODE && hierarchy[r].type!=NULL_NODE)
	{
		boxes[node_id].min[0]=boxes[r].min[0];
		boxes[node_id].min[1]=boxes[r].min[1];
		boxes[node_id].min[2]=boxes[r].min[2];
		boxes[node_id].max[0]=boxes[r].max[0];
		boxes[node_id].max[1]=boxes[r].max[1];
		boxes[node_id].max[2]=boxes[r].max[2];
	}
	else if(hierarchy[l].type!=NULL_NODE && hierarchy[r].type!=NULL_NODE)
	{
		boxes[node_id].min[0]=min(boxes[l].min[0],boxes[r].min[0]);
		boxes[node_id].min[1]=min(boxes[l].min[1],boxes[r].min[1]);
		boxes[node_id].min[2]=min(boxes[l].min[2],boxes[r].min[2]);

		boxes[node_id].max[0]=max(boxes[l].max[0],boxes[r].max[0]);
		boxes[node_id].max[1]=max(boxes[l].max[1],boxes[r].max[1]);
		boxes[node_id].max[2]=max(boxes[l].max[2],boxes[r].max[2]);
	}
	else
		hierarchy[node_id].type=NULL_NODE;

}

void OptimizeBVH()
{
    
}

void BuildBVH()
{
	//calcular la profuncidad del arbol, creo que es log2 de la cantidad de objects.
	//cada hoja puede contener hasta 4 objects, por lo tanto la cantidad de cajas se calcularia como
	//Log2(objects/cant_x_caja)+1 = Profundidad del arbol
	//cantidad de cajas=(2^profundidad) -1;
	
	int num_hojas;
	//int num_cajas;
	int depth;
	int i,j;
	float a,b;

	CleanBVH();

	num_hojas=escena.num_objects/BOX_OBJ_CAP;
	if(escena.num_objects%BOX_OBJ_CAP)
		num_hojas++;
	
	a=log((float)num_hojas);
	b=log((float)2);
	depth=(a/b);
	if((a/b)-(float)depth)
		depth++;
	depth++;
	boxes_num=pow((float)2,depth)-1;
	num_hojas=pow((float)2,depth-1);

	//se obtiene el espacio de memoria y se inicializa a ceros

	hierarchy=(BoundingVolume*)aligned_malloc(ALIGMENT,boxes_num*sizeof(BoundingVolume));
	boxes=(Box*)aligned_malloc(ALIGMENT,boxes_num*sizeof(Box));
	v_traverse=(int*)aligned_malloc(ALIGMENT,boxes_num*sizeof(int));
	skip_ptrs=(int*)aligned_malloc(ALIGMENT,boxes_num*sizeof(int));

	memset(hierarchy,0,boxes_num*sizeof(BoundingVolume));
	memset(boxes,0,boxes_num*sizeof(Box));
	memset(v_traverse,0,boxes_num*sizeof(int));
	memset(skip_ptrs,-1,boxes_num*sizeof(int));

	//se genera la gerarquia comenzando en el nodo primero
	//Primero generando las hojs y despues aumentando los contenedores
	GenerateLeaves(num_hojas,boxes_num);
	GrowHierarchy(0);

	//generar la lista de indices de recorrido, para no estar dando lata con en TraverseBVH
	idx_traverse=0;
	BuildTraverseVector(0);

	//Generar la lista de saltos
	skip_ptrs[0]=-1;
	for(i=1;i<boxes_num;i++)
	{
		node_stop=v_traverse[i];
		stop=0;
		next_node=-1;
		TraverseStop(0);
		if(next_node!=-1)
		{
			for(j=0;j<boxes_num;j++)
				if(v_traverse[j]==next_node)
				{
					skip_ptrs[i]=j;
					break;
				}
		}
		else
			skip_ptrs[i]=-1;
	}

	//Imprimir los vectores de traverse y de skip pointers
	//for(i=0;i<num_cajas;i++)
	//	printf("%d ",v_traverse[i]);
	//printf("\n");
	//for(i=0;i<num_cajas;i++)
	//	printf("%d ",skip_ptrs[i]);
}

void CleanBVH()
{
	if(hierarchy!=NULL)
		aligned_free(hierarchy);

	if(boxes!=NULL)
		aligned_free(boxes);

	if(v_traverse!=NULL)
		aligned_free(v_traverse);

	if(skip_ptrs!=NULL)
	aligned_free(skip_ptrs);
/*
	if(cajas_min_x!=NULL)
		aligned_free(cajas_min_x);
	if(cajas_min_y!=NULL)
		aligned_free(cajas_min_y);
	if(cajas_min_z!=NULL)
		aligned_free(cajas_min_z);

	if(cajas_max_x!=NULL)
		aligned_free(cajas_max_x);
	if(cajas_max_y!=NULL)
		aligned_free(cajas_max_y);
	if(cajas_max_z!=NULL)
		aligned_free(cajas_max_z);
 */
}

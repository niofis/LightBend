#include <math.h>
#include "list.h"
#include "solids.h"
#include "renderer.h"



float* point()
{
    return aligned_malloc16(sizeof(float)*3);
}


//Name: CreateSphere
//Function: Creates a sphere acording to the number of slices and slice resolution indicated
//          through the parameters.
//Conditions: num_slices must be >= 2
//Result: if num_slices>=2 A list of triangles, or else, NULL
List* CreateSphere(float* center, float radious, int num_slices, int slice_resolution, int group_id)
{
	List* sphere;
    List** points;
    float* pt;

    if(num_slices<2)
        return NULL;

	sphere=(List*)aligned_malloc(ALIGMENT,sizeof(List));

    points=(List**)aligned_malloc16(sizeof(List*)*(num_slices+1));

    //first point, on top
    pt=point();
    V_COPY(pt,center);
    pt[1]=pt[1]-radious;
    list_add(points[0],pt);

    //last point, botton
    pt=point();
    V_COPY(pt,center);
    pt[1]=pt[1]+radious;
    list_add(points[num_slices],pt);


    Translate(center,sphere);
    return sphere;
}

void Translate(float* offset, List* triangles)
{
    int i;
    Triangle* tr;
    for(i=0;i<triangles->count;++i)
    {
        tr=(Triangle*)list_get(triangles,i);
        V_ADD(tr->v1,tr->v1,offset);
        V_ADD(tr->v2,tr->v2,offset);
        V_ADD(tr->v3,tr->v3,offset);
    }
}

#include <math.h>
#include "list.h"
#include "primitives.h"
#include "solids.h"
#include "renderer.h"


float* point(float x, float y, float z)
{
    float* pt=aligned_malloc16(sizeof(float)*3);
    V_INIT(pt,x,y,z);
    return pt;
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

//Name: rotate
//Function: rotates a point the specified rads, on the axis especified (0:x, 1:y, 2:z)
//Conditions: point must be a 3 elements array, rads must be radians and 0<=axis<=2
//Results: point gets rotated, no return value with the return keyword
void rotate(float* point, float rads, int axis)
{
    float tx;
    float ty;
    float tz;

    tx=point[0];
    ty=point[1];
    tz=point[2];

    //rotation over x:
    //tx=x
    //ty=y*cos + z*sin
    //tz=-y*sin + z*cos

    if(axis==0)
    {
        point[1]=ty*cos(rads) + tz*sin(rads);
        point[2]=-ty*sin(rads) + tz*cos(rads);
    }

    //rotation over y
    //tx=x*cos + z*sin
    //ty=y
    //tz=-x*sin + z*cos

    if(axis==1)
    {
        point[0]=tx*cos(rads) + tz*sin(rads);
        point[2]=-tx*sin(rads) + tz*cos(rads);
    }
    //rotation over z
    //tx=x*cos + y*sin
    //ty=-x*sin + y*cos
    //tz=z

    if(axis==2)
    {
        point[0]=tx*cos(rads) + ty*sin(rads);
        point[1]=-tx*sin(rads) + ty*cos(rads);
    }


}

//Name: CreateSphere
//Function: Creates a sphere acording to the number of slices and slice resolution indicated
//          through the parameters.
//Conditions: num_slices must be >= 2
//Result: if num_slices>=2 A list of triangles, or else, NULL
List* CreateSphere(float* center, float radious, int num_slices, int slice_resolution, int group_id)
{
	List* sphere;
    List* points;
    float* pt;
    int slice;
    int section;
    float x_rads;
    float y_rads;

    if(num_slices<2)
        return NULL;


    x_rads=PI/num_slices;
    y_rads=2*PI/slice_resolution;

    sphere=list_new();

    points=list_new();

    //first point, on top
    list_add(points,list_new());
    pt=point(0,0,0);
    pt[1]=pt[1]+radious;
    list_add(list_get(points,0),pt);

    for(slice=1;slice<=num_slices;++slice)
    {
        float* npt=point(pt[0],pt[1],pt[2]);

        //rotate the topmost point x_rads*slice rads
        rotate(npt,x_rads*slice,0);


        list_add(points,list_new());

        for(section=0;section<slice_resolution;++section)
        {
            float* nnpt=point(npt[0],npt[1],npt[2]);

            rotate(nnpt,y_rads*section,1);

            list_add(list_get(points,slice),nnpt);
        }

    }

    //last point, botton
    pt=point(0,0,0);
    pt[1]=pt[1]-radious;
    list_add(list_get(points,num_slices),pt);

    //We now got all the points, it's time to stitch them together and create the triangles

    for(slice=1;slice<=num_slices;++slice)
    {
        for(section=0;section<slice_resolution;++section)
        {
            Triangle* tr;
            Triangle* tr2;
            float* pt1; //left,top
            float* pt2; //right,top
            float* pt3; //right,bottom
            float* pt4; //left,bottom



            if(slice==1)
            {
                pt2=pt1=(float*)list_get(list_get(points,slice-1),0);
            }
            else
            {
                pt1=(float*)list_get(list_get(points,slice-1),section);
                if(section<slice_resolution-1)
                {
                    pt2=(float*)list_get(list_get(points,slice-1),section+1);
                }
                else
                {
                    pt2=(float*)list_get(list_get(points,slice-1),0);
                }
            }

            if(section<slice_resolution-1)
            {
                pt3=(float*)list_get(list_get(points,slice),section+1);
            }
            else
            {
                pt3=(float*)list_get(list_get(points,slice),0);
            }

            pt4=(float*)list_get(list_get(points,slice),section);



            if(slice>1 && slice<num_slices)
            {
                tr=triangle_new();
                tr2=triangle_new();

                V_COPY(tr->v1,pt1);
                V_COPY(tr->v2,pt2);
                V_COPY(tr->v3,pt3);

                V_COPY(tr2->v1,pt1);
                V_COPY(tr2->v2,pt3);
                V_COPY(tr2->v3,pt4);

                tr->group_id=group_id;
                tr2->group_id=group_id;
                list_add(sphere,tr);
                list_add(sphere,tr2);
            }
            else if(slice==1)
            {
                tr=triangle_new();
                V_COPY(tr->v1,pt1);
                V_COPY(tr->v2,pt3);
                V_COPY(tr->v3,pt4);
                tr->group_id=group_id;
                list_add(sphere,tr);
            }
            else if(slice==num_slices)
            {
                tr=triangle_new();
                V_COPY(tr->v1,pt1);
                V_COPY(tr->v2,pt2);
                V_COPY(tr->v3,pt4);
                tr->group_id=group_id;
                list_add(sphere,tr);
            }
        }
    }



    while(points->count>0)
    {
        List* sl;
        sl=list_get(points,0);
        list_delete(sl,TRUE);
        list_remove(points,0,FALSE);
    }

    Translate(center,sphere);
    return sphere;
}

Triangle* box_create_triangle(float* pt1, float* pt2, float* pt3, int group_id)
{
    Triangle* tr;
    tr=triangle_new();
    V_COPY(tr->v1,pt1);
    V_COPY(tr->v2,pt2);
    V_COPY(tr->v3,pt3);
    tr->group_id=group_id;
    return tr;
}

void box_add_face(List* box, List*points, int pa, int pb, int pc, int pd, int group_id)
{
    list_add(box,box_create_triangle(list_get(points,pa),list_get(points,pc),list_get(points,pb),group_id));
    list_add(box,box_create_triangle(list_get(points,pa),list_get(points,pd),list_get(points,pc),group_id));
}

List* CreateBox(float* center, float* dims, int group_id)
{
    List* box;
    List* points;
    float pt[3];
    
    box=list_new();
    points=list_new();
    
    pt[0]=dims[0]/2;
    pt[1]=dims[1]/2;
    pt[2]=dims[2]/2;

    list_add(points,point(-pt[0], pt[1],-pt[2]));
    list_add(points,point( pt[0], pt[1],-pt[2]));
    list_add(points,point( pt[0],-pt[1],-pt[2]));
    list_add(points,point(-pt[0],-pt[1],-pt[2]));
    
    list_add(points,point(-pt[0], pt[1], pt[2]));
    list_add(points,point( pt[0], pt[1], pt[2]));
    list_add(points,point( pt[0],-pt[1], pt[2]));
    list_add(points,point(-pt[0],-pt[1], pt[2]));
    

    //front
    box_add_face(box,points,0,1,2,3,group_id);
    //top
    box_add_face(box,points,4,5,1,0,group_id);
    //left
    box_add_face(box,points,4,0,3,7,group_id);
    //right
    box_add_face(box,points,1,5,6,2,group_id);
    //bottom
    box_add_face(box,points,3,2,6,7,group_id);
    //back
    box_add_face(box,points,5,4,7,6,group_id);

    list_delete(points,TRUE);

    Translate(center,box);
    return box;
}

#if !defined(RENDERER)
#define RENDERER

#include "globals.h"
#include "list.h"

#include "primitives.h"
/*
#define OBJ_NULL		0
#define OBJ_SPHERE		1
#define OBJ_TRIANGLE	2
#define OBJ_SKYDOME		3
*/

#define MAX_DEPTH	10

#define AIR_INDEX 1.000292f
#define GLASS_INDEX 1.51714f

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2



#define BV_RAMA 0
#define BV_HOJA 1

#define EPSILON 0.001
#define V_CROSS(dest,v1,v2)dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define V_DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define V_SUB(dest,v1,v2)dest[0]=v1[0]-v2[0]; dest[1]=v1[1]-v2[1];dest[2]=v1[2]-v2[2];
#define V_ADD(dest,v1,v2)dest[0]=v1[0]+v2[0]; dest[1]=v1[1]+v2[1];dest[2]=v1[2]+v2[2];
#define V_SIZE(v1) (sqrt(v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2]))
#define V_MUL(v1,m)v1[0]=v1[0]*m; v1[1]=v1[1]*m;v1[2]=v1[2]*m;
#define V_DIV(v1,d)v1[0]=v1[0]/d; v1[1]=v1[1]/d;v1[2]=v1[2]/d;
#define V_INIT(v,x,y,z)v[0]=x;v[1]=y;v[2]=z;
#define V_REC(v1,v2)v1[0]=1/v2[0]; v1[1]=1/v2[1];v1[2]=1/v2[2];
#define V_COPY(dest,src)dest[0]=src[0]; dest[1]=src[1]; dest[2]=src[2];


//align(ALIGMENT)
//typedef struct
//{
//	float t;
//	float u;
//	float v;
//	float w;
//} Vector;
//
//align(ALIGMENT)
//typedef struct
//{
//	float a;
//	float r;
//	float g;
//	float b;
//} Color;




/*
align(ALIGMENT)
typedef struct
{
    int type;
    int group_id;
    float radious;
    int id;
	float v1[3];//x,y,z
	float v2[3];
	float v3[3];
	float normal[3];
} Object3D;
*/



align(ALIGMENT)
typedef struct
{
	float origen[3];
	float direccion[3];
} Ray;

align(ALIGMENT)
typedef struct
{
	int id_objeto;
	float dist;
	int hit;
	float refraction_ant;
	float color[4];
} TraceResult;

align(ALIGMENT)
typedef struct
{
    Group *groups;
    Material *materials;
    //Object3D *objects;
    Triangle *objects;
    Light *lights;
    Camera* cameras;
    int num_groups;
    int num_materials;
    int num_objects;
    int num_cameras;
    int num_lights;
} Escena;

align(ALIGMENT)
typedef struct
{
	List *groups;
	List *materials;
	List *objects;
	List *lights;
	List *cameras;
} Scene;

align(ALIGMENT)
typedef struct
{
	int *buffer;
	int width;
	int height;
	int num_threads;
	int num_blocks;
	int sector_y;
	int sector_x;
	int sector_height;
	int sector_width;
	int interactive;
	int verbose;
	int path_samples;
	int threads;
    int run_script;
    char* img_file;
	char* lua_script;

} RenderJob;


void RenderFrame(int* buffer, int threads);
void CleanRenderer();
void PreprocessObjects();
void CreateObjects(int qty);

align(ALIGMENT) extern int *buffer;
align(ALIGMENT) extern int bpp;
align(ALIGMENT) extern RenderJob job;
align(ALIGMENT) extern Escena escena;
align(ALIGMENT) extern void convertscene(Scene *scene, Escena *nscene);

#endif

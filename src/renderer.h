#if !defined(RENDERER)
#define RENDERER

#include "globals.h"

#define OBJ_NULO		0
#define OBJ_ESFERA		1
#define OBJ_TRIANGULO	2
#define OBJ_SKYDOME		3

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


//align(16)
//typedef struct
//{
//	float t;
//	float u;
//	float v;
//	float w;
//} Vector;
//
//align(16)
//typedef struct
//{
//	float a;
//	float r;
//	float g;
//	float b;
//} Color;

align(16)
typedef struct
{
	float lefttop[3];
	float leftbottom[3];
	float righttop[3];
	float eye[3];
	int id;
	int pad1;
	int pad2;
	int pad3;
} Camara;

align(16)
typedef struct
{
    float posicion[3];
    float color[4];
    float intensidad;
    int id;
    int pad1;
	int pad2;
} Luz;

align(16)
typedef struct
{
    int id;
    float refraccion;
    float reflexion;
    float specular;
    int textura;
    int* ptr_textura;
    int txt_width;
    int txt_height;
    float color[4];
} Material;

align(16)
typedef struct
{
	int id;
	int id_material;
	int pad1;
	int pad2;
} Grupo;

align(16)
typedef struct
{
    int tipo;
    int id_grupo;
    float radio;
    int id;
	float v1[3];//x,y,z
	float v2[3];
	float v3[3];
	float normal[3];
} Objeto3D;

align(16)
typedef struct
{
	float origen[3];
	float direccion[3];
} Ray;

align(16)
typedef struct
{
	int id_objeto;
	float dist;
	int hit;
	float refraccion_ant;
	float color[4];
} TraceResult;

align(16)
typedef struct
{
	Grupo *grupos;
	Material *materiales;
	Objeto3D *objetos;
	Luz *luces;
	Camara* camaras;
	int num_grupos;
	int num_materiales;
	int num_objetos;
	int num_camaras;
	int num_luces;
} Escena;

align(16)
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
	char* img_file;
	char* lua_script;
} RenderJob;

void RenderFrame(int* buffer, int threads);
void CleanRenderer();
void PreprocessObjects();
void CreateObjects(int qty);

align(16) extern int *buffer;
align(16) extern int bpp;
align(16) extern RenderJob job;
align(16) extern Escena escena;

#endif

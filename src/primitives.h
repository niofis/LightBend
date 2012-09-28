#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "globals.h"
#include "list.h"

align(ALIGMENT)
typedef struct
{
    float x;
    float y;
    float z;
} Vector;


align(ALIGMENT)
typedef struct
{
    float a;
    float r;
    float g;
    float b;
} Color;

align(ALIGMENT)
typedef struct
{
    int id;
    float refraction;
    float reflection;
    float specular;
    int textura;
    int* ptr_textura;
    int txt_width;
    int txt_height;
    float color[4];
} Material;

align(ALIGMENT)
typedef struct
{
    int id;
    int material_id;
    int pad1;
    int pad2;
} Group;

align(ALIGMENT)
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
} Camera;

align(ALIGMENT)
typedef struct
{
    float position[3];
    float color[4];
    float intensity;
    int id;
    int pad1;
    int pad2;
} Light;

align(ALIGMENT)
typedef struct
{
    int group_id;
    float v1[3];//x,y,z
    float v2[3];
    float v3[3];
    float normal[3];
} Triangle;


Triangle* triangle_new();


#endif // PRIMITIVES_H

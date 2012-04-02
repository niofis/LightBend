
#include "globals.h"
#include "renderer.h"
#include "bvh.h"
#include "demos.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
//#include "luajit.h"
#ifdef __cplusplus
}
#endif

//Para no cambiar la forma en que lua maneja los indices en las tablas
//cada vez que un indice es cargado a cRT se resta 1, para cambiarlo a base cero
//lua: doneLoading()
static int doneLoading(lua_State *L)
{
	BuildBVH();
	PreprocessObjects();
	return 0;
}

//lua: setGroup(id_group,id_material)
static int setGroup(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=lua_tonumber(L, 2)-1;
	return 0;
}

//lua: setMaterial(id_material,color_a,color_r,color_g,color_b,reflexion,refraccion,specular)
static int setMaterial(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	//207, 181, 59
	//azul
	escena.materiales[i].id=i;
	escena.materiales[i].color[0]=lua_tonumber(L, 2);
	escena.materiales[i].color[1]=lua_tonumber(L, 3);	//Old Gold
	escena.materiales[i].color[2]=lua_tonumber(L, 4);
	escena.materiales[i].color[3]=lua_tonumber(L, 5);
	escena.materiales[i].reflexion=lua_tonumber(L, 6);
	escena.materiales[i].refraccion=lua_tonumber(L, 7);
	escena.materiales[i].specular=lua_tonumber(L, 8);
	escena.materiales[i].ptr_textura=0;	
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;
	return 0;
}

//lua: setLight(id_light,color_a,color_r,color_g,color_b,intensidad,x,y,z)
static int setLight(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	escena.luces[i].id=i;
	escena.luces[i].color[0]=lua_tonumber(L, 2);
	escena.luces[i].color[1]=lua_tonumber(L, 3);
	escena.luces[i].color[2]=lua_tonumber(L, 4);
	escena.luces[i].color[3]=lua_tonumber(L, 5);
	escena.luces[i].intensidad=lua_tonumber(L, 6);
	escena.luces[i].posicion[0]=lua_tonumber(L, 7);
	escena.luces[i].posicion[1]=lua_tonumber(L, 8);
	escena.luces[i].posicion[2]=lua_tonumber(L, 9);
	return 0;
}

//lua: setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
static int setCamera(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	escena.camaras[i].eye[0]=lua_tonumber(L, 2);
	escena.camaras[i].eye[1]=lua_tonumber(L, 3);
	escena.camaras[i].eye[2]=lua_tonumber(L, 4);

	escena.camaras[i].lefttop[0]=lua_tonumber(L, 5);
	escena.camaras[i].lefttop[1]=lua_tonumber(L, 6);
	escena.camaras[i].lefttop[2]=lua_tonumber(L, 7);

	escena.camaras[i].righttop[0]=lua_tonumber(L, 8);
	escena.camaras[i].righttop[1]=lua_tonumber(L, 9);
	escena.camaras[i].righttop[2]=lua_tonumber(L, 10);

	escena.camaras[i].leftbottom[0]=lua_tonumber(L, 11);
	escena.camaras[i].leftbottom[1]=lua_tonumber(L, 12);
	escena.camaras[i].leftbottom[2]=lua_tonumber(L, 13);
	return 0;
}

//lua: setSphere(id_object,id_group,radio,x,y,z)
static int setSphere(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	escena.objetos[i].id=i;
	escena.objetos[i].id_grupo=lua_tonumber(L, 2)-1;
	escena.objetos[i].radio=lua_tonumber(L, 3);
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=lua_tonumber(L, 4);
	escena.objetos[i].v1[1]=lua_tonumber(L, 5);
	escena.objetos[i].v1[2]=lua_tonumber(L, 6);
	return 0;
}

//lua: setTriangle(id_object,id_group,radio,x1,y1,z1,x2,y2,z2,x3,y3,z3)
static int setTriangle(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	escena.objetos[i].id_grupo=lua_tonumber(L, 2)-1;
	escena.objetos[i].id=i;
	escena.objetos[i].tipo=OBJ_TRIANGULO;
	V_INIT(escena.objetos[i].v1,lua_tonumber(L, 3),lua_tonumber(L, 4),lua_tonumber(L, 5));
	V_INIT(escena.objetos[i].v2,lua_tonumber(L, 6),lua_tonumber(L, 7),lua_tonumber(L, 8));
	V_INIT(escena.objetos[i].v3,lua_tonumber(L, 9),lua_tonumber(L,10),lua_tonumber(L,11));
	return 0;
}

//lua: initScene(num_camaras,num_luces,num_materiales,num_grupos,num_objetos)
static int initScene(lua_State *L)
{
	//Para inicializar la cantidad de objetos, camaras, luces, materiales y grupos
	escena.num_camaras=lua_tonumber(L, 1);
	escena.num_luces=lua_tonumber(L, 2);
	escena.num_materiales=lua_tonumber(L, 3);
	escena.num_grupos=lua_tonumber(L, 4);
	escena.num_objetos=lua_tonumber(L, 5);

	escena.camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*escena.num_camaras);
	escena.luces=(Luz*)aligned_malloc(16,sizeof(Luz)*escena.num_luces);
	escena.materiales=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materiales);
	escena.grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*escena.num_grupos);
	escena.objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*escena.num_objetos);

	return 0;
}

static int loadModel(lua_State *L)
{

	lua_pushnumber(L,1); //return number of triangles
	return 1;
}

static const luaL_reg cRTlib[] = {
{"initScene",   initScene},
{"setTriangle",   setTriangle},
{"setSphere",   setSphere},
{"setCamera",   setCamera},
{"setLight",   setLight},
{"setMaterial",   setMaterial},
{"setGroup",   setGroup},
{"doneLoading",doneLoading},
{NULL, NULL}
};


void runluascript(char* script_file)
{
	lua_State *L = lua_open();

    // load the libs
    luaL_openlibs(L);
	luaL_register(L, "cRT", cRTlib);

    //run a Lua scrip here
    if(luaL_dofile(L,script_file))
	{
		printf("%s\n", lua_tostring(L, -1));
		printf("loading demo 1\n");
		Demo1();
	}

    lua_close(L);

}

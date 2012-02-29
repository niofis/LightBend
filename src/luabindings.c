
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
	grupos[i].id=i;
	grupos[i].id_material=lua_tonumber(L, 2)-1;
	return 0;
}

//lua: setMaterial(id_material,color_a,color_r,color_g,color_b,reflexion,refraccion,specular)
static int setMaterial(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	//207, 181, 59
	//azul
	materiales[i].id=i;
	materiales[i].color[0]=lua_tonumber(L, 2);
	materiales[i].color[1]=lua_tonumber(L, 3);	//Old Gold
	materiales[i].color[2]=lua_tonumber(L, 4);
	materiales[i].color[3]=lua_tonumber(L, 5);
	materiales[i].reflexion=lua_tonumber(L, 6);
	materiales[i].refraccion=lua_tonumber(L, 7);
	materiales[i].specular=lua_tonumber(L, 8);
	materiales[i].ptr_textura=0;	
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;
	return 0;
}

//lua: setLight(id_light,color_a,color_r,color_g,color_b,intensidad,x,y,z)
static int setLight(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	luces[i].id=i;
	luces[i].color[0]=lua_tonumber(L, 2);
	luces[i].color[1]=lua_tonumber(L, 3);
	luces[i].color[2]=lua_tonumber(L, 4);
	luces[i].color[3]=lua_tonumber(L, 5);
	luces[i].intensidad=lua_tonumber(L, 6);
	luces[i].posicion[0]=lua_tonumber(L, 7);
	luces[i].posicion[1]=lua_tonumber(L, 8);
	luces[i].posicion[2]=lua_tonumber(L, 9);
	return 0;
}

//lua: setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
static int setCamera(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	camaras[i].eye[0]=lua_tonumber(L, 2);
	camaras[i].eye[1]=lua_tonumber(L, 3);
	camaras[i].eye[2]=lua_tonumber(L, 4);

	camaras[i].lefttop[0]=lua_tonumber(L, 5);
	camaras[i].lefttop[1]=lua_tonumber(L, 6);
	camaras[i].lefttop[2]=lua_tonumber(L, 7);

	camaras[i].righttop[0]=lua_tonumber(L, 8);
	camaras[i].righttop[1]=lua_tonumber(L, 9);
	camaras[i].righttop[2]=lua_tonumber(L, 10);

	camaras[i].leftbottom[0]=lua_tonumber(L, 11);
	camaras[i].leftbottom[1]=lua_tonumber(L, 12);
	camaras[i].leftbottom[2]=lua_tonumber(L, 13);
	return 0;
}

//lua: setSphere(id_object,id_group,radio,x,y,z)
static int setSphere(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	objetos[i].id=i;
	objetos[i].id_grupo=lua_tonumber(L, 2)-1;
	objetos[i].radio=lua_tonumber(L, 3);
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=lua_tonumber(L, 4);
	objetos[i].v1[1]=lua_tonumber(L, 5);
	objetos[i].v1[2]=lua_tonumber(L, 6);
	return 0;
}

//lua: setTriangle(id_object,id_group,radio,x1,y1,z1,x2,y2,z2,x3,y3,z3)
static int setTriangle(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	objetos[i].id_grupo=lua_tonumber(L, 2)-1;
	objetos[i].id=i;
	objetos[i].tipo=OBJ_TRIANGULO;
	V_INIT(objetos[i].v1,lua_tonumber(L, 3),lua_tonumber(L, 4),lua_tonumber(L, 5));
	V_INIT(objetos[i].v2,lua_tonumber(L, 6),lua_tonumber(L, 7),lua_tonumber(L, 8));
	V_INIT(objetos[i].v3,lua_tonumber(L, 9),lua_tonumber(L,10),lua_tonumber(L,11));
	return 0;
}

//lua: initScene(num_camaras,num_luces,num_materiales,num_grupos,num_objetos)
static int initScene(lua_State *L)
{
	//Para inicializar la cantidad de objetos, camaras, luces, materiales y grupos
	num_camaras=lua_tonumber(L, 1);
	num_luces=lua_tonumber(L, 2);
	num_materiales=lua_tonumber(L, 3);
	num_grupos=lua_tonumber(L, 4);
	num_objetos=lua_tonumber(L, 5);

	camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*num_camaras);
	luces=(Luz*)aligned_malloc(16,sizeof(Luz)*num_luces);
	materiales=(Material*)aligned_malloc(16,sizeof(Material)*num_materiales);
	grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*num_grupos);
	objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);

	return 0;
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


void runluascript()
{
	lua_State *L = lua_open();

    // load the libs
    luaL_openlibs(L);
	luaL_register(L, "cRT", cRTlib);

    //run a Lua scrip here
    if(luaL_dofile(L,"script.lua"))
	{
		printf("%s\n", lua_tostring(L, -1));
		printf("loading demo 1\n");
		Demo1();
	}

    lua_close(L);

}

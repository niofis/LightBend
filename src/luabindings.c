
#include "globals.h"
#include "renderer.h"
#include "bvh.h"
#include "demos.h"
#include "models.h"

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

Scene lua_scene;

//Para no cambiar la forma en que lua maneja los indices en las tablas
//cada vez que un indice es cargado a lightbend se resta 1, para cambiarlo a base cero
//lua: doneLoading()
static int doneLoading(lua_State *L)
{
	BuildBVH();
	PreprocessObjects();
	return 0;
}

//lua: setGroup(id_group,material_id)
static int setGroup(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    escena.groups[i].id=i;
    escena.groups[i].material_id=lua_tonumber(L, 2)-1;
	return 0;
}

//lua: setMaterial(material_id,color_a,color_r,color_g,color_b,reflexion,refraccion,specular)
static int setMaterial(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
	//207, 181, 59
	//azul
    escena.materials[i].id=i;
    escena.materials[i].color[0]=lua_tonumber(L, 2);
    escena.materials[i].color[1]=lua_tonumber(L, 3);	//Old Gold
    escena.materials[i].color[2]=lua_tonumber(L, 4);
    escena.materials[i].color[3]=lua_tonumber(L, 5);
    escena.materials[i].reflexion=lua_tonumber(L, 6);
    escena.materials[i].refraccion=lua_tonumber(L, 7);
    escena.materials[i].specular=lua_tonumber(L, 8);
    escena.materials[i].ptr_textura=0;
    escena.materials[i].textura=0;
    escena.materials[i].txt_height=0;
    escena.materials[i].txt_width=0;
	return 0;
}

//lua: setLight(id_light,color_a,color_r,color_g,color_b,intensidad,x,y,z)
static int setLight(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    escena.lights[i].id=i;
    escena.lights[i].color[0]=lua_tonumber(L, 2);
    escena.lights[i].color[1]=lua_tonumber(L, 3);
    escena.lights[i].color[2]=lua_tonumber(L, 4);
    escena.lights[i].color[3]=lua_tonumber(L, 5);
    escena.lights[i].intensidad=lua_tonumber(L, 6);
    escena.lights[i].posicion[0]=lua_tonumber(L, 7);
    escena.lights[i].posicion[1]=lua_tonumber(L, 8);
    escena.lights[i].posicion[2]=lua_tonumber(L, 9);
	return 0;
}

//lua: setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
static int setCamera(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    escena.cameras[i].eye[0]=lua_tonumber(L, 2);
    escena.cameras[i].eye[1]=lua_tonumber(L, 3);
    escena.cameras[i].eye[2]=lua_tonumber(L, 4);

    escena.cameras[i].lefttop[0]=lua_tonumber(L, 5);
    escena.cameras[i].lefttop[1]=lua_tonumber(L, 6);
    escena.cameras[i].lefttop[2]=lua_tonumber(L, 7);

    escena.cameras[i].righttop[0]=lua_tonumber(L, 8);
    escena.cameras[i].righttop[1]=lua_tonumber(L, 9);
    escena.cameras[i].righttop[2]=lua_tonumber(L, 10);

    escena.cameras[i].leftbottom[0]=lua_tonumber(L, 11);
    escena.cameras[i].leftbottom[1]=lua_tonumber(L, 12);
    escena.cameras[i].leftbottom[2]=lua_tonumber(L, 13);
	return 0;
}

//lua: setSphere(id_object,id_group,radio,x,y,z)
static int setSphere(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    escena.objects[i].id=i;
    escena.objects[i].group_id=lua_tonumber(L, 2)-1;
    escena.objects[i].radio=lua_tonumber(L, 3);
    escena.objects[i].tipo=OBJ_SPHERE;
    escena.objects[i].v1[0]=lua_tonumber(L, 4);
    escena.objects[i].v1[1]=lua_tonumber(L, 5);
    escena.objects[i].v1[2]=lua_tonumber(L, 6);
	return 0;
}

//lua: setTriangle(id_object,id_group,radio,x1,y1,z1,x2,y2,z2,x3,y3,z3)
static int setTriangle(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    escena.objects[i].group_id=lua_tonumber(L, 2)-1;
    escena.objects[i].id=i;
    escena.objects[i].tipo=OBJ_TRIANGLE;
    V_INIT(escena.objects[i].v1,lua_tonumber(L, 3),lua_tonumber(L, 4),lua_tonumber(L, 5));
    V_INIT(escena.objects[i].v2,lua_tonumber(L, 6),lua_tonumber(L, 7),lua_tonumber(L, 8));
    V_INIT(escena.objects[i].v3,lua_tonumber(L, 9),lua_tonumber(L,10),lua_tonumber(L,11));
	return 0;
}

//lua: initScene(num_cameras,num_lights,num_materials,num_groups,num_objects)
static int initScene(lua_State *L)
{
    /*
    //Para inicializar la cantidad de objects, cameras, lights, materials y groups
    escena.num_cameras=lua_tonumber(L, 1);
    escena.num_lights=lua_tonumber(L, 2);
    escena.num_materials=lua_tonumber(L, 3);
    escena.num_groups=lua_tonumber(L, 4);
    escena.num_objects=lua_tonumber(L, 5);

    escena.cameras=(Camera*)aligned_malloc(16,sizeof(Camera)*escena.num_cameras);
    escena.lights=(Light*)aligned_malloc(16,sizeof(Light)*escena.num_lights);
    escena.materials=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materials);
    escena.groups=(Group*)aligned_malloc(16,sizeof(Group)*escena.num_groups);
    escena.objects=(Object3D*)aligned_malloc(16,sizeof(Object3D)*escena.num_objects);
    */

    lua_scene.cameras=list_create();
    lua_scene.groups=list_create();
    lua_scene.lights=list_create();
    lua_scene.meterials=list_create();
    lua_scene.objects=list_create();



	return 0;
}

static int loadModel(lua_State *L)
{

    char *file=lua_tostring(L,1);
    int i;
    int j;
    int k;
    struct aiScene* model=importmodel(file);

    lua_scene.cameras=list_create();
    lua_scene.groups=list_create();
    lua_scene.lights=list_create();
    lua_scene.meterials=list_create();
    lua_scene.objects=list_create();

    //get model into scene

    //model->
    if(model)
    {
        printf("Num Meshes: %d\n",model->mNumMeshes);
        for(i=0;i<model->mNumMeshes;++i)
        {
            struct aiMesh* m=model->mMeshes[i];
            Group *g=(Group *) aligned_malloc(ALIGMENT,sizeof(Group));
            g->id=1;
            list_add(lua_scene.groups,g);

            printf("Mesh %d Faces: %d\n",i,m->mNumFaces );
            for(j=0;j<m->mNumFaces;++j)
            {
                struct aiFace f=m->mFaces[j];
                Object3D *obj=aligned_malloc(ALIGMENT,sizeof(Object3D));
                printf("Face %d Vertices: %d\n",j,f.mNumIndices);
            }
        }
    }



    freemodel(model);

    return 0;
}

static const luaL_reg lightbendlib[] = {
{"initScene",   initScene},
{"setTriangle",   setTriangle},
{"setSphere",   setSphere},
{"setCamera",   setCamera},
{"setLight",   setLight},
{"setMaterial",   setMaterial},
{"setGroup",   setGroup},
{"loadModel",loadModel},
{"doneLoading",doneLoading},
{NULL, NULL}
};


void runluascript(char* script_file)
{
	lua_State *L = lua_open();

    // load the libs
    luaL_openlibs(L);
    luaL_register(L, "lightbend", lightbendlib);

    //run a Lua scrip here
    if(luaL_dofile(L,script_file))
	{
		printf("%s\n", lua_tostring(L, -1));
		printf("loading demo 1\n");
		Demo1();
	}

    lua_close(L);

}

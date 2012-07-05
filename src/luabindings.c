
#include "globals.h"
#include "renderer.h"
#include "bvh.h"
#include "demos.h"
#include "models.h"
#include "solids.h"

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
    

    convertscene(&lua_scene, NULL);

    list_delete(lua_scene.cameras,TRUE);
    list_delete(lua_scene.groups,TRUE);
    list_delete(lua_scene.lights,TRUE);
    list_delete(lua_scene.materials,TRUE);
    list_delete(lua_scene.objects,TRUE);

	BuildBVH();
	PreprocessObjects();
	return 0;
}

//lua: setGroup(id_group,material_id)
static int setGroup(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    Group *g=(Group *) aligned_malloc(ALIGMENT,sizeof(Group));
    g->id=i;
    g->material_id=lua_tonumber(L, 2)-1;
    list_add(lua_scene.groups,g);
	return 0;
}

//lua: setMaterial(material_id,color_a,color_r,color_g,color_b,reflection,refraction,specular)
static int setMaterial(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    Material *m=(Material *) aligned_malloc(ALIGMENT,sizeof(Material));
	//207, 181, 59
	//azul
    m->id=i;
    m->color[0]=lua_tonumber(L, 2);
    m->color[1]=lua_tonumber(L, 3);	//Old Gold
    m->color[2]=lua_tonumber(L, 4);
    m->color[3]=lua_tonumber(L, 5);
    m->reflection=lua_tonumber(L, 6);
    m->refraction=lua_tonumber(L, 7);
    m->specular=lua_tonumber(L, 8);
    m->ptr_textura=0;
    m->textura=0;
    m->txt_height=0;
    m->txt_width=0;
    list_add(lua_scene.materials,m);
	return 0;
}

//lua: setLight(id_light,color_a,color_r,color_g,color_b,intensity,x,y,z)
static int setLight(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    /*
    escena.lights[i].id=i;
    escena.lights[i].color[0]=lua_tonumber(L, 2);
    escena.lights[i].color[1]=lua_tonumber(L, 3);
    escena.lights[i].color[2]=lua_tonumber(L, 4);
    escena.lights[i].color[3]=lua_tonumber(L, 5);
    escena.lights[i].intensity=lua_tonumber(L, 6);
    escena.lights[i].position[0]=lua_tonumber(L, 7);
    escena.lights[i].position[1]=lua_tonumber(L, 8);
    escena.lights[i].position[2]=lua_tonumber(L, 9);
    */

    Light *li=(Light *) aligned_malloc(ALIGMENT,sizeof(Light));
    li->id=i;
    li->color[0]=lua_tonumber(L, 2);
    li->color[1]=lua_tonumber(L, 3);
    li->color[2]=lua_tonumber(L, 4);
    li->color[3]=lua_tonumber(L, 5);
    li->intensity=lua_tonumber(L, 6);
    li->position[0]=lua_tonumber(L, 7);
    li->position[1]=lua_tonumber(L, 8);
    li->position[2]=lua_tonumber(L, 9);
    list_add(lua_scene.lights,li);


	return 0;
}

//lua: setCamera(id_camera,eye_x,eye_y,eye_z,lt_x,lt_y,lt_z,rt_x,rt_y,rt_z,lb_x,lb_y,lb_z)
static int setCamera(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    Camera *cam=(Camera *)aligned_malloc(ALIGMENT,sizeof(Camera));
    cam->eye[0]=lua_tonumber(L, 2);
    cam->eye[1]=lua_tonumber(L, 3);
    cam->eye[2]=lua_tonumber(L, 4);

    cam->lefttop[0]=lua_tonumber(L, 5);
    cam->lefttop[1]=lua_tonumber(L, 6);
    cam->lefttop[2]=lua_tonumber(L, 7);

    cam->righttop[0]=lua_tonumber(L, 8);
    cam->righttop[1]=lua_tonumber(L, 9);
    cam->righttop[2]=lua_tonumber(L, 10);

    cam->leftbottom[0]=lua_tonumber(L, 11);
    cam->leftbottom[1]=lua_tonumber(L, 12);
    cam->leftbottom[2]=lua_tonumber(L, 13);

    list_add(lua_scene.cameras,cam);

	return 0;
}

//lua: setSphere(id_object,id_group,radious,x,y,z)
static int setSphere(lua_State *L)
{
    int group_id=lua_tonumber(L, 2)-1;
    float center[3];
    float radious=lua_tonumber(L, 3);
    float slices=lua_tonumber(L,7);
    float resolution=lua_tonumber(L,8);
    List* sphere;

    center[0]=lua_tonumber(L,4);
    center[1]=lua_tonumber(L,5);
    center[2]=lua_tonumber(L,6);

    sphere=CreateSphere(&center,radious,slices,resolution,group_id);

    list_append(lua_scene.objects,sphere);

    list_delete(sphere,FALSE);


    //Triangle *obj=(Triangle *)aligned_malloc(ALIGMENT,sizeof(Triangle));

    /*
    escena.objects[i].id=i;
    escena.objects[i].group_id=lua_tonumber(L, 2)-1;
    escena.objects[i].radious=lua_tonumber(L, 3);
    escena.objects[i].type=OBJ_SPHERE;
    escena.objects[i].v1[0]=lua_tonumber(L, 4);
    escena.objects[i].v1[1]=lua_tonumber(L, 5);
    escena.objects[i].v1[2]=lua_tonumber(L, 6);
    */


    //obj->group_id=lua_tonumber(L, 2)-1;
    //obj->id=i;
    //obj->type=OBJ_SPHERE;
    //obj->radious=lua_tonumber(L, 3);
    //obj->v1[0]=lua_tonumber(L, 4);
    //obj->v1[1]=lua_tonumber(L, 5);
    //obj->v1[2]=lua_tonumber(L, 6);

    //list_add(lua_scene.objects,obj);


	return 0;
}

//lua: setTriangle(id_object,id_group,radious,x1,y1,z1,x2,y2,z2,x3,y3,z3)
static int setTriangle(lua_State *L)
{
	int i=lua_tonumber(L, 1)-1;
    Triangle *obj=(Triangle *)aligned_malloc(ALIGMENT,sizeof(Triangle));

    obj->group_id=lua_tonumber(L, 2)-1;
    //obj->id=i;
    //obj->type=OBJ_TRIANGLE;

    V_INIT(obj->v1,lua_tonumber(L, 3),lua_tonumber(L, 4),lua_tonumber(L, 5));
    V_INIT(obj->v2,lua_tonumber(L, 6),lua_tonumber(L, 7),lua_tonumber(L, 8));
    V_INIT(obj->v3,lua_tonumber(L, 9),lua_tonumber(L,10),lua_tonumber(L,11));

    list_add(lua_scene.objects,obj);
	return 0;
}

//lua: initScene(num_cameras,num_lights,num_materials,num_groups,num_objects)
static int initScene(lua_State *L)
{
    lua_scene.cameras=list_create();
    lua_scene.groups=list_create();
    lua_scene.lights=list_create();
    lua_scene.materials=list_create();
    lua_scene.objects=list_create();
	return 0;
}

static int loadModel(lua_State *L)
{

    const char *file=lua_tostring(L,1);
    int i;
    int j;
    int k;
    struct aiScene* model=importmodel(file);
    int group_offset=lua_scene.groups->count;
    int material_offset=lua_scene.materials->count;

    //get model into scene

    //model->
    if(model)
    {
        //printf("Num Meshes: %d\n",model->mNumMeshes);
		//printf("Num Materials: %d\n",model->mNumMaterials);
		for(i=0;i<model->mNumMaterials;++i)
		{
			Material *m=(Material *) aligned_malloc(ALIGMENT,sizeof(Material));
			struct aiMaterial *ma=model->mMaterials[i];
			struct aiColor4D color;
			float ref;
			float rfl;
			float sp;

			aiGetMaterialColor(ma,AI_MATKEY_COLOR_DIFFUSE,&color);
			if(aiGetMaterialFloatArray(ma,AI_MATKEY_REFRACTI,&ref,(unsigned int*)0x0) != AI_SUCCESS)
				ref=1.0f;
			if(aiGetMaterialFloatArray(ma,AI_MATKEY_REFLECTIVITY,&rfl,(unsigned int*)0x0) != AI_SUCCESS)
				rfl=0.0f;
			if(aiGetMaterialFloatArray(ma,AI_MATKEY_SHININESS,&sp,(unsigned int*)0x0) != AI_SUCCESS)
				sp=0.0f;
			m->id=i+material_offset;
			m->color[0]=color.a;
			m->color[1]=color.r;
			m->color[2]=color.g;
			m->color[3]=color.b;
			m->refraction=ref;
			m->reflection=rfl;
			m->specular=sp;

			printf("refraction:%f reflection:%f color.a:%f\n",ref,rfl,color.a);

			list_add(lua_scene.materials,m);
			//printf("Material %d (%f,%f,%f,%f)\n",m->id,m->color[0],m->color[1],m->color[2],m->color[3]);
		}
        for(i=0;i<model->mNumMeshes;++i)
        {
            struct aiMesh* m=model->mMeshes[i];
            Group *g=(Group *) aligned_malloc(ALIGMENT,sizeof(Group));
            g->id=i+group_offset;
            g->material_id=m->mMaterialIndex+material_offset;
            list_add(lua_scene.groups,g);

            //printf("Mesh %d Faces: %d\n",i,m->mNumFaces );
            for(j=0;j<m->mNumFaces;++j)
            {
                struct aiFace f=m->mFaces[j];
                Triangle *obj=(Triangle *)aligned_malloc(ALIGMENT,sizeof(Triangle));
                obj->group_id=i+group_offset;
                //obj->id=j;
                //obj->type=OBJ_TRIANGLE;
                V_INIT(obj->v1,m->mVertices[f.mIndices[0]].x,m->mVertices[f.mIndices[0]].y,m->mVertices[f.mIndices[0]].z);
                V_INIT(obj->v2,m->mVertices[f.mIndices[1]].x,m->mVertices[f.mIndices[1]].y,m->mVertices[f.mIndices[1]].z);
                V_INIT(obj->v3,m->mVertices[f.mIndices[2]].x,m->mVertices[f.mIndices[2]].y,m->mVertices[f.mIndices[2]].z);
                //printf("Face %d Vertices: %d\n",j,f.mNumIndices);
				list_add(lua_scene.objects,obj);
			}
        }
		for(i=0;i<model->mNumLights;++i)
		{
			struct aiLight* l=model->mLights[i];
			Light *li=(Light *) aligned_malloc(ALIGMENT,sizeof(Light));
			li->id=i;
			V_INIT(li->position,l->mPosition.x,l->mPosition.y,l->mPosition.z);
			li->color[0]=1.0f;
			li->color[1]=l->mColorDiffuse.r;
			li->color[2]=l->mColorDiffuse.g;
			li->color[3]=l->mColorDiffuse.b;
			list_add(lua_scene.lights,li);
		}
    freemodel(model);



    }

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

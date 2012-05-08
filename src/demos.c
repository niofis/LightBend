#include "demos.h"
#include "MS3DFile.h"
#include "bvh.h"

void Demo1()
{
	int i=0;

	//Crear Camera
	escena.num_cameras=1;
	escena.cameras=(Camera*)aligned_malloc(16,sizeof(Camera)*escena.num_cameras);
	i=0;
	escena.cameras[0].eye[0]=0.0f;
	escena.cameras[0].eye[1]=0.0f;
	escena.cameras[0].eye[2]=-10.0f;

	escena.cameras[0].lefttop[0]=-3.2f;
	escena.cameras[0].lefttop[1]=2.4f;
	escena.cameras[0].lefttop[2]=-5.0f;

	escena.cameras[0].righttop[0]=3.2f;
	escena.cameras[0].righttop[1]=2.4f;
	escena.cameras[0].righttop[2]=-5.0f;

	escena.cameras[0].leftbottom[0]=-3.2f;
	escena.cameras[0].leftbottom[1]=-2.4f;
	escena.cameras[0].leftbottom[2]=-5.0f;

	//Crear Light
	escena.num_lights=1;
	escena.lights=(Light*)aligned_malloc(16,sizeof(Light)*escena.num_lights);
	i=0;
	escena.lights[i].color[0]=1.0f;
	escena.lights[i].color[1]=1.0f;
	escena.lights[i].color[2]=1.0f;
	escena.lights[i].color[3]=1.0f;
	escena.lights[i].intensity=100.0f;
	escena.lights[i].id=i;
	escena.lights[i].position[0]=0.0f;
	escena.lights[i].position[1]=2.0f;
	escena.lights[i].position[2]=-5.0f;


	//Crear Material
	escena.num_materials=3;
	escena.materials=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materials);
	i=0;
	//207, 181, 59
	//azul
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.811764f;	//Old Gold
	escena.materials[i].color[2]=0.709803f;
	escena.materials[i].color[3]=0.231372f;
	escena.materials[i].id=0;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	//rojo
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.811764f;
	escena.materials[i].color[2]=0.709803f;
	escena.materials[i].color[3]=0.231372f;
	escena.materials[i].id=0;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	//verde
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.811764f;
	escena.materials[i].color[2]=0.709803f;
	escena.materials[i].color[3]=0.231372f;
	escena.materials[i].id=0;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	escena.num_groups=3;
    escena.groups=(Group*)aligned_malloc(16,sizeof(Group)*escena.num_groups);
	i=0;
	escena.groups[i].id=i;
	escena.groups[i].material_id=0;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=1;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=2;
	

	escena.num_objects=3;
	escena.objects=(Object3D*)aligned_malloc(16,sizeof(Object3D)*escena.num_objects);
	i=0; 
	escena.objects[i].group_id=0;
	escena.objects[i].id=0;
	escena.objects[i].radious=1.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=0;
	escena.objects[i].v1[1]=0;
	escena.objects[i].v1[2]=0;
	i++;//1
	escena.objects[i].group_id=1;
	escena.objects[i].id=i;
	escena.objects[i].radious=1.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=0;
	escena.objects[i].v1[1]=2.12132f;
	escena.objects[i].v1[2]=0;
	i++;//2
	escena.objects[i].group_id=2;
	escena.objects[i].id=i;
	escena.objects[i].radious=1.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=0;
	escena.objects[i].v1[1]=-2.12132f;
	escena.objects[i].v1[2]=0;
	i++;
		
	//objects[i].group_id=0;
	//objects[i].id=i;
    //objects[i].type=OBJ_TRIANGLE;
	//V_INIT(objects[i].v1,-2.0f-2.0f,0-2.5f,0);
	//V_INIT(objects[i].v2,2.0f-2.0f,0-2.5f,0);
	//V_INIT(objects[i].v3,0.0f-2.0f,3.0f-2.5f,0);
	//i++; 

	//objects[i].group_id=1;
	//objects[i].id=i;
    //objects[i].type=OBJ_TRIANGLE;
	//V_INIT(objects[i].v1,-2.0f,0+3.0f-2.5f,0);
	//V_INIT(objects[i].v2,2.0f,0+3.0f-2.5f,0);
	//V_INIT(objects[i].v3,0.0f,3.0f+3.0f-2.5f,0);
	//i++; 

	//objects[i].group_id=2;
	//objects[i].id=i;
    //objects[i].type=OBJ_TRIANGLE;
	//V_INIT(objects[i].v1,-2.0f+2.0f,0-2.5f,0);
	//V_INIT(objects[i].v2,2.0f+2.0f,0-2.5f,0);
	//V_INIT(objects[i].v3,0.0f+2.0f,3.0f-2.5f,0);
	//i++; 

	BuildBVH();
	PreprocessObjects();

}

void Demo2()
{
	int i=0;

	//Crear Camera
	escena.num_cameras=1;
	escena.cameras=(Camera*)aligned_malloc(16,sizeof(Camera)*escena.num_cameras);
	i=0;
	escena.cameras[0].eye[0]=0.0f;
	escena.cameras[0].eye[1]=0.0f;
	escena.cameras[0].eye[2]=-10.0f;

	escena.cameras[0].lefttop[0]=-3.2f;
	escena.cameras[0].lefttop[1]=2.4f;
	escena.cameras[0].lefttop[2]=-5.0f;

	escena.cameras[0].righttop[0]=3.2f;
	escena.cameras[0].righttop[1]=2.4f;
	escena.cameras[0].righttop[2]=-5.0f;

	escena.cameras[0].leftbottom[0]=-3.2f;
	escena.cameras[0].leftbottom[1]=-2.4f;
	escena.cameras[0].leftbottom[2]=-5.0f;

	//Crear Light
	escena.num_lights=1;
	escena.lights=(Light*)aligned_malloc(16,sizeof(Light)*escena.num_lights);
	i=0;
	escena.lights[i].color[0]=1.0f;
	escena.lights[i].color[1]=1.0f;
	escena.lights[i].color[2]=1.0f;
	escena.lights[i].color[3]=1.0f;
	escena.lights[i].intensity=100.0f;
	escena.lights[i].id=i;
	escena.lights[i].position[0]=0.0f;
	escena.lights[i].position[1]=2.0f;
	escena.lights[i].position[2]=-5.0f;


	//Crear Material
	escena.num_materials=2;
	escena.materials=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materials);
	i=0;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.0f;
	escena.materials[i].color[2]=1.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=i;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.0f;
	escena.materials[i].color[2]=0.0f;
	escena.materials[i].color[3]=1.0f;
	escena.materials[i].id=i;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	escena.num_groups=2;
    escena.groups=(Group*)aligned_malloc(16,sizeof(Group)*escena.num_groups);
	i=0;
	escena.groups[i].id=i;
	escena.groups[i].material_id=0;
	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=1;

	

	//num_objects=2;
	//objects=(Object3D*)aligned_malloc(16,sizeof(Object3D)*num_objects);
	CreateObjects(2);
	i=0; 
	escena.objects[i].group_id=0;
	escena.objects[i].id=i;
	escena.objects[i].radious=10000.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=0.0f;
	escena.objects[i].v1[1]=-10000.0f;
	escena.objects[i].v1[2]=0.0f;

	// GEN_TRIANGULO eax + Object3D,mdos,zero,zero, dos,zero,zero, zero,tres,zero, 0
	i++; 
	escena.objects[i].group_id=1;
	escena.objects[i].id=i;
    escena.objects[i].type=OBJ_TRIANGLE;
	V_INIT(escena.objects[i].v1,-2.0f,0,0);
	V_INIT(escena.objects[i].v2,2.0f,0,0);
	V_INIT(escena.objects[i].v3,0.0f,3.0f,0);
	//V_SUB(objects[i].v2,objects[i].v2,objects[i].v1);
	//V_SUB(objects[i].v3,objects[i].v3,objects[i].v1);

	BuildBVH();
	PreprocessObjects();

}


void Demo3()
{
	int i=0;

	//Crear Camera
	escena.num_cameras=1;
	escena.cameras=(Camera*)aligned_malloc(16,sizeof(Camera)*escena.num_cameras);
	i=0;
	escena.cameras[0].eye[0]=0.0f;
	escena.cameras[0].eye[1]=0.0f;
	escena.cameras[0].eye[2]=-100.0f;

	escena.cameras[0].lefttop[0]=-3.2f;
	escena.cameras[0].lefttop[1]=2.4f;
	escena.cameras[0].lefttop[2]=-50.0f;

	escena.cameras[0].righttop[0]=3.2f;
	escena.cameras[0].righttop[1]=2.4f;
	escena.cameras[0].righttop[2]=-50.0f;

	escena.cameras[0].leftbottom[0]=-3.2f;
	escena.cameras[0].leftbottom[1]=-2.4f;
	escena.cameras[0].leftbottom[2]=-50.0f;

	//Crear Light
	escena.num_lights=1;
	escena.lights=(Light*)aligned_malloc(16,sizeof(Light)*escena.num_lights);
	i=0;
	escena.lights[i].color[0]=1.0f;
	escena.lights[i].color[1]=1.0f;
	escena.lights[i].color[2]=1.0f;
	escena.lights[i].color[3]=1.0f;
	escena.lights[i].intensity=100.0f;
	escena.lights[i].id=i;
	escena.lights[i].position[0]=0.0f;
	escena.lights[i].position[1]=2.0f;
	escena.lights[i].position[2]=-1.0f;

	//Crear Material
	escena.num_materials=6;
	escena.materials=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materials);
	i=0;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.0f;
	escena.materials[i].color[2]=1.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=i;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=0.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=1.0f;
	escena.materials[i].color[2]=1.0f;
	escena.materials[i].color[3]=1.0f;
	escena.materials[i].id=i;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=0.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=1.0f;
	escena.materials[i].color[2]=0.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=i;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=0.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.0f;
	escena.materials[i].color[2]=0.0f;
	escena.materials[i].color[3]=1.0f;
	escena.materials[i].id=i;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0.7f;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	escena.materials[i].color[0]=0.2f;
	escena.materials[i].color[1]=1.0f;
	escena.materials[i].color[2]=1.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=i;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=GLASS_INDEX;//GLASS_INDEX;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	escena.materials[i].color[0]=0.2f;
	escena.materials[i].color[1]=1.0f;
	escena.materials[i].color[2]=1.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=i;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=AIR_INDEX;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;



	escena.num_groups=6;
    escena.groups=(Group*)aligned_malloc(16,sizeof(Group)*escena.num_groups);
	i=0;
	escena.groups[i].id=i;
	escena.groups[i].material_id=0;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=1;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=2;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=3;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=4;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=5;

	

	//num_objects=7;
	//objects=(Object3D*)aligned_malloc(16,sizeof(Object3D)*num_objects);
	CreateObjects(9);
	i=0; 
	escena.objects[i].group_id=0;
	escena.objects[i].id=0;
	escena.objects[i].radious=10000.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=-10004.0f;
	escena.objects[i].v1[1]=0.0f;
	escena.objects[i].v1[2]=0.0f;
	i++;//1
	escena.objects[i].group_id=1;
	escena.objects[i].id=i;
	escena.objects[i].radious=10000.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=0.0f;
	escena.objects[i].v1[1]=0.0f;
	escena.objects[i].v1[2]=10004.0f;
	i++;
	escena.objects[i].group_id=1;
	escena.objects[i].id=i;
	escena.objects[i].radious=10000.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=0.0f;
	escena.objects[i].v1[1]=10004.0f;
	escena.objects[i].v1[2]=0.0f;
	i++;
	escena.objects[i].group_id=1;
	escena.objects[i].id=i;
	escena.objects[i].radious=10000.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=0.0f;
	escena.objects[i].v1[1]=-10004.0f;
	escena.objects[i].v1[2]=0.0f;
	i++;
	escena.objects[i].group_id=2;
	escena.objects[i].id=i;
	escena.objects[i].radious=10000.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=10004.0f;
	escena.objects[i].v1[1]=0.0f;
	escena.objects[i].v1[2]=0.0f;
	i++;
	escena.objects[i].group_id=3;
	escena.objects[i].id=i;
	escena.objects[i].radious=1.0f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=-2.0f;
	escena.objects[i].v1[1]=-3.0f;
	escena.objects[i].v1[2]=1.0f;
	i++;
	escena.objects[i].group_id=4;
	escena.objects[i].id=i;
	escena.objects[i].radious=1.5f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=2.0f;
	escena.objects[i].v1[1]=-2.0f;
	escena.objects[i].v1[2]=-2.0f;
	i++;
	escena.objects[i].group_id=5;
	escena.objects[i].id=i;
	escena.objects[i].radious=0.2f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=2.0f;
	escena.objects[i].v1[1]=-2.0f;
	escena.objects[i].v1[2]=-2.0f;
	i++;
	escena.objects[i].group_id=2;
	escena.objects[i].id=i;
	escena.objects[i].radious=0.5f;
    escena.objects[i].type=OBJ_SPHERE;
	escena.objects[i].v1[0]=-3.0f;
	escena.objects[i].v1[1]=-3.5f;
	escena.objects[i].v1[2]=-2.0f;
	i++;

	BuildBVH();
		PreprocessObjects();

}

void Demo4()
{
	int i=0;
	int x=0;

	//Crear Camera
	escena.num_cameras=1;
	escena.cameras=(Camera*)aligned_malloc(16,sizeof(Camera)*escena.num_cameras);
	i=0;
	escena.cameras[i].eye[0]=0.0f;
	escena.cameras[i].eye[1]=0.0f;
	escena.cameras[i].eye[2]=-10.0f;

	escena.cameras[i].lefttop[0]=-3.2f;
	escena.cameras[i].lefttop[1]=2.4f;
	escena.cameras[i].lefttop[2]=-5.0f;

	escena.cameras[i].righttop[0]=3.2f;
	escena.cameras[i].righttop[1]=2.4f;
	escena.cameras[i].righttop[2]=-5.0f;

	escena.cameras[i].leftbottom[0]=-3.2f;
	escena.cameras[i].leftbottom[1]=-2.4f;
	escena.cameras[i].leftbottom[2]=-5.0f;

	//Crear Light
	escena.num_lights=1;
	escena.lights=(Light*)aligned_malloc(16,sizeof(Light)*escena.num_lights);
	//lights=(Light*)CreateLights(num_lights);
	i=0;
	escena.lights[i].color[0]=1.0f;
	escena.lights[i].color[1]=1.0f;
	escena.lights[i].color[2]=1.0f;
	escena.lights[i].color[3]=1.0f;
	escena.lights[i].intensity=100.0f;
	escena.lights[i].id=i;
	escena.lights[i].position[0]=0.0f;
	escena.lights[i].position[1]=2.0f;
	escena.lights[i].position[2]=-5.0f;


	//Crear Material
	escena.num_materials=3;
	escena.materials=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materials);
	//materials=(Material*)CreateMaterials(num_materials);
	i=0;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=1.0f;
	escena.materials[i].color[2]=1.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=0;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.0f;
	escena.materials[i].color[2]=0.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=0;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	i++;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=0.0f;
	escena.materials[i].color[2]=1.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=0;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	escena.num_groups=3;
    escena.groups=(Group*)aligned_malloc(16,sizeof(Group)*escena.num_groups);
    //groups=(Group*)CreateGroups(num_groups);
	i=0;
	escena.groups[i].id=i;
	escena.groups[i].material_id=0;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=1;

	i++;
	escena.groups[i].id=i;
	escena.groups[i].material_id=2;
	

	escena.num_objects=23;
	escena.objects=(Object3D*)aligned_malloc(16,sizeof(Object3D)*escena.num_objects);
	//objects=(Object3D*)CreateObjects(num_objects);
	i=0; 
	escena.objects[i].group_id=0;
	escena.objects[i].id=0;
	escena.objects[i].radious=10.0f;
    escena.objects[i].type=OBJ_SPHERE;
	V_INIT(escena.objects[i].v1,0.0f,0.0f,14.0f);
	i++;
	escena.objects[i].group_id=1;
	escena.objects[i].id=0;
	escena.objects[i].radious=2.0f;
    escena.objects[i].type=OBJ_SPHERE;
	V_INIT(escena.objects[i].v1,-2.5f,2.0f,6.0f);

	i++;
	escena.objects[i].group_id=1;
	escena.objects[i].id=0;
	escena.objects[i].radious=2.0f;
    escena.objects[i].type=OBJ_SPHERE;
	V_INIT(escena.objects[i].v1,2.5f,2.0f,6.0f);

	for(x=0;x<20;x++)
	{
		i++;
		escena.objects[i].group_id=1;
		escena.objects[i].id=0;
		escena.objects[i].radious=2.0f;
        escena.objects[i].type=OBJ_SPHERE;
		V_INIT(escena.objects[i].v1,-2.5f + (x*0.25f),-2.0f,6.0f);
	}
	BuildBVH();
		PreprocessObjects();

}



void Demo7()
{
	int i=0;
	int nx=10,ny=10,nz=1,x,y,z;
	float fx,fy,fz;

	//Crear Camera
	escena.num_cameras=1;
	escena.cameras=(Camera*)aligned_malloc(16,sizeof(Camera)*escena.num_cameras);
	i=0;
	escena.cameras[i].eye[0]=0.0f;
	escena.cameras[i].eye[1]=0.0f;
	escena.cameras[i].eye[2]=-10.0f;

	escena.cameras[i].lefttop[0]=-3.2f;
	escena.cameras[i].lefttop[1]=2.4f;
	escena.cameras[i].lefttop[2]=-5.0f;

	escena.cameras[i].righttop[0]=3.2f;
	escena.cameras[i].righttop[1]=2.4f;
	escena.cameras[i].righttop[2]=-5.0f;

	escena.cameras[i].leftbottom[0]=-3.2f;
	escena.cameras[i].leftbottom[1]=-2.4f;
	escena.cameras[i].leftbottom[2]=-5.0f;

	//Crear Light
	escena.num_lights=1;
	escena.lights=(Light*)aligned_malloc(16,sizeof(Light)*escena.num_lights);
	i=0;
	escena.lights[i].color[0]=1.0f;
	escena.lights[i].color[1]=1.0f;
	escena.lights[i].color[2]=1.0f;
	escena.lights[i].color[3]=1.0f;
	escena.lights[i].intensity=100.0f;
	escena.lights[i].id=i;
	escena.lights[i].position[0]=0.0f;
	escena.lights[i].position[1]=2.0f;
	escena.lights[i].position[2]=-5.0f;


	//Crear Material
	escena.num_materials=1;
	escena.materials=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materials);
	i=0;
	escena.materials[i].color[0]=1.0f;
	escena.materials[i].color[1]=1.0f;
	escena.materials[i].color[2]=0.0f;
	escena.materials[i].color[3]=0.0f;
	escena.materials[i].id=0;
	escena.materials[i].ptr_textura=0;
	escena.materials[i].reflection=0;
	escena.materials[i].refraction=0;
	escena.materials[i].specular=1.0f;
	escena.materials[i].textura=0;
	escena.materials[i].txt_height=0;
	escena.materials[i].txt_width=0;

	escena.num_groups=1;
    escena.groups=(Group*)aligned_malloc(16,sizeof(Group)*escena.num_groups);
	i=0;
	escena.groups[i].id=i;
	escena.groups[i].material_id=0;

	escena.num_objects=nx*ny*nz;
	escena.objects=(Object3D*)aligned_malloc(16,sizeof(Object3D)*escena.num_objects);
	//CreateObjects(num_objects);
	i=0; 
	fz=0;
	for(z=0;z<nz;z++)
	{
		fy=ny/2;
		for(y=0;y<ny;y++)
		{
			fx=-nx/2;
			for(x=0;x<nx;x++)
			{
				escena.objects[i].group_id=0;
				escena.objects[i].id=i;
				//objects[i].radious=0.5f;
                escena.objects[i].type=OBJ_TRIANGLE;
				//objects[i].v1[3]=0;
				//objects[i].v1[0]=fx;
				//objects[i].v1[1]=fy;
				//objects[i].v1[2]=fz;

				V_INIT(escena.objects[i].v1,fx-0.5f,fy-0.5f,fz);
				V_INIT(escena.objects[i].v3,fx,fy+0.5f,fz);
				V_INIT(escena.objects[i].v2,fx+0.5f,fy-0.5f,fz);

				//V1_SET(i,fx-0.5f,fy-0.5f,fz);
				//V2_SET(i,fx,fy+0.5f,fz);
				//V3_SET(i,fx+0.5f,fy-0.5f,fz);
				i++;
				fx += 1.0f;
			}
			fy-=1.0f;
		}
		fz+=1.0f;
	}

	BuildBVH();
	PreprocessObjects();
}

void Demo9()
{
	int i;
	ms3d_material_t* ms3d_material;
	ms3d_group_t* ms3d_group;
	ms3d_vertex_t* ms3d_vertex;
	ms3d_triangle_t* ms3d_triangle;

	LoadSceneFromFile("f360.ms3d");


	escena.num_cameras=1;
	escena.cameras=(Camera*)aligned_malloc(16,sizeof(Camera)*escena.num_cameras);
	i=0;
	escena.cameras[0].eye[0]=0.0f;
	escena.cameras[0].eye[1]=0.0f;
	escena.cameras[0].eye[2]=-20.0f;

	escena.cameras[0].lefttop[0]=-3.2f;
	escena.cameras[0].lefttop[1]=2.4f;
	escena.cameras[0].lefttop[2]=-10.0f;

	escena.cameras[0].righttop[0]=3.2f;
	escena.cameras[0].righttop[1]=2.4f;
	escena.cameras[0].righttop[2]=-10.0f;

	escena.cameras[0].leftbottom[0]=-3.2f;
	escena.cameras[0].leftbottom[1]=-2.4f;
	escena.cameras[0].leftbottom[2]=-10.0f;

	//Crear Light
	escena.num_lights=1;
	escena.lights=(Light*)aligned_malloc(16,sizeof(Light)*escena.num_lights);
	i=0;
	escena.lights[i].color[0]=1.0f;
	escena.lights[i].color[1]=1.0f;
	escena.lights[i].color[2]=1.0f;
	escena.lights[i].color[3]=1.0f;
	escena.lights[i].intensity=100.0f;
	escena.lights[i].id=i;
	escena.lights[i].position[0]=0.0f;
	escena.lights[i].position[1]=2.0f;
	escena.lights[i].position[2]=-5.0f;


	//Crear Material
	escena.num_materials=MS3DGetNumMaterials();
	escena.materials=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materials);
	for(i=0;i<escena.num_materials;i++)
	{
		ms3d_material=MS3DGetMaterialAt(i);
		escena.materials[i].color[0]=1.0f;
		escena.materials[i].color[1]=ms3d_material->diffuse[0];
		escena.materials[i].color[2]=ms3d_material->diffuse[1];
		escena.materials[i].color[3]=ms3d_material->diffuse[2];
		escena.materials[i].id=i;
		escena.materials[i].ptr_textura=0;
		escena.materials[i].reflection=ms3d_material->shininess;
		escena.materials[i].refraction=ms3d_material->transparency;
		escena.materials[i].specular=1.0f;
		escena.materials[i].textura=0;
		escena.materials[i].txt_height=0;
		escena.materials[i].txt_width=0;
	}

	escena.num_groups=MS3DGetNumGroups();
    escena.groups=(Group*)aligned_malloc(16,sizeof(Group)*escena.num_groups);
	for(i=0;i<escena.num_groups;i++)
	{
		ms3d_group=MS3DGetGroupAt(i);
		escena.groups[i].id=i;
		escena.groups[i].material_id=ms3d_group->materialIndex;
	}


	escena.num_objects=MS3DGetNumTriangles();
	//objects=(Object3D*)aligned_malloc(16,sizeof(Object3D)*num_objects);
	CreateObjects(escena.num_objects);
	for(i=0;i<escena.num_objects;i++)
	{
		ms3d_triangle=MS3DGetTriangleAt(i);
		escena.objects[i].group_id=ms3d_triangle->groupIndex;
		escena.objects[i].id=i;
        escena.objects[i].type=OBJ_TRIANGLE;

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[0]);
		V_INIT(escena.objects[i].v1,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[1]);
		V_INIT(escena.objects[i].v2,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[2]);
		V_INIT(escena.objects[i].v3,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);
	}
	
	MS3DClean();
	BuildBVH();
	PreprocessObjects();

}

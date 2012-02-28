#include "demos.h"
#include "MS3DFile.h"
#include "bvh.h"

void Demo1()
{
	int i=0;

	//Crear Camara
	num_camaras=1;
	camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*num_camaras);
	i=0;
	camaras[0].eye[0]=0.0f;
	camaras[0].eye[1]=0.0f;
	camaras[0].eye[2]=-10.0f;

	camaras[0].lefttop[0]=-3.2f;
	camaras[0].lefttop[1]=2.4f;
	camaras[0].lefttop[2]=-5.0f;

	camaras[0].righttop[0]=3.2f;
	camaras[0].righttop[1]=2.4f;
	camaras[0].righttop[2]=-5.0f;

	camaras[0].leftbottom[0]=-3.2f;
	camaras[0].leftbottom[1]=-2.4f;
	camaras[0].leftbottom[2]=-5.0f;

	//Crear Luz
	num_luces=1;
	luces=(Luz*)aligned_malloc(16,sizeof(Luz)*num_luces);
	i=0;
	luces[i].color[0]=1.0f;
	luces[i].color[1]=1.0f;
	luces[i].color[2]=1.0f;
	luces[i].color[3]=1.0f;
	luces[i].intensidad=100.0f;
	luces[i].id=i;
	luces[i].posicion[0]=0.0f;
	luces[i].posicion[1]=2.0f;
	luces[i].posicion[2]=-5.0f;


	//Crear Material
	num_materiales=3;
	materiales=(Material*)aligned_malloc(16,sizeof(Material)*num_materiales);
	i=0;
	//207, 181, 59
	//azul
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.811764f;	//Old Gold
	materiales[i].color[2]=0.709803f;
	materiales[i].color[3]=0.231372f;
	materiales[i].id=0;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	//rojo
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.811764f;
	materiales[i].color[2]=0.709803f;
	materiales[i].color[3]=0.231372f;
	materiales[i].id=0;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	//verde
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.811764f;
	materiales[i].color[2]=0.709803f;
	materiales[i].color[3]=0.231372f;
	materiales[i].id=0;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	num_grupos=3;
	grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*num_grupos);
	i=0;
	grupos[i].id=i;
	grupos[i].id_material=0;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=1;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=2;
	

	num_objetos=3;
	objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	i=0; 
	objetos[i].id_grupo=0;
	objetos[i].id=0;
	objetos[i].radio=1.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=0;
	objetos[i].v1[1]=0;
	objetos[i].v1[2]=0;
	i++;//1
	objetos[i].id_grupo=1;
	objetos[i].id=i;
	objetos[i].radio=1.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=0;
	objetos[i].v1[1]=2.12132f;
	objetos[i].v1[2]=0;
	i++;//2
	objetos[i].id_grupo=2;
	objetos[i].id=i;
	objetos[i].radio=1.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=0;
	objetos[i].v1[1]=-2.12132f;
	objetos[i].v1[2]=0;
	i++;
		
	//objetos[i].id_grupo=0;
	//objetos[i].id=i;
	//objetos[i].tipo=OBJ_TRIANGULO;
	//V_INIT(objetos[i].v1,-2.0f-2.0f,0-2.5f,0);
	//V_INIT(objetos[i].v2,2.0f-2.0f,0-2.5f,0);
	//V_INIT(objetos[i].v3,0.0f-2.0f,3.0f-2.5f,0);
	//i++; 

	//objetos[i].id_grupo=1;
	//objetos[i].id=i;
	//objetos[i].tipo=OBJ_TRIANGULO;
	//V_INIT(objetos[i].v1,-2.0f,0+3.0f-2.5f,0);
	//V_INIT(objetos[i].v2,2.0f,0+3.0f-2.5f,0);
	//V_INIT(objetos[i].v3,0.0f,3.0f+3.0f-2.5f,0);
	//i++; 

	//objetos[i].id_grupo=2;
	//objetos[i].id=i;
	//objetos[i].tipo=OBJ_TRIANGULO;
	//V_INIT(objetos[i].v1,-2.0f+2.0f,0-2.5f,0);
	//V_INIT(objetos[i].v2,2.0f+2.0f,0-2.5f,0);
	//V_INIT(objetos[i].v3,0.0f+2.0f,3.0f-2.5f,0);
	//i++; 

	BuildBVH();
	PreprocessObjects();

}

void Demo2()
{
	int i=0;

	//Crear Camara
	num_camaras=1;
	camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*num_camaras);
	i=0;
	camaras[0].eye[0]=0.0f;
	camaras[0].eye[1]=0.0f;
	camaras[0].eye[2]=-10.0f;

	camaras[0].lefttop[0]=-3.2f;
	camaras[0].lefttop[1]=2.4f;
	camaras[0].lefttop[2]=-5.0f;

	camaras[0].righttop[0]=3.2f;
	camaras[0].righttop[1]=2.4f;
	camaras[0].righttop[2]=-5.0f;

	camaras[0].leftbottom[0]=-3.2f;
	camaras[0].leftbottom[1]=-2.4f;
	camaras[0].leftbottom[2]=-5.0f;

	//Crear Luz
	num_luces=1;
	luces=(Luz*)aligned_malloc(16,sizeof(Luz)*num_luces);
	i=0;
	luces[i].color[0]=1.0f;
	luces[i].color[1]=1.0f;
	luces[i].color[2]=1.0f;
	luces[i].color[3]=1.0f;
	luces[i].intensidad=100.0f;
	luces[i].id=i;
	luces[i].posicion[0]=0.0f;
	luces[i].posicion[1]=2.0f;
	luces[i].posicion[2]=-5.0f;


	//Crear Material
	num_materiales=2;
	materiales=(Material*)aligned_malloc(16,sizeof(Material)*num_materiales);
	i=0;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.0f;
	materiales[i].color[2]=1.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=i;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.0f;
	materiales[i].color[2]=0.0f;
	materiales[i].color[3]=1.0f;
	materiales[i].id=i;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	num_grupos=2;
	grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*num_grupos);
	i=0;
	grupos[i].id=i;
	grupos[i].id_material=0;
	i++;
	grupos[i].id=i;
	grupos[i].id_material=1;

	

	//num_objetos=2;
	//objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	CreateObjects(2);
	i=0; 
	objetos[i].id_grupo=0;
	objetos[i].id=i;
	objetos[i].radio=10000.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=0.0f;
	objetos[i].v1[1]=-10000.0f;
	objetos[i].v1[2]=0.0f;

	// GEN_TRIANGULO eax + Objeto3D,mdos,zero,zero, dos,zero,zero, zero,tres,zero, 0
	i++; 
	objetos[i].id_grupo=1;
	objetos[i].id=i;
	objetos[i].tipo=OBJ_TRIANGULO;
	V_INIT(objetos[i].v1,-2.0f,0,0);
	V_INIT(objetos[i].v2,2.0f,0,0);
	V_INIT(objetos[i].v3,0.0f,3.0f,0);
	//V_SUB(objetos[i].v2,objetos[i].v2,objetos[i].v1);
	//V_SUB(objetos[i].v3,objetos[i].v3,objetos[i].v1);

	BuildBVH();
	PreprocessObjects();

}


void Demo3()
{
	int i=0;

	//Crear Camara
	num_camaras=1;
	camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*num_camaras);
	i=0;
	camaras[0].eye[0]=0.0f;
	camaras[0].eye[1]=0.0f;
	camaras[0].eye[2]=-100.0f;

	camaras[0].lefttop[0]=-3.2f;
	camaras[0].lefttop[1]=2.4f;
	camaras[0].lefttop[2]=-50.0f;

	camaras[0].righttop[0]=3.2f;
	camaras[0].righttop[1]=2.4f;
	camaras[0].righttop[2]=-50.0f;

	camaras[0].leftbottom[0]=-3.2f;
	camaras[0].leftbottom[1]=-2.4f;
	camaras[0].leftbottom[2]=-50.0f;

	//Crear Luz
	num_luces=1;
	luces=(Luz*)aligned_malloc(16,sizeof(Luz)*num_luces);
	i=0;
	luces[i].color[0]=1.0f;
	luces[i].color[1]=1.0f;
	luces[i].color[2]=1.0f;
	luces[i].color[3]=1.0f;
	luces[i].intensidad=100.0f;
	luces[i].id=i;
	luces[i].posicion[0]=0.0f;
	luces[i].posicion[1]=2.0f;
	luces[i].posicion[2]=-1.0f;

	//Crear Material
	num_materiales=6;
	materiales=(Material*)aligned_malloc(16,sizeof(Material)*num_materiales);
	i=0;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.0f;
	materiales[i].color[2]=1.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=i;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=0.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=1.0f;
	materiales[i].color[2]=1.0f;
	materiales[i].color[3]=1.0f;
	materiales[i].id=i;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=0.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=1.0f;
	materiales[i].color[2]=0.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=i;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=0.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.0f;
	materiales[i].color[2]=0.0f;
	materiales[i].color[3]=1.0f;
	materiales[i].id=i;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0.7f;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	materiales[i].color[0]=0.2f;
	materiales[i].color[1]=1.0f;
	materiales[i].color[2]=1.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=i;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=GLASS_INDEX;//GLASS_INDEX;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	materiales[i].color[0]=0.2f;
	materiales[i].color[1]=1.0f;
	materiales[i].color[2]=1.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=i;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=AIR_INDEX;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;



	num_grupos=6;
	grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*num_grupos);
	i=0;
	grupos[i].id=i;
	grupos[i].id_material=0;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=1;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=2;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=3;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=4;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=5;

	

	//num_objetos=7;
	//objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	CreateObjects(9);
	i=0; 
	objetos[i].id_grupo=0;
	objetos[i].id=0;
	objetos[i].radio=10000.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=-10004.0f;
	objetos[i].v1[1]=0.0f;
	objetos[i].v1[2]=0.0f;
	i++;//1
	objetos[i].id_grupo=1;
	objetos[i].id=i;
	objetos[i].radio=10000.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=0.0f;
	objetos[i].v1[1]=0.0f;
	objetos[i].v1[2]=10004.0f;
	i++;
	objetos[i].id_grupo=1;
	objetos[i].id=i;
	objetos[i].radio=10000.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=0.0f;
	objetos[i].v1[1]=10004.0f;
	objetos[i].v1[2]=0.0f;
	i++;
	objetos[i].id_grupo=1;
	objetos[i].id=i;
	objetos[i].radio=10000.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=0.0f;
	objetos[i].v1[1]=-10004.0f;
	objetos[i].v1[2]=0.0f;
	i++;
	objetos[i].id_grupo=2;
	objetos[i].id=i;
	objetos[i].radio=10000.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=10004.0f;
	objetos[i].v1[1]=0.0f;
	objetos[i].v1[2]=0.0f;
	i++;
	objetos[i].id_grupo=3;
	objetos[i].id=i;
	objetos[i].radio=1.0f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=-2.0f;
	objetos[i].v1[1]=-3.0f;
	objetos[i].v1[2]=1.0f;
	i++;
	objetos[i].id_grupo=4;
	objetos[i].id=i;
	objetos[i].radio=1.5f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=2.0f;
	objetos[i].v1[1]=-2.0f;
	objetos[i].v1[2]=-2.0f;
	i++;
	objetos[i].id_grupo=5;
	objetos[i].id=i;
	objetos[i].radio=0.2f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=2.0f;
	objetos[i].v1[1]=-2.0f;
	objetos[i].v1[2]=-2.0f;
	i++;
	objetos[i].id_grupo=2;
	objetos[i].id=i;
	objetos[i].radio=0.5f;
	objetos[i].tipo=OBJ_ESFERA;
	objetos[i].v1[0]=-3.0f;
	objetos[i].v1[1]=-3.5f;
	objetos[i].v1[2]=-2.0f;
	i++;

	BuildBVH();
		PreprocessObjects();

}

void Demo4()
{
	int i=0;
	int x=0;

	//Crear Camara
	num_camaras=1;
	camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*num_camaras);
	i=0;
	camaras[i].eye[0]=0.0f;
	camaras[i].eye[1]=0.0f;
	camaras[i].eye[2]=-10.0f;

	camaras[i].lefttop[0]=-3.2f;
	camaras[i].lefttop[1]=2.4f;
	camaras[i].lefttop[2]=-5.0f;

	camaras[i].righttop[0]=3.2f;
	camaras[i].righttop[1]=2.4f;
	camaras[i].righttop[2]=-5.0f;

	camaras[i].leftbottom[0]=-3.2f;
	camaras[i].leftbottom[1]=-2.4f;
	camaras[i].leftbottom[2]=-5.0f;

	//Crear Luz
	num_luces=1;
	luces=(Luz*)aligned_malloc(16,sizeof(Luz)*num_luces);
	//luces=(Luz*)CreateLights(num_luces);
	i=0;
	luces[i].color[0]=1.0f;
	luces[i].color[1]=1.0f;
	luces[i].color[2]=1.0f;
	luces[i].color[3]=1.0f;
	luces[i].intensidad=100.0f;
	luces[i].id=i;
	luces[i].posicion[0]=0.0f;
	luces[i].posicion[1]=2.0f;
	luces[i].posicion[2]=-5.0f;


	//Crear Material
	num_materiales=3;
	materiales=(Material*)aligned_malloc(16,sizeof(Material)*num_materiales);
	//materiales=(Material*)CreateMaterials(num_materiales);
	i=0;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=1.0f;
	materiales[i].color[2]=1.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=0;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.0f;
	materiales[i].color[2]=0.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=0;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	i++;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=0.0f;
	materiales[i].color[2]=1.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=0;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	num_grupos=3;
	grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*num_grupos);
	//grupos=(Grupo*)CreateGroups(num_grupos);
	i=0;
	grupos[i].id=i;
	grupos[i].id_material=0;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=1;

	i++;
	grupos[i].id=i;
	grupos[i].id_material=2;
	

	num_objetos=23;
	objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	//objetos=(Objeto3D*)CreateObjects(num_objetos);
	i=0; 
	objetos[i].id_grupo=0;
	objetos[i].id=0;
	objetos[i].radio=10.0f;
	objetos[i].tipo=OBJ_ESFERA;
	V_INIT(objetos[i].v1,0.0f,0.0f,14.0f);
	i++;
	objetos[i].id_grupo=1;
	objetos[i].id=0;
	objetos[i].radio=2.0f;
	objetos[i].tipo=OBJ_ESFERA;
	V_INIT(objetos[i].v1,-2.5f,2.0f,6.0f);

	i++;
	objetos[i].id_grupo=1;
	objetos[i].id=0;
	objetos[i].radio=2.0f;
	objetos[i].tipo=OBJ_ESFERA;
	V_INIT(objetos[i].v1,2.5f,2.0f,6.0f);

	for(x=0;x<20;x++)
	{
		i++;
		objetos[i].id_grupo=1;
		objetos[i].id=0;
		objetos[i].radio=2.0f;
		objetos[i].tipo=OBJ_ESFERA;
		V_INIT(objetos[i].v1,-2.5f + (x*0.25f),-2.0f,6.0f);
	}
	BuildBVH();
		PreprocessObjects();

}



void Demo7()
{
	int i=0;
	int nx=10,ny=10,nz=1,x,y,z;
	float fx,fy,fz;

	//Crear Camara
	num_camaras=1;
	camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*num_camaras);
	i=0;
	camaras[i].eye[0]=0.0f;
	camaras[i].eye[1]=0.0f;
	camaras[i].eye[2]=-10.0f;

	camaras[i].lefttop[0]=-3.2f;
	camaras[i].lefttop[1]=2.4f;
	camaras[i].lefttop[2]=-5.0f;

	camaras[i].righttop[0]=3.2f;
	camaras[i].righttop[1]=2.4f;
	camaras[i].righttop[2]=-5.0f;

	camaras[i].leftbottom[0]=-3.2f;
	camaras[i].leftbottom[1]=-2.4f;
	camaras[i].leftbottom[2]=-5.0f;

	//Crear Luz
	num_luces=1;
	luces=(Luz*)aligned_malloc(16,sizeof(Luz)*num_luces);
	i=0;
	luces[i].color[0]=1.0f;
	luces[i].color[1]=1.0f;
	luces[i].color[2]=1.0f;
	luces[i].color[3]=1.0f;
	luces[i].intensidad=100.0f;
	luces[i].id=i;
	luces[i].posicion[0]=0.0f;
	luces[i].posicion[1]=2.0f;
	luces[i].posicion[2]=-5.0f;


	//Crear Material
	num_materiales=1;
	materiales=(Material*)aligned_malloc(16,sizeof(Material)*num_materiales);
	i=0;
	materiales[i].color[0]=1.0f;
	materiales[i].color[1]=1.0f;
	materiales[i].color[2]=0.0f;
	materiales[i].color[3]=0.0f;
	materiales[i].id=0;
	materiales[i].ptr_textura=0;
	materiales[i].reflexion=0;
	materiales[i].refraccion=0;
	materiales[i].specular=1.0f;
	materiales[i].textura=0;
	materiales[i].txt_height=0;
	materiales[i].txt_width=0;

	num_grupos=1;
	grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*num_grupos);
	i=0;
	grupos[i].id=i;
	grupos[i].id_material=0;

	num_objetos=nx*ny*nz;
	objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	//CreateObjects(num_objetos);
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
				objetos[i].id_grupo=0;
				objetos[i].id=i;
				//objetos[i].radio=0.5f;
				objetos[i].tipo=OBJ_TRIANGULO;
				//objetos[i].v1[3]=0;
				//objetos[i].v1[0]=fx;
				//objetos[i].v1[1]=fy;
				//objetos[i].v1[2]=fz;

				V_INIT(objetos[i].v1,fx-0.5f,fy-0.5f,fz);
				V_INIT(objetos[i].v3,fx,fy+0.5f,fz);
				V_INIT(objetos[i].v2,fx+0.5f,fy-0.5f,fz);

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


	num_camaras=1;
	camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*num_camaras);
	i=0;
	camaras[0].eye[0]=0.0f;
	camaras[0].eye[1]=0.0f;
	camaras[0].eye[2]=-20.0f;

	camaras[0].lefttop[0]=-3.2f;
	camaras[0].lefttop[1]=2.4f;
	camaras[0].lefttop[2]=-10.0f;

	camaras[0].righttop[0]=3.2f;
	camaras[0].righttop[1]=2.4f;
	camaras[0].righttop[2]=-10.0f;

	camaras[0].leftbottom[0]=-3.2f;
	camaras[0].leftbottom[1]=-2.4f;
	camaras[0].leftbottom[2]=-10.0f;

	//Crear Luz
	num_luces=1;
	luces=(Luz*)aligned_malloc(16,sizeof(Luz)*num_luces);
	i=0;
	luces[i].color[0]=1.0f;
	luces[i].color[1]=1.0f;
	luces[i].color[2]=1.0f;
	luces[i].color[3]=1.0f;
	luces[i].intensidad=100.0f;
	luces[i].id=i;
	luces[i].posicion[0]=0.0f;
	luces[i].posicion[1]=2.0f;
	luces[i].posicion[2]=-5.0f;


	//Crear Material
	num_materiales=MS3DGetNumMaterials();
	materiales=(Material*)aligned_malloc(16,sizeof(Material)*num_materiales);
	for(i=0;i<num_materiales;i++)
	{
		ms3d_material=MS3DGetMaterialAt(i);
		materiales[i].color[0]=1.0f;
		materiales[i].color[1]=ms3d_material->diffuse[0];
		materiales[i].color[2]=ms3d_material->diffuse[1];
		materiales[i].color[3]=ms3d_material->diffuse[2];
		materiales[i].id=i;
		materiales[i].ptr_textura=0;
		materiales[i].reflexion=ms3d_material->shininess;
		materiales[i].refraccion=ms3d_material->transparency;
		materiales[i].specular=1.0f;
		materiales[i].textura=0;
		materiales[i].txt_height=0;
		materiales[i].txt_width=0;
	}

	num_grupos=MS3DGetNumGroups();
	grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*num_grupos);
	for(i=0;i<num_grupos;i++)
	{
		ms3d_group=MS3DGetGroupAt(i);
		grupos[i].id=i;
		grupos[i].id_material=ms3d_group->materialIndex;
	}


	num_objetos=MS3DGetNumTriangles();
	//objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	CreateObjects(num_objetos);
	for(i=0;i<num_objetos;i++)
	{
		ms3d_triangle=MS3DGetTriangleAt(i);
		objetos[i].id_grupo=ms3d_triangle->groupIndex;
		objetos[i].id=i;
		objetos[i].tipo=OBJ_TRIANGULO;

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[0]);
		V_INIT(objetos[i].v1,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[1]);
		V_INIT(objetos[i].v2,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[2]);
		V_INIT(objetos[i].v3,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);
	}
	
	MS3DClean();
	BuildBVH();
	PreprocessObjects();

}
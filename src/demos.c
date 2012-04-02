#include "demos.h"
#include "MS3DFile.h"
#include "bvh.h"

void Demo1()
{
	int i=0;

	//Crear Camara
	escena.num_camaras=1;
	escena.camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*escena.num_camaras);
	i=0;
	escena.camaras[0].eye[0]=0.0f;
	escena.camaras[0].eye[1]=0.0f;
	escena.camaras[0].eye[2]=-10.0f;

	escena.camaras[0].lefttop[0]=-3.2f;
	escena.camaras[0].lefttop[1]=2.4f;
	escena.camaras[0].lefttop[2]=-5.0f;

	escena.camaras[0].righttop[0]=3.2f;
	escena.camaras[0].righttop[1]=2.4f;
	escena.camaras[0].righttop[2]=-5.0f;

	escena.camaras[0].leftbottom[0]=-3.2f;
	escena.camaras[0].leftbottom[1]=-2.4f;
	escena.camaras[0].leftbottom[2]=-5.0f;

	//Crear Luz
	escena.num_luces=1;
	escena.luces=(Luz*)aligned_malloc(16,sizeof(Luz)*escena.num_luces);
	i=0;
	escena.luces[i].color[0]=1.0f;
	escena.luces[i].color[1]=1.0f;
	escena.luces[i].color[2]=1.0f;
	escena.luces[i].color[3]=1.0f;
	escena.luces[i].intensidad=100.0f;
	escena.luces[i].id=i;
	escena.luces[i].posicion[0]=0.0f;
	escena.luces[i].posicion[1]=2.0f;
	escena.luces[i].posicion[2]=-5.0f;


	//Crear Material
	escena.num_materiales=3;
	escena.materiales=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materiales);
	i=0;
	//207, 181, 59
	//azul
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.811764f;	//Old Gold
	escena.materiales[i].color[2]=0.709803f;
	escena.materiales[i].color[3]=0.231372f;
	escena.materiales[i].id=0;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	//rojo
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.811764f;
	escena.materiales[i].color[2]=0.709803f;
	escena.materiales[i].color[3]=0.231372f;
	escena.materiales[i].id=0;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	//verde
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.811764f;
	escena.materiales[i].color[2]=0.709803f;
	escena.materiales[i].color[3]=0.231372f;
	escena.materiales[i].id=0;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	escena.num_grupos=3;
	escena.grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*escena.num_grupos);
	i=0;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=0;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=1;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=2;
	

	escena.num_objetos=3;
	escena.objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*escena.num_objetos);
	i=0; 
	escena.objetos[i].id_grupo=0;
	escena.objetos[i].id=0;
	escena.objetos[i].radio=1.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=0;
	escena.objetos[i].v1[1]=0;
	escena.objetos[i].v1[2]=0;
	i++;//1
	escena.objetos[i].id_grupo=1;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=1.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=0;
	escena.objetos[i].v1[1]=2.12132f;
	escena.objetos[i].v1[2]=0;
	i++;//2
	escena.objetos[i].id_grupo=2;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=1.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=0;
	escena.objetos[i].v1[1]=-2.12132f;
	escena.objetos[i].v1[2]=0;
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
	escena.num_camaras=1;
	escena.camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*escena.num_camaras);
	i=0;
	escena.camaras[0].eye[0]=0.0f;
	escena.camaras[0].eye[1]=0.0f;
	escena.camaras[0].eye[2]=-10.0f;

	escena.camaras[0].lefttop[0]=-3.2f;
	escena.camaras[0].lefttop[1]=2.4f;
	escena.camaras[0].lefttop[2]=-5.0f;

	escena.camaras[0].righttop[0]=3.2f;
	escena.camaras[0].righttop[1]=2.4f;
	escena.camaras[0].righttop[2]=-5.0f;

	escena.camaras[0].leftbottom[0]=-3.2f;
	escena.camaras[0].leftbottom[1]=-2.4f;
	escena.camaras[0].leftbottom[2]=-5.0f;

	//Crear Luz
	escena.num_luces=1;
	escena.luces=(Luz*)aligned_malloc(16,sizeof(Luz)*escena.num_luces);
	i=0;
	escena.luces[i].color[0]=1.0f;
	escena.luces[i].color[1]=1.0f;
	escena.luces[i].color[2]=1.0f;
	escena.luces[i].color[3]=1.0f;
	escena.luces[i].intensidad=100.0f;
	escena.luces[i].id=i;
	escena.luces[i].posicion[0]=0.0f;
	escena.luces[i].posicion[1]=2.0f;
	escena.luces[i].posicion[2]=-5.0f;


	//Crear Material
	escena.num_materiales=2;
	escena.materiales=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materiales);
	i=0;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.0f;
	escena.materiales[i].color[2]=1.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=i;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.0f;
	escena.materiales[i].color[2]=0.0f;
	escena.materiales[i].color[3]=1.0f;
	escena.materiales[i].id=i;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	escena.num_grupos=2;
	escena.grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*escena.num_grupos);
	i=0;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=0;
	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=1;

	

	//num_objetos=2;
	//objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	CreateObjects(2);
	i=0; 
	escena.objetos[i].id_grupo=0;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=10000.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=0.0f;
	escena.objetos[i].v1[1]=-10000.0f;
	escena.objetos[i].v1[2]=0.0f;

	// GEN_TRIANGULO eax + Objeto3D,mdos,zero,zero, dos,zero,zero, zero,tres,zero, 0
	i++; 
	escena.objetos[i].id_grupo=1;
	escena.objetos[i].id=i;
	escena.objetos[i].tipo=OBJ_TRIANGULO;
	V_INIT(escena.objetos[i].v1,-2.0f,0,0);
	V_INIT(escena.objetos[i].v2,2.0f,0,0);
	V_INIT(escena.objetos[i].v3,0.0f,3.0f,0);
	//V_SUB(objetos[i].v2,objetos[i].v2,objetos[i].v1);
	//V_SUB(objetos[i].v3,objetos[i].v3,objetos[i].v1);

	BuildBVH();
	PreprocessObjects();

}


void Demo3()
{
	int i=0;

	//Crear Camara
	escena.num_camaras=1;
	escena.camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*escena.num_camaras);
	i=0;
	escena.camaras[0].eye[0]=0.0f;
	escena.camaras[0].eye[1]=0.0f;
	escena.camaras[0].eye[2]=-100.0f;

	escena.camaras[0].lefttop[0]=-3.2f;
	escena.camaras[0].lefttop[1]=2.4f;
	escena.camaras[0].lefttop[2]=-50.0f;

	escena.camaras[0].righttop[0]=3.2f;
	escena.camaras[0].righttop[1]=2.4f;
	escena.camaras[0].righttop[2]=-50.0f;

	escena.camaras[0].leftbottom[0]=-3.2f;
	escena.camaras[0].leftbottom[1]=-2.4f;
	escena.camaras[0].leftbottom[2]=-50.0f;

	//Crear Luz
	escena.num_luces=1;
	escena.luces=(Luz*)aligned_malloc(16,sizeof(Luz)*escena.num_luces);
	i=0;
	escena.luces[i].color[0]=1.0f;
	escena.luces[i].color[1]=1.0f;
	escena.luces[i].color[2]=1.0f;
	escena.luces[i].color[3]=1.0f;
	escena.luces[i].intensidad=100.0f;
	escena.luces[i].id=i;
	escena.luces[i].posicion[0]=0.0f;
	escena.luces[i].posicion[1]=2.0f;
	escena.luces[i].posicion[2]=-1.0f;

	//Crear Material
	escena.num_materiales=6;
	escena.materiales=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materiales);
	i=0;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.0f;
	escena.materiales[i].color[2]=1.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=i;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=0.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=1.0f;
	escena.materiales[i].color[2]=1.0f;
	escena.materiales[i].color[3]=1.0f;
	escena.materiales[i].id=i;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=0.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=1.0f;
	escena.materiales[i].color[2]=0.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=i;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=0.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.0f;
	escena.materiales[i].color[2]=0.0f;
	escena.materiales[i].color[3]=1.0f;
	escena.materiales[i].id=i;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0.7f;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	escena.materiales[i].color[0]=0.2f;
	escena.materiales[i].color[1]=1.0f;
	escena.materiales[i].color[2]=1.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=i;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=GLASS_INDEX;//GLASS_INDEX;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	escena.materiales[i].color[0]=0.2f;
	escena.materiales[i].color[1]=1.0f;
	escena.materiales[i].color[2]=1.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=i;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=AIR_INDEX;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;



	escena.num_grupos=6;
	escena.grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*escena.num_grupos);
	i=0;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=0;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=1;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=2;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=3;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=4;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=5;

	

	//num_objetos=7;
	//objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	CreateObjects(9);
	i=0; 
	escena.objetos[i].id_grupo=0;
	escena.objetos[i].id=0;
	escena.objetos[i].radio=10000.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=-10004.0f;
	escena.objetos[i].v1[1]=0.0f;
	escena.objetos[i].v1[2]=0.0f;
	i++;//1
	escena.objetos[i].id_grupo=1;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=10000.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=0.0f;
	escena.objetos[i].v1[1]=0.0f;
	escena.objetos[i].v1[2]=10004.0f;
	i++;
	escena.objetos[i].id_grupo=1;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=10000.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=0.0f;
	escena.objetos[i].v1[1]=10004.0f;
	escena.objetos[i].v1[2]=0.0f;
	i++;
	escena.objetos[i].id_grupo=1;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=10000.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=0.0f;
	escena.objetos[i].v1[1]=-10004.0f;
	escena.objetos[i].v1[2]=0.0f;
	i++;
	escena.objetos[i].id_grupo=2;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=10000.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=10004.0f;
	escena.objetos[i].v1[1]=0.0f;
	escena.objetos[i].v1[2]=0.0f;
	i++;
	escena.objetos[i].id_grupo=3;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=1.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=-2.0f;
	escena.objetos[i].v1[1]=-3.0f;
	escena.objetos[i].v1[2]=1.0f;
	i++;
	escena.objetos[i].id_grupo=4;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=1.5f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=2.0f;
	escena.objetos[i].v1[1]=-2.0f;
	escena.objetos[i].v1[2]=-2.0f;
	i++;
	escena.objetos[i].id_grupo=5;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=0.2f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=2.0f;
	escena.objetos[i].v1[1]=-2.0f;
	escena.objetos[i].v1[2]=-2.0f;
	i++;
	escena.objetos[i].id_grupo=2;
	escena.objetos[i].id=i;
	escena.objetos[i].radio=0.5f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	escena.objetos[i].v1[0]=-3.0f;
	escena.objetos[i].v1[1]=-3.5f;
	escena.objetos[i].v1[2]=-2.0f;
	i++;

	BuildBVH();
		PreprocessObjects();

}

void Demo4()
{
	int i=0;
	int x=0;

	//Crear Camara
	escena.num_camaras=1;
	escena.camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*escena.num_camaras);
	i=0;
	escena.camaras[i].eye[0]=0.0f;
	escena.camaras[i].eye[1]=0.0f;
	escena.camaras[i].eye[2]=-10.0f;

	escena.camaras[i].lefttop[0]=-3.2f;
	escena.camaras[i].lefttop[1]=2.4f;
	escena.camaras[i].lefttop[2]=-5.0f;

	escena.camaras[i].righttop[0]=3.2f;
	escena.camaras[i].righttop[1]=2.4f;
	escena.camaras[i].righttop[2]=-5.0f;

	escena.camaras[i].leftbottom[0]=-3.2f;
	escena.camaras[i].leftbottom[1]=-2.4f;
	escena.camaras[i].leftbottom[2]=-5.0f;

	//Crear Luz
	escena.num_luces=1;
	escena.luces=(Luz*)aligned_malloc(16,sizeof(Luz)*escena.num_luces);
	//luces=(Luz*)CreateLights(num_luces);
	i=0;
	escena.luces[i].color[0]=1.0f;
	escena.luces[i].color[1]=1.0f;
	escena.luces[i].color[2]=1.0f;
	escena.luces[i].color[3]=1.0f;
	escena.luces[i].intensidad=100.0f;
	escena.luces[i].id=i;
	escena.luces[i].posicion[0]=0.0f;
	escena.luces[i].posicion[1]=2.0f;
	escena.luces[i].posicion[2]=-5.0f;


	//Crear Material
	escena.num_materiales=3;
	escena.materiales=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materiales);
	//materiales=(Material*)CreateMaterials(num_materiales);
	i=0;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=1.0f;
	escena.materiales[i].color[2]=1.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=0;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.0f;
	escena.materiales[i].color[2]=0.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=0;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	i++;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=0.0f;
	escena.materiales[i].color[2]=1.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=0;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	escena.num_grupos=3;
	escena.grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*escena.num_grupos);
	//grupos=(Grupo*)CreateGroups(num_grupos);
	i=0;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=0;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=1;

	i++;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=2;
	

	escena.num_objetos=23;
	escena.objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*escena.num_objetos);
	//objetos=(Objeto3D*)CreateObjects(num_objetos);
	i=0; 
	escena.objetos[i].id_grupo=0;
	escena.objetos[i].id=0;
	escena.objetos[i].radio=10.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	V_INIT(escena.objetos[i].v1,0.0f,0.0f,14.0f);
	i++;
	escena.objetos[i].id_grupo=1;
	escena.objetos[i].id=0;
	escena.objetos[i].radio=2.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	V_INIT(escena.objetos[i].v1,-2.5f,2.0f,6.0f);

	i++;
	escena.objetos[i].id_grupo=1;
	escena.objetos[i].id=0;
	escena.objetos[i].radio=2.0f;
	escena.objetos[i].tipo=OBJ_ESFERA;
	V_INIT(escena.objetos[i].v1,2.5f,2.0f,6.0f);

	for(x=0;x<20;x++)
	{
		i++;
		escena.objetos[i].id_grupo=1;
		escena.objetos[i].id=0;
		escena.objetos[i].radio=2.0f;
		escena.objetos[i].tipo=OBJ_ESFERA;
		V_INIT(escena.objetos[i].v1,-2.5f + (x*0.25f),-2.0f,6.0f);
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
	escena.num_camaras=1;
	escena.camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*escena.num_camaras);
	i=0;
	escena.camaras[i].eye[0]=0.0f;
	escena.camaras[i].eye[1]=0.0f;
	escena.camaras[i].eye[2]=-10.0f;

	escena.camaras[i].lefttop[0]=-3.2f;
	escena.camaras[i].lefttop[1]=2.4f;
	escena.camaras[i].lefttop[2]=-5.0f;

	escena.camaras[i].righttop[0]=3.2f;
	escena.camaras[i].righttop[1]=2.4f;
	escena.camaras[i].righttop[2]=-5.0f;

	escena.camaras[i].leftbottom[0]=-3.2f;
	escena.camaras[i].leftbottom[1]=-2.4f;
	escena.camaras[i].leftbottom[2]=-5.0f;

	//Crear Luz
	escena.num_luces=1;
	escena.luces=(Luz*)aligned_malloc(16,sizeof(Luz)*escena.num_luces);
	i=0;
	escena.luces[i].color[0]=1.0f;
	escena.luces[i].color[1]=1.0f;
	escena.luces[i].color[2]=1.0f;
	escena.luces[i].color[3]=1.0f;
	escena.luces[i].intensidad=100.0f;
	escena.luces[i].id=i;
	escena.luces[i].posicion[0]=0.0f;
	escena.luces[i].posicion[1]=2.0f;
	escena.luces[i].posicion[2]=-5.0f;


	//Crear Material
	escena.num_materiales=1;
	escena.materiales=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materiales);
	i=0;
	escena.materiales[i].color[0]=1.0f;
	escena.materiales[i].color[1]=1.0f;
	escena.materiales[i].color[2]=0.0f;
	escena.materiales[i].color[3]=0.0f;
	escena.materiales[i].id=0;
	escena.materiales[i].ptr_textura=0;
	escena.materiales[i].reflexion=0;
	escena.materiales[i].refraccion=0;
	escena.materiales[i].specular=1.0f;
	escena.materiales[i].textura=0;
	escena.materiales[i].txt_height=0;
	escena.materiales[i].txt_width=0;

	escena.num_grupos=1;
	escena.grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*escena.num_grupos);
	i=0;
	escena.grupos[i].id=i;
	escena.grupos[i].id_material=0;

	escena.num_objetos=nx*ny*nz;
	escena.objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*escena.num_objetos);
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
				escena.objetos[i].id_grupo=0;
				escena.objetos[i].id=i;
				//objetos[i].radio=0.5f;
				escena.objetos[i].tipo=OBJ_TRIANGULO;
				//objetos[i].v1[3]=0;
				//objetos[i].v1[0]=fx;
				//objetos[i].v1[1]=fy;
				//objetos[i].v1[2]=fz;

				V_INIT(escena.objetos[i].v1,fx-0.5f,fy-0.5f,fz);
				V_INIT(escena.objetos[i].v3,fx,fy+0.5f,fz);
				V_INIT(escena.objetos[i].v2,fx+0.5f,fy-0.5f,fz);

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


	escena.num_camaras=1;
	escena.camaras=(Camara*)aligned_malloc(16,sizeof(Camara)*escena.num_camaras);
	i=0;
	escena.camaras[0].eye[0]=0.0f;
	escena.camaras[0].eye[1]=0.0f;
	escena.camaras[0].eye[2]=-20.0f;

	escena.camaras[0].lefttop[0]=-3.2f;
	escena.camaras[0].lefttop[1]=2.4f;
	escena.camaras[0].lefttop[2]=-10.0f;

	escena.camaras[0].righttop[0]=3.2f;
	escena.camaras[0].righttop[1]=2.4f;
	escena.camaras[0].righttop[2]=-10.0f;

	escena.camaras[0].leftbottom[0]=-3.2f;
	escena.camaras[0].leftbottom[1]=-2.4f;
	escena.camaras[0].leftbottom[2]=-10.0f;

	//Crear Luz
	escena.num_luces=1;
	escena.luces=(Luz*)aligned_malloc(16,sizeof(Luz)*escena.num_luces);
	i=0;
	escena.luces[i].color[0]=1.0f;
	escena.luces[i].color[1]=1.0f;
	escena.luces[i].color[2]=1.0f;
	escena.luces[i].color[3]=1.0f;
	escena.luces[i].intensidad=100.0f;
	escena.luces[i].id=i;
	escena.luces[i].posicion[0]=0.0f;
	escena.luces[i].posicion[1]=2.0f;
	escena.luces[i].posicion[2]=-5.0f;


	//Crear Material
	escena.num_materiales=MS3DGetNumMaterials();
	escena.materiales=(Material*)aligned_malloc(16,sizeof(Material)*escena.num_materiales);
	for(i=0;i<escena.num_materiales;i++)
	{
		ms3d_material=MS3DGetMaterialAt(i);
		escena.materiales[i].color[0]=1.0f;
		escena.materiales[i].color[1]=ms3d_material->diffuse[0];
		escena.materiales[i].color[2]=ms3d_material->diffuse[1];
		escena.materiales[i].color[3]=ms3d_material->diffuse[2];
		escena.materiales[i].id=i;
		escena.materiales[i].ptr_textura=0;
		escena.materiales[i].reflexion=ms3d_material->shininess;
		escena.materiales[i].refraccion=ms3d_material->transparency;
		escena.materiales[i].specular=1.0f;
		escena.materiales[i].textura=0;
		escena.materiales[i].txt_height=0;
		escena.materiales[i].txt_width=0;
	}

	escena.num_grupos=MS3DGetNumGroups();
	escena.grupos=(Grupo*)aligned_malloc(16,sizeof(Grupo)*escena.num_grupos);
	for(i=0;i<escena.num_grupos;i++)
	{
		ms3d_group=MS3DGetGroupAt(i);
		escena.grupos[i].id=i;
		escena.grupos[i].id_material=ms3d_group->materialIndex;
	}


	escena.num_objetos=MS3DGetNumTriangles();
	//objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*num_objetos);
	CreateObjects(escena.num_objetos);
	for(i=0;i<escena.num_objetos;i++)
	{
		ms3d_triangle=MS3DGetTriangleAt(i);
		escena.objetos[i].id_grupo=ms3d_triangle->groupIndex;
		escena.objetos[i].id=i;
		escena.objetos[i].tipo=OBJ_TRIANGULO;

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[0]);
		V_INIT(escena.objetos[i].v1,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[1]);
		V_INIT(escena.objetos[i].v2,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);

		ms3d_vertex=MS3DGetVertexAt(ms3d_triangle->vertexIndices[2]);
		V_INIT(escena.objetos[i].v3,ms3d_vertex->vertex[0],ms3d_vertex->vertex[1],-ms3d_vertex->vertex[2]);
	}
	
	MS3DClean();
	BuildBVH();
	PreprocessObjects();

}
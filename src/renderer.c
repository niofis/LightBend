#include <math.h>
#include <stdlib.h>

#include "renderer.h"
#include "globals.h"
#include "bvh.h"

long done_threads;

align(16) Escena escena;

align(16) int *buffer;
align(16) int bpp;

align(16) RenderJob job;

#define BOX 50

int ShadowRay(Ray *ray,float max_dist)
{
	//regresa verdadero o falso, 
	//dependiendo si encuentra un obstaculo o no en el camino a la luz
	
	int i,si;
	int k,u,v;
	Objeto3D* objeto;
	float edge[3]={0,0,0};
	float normal[3]={0,0,0};
	float temp[3]={0,0,0};
	float edgeu,edgev,edgew;
	float t0,t,ta,B,B2,C,I;
	BoundingVolume *bv;

	#if defined(USE_BVH)
	//Recorrer el v_traverse, he ir checando con cada BoundingBox si tiene un hit
	//Si no hace hit, saltar al nodo indicado en el skip_ptrs
	//Si hace hit, revisar si es raiz u hoja, en el primer caso, continuar con el
	//recorrido, si es hoja, probar algun hit con los objetos contenidos
	//Continua el recorrido hasta que el skip_ptrs nos indique un-1
	
	for(si=0;si<num_cajas && si!=-1 ;si++) //si se llego al final del vector traverse o se encontro con un nodo terminal, cancela el ciclo
	{
		bv=&hierarchy[v_traverse[si]];
		if(bv->tipo==NODO_INVALIDO)	//no debe pasar, pero lo dejo igual
			continue;

		if(BoxHit(v_traverse[si],ray))
		{
			//Si el rayo toca la caja, y es raiz, se pasa a la siguiente caja
			if(bv->tipo==NODO_RAIZ)
				continue;
		}
		else
		{
			//Si no toca la caja, entonces se brinca al nodo indicado en el skip pointers vector
			si=skip_ptrs[si]-1;
			continue;
		}

		for(i=0;i<bv->cant_objs;i++)
		{
			objeto=&escena.objetos[bv->objs[i]];
	#else
		for(i=0;i<num_objetos;i++)
		{
			objeto=&objetos[i];
	#endif

			if(objeto->tipo==OBJ_ESFERA)
			{
				//Vector *c=sphere->center;
				V_SUB(edge,ray->origen,objeto->v1);//Vector *f= (*e)-c;
				B=-2.0f*V_DOT(edge,ray->direccion);//B=((*f) * d)*2;
				B2=B*B;
				C=(V_DOT(edge,edge)) - (objeto->radio*objeto->radio);// C=((*f) * f) - r2;
				I=B2 - 4.0f*C;

				if(I<0)					//No hay intersección
					continue;

				t0=sqrtf(I);		//Cálculos para obtener el(los) punto(s) de intersección

				t=(B - t0)/2.0f;

				if(t<0.01)
					t=(B + t0)/2.0f;	

				if(t<0.01)
					continue;
				if(t<=max_dist)
					return 1;
			}
			else if(objeto->tipo==OBJ_TRIANGULO)
			{
				//http://ompf.org/forum/viewtopic.php?f=4&t=1383

				// calc edges and normal
				//b = C-A; c = B-A; 
				//N = Cross(c,b);
				//V_CROSS(normal,objeto->v3,objeto->v2);

				// distance test
				V_SUB(temp,ray->origen,objeto->v1);
				B=V_DOT(temp,objeto->normal);
				B2=V_DOT(ray->direccion,objeto->normal);

				//t = - Dot((O-A),N) / Dot(D,N);
				t=-B/B2;
				if (t < EPSILON)
					continue;
				// determine projection dimensiondimensions

				if (fabs(objeto->normal[0]) > fabs(objeto->normal[1]))
				if (fabs(objeto->normal[0]) > fabs(objeto->normal[2])) k = 0; /* X */ else k=2; /* Z */
				else
				if (fabs(objeto->normal[1]) > fabs(objeto->normal[2])) k = 1; /* Y */ else k=2; /* Z */
				u = (k+1) % 3; v = (k+2) % 3;
				// calc hitpoint
				temp[u] = ray->origen[u] + t * ray->direccion[u]-objeto->v1[u];
				temp[v] = ray->origen[v] + t * ray->direccion[v]-objeto->v1[v];
				
				I=(objeto->v3[u] * objeto->v2[v] - objeto->v3[v] * objeto->v2[u]);

				B = (objeto->v3[u] * temp[v] - objeto->v3[v] * temp[u]) / I;
				if (B < 0)
					continue;
				C = (objeto->v2[v] * temp[u] - objeto->v2[u] * temp[v]) / I;
				if (C < 0)
					continue;
				if (B+C > 1)
					continue;
				if(t<=max_dist)
					return 1;
			}
		}
	#if defined(USE_BVH)
	}
	#endif
	return 0;
}

void Shading(float* punto, float* direccion, float* normal,Material* material, float* color)
{
	Luz*	luz;
	Ray ray;
	float norm;
	float t;
	float intensidad;
	float vr[3];
	float int_luz[4]={0,0,0,0};
	float specular[4]={0,0,0,0};
	int z;
	int i;

	ray.origen[0]=punto[0];
	ray.origen[1]=punto[1];
	ray.origen[2]=punto[2];


	for(z=0;z<escena.num_luces;z++)
	{
		luz=&escena.luces[z];

		V_SUB(ray.direccion,luz->posicion,ray.origen);
		norm=V_SIZE(ray.direccion);
		V_DIV(ray.direccion,norm);


		if(norm<luz->intensidad)
		{
			if(!ShadowRay(&ray,norm))
			{
				//i= producto punto de la normal del objeto con la direccion del rayo
				intensidad=V_DOT(normal,ray.direccion);
				if(intensidad>0)
				{
					//a la intensidad hay que multiplicarla por el porcentaje entre la intensidad de la luz
					//y el producto punto de la normal y el angulo (guardado en la variable intensidad)
					//intensidad*=(luces[z].intensidad-norm)/luces[z].intensidad;
					t=intensidad*(luz->intensidad-norm)/luz->intensidad;
					int_luz[1]+=luz->color[1]*t;
					int_luz[2]+=luz->color[2]*t;
					int_luz[3]+=luz->color[3]*t;

					//iluminacion specular
					//tomado de:
					//http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_2_Phong_Mirrors_and_Shadows.shtml
					//por Jacco Bikker, a.k.a. "The Phantom"
					//vector3 V = a_Ray.GetDirection();
					//vector3 R = L - 2.0f * DOT( L, N ) * N;
					//float dot = DOT( V, R );
					//if (dot > 0)
					//{
					//	float spec = powf( dot, 20 ) * prim->GetMaterial()->GetSpecular() * shade;
					//  // add specular component to ray color
					//  a_Acc += spec * light->GetMaterial()->GetColor();
					//}
					if(material->specular>0.0f)
					{
						intensidad*=2.0f;
						vr[0]=ray.direccion[0] - (intensidad * normal[0]);
						vr[1]=ray.direccion[1] - (intensidad * normal[1]);
						vr[2]=ray.direccion[2] - (intensidad * normal[2]);


						//intensidad=ray.direccion[0]o*vr[0] + ray.direccion[1]o*vr[1]+ray.direccion[2]o*vr[2];
						intensidad=V_DOT(vr,direccion);
						if(intensidad>0)
						{
							t=intensidad;
							for(i=0;i<19;i++)
								intensidad*=t;
							intensidad*=material->specular;
							specular[1]+=luz->color[1]*intensidad;
							specular[2]+=luz->color[2]*intensidad;
							specular[3]+=luz->color[3]*intensidad;
						}
					}
				}
			}
		}
	}

	color[1]*=min(1.0f,int_luz[1]);
	color[2]*=min(1.0f,int_luz[2]);
	color[3]*=min(1.0f,int_luz[3]);

	color[1]+=specular[1];
	color[2]+=specular[2];
	color[3]+=specular[3];

}

void TraceRay(Ray *ray, TraceResult *result, float* rf_stack,int depth)
{
	
	int i,si;
	int k,u,v;
	Objeto3D* objeto;
	Material* material;
	BoundingVolume *bv;
	Ray nray;
	TraceResult nresult;
	float edge[3]={0,0,0};
	float normal[3]={0,0,0};
	float temp[3]={0,0,0};
	float edgeu,edgev,edgew;
	float t0,t,ta,B,B2,C,I;
	float punto[3];
	float norm;
	int id_obj_ant;
	//borrar estas dos variables pues solo las puse de prueba
	//int num_objetos=0;
	//Objeto3D *objetos=NULL;

	ta=0;
	id_obj_ant=result->id_objeto;
	result->hit=0;
	result->id_objeto=0;
	result->dist=0;
	


	//recorre el stack revisando caja por caja atravezada por el rayo
	//Recorrer el v_traverse, he ir checando con cada BoundingBox si tiene un hit
	//Si no hace hit, saltar al nodo indicado en el skip_ptrs
	//Si hace hit, revisar si es raiz u hoja, en el primer caso, continuar con el
	//recorrido, si es hoja, probar algun hit con los objetos contenidos
	//Continua el recorrido hasta que el skip_ptrs nos indique un-1
	
	for(si=0;si<num_cajas && si!=-1 ;si++) //si se llego al final del vector traverse o se encontro con un nodo terminal, cancela el ciclo
	{

		bv=&hierarchy[v_traverse[si]];
		if(bv->tipo==NODO_INVALIDO)	//no debe pasar, pero lo dejo igual
			continue;
		if(BoxHit(v_traverse[si],ray))
		{
			//Si el rayo toca la caja, y es raiz, se pasa a la siguiente caja
			if(bv->tipo==NODO_RAIZ)
				continue;
		}
		else
		{
			//Si no toca la caja, entonces se brinca al nodo indicado en el skip pointers vector
			si=skip_ptrs[si]-1;
			continue;
		}
		for(i=0;i<bv->cant_objs;i++)
		{
			objeto=&escena.objetos[bv->objs[i]];
			if(objeto->tipo==OBJ_ESFERA)
			{
				//Vector *c=sphere->center;
				V_SUB(edge,ray->origen,objeto->v1);//Vector *f= (*e)-c;
				B=-2.0f*V_DOT(edge,ray->direccion);//B=((*f) * d)*2;
				B2=B*B;
				C=(V_DOT(edge,edge)) - (objeto->radio*objeto->radio);// C=((*f) * f) - r2;
				I=B2 - 4.0f*C;

				if(I<0)					//No hay intersección
					continue;

				t0=sqrtf(I);		//Cálculos para obtener el(los) punto(s) de intersección

				t=(B - t0)/2.0f;

				if(t<0.01)
					t=(B + t0)/2.0f;	

				if(t<0.01)
					continue;
				if(t<ta || ta==0)
				{
					ta=t;
					result->hit=1;
					result->id_objeto=bv->objs[i];
					result->dist=ta;
				}
			}
			else if(objeto->tipo==OBJ_TRIANGULO)
			{
				//http://ompf.org/forum/viewtopic.php?f=4&t=1383

				// calc edges and normal
				//b = C-A; c = B-A; 
				//N = Cross(c,b);
				//V_CROSS(normal,objeto->v3,objeto->v2);

				// distance test
				V_SUB(temp,ray->origen,objeto->v1);
				B=V_DOT(temp,objeto->normal);
				B2=V_DOT(ray->direccion,objeto->normal);

				//t = - Dot((O-A),N) / Dot(D,N);
				t=-B/B2;
				if (t < EPSILON)
					continue;
				// determine projection dimensiondimensions

				if (fabs(objeto->normal[0]) > fabs(objeto->normal[1]))
				if (fabs(objeto->normal[0]) > fabs(objeto->normal[2])) k = 0; /* X */ else k=2; /* Z */
				else
				if (fabs(objeto->normal[1]) > fabs(objeto->normal[2])) k = 1; /* Y */ else k=2; /* Z */
				u = (k+1) % 3; v = (k+2) % 3;
				// calc hitpoint
				temp[u] = ray->origen[u] + t * ray->direccion[u]-objeto->v1[u];
				temp[v] = ray->origen[v] + t * ray->direccion[v]-objeto->v1[v];
				
				I=(objeto->v3[u] * objeto->v2[v] - objeto->v3[v] * objeto->v2[u]);

				B = (objeto->v3[u] * temp[v] - objeto->v3[v] * temp[u]) / I;
				if (B < 0)
					continue;
				C = (objeto->v2[v] * temp[u] - objeto->v2[u] * temp[v]) / I;
				if (C < 0)
					continue;
				if (B+C > 1)
					continue;
				if(t<ta || ta==0)
				{
					ta=t;
					result->hit=1;
					result->id_objeto=bv->objs[i];
					result->dist=ta;
				}
			}
		}
	}

	if(!result->hit)
		return;
	
	objeto=&escena.objetos[result->id_objeto];
	material=&escena.materiales[escena.grupos[objeto->id_grupo].id_material];

	result->color[0]=material->color[0];
	result->color[1]=material->color[1];
	result->color[2]=material->color[2];
	result->color[3]=material->color[3];


	nray.origen[0]=ray->origen[0]+ray->direccion[0]*result->dist;
	nray.origen[1]=ray->origen[1]+ray->direccion[1]*result->dist;
	nray.origen[2]=ray->origen[2]+ray->direccion[2]*result->dist;

	//Obtener la normal del objeto detectado
	if(objeto->tipo==OBJ_ESFERA)
	{
		V_SUB(normal,nray.origen,objeto->v1);
		norm=V_SIZE(normal);
		V_DIV(normal,norm);
	}
	else if(objeto->tipo==OBJ_TRIANGULO)
	{
		//V_CROSS(normal,objeto->v3,objeto->v2);
		//norm=V_SIZE(normal);
		//V_DIV(normal,norm);
		normal[0]=objeto->normal[0];
		normal[1]=objeto->normal[1];
		normal[2]=objeto->normal[2];
	}


	Shading(nray.origen,ray->direccion,normal,material,result->color);

	//Solo se permite una recursion de hasta 10 veces
	depth++;
	if(depth>=MAX_DEPTH)
		return;
	//Habiendo aun mas pasos para recursion, se puede probar por reflexion y refraccion

	//Prueba Reflexión
	if(material->reflexion>0.0f)
	{
		//vert0=(float*)(&(ray->direction->u)); //V
		//vert1=(float*)(&(pt->normal->u));	//N
		t=(V_DOT(ray->direccion,normal)) * 2 ;
		//R = V – 2 * ( V . N ) * N;

		nray.direccion[0]=ray->direccion[0] - t * normal[0];
		nray.direccion[1]=ray->direccion[1] - t * normal[1];
		nray.direccion[2]=ray->direccion[2] - t * normal[2];

		norm=V_SIZE(nray.direccion);
		V_DIV(nray.direccion,norm);

		nresult.id_objeto=result->id_objeto;

		rf_stack[depth]=rf_stack[depth-1];
		TraceRay(&nray,&nresult,rf_stack,depth);

		result->color[1]=((1.0f-material->reflexion)*result->color[1])+(material->reflexion*nresult.color[1]);
		result->color[2]=((1.0f-material->reflexion)*result->color[2])+(material->reflexion*nresult.color[2]);
		result->color[3]=((1.0f-material->reflexion)*result->color[3])+(material->reflexion*nresult.color[3]);
	}
	if(material->refraccion>0.0f && result->color[0]<1.0f)
	{
		//;Reflections and Refractions in Ray Tracing
		//;Bram de Greve (bram.degreve@gmail.com)
		//;10th October 2004
		//;const double n = n1 / n2;
		//;const double cosI = dot(normal, incident);
		//;const double sinT2 = n * n * (1.0 - cosI * cosI);
		//;if (sinT2 > 1.0)
		//;{
		//;return Vector::invalid;
		//;}
		//;return n * incident - (n + sqrt(1.0 - sinT2)) * normal;
		//norm=result->refraccion_ant / material->refraccion;
		norm=rf_stack[depth-1] / material->refraccion;
		t=V_DOT(normal,ray->direccion);
		if(t>0)
		{
			V_MUL(normal,-1.0f);
			norm=rf_stack[depth-2] / material->refraccion;
			t=-t;
		}

		ta=norm*norm*(1.0f-t*t);
		if(ta<=1.0f)
		{
			//si el objeto anterior es igual al actual, invertir la normal
			//if(id_obj_ant==result->id_objeto)
			//{
			//	normal[0]*=-1.0f;
			//	normal[1]*=-1.0f;
			//	normal[2]*=-1.0f;
			//}

			//nuevo rayo de refraccion
			nray.direccion[0]=norm*ray->direccion[0] - (norm + sqrt(1.0f - ta)) * normal[0];
			nray.direccion[1]=norm*ray->direccion[1] - (norm + sqrt(1.0f - ta)) * normal[1];
			nray.direccion[2]=norm*ray->direccion[2] - (norm + sqrt(1.0f - ta)) * normal[2];
			norm=V_SIZE(nray.direccion);
			V_DIV(nray.direccion,norm);
			nresult.refraccion_ant=material->refraccion;
			nresult.id_objeto=result->id_objeto;

			rf_stack[depth]=material->refraccion;
			TraceRay(&nray,&nresult,rf_stack,depth);

			//result->color[1]=nresult.color[1];
			//result->color[2]=nresult.color[2];
			//result->color[3]=nresult.color[3];
					
			result->color[1]=(result->color[0]*result->color[1])+((1.0f - result->color[0])*nresult.color[1]);
			result->color[2]=(result->color[0]*result->color[2])+((1.0f - result->color[0])*nresult.color[2]);
			result->color[3]=(result->color[0]*result->color[3])+((1.0f - result->color[0])*nresult.color[3]);

		}
	}
}

THREAD Render(int param)
{

	int i,x,y,z;
	int si;
	int total_pix,cant,ini,end;
	int step;
	float h,w;
	int rgb;
	float dx,dy;
	float norm;
	float t;

	Ray ray={{0,0,0},{0,0,0}};

	float dir_or[3];
	float punto[3];
	float normal[3];


	float dt[3];
	float dl[3];

	float vr[3];

	float color[4];

	Objeto3D* objeto;
	Material* material;

	TraceResult result;

	float rf_stack[MAX_DEPTH];


	V_SUB(dt,escena.camaras[0].righttop,escena.camaras[0].lefttop);
	V_SUB(dl,escena.camaras[0].leftbottom,escena.camaras[0].lefttop);

	step = ((int)param)>>16;
	i=((int)param) & 0xFFFF;


	for(y=i;y<job.height;y+=step)
	for(x=0;x<job.width;x++)
	{
		dx=(x+0.5f)/job.width;
		dy=(y+0.5f)/job.height;

		ray.origen[0]=(dt[0]*dx  + dl[0]*dy + escena.camaras[0].lefttop[0]);//camaras[0].eye[0];
		ray.origen[1]=(dt[1]*dx  + dl[1]*dy + escena.camaras[0].lefttop[1]);//camaras[0].eye[1];
		ray.origen[2]=(dt[2]*dx  + dl[2]*dy + escena.camaras[0].lefttop[2]);//camaras[0].eye[2];
		ray.direccion[0]= ray.origen[0] - escena.camaras[0].eye[0];//ray.origen[0];
		ray.direccion[1]= ray.origen[1] - escena.camaras[0].eye[1];//ray.origen[1];
		ray.direccion[2]= ray.origen[2] - escena.camaras[0].eye[2];//ray.origen[2];

		norm=V_SIZE(ray.direccion);
		V_DIV(ray.direccion,norm);

		//dir_or[0]=ray.direccion[0];
		//dir_or[1]=ray.direccion[1];
		//dir_or[2]=ray.direccion[2];

		
		
		/*if(BoxHit(BOX,&ray)!=NULL)
			buffer[y*width + x]=~0;
		else
			buffer[y*width + x]=0;*/

		result.refraccion_ant=AIR_INDEX;
		result.id_objeto=-1;

		rf_stack[0]=AIR_INDEX;
		TraceRay(&ray,&result,&rf_stack,0);

		if(result.hit)
		{
			rgb=255;
			rgb<<=8;
			rgb+=min((int)(result.color[1]*255.0f),255);
			rgb<<=8;
			rgb+=min((int)(result.color[2]*255.0f),255);
			rgb<<=8;
			rgb+=min((int)(result.color[3]*255.0f),255);

			buffer[y*job.width + x]=rgb;
			//buffer[y*width + x]=0;
		}
		else
		{
			//buffer[y*job.width + x]=0;
			buffer[y*job.width + x]=255<<24;
		}
			

		//if(BoxHit(31,&ray)!=NULL)
		//	buffer[y*width + x]=~0;
		//else
		//	buffer[y*width + x]=0;
		
	}
	#if defined(WIN32)
		//InterlockedIncrement(&done_threads);
		done_threads++;
	#else
		__sync_fetch_and_add(&done_threads,1);
	#endif

	return 0;
}

void RenderFrame(int* pixels, int threads)
{
	int x=0;
	int param;
	int sh;
	buffer=pixels;
	done_threads=0;

	if(threads==1)
	{
		param=(threads<<16) | x;
		Render(param);
		return;
	}
	else
	{
		for(x=0;x<threads-1;x++)
		{
			param=(threads<<16) | x; //step,start
			CreateThread(Render,param);
		}

		param=(threads<<16) | x; //step,start
			CreateThread(Render,param);

		while(done_threads<threads)
			Sleep(1);
	
		/*#pragma omp parallel
			{
				Render(omp_get_num_threads()<<16 | omp_get_thread_num());
			}*/
	}

}



void CleanRenderer()
{
	if(escena.grupos)
		aligned_free(escena.grupos);
	if(escena.materiales)
		aligned_free(escena.materiales);
	if(escena.objetos)
		aligned_free(escena.objetos);
	if(escena.luces)
		aligned_free(escena.luces);
	if(escena.camaras)
		aligned_free(escena.camaras);


	escena.grupos=0;
	escena.materiales=0;
	escena.objetos=0;
	escena.luces=0;
	escena.camaras=0;
	escena.num_grupos=0;
	escena.num_materiales=0;
	escena.num_objetos=0;
	escena.num_luces=0;
	escena.num_camaras=0;
}

void PreprocessObjects()
{
	int i;
	float n;
	for(i=0;i<escena.num_objetos;i++)
	{
		V_SUB(escena.objetos[i].v2,escena.objetos[i].v2,escena.objetos[i].v1);
		V_SUB(escena.objetos[i].v3,escena.objetos[i].v3,escena.objetos[i].v1);
		V_CROSS(escena.objetos[i].normal,escena.objetos[i].v3,escena.objetos[i].v2);
		n=V_SIZE(escena.objetos[i].normal);
		V_DIV(escena.objetos[i].normal,n);
	}
}

void CreateObjects(int qty)
{
	escena.num_objetos=qty;
	escena.objetos=(Objeto3D*)aligned_malloc(16,sizeof(Objeto3D)*escena.num_objetos);
}
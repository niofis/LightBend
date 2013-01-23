#include <math.h>
#include <stdlib.h>

#include "renderer.h"
#include "globals.h"
#include "bvh.h"

long done_threads;

align(ALIGMENT) Escena escena;

align(ALIGMENT) int *buffer;
align(ALIGMENT) int bpp;

align(ALIGMENT) RenderJob job;

#define BOX 50

int ShadowRay(Ray *ray,float max_dist)
{
	//regresa verdadero o falso, 
	//dependiendo si encuentra un obstaculo o no en el camino a la luz
	
	int i,si;
	int k,u,v;
    Triangle* objeto;
	float temp[3]={0,0,0};
	BoundingVolume *bv;
    float B,B2,C,I,t;

	//Recorrer el v_traverse, he ir checando con cada BoundingBox si tiene un hit
	//Si no hace hit, saltar al nodo indicado en el skip_ptrs
	//Si hace hit, revisar si es raiz u hoja, en el primer caso, continuar con el
    //recorrido, si es hoja, probar algun hit con los objects contenidos
	//Continua el recorrido hasta que el skip_ptrs nos indique un-1
	
	for(si=0;si<num_cajas && si!=-1 ;si++) //si se llego al final del vector traverse o se encontro con un nodo terminal, cancela el ciclo
	{
		bv=&hierarchy[v_traverse[si]];
		if(bv->type==NODO_INVALIDO)	//no debe pasar, pero lo dejo igual
			continue;

		if(BoxHit(v_traverse[si],ray))
		{
			//Si el rayo toca la caja, y es raiz, se pasa a la siguiente caja
			if(bv->type==NODO_RAIZ)
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
            objeto=&escena.objects[bv->objs[i]];
            
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

	return 0;
}

void Shading(float* punto, float* direccion, float* normal,Material* material, float* color)
{
    Light*	luz;
	Ray ray;
	float norm;
	float t;
	float intensity;
	float vr[3];
	float int_luz[4]={0,0,0,0};
	float specular[4]={0,0,0,0};
	int z;
	int i;

	ray.origen[0]=punto[0];
	ray.origen[1]=punto[1];
	ray.origen[2]=punto[2];


    for(z=0;z<escena.num_lights;z++)
	{
        luz=&escena.lights[z];

		V_SUB(ray.direccion,luz->position,ray.origen);
		norm=V_SIZE(ray.direccion);
		V_DIV(ray.direccion,norm);


		if(norm<luz->intensity)
		{
			if(!ShadowRay(&ray,norm))
			{
				//i= producto punto de la normal del objeto con la direccion del rayo
				intensity=V_DOT(normal,ray.direccion);
				if(intensity>0)
				{
					//a la intensity hay que multiplicarla por el porcentaje entre la intensity de la luz
					//y el producto punto de la normal y el angulo (guardado en la variable intensity)
                    //intensity*=(lights[z].intensity-norm)/lights[z].intensity;
					t=intensity*(luz->intensity-norm)/luz->intensity;
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
						intensity*=2.0f;
						vr[0]=ray.direccion[0] - (intensity * normal[0]);
						vr[1]=ray.direccion[1] - (intensity * normal[1]);
						vr[2]=ray.direccion[2] - (intensity * normal[2]);


						//intensity=ray.direccion[0]o*vr[0] + ray.direccion[1]o*vr[1]+ray.direccion[2]o*vr[2];
						intensity=V_DOT(vr,direccion);
						if(intensity>0)
						{
							t=intensity;
							for(i=0;i<19;i++)
								intensity*=t;
							intensity*=material->specular;
							specular[1]+=luz->color[1]*intensity;
							specular[2]+=luz->color[2]*intensity;
							specular[3]+=luz->color[3]*intensity;
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
    Triangle* objeto;
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
    //int num_objects=0;
    //Object3D *objects=NULL;

	ta=0;
	id_obj_ant=result->id_objeto;
	result->hit=0;
	result->id_objeto=0;
	result->dist=0;
	


	//recorre el stack revisando caja por caja atravezada por el rayo
	//Recorrer el v_traverse, he ir checando con cada BoundingBox si tiene un hit
	//Si no hace hit, saltar al nodo indicado en el skip_ptrs
	//Si hace hit, revisar si es raiz u hoja, en el primer caso, continuar con el
    //recorrido, si es hoja, probar algun hit con los objects contenidos
	//Continua el recorrido hasta que el skip_ptrs nos indique un-1
	
	for(si=0;si<num_cajas && si!=-1 ;si++) //si se llego al final del vector traverse o se encontro con un nodo terminal, cancela el ciclo
	{

		bv=&hierarchy[v_traverse[si]];
		if(bv->type==NODO_INVALIDO)	//no debe pasar, pero lo dejo igual
			continue;
		if(BoxHit(v_traverse[si],ray))
		{
			//Si el rayo toca la caja, y es raiz, se pasa a la siguiente caja
			if(bv->type==NODO_RAIZ)
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
            objeto=&escena.objects[bv->objs[i]];
            /*
            if(objeto->type==OBJ_SPHERE)
			{
				//Vector *c=sphere->center;
				V_SUB(edge,ray->origen,objeto->v1);//Vector *f= (*e)-c;
				B=-2.0f*V_DOT(edge,ray->direccion);//B=((*f) * d)*2;
				B2=B*B;
				C=(V_DOT(edge,edge)) - (objeto->radious*objeto->radious);// C=((*f) * f) - r2;
				I=B2 - 4.0f*C;

				if(I<0)					//No hay interseccin
					continue;

				t0=sqrtf(I);		//Clculos para obtener el(los) punto(s) de interseccin

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
            else if(objeto->type==OBJ_TRIANGLE)
			{
            */
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
            //}
		}
	}

	if(!result->hit)
		return;
	
    objeto=&escena.objects[result->id_objeto];
    material=&escena.materials[escena.groups[objeto->group_id].material_id];

	result->color[0]=material->color[0];
	result->color[1]=material->color[1];
	result->color[2]=material->color[2];
	result->color[3]=material->color[3];


	nray.origen[0]=ray->origen[0]+ray->direccion[0]*result->dist;
	nray.origen[1]=ray->origen[1]+ray->direccion[1]*result->dist;
	nray.origen[2]=ray->origen[2]+ray->direccion[2]*result->dist;

	//Obtener la normal del objeto detectado
    /*
    if(objeto->type==OBJ_SPHERE)
	{
		V_SUB(normal,nray.origen,objeto->v1);
		norm=V_SIZE(normal);
		V_DIV(normal,norm);
	}
    else if(objeto->type==OBJ_TRIANGLE)
	{
    */
		//V_CROSS(normal,objeto->v3,objeto->v2);
		//norm=V_SIZE(normal);
		//V_DIV(normal,norm);
		normal[0]=objeto->normal[0];
		normal[1]=objeto->normal[1];
		normal[2]=objeto->normal[2];
    //}


	Shading(nray.origen,ray->direccion,normal,material,result->color);

	//Solo se permite una recursion de hasta 10 veces
	depth++;
	if(depth>=MAX_DEPTH)
		return;
	//Habiendo aun mas pasos para recursion, se puede probar por reflection y refraction

	//Prueba Reflexin
	if(material->reflection>0.0f)
	{
		//vert0=(float*)(&(ray->direction->u)); //V
		//vert1=(float*)(&(pt->normal->u));	//N
		t=(V_DOT(ray->direccion,normal)) * 2 ;
		//R = V  2 * ( V . N ) * N;

		nray.direccion[0]=ray->direccion[0] - t * normal[0];
		nray.direccion[1]=ray->direccion[1] - t * normal[1];
		nray.direccion[2]=ray->direccion[2] - t * normal[2];

		norm=V_SIZE(nray.direccion);
		V_DIV(nray.direccion,norm);

		nresult.id_objeto=result->id_objeto;

		rf_stack[depth]=rf_stack[depth-1];
		TraceRay(&nray,&nresult,rf_stack,depth);

		result->color[1]=((1.0f-material->reflection)*result->color[1])+(material->reflection*nresult.color[1]);
		result->color[2]=((1.0f-material->reflection)*result->color[2])+(material->reflection*nresult.color[2]);
		result->color[3]=((1.0f-material->reflection)*result->color[3])+(material->reflection*nresult.color[3]);
	}
	if(material->refraction>0.0f && result->color[0]<1.0f)
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
		//norm=result->refraction_ant / material->refraction;
		norm=rf_stack[depth-1] / material->refraction;
		t=V_DOT(normal,ray->direccion);
		if(t>0)
		{
			V_MUL(normal,-1.0f);
			norm=rf_stack[depth-2] / material->refraction;
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

			//nuevo rayo de refraction
			nray.direccion[0]=norm*ray->direccion[0] - (norm + sqrt(1.0f - ta)) * normal[0];
			nray.direccion[1]=norm*ray->direccion[1] - (norm + sqrt(1.0f - ta)) * normal[1];
			nray.direccion[2]=norm*ray->direccion[2] - (norm + sqrt(1.0f - ta)) * normal[2];
			norm=V_SIZE(nray.direccion);
			V_DIV(nray.direccion,norm);
			nresult.refraction_ant=material->refraction;
			nresult.id_objeto=result->id_objeto;

			rf_stack[depth]=material->refraction;
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

	int i,x,y;
	int step;
	int rgb;
	float dx,dy;
	float norm;

	Ray ray={{0,0,0},{0,0,0}};


	float dt[3];
	float dl[3];


	TraceResult result;

	float rf_stack[MAX_DEPTH];


	V_SUB(dt,escena.cameras[0].righttop,escena.cameras[0].lefttop);
	V_SUB(dl,escena.cameras[0].leftbottom,escena.cameras[0].lefttop);

	step = ((int)param)>>16;
	i=((int)param) & 0xFFFF;


	for(y=i;y<job.height;y+=step)
	for(x=0;x<job.width;x++)
	{
		dx=(x+0.5f)/job.width;
		dy=(y+0.5f)/job.height;

        ray.origen[0]=escena.cameras[0].eye[0];//(dt[0]*dx  + dl[0]*dy + escena.cameras[0].lefttop[0]);//
        ray.origen[1]=escena.cameras[0].eye[1];//(dt[1]*dx  + dl[1]*dy + escena.cameras[0].lefttop[1]);//
        ray.origen[2]=escena.cameras[0].eye[2];//(dt[2]*dx  + dl[2]*dy + escena.cameras[0].lefttop[2]);//
        ray.direccion[0]= (dt[0]*dx  + dl[0]*dy + escena.cameras[0].lefttop[0]- escena.cameras[0].eye[0]);//ray.origen[0] - escena.cameras[0].eye[0];//ray.origen[0];
        ray.direccion[1]= (dt[1]*dx  + dl[1]*dy + escena.cameras[0].lefttop[1]- escena.cameras[0].eye[1]);//ray.origen[1] - escena.cameras[0].eye[1];//ray.origen[1];
        ray.direccion[2]= (dt[2]*dx  + dl[2]*dy + escena.cameras[0].lefttop[2]- escena.cameras[0].eye[2]);//ray.origen[2] - escena.cameras[0].eye[2];//ray.origen[2];

		norm=V_SIZE(ray.direccion);
		V_DIV(ray.direccion,norm);

		//dir_or[0]=ray.direccion[0];
		//dir_or[1]=ray.direccion[1];
		//dir_or[2]=ray.direccion[2];

		
		
		/*if(BoxHit(BOX,&ray)!=NULL)
			buffer[y*width + x]=~0;
		else
			buffer[y*width + x]=0;*/

		result.refraction_ant=AIR_INDEX;
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
            //buffer[y*job.width + x]=255<<24;
            buffer[y*job.width + x]=0xFF888888;
		}
			

		//if(BoxHit(31,&ray)!=NULL)
		//	buffer[y*width + x]=~0;
		//else
		//	buffer[y*width + x]=0;
		
	}
	#if defined(WIN32)
		InterlockedIncrement(&done_threads);
		//done_threads++;
	#else
        //done_threads++;
		__sync_fetch_and_add(&done_threads,1);
	#endif

	return 0;
}

void RenderFrame(int* pixels, int threads)
{
	int x=0;
	int param;
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
			Render(param);

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
    if(escena.groups)
        aligned_free(escena.groups);
    if(escena.materials)
        aligned_free(escena.materials);
    if(escena.objects)
        aligned_free(escena.objects);
    if(escena.lights)
        aligned_free(escena.lights);
	if(escena.cameras)
		aligned_free(escena.cameras);


    escena.groups=NULL;
    escena.materials=NULL;
    escena.objects=NULL;
    escena.lights=NULL;
    escena.cameras=NULL;
    escena.num_groups=0;
    escena.num_materials=0;
    escena.num_objects=0;
    escena.num_lights=0;
	escena.num_cameras=0;
}

void PreprocessObjects()
{
	int i;
	float n;
    for(i=0;i<escena.num_objects;i++)
	{
        V_SUB(escena.objects[i].v2,escena.objects[i].v2,escena.objects[i].v1);
        V_SUB(escena.objects[i].v3,escena.objects[i].v3,escena.objects[i].v1);
        V_CROSS(escena.objects[i].normal,escena.objects[i].v3,escena.objects[i].v2);
        n=V_SIZE(escena.objects[i].normal);
        V_DIV(escena.objects[i].normal,n);
	}
}

void CreateObjects(int qty)
{
    escena.num_objects=qty;
    escena.objects=(Triangle*)aligned_malloc(ALIGMENT,sizeof(Triangle)*escena.num_objects);
}

void convertscene(Scene *scene, Escena *nscene)
{
	int i=0;

	printf("Cameras: %d\n",scene->cameras->count);
    printf("Groups: %d\n",scene->groups->count);
    printf("Lights: %d\n",scene->lights->count);
    printf("Materials: %d\n",scene->materials->count);
    printf("Objects: %d\n",scene->objects->count);

	CleanRenderer();

    escena.num_cameras=scene->lights->count;
    escena.cameras=(Camera*)aligned_malloc(ALIGMENT,sizeof(Camera)*escena.num_cameras);
    for(i=0;i<scene->cameras->count;++i)
    {
        Camera* c=(Camera*)list_get(scene->cameras,i);
        escena.cameras[0].eye[0]=c->eye[0];
        escena.cameras[0].eye[1]=c->eye[1];
        escena.cameras[0].eye[2]=c->eye[2];

        escena.cameras[0].lefttop[0]=c->lefttop[0];
        escena.cameras[0].lefttop[1]=c->lefttop[1];
        escena.cameras[0].lefttop[2]=c->lefttop[2];

        escena.cameras[0].righttop[0]=c->righttop[0];
        escena.cameras[0].righttop[1]=c->righttop[1];
        escena.cameras[0].righttop[2]=c->righttop[2];

        escena.cameras[0].leftbottom[0]=c->leftbottom[0];
        escena.cameras[0].leftbottom[1]=c->leftbottom[1];
        escena.cameras[0].leftbottom[2]=c->leftbottom[2];
    }

    escena.num_lights=scene->lights->count;
    escena.lights=(Light*)aligned_malloc(ALIGMENT,sizeof(Light)*escena.num_lights);
	for(i=0;i<scene->lights->count;++i)
	{
        Light* l=(Light*)list_get(scene->lights,i);
        escena.lights[i].color[0]=l->color[0];
        escena.lights[i].color[1]=l->color[1];
        escena.lights[i].color[2]=l->color[2];
        escena.lights[i].color[3]=l->color[3];
        escena.lights[i].intensity=l->intensity;
        escena.lights[i].id=i;
        escena.lights[i].position[0]=l->position[0];
        escena.lights[i].position[1]=l->position[1];
        escena.lights[i].position[2]=l->position[2];
	}

	escena.num_materials=scene->materials->count;
	escena.materials=(Material*)aligned_malloc(ALIGMENT,sizeof(Material)*escena.num_materials);
	for(i=0;i<scene->materials->count;++i)
	{
		Material* m=(Material*)list_get(scene->materials,i);
		escena.materials[i].color[0]=m->color[0];
		escena.materials[i].color[1]=m->color[1];
		escena.materials[i].color[2]=m->color[2];
		escena.materials[i].color[3]=m->color[3];
		escena.materials[i].id=i;
		escena.materials[i].ptr_textura=0;
		escena.materials[i].reflection=m->reflection;
		escena.materials[i].refraction=m->refraction;
		escena.materials[i].specular=m->specular;
		escena.materials[i].textura=0;
		escena.materials[i].txt_height=0;
		escena.materials[i].txt_width=0;
	}

	escena.num_groups=scene->groups->count;
    escena.groups=(Group*)aligned_malloc(ALIGMENT,sizeof(Group)*escena.num_groups);
	for(i=0;i<scene->groups->count;++i)
	{
		Group *g=(Group*)list_get(scene->groups,i);
		escena.groups[i].id=i;
		escena.groups[i].material_id=g->material_id;
	}

	escena.num_objects=scene->objects->count;
    escena.objects=(Triangle*)aligned_malloc(ALIGMENT,sizeof(Triangle)*escena.num_objects);

	for(i=0;i<scene->objects->count;++i)
	{
        Triangle *obj=(Triangle*)list_get(scene->objects,i);
		escena.objects[i].group_id=obj->group_id;
        //escena.objects[i].id=i;
        //escena.objects[i].type=obj->type;
        //escena.objects[i].radious=obj->radious;
		
        V_INIT(escena.objects[i].v1,obj->v1[0],obj->v1[1],obj->v1[2]);
        V_INIT(escena.objects[i].v2,obj->v2[0],obj->v2[1],obj->v2[2]);
        V_INIT(escena.objects[i].v3,obj->v3[0],obj->v3[1],obj->v3[2]);
	}

    //BuildBVH();
    //PreprocessObjects();

}

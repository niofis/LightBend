#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "globals.h"
#include "renderer.h"
#include "demos.h"
#include "utils.h"
#include "bvh.h"
#include "luabindings.h"

int threads=1;


long long inicio;
long long fin;


int last_frame=-1;
int frame_count=0;
double max_time=0.0;
double min_time=99999999999.0;
double acc_time=0.0;
char text[256];
int cpu_count=0;

void reset_stats()
{
    last_frame=-1;
	frame_count=0;
	max_time=0.0;
	min_time=99999999999.0;
	acc_time=0.0;
}

void stats(SDL_Surface* screen,double time, int showhelp)
{
	int y=0;


	if(max_time<time)
		max_time=time;
	if(min_time>time)
		min_time=time;
	if(last_frame<frame_count){
		acc_time+=time;
		last_frame=frame_count;
	}

	sprintf(text,"Fps: %8.4f Spf: %8.4f",1/time,time);
	stringColor(screen,0,y,text,~0);

	y+=8;
	sprintf(text,"Avg: %8.4f Max fps: %8.4f Min fps: %8.4f",1/(acc_time/frame_count),1/min_time,1/max_time);
	stringColor(screen,0,y,text,~0);

	y+=8;
	sprintf(text,"Avg: %8.4f Max spf: %8.4f Min spf: %8.4f",acc_time/frame_count,max_time,min_time);
	stringColor(screen,0,y,text,~0);

	y+=8;
	sprintf(text,"Res: %dx%dx%d",width,height,bpp);
	stringColor(screen,0,y,text,~0);

	y+=8;
	sprintf(text,"CPUs: %d Threads: %d",cpu_count,threads);
	stringColor(screen,0,y,text,~0);

	y+=8;
	sprintf(text,"Help (h to toggle)");
	stringColor(screen,0,y,text,~0);	
		
	if(showhelp)
	{


		y+=8;
		sprintf(text,"Numbers 1-9 load demos");
		stringColor(screen,0,y,text,~0);
		
		y+=8;
		sprintf(text,"Number 0 runs lua script");
		stringColor(screen,0,y,text,~0);

		
		y+=8;
		sprintf(text,"c key toggles continuous rendering");
		stringColor(screen,0,y,text,~0);

		y+=8;
		sprintf(text,"n key renders next frame");
		stringColor(screen,0,y,text,~0);
	}
}


int main(int argc, char* args[])
{
	int videoflags=SDL_HWACCEL | SDL_HWSURFACE;
	SDL_Surface* screen;
	SDL_Surface* surface;
	SDL_Event event;
	int done = 0;
	long long freq;
	long long  i,f,q;
	int mouse_y;
	const SDL_VideoInfo *info;
	Uint8 * keys;
	Camara* cam;
	int showhelp=0;
	int continuous=0;
	int render_next=1;

	width=640;
	height=480;
	bpp=32;

	threads=cpu_count=omp_get_num_procs();
	omp_set_dynamic(0);
	omp_set_num_threads(threads);
	omp_set_nested(1);

	q=freq=CLOCKS_PER_SEC;


	if(SDL_Init(SDL_INIT_VIDEO) < 0)

	{
		printf("Error: SDL_Init");
		return 1;
	}

	SDL_WM_SetCaption("cRTu",NULL);

	info = SDL_GetVideoInfo();


	surface = SDL_CreateRGBSurface(videoflags, width, height, bpp, 0, 0, 0, 0);

	screen = SDL_SetVideoMode(width, height,bpp, videoflags);
	if(!screen)
	{
		printf("Error: SDL_SetVideoMode");
		return 2;
	}

	Initialize();

	Demo1();

	while(!done)
	{
		if(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:

					if(event.key.keysym.sym == SDLK_LALT || event.key.keysym.sym == SDLK_TAB)
						break;
					if(event.key.keysym.sym == SDLK_RETURN)
					{

						videoflags ^= SDL_FULLSCREEN;
						SDL_FreeSurface(screen);
						screen = SDL_SetVideoMode(width, height, bpp, videoflags);
						if(!screen)
							done = 1;
						break;
					}
					if(event.key.keysym.sym == SDLK_ESCAPE)
						done=1;
					if(event.key.keysym.sym == SDLK_HOME)
					{
						threads++;
						reset_stats();
					}
					if(event.key.keysym.sym == SDLK_END)
					{
						if(threads>1)
							threads--;
						reset_stats();
					}
					if(event.key.keysym.sym == SDLK_1)
					{
						CleanRenderer();
						Demo1();
						reset_stats();
						render_next=1;
					}
					if(event.key.keysym.sym == SDLK_2)
					{
						CleanRenderer();
						Demo2();
						reset_stats();
						render_next=1;
					}
					if(event.key.keysym.sym == SDLK_3)
					{
						CleanRenderer();
						Demo3();
						reset_stats();
						render_next=1;
					}
					if(event.key.keysym.sym == SDLK_4)
					{
						CleanRenderer();
						Demo4();
						reset_stats();
						render_next=1;
					}
					if(event.key.keysym.sym == SDLK_7)
					{
						CleanRenderer();
						Demo7();
						reset_stats();
						render_next=1;
					}
					
					if(event.key.keysym.sym == SDLK_9)
					{
						CleanRenderer();
						Demo9();
						reset_stats();
						render_next=1;
					}
					if(event.key.keysym.sym == SDLK_0)
					{
						CleanRenderer();
						//run lua script
						runluascript();
						reset_stats();
						render_next=1;
					}
					if(event.key.keysym.sym == SDLK_n)
					{
						render_next=1;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					break;
				case SDL_MOUSEMOTION:
					break;
				case SDL_KEYUP:
					if(event.key.keysym.sym == SDLK_h)
					{
						showhelp^=1;
					}
					if(event.key.keysym.sym == SDLK_c)
					{
						continuous^=1;
					}
					
					break;
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}
		else
		{
			//scene.cameras[0]->Rotate(0.017452 * 2.5,2);
			
			keys=SDL_GetKeyState(NULL); 
			cam = &camaras[0];
			//scene.cameras[0]->Rotate(0.017452 * 2.5,2);
			if(keys[SDLK_UP])
				RotateCamera(cam,0.017452 * 2.5,1);
			if(keys[SDLK_DOWN])
				RotateCamera(cam,0.017452 * -2.5,1);
			if(keys[SDLK_LEFT])
				RotateCamera(cam,0.017452 * -2.5,2);
			if(keys[SDLK_RIGHT])
				RotateCamera(cam,0.017452 * 2.5,2);

			if(keys[SDLK_w])
				MoveCamera(cam,0.0f,0.0f,1.0f);
			if(keys[SDLK_s])
				MoveCamera(cam,0.0f,0.0f,-1.0f);
			if(keys[SDLK_a])
				MoveCamera(cam,-1.0f,0.0f,0.0f);
			if(keys[SDLK_d])
				MoveCamera(cam,1.0f,0.0f,0.0f);
			if(keys[SDLK_q])
				MoveCamera(cam,0.0f,1.0f,0.0f);
			if(keys[SDLK_e])
				MoveCamera(cam,0.0f,-1.0f,0.0f);



		}

		//Render


		if(continuous || render_next)
		{
			i=clock();

			SDL_LockSurface(surface);
			RenderFrame(surface->pixels,threads);
			SDL_UnlockSurface(surface);

			f=clock();
			render_next=0;
			frame_count++;
		}

SDL_BlitSurface(surface, NULL, screen, NULL);
		stats(screen,(double)((double)(f-i)/(double)q),showhelp);

		SDL_Flip(screen);


	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(surface);
	SDL_Quit();

	CleanBVH();
	CleanRenderer();

	return 0;
}


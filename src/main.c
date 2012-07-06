#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include "image.h"
#include "globals.h"
#include "renderer.h"
#include "demos.h"
#include "utils.h"
#include "bvh.h"
#include "luabindings.h"


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
	stringColor(screen,0,y,text,0xFFFFFFFF);

	y+=8;
	sprintf(text,"Avg: %8.4f Max fps: %8.4f Min fps: %8.4f",1/(acc_time/frame_count),1/min_time,1/max_time);
	stringColor(screen,0,y,text,0xFFFFFFFF);

	y+=8;
	sprintf(text,"Avg: %8.4f Max spf: %8.4f Min spf: %8.4f",acc_time/frame_count,max_time,min_time);
	stringColor(screen,0,y,text,0xFFFFFFFF);

	y+=8;
	sprintf(text,"Res: %dx%dx%d",job.width,job.height,bpp);
	stringColor(screen,0,y,text,0xFFFFFFFF);

	y+=8;
	sprintf(text,"CPUs: %d Threads: %d",cpu_count,job.threads);
	stringColor(screen,0,y,text,0xFFFFFFFF);

	y+=8;
	sprintf(text,"Help (h to toggle)");
	stringColor(screen,0,y,text,0xFFFFFFFF);	
		
	if(showhelp)
	{
		y+=8;
		sprintf(text,"Numbers 1-9 load demos");
		stringColor(screen,0,y,text,0xFFFFFFFF);
		
		y+=8;
		sprintf(text,"Number 0 runs lua script");
		stringColor(screen,0,y,text,0xFFFFFFFF);

		
		y+=8;
		sprintf(text,"c key toggles continuous rendering");
		stringColor(screen,0,y,text,0xFFFFFFFF);

		y+=8;
		sprintf(text,"n key renders next frame");
		stringColor(screen,0,y,text,0xFFFFFFFF);

		y+=8;
		sprintf(text,"i key saves current image.png");
		stringColor(screen,0,y,text,0xFFFFFFFF);

		y+=8;
		sprintf(text,"o key saves current image.png with frame info");
		stringColor(screen,0,y,text,0xFFFFFFFF);
	}
}

void process_args(int argc, char* args[])
{
	int i=0;

	job.width=640;
	job.height=480;
	job.sector_y=0;
	job.sector_x=0;
	job.sector_width=job.width;
	job.sector_height=job.height;
	job.interactive=0;
	job.img_file="image.png";
	job.lua_script="script.lua";
	job.verbose=0;
	job.threads=0;
    job.run_script=0;


	for(i=0;i<argc;++i)
	{
		if(strcmp("-width",args[i])==0)
			job.width=abs(atoi(args[++i]));
		else if(strcmp("-height",args[i])==0)
			job.height=abs(atoi(args[++i]));
		else if(strcmp("-s ",args[i])==0)
		{
			job.sector_x=abs(atoi(args[++i]));
			job.sector_y=abs(atoi(args[++i]));
			job.sector_width=abs(atoi(args[++i]));
			job.sector_height=abs(atoi(args[++i]));
		}
		else if(strcmp("-i",args[i])==0)
			job.interactive=1;
		else if(strcmp("-v",args[i])==0)
			job.verbose=1;
		else if(strcmp("-png",args[i])==0)
			job.img_file=args[++i];
		else if(strcmp("-script",args[i])==0)
        {
			job.lua_script=args[++i];
            job.run_script=1;
        }
		else if(strcmp("-threads",args[i])==0)
			job.threads=abs(atoi(args[++i]));
	}

	if(job.width==0)
		job.width=640;
	if(job.height==0)
		job.height=480;
	if(job.sector_width==0)
		job.sector_width=job.width-job.sector_x;
	if(job.sector_height==0)
		job.sector_height=job.height-job.sector_y;

	//default to interactive mode when no parameters
	if(argc==1)
		job.interactive=1;
}

int interactive_mode()
{
	int videoflags=SDL_HWACCEL | SDL_HWSURFACE;
	SDL_Surface* screen;
	SDL_Surface* surface;
	SDL_Event event;
	int done = 0;
    double start;
    double finish;
	int mouse_y;
	const SDL_VideoInfo *info;
	Uint8 * keys;
	Camera* cam;
	int showhelp=0;
	int continuous=0;
	int render_next=1;


	if(SDL_Init(SDL_INIT_VIDEO) < 0)

	{
		printf("Error: SDL_Init");
		return 1;
	}

	SDL_WM_SetCaption("LightBend",NULL);

	info = SDL_GetVideoInfo();


	surface = SDL_CreateRGBSurface(videoflags, job.width, job.height, bpp, 0, 0, 0, 0);

	screen = SDL_SetVideoMode(job.width, job.height,bpp, videoflags);
	if(!screen)
	{
		printf("Error: SDL_SetVideoMode");
		return 2;
	}

    if(job.run_script==1)
    {
        runluascript(job.lua_script);
    } else
    {
        Demo1();
    }



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
						screen = SDL_SetVideoMode(job.width, job.height, bpp, videoflags);
						if(!screen)
							done = 1;
						break;
					}
					if(event.key.keysym.sym == SDLK_ESCAPE)
						done=1;
					if(event.key.keysym.sym == SDLK_HOME)
					{
						job.threads++;
						reset_stats();
					}
					if(event.key.keysym.sym == SDLK_END)
					{
						if(job.threads>1)
							job.threads--;
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
                        /*
						CleanRenderer();
						Demo9();
						reset_stats();
						render_next=1;
                        */
					}
					if(event.key.keysym.sym == SDLK_0)
					{
						CleanRenderer();
						//run lua script
						runluascript(job.lua_script);
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
					if(event.key.keysym.sym == SDLK_o)
					{
						//save image with info
						SDL_LockSurface(screen);
						save_image(job.img_file,job.width,job.height,(unsigned char*)screen->pixels);
						SDL_UnlockSurface(screen);
					}
					if(event.key.keysym.sym == SDLK_i)
					{
						//save image without info
						SDL_LockSurface(surface);
						save_image(job.img_file,job.width,job.height,(unsigned char*)surface->pixels);
						SDL_UnlockSurface(surface);
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
			cam = &escena.cameras[0];
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
            start=omp_get_wtime();
			SDL_LockSurface(surface);
			RenderFrame((int*)surface->pixels,job.threads);
			SDL_UnlockSurface(surface);
            finish=omp_get_wtime();
			render_next=0;
			frame_count++;
		}

		SDL_BlitSurface(surface, NULL, screen, NULL);
        stats(screen,finish-start,showhelp);

		SDL_Flip(screen);


	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(surface);
    SDL_Quit();

	CleanBVH();
	CleanRenderer();
}

void offline_mode()
{
	double start;
	double finish;
    int* buffer=(int*) aligned_malloc16(job.width*job.height*4);
	
    runluascript(job.lua_script);
	
    printf("Rendering...\n\r");

	start=omp_get_wtime();
    RenderFrame(buffer,job.threads);
	finish=omp_get_wtime();
	
	printf("Done in %8.4f s\n\r",finish-start);
		
    save_image(job.img_file,job.width,job.height,(unsigned char*)buffer);


    CleanBVH();
    CleanRenderer();

    aligned_free(buffer);
}



int main(int argc, char* args[])
{

	#ifdef SSE
	//_MM_SET_FLUSH_ZERO_MOD(_MM_FLUSH_ZERO_ON);
	#endif

    //debug("Init");


	bpp=32;


    #pragma omp critical
    cpu_count=omp_get_num_procs();
	
    process_args(argc, args);

	if(job.threads==0)
		job.threads=cpu_count;
	
    omp_set_dynamic(0);
    omp_set_num_threads(job.threads);
    omp_set_nested(1);


	if(job.interactive==1)
		interactive_mode();
    else
        offline_mode();



    //debug("Exit");

	return 0;
}


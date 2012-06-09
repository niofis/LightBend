#if !defined(GLOBALS)
#define GLOBALS

	#define USE_BVH
	#include <time.h>	
	#include <math.h>
	#include <omp.h>

	#include "memory.h"

	#define ALIGMENT 16

	#define FALSE 0
	#define TRUE ~FALSE

	

	#if defined(WIN32)
		#include <windows.h>
		#define SSE
		#include <mmintrin.h>
		#include <xmmintrin.h>
		#include <intrin.h>
		#define THREAD DWORD __stdcall
		#define CreateThread(f,p) CreateThread(NULL,0,f,p,0,NULL)
		#define align(x) __declspec(align(x))
	#else
			
		#include <pthread.h>
		#define THREAD void*
		#define CreateThread(fc,pc) {pthread_t  handle; pthread_create(&handle,0,fc,pc);}
		#define align(x) __attribute__((aligned(x)))

			
		#define DWORD unsigned short
		#define Sleep(x) usleep(x*1000)
		#define CopyMemory memcpy
		#define LARGE_INTEGER long long
		#define min(x,y) (x<y)?x:y
		#define max(x,y) (x>y)?x:y
	#endif
#endif

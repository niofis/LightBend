#include "utils.h"

int RotateCamera(Camera* camera, float rads, int axis) //1=x 2=y 4=z
{
		//http://www.gamedev.net/reference/articles/article1095.asp
	//Adaptado eje Y, Eje de rotacion (quaternion)

		
	//Rotacion: http://www.gamasutra.com/features/19980703/quaternions_01.htm
	//v = q v q-1 (where v = [0, v]) 
	
	//Multiplicacion de quaterniones: http://www.gamedev.net/reference/articles/article1095.asp
	//w = w1w2 - x1x2 - y1y2 - z1z2
	//x = w1x2 + x1w2 + y1z2 - z1y2
	//y = w1y2 + y1w2 + z1x2 - x1z2
	//z = w1z2 + z1w2 + x1y2 - y1x2 
	
	//http://www.gamedev.net/reference/articles/article1199.asp
	//http://mathworld[2]olfram.com/RodriguesRotationFormula.html
	//float rads=0.017452 * -2.5;
	
	float x =0;// axis==1?1:0;
	float y =0;// axis==2?1:0;
	float z =0;// axis==4?1:0;
	float ax[4]={0,0,0,0};
    //float dir=(rads<0)?-1.0f:1.0f;
	float norm=0;

	float c = cos(rads);
	float s = sin(rads);
	float t = 1-c;

	float sx=0.0f;
	float sy=0.0f;
	float sz=0.0f;

	switch(axis)
	{
		case 1:
		V_SUB(ax,camera->lefttop,camera->righttop);
		norm=V_SIZE(ax);
		V_DIV(ax,norm);
		break;
		case 2:
		V_SUB(ax,camera->lefttop,camera->leftbottom);
		norm=V_SIZE(ax);
		V_DIV(ax,norm);
		break;
		case 3:
		break;
		default:
		return 0;
	}

	x=ax[0];
	y=ax[1];
	z=ax[2];
		



	sx=camera->eye[0];
	sy=camera->eye[1];
	sz=camera->eye[2];
	camera->eye[0] = (((t*x*x)+c)*sx) + (((t*x*y) + (s*z))*sy) + (((t*x*z)-(s*y))*sz); 
	camera->eye[1] = (((t*x*y)-(s*z))*sx) + (((t*y*y)+c)*sy) + (((t*y*z)+(x*s))*sz); 
	camera->eye[2] = (((t*x*z)+(s*y))*sx) + (((t*y*z)-(s*x))*sy) + (((t*z*z)+c)*sz);

	
	sx=camera->lefttop[0];
	sy=camera->lefttop[1];
	sz=camera->lefttop[2];
	camera->lefttop[0] = (((t*x*x)+c)*sx) + (((t*x*y) + (s*z))*sy) + (((t*x*z)-(s*y))*sz); 
	camera->lefttop[1] = (((t*x*y)-(s*z))*sx) + (((t*y*y)+c)*sy) + (((t*y*z)+(x*s))*sz); 
	camera->lefttop[2] = (((t*x*z)+(s*y))*sx) + (((t*y*z)-(s*x))*sy) + (((t*z*z)+c)*sz);
	
	sx=camera->righttop[0];
	sy=camera->righttop[1];
	sz=camera->righttop[2];
	camera->righttop[0] = (((t*x*x)+c)*sx) + (((t*x*y) + (s*z))*sy) + (((t*x*z)-(s*y))*sz); 
	camera->righttop[1] = (((t*x*y)-(s*z))*sx) + (((t*y*y)+c)*sy) + (((t*y*z)+(x*s))*sz); 
	camera->righttop[2] = (((t*x*z)+(s*y))*sx) + (((t*y*z)-(s*x))*sy) + (((t*z*z)+c)*sz);
	
	sx=camera->leftbottom[0];
	sy=camera->leftbottom[1];
	sz=camera->leftbottom[2];
	camera->leftbottom[0] = (((t*x*x)+c)*sx) + (((t*x*y) + (s*z))*sy) + (((t*x*z)-(s*y))*sz); 
	camera->leftbottom[1] = (((t*x*y)-(s*z))*sx) + (((t*y*y)+c)*sy) + (((t*y*z)+(x*s))*sz); 
	camera->leftbottom[2] = (((t*x*z)+(s*y))*sx) + (((t*y*z)-(s*x))*sy) + (((t*z*z)+c)*sz);

	return 0;
}

int MoveCamera(Camera* camera, float dx, float dy, float dz)
{
	float vtc_x[3];
	float vtc_y[3];
	float vtc_z[3];
	float n;

	V_SUB(vtc_x,camera->righttop,camera->lefttop);
	n=V_SIZE(vtc_x);
	V_DIV(vtc_x,n);
	
	V_SUB(vtc_y,camera->leftbottom,camera->lefttop);
	n=V_SIZE(vtc_y);
	V_DIV(vtc_y,n);

	V_CROSS(vtc_z,vtc_y,vtc_x);
	n=V_SIZE(vtc_z);
	V_DIV(vtc_z,n);

	V_MUL(vtc_x,dx);
	V_MUL(vtc_y,dy);
	V_MUL(vtc_z,dz);

	V_ADD(camera->eye,camera->eye,vtc_x);
	V_ADD(camera->eye,camera->eye,vtc_y);
	V_ADD(camera->eye,camera->eye,vtc_z);

	V_ADD(camera->lefttop,camera->lefttop,vtc_x);
	V_ADD(camera->lefttop,camera->lefttop,vtc_y);
	V_ADD(camera->lefttop,camera->lefttop,vtc_z);

	V_ADD(camera->righttop,camera->righttop,vtc_x);
	V_ADD(camera->righttop,camera->righttop,vtc_y);
	V_ADD(camera->righttop,camera->righttop,vtc_z);

	V_ADD(camera->leftbottom,camera->leftbottom,vtc_x);
	V_ADD(camera->leftbottom,camera->leftbottom,vtc_y);
	V_ADD(camera->leftbottom,camera->leftbottom,vtc_z);

	return 0;
}

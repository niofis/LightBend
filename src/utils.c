#include "utils.h"

int RotateCamera(Camara* camara, float rads, int axis) //1=x 2=y 4=z
{
		//http://www.gamedev.net/reference/articles/article1095.asp
	//Adaptado eje Y, Eje de rotacion (quaternion)

		
	//Rotacion: http://www.gamasutra.com/features/19980703/quaternions_01.htm
	//v´ = q v q-1 (where v = [0, v]) 
	
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
	float dir=(rads<0)?-1.0f:1.0f;
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
		V_SUB(ax,camara->lefttop,camara->righttop);
		norm=V_SIZE(ax);
		V_DIV(ax,norm);
		break;
		case 2:
		V_SUB(ax,camara->lefttop,camara->leftbottom);
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
		



	sx=camara->eye[0];
	sy=camara->eye[1];
	sz=camara->eye[2];
	camara->eye[0] = (((t*x*x)+c)*sx) + (((t*x*y) + (s*z))*sy) + (((t*x*z)-(s*y))*sz); 
	camara->eye[1] = (((t*x*y)-(s*z))*sx) + (((t*y*y)+c)*sy) + (((t*y*z)+(x*s))*sz); 
	camara->eye[2] = (((t*x*z)+(s*y))*sx) + (((t*y*z)-(s*x))*sy) + (((t*z*z)+c)*sz);

	
	sx=camara->lefttop[0];
	sy=camara->lefttop[1];
	sz=camara->lefttop[2];
	camara->lefttop[0] = (((t*x*x)+c)*sx) + (((t*x*y) + (s*z))*sy) + (((t*x*z)-(s*y))*sz); 
	camara->lefttop[1] = (((t*x*y)-(s*z))*sx) + (((t*y*y)+c)*sy) + (((t*y*z)+(x*s))*sz); 
	camara->lefttop[2] = (((t*x*z)+(s*y))*sx) + (((t*y*z)-(s*x))*sy) + (((t*z*z)+c)*sz);
	
	sx=camara->righttop[0];
	sy=camara->righttop[1];
	sz=camara->righttop[2];
	camara->righttop[0] = (((t*x*x)+c)*sx) + (((t*x*y) + (s*z))*sy) + (((t*x*z)-(s*y))*sz); 
	camara->righttop[1] = (((t*x*y)-(s*z))*sx) + (((t*y*y)+c)*sy) + (((t*y*z)+(x*s))*sz); 
	camara->righttop[2] = (((t*x*z)+(s*y))*sx) + (((t*y*z)-(s*x))*sy) + (((t*z*z)+c)*sz);
	
	sx=camara->leftbottom[0];
	sy=camara->leftbottom[1];
	sz=camara->leftbottom[2];
	camara->leftbottom[0] = (((t*x*x)+c)*sx) + (((t*x*y) + (s*z))*sy) + (((t*x*z)-(s*y))*sz); 
	camara->leftbottom[1] = (((t*x*y)-(s*z))*sx) + (((t*y*y)+c)*sy) + (((t*y*z)+(x*s))*sz); 
	camara->leftbottom[2] = (((t*x*z)+(s*y))*sx) + (((t*y*z)-(s*x))*sy) + (((t*z*z)+c)*sz);

	return 0;
}

int MoveCamera(Camara* camara, float dx, float dy, float dz)
{
	float vtc_x[3];
	float vtc_y[3];
	float vtc_z[3];
	float n;

	V_SUB(vtc_x,camara->righttop,camara->lefttop);
	n=V_SIZE(vtc_x);
	V_DIV(vtc_x,n);
	
	V_SUB(vtc_y,camara->leftbottom,camara->lefttop);
	n=V_SIZE(vtc_y);
	V_DIV(vtc_y,n);

	V_CROSS(vtc_z,vtc_y,vtc_x);
	n=V_SIZE(vtc_z);
	V_DIV(vtc_z,n);

	V_MUL(vtc_x,dx);
	V_MUL(vtc_y,dy);
	V_MUL(vtc_z,dz);

	V_ADD(camara->eye,camara->eye,vtc_x);
	V_ADD(camara->eye,camara->eye,vtc_y);
	V_ADD(camara->eye,camara->eye,vtc_z);

	V_ADD(camara->lefttop,camara->lefttop,vtc_x);
	V_ADD(camara->lefttop,camara->lefttop,vtc_y);
	V_ADD(camara->lefttop,camara->lefttop,vtc_z);

	V_ADD(camara->righttop,camara->righttop,vtc_x);
	V_ADD(camara->righttop,camara->righttop,vtc_y);
	V_ADD(camara->righttop,camara->righttop,vtc_z);

	V_ADD(camara->leftbottom,camara->leftbottom,vtc_x);
	V_ADD(camara->leftbottom,camara->leftbottom,vtc_y);
	V_ADD(camara->leftbottom,camara->leftbottom,vtc_z);

	return 0;
}
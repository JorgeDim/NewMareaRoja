#pragma once
#ifndef FUNCIONES_OPENGL_JSM
#define FUNCIONES_OPENGL_JSM 1
#include <math.h>
#include <string.h>
#include "GlutFreeGlut.h"

extern GLuint baseF; 
extern GLuint baseBIT; 

extern float Escala;
extern  GLfloat   MatrizRotacionGlobalINV[16];


class FuncionesOpenGL
{
public:
	static void Print(char s[],int bit=0);
	static void material(int cual=0);
	static void esfera(double R,int N);
	static void cono(double x0,double y0,double z0,double x1,double y1,double z1,double R,int N);

	static void esfera(double x0,double y0,double z0,double R,int N,int N2);
	static void ejes();
	static void ColorF(double minF,double maxF,double lF);
	static void ColorF2(double minF,double maxF,double lF);
	static void ColorF3(float t,int code);
	static void ColorF4(float t,int code);
	static void ActivaLuz0();
	static void Win2World(GLfloat WinX ,GLfloat winY,GLfloat winZ, GLdouble *posX,GLdouble *posY,GLdouble *posZ);
	static void World2Win(GLdouble posX,GLdouble posY,GLdouble posZ, GLdouble *WinX ,GLdouble *winY,GLdouble *winZ);

	static GLint viewport[4];
	static GLdouble modelview[16];
	static GLdouble projection[16];
	static int viewport_calculado;
	static int modelview_calculado;
	static int projection_calculado;

	static void ObtieneMatrices();

};


#endif


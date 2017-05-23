#pragma once
#define FUNCIONES_OPENGL_CPP_JSM 1

#include "FuncionesOpenGL.h"


 int FuncionesOpenGL::viewport_calculado=false;
 int FuncionesOpenGL::modelview_calculado=false;
 int FuncionesOpenGL::projection_calculado=false;
 
 GLint    FuncionesOpenGL::viewport[4]={0,0,0,0};
 GLdouble FuncionesOpenGL::modelview[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
 GLdouble FuncionesOpenGL::projection[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
 extern  float FactorAmbient,FactorDifusse,FactorSpecular,FactorEmission;



void FuncionesOpenGL::Print(char s[],int bit)
{

	if (bit==0) {
		glListBase(baseF); 
		glCallLists(strlen(s), GL_UNSIGNED_BYTE, s); 
	} else {
		glListBase(baseBIT); 
		glCallLists(strlen(s), GL_UNSIGNED_BYTE, s); 
	}
}


void FuncionesOpenGL::ejes()
{	
	int i,j;
	glPushAttrib( GL_LIGHTING_BIT );
    glDisable( GL_LIGHTING );

	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(10, 0, 0);
	glEnd();
	glBegin(GL_LINES);
	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 10, 0);
	glEnd();
	glBegin(GL_LINES);
	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0,10);
	glEnd();

	for (i=0;i<=10;i++) {
		glColor3d(0.3, 0.3, 0.1);
		glBegin(GL_LINES);
		glVertex3d( 0, i, 0);
		glVertex3d(10, i, 0);
		glEnd();
		glBegin(GL_LINES);
		glVertex3d(i,  0, 0);
		glVertex3d(i, 10, 0);
		glEnd();
		if (i<10) {
			for (j=1;j<10;j++) {
				glColor3d(0.1, 0.1, 0.1);
				glBegin(GL_LINES);
				glVertex3d( 0, i+0.1*j, 0);
				glVertex3d(10, i+0.1*j, 0);
				glEnd();
				glBegin(GL_LINES);
				glVertex3d(i+0.1*j,  0, 0);
				glVertex3d(i+0.1*j, 10, 0);
				glEnd();
			}
		}
	}

	glPopAttrib();

}
void FuncionesOpenGL::Win2World(GLfloat WinX ,GLfloat WinY,GLfloat WinZ, GLdouble *posX,GLdouble *posY,GLdouble *posZ)
{

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	gluUnProject( WinX, WinY, WinZ, modelview, projection, viewport, posX, posY, posZ);
}
void FuncionesOpenGL::World2Win(GLdouble posX,GLdouble posY,GLdouble posZ, GLdouble *WinX ,GLdouble *WinY,GLdouble *WinZ)
{

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );
	gluProject( posX, posY, posZ, modelview, projection, viewport, WinX, WinY, WinZ );
}


void FuncionesOpenGL::ObtieneMatrices()
{
	if (!modelview_calculado) glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	if (!projection_calculado) 			glGetDoublev( GL_PROJECTION_MATRIX, projection );
	if (!viewport_calculado) 			glGetIntegerv( GL_VIEWPORT, viewport );
	modelview_calculado=true;
	projection_calculado=true;
	viewport_calculado=true;

}

void FuncionesOpenGL::esfera(double R,int N)
{

	int i,j;
	double pi=4*atan((double)1);
	double dt=pi/N,dt2,u,v;

//glEnable(GL_NORMALIZE);

	for (j=0;j<N;j++) {
		int N2=2*N;
			dt2=2*pi/N2;
		for (i=0;i<N2;i++){
			u=i*dt2;
			v=j*dt;
			glBegin(GL_QUADS);
//			glNormal3d(sin(v+dt/2)*cos(u+dt2/2)*Escala, sin(v+dt/2)*sin(u+dt2/2)*Escala, cos(v+dt/2)*Escala);
						glNormal3d(sin(v)*cos(u)*Escala, sin(v)*sin(u)*Escala, cos(v)*Escala);
			glVertex3d(R*sin(v)*cos(u), R*sin(v)*sin(u), R*cos(v));
			u+=dt2;
						glNormal3d(sin(v)*cos(u)*Escala, sin(v)*sin(u)*Escala, cos(v)*Escala);
			glVertex3d(R*sin(v)*cos(u), R*sin(v)*sin(u), R*cos(v));
			v+=dt;
						glNormal3d(sin(v)*cos(u)*Escala, sin(v)*sin(u)*Escala, cos(v)*Escala);
			glVertex3d(R*sin(v)*cos(u), R*sin(v)*sin(u), R*cos(v));
			u-=dt2;
					glNormal3d(sin(v)*cos(u)*Escala, sin(v)*sin(u)*Escala, cos(v)*Escala);
			glVertex3d(R*sin(v)*cos(u), R*sin(v)*sin(u), R*cos(v));
			glEnd();
		}
	}

}

void FuncionesOpenGL::ColorF(double minF,double maxF,double lF)
{
	
	GLfloat mat_ambient[3] ; 
	GLfloat mat_diffuse[3] ;
	GLfloat mat_specular[3];
	double t;
	GLfloat r,g,b;
	t=(lF-minF)/(maxF-minF);
	if (t<.3) {
		r=0;
		g=t/.3;
		b=1;
	} else if (t<.5) {
		r=0;
		g=1;
		b=(.5-t)/.2;
	} else if (t<.7) {
		r=(t-.5)/.2;
		g=1;
		b=0;
	} else {
		r=1;
		g=(1-t)/.3;
		b=0;
	}
	r=sqrt(r);g=sqrt(g);b=sqrt(b);
	if (0) {	
		glColor3d(r,g,b);
	} else {
		mat_ambient[0]=r/3 ;
		mat_ambient[1]=g/3 ;
		mat_ambient[2]=b/3 ;
		mat_diffuse[0]=r/2 ;
		mat_diffuse[1]=g/2 ;
		mat_diffuse[2]=b/2 ;
		mat_specular[0]=r ;
		mat_specular[1]=g ;
		mat_specular[2]=b ;

		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
//		glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_specular);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_ambient);
	}
}


void FuncionesOpenGL::ColorF2(double minF,double maxF,double lF)
{

	GLfloat mat_ambient[3] ;
	GLfloat mat_diffuse[3] ;
	GLfloat mat_specular[3];
	double t;
	GLfloat r,g,b;
	t=(lF-minF)/(maxF-minF);
	r=t;
	g=0;
	b=1-t;
	r=sqrt(r);g=sqrt(g);b=sqrt(b);
	if (0) {
		glColor3d(r,g,b);
	} else {
		mat_ambient[0]=r/3 ;
		mat_ambient[1]=g/3 ;
		mat_ambient[2]=b/3 ;
		mat_diffuse[0]=r/2 ;
		mat_diffuse[1]=g/2 ;
		mat_diffuse[2]=b/2 ;
		mat_specular[0]=r ;
		mat_specular[1]=g ;
		mat_specular[2]=b ;

		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
//		glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_specular);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_ambient);
	}
}

void FuncionesOpenGL::ColorF3(float t,int code)
{

	GLfloat mat_ambient[3] ;
	GLfloat mat_diffuse[3] ;
	GLfloat mat_specular[3];
	GLfloat r,g,b;
#if 0
	if (t>0.5) {
		r=1-1.4*(1-t);
		g=.5-1.0*(1-t);
		b=.5*(1-t);
	} else {
		r=1-1.4*(1-t)+0.4*(1-2*t);
		g=0*t*(1-t);
		b=.5*(1-t);
	}
#endif
	r=0;g=1;b=0;
	if (t<0.7) {
		r=1;g=0;b=0;
	}
	if (t<0.3) {
		r=0;g=0;b=1;
	}
	//r=sqrt(r);g=sqrt(g);b=sqrt(b);
	if (code==1) {
		glColor3f(r,g,b);
	} else {
		mat_ambient[0]=r/3 ;
		mat_ambient[1]=g/3 ;
		mat_ambient[2]=b/3 ;
		mat_diffuse[0]=r/2 ;
		mat_diffuse[1]=g/2 ;
		mat_diffuse[2]=b/2 ;
		mat_specular[0]=r ;
		mat_specular[1]=g ;
		mat_specular[2]=b ;

		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
//		glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
		glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_specular);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_ambient);
	}
}


void FuncionesOpenGL::material(int cual)
{

	//Defino un material Rojo
	GLfloat mat_ambient_negro[] = {0.05, 0.05, 0.05, 1.0f};
	GLfloat mat_diffuse_negro[] = { 0.0, 0.0, 0.0, 1.0f};
	GLfloat mat_specular_negro[] = {0.08, 0.08, 0.08, 1.0f};
	//Defino un material Rojo
	GLfloat mat_ambient_toro[] = {0.25, 0.05, 0.05, 1.0f};
	GLfloat mat_diffuse_toro[] = { 0.8, 0.0, 0.0, 1.0f};
	GLfloat mat_specular_toro[] = {0.9, 0.08, 0.08, 1.0f};
	//Defino un material Rojo
	GLfloat mat_rojo2_ambient[] =  {0.2, 0.05 , 0.05 , 1.0f}; 
	GLfloat mat_rojo2_diffuse[] =  {0.4, 0.1  , 0.1  , 1.0f};
	GLfloat mat_rojo2_specular[] = {0.6, 0.15 , 0.15 , 1.0f};
	GLfloat mat_rojo2_emission[] = {0.1, 0.025, 0.025, 1.0f};
	//Defino un material Azul
	GLfloat mat_azul2_ambient[] =  {0.05, 0.05 , 0.25 , 1.0f};
	GLfloat mat_azul2_diffuse[] =  {0.1, 0.1  , 0.4  , 1.0f};
	GLfloat mat_azul2_specular[] = {0.15, 0.15 , 0.6 , 1.0f};
	GLfloat mat_azul2_emission[] = {0.025, 0.025, 0.1, 1.0f};
	//Defino un material Verde
	GLfloat mat_verde2_ambient[] =  {0.05, 0.25 , 0.05 , 1.0f};
	GLfloat mat_verde2_diffuse[] =  {0.1, 0.4  , 0.1  , 1.0f};
	GLfloat mat_verde2_specular[] = {0.15, 0.6 , 0.15 , 1.0f};
	GLfloat mat_verde2_emission[] = {0.025, 0.1, 0.025, 1.0f};
	
	GLfloat mat_3_ambient[] =  {0.1, 0.2 , 0.05 , 1.0f}; 
	GLfloat mat_3_diffuse[] =  {0.3, 0.4  , 0.1  , 1.0f};
	GLfloat mat_3_specular[] = {0.4, 0.6 , 0.15 , 1.0f};
	GLfloat mat_3_emission[] = {0.1, 0.15, 0.025, 1.0f};

	GLfloat matBC_2_ambient[] =  {0.1, 0.0 , 0.05 , 1.0f}; 
	GLfloat matBC_2_diffuse[] =  {0.3, 0.0  , 0.1  , 1.0f};
	GLfloat matBC_2_specular[] = {0.4, 0.0 , 0.15 , 1.0f};
	GLfloat matBC_2_emission[] = {0.1, 0.0, 0.025, 1.0f};

	GLfloat matBC_3_ambient[] =  {0.0, 0.2 , 0.05 , 1.0f}; 
	GLfloat matBC_3_diffuse[] =  {0.0, 0.4  , 0.1  , 1.0f};
	GLfloat matBC_3_specular[] = {0.0, 0.6 , 0.15 , 1.0f};
	GLfloat matBC_3_emission[] = {0.0, 0.15, 0.025, 1.0f};


	GLfloat  mat_ambient_1[] = {0.15, 0.15, 0.25, 1.0f}; 
	GLfloat  mat_diffuse_1[] = { 0.2, 0.25, 0.35, 1.0f};
	GLfloat mat_specular_1[] = {0.5, 0.05, 0.5, 1.0f};

	float faclara=1.7;
	GLfloat  mat_ambient_1b[] = {0.3*faclara*FactorAmbient, 0.3*faclara*FactorAmbient, 0.50*faclara*FactorAmbient, 1.0f};
	GLfloat  mat_diffuse_1b[] = {0.20*faclara*0.4*FactorDifusse, 0.25*faclara*0.4*FactorDifusse, 0.35*faclara*0.4*FactorDifusse, 1.0f};
	GLfloat mat_specular_1b[] = {0.03*FactorSpecular        , 0.1*FactorSpecular          , 0.02*FactorSpecular         , 1.0f};
	GLfloat mat_emission_1b[] = {0.15*.5*FactorEmission         , 0.15*.5*FactorEmission         , 0.15*.6*FactorEmission       , 1.0f};

	
	switch (cual) 
	{
	case 100:
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 50.0f);
		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient_negro);
		glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_negro);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_negro);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_ambient_negro);
		break;
	case 0:
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 50.0f);
		glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient_toro);
		glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_toro);
		glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_toro);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  mat_ambient_toro);
		break;
	case 2:
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 10.1f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , mat_rojo2_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , mat_rojo2_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , mat_rojo2_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION , mat_rojo2_emission);
		break;
	case 3:
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 10.1f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , mat_3_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , mat_3_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , mat_3_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION , mat_3_emission);
		break;

	case 1:
	case 11:
		
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 5000.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT , mat_ambient_1b);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE , mat_diffuse_1b);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular_1b);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission_1b);
		break;
	case 12:
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 10.1f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , matBC_2_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , matBC_2_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , matBC_2_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION , matBC_2_emission);
		break;
	case 13:
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 10.1f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , matBC_3_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , matBC_3_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , matBC_3_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION , matBC_3_emission);
		break;


	case 20:
	case 22:
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 10.1f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , mat_verde2_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , mat_verde2_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , mat_verde2_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION , mat_verde2_emission);
		break;
	case 21:
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 10.1f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , mat_azul2_ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , mat_azul2_diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , mat_azul2_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION , mat_azul2_emission);
		break;


		GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; //set the material to red
		GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; //set the material to white
		GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; //set the material to green
		GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set the light specular to white
		GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
		GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set the diffuse light to white
		GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; //set the diffuse light to white
		GLfloat mShininess[] = {128}; //set the shininess of the material


		//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
		//	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);

		//	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, greenEmissiveMaterial);
	} 

}
void FuncionesOpenGL::ActivaLuz0()
{

	GLfloat light_ambient[] = { 0.75, 0.75, 0.75, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 10.0, 0.0 };
	GLfloat light2_position[] = { -2.0, -2.0, 10.0, 0.0 };
	glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT0, GL_POSITION, light_position);

	glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv (GL_LIGHT1, GL_POSITION, light_position);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
}


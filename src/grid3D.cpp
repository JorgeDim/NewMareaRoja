//#pragma once
#include <stdio.h>
#include "grid3D.h"
#include "Class_Vector.h"
#include "Macros.h"

#include "GlutFreeGlut.h"
#include "FuncionesOpenGL.h"



int largoCola=maxpasadas/4;
extern char  text[200];

extern GLuint textureID;
extern GLuint textureID2;
extern GLUI *glui;
extern GLUI_TextBox *glui_edittext;
extern int Etapa;
extern float FactorZ;

extern ofstream myfileSalida;
extern float GlobalCentros;
extern void tic();
extern void toc();
extern int Add_Voronoi;
extern int DibujaSupInf;
extern int PrintMouse,PrintLinea,PrintTiempos,PrintCaras,PrintInvert,PrintInicio,PrintFunciones,PrintParametros,PrintLecturas,PrintDZmin,PrintVecinos1;

extern float Tsimulacion,TsimulacionP,TColaP;
extern vector<vector<double> > U,V,W;
extern int step;
extern float stepf;
extern double FactorVel;
extern int FlagMuestraCaraSuperior,FlagMuestraCaraInferior;
extern int FlagDibujaLineas;
extern int Algunos_Porcentaje;

extern int FlagCaraSuperiorTransparente,FlagCaraSuperiorTextura,FlagCaraInferiorTextura;


GLfloat *GLfloat_buffer ;
int nParticulas=0;
int GL_threads=10;
int GL_immediate_mode=1;
double ThetaMax,ThetaMin,dTheta_med;
static vector<double> Particulas[maxpasadas+1][3];
static vector<double> Particulas0[3];
vector<float> ParticulasZ;
vector<float> ParticulasZlambda;
static vector<int> ParticulasBloq;
static vector<int> ParticulaEsAleatoria;
int primerdrawVelGL=1;


int npasadas=1;
int jprevio;
int multiplode3=0,deltade3;
float Hz;
extern GLUI_Spinner *Spinner_particulas;


double xx0,yy0,zz0,xx1,yy1,zz1,xx2,yy2,zz2;
int xxi;
int Dibuja3puntos=false;

#define sqr(x) ((x)*(x))

extern int VersionDatos;
extern int ModoDibujaAlgunos;
extern vector<int> CualesCarasDibuja;
extern vector<int> CualesBloquesDibuja;
extern double FactorCercania;
extern float TLimite;
extern int TLimite_if;
extern void ZGlobal(double*v);
extern int NumON;
extern float NumEscala;
extern int Modo_DibujaEdges,ModoDibujaNormales;
extern int ModoDibujaInterior;
extern int ModoDibujaFrontera;
extern int Modo_DibujaCentroCaras;
extern int Modo_DibujaCentroBloques;
extern double Dominio_Rint,Dominio_Rmed,Dominio_Xmax,Dominio_Hsup;
extern float FactorAchica,FactorAchicaV;

extern int MODO_CampoVelocidades,MODO_Origen,MODO_Pausa;


void filtracomentario(ifstream &myfile) {
	//	return;
	int i,j;
	int DBG1=0;
	std::streampos pos ,ppos;
	if(DBG1==1) cout<<"filtracomentario"<<endl;

	int comentario=1;
	string line;

	char ch[20],ch2[20];

	//fijo la secuencia de 20 caracteres a leer
	int i2=0;
	for (i=0;i<20;i++) {
		myfile.get(ch[i]);
		if(DBG1==1) cout<<"i="<<i<<"\tch[i]="<<ch[i]<<"="<<(int)ch[i]<<endl;
		if (i==0 && ((int)ch[i])!=10) {
			i--;
			i2++;
			if (i2>100) exit(1);
		}
		if (i==1 && ((int)ch[i])==10) {
			i--; //Avanzo dor return seguidos
		}
	}

	pos=myfile.tellg(); //posicion final de la secuencia
	for (ppos=pos ; ppos>pos-500LL ; ppos -= 1LL){ //busco la secuencia en [ppos]
		myfile.seekg(ppos);
		if(1==0)cout<<"Trato ppos="<<ppos<<endl;

		for (j=0;j<20;j++) {
			myfile.get(ch2[j]);
			if(1==0)cout<<"ch2[j]="<<ch2[j]<<"="<<(int)ch2[j]<<endl;
			if (ch[j]!=ch2[j]) {
				if(1==0)cout<<"nop"<<endl;
				break;
			}
		}
		if (j==20) {
			if(1==0) cout<<"sip"<<endl;
			break;
		}
	}

	myfile.seekg(ppos); //Testeo la ubicación [ppos]

	if(DBG1==1) cout<<"Testeo la ubicación [ppos]="<<ppos<<endl;
	for (j=0;j<20;j++) {
		myfile.get(ch2[j]);
		if(DBG1==1) cout<<"j="<<j
				<<"\tch2[j]="<<ch2[j]<<"="<<(int)ch2[j]
													 <<"\tch[j]="<<ch[j]<<"="<<(int)ch[j]
																					   <<endl;
		if (ch[j]!=ch2[j]) break;
	}

	myfile.seekg(ppos); //Comienzo la busqueda en la ubicación [ppos]


	long long int deltapos=0LL;
	getline(myfile,line);// <<endl
	if(1==0) cout<<"line="<<line<<endl;
	while (comentario){
		getline(myfile,line);
		if(1==0) cout<<"line="<<line<<endl;
		if (line.length() > 0 && (line[0] == '#' || line[0] == ':' || line[0] == 'H'  )) {

			if(DBG1==1) cout<<"Comentario:"<<line<<endl;
			comentario=1;
			deltapos += line.length()+1;
		}
		else //Encontre una nueva linea
		{
			comentario=0;
			if(DBG1==1) {
				myfile.seekg(ppos+deltapos); //Test 1
				char ch;
				cout<<"deltapos="<<deltapos<<endl;
				cout<<"test1 (aqui seguiria la lectura)"<<endl;
				myfile.get(ch);cout<<"ch="<<ch<<"="<<(int)ch<<endl;
				myfile.get(ch);cout<<"ch="<<ch<<"="<<(int)ch<<endl;
				myfile.get(ch);cout<<"ch="<<ch<<"="<<(int)ch<<endl;
				myfile.get(ch);cout<<"ch="<<ch<<"="<<(int)ch<<endl;
				myfile.seekg(ppos+deltapos); //Test 2
				cout<<"test2 (aqui seguiria la lectura, getline)"<<endl;
				getline(myfile,line);cout<<"line1="<<line<<endl;
				getline(myfile,line);cout<<"line2="<<line<<endl;
				getline(myfile,line);cout<<"line3="<<line<<endl;
				getline(myfile,line);cout<<"line4="<<line<<endl;
				getline(myfile,line);cout<<"line5="<<line<<endl;
				getline(myfile,line);cout<<"line6="<<line<<endl;
				getline(myfile,line);cout<<"line7="<<line<<endl;
				getline(myfile,line);cout<<"line8="<<line<<endl;
			}


			myfile.seekg(ppos+deltapos); //Return
		}
	}

	if(DBG1==1) cout<<"filtracomentario():END"<<endl;
}


double ppunto(R3 a,R3 b) {
	return(a.x*b.x+a.y*b.y+a.z*b.z);
}
R3 pcruz(R3 a,R3 b) {
	R3 c;
	c.x=a.y*b.z-a.z*b.y;
	c.y=a.z*b.x-a.x*b.z;
	c.z=a.x*b.y-a.y*b.x;

	return(c);
}

double ppuntodiff(R3 N,R3 b,R3 c) {
	// N \cdot (b-c)
	return(N.x*(b.x-c.x)+N.y*(b.y-c.y)+N.z*(b.z-c.z));
}

grid3D::grid3D(void)
{
}

grid3D::~grid3D(void)
{
}


void R3::save(ofstream &myfile) {
	if(DBG) cout<<"R3::save(ofstream &myfile)"<<endl;
	if (binario) {
		if (DBG) cout<<"[x,y,z,l]=["<<x<<","<<y<<","<<z<<","<<L<<"]"<<endl;
		myfile.write((char*)&x,sizeof(x)*4);
	} else {
		myfile  <<x<<" "<<y<<" "<<z<<" "<<L<<endl;
	}
	if(DBG) cout<<"R3::save(ofstream &myfile):END"<<endl;
}

void R3::read(ifstream &myfile) {
	if (binario) {
		myfile.read((char*)&x,sizeof(x)*4);
	} else {
		myfile  >>x	>>y	>>z	>>L;
	}
	if(1==0) cout<<"R3:x="<<x<<"\ty="<<y<<"\tz="<<z<<"\tL="<<L<<endl;
}


void Vertex3D::save(ofstream &myfile) {

	if (binario) {
		myfile.write((char*)&no,sizeof(no));
		myfile.write((char*)&x,sizeof(x)*3);
	} else {
		myfile  <<no<<" "<<x<<" "<<y<<" "<<z<<endl;
	}
}

void Vertex3D::read(ifstream &myfile,grid3D *papaL) {

	if (binario) {
		myfile.read((char*)&no,sizeof(no));
		myfile.read((char*)&x,sizeof(x)*3);
	} else {
		myfile  >>no	>>x	>>y	>>z;
	}
	papa=papaL;

	//	cout <<"no="<<no<<"\tx="<<x<<"\ty="<<y<<"\tz="<<z<<endl;

}

void Hexa3D::save(ofstream &myfile) {
	if (binario) {
	} else {
		myfile  <<"#Hexahedro"<<no<<": Vertices"<<endl;
		myfile  <<no<<" "
				<<iv[0]<<" "
				<<iv[1]<<" "
				<<iv[2]<<" "
				<<iv[3]<<" "
				<<iv[4]<<" "
				<<iv[5]<<" "
				<<iv[6]<<" "
				<<iv[7]<<" "
				<<volumen<<endl;

		myfile  <<"#Caras (6)"<<endl;
		myfile  <<icara[0]<<" "
				<<icara[1]<<" "
				<<icara[2]<<" "
				<<icara[3]<<" "
				<<icara[4]<<" "
				<<icara[5]<<endl;

		centro.save(myfile);

		int i;

		myfile  <<"#Poligonos: NPoligonos,cada Poligono  "<<endl;
		myfile  <<Poligono.size()<<endl;
		for (i=0;i<   Poligono.size();i++)    {
			myfile  <<"#Poligono "<<i<<endl;
			Poligono[i].save(myfile);
		}

		myfile  <<vecino.size()<<endl;
		for (i=0;i<     vecino.size();i++) { myfile<<     vecino[i]<<" "; } myfile<<endl;

		myfile  <<tipo_vecino.size()<<endl;
		for (i=0;i<tipo_vecino.size();i++) { myfile<<tipo_vecino[i]<<" "; } myfile<<endl;

		myfile  <<dibujado.size()<<endl;
		for (i=0;i<   dibujado.size();i++) { myfile<<   dibujado[i]<<" "; } myfile<<endl;

	}

}

void TriPrisma::DrawCentro() {

	// Prisma de base Triangular:
	//    5
	//   /|\
	//  / | \
	// 3-----4
	// |  |  |
	// |  2  |
	// | / \ |
	// |/   \|
	// 0-----1

	double x[6],y[6],z[6],nx,ny,nz;
	int i;
	float lambda=GlobalCentros;
	float lambdaZ=sqrt(GlobalCentros)*1;
	if (DBG) cout <<"TriPrisma::DrawCentro()"<<endl;
	if (CentroDibujado==1) return;
	CentroDibujado=1;
	if (lambdaZ>1)lambdaZ=1;
	for (i=0;i<6;i++) {
		x[i]=lambda*papa->v3D[iv[i]].x+(1-lambda)*centro.x;
		y[i]=lambda*papa->v3D[iv[i]].y+(1-lambda)*centro.y;
		z[i]=lambda*papa->v3D[iv[i]].z+(1-lambda)*centro.z;
	}
	glBegin(GL_TRIANGLES );

	nx=(y[1]-y[0])*(z[2]-z[0])-(z[1]-z[0])*(y[2]-y[0]);
	ny=(z[1]-z[0])*(x[2]-x[0])-(x[1]-x[0])*(z[2]-z[0]);
	nz=(x[1]-x[0])*(y[2]-y[0])-(y[1]-y[0])*(x[2]-x[0]);
	glNormal3f(nx, ny, nz*FactorZ);
	glVertex3d(x[0], y[0],z[0]*FactorZ);
	glVertex3d(x[2], y[2],z[2]*FactorZ);
	glVertex3d(x[1], y[1],z[1]*FactorZ);
	glEnd();
	glBegin(GL_TRIANGLES );
	nx=(y[4]-y[3])*(z[5]-z[3])-(z[4]-z[3])*(y[5]-y[3]);
	ny=(z[4]-z[3])*(x[5]-x[3])-(x[4]-x[3])*(z[5]-z[3]);
	nz=(x[4]-x[3])*(y[5]-y[3])-(y[4]-y[3])*(x[5]-x[3]);
	glNormal3f(nx, ny, nz*FactorZ);
	glVertex3d(x[3], y[3],z[3]*FactorZ);
	glVertex3d(x[4], y[4],z[4]*FactorZ);
	glVertex3d(x[5], y[5],z[5]*FactorZ);
	glEnd();
	glBegin(GL_QUADS );
	nx=(y[1]-y[0])*(z[3]-z[0])-(z[1]-z[0])*(y[3]-y[0]);
	ny=(z[1]-z[0])*(x[3]-x[0])-(x[1]-x[0])*(z[3]-z[0]);
	nz=(x[1]-x[0])*(y[3]-y[0])-(y[1]-y[0])*(x[3]-x[0]);
	glNormal3f(nx, ny, nz*FactorZ);
	glVertex3d(x[0], y[0],z[0]*FactorZ);
	glVertex3d(x[1], y[1],z[1]*FactorZ);
	glVertex3d(x[4], y[4],z[4]*FactorZ);
	glVertex3d(x[3], y[3],z[3]*FactorZ);
	glEnd();
	glBegin(GL_QUADS );
	nx=(y[2]-y[1])*(z[4]-z[1])-(z[2]-z[1])*(y[4]-y[1]);
	ny=(z[2]-z[1])*(x[4]-x[1])-(x[2]-x[1])*(z[4]-z[1]);
	nz=(x[2]-x[1])*(y[4]-y[1])-(y[2]-y[1])*(x[4]-x[1]);
	glNormal3f(nx, ny, nz*FactorZ);
	glVertex3d(x[1], y[1],z[1]*FactorZ);
	glVertex3d(x[2], y[2],z[2]*FactorZ);
	glVertex3d(x[5], y[5],z[5]*FactorZ);
	glVertex3d(x[4], y[4],z[4]*FactorZ);
	glEnd();
	glBegin(GL_QUADS );
	nx=(y[3]-y[0])*(z[2]-z[0])-(z[3]-z[0])*(y[2]-y[0]);
	ny=(z[3]-z[0])*(x[2]-x[0])-(x[3]-x[0])*(z[2]-z[0]);
	nz=(x[3]-x[0])*(y[2]-y[0])-(y[3]-y[0])*(x[2]-x[0]);
	glNormal3f(nx, ny, nz*FactorZ);
	glVertex3d(x[0], y[0],z[0]*FactorZ);
	glVertex3d(x[3], y[3],z[3]*FactorZ);
	glVertex3d(x[5], y[5],z[5]*FactorZ);
	glVertex3d(x[2], y[2],z[2]*FactorZ);
	glEnd();

}

void TriPrisma::save(ofstream &myfile) {
	int i;
	if (binario) {
		myfile.write((char*)&no,sizeof(no));
		//		cout<<"sizeof(iv)="<<sizeof(iv)<<endl;
		myfile.write((char*)iv,sizeof(iv));
		//		cout<<"2sizeof(icara)="<<sizeof(icara)<<endl;
		myfile.write((char*)icara,sizeof(icara));
		centro.save(myfile);

		int psize=Poligono.size();
		//		cout<<"3sizeof(icara)="<<sizeof(icara)<<endl;
		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<   Poligono.size();i++)  Poligono[i].save(myfile);

		psize=vecino.size();
		//		cout<<"4sizeof(icara)="<<sizeof(icara)<<endl;
		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<     vecino.size();i++) 	myfile.write((char*)vecino[i],sizeof(vecino[i]));

		psize=tipo_vecino.size();
		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<     tipo_vecino.size();i++) 	myfile.write((char*)tipo_vecino[i],sizeof(tipo_vecino[i]));

		//		cout<<"5sizeof(icara)="<<sizeof(icara)<<endl;
		psize=dibujado.size();
		myfile.write((char*)&psize,sizeof(psize));
		//		cout<<"6sizeof(icara)="<<sizeof(icara)<<endl;
		for (i=0;i<     dibujado.size();i++) 	myfile.write((char*)dibujado[i],sizeof(dibujado[i]));

	} else {

		myfile  <<"#TriPrisma"<<no<<": no,Vertices[0..5],Vol"<<endl;
		myfile  <<no<<" "<<iv[0]<<" "<<iv[1]<<" "<<iv[2]<<" "<<iv[3]<<" "<<iv[4]<<" "<<iv[5]<<" "<<volumen<<endl;

		myfile  <<"#Caras (5)"<<endl;
		myfile  <<icara[0]<<" "<<icara[1]<<" "<<icara[2]<<" "<<icara[3]<<" "<<icara[4]<<endl;

		centro.save(myfile);


		myfile  <<"#Poligonos: NPoligonos,cada Poligono  "<<endl;
		myfile  <<Poligono.size()<<endl;
		for (i=0;i<   Poligono.size();i++)    {
			myfile  <<"#Poligono "<<i<<endl;
			Poligono[i].save(myfile);
		}

		myfile  <<"#Vecinos: NVecinos,cada Vecino  "<<endl;

		myfile << vecino.size()<<endl;

		for (i=0;i<     vecino.size();i++) 	myfile<<vecino[i]<<" ";
		myfile<<endl;

		myfile  <<"#TipoVecinos: size,cada tipo  "<<endl;
		myfile << tipo_vecino.size()<<endl;
		for (i=0;i<     tipo_vecino.size();i++) 	myfile<<tipo_vecino[i]<<" ";
		myfile<<endl;

		myfile  <<"#dibujado: size,cada uno  "<<endl;
		myfile << dibujado.size()<<endl;
		for (i=0;i<     dibujado.size();i++) 	myfile<<dibujado[i]<<" ";
		myfile<<endl;

	}

}

void VolumenFinito::read(ifstream &myfile,grid3D *papaL) {

	papa=papaL;

	if (DBG) cout<<"VolumenFinito::read(ifstream &myfile,grid3D *papaL)"<<endl;

	int i;
	if (binario) {
		myfile.read((char*)&no,sizeof(no));
		myfile.read((char*)&volumen,sizeof(volumen));
		centro.read(myfile);

		if (DBG) cout<<"473"<<endl;

		int psize;
		myfile.read((char*)&psize,sizeof(psize));		Poligono.resize(psize);
		for (i=0;i<   Poligono.size();i++)  Poligono[i].read(myfile);


		if (DBG) cout<<"480"<<endl;

		myfile.read((char*)&psize,sizeof(psize));		vecino.resize(psize);
		for (i=0;i<     vecino.size();i++) 	myfile.read((char*)&(vecino[i]),sizeof(vecino[i]));

		if (DBG) cout<<"485"<<endl;

		myfile.read((char*)&psize,sizeof(psize));		tipo_vecino.resize(psize);
		for (i=0;i<     tipo_vecino.size();i++) 	myfile.read((char*)&(tipo_vecino[i]),sizeof(tipo_vecino[i]));

		if (DBG) cout<<"490"<<endl;

		myfile.read((char*)&psize,sizeof(psize));		vecino_centro.resize(psize);
		for (i=0;i<   vecino_centro.size();i++)  vecino_centro[i].read(myfile);

		if (DBG) cout<<"495"<<endl;

		myfile.read((char*)&psize,sizeof(psize));		vecino_centro_caraoriginal.resize(psize);
		for (i=0;i<   vecino_centro_caraoriginal.size();i++)  vecino_centro_caraoriginal[i].read(myfile);

		if (DBG) cout<<"500"<<endl;

		myfile.read((char*)&psize,sizeof(psize));		vecino_normal.resize(psize);
		for (i=0;i<   vecino_normal.size();i++)  vecino_normal[i].read(myfile);

		if (DBG) cout<<"505"<<endl;

		myfile.read((char*)&psize,sizeof(psize));		dibujado.resize(psize);
		for (i=0;i<     dibujado.size();i++) 	myfile.read((char*)&(dibujado[i]),sizeof(dibujado[i]));

	} else {

		filtracomentario(myfile);

		cout<<"grid3D.cpp:494: Falta programar esto..."<<endl;
		exit(0);
		if (VersionDatos>=0.099) {
			myfile  >>volumen;
		}

		filtracomentario(myfile);

		centro.read(myfile);

		int i,sizeL;

		filtracomentario(myfile);
		myfile  >> sizeL; Poligono.resize(sizeL);
		if(1==0) cout  <<"sizeL="<< sizeL<<endl;

		for (i=0;i<   Poligono.size();i++)    {

			filtracomentario(myfile);
			Poligono[i].read(myfile);
		}

		myfile  >> sizeL; vecino.resize(sizeL);
		for (i=0;i<     vecino.size();i++) { myfile>>     vecino[i]; }

		myfile  >> sizeL; tipo_vecino.resize(sizeL);
		for (i=0;i<tipo_vecino.size();i++) { myfile>>tipo_vecino[i]; }

		myfile  >> sizeL; dibujado.resize(sizeL);
		for (i=0;i<   dibujado.size();i++) { myfile>>   dibujado[i]; }

	}


	if (DBG) cout<<"VolumenFinito::read(ifstream &myfile,grid3D *papaL):END"<<endl;
}



void VolumenFinito::save(ofstream &myfile) {
	int i;
	if (DBG) cout<<"VolumenFinito::save(ofstream &myfile)"<<endl;

	if (binario) {


		myfile.write((char*)&no,sizeof(no));
		myfile.write((char*)&volumen,sizeof(volumen));
		centro.save(myfile);

		if (DBG) cout<<"542"<<endl;

		int psize=Poligono.size();
		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<   Poligono.size();i++)  {
			if (DBG) cout <<"#Poligono "<<i<<endl;
			Poligono[i].save(myfile);
		}

		if (DBG) cout<<"554"<<endl;

		psize=vecino.size();
		myfile.write((char*)&psize,sizeof(psize));
		if (DBG) cout<<"558: vecino.size()="<<vecino.size()<<endl;


		for (i=0;i<     vecino.size();i++) 	{
			if (DBG) cout <<"#Vecino "<<i<<endl;
			myfile.write((char*)&(vecino[i]),sizeof(vecino[i]));
		}

		if (DBG) cout<<"552"<<endl;

		psize=tipo_vecino.size();
		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<     tipo_vecino.size();i++) 	myfile.write((char*)&(tipo_vecino[i]),sizeof(tipo_vecino[i]));


		psize=vecino_centro.size();
		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<   vecino_centro.size();i++)  vecino_centro[i].save(myfile);

		psize=vecino_centro_caraoriginal.size();
		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<   vecino_centro_caraoriginal.size();i++)  vecino_centro_caraoriginal[i].save(myfile);

		if (DBG) cout<<"567"<<endl;

		psize=vecino_normal.size();
		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<   vecino_normal.size();i++)  vecino_normal[i].save(myfile);

		psize=dibujado.size();
		myfile.write((char*)&psize,sizeof(psize));
		//		cout<<"6sizeof(icara)="<<sizeof(icara)<<endl;

		if (DBG) cout<<"577"<<endl;


		for (i=0;i<     dibujado.size();i++) 	myfile.write((char*)(&dibujado[i]),sizeof(dibujado[i]));

	} else {

		myfile  <<"#VolFinito = "<<no<<endl;
		myfile  <<"volumen= "<<volumen<<endl;
		myfile  <<"centro= ";
		centro.save(myfile);


		myfile  <<"#Poligonos: NPoligonos,cada Poligono  "<<endl;
		myfile  <<Poligono.size()<<endl;
		for (i=0;i<   Poligono.size();i++)    {
			myfile  <<"#Poligono "<<i<<endl;
			Poligono[i].save(myfile);
		}

		myfile  <<"#Vecinos: NVecinos,cada Vecino  "<<endl;

		myfile << vecino.size()<<endl;

		for (i=0;i<     vecino.size();i++) 	myfile<<vecino[i]<<" ";
		myfile<<endl;

		myfile  <<"#TipoVecinos: size,cada tipo  "<<endl;
		myfile << tipo_vecino.size()<<endl;
		for (i=0;i<     tipo_vecino.size();i++) 	myfile<<tipo_vecino[i]<<" ";
		myfile<<endl;

		myfile << "vecino_centro<R3>:"<<endl;
		myfile << vecino_centro.size()<<endl;
		for (i=0;i<     vecino_centro.size();i++) 	vecino_centro[i].save(myfile);
		myfile << "vecino_centro_caraoriginal<R3>:"<<endl;
		myfile << vecino_centro_caraoriginal.size()<<endl;
		for (i=0;i<     vecino_centro_caraoriginal.size();i++) 	vecino_centro_caraoriginal[i].save(myfile);

		myfile << "vecino_normal<R3>:"<<endl;
		myfile << vecino_normal.size()<<endl;
		for (i=0;i<     vecino_normal.size();i++) 	vecino_normal[i].save(myfile);

		myfile  <<"#dibujado: size,cada uno  "<<endl;
		myfile << dibujado.size()<<endl;
		for (i=0;i<     dibujado.size();i++) 	myfile<<dibujado[i]<<" ";
		myfile<<endl;

	}

}


void Hexa3D::read(ifstream &myfile,grid3D *papaL) {

	papa=papaL;


	if (binario) {
	} else {
		filtracomentario(myfile);
		myfile  >>no
		>>iv[0]
			 >>iv[1]
				  >>iv[2]
					   >>iv[3]
							>>iv[4]
								 >>iv[5]
									  >>iv[6]
										   >>iv[7];
		if (VersionDatos>=0.099) {
			myfile  >>volumen;
		}

		filtracomentario(myfile);
		myfile  >>icara[0]
						>>icara[1]
								>>icara[2]
										>>icara[3]
												>>icara[4]
														>>icara[5];

		centro.read(myfile);

		int i,sizeL;

		filtracomentario(myfile);
		myfile  >> sizeL; Poligono.resize(sizeL);
		if(1==0) cout  <<"sizeL="<< sizeL<<endl;

		for (i=0;i<   Poligono.size();i++)    {

			filtracomentario(myfile);
			Poligono[i].read(myfile);
		}

		myfile  >> sizeL; vecino.resize(sizeL);
		for (i=0;i<     vecino.size();i++) { myfile>>     vecino[i]; }

		myfile  >> sizeL; tipo_vecino.resize(sizeL);
		for (i=0;i<tipo_vecino.size();i++) { myfile>>tipo_vecino[i]; }

		myfile  >> sizeL; dibujado.resize(sizeL);
		for (i=0;i<   dibujado.size();i++) { myfile>>   dibujado[i]; }

	}

}


void TriPrisma::read(ifstream &myfile,grid3D *papaL) {

	papa=papaL;

	int i;
	if (binario) {
		myfile.read((char*)&no,sizeof(no));
		myfile.read((char*)iv,sizeof(iv));
		myfile.read((char*)icara,sizeof(icara));
		centro.read(myfile);

		int psize;
		myfile.read((char*)&psize,sizeof(psize));		Poligono.resize(psize);
		for (i=0;i<   Poligono.size();i++)  Poligono[i].read(myfile);

		psize=vecino.size();
		myfile.read((char*)&psize,sizeof(psize));		vecino.resize(psize);
		for (i=0;i<     vecino.size();i++) 	myfile.read((char*)vecino[i],sizeof(vecino[i]));

		psize=tipo_vecino.size();
		myfile.read((char*)&psize,sizeof(psize));		tipo_vecino.resize(psize);
		for (i=0;i<     tipo_vecino.size();i++) 	myfile.read((char*)tipo_vecino[i],sizeof(tipo_vecino[i]));

		psize=dibujado.size();
		myfile.read((char*)&psize,sizeof(psize));		dibujado.resize(psize);
		for (i=0;i<     dibujado.size();i++) 	myfile.read((char*)dibujado[i],sizeof(dibujado[i]));

	} else {

		filtracomentario(myfile);
		myfile  >>no>>iv[0]>>iv[1]>>iv[2]>>iv[3]>>iv[4]>>iv[5];
		if (VersionDatos>=0.099) {
			myfile  >>volumen;
		}

		filtracomentario(myfile);
		myfile  >>icara[0]>>icara[1]>>icara[2]>>icara[3]>>icara[4];

		centro.read(myfile);

		int i,sizeL;

		filtracomentario(myfile);
		myfile  >> sizeL; Poligono.resize(sizeL);
		if(1==0) cout  <<"sizeL="<< sizeL<<endl;

		for (i=0;i<   Poligono.size();i++)    {

			filtracomentario(myfile);
			Poligono[i].read(myfile);
		}

		myfile  >> sizeL; vecino.resize(sizeL);
		for (i=0;i<     vecino.size();i++) { myfile>>     vecino[i]; }

		myfile  >> sizeL; tipo_vecino.resize(sizeL);
		for (i=0;i<tipo_vecino.size();i++) { myfile>>tipo_vecino[i]; }

		myfile  >> sizeL; dibujado.resize(sizeL);
		for (i=0;i<   dibujado.size();i++) { myfile>>   dibujado[i]; }

	}

}


void TriPrisma::readMSH(ifstream &myfile,grid3D *papaL) {

	papa=papaL;


	//	filtracomentario(myfile);
	myfile  >>no
	>>iv[0]
		 >>iv[1]
			  >>iv[2]
				   >>iv[3]
						>>iv[4]
							 >>iv[5];

	//	cout<<"Leyendo TriPrisma:"<<iv[0]<<" "<<iv[1]<<" "<<iv[2]<<" "<<iv[3]<<" "<<iv[4]<<" "<<iv[5]<<endl;



}



void PoligonoPlano::save(ofstream &myfile) {


	int i;


	if (DBG) cout<<"PoligonoPlano::save(ofstream &myfile)"<<endl;


	if (punto.size()==0) {
		AreaPoligono=0;Dab=0;normal.x=0;normal.y=0;normal.z=0;
	}
	if (binario) {
		if (DBG) cout<<"787"<<endl;

		myfile.write((char*)&AreaPoligono,sizeof(AreaPoligono)*2); //Area+Dab
		normal.save(myfile);
		centro.save(myfile);
		int psize=punto.size();


		if (DBG) cout<<"795, punto.size()="<<punto.size()<<endl;

		myfile.write((char*)&psize,sizeof(psize));
		for (i=0;i<   punto.size();i++)  punto[i].save(myfile);

	} else {

		myfile  <<AreaPoligono<<" "
				<<Dab<<endl;
		normal.save(myfile);
		centro.save(myfile);

		myfile  <<punto.size()<<endl;
		for (i=0;i<   punto.size();i++)    punto[i].save(myfile);
	}
}



void PoligonoPlano::read(ifstream &myfile) {

	int i,sizeL;

	if (DBG>1) cout<<"PoligonoPlano::read(ifstream &myfile) "<<endl;
	if (binario) {
		myfile.read((char*)&AreaPoligono,sizeof(AreaPoligono)*2);
		normal.read(myfile);
		centro.read(myfile);

		if (DBG>1) cout<<"858"<<endl;

		myfile.read((char*)&sizeL,sizeof(sizeL));  punto.resize(sizeL);
		for (i=0;i<   punto.size();i++)  punto[i].read(myfile);

	} else {
		myfile  >>AreaPoligono
		>>Dab;
		normal.read(myfile);
		centro.read(myfile);

		myfile  >> sizeL; punto.resize(sizeL);
		for (i=0;i<   punto.size();i++)    punto[i].read(myfile);
	}

	if (DBG>1) cout<<"PoligonoPlano::read(ifstream &myfile):END "<<endl;
}


void Cara3D::inicializa(grid3D *pp) {

	if (DBG) cout<<"Cara3D::inicializa"<<endl;
	no  = 0;
	papa=pp;
	nvCara  = 0;
	nVolumenes  = 0;
	BC  = 0;
	BC2 = 0;
	iBC = 0;
	volumen=0;

	iv[0]       = 0;
	iv[1]       = 0;
	iv[2]       = 0;
	iv[3]       = 0;
	ih[0]       = 0;
	ih[1]       = 0;

	centro.x =0 ;
	centro.y =0 ;
	centro.z =0 ;
	centro.L =0 ;
	normalCara.x =0 ;
	normalCara.y =0 ;
	normalCara.z =0 ;
	normalCara.L =0 ;


}

void Cara3D::save(ofstream &myfile) {

	if (binario) {
		myfile.write((char*)&no,sizeof(no)*4);
		myfile.write((char*)&BC,sizeof(BC)*3);
		myfile.write((char*)iv,sizeof(iv[0])*6);
		centro.save(myfile);
		normalCara.save(myfile);

	} else {

		myfile  <<"#Cara "<<no<<endl;
		myfile  <<no<<" "
				<<nvCara<<" "
				<<nVolumenes<<" "
				<<BC<<" "
				<<BC2<<" "
				<<iBC<<" "
				<<volumen<<endl;

		myfile  <<iv[0]<<" "
				<<iv[1]<<" "
				<<iv[2]<<" "
				<<iv[3]<<endl;
		myfile  <<ih[0]<<" "
				<<ih[1]<<endl;


		centro.save(myfile);
		normalCara.save(myfile);

	}
}


void Cara3D::read(ifstream &myfile,grid3D *papaL) {

	//cout<<"Cara3D::read"<<endl;
	papa=papaL;
	if (binario) {
		myfile.read((char*)&no,sizeof(no)*4);
		myfile.read((char*)&BC,sizeof(BC)*3);
		myfile.read((char*)iv,sizeof(iv[0])*6);
		centro.read(myfile);
		normalCara.read(myfile);

	} else {


		filtracomentario(myfile);

		myfile  >>no>>nvCara>>nVolumenes>>BC>>BC2>>iBC;

		myfile  >>volumen;

		if(1==0)cout <<"no="<<no<<"\tnv="<<nvCara<<endl;


		myfile  >>iv[0]>>iv[1]>>iv[2]>>iv[3];
		if(1==0)cout <<"iv[0]="<<iv[0]<<"\tiv[1]="<<iv[1]<<"\tiv[2]="<<iv[2]<<"\tiv[3]="<<iv[3]<<endl;

		myfile  >>ih[0]>>ih[1];

		if(1==0)cout <<"ih[0]="<<ih[0]<<"\tih[1]="<<ih[1]<<endl;

		centro.read(myfile);
		if(1==0)cout <<"centro.x="<<centro.x<<endl;
		normalCara.read(myfile);

		if(1==0)cout <<"normalCara.x="<<normalCara.x<<endl;
	}
	nRandom = (   (double)rand() / ((double)(RAND_MAX)+(double)(1)) );

}


void grid3D::CalculaNormalVertex() {
	Vector<int> cuantos(nV3D);
	int i,j,k;
	for (i=0;i<nV3D;i++) {
		cuantos[i]=0;
		v3D[i].normalVetex.L=0;
	}
	for (i=0;i<Cara.size();i++) {
		if (Cara[i].nVolumenes>1) continue;
		for (j=0;j<Cara[i].nvCara;j++) {
			k=Cara[i].iv[j];
			if (v3D[k].normalVetex.L==-1) continue;
			if (cuantos[k]>0 & ppunto(Cara[i].normalCara,v3D[k].normalVetex)<0.1) {
				v3D[k].normalVetex.L=-1;
			} else {
				v3D[k].normalVetex.x= v3D[k].normalVetex.x*cuantos[k]+ Cara[i].normalCara.x;
				v3D[k].normalVetex.y= v3D[k].normalVetex.y*cuantos[k]+ Cara[i].normalCara.y;
				v3D[k].normalVetex.z= v3D[k].normalVetex.z*cuantos[k]+ Cara[i].normalCara.z;
				cuantos[k]++;
				v3D[k].normalVetex.NormaUnitario();
			}
		}
	}
}

void grid3D::write(ofstream &myfile) {

	int Version=4;
	int i,sizeL;


	if (DBG) cout<<"grid3D::write(ofstream ....)"<<endl;

	if (binario) {
		myfile.write((char*)&Version,sizeof(Version));
		myfile.write((char*)&nH3D,sizeof(nH3D)*5);
		myfile.write((char*)&xmin,sizeof(xmin)*6);

		if (DBG) cout<<"958"<<endl;

		sizeL=v3D.size();		myfile.write((char*)&sizeL,sizeof(sizeL));
		for (i=0;i< v3D.size();i++)  v3D[i].save(myfile);
		sizeL=h3D.size();		myfile.write((char*)&sizeL,sizeof(sizeL));
		for (i=0;i< h3D.size();i++)  h3D[i].save(myfile);
		sizeL=Cara.size();		myfile.write((char*)&sizeL,sizeof(sizeL));
		for (i=0;i< Cara.size();i++)  Cara[i].save(myfile);
		//Version 3

		if (DBG) cout<<"968"<<endl;


		myfile.write((char*)&nTriPrisma3D,sizeof(nTriPrisma3D)*2); //ntriprismas y ntriprismasanalizados
		sizeL=TriPrisma3D.size();		myfile.write((char*)&sizeL,sizeof(sizeL));
		for (i=0;i< TriPrisma3D.size();i++)  TriPrisma3D[i].save(myfile);

		if (DBG) cout<<"975"<<endl;


		sizeL=VolFinito.size();		myfile.write((char*)&sizeL,sizeof(sizeL));
		for (i=0;i< VolFinito.size();i++)  VolFinito[i].save(myfile);
	} else {

		myfile  <<"#Version "<<Version<<endl;
		myfile  <<nH3D<<" "<<nV3D<<" "<<nCaras<<" "<<nPoligonos<<" "<<QuienGeneraPoligonos<<endl;
		myfile  <<xmin<<" "<<xmax<<" "<<ymin<<" "<<ymax<<" "<<zmin<<" "<<zmax<<endl;

		myfile  <<v3D.size()<<endl;
		for (i=0;i< v3D.size();i++)  v3D[i].save(myfile);

		myfile  <<h3D.size()<<endl;
		for (i=0;i< h3D.size();i++)  h3D[i].save(myfile);

		myfile  <<Cara.size()<<endl;
		for (i=0;i<Cara.size();i++) Cara[i].save(myfile);


		myfile  <<nTriPrisma3D<<" "<<TriPri3DAnalizados<<endl;
		myfile  <<TriPrisma3D.size()<<endl;
		for (i=0;i<TriPrisma3D.size();i++) TriPrisma3D[i].save(myfile);


		myfile  <<nVolFinito<<endl;
		myfile  <<VolFinito.size()<<endl;
		for (i=0;i<VolFinito.size();i++) VolFinito[i].save(myfile);
	}
	if (DBG) cout<<"grid3D::write(ofstream ....):END"<<endl;

}


void grid3D::readMSH3D(char *ifile_name) {


	ifstream myfile;
	int i;

	if (PrintLinea) cout<<"grid3D::readMSH3D..."<<endl;


	if (PrintLinea) cout<<"ifile_name="<<ifile_name<<endl;
	myfile.open (ifile_name);

	myfile	>>nV3D	>>nH3D  >>nTriPrisma3D;
	if (PrintLinea) cout<<"nV3D="<<nV3D<<"\tnH3D="<<nH3D<<"\tnTriPrisma3D="<<nTriPrisma3D<<endl;

	v3D.resize(nV3D);
	if (PrintLinea) cout<<"v3D.size()="<<v3D.size()<<endl;
	for (i=0;i< v3D.size();i++) {
		v3D[i].read(myfile,this);
		//No hay escalamiento de Coordenadas
//		v3D[i].x /=1000;
//		v3D[i].y /=1000;
//		v3D[i].z /=1000;
	}
	if (PrintLinea) cout<<"grid3D::read v3D Ok"<<endl;
	h3D.resize(nH3D);
	if (nH3D>0) {
		h3D.resize(nH3D);
		if (PrintLinea) cout<<"h3D.size()="<<h3D.size()<<endl;

		int navance=1;
		printf("0");fflush(stdout);
		for (i=0;i< h3D.size();i++)  {
			if (i>=navance*h3D.size()/20) {
				printf(".%d",navance);fflush(stdout);
				myfileSalida<<"."<<navance;
				navance++;
			}
			h3D[i].read(myfile,this);
		}

		cout<<".OK"<<endl;
	}
	if (nTriPrisma3D>0) {
		TriPrisma3D.resize(nTriPrisma3D);
		if (PrintLinea) cout<<"TriPrisma3D.size()="<<TriPrisma3D.size()<<endl;

		int navance=1;
		printf("0");fflush(stdout);
		for (i=0;i< TriPrisma3D.size();i++)  {
			if (i>=navance*TriPrisma3D.size()/20) {
				printf(".%d",navance);fflush(stdout);
				myfileSalida<<"."<<navance;
				navance++;
			}
			TriPrisma3D[i].readMSH(myfile,this);
		}

		cout<<".OK"<<endl;
	}
	myfileSalida<<".OK"<<endl;

}




void grid3D::write(char * ifile_name) {
	if (PrintLinea) cout<<"grid3D::write(char * "<<ifile_name<<")"<<endl;

	ofstream myfile;
	clock_t start_t, end_t;
	double total_t;


	start_t = clock();


	if (binario) {
		myfile.open (ifile_name, std::ios::out | std::ios::binary);
	}else {
		myfile.open (ifile_name);
	}
	write(myfile);
	myfile.close();


	end_t = clock();
	total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	if (PrintTiempos) cout<<"Lista la escritura en "<<total_t<<" seg";
	if (total_t>60) {
		int min=total_t/60; total_t-=min*60;
		if (PrintTiempos) cout<<" ( "<<min<<":"<<total_t<<"min)";
	}
	if (PrintTiempos) cout <<endl;

}
void grid3D::read(char * ifile_name) {

	if (DBG) cout<<"grid3D::read(char * "<<ifile_name<<")"<<endl;
	ifstream myfile;

	clock_t start_t, end_t;
	double total_t;


	start_t = clock();



	if (binario) {
		myfile.open (ifile_name, std::ios::in | std::ios::binary);
	}else {
		myfile.open (ifile_name);
	}
	read(myfile);
	myfile.close();

	end_t = clock();
	total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	if (PrintTiempos) cout<<"Lista la lectura en "<<total_t<<" seg";
	if (total_t>60) {
		int min=total_t/60; total_t-=min*60;
		if (PrintTiempos) cout<<" ( "<<min<<":"<<total_t<<"min)";
	}
	if (PrintTiempos) cout <<endl;

	if (DBG) cout<<"grid3D::read(char * "<<ifile_name<<"):END"<<endl;

}
void grid3D::read(ifstream &myfile) {

	if (DBG) cout<<"grid3D::read(ifstream ....)"<<endl;

	int i,sizeL;
	int Version;

	if (binario) {
		myfile.read((char*)&Version,sizeof(Version));

		if (DBG) cout<<"Version="<<Version<<endl;

		myfile.read((char*)&nH3D,sizeof(nH3D)*5);
		myfile.read((char*)&xmin,sizeof(xmin)*6);

		if (DBG) cout<<"1"<<endl;
		myfile.read((char*)&sizeL,sizeof(sizeL));   	v3D.resize(sizeL);
		for (i=0;i< v3D.size();i++)  v3D[i].read(myfile,this);
		if (DBG) cout<<"2"<<endl;

		myfile.read((char*)&sizeL,sizeof(sizeL));   	h3D.resize(sizeL);
		for (i=0;i< h3D.size();i++)  h3D[i].read(myfile,this);
		if (DBG) cout<<"3"<<endl;

		myfile.read((char*)&sizeL,sizeof(sizeL));   	Cara.resize(sizeL);
		for (i=0;i< Cara.size();i++)  Cara[i].read(myfile,this);
		//Version 3
		if (DBG) cout<<"4"<<endl;

		if (Version>=3) {
			myfile.read((char*)&nTriPrisma3D,sizeof(nTriPrisma3D)*2);
			if (DBG) cout<<"5"<<endl;
			myfile.read((char*)&sizeL,sizeof(sizeL));   	TriPrisma3D.resize(sizeL);
			for (i=0;i< TriPrisma3D.size();i++)  TriPrisma3D[i].read(myfile,this);
			if (DBG) cout<<"6"<<endl;


		}

		if (Version>=4) {
			myfile.read((char*)&sizeL,sizeof(sizeL));   	VolFinito.resize(sizeL);
			nVolFinito=sizeL;
			if (DBG) cout<<"NVolFinitos: "<<VolFinito.size()<<endl;
			for (i=0;i< VolFinito.size();i++)  {
				if (DBG) cout<<"VolFinito: "<<i<<endl;
				VolFinito[i].read(myfile,this);
			}
			if (DBG) cout<<"7"<<endl;
		}
	} else {


		if (PrintLinea) cout<<"grid3D::read..."<<endl;

		char s[100];
		myfile  >>s>>Version;
		if (PrintLinea) cout <<"Version="<<Version<<endl;


		myfile  >>nH3D
		>>nV3D
		>>nCaras
		>>nPoligonos
		>>QuienGeneraPoligonos;
		myfile  >>xmin
		>>xmax
		>>ymin
		>>ymax
		>>zmin
		>>zmax;


		int i,sizeL;
		myfile  >> sizeL; v3D.resize(sizeL);
		if (PrintLinea) cout<<"v3D.size()="<<v3D.size()<<endl;
		for (i=0;i< v3D.size();i++)  v3D[i].read(myfile,this);
		if (PrintLinea) cout<<"grid3D::read v3D Ok"<<endl;

		myfile  >> sizeL; h3D.resize(sizeL);
		if (PrintLinea) cout<<"h3D.size()="<<h3D.size()<<endl;

		int navance=1;
		printf("0");fflush(stdout);
		for (i=0;i< h3D.size();i++)  {
			if (i>=navance*h3D.size()/50) {
				printf(".%d",navance);fflush(stdout);
				myfileSalida<<"."<<navance;
				navance++;
			}
			h3D[i].read(myfile,this);
		}

		cout<<".OK"<<endl;
		myfileSalida<<".OK"<<endl;
		//	cout<<"grid3D::read h3D Ok"<<endl;

		myfile  >> sizeL; Cara.resize(sizeL);

		if (PrintLinea) cout<<"Cara.size()="<<Cara.size()<<endl;
		navance=1;
		printf("[50]:0");fflush(stdout);
		for (i=0;i<Cara.size();i++) {
			if (i>=navance*Cara.size()/50) {
				printf(".%d",navance);fflush(stdout);
				myfileSalida<<"."<<navance;
				navance++;
			}
			Cara[i].read(myfile,this);
		}

		cout<<".OK"<<endl;
		myfileSalida<<".OK"<<endl;
		//	cout<<"grid3D::read Cara Ok"<<endl;

		if (Version>=3) {

			navance=1;
			myfile  >> nTriPrisma3D >>TriPri3DAnalizados;
			myfile  >> sizeL; TriPrisma3D.resize(sizeL);

			if (PrintLinea) cout<<"TriPrisma3D.size()="<<TriPrisma3D.size()<<endl;
			printf("[20]:0");fflush(stdout);
			for (i=0;i<TriPrisma3D.size();i++) {
				if (i>=navance*TriPrisma3D.size()/20) {
					printf(".%d",navance);fflush(stdout);
					myfileSalida<<"."<<navance;
					navance++;
				}
				TriPrisma3D[i].read(myfile,this);
			}
			cout<<".OK"<<endl;
			myfileSalida<<".OK"<<endl;
		}
	}
	if (DBG) cout<<"grid3D::read(ifstream ....):END"<<endl;

}



void grid3D::draw_caraGL(int ii[4])
{

	int li;
	double x[4],y[4],z[4],v[3],xg,yg,zg,lambda=0.0,nx,ny,nz,nxx,nyy,nzz,nnn;
	GLdouble winX1,winY1,winX2,winY2,winX3,winY3,winZ,winZ2;
	xg=0;yg=0;zg=0;

	for (li=0;li<4;li++) {
		x[li]=v3D[ii[li]].x;	
		y[li]=v3D[ii[li]].y;	
		z[li]=v3D[ii[li]].z*FactorZ;
		xg+=x[li]/4;		yg+=y[li]/4;		zg+=z[li]/4;
	}
	for (li=0;li<4;li++) {
		x[li]+=(xg-x[li])*lambda;	
		y[li]+=(yg-y[li])*lambda;	
		z[li]+=(zg-z[li])*lambda;		
	}

	nxx=nx=(y[2]-y[0])*(z[3]-z[1])-(z[2]-z[0])*(y[3]-y[1]);
	nyy=ny=(z[2]-z[0])*(x[3]-x[1])-(x[2]-x[0])*(z[3]-z[1]);
	nzz=nz=(x[2]-x[0])*(y[3]-y[1])-(y[2]-y[0])*(x[3]-x[1]);
	nnn=sqrt(sqr(nxx)+sqr(nyy)+sqr(nzz));

	//	ZGlobal(v);
	FuncionesOpenGL::modelview_calculado=false;	
	FuncionesOpenGL::World2Win(x[0],y[0],z[0],&winX1,&winY1,&winZ);
	FuncionesOpenGL::World2Win(x[1],y[1],z[1],&winX2,&winY2,&winZ);
	FuncionesOpenGL::World2Win(x[2],y[2],z[2],&winX3,&winY3,&winZ);
	if ((winX2-winX1)*(winY3-winY1)-(winY2-winY1)*(winX3-winX1) <0 ){ 
		nxx=-nxx;nyy=-nyy;nzz=-nzz;
	}


	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
	for (li=0;li<4;li++) {
		if (x[li]<xg)
			nx=nxx+(x[li]-xg)*((x[li]-xg))/0.51;
		else
			nx=nxx-(x[li]-xg)*((x[li]-xg))/0.51;
		if (y[li]<yg)
			ny=nyy+(y[li]-yg)*((y[li]-yg))/0.51;
		else
			ny=nyy-(y[li]-yg)*((y[li]-yg))/0.51;
		if  (z[li]<zg)
			nz=nzz+(z[li]-zg)*((z[li]-zg))/0.51;
		else
			nz=nzz-(z[li]-zg)*((z[li]-zg))/0.51;


		//glNormal3d(nxx,nyy,nzz);
		glNormal3d(nx,ny,nz);
		glVertex3d(x[li], y[li],z[li]);
	}
	glEnd();

	if(ModoDibujaNormales) {
		glPushAttrib( GL_LIGHTING_BIT );
		glDisable( GL_LIGHTING );

		glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3d(xg,yg,zg);
		glVertex3d(xg+nxx/nnn/10,yg+nyy/nnn/10,zg+nzz/nnn/10);
		glEnd();
		glPopAttrib();
	}
}

void Cara3D::draw_caraGL00(vector<double> &F,double minF,double maxF,int* ii)
{

	int li;
	double x[4],y[4],z[4],v[3],xg,yg,zg,lambda=0.0,nx,ny,nz,nxx,nyy,nzz,nnn;
	GLdouble winX1,winY1,winX2,winY2,winX3,winY3,winZ,winZ2;
	GLdouble posX0,posY0,posZ0,posX1,posY1,posZ1;
	xg=0;yg=0;zg=0;

	if(DBG>1) cout<<"Cara3D::draw_caraGL(vector<double>F,double "<<minF<<",double "<<maxF<<",int ii[4])"<<endl;

	if (ModoDibujaAlgunos && nRandom>(double)Algunos_Porcentaje/100) {
//		cout<<"return"<<endl;
		return;
	}
	//	cout <<"nvC="<<nvC<<endl;
	xg=0;yg=0;zg=0;
	for (li=0;li<nvCara;li++) {
		x[li]=papa->v3D[iv[li]].x;
		y[li]=papa->v3D[iv[li]].y;
		z[li]=papa->v3D[iv[li]].z*FactorZ;
		xg+=x[li]/nvCara;		yg+=y[li]/nvCara;		zg+=z[li]/nvCara;
	}

//	xg= centro.x;
//	yg= centro.y;
//	zg= centro.z*FactorZ;

	for (li=0;li<nvCara;li++) {
		x[li]+=(xg-x[li])*FactorAchica;
		y[li]+=(yg-y[li])*FactorAchica;
		z[li]+=(zg-z[li])*FactorAchica;
	}

	if(DBG>1) cout<<"1439"<<endl;

	//Version que tambien funciona pero más rápido!!
	nxx=normalCara.x;
	nyy=normalCara.y;
	nzz=normalCara.z/FactorZ;
	nnn=sqrt(sqr(nxx)+sqr(nyy)+sqr(nzz));
	nxx/=nnn;
	nyy/=nnn;
	nzz/=nnn;

	if(DBG>1) cout<<"1446"<<endl;

	ZGlobal(v);

	if(DBG>1) cout<<"1450"<<endl;

	if (0) {
		FuncionesOpenGL::modelview_calculado=false;
		FuncionesOpenGL::World2Win(x[0],y[0],z[0],&winX1,&winY1,&winZ1);
		FuncionesOpenGL::World2Win(x[1],y[1],z[1],&winX2,&winY2,&winZ2);
		FuncionesOpenGL::World2Win(x[2],y[2],z[2],&winX3,&winY3,&winZ3);
		int signo=1;
		signo2=1;
		if ((winX2-winX1)*(winY3-winY1)-(winY2-winY1)*(winX3-winX1) <0 ){
		signo2=-1;
	}
	} else {

		FuncionesOpenGL::World2Win(x[0],y[0],z[0],&winX1,&winY1,&winZ1);
		FuncionesOpenGL::Win2World(winX1,winY1,winZ1, &posX0, &posY0, &posZ0);
		FuncionesOpenGL::Win2World(winX1,winY1,winZ1-1, &posX1, &posY1, &posZ1);
		v[0]=posX1-posX0;
		v[1]=posY1-posY0;
		v[2]=posZ1-posZ0;
	}


	if (this->iBC==IBC_SUP)	signo2=1;


	glEnable(GL_NORMALIZE);
	int s;
	if (nvCara==4)	glBegin(GL_QUADS);
	else glBegin(GL_TRIANGLES);

	if(DBG>1) cout<<"1457"<<endl;

	if ( nxx*v[0]+nyy*v[1]+nzz*v[2]<0) s=-1;//	glNormal3d(-nx,-ny,-nz);
	else								s=1;//glNormal3d(nx,ny,nz);
	for (li=0;li<nvCara;li++) {
		if (0*TLimite_if) {
			if (F[ii[li]]>TLimite) {

				FuncionesOpenGL::ColorF(minF,maxF,maxF);

			} else {

				FuncionesOpenGL::ColorF(minF,maxF,minF);
			}
		} else {
			FuncionesOpenGL::ColorF(minF,maxF,F[ii[li]]);
		}


		ny=-(y[li]-yg);
		nx=-(x[li]-xg);
		nz=-(z[li]-zg);
		nnn=sqrt(sqr(nx)+sqr(ny)+sqr(nz));
		nx/=nnn;
		ny/=nnn;
		nz/=nnn;



		if (FactorSuavidad>0 & papa->v3D[iv[li]].normalVetex.L>0.1) {
			nx=nxx*(1-FactorSuavidad)+FactorSuavidad*papa->v3D[iv[li]].normalVetex.x;
			ny=nyy*(1-FactorSuavidad)+FactorSuavidad*papa->v3D[iv[li]].normalVetex.y;
			nz=nzz*(1-FactorSuavidad)+FactorSuavidad*papa->v3D[iv[li]].normalVetex.z/FactorZ;


		} else {

			nx=s*nxx+nx/20;
			ny=s*nyy+ny/20;
			nz=s*nzz+nz/20;
		}

		//glNormal3d(s*nxx,s*nyy,s*nzz);

		if ( nx*v[0]+ny*v[1]+nz*v[2]<0) {
			glNormal3d(-nx,-ny,-nz);
		} else
			glNormal3d(nx,ny,nz);
		glVertex3d(x[li], y[li],z[li]);
	}
	glEnd();


}


void grid3D::draw_caraGL00(vector<double> &F,double minF,double maxF,int* ii)
{
	int li;
	double x[4],y[4],z[4],v[3],xg,yg,zg,lambda=0.0,nx,ny,nz,nxx,nyy,nzz,nnn;
	GLdouble winX1,winY1,winX2,winY2,winX3,winY3,winZ,winZ2;
	xg=0;yg=0;zg=0;

	if(DBG) cout<<"grid3D::draw_caraGL(vector<double>F,double "<<minF<<",double "<<maxF<<",int ii[4])"<<endl;

	for (li=0;li<3;li++) {
		if(DBG) cout<<"1427: li="<<li<<endl;
		x[li]=v3D[ii[li]].x;
		y[li]=v3D[ii[li]].y;
		z[li]=v3D[ii[li]].z*FactorZ;
		xg+=x[li]/4;		yg+=y[li]/4;		zg+=z[li]/4;
	}
	if(DBG) cout<<"1432"<<endl;

	for (li=0;li<3;li++) {
		x[li]+=(xg-x[li])*lambda;
		y[li]+=(yg-y[li])*lambda;
		z[li]+=(zg-z[li])*lambda;
	}
	if(DBG) cout<<"1439"<<endl;

	nxx=nx=(y[2]-y[0])*(z[3]-z[1])-(z[2]-z[0])*(y[3]-y[1]);
	nyy=ny=(z[2]-z[0])*(x[3]-x[1])-(x[2]-x[0])*(z[3]-z[1]);
	nzz=nz=(x[2]-x[0])*(y[3]-y[1])-(y[2]-y[0])*(x[3]-x[1]);
	nnn=sqrt(sqr(nxx)+sqr(nyy)+sqr(nzz));

	if(DBG) cout<<"1446"<<endl;

	ZGlobal(v);

	if(DBG) cout<<"1450"<<endl;


	glEnable(GL_NORMALIZE);
	int s;
	glBegin(GL_QUADS);

	if(DBG) cout<<"1457"<<endl;

	if ( nxx*v[0]+nyy*v[1]+nzz*v[2]<0) s=-1;//	glNormal3d(-nx,-ny,-nz);
	else								s=1;//glNormal3d(nx,ny,nz);
	for (li=0;li<3;li++) {
		if (TLimite_if) {
			if (F[ii[li]]>TLimite) {

				FuncionesOpenGL::ColorF(minF,maxF,maxF);

			} else {

				FuncionesOpenGL::ColorF(minF,maxF,minF);
			}
		} else

			FuncionesOpenGL::ColorF(minF,maxF,F[ii[li]]);
		if (x[li]<xg)
			nx=nxx+(x[li]-xg)*((x[li]-xg))/10.51;
		else
			nx=nxx-(x[li]-xg)*((x[li]-xg))/10.51;
		if (y[li]<yg)
			ny=nyy+(y[li]-yg)*((y[li]-yg))/10.51;
		else
			ny=nyy-(y[li]-yg)*((y[li]-yg))/10.51;
		if  (z[li]<zg)
			nz=nzz+(z[li]-zg)*((z[li]-zg))/10.51;
		else
			nz=nzz-(z[li]-zg)*((z[li]-zg))/10.51;


		//glNormal3d(nxx,nyy,nzz);
		glNormal3d(s*nx,s*ny,s*nz);
		glVertex3d(x[li], y[li],z[li]);
	}
	glEnd();

}


void Hexa3D::draw_caraGL(int i0,int i1,int i2,int i3)
{
	int li;
	double x[4],y[4],z[4],v[3],xg,yg,zg,lambda=0.0,nx,ny,nz,nxx,nyy,nzz;
	x[0]=papa->v3D[iv[i0]].x;
	x[1]=papa->v3D[iv[i1]].x;	x[2]=papa->v3D[iv[i2]].x;	x[3]=papa->v3D[iv[i3]].x;
	y[0]=papa->v3D[iv[i0]].y;	y[1]=papa->v3D[iv[i1]].y;	y[2]=papa->v3D[iv[i2]].y;	y[3]=papa->v3D[iv[i3]].y;
	z[0]=papa->v3D[iv[i0]].z*FactorZ;	z[1]=papa->v3D[iv[i1]].z*FactorZ;	z[2]=papa->v3D[iv[i2]].z*FactorZ;	z[3]=papa->v3D[iv[i3]].z*FactorZ;
	xg=0;yg=0;zg=0;
	for (li=0;li<4;li++) {
		xg+=x[li]/4;		yg+=y[li]/4;		zg+=z[li]/4;
	}
	for (li=0;li<4;li++) {
		x[li]+=(xg-x[li])*lambda;	
		y[li]+=(yg-y[li])*lambda;	
		z[li]+=(zg-z[li])*lambda;		
	}

	nxx=nx=(y[2]-y[0])*(z[3]-z[1])-(z[2]-z[0])*(y[3]-y[1]);
	nyy=ny=(z[2]-z[0])*(x[3]-x[1])-(x[2]-x[0])*(z[3]-z[1]);
	nzz=nz=(x[2]-x[0])*(y[3]-y[1])-(y[2]-y[0])*(x[3]-x[1]);

	ZGlobal(v);
	glEnable(GL_NORMALIZE);
	glBegin(GL_QUADS);
	for (li=0;li<4;li++) {
		if (x[li]<xg)
			nx=-nxx+(x[li]-xg)*((x[li]-xg))/0.51;
		else
			nx=-nxx-(x[li]-xg)*((x[li]-xg))/0.51;
		if (y[li]<yg)
			ny=-nyy+(y[li]-yg)*((y[li]-yg))/0.51;
		else
			ny=-nyy-(y[li]-yg)*((y[li]-yg))/0.51;
		if  (z[li]<zg)
			nz=-nzz+(z[li]-zg)*((z[li]-zg))/0.51;
		else
			nz=-nzz-(z[li]-zg)*((z[li]-zg))/0.51;


		if (nxx*v[0]+nyy*v[1]+nzz*v[2]<0) 
			glNormal3d(nx,ny,nz);
		else
			glNormal3d(-nx,-ny,-nz);


		//glNormal3d(nx,ny,nz);
		glVertex3d(x[li], y[li],z[li]);
	}
	glEnd();

}

void Hexa3D::draw_caraGL(vector<double>F,double minF,double maxF, int i0,int i1,int i2,int i3)
{
	int li;
	double x[4],y[4],z[4],v[3],nx,ny,nz,nxx,nyy,nzz;
	double lF[4];
	x[0]=papa->v3D[iv[i0]].x;	x[1]=papa->v3D[iv[i1]].x;	x[2]=papa->v3D[iv[i2]].x;	x[3]=papa->v3D[iv[i3]].x;
	y[0]=papa->v3D[iv[i0]].y;	y[1]=papa->v3D[iv[i1]].y;	y[2]=papa->v3D[iv[i2]].y;	y[3]=papa->v3D[iv[i3]].y;
	z[0]=papa->v3D[iv[i0]].z*FactorZ;	z[1]=papa->v3D[iv[i1]].z*FactorZ;	z[2]=papa->v3D[iv[i2]].z*FactorZ;	z[3]=papa->v3D[iv[i3]].z*FactorZ;
	lF[0]=F[iv[i0]];				lF[1]=F[iv[i1]];				lF[2]=F[iv[i2]];					lF[3]=F[iv[i3]];				

	nxx=nx=(y[2]-y[0])*(z[3]-z[1])-(z[2]-z[0])*(y[3]-y[1]);
	nyy=ny=(z[2]-z[0])*(x[3]-x[1])-(x[2]-x[0])*(z[3]-z[1]);
	nzz=nz=(x[2]-x[0])*(y[3]-y[1])-(y[2]-y[0])*(x[3]-x[1]);

	ZGlobal(v);
	glEnable(GL_NORMALIZE);
	{
		glBegin(GL_TRIANGLES );
		if ( nxx*v[0]+nyy*v[1]+nzz*v[2]<0) 	glNormal3d(-nx,-ny,-nz);
		else								glNormal3d(nx,ny,nz);

		FuncionesOpenGL::ColorF(minF,maxF,lF[0]);glVertex3d(x[0], y[0],z[0]);
		//		cout<<"Hexa3D::draw_caraGL minF,MaxF,lF[0]="<<minF<<" "<<maxF<<" "<<lF[0]<<endl;
		FuncionesOpenGL::ColorF(minF,maxF,lF[1]);glVertex3d(x[1], y[1],z[1]);
		FuncionesOpenGL::ColorF(minF,maxF,lF[2]);glVertex3d(x[2], y[2],z[2]);
		glEnd();
	}

	{
		glBegin(GL_TRIANGLES );
		if ( nxx*v[0]+nyy*v[1]+nzz*v[2]<0) 	glNormal3d(-nx,-ny,-nz);
		else								glNormal3d(nx,ny,nz);

		FuncionesOpenGL::ColorF(minF,maxF,lF[0]);glVertex3d(x[0], y[0],z[0]);
		FuncionesOpenGL::ColorF(minF,maxF,lF[2]);glVertex3d(x[2], y[2],z[2]);
		FuncionesOpenGL::ColorF(minF,maxF,lF[3]);glVertex3d(x[3], y[3],z[3]);
		glEnd();
	}

}

void Hexa3D::draw_edgeGL(int i0,int i1)
{
	int li;
	vector<Vertex3D> *lv3D;
	lv3D=&(papa->v3D);

	glBegin(GL_LINES);
	glVertex3d((papa->v3D)[iv[i0]].x, (papa->v3D)[iv[i0]].y,(papa->v3D)[iv[i0]].z*FactorZ);
	glVertex3d(papa->v3D[iv[i1]].x, papa->v3D[iv[i1]].y,papa->v3D[iv[i1]].z*FactorZ);
	glEnd();

}

int grid3D::BuscaCara3(int i0,int i1,int i2) {
	int i;
	int is1,is2,is4,is3,iis3,iis1,iis2,iis4;
	is1=i0+i1+i2;
	is2=sqr(i0)+sqr(i1)+sqr(i2);
	is3=(i0+1)*(i1+1)*(i2+1);
	for (i=0;i<nCaras;i++) {
		if(Cara[i].nvCara !=3 ) continue;
		iis1=Cara[i].iv[0]+Cara[i].iv[1]+Cara[i].iv[2];
		if (iis1 != is1) continue;
		iis2=sqr(Cara[i].iv[0])+sqr(Cara[i].iv[1])+sqr(Cara[i].iv[2]);
		if (iis2 != is2) continue;
		iis3=(Cara[i].iv[0]+1)*(Cara[i].iv[1]+1)*(Cara[i].iv[2]+1);
		if (iis3 != is3) continue;
		break;
	}
	return (i);
}

int grid3D::BuscaCara4(int i0,int i1,int i2,int i3) {
	int i;
	int is,is2,is3,ip,iip,iis,iis2,iis3;
	is=i0+i1+i2+i3;
	is2=sqr(i0)+sqr(i1)+sqr(i2)+sqr(i3);
	ip=(i0+1)*(i1+1)*(i2+1)*(i3+1);
	is3=ip/(i0+1)+ip/(i1+1)+ip/(i2+1)+ip/(i3+1);
	for (i=0;i<nCaras;i++) {
		if(Cara[i].nvCara !=4 ) continue;
		iis=Cara[i].iv[0]+Cara[i].iv[1]+Cara[i].iv[2]+Cara[i].iv[3];
		if (iis != is) continue;
		iis2=sqr(Cara[i].iv[0])+sqr(Cara[i].iv[1])+sqr(Cara[i].iv[2])+sqr(Cara[i].iv[3]);
		if (iis2 != is2) continue;
		iip=(Cara[i].iv[0]+1)*(Cara[i].iv[1]+1)*(Cara[i].iv[2]+1)*(Cara[i].iv[3]+1);
		if (iip != ip) continue;
		iis3=iip/(Cara[i].iv[0]+1)+iip/(Cara[i].iv[1]+1)+iip/(Cara[i].iv[2]+1)+iip/(Cara[i].iv[3]+1);
		if (iis3 != is3) continue;
		break;
	}
	return (i);
}
int grid3D::AddCara4(int ib,int i0,int i1,int i2,int i3)
{
	int i;
	i=BuscaCara4( i0, i1, i2, i3);
	if (i<nCaras) { //Cara existente
		Cara[i].ih[Cara[i].nVolumenes]=ib;
		Cara[i].nVolumenes++;

		return(i);
	}
	Cara.push_back(Cara3D());
	Cara[nCaras].inicializa(this);
	Cara[nCaras].nvCara=4;
	Cara[nCaras].nVolumenes=1;
	Cara[nCaras].iv[0]=i0;
	Cara[nCaras].iv[1]=i1;
	Cara[nCaras].iv[2]=i2;
	Cara[nCaras].iv[3]=i3;
	Cara[nCaras].ih[0]=ib;
	nCaras++;
	return (nCaras-1);


}
int grid3D::AddCara3(int ib,int i0,int i1,int i2,int iBC)
//Agrega Cara Triangular
{
	int i;
	//	if (nCaras<10) {
	//		cout<<"C AddCara3(int ib="<<ib<<",int i0="<<i0<<",int i1="<<i1<<",int i2="<<i2<<")"<<endl;
	//	}
	i=BuscaCara3( i0, i1, i2);
	if (i<nCaras) { //Cara existente
		//		if (nCaras<10) {
		//			cout<<"C CaraExistente: i="<<i<<endl;
		//		}

		Cara[i].ih[Cara[i].nVolumenes]=ib;
		Cara[i].nVolumenes++;

		return(i);
	}
	if (nCaras<10) {
		if (PrintCaras) cout<<"C Nueva Cara: no="<<nCaras<<endl;
	}
	Cara.push_back(Cara3D());
	Cara[nCaras].inicializa(this);
	Cara[nCaras].no=nCaras;
	Cara[nCaras].nvCara=3;
	Cara[nCaras].nVolumenes=1;
	Cara[nCaras].iv[0]=i0;
	Cara[nCaras].iv[1]=i1;
	Cara[nCaras].iv[2]=i2;
	Cara[nCaras].iv[3]=-1; //Este nodo no se usa
	Cara[nCaras].ih[0]=ib;
	Cara[nCaras].iBC=iBC;
	nCaras++;
	return (nCaras-1);


}


void grid3D::Poligono_InicialCara(R3 a, R3 b, PoligonoPlano &P,int iC) {

	double d1x,d1y,d1z,dab;
	double d2x,d2y,d2z,dd;
	double d3x,d3y,d3z;
	double lambda=xmax+ymax+zmax-(xmin+ymin+zmin);
	d1x=(b.x-a.x); d1y=(b.y-a.y); d1z=(b.z-a.z);
	dab=sqrt(sqr(d1x)+sqr(d1y)+sqr(d1z));
	if (fabs(d1x)>dab/4) {
		d2x=-d1y; d2y=d1x; d2z=0;
	} else if (fabs(d1y)>dab/4) {
		d2x=-d1y; d2y=d1x; d2z=0;
	} if (fabs(d1z)>dab/4) {
		d2x=-d1z; d2y=0; d2z=d1x;
	}
	d3x=(d1y*d2z-d1z*d2y); d3y=(d1z*d2x-d1x*d2z); d3z=(d1x*d2y-d1y*d2x);

	dd=sqrt(sqr(d2x)+sqr(d2y)+sqr(d2z)); d2x /=dd; d2y /=dd; d2z /=dd;
	dd=sqrt(sqr(d3x)+sqr(d3y)+sqr(d3z)); d3x /=dd; d3y /=dd; d3z /=dd;

	P.Dab=dab;
	P.normal.x=d1x/dab;
	P.normal.y=d1y/dab;
	P.normal.z=d1z/dab;
	P.centro.x=(a.x+b.x)/2;
	P.centro.y=(a.y+b.y)/2;
	P.centro.z=(a.z+b.z)/2;
	P.punto.clear();
	P.punto.resize(Cara[iC].nvCara);
	for (int j=0;j<P.punto.size();j++) {
		P.punto[j].x = v3D[Cara[iC].iv[j]].x;
		P.punto[j].y = v3D[Cara[iC].iv[j]].y;
		P.punto[j].z = v3D[Cara[iC].iv[j]].z;
	}


}


void grid3D::Poligono_Inicial(R3 a, R3 b, PoligonoPlano &P)
{
	double d1x,d1y,d1z,dab;
	double d2x,d2y,d2z,dd;
	double d3x,d3y,d3z;
	double lambda=xmax+ymax+zmax-(xmin+ymin+zmin);
	d1x=(b.x-a.x); d1y=(b.y-a.y); d1z=(b.z-a.z);
	dab=sqrt(sqr(d1x)+sqr(d1y)+sqr(d1z));
	if (fabs(d1x)>dab/4) {
		d2x=-d1y; d2y=d1x; d2z=0;
	} else if (fabs(d1y)>dab/4) {
		d2x=-d1y; d2y=d1x; d2z=0;
	} if (fabs(d1z)>dab/4) {
		d2x=-d1z; d2y=0; d2z=d1x;
	} 
	d3x=(d1y*d2z-d1z*d2y); d3y=(d1z*d2x-d1x*d2z); d3z=(d1x*d2y-d1y*d2x);

	dd=sqrt(sqr(d2x)+sqr(d2y)+sqr(d2z)); d2x /=dd; d2y /=dd; d2z /=dd; 
	dd=sqrt(sqr(d3x)+sqr(d3y)+sqr(d3z)); d3x /=dd; d3y /=dd; d3z /=dd; 

	P.Dab=dab;
	P.normal.x=d1x/dab;
	P.normal.y=d1y/dab;
	P.normal.z=d1z/dab;
	P.centro.x=(a.x+b.x)/2;
	P.centro.y=(a.y+b.y)/2;
	P.centro.z=(a.z+b.z)/2;
	P.punto.clear();
	P.punto.resize(4);
	P.punto[0].x = (a.x+b.x)/2 + lambda*d2x + lambda*d3x;
	P.punto[0].y = (a.y+b.y)/2 + lambda*d2y + lambda*d3y;
	P.punto[0].z = (a.z+b.z)/2 + lambda*d2z + lambda*d3z;

	P.punto[1].x = (a.x+b.x)/2 - lambda*d2x + lambda*d3x;
	P.punto[1].y = (a.y+b.y)/2 - lambda*d2y + lambda*d3y;
	P.punto[1].z = (a.z+b.z)/2 - lambda*d2z + lambda*d3z;

	P.punto[2].x = (a.x+b.x)/2 - lambda*d2x - lambda*d3x;
	P.punto[2].y = (a.y+b.y)/2 - lambda*d2y - lambda*d3y;
	P.punto[2].z = (a.z+b.z)/2 - lambda*d2z - lambda*d3z;

	P.punto[3].x = (a.x+b.x)/2 + lambda*d2x - lambda*d3x;
	P.punto[3].y = (a.y+b.y)/2 + lambda*d2y - lambda*d3y;
	P.punto[3].z = (a.z+b.z)/2 + lambda*d2z - lambda*d3z;

}

void RecortaPoligono(R3 a, R3 b, PoligonoPlano &P)
{
	double a2,b2,KP,KQ,xpn,ypn,zpn,xnp,ynp,znp;
	int icj,ibB,k,kk,km1,kneg_ini,kneg_fin,nerase;
	a2=sqr(a.x)+sqr(a.y)+sqr(a.z);
	b2=sqr(b.x)+sqr(b.y)+sqr(b.z);
	xx2=b.x;
	yy2=b.y;
	zz2=b.z;
	//busco k tal que KQ(k)>0 (vertice dentro de la zona)
	for(k=0 ; k<P.punto.size() ; k++) {
		KQ= 2*(a.x-b.x)*P.punto[k].x+
				2*(a.y-b.y)*P.punto[k].y+
				2*(a.z-b.z)*P.punto[k].z + b2-a2;
		if (KQ>0) break;
	}
	if (k>=P.punto.size()) {
		P.punto.clear();
		return;    //Poligono fuera de la zona de interes
	} 
	//hay un punto con KP>0.....(OK)
	for(kk=0 ; kk < P.punto.size() ; kk++) {
		km1=k;
		k++;if ( k>=P.punto.size() ) k=0;
		KP=KQ;
		KQ= 2*(a.x-b.x)*P.punto[k].x+
				2*(a.y-b.y)*P.punto[k].y+
				2*(a.z-b.z)*P.punto[k].z + b2-a2;
		if (KQ<0) break;
	}
	if (kk>=P.punto.size()) return; //Todoel poligono es positivo
	//Encontre KQ(k) negativo
	kneg_ini=k;
	xpn=( KP*P.punto[k].x - KQ*P.punto[km1].x ) / (KP-KQ);
	ypn=( KP*P.punto[k].y - KQ*P.punto[km1].y ) / (KP-KQ);
	zpn=( KP*P.punto[k].z - KQ*P.punto[km1].z ) / (KP-KQ);
	nerase=0;
	for(kk=0 ; kk < P.punto.size() ; kk++) {
		km1=k;
		k++;if ( k>=P.punto.size() ) k=0;
		KP=KQ;
		KQ= 2*(a.x-b.x)*P.punto[k].x+
				2*(a.y-b.y)*P.punto[k].y+
				2*(a.z-b.z)*P.punto[k].z + b2-a2;
		if (kk>1) nerase++;
		if (KQ>0) break;
	}
	kneg_fin=km1;
	xnp=( KP*P.punto[k].x - KQ*P.punto[km1].x ) / (KP-KQ);
	ynp=( KP*P.punto[k].y - KQ*P.punto[km1].y ) / (KP-KQ);
	znp=( KP*P.punto[k].z - KQ*P.punto[km1].z ) / (KP-KQ);
	if (kneg_fin==kneg_ini) {
		P.punto.insert( P.punto.begin()+kneg_ini , R3() );
		P.punto[kneg_ini  ].x=xpn;
		P.punto[kneg_ini  ].y=ypn;
		P.punto[kneg_ini  ].z=zpn;
		P.punto[kneg_ini+1].x=xnp;
		P.punto[kneg_ini+1].y=ynp;
		P.punto[kneg_ini+1].z=znp;
	} else if (nerase==0) {
		P.punto[kneg_ini].x=xpn;
		P.punto[kneg_ini].y=ypn;
		P.punto[kneg_ini].z=zpn;
		P.punto[kneg_fin].x=xnp;
		P.punto[kneg_fin].y=ynp;
		P.punto[kneg_fin].z=znp;
	} else {
		P.punto[kneg_ini].x=xpn;
		P.punto[kneg_ini].y=ypn;
		P.punto[kneg_ini].z=zpn;
		P.punto[kneg_fin].x=xnp;
		P.punto[kneg_fin].y=ynp;
		P.punto[kneg_fin].z=znp;
		if (kneg_ini+nerase < P.punto.size() ) {
			P.punto.erase( P.punto.begin()+kneg_ini+1 , P.punto.begin()+kneg_ini+nerase+1 );
		} else {
			int n1=P.punto.size()-kneg_ini-1;
			if (n1>0) P.punto.erase( P.punto.begin()+kneg_ini+1 , P.punto.begin()+kneg_ini+n1+1 );
			int n2=nerase-n1;
			P.punto.erase( P.punto.begin() , P.punto.begin()+n2 );
		}
	}
}

void grid3D::CentroCarasBloques()
{
	int i,j,k,l,icj,ibb,jj;
	double xg,yg,zg,x0,y0,z0,x1,y1,z1,d1x,d1y,d1z,d2x,d2y,d2z,d3x,d3y,d3z,dij,lambda;
	double Ax,Ay,Az,AA;
	for(i=0;i<nTriPrisma3D;i++) {
		xg=0;yg=0;zg=0;
		for(j=0;j<6;j++) {
			xg+=v3D[TriPrisma3D[i].iv[j]].x; yg+=v3D[TriPrisma3D[i].iv[j]].y; zg+=v3D[TriPrisma3D[i].iv[j]].z;
		}
		TriPrisma3D[i].centro.x=xg/6; TriPrisma3D[i].centro.y=yg/6; TriPrisma3D[i].centro.z=zg/6;
	}
	for(i=0;i<nH3D;i++) {
		xg=0;yg=0;zg=0;
		for(j=0;j<8;j++) {
			xg+=v3D[h3D[i].iv[j]].x; yg+=v3D[h3D[i].iv[j]].y; zg+=v3D[h3D[i].iv[j]].z;
		}
		h3D[i].centro.x=xg/8; h3D[i].centro.y=yg/8; h3D[i].centro.z=zg/8;
	}
	for(i=0;i<nCaras;i++) {
		xg=0;yg=0;zg=0;
		Cara[i].no=i;
		for(j=0;j<Cara[i].nvCara;j++) {
			xg+=v3D[Cara[i].iv[j]].x; yg+=v3D[Cara[i].iv[j]].y; zg+=v3D[Cara[i].iv[j]].z;
		}
		Cara[i].centro.x=xg/Cara[i].nvCara; Cara[i].centro.y=yg/Cara[i].nvCara; Cara[i].centro.z=zg/Cara[i].nvCara;
		Ax = (v3D[Cara[i].iv[1]].y - v3D[Cara[i].iv[0]].y) * (v3D[Cara[i].iv[2]].z - v3D[Cara[i].iv[0]].z)
            						-(v3D[Cara[i].iv[1]].z - v3D[Cara[i].iv[0]].z) * (v3D[Cara[i].iv[2]].y - v3D[Cara[i].iv[0]].y);
		Ay = (v3D[Cara[i].iv[1]].z - v3D[Cara[i].iv[0]].z) * (v3D[Cara[i].iv[2]].x - v3D[Cara[i].iv[0]].x)
									-(v3D[Cara[i].iv[1]].x - v3D[Cara[i].iv[0]].x) * (v3D[Cara[i].iv[2]].z - v3D[Cara[i].iv[0]].z);
		Az = (v3D[Cara[i].iv[1]].x - v3D[Cara[i].iv[0]].x) * (v3D[Cara[i].iv[2]].y - v3D[Cara[i].iv[0]].y)
									-(v3D[Cara[i].iv[1]].y - v3D[Cara[i].iv[0]].y) * (v3D[Cara[i].iv[2]].x - v3D[Cara[i].iv[0]].x);
		if (Cara[i].nvCara>3) {
			Ax+= (v3D[Cara[i].iv[2]].y - v3D[Cara[i].iv[0]].y) * (v3D[Cara[i].iv[3]].z - v3D[Cara[i].iv[0]].z)
											-(v3D[Cara[i].iv[2]].z - v3D[Cara[i].iv[0]].z) * (v3D[Cara[i].iv[3]].y - v3D[Cara[i].iv[0]].y);
			Ay+= (v3D[Cara[i].iv[2]].z - v3D[Cara[i].iv[0]].z) * (v3D[Cara[i].iv[3]].x - v3D[Cara[i].iv[0]].x)
											-(v3D[Cara[i].iv[2]].x - v3D[Cara[i].iv[0]].x) * (v3D[Cara[i].iv[3]].z - v3D[Cara[i].iv[0]].z);
			Az+= (v3D[Cara[i].iv[2]].x - v3D[Cara[i].iv[0]].x) * (v3D[Cara[i].iv[3]].y - v3D[Cara[i].iv[0]].y)
											-(v3D[Cara[i].iv[2]].y - v3D[Cara[i].iv[0]].y) * (v3D[Cara[i].iv[3]].x - v3D[Cara[i].iv[0]].x);
		}
		Cara[i].normalCara.x=Ax;
		Cara[i].normalCara.y=Ay;
		Cara[i].normalCara.z=Az;
		Cara[i].normalCara.NormaUnitario();
	}

}


void grid3D::generaPoligonos2Algunos(vector<int> &CualesRehacer)
{
	int i,ii,j,jj,k,ibb,l,icj;



	//Primer nivel de vecinos
	for(ii=0;ii<CualesRehacer.size();ii++) {
		i=CualesRehacer[ii];
		if (DBG) cout<<"Genero Bloq "<<i<<endl;
		h3D[i].vecino.resize(6);
		h3D[i].tipo_vecino.resize(6);
		for (j=0;j<6;j++) {
			icj=h3D[i].icara[j];
			if (Cara[icj].nVolumenes>1) {
				h3D[i].tipo_vecino[j]=ES_BLOQUE;
				ibb=Cara[icj].ih[0]; if (ibb==i) ibb=Cara[icj].ih[1];
				h3D[i].vecino[j]=ibb;
			} else {
				h3D[i].tipo_vecino[j]=ES_CARA;;
				h3D[i].vecino[j]=icj;
			}
		}
	}

	int iprint=72;
#if DBG2==10
	if (Etapa>=15)
		for (j=0;j<h3D[iprint].vecino.size();j++) {
			cout <<"Bloq "<<iprint<<" <-"<<j<<"->";
			if (h3D[iprint].tipo_vecino[j]==ES_BLOQUE)
				cout <<" Bloq "<<h3D[iprint].vecino[j]<<endl;
			else
				cout <<" Cara "<<h3D[iprint].vecino[j]<<endl;
		}
#endif
	//segundo nivel de vecinos (los vecinos de mis BLOQUES vecinos)
	int ip=0;

	for(ii=0;ii<CualesRehacer.size();ii++) {
		i=CualesRehacer[ii];
		int nvecinos_level1=h3D[i].vecino.size();
		for (j=0 ; j<nvecinos_level1 ;j++) {
			if (DBG && i==iprint) {
				cout <<i<<":Vecino L1="<<h3D[i].vecino[j];
				if (h3D[i].tipo_vecino[j]==ES_BLOQUE)
					cout <<"\tTipo=BLOQUE"<<endl;
				else
					cout <<"\tTipo=CARA:"<<h3D[i].tipo_vecino[j]<<endl;
			}
			if (h3D[i].tipo_vecino[j]==ES_CARA || h3D[i].tipo_vecino[j]==ES_CARA_L2) continue; //Las Caras No tienen vecinos (Ya existen ES_CARA_L2)
			ibb=h3D[i].vecino[j];

			if(1==0) cout<<"Estudio vecinos del bloque "<<ibb<<endl;
			for (k=0 ; k<h3D[ibb].vecino.size() && k<6 ;k++) {
				int tv=h3D[ibb].tipo_vecino[k];
				//				if(1==1) cout<<"vecino "<<k<<"\ttipo="<<tv<<endl;
				if (tv==ES_CARA || tv==ES_CARA_L2) {
					continue;
					if (fabs(Cara[ h3D[i].vecino[k] ].normalCara.z) >0.9) continue;
					int iC=h3D[ibb].vecino[k];
					//					if (Cara[ iC ].iBC ==1||Cara[ iC ].iBC >=10 || 0*ip>5) continue;
					tv=ES_CARA_L2;
					if(1==0) cout<<"Cara candidata="<<iC<<endl;
					ip++;
				}
				//Si este vecino de [j] es el nodo [i], no agregar...
				if (h3D[ibb].tipo_vecino[k]==ES_BLOQUE && h3D[ibb].vecino[k]==i) continue;
				//Veamos si este vecino [k] de [j] ya estaba en la lista....
				for (l=0  ; l<h3D[i].vecino.size() ;l++) {
					//					if (h3D[i].tipo_vecino[l]==ES_CARA) continue;
					if (h3D[i].vecino[l]==h3D[ibb].vecino[k] && h3D[i].tipo_vecino[l]==h3D[ibb].tipo_vecino[k]) break;//Ya estaba
				}
				if (l>=h3D[i].vecino.size()) {//es un nuevo vecino
					h3D[i].vecino.push_back(0);
					h3D[i].tipo_vecino.push_back(0);
					h3D[i].vecino[l]=h3D[ibb].vecino[k];
					h3D[i].tipo_vecino[l]=tv;


					if (DBG && i==3) {
						cout<< "bloque["<<i<<"]: Agrego nuevo vecino: Tipo="<<tv<<"\t cual="<<h3D[ibb].vecino[k]<<endl;
					}
					if(1==0) cout<< "bloque["<<i<<"]: Agrego nuevo vecino: Tipo="<<tv<<"\t cual="<<h3D[ibb].vecino[k]<<endl;
				}

			}
		}
	}

#if DBG2==10
	if(Etapa>15)
		for (j=0;j<h3D[iprint].vecino.size();j++) {
			cout <<"Bloq "<<iprint<<" <-"<<j<<"->";
			if (h3D[iprint].tipo_vecino[j]==ES_BLOQUE)
				cout <<" Bloq="<<h3D[iprint].vecino[j]<<endl;
			else
				cout <<" Cara="<<h3D[iprint].vecino[j]<<", tipo="<<h3D[iprint].tipo_vecino[j]<<endl;
		}
#endif

	for(ii=0;ii<CualesRehacer.size();ii++) {
		i=CualesRehacer[ii];
		if(1==0) cout<<"Rehacer i="<<i<<endl;


		R3 VA,VB,NB;
		VA=h3D[i].centro;
		for (j=0 ; j< h3D[i].vecino.size() ; j++) {
			if (h3D[i].tipo_vecino[j]==ES_CARA) {  // No para ES_CARA_L2
				VB=Cara[ h3D[i].vecino[j] ].centro;
				NB=Cara[ h3D[i].vecino[j] ].normalCara;
				if(1==0) cout<<"Cara[ h3D[i].vecino[j] ].iBC="<<Cara[ h3D[i].vecino[j] ].iBC<<endl;
				/*
				if (Cara[ h3D[i].vecino[j] ].iBC ==1||Cara[ h3D[i].vecino[j] ].iBC >=10) {
					double lambda=2*ppuntodiff(NB,VB,VA);
					Cara[ h3D[i].vecino[j] ].centro.x = VA.x+lambda*NB.x;
					Cara[ h3D[i].vecino[j] ].centro.y = VA.y+lambda*NB.y;
					Cara[ h3D[i].vecino[j] ].centro.z = VA.z+lambda*NB.z;
					VB=Cara[ h3D[i].vecino[j] ].centro;
				}
				 */
			}
		}
	}

	int navance=0;
	for(ii=0;ii<CualesRehacer.size();ii++) {
		i=CualesRehacer[ii];
		if (ii>=navance*CualesRehacer.size()/20) {
			printf(".%d",navance);fflush(stdout);
			myfileSalida<<"."<<navance;
			navance++;
		}
		h3D[i].Poligono.resize( h3D[i].vecino.size() );
		R3 VA,VB,NB;
		VA=h3D[i].centro;
		for (j=0 ; j< h3D[i].vecino.size() ; j++) {
			if (h3D[i].tipo_vecino[j]==ES_BLOQUE) {
				VB=h3D[ h3D[i].vecino[j] ].centro;
				if ( DBG2==10 && i==iprint) {
					if (PrintCaras) cout<<"Bloque vecino de "<<i<<"="<< h3D[i].vecino[j]<<endl;
				}
			} else {
				if ( DBG2==10 && i==iprint) {
					if (PrintCaras) cout<<"Cara vecina vecino de "<<i<<"="<< h3D[i].vecino[j]<<endl;
				}
				VB=Cara[ h3D[i].vecino[j] ].centro;
				NB=Cara[ h3D[i].vecino[j] ].normalCara;
				if (Cara[ h3D[i].vecino[j] ].iBC ==1||Cara[ h3D[i].vecino[j] ].iBC >=10) {
					double lambda=2*ppuntodiff(NB,VB,VA);
					VB.x = VA.x+lambda*NB.x;
					VB.y = VA.y+lambda*NB.y;
					VB.z = VA.z+lambda*NB.z;
				}
			}
			Poligono_Inicial(VA,VB, h3D[i].Poligono[j]);
			if ( DBG2==10 && i==iprint) {
				if (PrintCaras) cout<<"GeneraPoligonoInicial(VA,VB, h3D[i].Poligono[j]): A="<<h3D[i].Poligono[j].AreaPoligono<<endl;
			}
			for (jj=0 ; jj< h3D[i].vecino.size() ; jj++) {
				if (jj==j) continue;
				if (h3D[i].tipo_vecino[jj]==ES_BLOQUE) {
					VB=h3D[ h3D[i].vecino[jj] ].centro;
					if ( DBG2==10 && i==iprint) {
						if (PrintCaras) cout<<"K/Bloque vecino de "<<i<<"="<< h3D[i].vecino[jj]<<endl;
					}
				}
				if (h3D[i].tipo_vecino[jj]==ES_CARA || h3D[i].tipo_vecino[jj]==ES_CARA_L2) {
					if ( DBG2==10 && i==iprint) {
						if (PrintCaras) cout<<"K/Cara vecina vecino de "<<i<<"="<< h3D[i].vecino[jj]<<endl;
					}
					VB=Cara[ h3D[i].vecino[jj] ].centro;
					NB=Cara[ h3D[i].vecino[jj] ].normalCara;
					if (Cara[ h3D[i].vecino[jj] ].iBC ==1||Cara[ h3D[i].vecino[jj] ].iBC >=10) {
						double lambda=2*ppuntodiff(NB,VB,VA);
						VB.x = VA.x+lambda*NB.x;
						VB.y = VA.y+lambda*NB.y;
						VB.z = VA.z+lambda*NB.z;
					}
				}
				RecortaPoligono(VA,VB, h3D[i].Poligono[j]);
				if ( DBG2==10 && i==iprint) {
					if (PrintCaras) cout<<"h3D[i].Poligono[j].punto.size()="<< h3D[i].Poligono[j].punto.size()<<endl;
				}
				if (h3D[i].Poligono[j].punto.size() == 0) {

					if ( DBG2==10 && i==iprint) {
						if (PrintCaras) cout<<"Borrando este vecino="<<endl;
					}
					h3D[i].Poligono.erase(h3D[i].Poligono.begin()+j);
					h3D[i].vecino.erase(h3D[i].vecino.begin()+j);
					h3D[i].tipo_vecino.erase(h3D[i].tipo_vecino.begin()+j);
					j--;
					break;
				}
			}
		}
	}
	cout<<".OK"<<endl;
	myfileSalida<<".OK"<<endl;

	//calculos de areas y longitudes de trazos
	for(ii=0;ii<CualesRehacer.size();ii++) {
		i=CualesRehacer[ii];
		for (k=0; k<h3D[i].Poligono.size(); k++) {
			vector<R3> *Pto;
			Pto= &(h3D[i].Poligono[k].punto);
			double Area,Ax,Ay,Az;
			Area=0;
			for (j=1; j<Pto->size(); j++) {
				(*Pto)[j].L = sqrt(	  sqr( (*Pto)[j].x- (*Pto)[j-1].x )
						+ sqr( (*Pto)[j].y- (*Pto)[j-1].y )
						+ sqr( (*Pto)[j].z- (*Pto)[j-1].z ) );
				if ((*Pto)[j].L <1e-5) {
					(*Pto).erase( (*Pto).begin() + j);
					j--;
					continue;
				}
				if (j<2) continue;
				Az=((*Pto)[j-1].x-(*Pto)[0].x)*((*Pto)[j].y-(*Pto)[0].y)-((*Pto)[j-1].y-(*Pto)[0].y)*((*Pto)[j].x-(*Pto)[0].x);
				Ax=((*Pto)[j-1].y-(*Pto)[0].y)*((*Pto)[j].z-(*Pto)[0].z)-((*Pto)[j-1].z-(*Pto)[0].z)*((*Pto)[j].y-(*Pto)[0].y);
				Ay=((*Pto)[j-1].z-(*Pto)[0].z)*((*Pto)[j].x-(*Pto)[0].x)-((*Pto)[j-1].x-(*Pto)[0].x)*((*Pto)[j].z-(*Pto)[0].z);
				Area+=sqrt(sqr(Ax)+sqr(Ay)+sqr(Az))/2;
			}
			h3D[i].Poligono[k].AreaPoligono=Area;
			if (Area <1e-10) {
				h3D[i].Poligono.erase(h3D[i].Poligono.begin()+k);
				h3D[i].vecino.erase(h3D[i].vecino.begin()+k);
				h3D[i].tipo_vecino.erase(h3D[i].tipo_vecino.begin()+k);
				k--;
			}
		}
	}
}
void grid3D::Poligonos_Generar_Version3()
{
	int i,j,k,l,icj,ibb,jj;
	double xg,yg,zg,x0,y0,z0,x1,y1,z1,d1x,d1y,d1z,d2x,d2y,d2z,d3x,d3y,d3z,dij,lambda;
	double Ax,Ay,Az,AA;
	QuienGeneraPoligonos=2;

	//Primer nivel de vecinos
	if (PrintVecinos1) cout<<"P Primer nivel de vecinos:"<<endl;
	nVolFinito=nH3D+nTriPrisma3D;
	VolFinito.resize(nVolFinito);
	for(i=0;i<nVolFinito;i++) {
		if (i<nH3D) {
			VolFinito[i].centro=h3D[i].centro;
			VolFinito[i].vecino.resize(6);
			VolFinito[i].tipo_vecino.resize(6);
			VolFinito[i].vecino_centro.resize(6);
			VolFinito[i].vecino_normal.resize(6);
			for (j=0;j<6;j++) {
				icj=h3D[i].icara[j];
				if (Cara[icj].nVolumenes>1) {
					VolFinito[i].tipo_vecino[j]=ES_BLOQUE;
					ibb=Cara[icj].ih[0]; if (ibb==i) ibb=Cara[icj].ih[1];
					VolFinito[i].vecino[j]=ibb;
					VolFinito[i].vecino_centro[j]=h3D[ibb].centro;
					VolFinito[i].vecino_normal[j]=(h3D[ibb].centro-h3D[i].centro);
					VolFinito[i].vecino_normal[j].NormaUnitario();
				} else {
					VolFinito[i].tipo_vecino[j]=ES_CARA;;
					VolFinito[i].vecino[j]=icj;
					VolFinito[i].vecino_centro[j]=Cara[icj].centro;
					VolFinito[i].vecino_normal[j]=Cara[icj].normalCara;
				}
			}
		} else {
			int jTP=i-nH3D;
			VolFinito[i].centro=TriPrisma3D[jTP].centro;
			VolFinito[i].vecino.resize(5);
			VolFinito[i].tipo_vecino.resize(5);
			VolFinito[i].vecino_centro.resize(5);
			VolFinito[i].vecino_normal.resize(5);
			VolFinito[i].vecino_normal.resize(5);
			for (j=0;j<5;j++) {
				icj=TriPrisma3D[i].icara[j];
				if (Cara[icj].nVolumenes>1) {
					VolFinito[i].tipo_vecino[j]=ES_BLOQUE;
					ibb=Cara[icj].ih[0]; if (ibb==i) ibb=Cara[icj].ih[1];
					VolFinito[i].vecino[j]=ibb;
					VolFinito[i].vecino_centro[j]=TriPrisma3D[ibb].centro;
					VolFinito[i].vecino_normal[j]=(TriPrisma3D[ibb].centro-TriPrisma3D[jTP].centro);
					VolFinito[i].vecino_normal[j].NormaUnitario();
				} else {
					VolFinito[i].tipo_vecino[j]=ES_CARA;;
					VolFinito[i].vecino[j]=icj;
					VolFinito[i].vecino_centro[j]=Cara[icj].centro;
					VolFinito[i].vecino_normal[j]=Cara[icj].normalCara;
				}
			}


		}
	}
#if 0
	//segundo nivel de vecinos (los vecinos de mis vecinos)
	int itera;
	for (itera=0;itera<1;itera++) {
		if (PrintVecinos1) cout<<"P itera="<<itera<<endl;
		int ip=0;

		int navance=0;
		for(i=0;i<nVolFinito;i++) {
			int nvecinos_level1=VolFinito[i].vecino.size();

			if (i>=navance*nVolFinito/20) {
				printf(".%d",navance);fflush(stdout);

//				cout<<"P itera="<<itera;
//				cout<<"P i="<<i<<" nVolFinito="<<nVolFinito;
//				cout<<"P nvecinos_level1="<<nvecinos_level1<<endl;

				myfileSalida<<"."<<navance;
				navance++;
			}
			for (j=0 ; j<nvecinos_level1 ;j++) {
				if (VolFinito[i].tipo_vecino[j]==ES_CARA || VolFinito[i].tipo_vecino[j]==ES_CARA_L2 ) continue; //Las Caras No tienen vecinos (Auno no existen ES_CARA_L2)
				ibb=VolFinito[i].vecino[j];
				for (k=0 ; k<VolFinito[ibb].vecino.size() ;k++) {
					int tv=VolFinito[ibb].tipo_vecino[k];
					if (tv==ES_CARA || tv==ES_CARA_L2) {
						int iC=VolFinito[ibb].vecino[k];
						if (Cara[ iC ].iBC ==1||Cara[ iC ].iBC >=10 || 0*ip>5) continue;
						tv=ES_CARA_L2;
						ip++;
					}
					//Si este vecino de [j] es el nodo [i], no agregar...
					if (VolFinito[ibb].tipo_vecino[k]==ES_BLOQUE && VolFinito[ibb].vecino[k]==i) continue;
					//Veamos si este vecino [k] de [j] ya estaba en la lista....
					for (l=0  ; l<VolFinito[i].vecino.size() ;l++) {
						//					if (h3D[i].tipo_vecino[l]==ES_CARA) continue;
						if (VolFinito[i].vecino[l]==VolFinito[ibb].vecino[k]) break;//Ya estaba
					}
					if (l>=VolFinito[i].vecino.size()) {//es un nuevo vecino
						VolFinito[i].vecino.push_back(VolFinito[ibb].vecino[k]);
						VolFinito[i].tipo_vecino.push_back(tv);
						VolFinito[i].vecino_centro.push_back(VolFinito[ibb].vecino_centro[k]);
						VolFinito[i].vecino_normal.push_back(VolFinito[ibb].vecino_centro[k]-VolFinito[i].centro);
						VolFinito[i].vecino_normal[l].NormaUnitario();
					}

				}
			}
		}
	}
	if (PrintVecinos1) cout<<"P itera="<<itera<<endl;
#endif
	if (0) {
		// Agrego los niveles inferiores
		if (PrintVecinos1) cout<<"P Agrego los niveles inferiores:"<<endl;
		tic();
		int navance=0;
		for(i=0;i<nVolFinito;i++) {


			if (i>=navance*nVolFinito/20) {
				printf(".%d",navance);fflush(stdout);


				myfileSalida<<"."<<navance;
				navance++;
			}
			ibb=i/3*3 ;
			if (ibb<i-1) {
				l=VolFinito[i].vecino.size();
				{
					VolFinito[i].vecino.push_back(ibb);
					VolFinito[i].tipo_vecino.push_back(ES_BLOQUE);
					VolFinito[i].vecino_centro.push_back(VolFinito[ibb].centro);
					VolFinito[i].vecino_normal.push_back(VolFinito[ibb].centro-VolFinito[i].centro);
					VolFinito[i].vecino_normal[l].NormaUnitario();
				}

			}
		}

		cout<<".OK"<<endl;toc();


	}
	if(1) {
		// nivel de vecinos (el soporte de mis vertices)
		if (PrintVecinos1)  cout<<"P soporte de mis vertices:"<<endl;tic();
		int navance=0;
		for(i=0;i<nVolFinito;i++) {

			if (i>=navance*nVolFinito/20) {
				printf(".%d",navance);fflush(stdout);
				myfileSalida<<"."<<navance;
				navance++;
			}
			int nvertices;
			if (i<nH3D) nvertices=8;
			else nvertices=6;
			for (j=0 ; j<nvertices ;j++) {
				int vertice;
				if (i<nH3D)
					vertice=h3D[i].iv[j];
				else
					vertice=TriPrisma3D[i-nH3D].iv[j];
				for (int ell=0;ell<v3D[vertice].soporte.size();ell++) {
					ibb=v3D[vertice].soporte[ell];
					if (ibb==i)continue;
					//Veamos si este vecino [k] de [j] ya estaba en la lista....
					for (l=0  ; l<VolFinito[i].vecino.size() ;l++) {
						if (VolFinito[i].tipo_vecino[l]==ES_CARA) continue;
						if (VolFinito[i].vecino[l]==ibb) break;//Ya estaba
					}
					if (l>=VolFinito[i].vecino.size()) {//es un nuevo vecino
						VolFinito[i].vecino.push_back(ibb);
						VolFinito[i].tipo_vecino.push_back(ES_BLOQUE);
						VolFinito[i].vecino_centro.push_back(VolFinito[ibb].centro);
						VolFinito[i].vecino_normal.push_back(VolFinito[ibb].centro-VolFinito[i].centro);
						VolFinito[i].vecino_normal[l].NormaUnitario();
					}
				}
			}
		}
		cout<<".OK"<<endl;toc();
	}


	if (1) {
		// Agrego los 3 niveles de mis vecinos
		if (PrintVecinos1) cout<<"P Agrego los 3 niveles de mis vecinos:"<<endl;tic();
		int navance=0;
		for(i=0;i<nVolFinito;i++) {
			if (i>=navance*nVolFinito/20) {
				printf(".%d",navance);fflush(stdout);
				myfileSalida<<"."<<navance;
				navance++;
			}
			int nvecinos_level1=VolFinito[i].vecino.size();
			for (j=0 ; j<nvecinos_level1 ;j++) {
				if (VolFinito[i].tipo_vecino[j]==ES_CARA || VolFinito[i].tipo_vecino[j]==ES_CARA_L2 ) continue; //Las Caras No tienen vecinos (Auno no existen ES_CARA_L2)
				int ibb0=VolFinito[i].vecino[j];
				for (k=0;k<3;k++) {
					ibb=ibb0/3*3+k;
					//Veamos si este vecino [k] de [j] ya estaba en la lista....
					if (ibb==ibb0) continue;
					if (ibb==i) continue;
					for (l=0  ; l<VolFinito[i].vecino.size() ;l++) {
						if (VolFinito[i].tipo_vecino[l]==ES_BLOQUE && VolFinito[i].vecino[l]==ibb) break;//Ya estaba
					}
					if (l>=VolFinito[i].vecino.size()) {//es un nuevo vecino
						VolFinito[i].vecino.push_back(ibb);
						VolFinito[i].tipo_vecino.push_back(ES_BLOQUE);
						VolFinito[i].vecino_centro.push_back(VolFinito[ibb].centro);
						VolFinito[i].vecino_normal.push_back(VolFinito[ibb].centro-VolFinito[i].centro);
						VolFinito[i].vecino_normal[l].NormaUnitario();
					}
				}
			}
		}
		cout<<".OK"<<endl;toc();
	}

	//Agrego Caras de mis vecinos
	int imprimir2=0;

	if (PrintVecinos1) cout<<"P Agrego Caras de mis vecinos:"<<endl;
	if(1){
		int navance=0;
		for(i=0;i<nVolFinito;i++) {
			int nvecinos_level1=VolFinito[i].vecino.size();

			if (i>=navance*nVolFinito/20) {
				printf(".%d",navance);fflush(stdout);myfileSalida<<"."<<navance;navance++;
			}
			imprimir=0;
			if (i==1165 ) imprimir=0;

			if (imprimir) {
				cout<<", VolFinito="<<i<<endl;
			}

			for (j=0 ; j<nvecinos_level1 ;j++) {
				if (VolFinito[i].tipo_vecino[j]==ES_CARA || VolFinito[i].tipo_vecino[j]==ES_CARA_L2 ) continue; //Las Caras No tienen vecinos (Auno no existen ES_CARA_L2)
				ibb=VolFinito[i].vecino[j];
				imprimir2=1;
				for (k=0 ; k<VolFinito[ibb].vecino.size() ;k++) {
					if (VolFinito[ibb].tipo_vecino[k]==ES_CARA ) {
						for (l=0  ; l<VolFinito[i].vecino.size() ;l++) {
							if (VolFinito[i].tipo_vecino[l]==ES_BLOQUE) continue;//Solo busco las caras preexistentes
							if (VolFinito[i].vecino[l]==VolFinito[ibb].vecino[k]) break;//Ya estaba
						}
						if (l>=VolFinito[i].vecino.size()) { //es un nuevo vecino

							if (imprimir  && imprimir2) {
								if (imprimir2) {
									cout<<", vecino:"<<ibb;
								}
								cout<<endl;;
								imprimir2=0;
							}
							// Solo la agrego si no corta a los nodos originales
							int loagrego=1;
							R3 VA,VB,NB;
							VA=VolFinito[ibb].vecino_centro[k];
							NB=VolFinito[ibb].vecino_normal[k];
							{

								if (imprimir) {
									cout<<", Cara="<<VolFinito[ibb].vecino[k];
//									cout<<", VA=["<<VA.x<<","<<VA.y<<","<<VA.z<<"]";
									cout<<", NB=["<<NB.x<<","<<NB.y<<","<<NB.z<<"]";
								}

								int nvertices;
								if (i<nH3D) nvertices=8; else nvertices=6;
								int nvertices_en_Plano=0;
								for (jj=0 ; jj<nvertices ;jj++) {
									int vertice;
									if (i<nH3D) vertice=h3D[i].iv[jj];else vertice=TriPrisma3D[i-nH3D].iv[jj];
									VB.x=v3D[vertice].x;
									VB.y=v3D[vertice].y;
									VB.z=v3D[vertice].z;
									if (imprimir && 0) {
										cout<<", VB=["<<VB.x<<","<<VB.y<<","<<VB.z<<"]";
										cout<<", ppuntodiff(NB,VB,VA)="<<ppuntodiff(NB,VB,VA);
									}
									if (ppuntodiff(NB,VB,VA)>1e-5) {
										if (imprimir) {
											cout<<", El plano corta al vertice. No lo considero"<<endl;
										}
										loagrego=0;break; //El plano corta al vertice. No lo considero
									}
									if (ibb/3==i/3 && fabs(NB.z)>fabs(NB.x) &&fabs(NB.z)>fabs(NB.y) ) continue;

									if (ppuntodiff(NB,VB,VA)>-1e-10) {
										nvertices_en_Plano++;
										if (nvertices_en_Plano>2) {
											if (imprimir) {
												cout<<", El plano corta a "<<nvertices_en_Plano<<" vertices. No lo considero"<<endl;
											}
											loagrego=0;break; //El plano corta al vertice. No lo considero
										}
									}

								}
							}
							if (loagrego) {
								if (imprimir) {
									cout<<", Agrego este vecino"<<endl;
								}
								VolFinito[i].vecino.push_back(VolFinito[ibb].vecino[k]);
								if (ibb/3==i/3 && fabs(NB.z)>fabs(NB.x) &&fabs(NB.z)>fabs(NB.y) )
									VolFinito[i].tipo_vecino.push_back(ES_CARA);
								else
									VolFinito[i].tipo_vecino.push_back(ES_CARA_L2);
								VolFinito[i].vecino_centro.push_back(VolFinito[ibb].vecino_centro[k]);
								VolFinito[i].vecino_normal.push_back(VolFinito[ibb].vecino_normal[k]);
							}
						}
					}

				}
			}
		}
	}

	cout<<".OK"<<endl;
//
	if (PrintVecinos1) cout<<"P Retocar coordenadas de los bordes Nivel 1"<<endl;
	for(i=0;i<nVolFinito;i++) {
		R3 VA,VB,NB;
		VA=VolFinito[i].centro;
		VolFinito[i].vecino_centro_caraoriginal.resize(VolFinito[i].vecino_centro.size());
		for (j=0 ; j< VolFinito[i].vecino.size() ; j++) {
			if (VolFinito[i].tipo_vecino[j]==ES_CARA  || VolFinito[i].tipo_vecino[j]==ES_CARA_L2) { //Retocar coordenadas de los bordes Nivel 1 (no para ES_CARA_L2)
				VB=VolFinito[i].vecino_centro[j];
				VolFinito[i].vecino_centro_caraoriginal[j]=VB;
				NB=VolFinito[i].vecino_normal[j];
				//if (Cara[ VolFinito[i].vecino[j] ].iBC ==1||Cara[ VolFinito[i].vecino[j] ].iBC >=10)
				{
					double lambda=2*ppuntodiff(NB,VB,VA);
					VolFinito[i].vecino_centro[j].x = VA.x+lambda*NB.x;
					VolFinito[i].vecino_centro[j].y = VA.y+lambda*NB.y;
					VolFinito[i].vecino_centro[j].z = VA.z+lambda*NB.z;
				}
			}
		}
	}

	if (PrintVecinos1) cout<<"P Genera Poligonos"<<endl;
	int  navance=0;
	for (int ipasada=0;ipasada<4;ipasada++) {
		for(i=0;i<nVolFinito;i++) {
			if (i>=navance*nVolFinito/20) {
				printf(".%d",navance);fflush(stdout); myfileSalida<<"."<<navance; navance++;
			}
			VolFinito[i].Poligono.resize( VolFinito[i].vecino.size() );
			R3 CentroVolFinito,CentroVecinoJ,CentroVecinoJJ,NormalIaJ;
			CentroVolFinito=VolFinito[i].centro;


			imprimir=0;
			if (i==1165 ) imprimir=1;
			if (i==2837 ) imprimir=1;


			if (imprimir) {
				if (PrintVecinos1) cout<<"P VolFinito="<<i<<endl;
			}

			//ipasada==0 : Test para saber si incluir o no a triangulos de borde (ES_CARA_L2).
			//             Criterio: Poligono inicial==triangulo, se corta por lo bloques vecinos y se elimina si area =0
			//ipasada==1 : Se detectan planos paralelos
			//ipasada==2 : Se simetrizan las incidencias
			for (j=0 ; j< VolFinito[i].vecino.size() ; j++) {
				CentroVecinoJ=VolFinito[i].vecino_centro[j];
				NormalIaJ=VolFinito[i].vecino_normal[j];
				if (ipasada==0) {
					if (VolFinito[i].tipo_vecino[j]!=ES_CARA_L2) continue; //Solo Caras ES_CARA_L2 en ipasada==0
					int iC=VolFinito[i].vecino[j];
					Poligono_InicialCara(CentroVolFinito,CentroVecinoJ, VolFinito[i].Poligono[j],iC);
				} else if (ipasada==2) {
					if (VolFinito[i].tipo_vecino[j]!=ES_BLOQUE) continue; //Solo Bloques en ipasada==2 (simetrizando las incidencias)
				} else  {
					Poligono_Inicial(CentroVolFinito,CentroVecinoJ, VolFinito[i].Poligono[j]);
				}

				if (imprimir) {
					if (PrintVecinos1) cout<<"P ipasada="<<ipasada<<" j="<<j<<" vec[j]="<<VolFinito[i].vecino[j] <<" tipo="<<VolFinito[i].tipo_vecino[j];
					if (PrintVecinos1) cout <<" N=["<<VolFinito[i].Poligono[j].normal.x<<","<<VolFinito[i].Poligono[j].normal.y<<","<<VolFinito[i].Poligono[j].normal.z<<"]";
					if (PrintVecinos1) cout<<endl;
				}

				int muere=0;

				if (ipasada==2) { //Simetrización
					muere=1;
					int i2= VolFinito[i].vecino[j];

					if (imprimir) {
						if (PrintVecinos1) cout<<"P i2="<<i2;
					}

					for (jj=0 ; jj< VolFinito[i2].vecino.size() ; jj++) {
						if (VolFinito[i2].tipo_vecino[jj]!=ES_BLOQUE) continue; //Solo Bloques en ipasada==2 (simetrizando las incidencias)
						if (imprimir) {
							if (PrintVecinos1) cout<<"P  ¿"<<VolFinito[i2].vecino[jj]<<"=="<<i<<"?  ";
						}
						if (VolFinito[i2].vecino[jj]==i) {
							muere=0;

							if (imprimir) {
								if (PrintVecinos1) cout<<"P SI!!"<<endl;
							}
							break;
						}
					}
					if (imprimir) {
						if (PrintVecinos1) cout<<"P muere="<<muere<<endl;
					}
					if (muere==1) { //Vecino No simetrico

						VolFinito[i].Poligono.erase(VolFinito[i].Poligono.begin()+j);
						VolFinito[i].vecino.erase(VolFinito[i].vecino.begin()+j);
						VolFinito[i].tipo_vecino.erase(VolFinito[i].tipo_vecino.begin()+j);
						VolFinito[i].vecino_centro_caraoriginal.erase(VolFinito[i].vecino_centro_caraoriginal.begin()+j);
						VolFinito[i].vecino_centro.erase(VolFinito[i].vecino_centro.begin()+j);
						VolFinito[i].vecino_normal.erase(VolFinito[i].vecino_normal.begin()+j);
						j--;

					}
					continue;

				}


				for (jj=0 ; jj< VolFinito[i].vecino.size() ; jj++) {

					if (ipasada==0 && VolFinito[i].tipo_vecino[jj]!=ES_BLOQUE) continue; //En ipasada=0 solo se intersecta con los bloques

					int es_paralelo=0;
					if (jj==j) continue;

					CentroVecinoJJ=VolFinito[i].vecino_centro[jj];

					if (imprimir &&  VolFinito[i].vecino[j]==36098 ) {
						if (PrintVecinos1) cout<<"  jj="<<jj<<" Vecino[jj]="<< VolFinito[i].vecino[jj] << "\tppunto(NAB,VolFinito[i].vecino_normal[jj])="<<ppunto(NormalIaJ,VolFinito[i].vecino_normal[jj])<<endl;
						if (PrintVecinos1) cout<<"  P N1=["<<VolFinito[i].vecino_normal[j].x<<","<<VolFinito[i].vecino_normal[j].y<<","<<VolFinito[i].vecino_normal[j].z<<"]"<<endl;
						if (PrintVecinos1) cout<<"  P N2=["<<VolFinito[i].vecino_normal[jj].x<<","<<VolFinito[i].vecino_normal[jj].y<<","<<VolFinito[i].vecino_normal[jj].z<<"]"<<endl;
						if (PrintVecinos1) cout<<"  P VB=["<<CentroVecinoJ.x<<","<<CentroVecinoJ.y<<","<<CentroVecinoJ.z<<"]"<<endl;
						if (PrintVecinos1) cout<<"  P VBj=["<<CentroVecinoJJ.x<<","<<CentroVecinoJJ.y<<","<<CentroVecinoJJ.z<<"]\tppuntodiff(NAB, VB, VBj)="<<ppuntodiff(NormalIaJ, CentroVecinoJ, CentroVecinoJJ)<<endl;
					}

					if (ipasada==1  && VolFinito[i].tipo_vecino[jj] !=ES_BLOQUE ) { //Test de paralelismo solo en ipasada==1
						if(ppunto(NormalIaJ,VolFinito[i].vecino_normal[jj])>.99999999 && ppuntodiff(NormalIaJ, CentroVecinoJ, CentroVecinoJJ)>-1e-10) { //Caso paralelos
							if (ipasada==0)
								continue;
							else
								es_paralelo=1;
						}

						if (es_paralelo && jj>j) {
							if (imprimir) {
								if (PrintVecinos1) cout<<"  P Vecino "<< VolFinito[i].vecino[jj]<<" se muere por paralelo, tipo="<< VolFinito[i].tipo_vecino[jj]<<endl;
								if (PrintVecinos1) cout<<"    jj="<<jj<<" Vecino[jj]="<< VolFinito[i].vecino[jj] <<
										"\tppunto(NAB,VolFinito[i].vecino_normal[jj])="<<ppunto(NormalIaJ,VolFinito[i].vecino_normal[jj])<<endl;
								if (PrintVecinos1) cout<<"    P N1=["<<VolFinito[i].vecino_normal[j].x<<","<<VolFinito[i].vecino_normal[j].y<<","<<VolFinito[i].vecino_normal[j].z<<"]"<<endl;
								if (PrintVecinos1) cout<<"    P N2=["<<VolFinito[i].vecino_normal[jj].x<<","<<VolFinito[i].vecino_normal[jj].y<<","<<VolFinito[i].vecino_normal[jj].z<<"]"<<endl;
								if (PrintVecinos1) cout<<"    P VA=["<<CentroVolFinito.x<<","<<CentroVolFinito.y<<","<<CentroVolFinito.z<<"]"<<endl;
								if (PrintVecinos1) cout<<"    P VB=["<<CentroVecinoJ.x<<","<<CentroVecinoJ.y<<","<<CentroVecinoJ.z<<"]"<<endl;
								if (PrintVecinos1) cout<<"    P VBj=["<<CentroVecinoJJ.x<<","<<CentroVecinoJJ.y<<","<<CentroVecinoJJ.z<<
										"]\tppuntodiff(NAB, VB, VBj)="<<ppuntodiff(NormalIaJ, CentroVecinoJ, CentroVecinoJJ)<<endl;
								R3 Ntmp=CentroVecinoJ-CentroVolFinito;//Ntmp.NormaUnitario();
								if (PrintVecinos1) cout<<"    P Ntmp=["<<Ntmp.x<<","<<Ntmp.y<<","<<Ntmp.z<<"]"<<endl;
								R3 Ntmpj=CentroVecinoJJ-CentroVolFinito;//Ntmpj.NormaUnitario();
								if (PrintVecinos1) cout<<"    P Ntmpj=["<<Ntmpj.x<<","<<Ntmpj.y<<","<<Ntmpj.z<<"]"<<endl;

							}
							VolFinito[i].Poligono.erase(VolFinito[i].Poligono.begin()+jj);
							VolFinito[i].vecino.erase(VolFinito[i].vecino.begin()+jj);
							VolFinito[i].tipo_vecino.erase(VolFinito[i].tipo_vecino.begin()+jj);
							VolFinito[i].vecino_centro_caraoriginal.erase(VolFinito[i].vecino_centro_caraoriginal.begin()+jj);
							VolFinito[i].vecino_centro.erase(VolFinito[i].vecino_centro.begin()+jj);
							VolFinito[i].vecino_normal.erase(VolFinito[i].vecino_normal.begin()+jj);
							jj--;
							continue;
						}
						if ( es_paralelo && jj<j) {
							if (imprimir ) {
								if (es_paralelo==0)
									if (PrintVecinos1) cout<<"P Vol se muere por area 0: Vecino "<< VolFinito[i].vecino[jj]<<", tipo="<< VolFinito[i].tipo_vecino[jj]<<endl;
								else
									if (PrintVecinos1) cout<<"P Vol j se muere por serparalelo a: Vecino "<< VolFinito[i].vecino[jj]<<", tipo="<< VolFinito[i].tipo_vecino[jj]<<endl;

								if (PrintVecinos1) cout<<"    jj="<<jj<<" Vecino[jj]="<< VolFinito[i].vecino[jj] << "\tppunto(NAB,VolFinito[i].vecino_normal[jj])="<<ppunto(NormalIaJ,VolFinito[i].vecino_normal[jj])<<endl;
								if (PrintVecinos1) cout<<"    P N1=["<<VolFinito[i].vecino_normal[j].x<<","<<VolFinito[i].vecino_normal[j].y<<","<<VolFinito[i].vecino_normal[j].z<<"]"<<endl;
								if (PrintVecinos1) cout<<"    P N2=["<<VolFinito[i].vecino_normal[jj].x<<","<<VolFinito[i].vecino_normal[jj].y<<","<<VolFinito[i].vecino_normal[jj].z<<"]"<<endl;
								if (PrintVecinos1) cout<<"    P VB=["<<CentroVecinoJ.x<<","<<CentroVecinoJ.y<<","<<CentroVecinoJ.z<<"]"<<endl;
								if (PrintVecinos1) cout<<"    P VBj=["<<CentroVecinoJJ.x<<","<<CentroVecinoJJ.y<<","<<CentroVecinoJJ.z<<"]\tppuntodiff(NAB, VB, VBj)="<<ppuntodiff(NormalIaJ, CentroVecinoJ, CentroVecinoJJ)<<endl;


								muere=1;
							}
							VolFinito[i].Poligono.erase(VolFinito[i].Poligono.begin()+j);
							VolFinito[i].vecino.erase(VolFinito[i].vecino.begin()+j);
							VolFinito[i].tipo_vecino.erase(VolFinito[i].tipo_vecino.begin()+j);
							VolFinito[i].vecino_centro_caraoriginal.erase(VolFinito[i].vecino_centro_caraoriginal.begin()+j);
							VolFinito[i].vecino_centro.erase(VolFinito[i].vecino_centro.begin()+j);
							VolFinito[i].vecino_normal.erase(VolFinito[i].vecino_normal.begin()+j);
							j--;



							break;
						}
					}

					if (es_paralelo==0)
						RecortaPoligono(CentroVolFinito,CentroVecinoJJ, VolFinito[i].Poligono[j]);
					if ( VolFinito[i].Poligono[j].punto.size() == 0  ) {
						if (imprimir ) {
							if (es_paralelo==0)
								if (PrintVecinos1) cout<<"P Vol se muere por area 0: Vecino "<< VolFinito[i].vecino[jj]<<", tipo="<< VolFinito[i].tipo_vecino[jj]<<endl;
							else
								if (PrintVecinos1) cout<<"P Vol j se muere por serparalelo a: Vecino "<< VolFinito[i].vecino[jj]<<", tipo="<< VolFinito[i].tipo_vecino[jj]<<endl;

							if (PrintVecinos1) cout<<"    jj="<<jj<<" Vecino[jj]="<< VolFinito[i].vecino[jj] << "\tppunto(NAB,VolFinito[i].vecino_normal[jj])="<<ppunto(NormalIaJ,VolFinito[i].vecino_normal[jj])<<endl;
							if (PrintVecinos1) cout<<"    P N1=["<<VolFinito[i].vecino_normal[j].x<<","<<VolFinito[i].vecino_normal[j].y<<","<<VolFinito[i].vecino_normal[j].z<<"]"<<endl;
							if (PrintVecinos1) cout<<"    P N2=["<<VolFinito[i].vecino_normal[jj].x<<","<<VolFinito[i].vecino_normal[jj].y<<","<<VolFinito[i].vecino_normal[jj].z<<"]"<<endl;
							if (PrintVecinos1) cout<<"    P VB=["<<CentroVecinoJ.x<<","<<CentroVecinoJ.y<<","<<CentroVecinoJ.z<<"]"<<endl;
							if (PrintVecinos1) cout<<"    P VBj=["<<CentroVecinoJJ.x<<","<<CentroVecinoJJ.y<<","<<CentroVecinoJJ.z<<"]\tppuntodiff(NAB, VB, VBj)="<<ppuntodiff(NormalIaJ, CentroVecinoJ, CentroVecinoJJ)<<endl;


							muere=1;
						}
						VolFinito[i].Poligono.erase(VolFinito[i].Poligono.begin()+j);
						VolFinito[i].vecino.erase(VolFinito[i].vecino.begin()+j);
						VolFinito[i].tipo_vecino.erase(VolFinito[i].tipo_vecino.begin()+j);
						VolFinito[i].vecino_centro_caraoriginal.erase(VolFinito[i].vecino_centro_caraoriginal.begin()+j);
						VolFinito[i].vecino_centro.erase(VolFinito[i].vecino_centro.begin()+j);
						VolFinito[i].vecino_normal.erase(VolFinito[i].vecino_normal.begin()+j);
						j--;
						break;
					}
				}
				if (imprimir && muere==0) {
					if (PrintVecinos1) cout<<"P Vol sigue"<<endl;
				}
			}
		}
	}
	if (PrintVecinos1) cout<<".OK"<<endl;
	myfileSalida<<".OK"<<endl;

	//calculos de areas y longitudes de trazos
	for (i=0;i<nVolFinito;i++) {
		VolFinito[i].dibujado.resize(VolFinito[i].Poligono.size());
		for (k=0; k<VolFinito[i].Poligono.size(); k++) {
			vector<R3> *Pto;
			Pto= &(VolFinito[i].Poligono[k].punto);
			double Area,Ax,Ay,Az;
			Area=0;
			for (j=1; j<Pto->size(); j++) {	
				(*Pto)[j].L = sqrt(	  sqr( (*Pto)[j].x- (*Pto)[j-1].x ) 
						+ sqr( (*Pto)[j].y- (*Pto)[j-1].y )
						+ sqr( (*Pto)[j].z- (*Pto)[j-1].z ) );
				if ((*Pto)[j].L <1e-5) {
					(*Pto).erase( (*Pto).begin() + j);
					j--;
					continue;
				}
				if (j<2) continue;
				Az=((*Pto)[j-1].x-(*Pto)[0].x)*((*Pto)[j].y-(*Pto)[0].y)-((*Pto)[j-1].y-(*Pto)[0].y)*((*Pto)[j].x-(*Pto)[0].x);
				Ax=((*Pto)[j-1].y-(*Pto)[0].y)*((*Pto)[j].z-(*Pto)[0].z)-((*Pto)[j-1].z-(*Pto)[0].z)*((*Pto)[j].y-(*Pto)[0].y);
				Ay=((*Pto)[j-1].z-(*Pto)[0].z)*((*Pto)[j].x-(*Pto)[0].x)-((*Pto)[j-1].x-(*Pto)[0].x)*((*Pto)[j].z-(*Pto)[0].z);
				Area+=sqrt(sqr(Ax)+sqr(Ay)+sqr(Az))/2;
			}
			VolFinito[i].Poligono[k].AreaPoligono=Area;
			if (Area <1e-10) {
				VolFinito[i].Poligono.erase   (VolFinito[i].Poligono.begin()+k);
				VolFinito[i].vecino.erase     (VolFinito[i].vecino.begin()+k);
				VolFinito[i].tipo_vecino.erase(VolFinito[i].tipo_vecino.begin()+k);
				VolFinito[i].vecino_centro_caraoriginal.erase(VolFinito[i].vecino_centro_caraoriginal.begin()+k);
				VolFinito[i].vecino_centro.erase(VolFinito[i].vecino_centro.begin()+k);
				VolFinito[i].vecino_normal.erase(VolFinito[i].vecino_normal.begin()+k);
				k--;
			}
		}
	}
}


void grid3D::DZmin(double DzMinimo) {
	if (PrintDZmin) cout <<"P grid3D::DZmin(double DzMinimo="<<DzMinimo<<")"<<endl;
	int i,j,niz=4;
	for (i=0;i<v3D.size()/niz;i+=niz) {
		if (PrintDZmin) cout <<"P i="<<i<<endl;
		for(j=1;j<niz;j++) {

			if (i==820 ) {
				if (PrintDZmin) cout <<i+j<<"\t"<< v3D[i+j].z <<"\t"<<v3D[i+j].z-v3D[i+j-1].z <<endl;
			}
			if (v3D[i+j].z-v3D[i+j-1].z<DzMinimo) v3D[i+j].z=v3D[i+j-1].z+DzMinimo;
			if (i==820 ) {
				if (PrintDZmin) cout <<i+j<<"\t"<< v3D[i+j].z <<"\t"<<v3D[i+j].z-v3D[i+j-1].z <<endl;
			}
		}
	}
}




void grid3D::GeneraCarasTriPri()
{
	int ib,i;

	int navance=0;
	for (i=TriPri3DAnalizados;i<nTriPrisma3D;i++){

		if (i>=navance*(nTriPrisma3D-TriPri3DAnalizados)/20) {
			printf(".%d",navance);fflush(stdout);
			myfileSalida<<"."<<navance;
			navance++;
		}
		// Prisma de base Triangular:
		//    5
		//   /|\
		//  / | \
		// 3-----4
		// |  |  |
		// |  2  |
		// | / \ |
		// |/   \|
		// 0-----1

		ib=i;
		TriPrisma * TriP3D= &(TriPrisma3D[i]);

		//		cout<<"i="<<i<<endl;
		//		cout<<"vertices:"<<TriP3D->iv[0]<<" "<<TriP3D->iv[1]<<" "<<TriP3D->iv[2]
		//																			  <<" "<<TriP3D->iv[3]<<" "<<TriP3D->iv[4]<<" "<<TriP3D->iv[5]<<endl;

		TriP3D->icara[0]=AddCara3(i,TriP3D->iv[0],TriP3D->iv[2],TriP3D->iv[1],IBC_INF);
		TriP3D->icara[1]=AddCara3(i,TriP3D->iv[3],TriP3D->iv[4],TriP3D->iv[5],IBC_SUP);
		TriP3D->icara[2]=AddCara4(i,TriP3D->iv[0],TriP3D->iv[3],TriP3D->iv[5],TriP3D->iv[2]);
		TriP3D->icara[3]=AddCara4(i,TriP3D->iv[0],TriP3D->iv[1],TriP3D->iv[4],TriP3D->iv[3]);
		TriP3D->icara[4]=AddCara4(i,TriP3D->iv[1],TriP3D->iv[2],TriP3D->iv[5],TriP3D->iv[4]);

		//		cout <<"nCaras="<<nCaras<<endl;

	}
	cout<<".OK"<<endl;
	myfileSalida<<".OK"<<endl;
	TriPri3DAnalizados=nTriPrisma3D;
	cout <<"nCaras="<<nCaras<<endl;
}


void grid3D::GeneraCaras(int inicia)
{
	int ib,i;
	static int cuantas=0;
	//	cout<<"grid3D::GeneraCaras: inicia="<<inicia<<endl;
	if (inicia<0) {
		cuantas=0;
	}

	if (cuantas==0) {
		nCaras=0;
	}


	int navance=0;
	for (i=0;i<inicia;i++){

		if (i>=navance*inicia/20) {
			printf(".%d",navance);fflush(stdout);
			myfileSalida<<"."<<navance;
			navance++;
		}
		if (cuantas<nH3D) {
			//	  2------3
			//   /|     /|
			//  6-|----7 |
			//	| |    | |
			//	| 0----|-1
			//	|/     |/
			//  4------5

			ib=cuantas; cuantas++;
			if(1==0) cout<<"ib="<<ib<<"\tinicia="<<inicia<<endl;
			h3D[ib].icara[0]=AddCara4(ib,h3D[ib].iv[0],h3D[ib].iv[2],h3D[ib].iv[3],h3D[ib].iv[1]);
			h3D[ib].icara[1]=AddCara4(ib,h3D[ib].iv[0],h3D[ib].iv[4],h3D[ib].iv[6],h3D[ib].iv[2]);
			h3D[ib].icara[2]=AddCara4(ib,h3D[ib].iv[0],h3D[ib].iv[1],h3D[ib].iv[5],h3D[ib].iv[4]);
			h3D[ib].icara[3]=AddCara4(ib,h3D[ib].iv[4],h3D[ib].iv[5],h3D[ib].iv[7],h3D[ib].iv[6]);
			h3D[ib].icara[4]=AddCara4(ib,h3D[ib].iv[1],h3D[ib].iv[3],h3D[ib].iv[7],h3D[ib].iv[5]);
			h3D[ib].icara[5]=AddCara4(ib,h3D[ib].iv[2],h3D[ib].iv[6],h3D[ib].iv[7],h3D[ib].iv[3]);
		} 
	}
	if (inicia>0) {
		cout<<".OK"<<endl;
		myfileSalida<<".OK"<<endl;
	}
}

void grid3D::SeleccionaVolFinito(double px,double py,double pz)
{
	int i,j,jj,k,nr=5,nz=3,ir,iz,pj,pjmin;
	float pd2min,pd2;

	pd2min=1e10;
	for (pj=0;pj<nTriPrisma3D;pj++) {
		pd2=sqr(px-TriPrisma3D[pj].centro.x)+sqr(py-TriPrisma3D[pj].centro.y)+sqr(pz-TriPrisma3D[pj].centro.z);
		if (pd2<pd2min) {
			pd2min=pd2;
			pjmin=pj;
		}
	}
	if(Add_Voronoi) {
		for (i=0;i<VolFinitoSelected.size();i++) {
			if (VolFinitoSelected[i]==pjmin) {

				imprimir=1;
				VolFinitoSelected.erase(VolFinitoSelected.begin()+i);
				return;
			}
		}
		imprimir=1;
		VolFinitoSelected.push_back(pjmin);
		cout<<"T Agregado VolFinitoSelected.size()="<<VolFinitoSelected.size()<<" i="<<pjmin<<endl;
	} else {
		for (i=0;i<Selected_Triprisma.size();i++) {
			if (Selected_Triprisma[i]==pjmin) {

				imprimir=1;
				Selected_Triprisma.erase(Selected_Triprisma.begin()+i);
				return;
			}
		}
		Selected_Triprisma.push_back(pjmin);
		imprimir=1;
		cout<<"T Agregado Selected_Triprisma.size()="<<Selected_Triprisma.size()<<" i="<<pjmin<<endl;
	}


}


void grid3D::SeleccionaYMuestraCara(double px,double py,double pz)
{
	int i,j,jj,k,nr=5,nz=3,ir,iz,pj,pjmin;
	float pd2min,pd2;

	pd2min=1e10;
	for (pj=0;pj<nCaras;pj++) {
		pd2=sqr(px-Cara[pj].centro.x)+sqr(py-Cara[pj].centro.y)+sqr(pz-Cara[pj].centro.z);
		if (pd2<pd2min) {
			pd2min=pd2;
			pjmin=pj;
		}
	}
	cout<<"C Cara: "<<pjmin<<":"<<endl;
	cout<<"C Normal=["<<Cara[pjmin].normalCara.x<<","<<Cara[pjmin].normalCara.y<<","<<Cara[pjmin].normalCara.z<<endl;
	cout<<"C signo2="<<Cara[pjmin].signo2<<endl;
	cout<<"C P =["<<px<<","<<py<<","<<pz<<"]"<<endl;

	printf(" V1 =[%.2f %.2f %.2f]\n",Cara[pjmin].winX1,Cara[pjmin].winY1,Cara[pjmin].winZ1);
	printf(" V2 =[%.2f %.2f %.2f]\n",Cara[pjmin].winX2,Cara[pjmin].winY2,Cara[pjmin].winZ2);
	printf(" V3 =[%.2f %.2f %.2f]\n",Cara[pjmin].winX3,Cara[pjmin].winY3,Cara[pjmin].winZ3);
	cout<<endl;
	//TODO: Imprimir propiedades de  visualizacion (signo2)

}


void grid3D::Particulas_Init_3(double PosX,double PosY,double PosZ)
{
	//Inicializa particulas agregadas con Mouse
	int i,j,jj,k,nr=5,nz=3,ir,iz;
	float rho,theta;

	ParticulasZ.resize(nParticulas+nz*nr);
	ParticulasZlambda.resize(nParticulas+nz*nr);
	ParticulaEsAleatoria.resize(nParticulas+nz*nr);
	ParticulasBloq.resize(nParticulas+nz*nr);
	for (k=0;k<=maxpasadas;k++) {
		for (j=0;j<3;j++) {
			Particulas[k][j].resize(nParticulas+nz*nr);
		}
	}
	for (j=0;j<3;j++) {
		Particulas0[j].resize(nParticulas+nz*nr);
	}

	GLfloat_buffer = new float[6*maxpasadas*(nParticulas+nz*nr)];

	for (ir=0;ir<nr;ir++) {
		//TODO
		int pj,pk,pjmin;
		float pd2min,pd2,px,py,pz,pzmin,pzmax,pdx,pdy,pdz;

		rho=(   (double)rand() / ((double)(RAND_MAX)+(double)(1)) )*500;
		if (ir==0) rho=0;
		theta=(   (double)rand() / ((double)(RAND_MAX)+(double)(1)) )*atan(1)*8;


		px= PosX+rho*cos(theta);
		py= PosY+rho*sin(theta);
		pz= PosZ;

		pjmin=EnCualTriprismaXY(px, py, 0);
		while (pjmin<0) {
			rho=(   (double)rand() / ((double)(RAND_MAX)+(double)(1)) )*500;
			theta=(   (double)rand() / ((double)(RAND_MAX)+(double)(1)) )*atan(1)*8;
			px= PosX+rho*cos(theta);
			py= PosY+rho*sin(theta);
			pjmin=EnCualTriprismaXY(px, py, 0);

		}

		R3 ABxAC,AB,AC,AP;

		ABxAC=Cara[TriPrisma3D[pjmin].icara[0]].normalCara;
		AP.x=px-v3D[TriPrisma3D[pjmin].iv[0]].x;
		AP.y=py-v3D[TriPrisma3D[pjmin].iv[0]].y;
		AP.z=0 -v3D[TriPrisma3D[pjmin].iv[0]].z;

		//Ecuacion: AP . (AB x AC)=0  <==>  [(px,py,0)-A+(0,0,pz)] . ABxAC=0
		pzmin=-ppunto(AP,ABxAC)/ABxAC.z;

//Tapa superior
		ABxAC=Cara[TriPrisma3D[pjmin+2].icara[1]].normalCara;
		AP.x=px-v3D[TriPrisma3D[pjmin+2].iv[3]].x;
		AP.y=py-v3D[TriPrisma3D[pjmin+2].iv[3]].y;
		AP.z=0 -v3D[TriPrisma3D[pjmin+2].iv[3]].z;

		//Ecuacion: AP . (AB x AC)=0  <==>  [(px,py,0)-A+(0,0,pz)] . ABxAC=0
		pzmax=-ppunto(AP,ABxAC)/ABxAC.z;

		for (iz=0;iz<nz;iz++) {
			i=nParticulas++;
			float lambda=(iz+0.5)/nz;

			Particulas[0][0][i]= TriPrisma3D[pjmin].centro.x*0+px;
			Particulas[0][1][i]= TriPrisma3D[pjmin].centro.y*0+py;
			Particulas[0][2][i]= pzmin*(1-lambda)+pzmax*lambda;
			ParticulasZlambda[i]= lambda;
			ParticulasZ[i]= 0.5*iz;
			ParticulaEsAleatoria[i]= false;
			Particulas0[0][i]=Particulas[0][0][i]; //[posicion en cola][xyz][particula]
			Particulas0[1][i]=Particulas[0][1][i];
			Particulas0[2][i]=Particulas[0][2][i];
			ParticulasBloq[i]=pjmin;

			pjmin++;

			for (j=0;j<3;j++) {
				for (k=0;k<maxpasadas;k++) Particulas[k+1][j][i]=Particulas[0][j][i];
			}
		}
	}

	Spinner_particulas->sync_live(1,1);
}

//TODO: Ver particulas que salen del dominio
void grid3D::Particulas_Init(int i)
{
	double x,y,z,t;
	int j,k;

	if (ParticulaEsAleatoria[i]) {
		j=(   (double)rand() / ((double)(RAND_MAX)+(double)(1)) )* (nTriPrisma3D);
		if (i==0) {
			j=300;
		}
		Hz=-v3D[TriPrisma3D[j].iv[0]].z;

		//	cout <<"i="<<i<<" j="<<j<<" nTriPrisma3D="<<nTriPrisma3D<<endl;
		Particulas[0][0][i]= TriPrisma3D[j].centro.x;
		Particulas[0][1][i]= TriPrisma3D[j].centro.y;
		Particulas[0][2][i]= TriPrisma3D[j].centro.z;
		ParticulasZ[i]= 0.3*(j%3);
		ParticulasZlambda[i]= 0.3*(j%3);
		ParticulasBloq[i]=j;
	} else {

		Particulas[0][0][i]= Particulas0[0][i];
		Particulas[0][1][i]= Particulas0[1][i];
		Particulas[0][2][i]= Particulas0[2][i];
		ParticulasBloq[i]=j;
	}

	//	cout<<"j="<<j<<" Hz="<<Hz<<TriPrisma3D[j].centro.z
	//			<<" ParticulasZ[i]="<<ParticulasZ[i]<<endl;



	for (j=0;j<3;j++) {
		for (k=0;k<maxpasadas;k++) Particulas[k+1][j][i]=Particulas[0][j][i];
	}
	multiplode3++;if (multiplode3>2) multiplode3=0;
	deltade3++;
}

void grid3D::drawVelGL(vector<double> U,vector<double> V,vector<double> W)
/////OLD....BORRAR
{
	//	cout<<"grid3D::drawVelGL"<<"primerdrawVelGL="<<primerdrawVelGL<<"nParticulas="<<nParticulas<<endl;
	static double dt=0.1*sqr(Dominio_Xmax);
	static int ipasadas=0;
	double d2,d2min,x,y,z,dx,dy,dz,t;
	int i,j,k,jmin;
	if (primerdrawVelGL) {
		int oldsize=Particulas[0][0].size();
		for (k=0;k<=maxpasadas;k++) {
			for (j=0;j<3;j++) {
				Particulas[k][j].resize(nParticulas);
			}
		}

		for (i=oldsize;i<nParticulas;i++) {
			ParticulaEsAleatoria[i]=1;
			Particulas_Init(i);
		}

//		GLfloat_buffer = (GLfloat*) malloc(sizeof(GLfloat)*(6*maxpasadas*nParticulas));
		GLfloat_buffer = new float[6*maxpasadas*nParticulas];
	}

	primerdrawVelGL=0;
	ipasadas++;

	for (i=0;i<nParticulas;i++) {
		x=Particulas[0][0][i];
		y=Particulas[0][1][i];
		z=Particulas[0][2][i];
		d2min=1e10;
		for (j=0;j<nV3D;j++) {
			d2=sqr(x-v3D[j].x)+sqr(y-v3D[j].y)+sqr(z-v3D[j].z);
			if (d2<d2min) {
				d2min=d2;
				jmin=j;
			}
		}
		//cout<<"factorV="<<factorV<<endl;
		double UUU=sqrt(sqr(U[jmin])+sqr(V[jmin])+sqr(W[jmin]));
		dx=U[jmin]*dt/npasadas*factorV/UUU*factorDespegaLineas;
		dy=V[jmin]*dt/npasadas*factorV/UUU*factorDespegaLineas;
		dz=W[jmin]*dt/npasadas*factorV/UUU;

		if (ipasadas>npasadas) {
			for (k=maxpasadas-1;k>=0;k--) 
				for (j=0;j<3;j++)
					Particulas[k+1][j][i]=Particulas[k][j][i];
		}

		x=Particulas[0][0][i]+=dx;
		y=Particulas[0][1][i]+=dy;
		z=Particulas[0][2][i]+=dz;

		//		if ( sqrt(sqr(x-2*Dominio_Xmax)+sqr(y)) < Dominio_Rint || x<xmin || x>xmax || y<ymin || y>ymax || z<zmin || z>zmax ) {
		//			PosINI(i);
		//		}
	} 

	for (i=0;i<nParticulas;i++) {
		for (k=0;k<maxpasadas;k++) {
			glBegin(GL_LINES);
			glVertex3d(Particulas[k][0][i],Particulas[k][1][i], Particulas[k][2][i]*FactorZ);
			glVertex3d(Particulas[k+1][0][i],Particulas[k+1][1][i], Particulas[k+1][2][i]*FactorZ);
			glEnd();
		}
		glPushMatrix();
		glTranslated(Particulas[0][0][i],Particulas[0][1][i], Particulas[0][2][i]);
		//		cout<<"esfera"<<endl;

		FuncionesOpenGL::esfera(0.005*Dominio_Xmax,4);
		glPopMatrix();
	}
	if (ipasadas>npasadas) ipasadas=0;


}

void grid3D::DibujaParticula (int i,R3 & origen)
{
	int k;

	//glEnable ( GL_COLOR_MATERIAL );
	//glClear(GL_COLOR_BUFFER_BIT);

	//glDisable(GL_DEPTH_TEST);
	if (GL_immediate_mode==1) {
		glEnable ( GL_COLOR_MATERIAL );
		FuncionesOpenGL::ColorF4(ParticulasZ[i],1);
	}
	for (k=0;k<largoCola;k++) {
		float x1,x2,y1,y2,z1,z2,xm,ym,zm;
		x1=Particulas[k][0][i];
		y1=Particulas[k][1][i];
		z1=Particulas[k][2][i]*FactorZ;
		x2=Particulas[k+1][0][i];
		y2=Particulas[k+1][1][i];
		z2=Particulas[k+1][2][i]*FactorZ;
#if 0
		xm=(x1+x2)/2;
		ym=(y1+y2)/2;
		zm=(z1+z2)/2;
		x1=x1+0.3*(xm-x1);
		y1=y1+0.3*(ym-y1);
		z1=z1+0.3*(zm-z1);
#endif

		if (GL_immediate_mode==1) {
			glBegin(GL_LINES);
			glVertex3d(x1,y1,z1);
			glVertex3d(x2,y2,z2);
			glEnd();
		} else {
			GLfloat_buffer[6*(i*largoCola+k)  ]=x1;
			GLfloat_buffer[6*(i*largoCola+k)+1]=y1;
			GLfloat_buffer[6*(i*largoCola+k)+2]=z1;
			GLfloat_buffer[6*(i*largoCola+k)+3]=x2;
			GLfloat_buffer[6*(i*largoCola+k)+4]=y2;
			GLfloat_buffer[6*(i*largoCola+k)+5]=z2;

		}
	}
	if (MODO_Origen) {
		int iz =ParticulasBloq[i];
		iz=iz-iz/3*3;
		if (GL_immediate_mode==1) {
			FuncionesOpenGL::ColorF4(ParticulasZ[i],1);
			glBegin(GL_LINES);
			glVertex3d(Particulas[0][0][i],Particulas[0][1][i], Particulas[0][2][i]*FactorZ);
			glVertex3d(origen.x,origen.y,origen.z*FactorZ);
			glEnd();
		}
	}


	if (GL_immediate_mode==1) {
		glDisable ( GL_COLOR_MATERIAL );
		FuncionesOpenGL::ColorF4(ParticulasZ[i],0);
		//FuncionesOpenGL::esfera(Particulas[0][0][i],Particulas[0][1][i], Particulas[0][2][i]*FactorZ,0.0012*xmax,3,9);
		FuncionesOpenGL::cono(Particulas[0][0][i],Particulas[0][1][i], Particulas[0][2][i]*FactorZ,Particulas[1][0][i],Particulas[1][1][i], Particulas[1][2][i]*FactorZ,200*Dominio_Xmax,5);
#if 0
		for (k=0;k<largoCola;k++) {
			float x1,x2,y1,y2,z1,z2,xm,ym,zm;
			x1=Particulas[k+1][0][i];
			y1=Particulas[k+1][1][i];
			z1=Particulas[k+1][2][i]*FactorZ;
			FuncionesOpenGL::esfera(x1,y1,z1,0.0002*xmax,2,5);
		}
#endif
	}
}

int grid3D::EnCualTriprisma(float px,float py,float pz,int tri0)
{
	int PinDominio=0,pj,pjmin,pjj,ipj;
	float pd2min=1e20,pd2;
	tri0=tri0-tri0%3;
	for (ipj=0;ipj<nTriPrisma3D;ipj+=3) {
		pj=ipj;
		if (ipj==0) pj=tri0;
		if (ipj==tri0) pj=0;
		float pc=(v3D[TriPrisma3D[pj].iv[1]].x-v3D[TriPrisma3D[pj].iv[0]].x)*(py-v3D[TriPrisma3D[pj].iv[0]].y)
				-(v3D[TriPrisma3D[pj].iv[1]].y-v3D[TriPrisma3D[pj].iv[0]].y)*(px-v3D[TriPrisma3D[pj].iv[0]].x);
		if (pc<0) continue;
		pc=(v3D[TriPrisma3D[pj].iv[2]].x-v3D[TriPrisma3D[pj].iv[1]].x)*(py-v3D[TriPrisma3D[pj].iv[1]].y)
				-(v3D[TriPrisma3D[pj].iv[2]].y-v3D[TriPrisma3D[pj].iv[1]].y)*(px-v3D[TriPrisma3D[pj].iv[1]].x);
		if (pc<0) continue;
		pc=(v3D[TriPrisma3D[pj].iv[0]].x-v3D[TriPrisma3D[pj].iv[2]].x)*(py-v3D[TriPrisma3D[pj].iv[2]].y)
				-(v3D[TriPrisma3D[pj].iv[0]].y-v3D[TriPrisma3D[pj].iv[2]].y)*(px-v3D[TriPrisma3D[pj].iv[2]].x);
		if (pc<0) continue;

//						cout<<"pj="<<pj<<endl;
//						printf("p =[%.2f %.2f]",px,py);cout<<endl;
//						printf("V0=[%.2f %.2f]",v3D[TriPrisma3D[pj].iv[0]].x,v3D[TriPrisma3D[pj].iv[0]].y);cout<<endl;
//						printf("V1=[%.2f %.2f]",v3D[TriPrisma3D[pj].iv[1]].x,v3D[TriPrisma3D[pj].iv[1]].y);cout<<endl;
//						printf("V2=[%.2f %.2f]",v3D[TriPrisma3D[pj].iv[2]].x,v3D[TriPrisma3D[pj].iv[2]].y);cout<<endl;


		for (pjj=0;pjj<3;pjj++) {
			pd2=sqr(px-TriPrisma3D[pj+pjj].centro.x)+sqr(py-TriPrisma3D[pj+pjj].centro.y)+sqr(pz-TriPrisma3D[pj+pjj].centro.z);
			if (pd2<pd2min) {
				pd2min=pd2;
				pjmin=pjj;
			}
		}
		if (pjmin==0) {
			float pp=Cara[TriPrisma3D[pj].icara[0]].normalCara.x*(px-v3D[TriPrisma3D[pj].iv[0]].x)+
					Cara[TriPrisma3D[pj].icara[0]].normalCara.y*(py-v3D[TriPrisma3D[pj].iv[0]].y)+
					Cara[TriPrisma3D[pj].icara[0]].normalCara.z*(pz-v3D[TriPrisma3D[pj].iv[0]].z);
			if (pp<=0) PinDominio=1;
		}
		if (pjmin==1) PinDominio=1;
		if (pjmin==2) {
			float pp=Cara[TriPrisma3D[pj+2].icara[1]].normalCara.x*(px-v3D[TriPrisma3D[pj+2].iv[3]].x)+
					Cara[TriPrisma3D[pj+2].icara[1]].normalCara.y*(py-v3D[TriPrisma3D[pj+2].iv[3]].y)+
					Cara[TriPrisma3D[pj+2].icara[1]].normalCara.z*(pz-v3D[TriPrisma3D[pj+2].iv[3]].z);
			if (pp<=0) PinDominio=1;
		}
		//PinDominio=1;
		pjmin+=pj;
		break;
	}
	if (PinDominio==0) pjmin=-1;
	return(pjmin);
}


int grid3D::EnCualTriprismaXY(float px,float py,int tri0)
{
	int PinDominio=0,pj,pjmin,pjj,ipj;
	float pd2min=1e20,pd2;
	tri0=tri0-tri0%3;
	for (ipj=0;ipj<nTriPrisma3D;ipj+=3) {
		pj=ipj;
		if (ipj==0) pj=tri0;
		if (ipj==tri0) pj=0;
		float pc=(v3D[TriPrisma3D[pj].iv[1]].x-v3D[TriPrisma3D[pj].iv[0]].x)*(py-v3D[TriPrisma3D[pj].iv[0]].y)
				-(v3D[TriPrisma3D[pj].iv[1]].y-v3D[TriPrisma3D[pj].iv[0]].y)*(px-v3D[TriPrisma3D[pj].iv[0]].x);
		if (pc<0) continue;
		pc=(v3D[TriPrisma3D[pj].iv[2]].x-v3D[TriPrisma3D[pj].iv[1]].x)*(py-v3D[TriPrisma3D[pj].iv[1]].y)
				-(v3D[TriPrisma3D[pj].iv[2]].y-v3D[TriPrisma3D[pj].iv[1]].y)*(px-v3D[TriPrisma3D[pj].iv[1]].x);
		if (pc<0) continue;
		pc=(v3D[TriPrisma3D[pj].iv[0]].x-v3D[TriPrisma3D[pj].iv[2]].x)*(py-v3D[TriPrisma3D[pj].iv[2]].y)
				-(v3D[TriPrisma3D[pj].iv[0]].y-v3D[TriPrisma3D[pj].iv[2]].y)*(px-v3D[TriPrisma3D[pj].iv[2]].x);
		if (pc<0) continue;

		return(pj);

	}
	return(-1);
}


void grid3D::drawParticulas_TriPrisma()
{
	//	cout<<"grid3D::drawVelGL"<<"primerdrawVelGL="<<primerdrawVelGL<<"nParticulas="<<nParticulas<<endl;
	static double dt,dtCola;
	static int ipasadas=0;
	int i,j,k;
	double d2,d2min,x,y,z,dx,dy,dz,t;
	if (primerdrawVelGL) {
		int oldsize=Particulas[0][0].size();
		ParticulasZ.resize(nParticulas);
		ParticulasZlambda.resize(nParticulas);
		ParticulaEsAleatoria.resize(nParticulas);
		ParticulasBloq.resize(nParticulas);
		for (k=0;k<=maxpasadas;k++) {
			for (j=0;j<3;j++) {
				Particulas[k][j].resize(nParticulas);
			}
		}
		for (j=0;j<3;j++) {
			Particulas0[j].resize(nParticulas);
		}
		for (i=oldsize;i<nParticulas;i++) {
			ParticulaEsAleatoria[i]=true;
			Particulas_Init(i);
		}


		GLfloat_buffer = new float[6*maxpasadas*nParticulas];
	}
	dt=Tsimulacion-TsimulacionP;
	dtCola=Tsimulacion-TColaP;
	primerdrawVelGL=0;
	if (!MODO_Pausa) {

		ipasadas++;

#ifdef __APPLE__
		dispatch_queue_t c_queue = dispatch_queue_create("myConcurrentQueue",
				DISPATCH_QUEUE_CONCURRENT);
		dispatch_apply(nParticulas, c_queue, ^(size_t i)
#else
#pragma omp parallel for num_threads(GL_threads)
				for (i=0;i<nParticulas;i++)
#endif
				{
		        //cout << "Got " << omp_get_num_threads() << " threads" << endl;
					int pj,pjj,pk,pjmin,PinDominio;
					float pd2min,pd2,px,py,pz,pdx,pdy,pdz;
					px=Particulas[0][0][i];
					py=Particulas[0][1][i];
					pz=Particulas[0][2][i];
					pd2min=1e10;


					pjmin=EnCualTriprisma(px,py,pz,ParticulasBloq[i]);

					if(DBG>1) cout<<"grid3D::drawParticulas_TriPrisma(): 3470"<<endl;
					if ( pjmin<0 ) {
						Particulas_Init(i);
						px=Particulas[0][0][i];
						py=Particulas[0][1][i];
						pz=Particulas[0][2][i];
						pjmin=EnCualTriprisma(px,py,pz,0);
						if (pjmin<0) {
							if(DBG>1) cout<<"pjmin<0: "<<"particula "<<i<<endl;
							if (DBG>1)	cout<<"xyz=["<<px<<","<<py<<","<<pz<<endl;
							pjmin=EnCualTriprismaXY(px, py, 0);
							if (pjmin<0) {
								cout<<"error grave 3085"<<endl;
								cout<<"particula "<<i<<endl;
								cout<<"xyz=["<<px<<","<<py<<","<<pz<<endl;
								exit(0);
							}
							if (DBG>1) cout <<"pjmin (ok)="<<pjmin<<endl;

							R3 ABxAC,AB,AC,AP;

							ABxAC=Cara[TriPrisma3D[pjmin].icara[0]].normalCara;
							AP.x=px-v3D[TriPrisma3D[pjmin].iv[0]].x;
							AP.y=py-v3D[TriPrisma3D[pjmin].iv[0]].y;
							AP.z=0 -v3D[TriPrisma3D[pjmin].iv[0]].z;

							//Ecuacion: AP . (AB x AC)=0  <==>  [(px,py,0)-A+(0,0,pz)] . ABxAC=0
							float pzmin=-ppunto(AP,ABxAC)/ABxAC.z;

							//Tapa superior
							ABxAC=Cara[TriPrisma3D[pjmin+2].icara[1]].normalCara;
							AP.x=px-v3D[TriPrisma3D[pjmin+2].iv[3]].x;
							AP.y=py-v3D[TriPrisma3D[pjmin+2].iv[3]].y;
							AP.z=0 -v3D[TriPrisma3D[pjmin+2].iv[3]].z;

							//Ecuacion: AP . (AB x AC)=0  <==>  [(px,py,0)-A+(0,0,pz)] . ABxAC=0
							float pzmax=-ppunto(AP,ABxAC)/ABxAC.z;
							pz=pzmin+(pzmax-pzmin)*ParticulasZlambda[i];
							if (DBG) cout <<"pzmin="<<pzmin<<" pz="<<pz<<" pzmax="<<pzmax<<" ParticulasZlambda[i]="<<ParticulasZlambda[i]<<endl;
							pjmin=EnCualTriprisma(px,py,pz,pjmin);
							if(DBG) cout <<"pjmin="<<pjmin<<endl;
							if (pjmin<0) {
								cout<<"error grave 3115"<<endl;
								cout <<"pzmin="<<pzmin<<" pz="<<pz<<" pzmax="<<pzmax<<" ParticulasZlambda[i]="<<ParticulasZlambda[i]<<endl;

//								exit(0);
							}

						}
					}
					if(DBG>1) cout<<"grid3D::drawParticulas_TriPrisma(): 3076"<<endl;
					 {
						//cout<<"factorV="<<factorV<<endl;
						double UU,VV,WW,UC;
						ParticulasBloq[i]=pjmin;
						UU=U[step][pjmin]*(1-stepf)+U[step+1][pjmin]*stepf;
						VV=V[step][pjmin]*(1-stepf)+V[step+1][pjmin]*stepf;
						WW=W[step][pjmin]*(1-stepf)+W[step+1][pjmin]*stepf;
						UC=sqrt(sqr(UU)+sqr(VV)+sqr(WW));


						ParticulasZ[i]=sqrt(UC/FactorVel);

						pdx=UU*dt;
						pdy=VV*dt;
						pdz=WW*dt;


						if (dtCola>=1000) {
							for (pk=largoCola-1;pk>=0;pk--)
								for (pj=0;pj<3;pj++)
									Particulas[pk+1][pj][i]=Particulas[pk][pj][i];
						} else {
							pk=largoCola-1;
							float t=dt/1000;
							for (pj=0;pj<3;pj++)
								Particulas[pk+1][pj][i]=Particulas[pk+1][pj][i]*(1-t)+t*Particulas[pk][pj][i];
						}

						px=Particulas[0][0][i]+=pdx;
						py=Particulas[0][1][i]+=pdy;
						pz=Particulas[0][2][i]+=pdz;
					}
				}
#ifdef __APPLE__
		);
#endif
	}
	if (dtCola>=1000) {
		TColaP=Tsimulacion;
	}

	if(GL_immediate_mode !=1) {
		#pragma omp parallel for num_threads(GL_threads)
		for (i=0;i<nParticulas;i++) {
			DibujaParticula (i,TriPrisma3D[ParticulasBloq[i]].centro);
		}
	} else {

		for (i=0;i<nParticulas;i++) {
			DibujaParticula (i,TriPrisma3D[ParticulasBloq[i]].centro);
		}
	}



	if (GL_immediate_mode==2) {

		glEnable ( GL_COLOR_MATERIAL );
		glColor3f(0,0,1);
		glBegin(GL_LINES);
		for (i=0;i<6*nParticulas*largoCola;i+=3) {
			glVertex3f(GLfloat_buffer[i],GLfloat_buffer[i+1],GLfloat_buffer[i+2]);

		}
		glEnd();
	}

	glDisable ( GL_COLOR_MATERIAL );
	if (ipasadas>npasadas) ipasadas=0;


}


void grid3D::drawVelGL2(vector<double> UU,vector<double> VV,vector<double> WW)
{
	double x,y,z;
	int i;
	glPushAttrib( GL_LIGHTING_BIT );
	glDisable( GL_LIGHTING );

	for (i=0;i<nH3D;i++) {
		x=h3D[i].centro.x;
		y=h3D[i].centro.y;
		z=h3D[i].centro.z;

		glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3d(x,y,z*FactorZ);
		glVertex3d(x+UU[i]*factorV,y +VV[i]*factorV,(z+WW[i]*factorV)*FactorZ);
		glEnd();
	} 
	glPopAttrib();


}


void grid3D::Voronoi_Draw_i(int i) {
	int j,k,ii,iimax;
	static int xxip=0;
	double xg,yg,zg,nnn;
	double xg2,yg2,zg2;
	double xcentro,ycentro,zcentro;
	GLdouble winX1,winY1,winZ,winX2,winY2,winX3,winY3,nx,ny,nz;

	if (imprimir) cout<<", Voronoi_Draw_i(i="<<i<<")"<<endl;

	for (k=0; k<VolFinito[i].Poligono.size(); k++) {
		//if (imprimir) cout<<", k="<<k<<" de "<<VolFinito[i].Poligono.size()<<endl;
		xg=VolFinito[i].Poligono[k].centro.x;
		yg=VolFinito[i].Poligono[k].centro.y;
		zg=VolFinito[i].Poligono[k].centro.z;


		xg2=xg*FactorCercania+(1-FactorCercania)*VolFinito[i].centro.x;
		yg2=yg*FactorCercania+(1-FactorCercania)*VolFinito[i].centro.y;
		zg2=zg*FactorCercania+(1-FactorCercania)*VolFinito[i].centro.z;
		//cout<<"xg="<<xg<<"\tyg="<<yg<<"\tzg="<<zg<<endl;

		if (DibujaSupInf>0 && VolFinito[i].vecino_normal[k].z>0.50) continue;
		if (DibujaSupInf>1 && VolFinito[i].vecino_normal[k].z<-0.50) continue;

		if (MODO_NumeraH){

			FuncionesOpenGL::material(100);

			char *p;
			char ss[100];
			glPushMatrix();

			glTranslatef(xg2,yg2,zg2);

			glMultMatrixf((GLfloat *)MatrizRotacionGlobalINV);
			glScalef(NumEscala,NumEscala,NumEscala);
			float y0=1.0/Escala,dy=1.7/Escala;
			glRasterPos3f(-1.0/Escala, y0-=dy ,0);

			if (VolFinito[i].tipo_vecino[k]==ES_CARA || VolFinito[i].tipo_vecino[k]==ES_CARA_L2)
				sprintf(ss,"h%d-p%d-C%d",i,k,VolFinito[i].vecino[k]);
			else
				sprintf(ss,"h%d-p%d-b%d",i,k,VolFinito[i].vecino[k]);
			for(p = ss; *p; p++) {
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
			}

			glPopMatrix();
		}

		//				if (VolFinito[i].dibujado[k] == 1) continue;
		vector<R3> *Pto;
		Pto= &(VolFinito[i].Poligono[k].punto);
		nx=VolFinito[i].Poligono[k].normal.x; ny=VolFinito[i].Poligono[k].normal.y;nz=VolFinito[i].Poligono[k].normal.z;
		if (Pto->size() >2) {
			FuncionesOpenGL::World2Win( (*Pto)[0].x , (*Pto)[0].y , (*Pto)[0].z,&winX1,&winY1,&winZ);
			FuncionesOpenGL::World2Win( (*Pto)[Pto->size()/2].x , (*Pto)[Pto->size()/2].y ,  (*Pto)[Pto->size()/2].z,&winX2,&winY2,&winZ);
			FuncionesOpenGL::World2Win( (*Pto)[Pto->size()-1].x , (*Pto)[Pto->size()-1].y ,
					(*Pto)[Pto->size()-1].z,&winX3,&winY3,&winZ);
			if ((winX2-winX1)*(winY3-winY1)-(winY2-winY1)*(winX3-winX1) <0 ){
				nx = -nx; ny = -ny; nz = -nz; ;
			}
		}
		if (Dibuja3puntos && xxi==i) {
			FuncionesOpenGL::material(2);	}
		else  {FuncionesOpenGL::material(3);}
		xcentro=0;ycentro=0;zcentro=0;
		for (j=0; j<Pto->size(); j++) {
			xcentro+=(*Pto)[  j].x;
			ycentro+=(*Pto)[  j].y;
			zcentro+=(*Pto)[  j].z;
			if (j>1) {
				glBegin(GL_TRIANGLES );
				glNormal3d(nx , ny , nz *FactorZ);
				glVertex3d( (*Pto)[  0].x, (*Pto)[  0].y, (*Pto)[0].z*FactorZ);
				glVertex3d( (*Pto)[j-1].x, (*Pto)[j-1].y, (*Pto)[j-1].z*FactorZ);
				glVertex3d( (*Pto)[  j].x, (*Pto)[  j].y, (*Pto)[j].z*FactorZ);
				glEnd();
			}

		}
		xcentro/=Pto->size();
		ycentro/=Pto->size();
		zcentro/=Pto->size();
		if(ModoDibujaNormales) {
			glPushAttrib( GL_LIGHTING_BIT );
			glDisable( GL_LIGHTING );

			glBegin(GL_LINES);
			glColor3f(1,0,0);
			glVertex3d(xg,yg,zg*FactorZ);
			nnn=sqrt(sqr(nx)+sqr(ny)+sqr(nz));
			glVertex3d(xg+nx/nnn/10,yg+ny/nnn/10,(zg+nz/nnn/10)*FactorZ);
			glEnd();
			glPopAttrib();
		}

		//if (imprimir) cout<<", 2:k="<<k<<endl;
		//Dibuja linea entre centros
		{
			glPushAttrib( GL_LIGHTING_BIT );
			glDisable( GL_LIGHTING );

			glBegin(GL_LINES);
			if (VolFinito[i].tipo_vecino[k]==ES_CARA || VolFinito[i].tipo_vecino[k]==ES_CARA_L2 ) {
				glColor3f(0,1,0);
				glVertex3d(xcentro,ycentro,zcentro*FactorZ);
				glVertex3d(VolFinito[i].vecino_centro_caraoriginal[k].x,VolFinito[i].vecino_centro_caraoriginal[k].y,VolFinito[i].vecino_centro_caraoriginal[k].z*FactorZ);
			}
			glColor3f(0,0,1);
			glVertex3d(xcentro,ycentro,zcentro*FactorZ);
			glVertex3d(xg,yg,zg*FactorZ);
			glColor3f(1,0,0);
			glVertex3d(xg,yg,zg*FactorZ);
			nnn=sqrt(sqr(nx)+sqr(ny)+sqr(nz));
			glVertex3d(VolFinito[i].vecino_centro[k].x,VolFinito[i].vecino_centro[k].y,VolFinito[i].vecino_centro[k].z*FactorZ);
			glEnd();
			glPopAttrib();
		}


		//if (imprimir) cout<<", 3:k="<<k<<endl;
		VolFinito[i].dibujado[k]=1;
		if (VolFinito[i].tipo_vecino[k]==ES_BLOQUE) {
			for (j=0; j<VolFinito[ VolFinito[i].tipo_vecino[k] ].dibujado.size(); j++) {
				if (   VolFinito[ VolFinito[i].vecino[k] ].tipo_vecino[j] ==ES_BLOQUE
						&& VolFinito[ VolFinito[i].vecino[k] ].vecino[j] == i) {

					VolFinito[ VolFinito[i].vecino[k] ].dibujado[j]=1;
					break;
				}

			}
		}


		//if (imprimir) cout<<", 4:k="<<k<<endl;
	}

}


void grid3D::TriPrisma_Draw_i(int i) {
	int j,k,ii,iimax;

	if (imprimir)	cout<<", TriPrisma_Draw_i(i="<<i<<")"<<endl;

	int tmp=ModoDibujaInterior;
	int tmp2=ModoDibujaFrontera;
	ModoDibujaInterior=1;
	ModoDibujaFrontera=1;
	for (k=0; k<5; k++) {

		if (DibujaSupInf>1 && k==0) continue;
		if (DibujaSupInf>0 && k==1) continue;
		Cara[TriPrisma3D[i].icara[k]].drawGL();


	}
	ModoDibujaInterior=tmp;
	ModoDibujaFrontera=tmp2;
	for (j=i-i%3;j<i-(i%3)+3;j++) {
		if (DBG) cout<<"j="<<j<<endl;
		FuncionesOpenGL::ColorF3(0.5*(j%3), 0);

		TriPrisma3D[j].DrawCentro();
	}

}


void grid3D::drawVoronoi()
{
	int i,j,k,ii,iimax;
	static int xxip=0;
	double xg,yg,zg,nnn;
	double xg2,yg2,zg2;
	GLdouble winX1,winY1,winZ,winX2,winY2,winX3,winY3,nx,ny,nz;

	FuncionesOpenGL::modelview_calculado=false;	
	double lambdaP=FactorAchicaV;

	glEnable(GL_NORMALIZE);
	if (DBG) cout<<"grid3D::drawVoronoi(): QuienGeneraPoligonos="<<QuienGeneraPoligonos<<" ,nVolFinito="<<nVolFinito<<endl;

	if (QuienGeneraPoligonos==2) {
		for (i=0;i<nVolFinito;i++) {
			VolFinito[i].dibujado.assign( VolFinito[i].Poligono.size(),0);
		}		

		iimax=nVolFinito;
		if (ModoDibujaAlgunos) iimax=CualesBloquesDibuja.size();

		for (ii=0;ii<iimax;ii++) {
			i=ii;
			if (ModoDibujaAlgunos) i=CualesBloquesDibuja[ii];


			{
			for (k=0; k<VolFinito[i].Poligono.size(); k++) {
				xg=VolFinito[i].Poligono[k].centro.x;
				yg=VolFinito[i].Poligono[k].centro.y;
				zg=VolFinito[i].Poligono[k].centro.z;


				xg2=xg*FactorCercania+(1-FactorCercania)*VolFinito[i].centro.x;
				yg2=yg*FactorCercania+(1-FactorCercania)*VolFinito[i].centro.y;
				zg2=zg*FactorCercania+(1-FactorCercania)*VolFinito[i].centro.z;
				//cout<<"xg="<<xg<<"\tyg="<<yg<<"\tzg="<<zg<<endl;


				if (DibujaSupInf>0 && VolFinito[i].vecino_normal[k].z>0.50) continue;
				if (DibujaSupInf>1 && VolFinito[i].vecino_normal[k].z<-0.50) continue;

				if (MODO_NumeraH){

					FuncionesOpenGL::material(100);

					char *p;
					char ss[100];
					glPushMatrix();

					glTranslatef(xg2,yg2,zg2);

					glMultMatrixf((GLfloat *)MatrizRotacionGlobalINV);
					glScalef(NumEscala,NumEscala,NumEscala);
					float y0=1.0/Escala,dy=1.7/Escala;
					glRasterPos3f(-1.0/Escala, y0-=dy ,0);

					if (VolFinito[i].tipo_vecino[k]==ES_CARA || VolFinito[i].tipo_vecino[k]==ES_CARA_L2)
						sprintf(ss,"h%d-p%d-C%d",i,k,VolFinito[i].vecino[k]);
					else
						sprintf(ss,"h%d-p%d-b%d",i,k,VolFinito[i].vecino[k]);
					for(p = ss; *p; p++) {
						glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
					}

					glPopMatrix();
				}

				//				if (VolFinito[i].dibujado[k] == 1) continue;
				vector<R3> *Pto;
				Pto= &(VolFinito[i].Poligono[k].punto);
				nx=VolFinito[i].Poligono[k].normal.x; ny=VolFinito[i].Poligono[k].normal.y;nz=VolFinito[i].Poligono[k].normal.z;
				if (Pto->size() >2) {
					FuncionesOpenGL::World2Win( (*Pto)[0].x , (*Pto)[0].y , (*Pto)[0].z,&winX1,&winY1,&winZ);
					FuncionesOpenGL::World2Win( (*Pto)[Pto->size()/2].x , (*Pto)[Pto->size()/2].y ,  (*Pto)[Pto->size()/2].z,&winX2,&winY2,&winZ);
					FuncionesOpenGL::World2Win( (*Pto)[Pto->size()-1].x , (*Pto)[Pto->size()-1].y , 
							(*Pto)[Pto->size()-1].z,&winX3,&winY3,&winZ);
					if ((winX2-winX1)*(winY3-winY1)-(winY2-winY1)*(winX3-winX1) <0 ){ 
						nx = -nx; ny = -ny; nz = -nz; ;
					}
				}
				if (Dibuja3puntos && xxi==i) {
					FuncionesOpenGL::material(2);	}
				else  {FuncionesOpenGL::material(3);}
				for (j=2; j<Pto->size(); j++) {
					glBegin(GL_TRIANGLES );
					glNormal3d(nx , ny , nz );
					glVertex3d( ((*Pto)[  0].x)*(1-lambdaP)+xg*lambdaP, ((*Pto)[  0].y)*(1-lambdaP)+yg*lambdaP, (((*Pto)[  0].z)*(1-lambdaP)+zg*lambdaP)*FactorZ);
					glVertex3d( ((*Pto)[j-1].x)*(1-lambdaP)+xg*lambdaP, ((*Pto)[j-1].y)*(1-lambdaP)+yg*lambdaP, (((*Pto)[j-1].z)*(1-lambdaP)+zg*lambdaP)*FactorZ);
					glVertex3d( ((*Pto)[  j].x)*(1-lambdaP)+xg*lambdaP, ((*Pto)[  j].y)*(1-lambdaP)+yg*lambdaP, (((*Pto)[  j].z)*(1-lambdaP)+zg*lambdaP)*FactorZ);
					glEnd();

				}
				if(ModoDibujaNormales) {
					glPushAttrib( GL_LIGHTING_BIT );
					glDisable( GL_LIGHTING );

					glBegin(GL_LINES);
					glColor3f(1,0,0);
					glVertex3d(xg,yg,zg*FactorZ);
					nnn=sqrt(sqr(nx)+sqr(ny)+sqr(nz));
					glVertex3d(xg+nx/nnn/10,yg+ny/nnn/10,(zg+nz/nnn/10)*FactorZ);
					glEnd();
					glPopAttrib();
				}

				VolFinito[i].dibujado[k]=1;
				if (VolFinito[i].tipo_vecino[k]==ES_BLOQUE) {
					for (j=0; j<VolFinito[ VolFinito[i].tipo_vecino[k] ].dibujado.size(); j++) {
						if (   VolFinito[ VolFinito[i].vecino[k] ].tipo_vecino[j] ==ES_BLOQUE
								&& VolFinito[ VolFinito[i].vecino[k] ].vecino[j] == i) {

							VolFinito[ VolFinito[i].vecino[k] ].dibujado[j]=1;
							break;
						}

					}
				}


			}
			}


		}
		if (Dibuja3puntos) {
			glTranslatef(xx0,yy0,zz0*FactorZ);
			FuncionesOpenGL::material(1);   FuncionesOpenGL::esfera(0.02,3);
			glTranslatef(xx1-xx0,yy1-yy0,(zz1-zz0)*FactorZ);
			FuncionesOpenGL::material(2);   FuncionesOpenGL::esfera(0.02,3);
			glTranslatef(xx2-xx1,yy2-yy1,(zz2-zz1)*FactorZ);
			FuncionesOpenGL::material(2);   FuncionesOpenGL::esfera(0.02,3);
			glTranslatef(-xx2,-yy2,-zz2*FactorZ);
		}
	}
}


void grid3D::minmax()
{	
	int i;
	double x,y,z;
	xmin=xmax=v3D[0].x;
	ymin=ymax=v3D[0].y;
	zmin=zmax=v3D[0].z;
	for (i=1;i<nV3D;i++) {
		x=v3D[i].x;
		y=v3D[i].y;
		z=v3D[i].z;
		if (x < xmin) xmin=x;
		if (x > xmax) xmax=x;
		if (y < ymin) ymin=y;
		if (y > ymax) ymax=y;
		if (z < zmin) zmin=z;
		if (z > zmax) zmax=z;
	}
}

void Cara3D::drawGL()
{
//	cout<<"Cara3D::drawGL()"<<endl;
	if (ModoDibujaAlgunos && nRandom>(double)Algunos_Porcentaje/100) {
//		cout<<"return"<<endl;
		return;
	}
//	cout<<"nRandom="<<nRandom<<endl;
	if (Modo_DibujaCentroCaras||MODO_NumeraH) {
		glTranslatef(centro.x,centro.y,centro.z);
		FuncionesOpenGL::material(1);   FuncionesOpenGL::esfera(0.02/Escala,3);
		{
			if (MODO_NumeraH){
				char *p;
				char ss[100];
				FuncionesOpenGL::material(100);
				glPushMatrix();
				glMultMatrixf((GLfloat *)MatrizRotacionGlobalINV);
				glScalef(NumEscala,NumEscala,NumEscala);
				float y0=0.5/Escala;
				glRasterPos3f(y0, y0 ,0);

				sprintf(ss,"C%d-B%d",no,iBC);
				for(p = ss; *p; p++) {
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
				}

				glPopMatrix();
			}


		}
		glTranslatef(-centro.x,-centro.y,-centro.z);
	}
	if (ModoDibujaFrontera && nVolumenes ==1) {
		//		FuncionesOpenGL::material(iBC+10);
		if (iBC == IBC_SUP) {
			//FuncionesOpenGL::material(1);
			if (FlagCaraSuperiorTransparente==1) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			FuncionesOpenGL::material(3);
			}
			draw_caraGL();
			if (FlagCaraSuperiorTransparente==1) {
				glDisable(GL_BLEND);
			}
		} else {
		draw_caraGL();
		}
	}
	if (ModoDibujaInterior && nVolumenes >1) {
		FuncionesOpenGL::material(2);
		draw_caraGL();
		if (0*Modo_DibujaCentroCaras) {
			glTranslatef(centro.x,centro.y,centro.z);
			FuncionesOpenGL::material(1);   FuncionesOpenGL::esfera(0.04,3);
			glTranslatef(-centro.x,-centro.y,-centro.z);
		}
	}
}


void Cara3D::draw_caraGL() {


	int li,signo;
	double x[4],y[4],z[4],v[3],xg,yg,zg,nx,ny,nz,nxx,nyy,nzz,nnn;
	xg=0;yg=0;zg=0;

	//	cout <<"nvC="<<nvC<<endl;
	for (li=0;li<nvCara;li++) {
		x[li]=papa->v3D[iv[li]].x;
		y[li]=papa->v3D[iv[li]].y;
		z[li]=papa->v3D[iv[li]].z*FactorZ;
		//xg+=x[li]/nvCara;		yg+=y[li]/nvCara;		zg+=z[li]/nvCara;
	}

	xg= centro.x;
	yg= centro.y;
	zg= centro.z*FactorZ;

	for (li=0;li<nvCara;li++) {
		x[li]+=(xg-x[li])*FactorAchica;
		y[li]+=(yg-y[li])*FactorAchica;
		z[li]+=(zg-z[li])*FactorAchica;
	}

#if 1==0
	// Si funciona
	if (nvCara>3) {
		nxx=nx=(y[2]-y[0])*(z[3]-z[1])-(z[2]-z[0])*(y[3]-y[1]);
		nyy=ny=(z[2]-z[0])*(x[3]-x[1])-(x[2]-x[0])*(z[3]-z[1]);
		nzz=nz=(x[2]-x[0])*(y[3]-y[1])-(y[2]-y[0])*(x[3]-x[1]);
	}else {

		nxx=nx=(y[1]-y[0])*(z[2]-z[0])-(z[1]-z[0])*(y[2]-y[0]);
		nyy=ny=(z[1]-z[0])*(x[2]-x[0])-(x[1]-x[0])*(z[2]-z[0]);
		nzz=nz=(x[1]-x[0])*(y[2]-y[0])-(y[1]-y[0])*(x[2]-x[0]);
	}
	nnn=sqrt(sqr(nxx)+sqr(nyy)+sqr(nzz));
	nxx/=nnn;
	nyy/=nnn;
	nzz/=nnn;
#endif

	//Version que tambien funciona pero más rápido!!
	nxx=normalCara.x;
	nyy=normalCara.y;
	nzz=normalCara.z/FactorZ;
	nnn=sqrt(sqr(nxx)+sqr(nyy)+sqr(nzz));
	nxx/=nnn;
	nyy/=nnn;
	nzz/=nnn;


	ZGlobal(v);


	FuncionesOpenGL::modelview_calculado=false;
	FuncionesOpenGL::World2Win(x[0],y[0],z[0],&winX1,&winY1,&winZ1);
	FuncionesOpenGL::World2Win(x[1],y[1],z[1],&winX2,&winY2,&winZ2);
	FuncionesOpenGL::World2Win(x[2],y[2],z[2],&winX3,&winY3,&winZ3);
	signo=1;
	signo2=1;
	if ((winX2-winX1)*(winY3-winY1)-(winY2-winY1)*(winX3-winX1) <0 ){
		signo2=-1;
	}

	if (this->iBC==IBC_SUP)	signo2=1;

	glEnable(GL_NORMALIZE);

	//glTexCoord2d(0.0,0.0); glVertex2d(-1.0,-1.0);
	//glTexCoord2d(1.0,0.0); glVertex2d(+1.0,-1.0);
	//glTexCoord2d(1.0,1.0); glVertex2d(+1.0,+1.0);


	if (this->iBC == IBC_SUP) {
//		glPushAttrib( GL_LIGHTING_BIT );
//		glDisable( GL_LIGHTING );
	}

	if (nvCara==4)	glBegin(GL_QUADS);
	else glBegin(GL_TRIANGLES);
	for (li=0;li<nvCara;li++) {
		if (FactorSuavidad>0 & papa->v3D[iv[li]].normalVetex.L>0.1) {
			nx=nxx*(1-FactorSuavidad)+FactorSuavidad*papa->v3D[iv[li]].normalVetex.x;
			ny=nyy*(1-FactorSuavidad)+FactorSuavidad*papa->v3D[iv[li]].normalVetex.y;
			nz=nzz*(1-FactorSuavidad)+FactorSuavidad*papa->v3D[iv[li]].normalVetex.z/FactorZ;

		} else {
			if (x[li]<xg)
				nx=signo*nxx+(x[li]-xg)*((x[li]-xg))*FactorNormales;
			else
				nx=signo*nxx-(x[li]-xg)*((x[li]-xg))*FactorNormales;
			if (y[li]<yg)
				ny=signo*nyy+(y[li]-yg)*((y[li]-yg))*FactorNormales;
			else
				ny=signo*nyy-(y[li]-yg)*((y[li]-yg))*FactorNormales;
			if  (z[li]<zg)
				nz=signo*nzz+(z[li]-zg)*((z[li]-zg))*FactorNormales;
			else
				nz=signo*nzz-(z[li]-zg)*((z[li]-zg))*FactorNormales;

		}

		//glNormal3d(nxx,nyy,nzz);

		//if ( nx*v[0]+ny*v[1]+nz*v[2]<0) 	signo2=-1;
		if (this->iBC == IBC_SUP ) {
			glTexCoord2d(1*x[li]/papa->xmax, 1*y[li]/papa->ymax);
		}
		if (this->iBC == IBC_INF) {
			glTexCoord2d(0.02*z[li]/papa->zmin,10*y[li]/papa->ymax);
		}
		glNormal3d(nx*signo2,ny*signo2,nz*signo2);
		glVertex3d(x[li], y[li],z[li]);
	}
	glEnd();

	if (this->iBC == IBC_SUP) {
	}


	if(ModoDibujaNormales) {
		glPushAttrib( GL_LIGHTING_BIT );
		glDisable( GL_LIGHTING );

		glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3d(xg,yg,zg);
		glVertex3d(xg+nxx/nnn/10,yg+nyy/nnn/10,zg+nzz/nnn/10);
		glEnd();
		glPopAttrib();
	}
	if(FlagDibujaLineas) {
		glPushAttrib( GL_LIGHTING_BIT );
		glDisable( GL_LIGHTING );

		glBegin(GL_LINES);
		glColor3f(1,0,0);
		for (li=0;li<nvCara;li++) {
			glVertex3d(x[li]+factorDespegaLineas*nxx*signo2, y[li]+factorDespegaLineas*nyy*signo2,z[li]+factorDespegaLineas*nzz*signo2);
			if (li==0 ) continue;

			glVertex3d(x[li]+factorDespegaLineas*nxx*signo2, y[li]+factorDespegaLineas*nyy*signo2,z[li]+factorDespegaLineas*nzz*signo2);
		}
		glVertex3d(x[0]+factorDespegaLineas*nxx*signo2, y[0]+factorDespegaLineas*nyy*signo2,z[0]+factorDespegaLineas*nzz*signo2);
		glEnd();


		glPopAttrib();
	}



}

#define Version 1//0:dibuja los cubos, 1:dibuja las caras

void grid3D::drawGL()
{
	//MareaRoja
	int i,ii;
	char s[100];
	if (DBG) cout<<"grid3D::drawGL()"<<endl;

	for(i=0;i<TriPrisma3D.size();i++) {
		TriPrisma3D[i].CentroDibujado=0;
	}
	if (DBG) cout<<"3551"<<endl;
	FuncionesOpenGL::ObtieneMatrices();
#if Version==1
	if (Modo_DibujaCentroBloques) {
		if (ModoDibujaAlgunos) {
			for (ii=0;ii<CualesBloquesDibuja.size();ii++) {
				i=CualesBloquesDibuja[ii];
				glTranslatef(h3D[i].centro.x,h3D[i].centro.y,h3D[i].centro.z*FactorZ);
				FuncionesOpenGL::material(1);   FuncionesOpenGL::esfera(0.01/Escala,3);
				glTranslatef(-h3D[i].centro.x,-h3D[i].centro.y,-h3D[i].centro.z*FactorZ);
			}

		} else {
			//OLD bloques
			for (i=0;i<nH3D;i++) {
				glTranslatef(h3D[i].centro.x,h3D[i].centro.y,h3D[i].centro.z*FactorZ);
				FuncionesOpenGL::material(1);   FuncionesOpenGL::esfera(0.01/Escala,3);
				glTranslatef(-h3D[i].centro.x,-h3D[i].centro.y,-h3D[i].centro.z*FactorZ);
			}
			//New: Triprismas
			for (i=0;i<nTriPrisma3D;i++) {

				//				glTranslatef(TriPrisma3D[i].centro.x,TriPrisma3D[i].centro.y,TriPrisma3D[i].centro.z);
				FuncionesOpenGL::ColorF3(0.5*(i%3), 0);
				//				FuncionesOpenGL::esfera(0.001,3);
				TriPrisma3D[i].DrawCentro();
				//				glTranslatef(-TriPrisma3D[i].centro.x,-TriPrisma3D[i].centro.y,-TriPrisma3D[i].centro.z);
			}
		}
		if (DBG) cout<<"grid3D::drawGL()1600"<<endl;
	}
	if (DBG) cout<<"grid3D::drawGL()1602"
			<<"\t nv3D="<<nV3D
			<<"\t nH3D="<<nH3D
			<<"\t nCaras="<<nCaras
			<<"\t Cara.size()="<<Cara.size()
			<<endl;

	//TODO DrawCaras
	nCaras=Cara.size();
	for (i=0;i<Cara.size();i++)  {
		if (Cara[i].iBC == IBC_SUP)  continue;
		if (Cara[i].iBC == IBC_INF)  continue;
		Cara[i].drawGL();
	}
	if (FlagMuestraCaraInferior==1) {


		if (FlagCaraInferiorTextura==1) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID2);
		}
		for (i=0;i<Cara.size();i++)  {
			if (Cara[i].iBC != IBC_INF )  continue;
			Cara[i].drawGL();
		}

		if (FlagCaraInferiorTextura==1) {
		   glDisable(GL_TEXTURE_2D);
		}
	}
	if (FlagMuestraCaraSuperior==1) {


		if (FlagCaraSuperiorTextura==1) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		for (i=0;i<Cara.size();i++)  {
			if (Cara[i].iBC != IBC_SUP )  continue;
			Cara[i].drawGL();
		}

		if (FlagCaraSuperiorTextura==1) {
		   glDisable(GL_TEXTURE_2D);
		}
	}

#endif

	if (DBG) cout<<"grid3D::drawGL()1600"<<endl;

	if (Modo_DibujaEdges) {
		glPushAttrib( GL_LIGHTING_BIT );
		glDisable( GL_LIGHTING );
		for (i=0;i<nH3D;i++) {
			//	  2------3
			//   /|     /|
			//  6-|----7 |
			//	| |    | |
			//	| 0----|-1
			//	|/     |/
			//  4------5

			h3D[i].draw_edgeGL(6,7);
			h3D[i].draw_edgeGL(3,7);
			h3D[i].draw_edgeGL(5,7);
		}

		glPopAttrib();
	}


	if (DBG) cout<<"grid3D::drawGL()1600"<<endl;

	for (i=0;i<	VolFinitoSelected.size();i++) {
		Voronoi_Draw_i(VolFinitoSelected[i]);
	}
	for (i=0;i<	Selected_Triprisma.size();i++) {
		TriPrisma_Draw_i(Selected_Triprisma[i]);
	}
	imprimir=0;

	if (MODO_NumeraH){

		FuncionesOpenGL::material(100);

		for (i=0;i<nH3D;i++) {
			char *p;
			glPushMatrix();

			glTranslatef(h3D[i].centro.x,h3D[i].centro.y,h3D[i].centro.z);
			//glTranslatef(0,0,.5);


			glMultMatrixf((GLfloat *)MatrizRotacionGlobalINV);
			glScalef(NumEscala,NumEscala,NumEscala);
			float y0=1.0/Escala,dy=1.7/Escala;
			glRasterPos3f(-1.0/Escala, y0-=dy ,0);
			sprintf(s,"%d",i);	
			for(p = s; *p; p++) {
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
			}
			if (MODO_NumeraFF) 	{
				glRasterPos3f(-3/Escala, y0-=dy ,0);
				sprintf(s,"FF=%.3f",PotencialPsi[i]);	
				for(p = s; *p; p++) {
					glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
				}
				glRasterPos3f(-3/Escala, y0-=dy ,0);
				sprintf(s,"U=%.3f",sqrt(sqr(UU[i])+sqr(VV[i])+sqr(WW[i])));	
				for(p = s; *p; p++) {
					glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
				}
				glRasterPos3f(-3/Escala, y0-=dy ,0);
				sprintf(s,"d=%.3f",sqrt(sqr(h3D[i].centro.x)+sqr(h3D[i].centro.y)));	
				for(p = s; *p; p++) {
					glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
				}
				/*
				glRasterPos3f(-3/Escala, y0-=dy ,0);
				sprintf(s,"VV=%.3f",VV[i]);	
				for(p = s; *p; p++) {
					glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
				}
				glRasterPos3f(-3/Escala, y0-=dy ,0);
				sprintf(s,"WW=%.3f",WW[i]);	
				for(p = s; *p; p++) {
					glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *p);
				}
				 */
			}

			//			FuncionesOpenGL::Print(s);
			glPopMatrix();
		}
	}
	if (DBG) cout<<"grid3D::drawGL():END"<<endl;
}

void grid3D::drawGL(vector<double> & F,double minF,double maxF )
{

	int i,ii,iimax;
	char s[100];

	if (DBG) cout <<"grid3D::drawGL(vector<double> F & F,double minF="<<minF<<" ,double maxF="<<maxF<<" )"<<endl;

	glPushAttrib( GL_LIGHTING_BIT );


	if (DBG) cout <<"4274: nCaras="<<nCaras<<" , Cara.size()"<<Cara.size()<<endl;

	iimax=nCaras;
	if (ModoDibujaAlgunos) iimax=CualesCarasDibuja.size();

	for (ii=0;ii<iimax;ii++) {
		i=ii;
		if (ModoDibujaAlgunos) i=CualesCarasDibuja[ii];
		//	  2------3
		//   /|     /|
		//  6-|----7 |
		//	| |    | |
		//	| 0----|-1
		//	|/     |/
		//  4------5

		//

		if (ModoDibujaFrontera && Cara[i].nVolumenes ==1) {
			//FuncionesOpenGL::material(Cara[i].iBC+10);
			if (Cara[i].iBC == IBC_SUP && FlagMuestraCaraSuperior!=1)  continue;
			if (Cara[i].iBC == IBC_INF && FlagMuestraCaraInferior!=1)  continue;

			if (DBG>1) cout <<"4293: i="<<i<<" de "<<iimax<<"   minF="<<minF<<" , maxF="<<maxF<<" , F[0]="<<F[0]<<" , Cara[i].iv[0]="<<Cara[i].iv[0]<<endl;
			Cara[i].draw_caraGL00(F,minF,maxF,Cara[i].iv);
			if (DBG>1) cout <<"4295: minF="<<minF<<" , maxF="<<maxF<<endl;
		}
		if (ModoDibujaInterior && Cara[i].nVolumenes >1) {
			Cara[i].draw_caraGL00(F,minF,maxF,Cara[i].iv);
			if (0*Modo_DibujaCentroCaras) {
				glTranslatef(Cara[i].centro.x,Cara[i].centro.y,Cara[i].centro.z);
				FuncionesOpenGL::material(1);   FuncionesOpenGL::esfera(0.04,3);
				glTranslatef(-Cara[i].centro.x,-Cara[i].centro.y,-Cara[i].centro.z);
			}
		}
	}



	if (Modo_DibujaEdges) {
		for (i=0;i<nH3D;i++) {
			//	  2------3
			//   /|     /|
			//  6-|----7 |
			//	| |    | |
			//	| 0----|-1
			//	|/     |/
			//  4------5

			h3D[i].draw_edgeGL(6,7);
			h3D[i].draw_edgeGL(3,7);
			h3D[i].draw_edgeGL(5,7);
		}
	}

	glPopAttrib();

	if (NumON){

		FuncionesOpenGL::material(100);

		for (i=0;i<nV3D;i++) {
			glPushMatrix();

			glTranslatef(v3D[i].x,v3D[i].y,v3D[i].z);
			glMultMatrixf((GLfloat *)MatrizRotacionGlobalINV);
			glScalef(NumEscala,NumEscala,NumEscala);
			glTranslatef(0,0,.5);
			sprintf(s,"%d",i);
			FuncionesOpenGL::Print(s);
			glPopMatrix();
		}
	}
	if (DBG) cout <<"grid3D::drawGL(vector<double> F):END"<<endl;


}

void grid3D::drawGL(vector<double> & F)
{
	int i,ii,iimax;
	char s[100];
	double minF,maxF;

	if (DBG) cout <<"grid3D::drawGL(vector<double> F)"<<endl;
	maxF=minF=F[0];
	for (i=0;i<nV3D;i++) {
		if (minF>F[i]) minF=F[i];
		if (maxF<F[i]) maxF=F[i];
	}

	if (DBG) cout <<"4267: Fmin,Fmax="<<minF<<" , "<<maxF<<endl;

	drawGL(F,minF,maxF);
	if (DBG) cout <<"grid3D::drawGL(vector<double> F):END"<<endl;

}


void grid3D::cubo(int ix,int iy,int iz,float Lx,float Ly,float Lz)
{
	int i,j,k;
	nH3D=ix*iy*iz;
	nV3D=(ix+1)*(iy+1)*(iz+1);
	v3D.resize(nV3D,Vertex3D());
	h3D.resize(nH3D,Hexa3D());
	for (i=0;i<=ix;i++) {
		for (j=0;j<=iy;j++) {
			for (k=0;k<=iz;k++) {
				if ((i<ix)&&(j<iy)&&(k<iz)) {

					h3D[i*(iy*iz)+j*(iz)+k].papa=this;
					h3D[i*(iy*iz)+j*(iz)+k].no=i*(iy*iz)+j*(iz)+k;
					h3D[i*(iy*iz)+j*(iz)+k].iv[0]=i*(iy+1)*(iz+1)+  j  *(iz+1)+  k;
					h3D[i*(iy*iz)+j*(iz)+k].iv[1]=i*(iy+1)*(iz+1)+(j+1)*(iz+1)+  k;
					h3D[i*(iy*iz)+j*(iz)+k].iv[2]=i*(iy+1)*(iz+1)+  j  *(iz+1)+(k+1);
					h3D[i*(iy*iz)+j*(iz)+k].iv[3]=i*(iy+1)*(iz+1)+(j+1)*(iz+1)+(k+1);
					h3D[i*(iy*iz)+j*(iz)+k].iv[4]=(i+1)*(iy+1)*(iz+1)+  j  *(iz+1)+  k;
					h3D[i*(iy*iz)+j*(iz)+k].iv[5]=(i+1)*(iy+1)*(iz+1)+(j+1)*(iz+1)+  k;
					h3D[i*(iy*iz)+j*(iz)+k].iv[6]=(i+1)*(iy+1)*(iz+1)+  j  *(iz+1)+(k+1);
					h3D[i*(iy*iz)+j*(iz)+k].iv[7]=(i+1)*(iy+1)*(iz+1)+(j+1)*(iz+1)+(k+1);
				}
				v3D[i*(iy+1)*(iz+1)+  j  *(iz+1)+  k].no=i*(iy+1)*(iz+1)+  j  *(iz+1)+  k;
				v3D[i*(iy+1)*(iz+1)+  j  *(iz+1)+  k].papa=this;
				v3D[i*(iy+1)*(iz+1)+  j  *(iz+1)+  k].x=Lx/ix*i;
				v3D[i*(iy+1)*(iz+1)+  j  *(iz+1)+  k].y=Ly/iy*j;
				v3D[i*(iy+1)*(iz+1)+  j  *(iz+1)+  k].z=Lz/iz*k;
			}
		}
	}
}

void grid3D::Junta(grid3D g1,grid3D g2) 
{
	int i,j;
	double DIJ;
	vector<int> i2enUnion(g2.nV3D);
	const double eps=1e-10; 
	v3D=g1.v3D;
	nV3D=g1.nV3D;
	h3D=g1.h3D;
	nH3D=g1.nH3D+g2.nH3D;
	for (i=0;i<g2.nV3D;i++) {
		for (j=0;j<g1.nV3D;j++) {
			DIJ=sqr(g1.v3D[j].x-g2.v3D[i].x)+sqr(g1.v3D[j].y-g2.v3D[i].y)+sqr(g1.v3D[j].z-g2.v3D[i].z);
			if (DIJ<eps) break;
		}
		if (j<g1.nV3D){
			i2enUnion[i]=j;
		} else {
			i2enUnion[i]=nV3D;
			v3D.push_back(g2.v3D[i]);
			nV3D++;
		}
	}
	for (i=0;i<g2.nH3D;i++) {
		h3D.push_back(g2.h3D[i]);
		for (j=0;j<8;j++) {
			h3D[g1.nH3D+i].iv[j]=i2enUnion[g2.h3D[i].iv[j]];
		}		
	}
	for (i=0;i<nV3D;i++) {
		v3D[i].no=i;
		v3D[i].papa=this;
	}
	for (i=0;i<nH3D;i++) {
		h3D[i].no=i;
		h3D[i].papa=this;
	}


}

void grid3D::Junta(grid3D g2) 
{
	int i,j,nv1,nH1;
	double DIJ;
	// Los vertices de la union son: vertices[g=this] + algunos vertices[g2] // (solo aquellos que son nuevos)
	// El arreglo i2enUnion[j] indica en qué número de vertice quedará el vertice g2.v3D[j].
	//                         i2enUnion[j] <g.nV3D  <==> g2.v3D[j] ya estaba en la malla g=this
	//                         i2enUnion[j]>=g.nV3D  <==> g2.v3D[j] es un vertice nuevo en la union
	vector<int> i2enUnion(g2.nV3D);
	const double eps=1e-10; 
	nv1=nV3D;
	nH1=nH3D;
	nH3D+=g2.nH3D;

#if DBG>0
	cout <<"nv1="<<nv1<<endl;
	cout <<"nH1="<<nH1<<endl;
#endif
	for (i=0;i<g2.nV3D;i++) {
		for (j=0;j<nv1;j++) {
			DIJ=sqr(v3D[j].x-g2.v3D[i].x)+sqr(v3D[j].y-g2.v3D[i].y)+sqr(v3D[j].z-g2.v3D[i].z);
			if (DIJ<eps) break; //Este es el criterio para seber si el vertice g2.v3D[i] ya estaba en g=this.
		}
		if (j<nv1){			//El vertice g2.v3D[i] ya estaba en g=this.
			i2enUnion[i]=j;
		} else {			//El vertice g2.v3D[i] es nuevo (se agrega al final y g=this crece)
			i2enUnion[i]=nV3D;
			v3D.push_back(g2.v3D[i]);
			nV3D++;
		}
	}

	//Ahora se agregan los hexahedros
	for (i=0;i<g2.nH3D;i++) {
		h3D.push_back(g2.h3D[i]);
		Hexa3D * ih3D= &h3D[nH1+i];
		for (j=0;j<8;j++) {
			ih3D->iv[j]=i2enUnion[ih3D->iv[j]];
		}		
		for (j=0;j<ih3D->vecino.size();j++) {
			if (ih3D->tipo_vecino[j]==ES_BLOQUE) {
				ih3D->vecino[j]+=nH1;
			}
		}

	}

	//Ahora se agrgan las Caras
	for (i=0;i<g2.Cara.size();i++) {
		int i0,i1,i2,i3;
		i0=g2.Cara[i].iv[0];
		i1=g2.Cara[i].iv[1];
		i2=g2.Cara[i].iv[2];
		i3=g2.Cara[i].iv[3];
		int CaraYaExistente=0;
		if (g2.Cara[i].nVolumenes==1) { //Se trataba de una Cara de borde (que puede cerrar una cara anterior)
			CaraYaExistente=1;   //Posible cara repetida
			if (i2enUnion[i0] >= nv1) CaraYaExistente=0; //nodo nuevo
			if (i2enUnion[i1] >= nv1) CaraYaExistente=0; //nodo nuevo
			if (i2enUnion[i2] >= nv1) CaraYaExistente=0; //nodo nuevo
			if (i2enUnion[i3] >= nv1) CaraYaExistente=0; //nodo nuevo
		}
		if (CaraYaExistente==1) {
			int iC=BuscaCara4(i2enUnion[i0],i2enUnion[i1],i2enUnion[i2],i2enUnion[i3]);
#if DBG>1
			cout<<"La nueva cara "<<i<<" Es la misma que la vieja "<<iC<<endl;
#endif
			if (iC>Cara.size()) {
				cout <<"i2enUnion[i0]="<<i2enUnion[i0]<<"\t"
						<<"i2enUnion[i1]="<<i2enUnion[i1]<<"\t"
						<<"i2enUnion[i2]="<<i2enUnion[i2]<<"\t"
						<<"i2enUnion[i3]="<<i2enUnion[i3]<<"\t"
						<<"nv1="<<nv1<< endl;
				cout << "Error en grid3D::Junta, linea 2023"<<endl;
				exit(0);
			}
			if (Cara[iC].nVolumenes>1) {
				cout <<"i2enUnion[i0]="<<i2enUnion[i0]<<"\t"
						<<"i2enUnion[i1]="<<i2enUnion[i1]<<"\t"
						<<"i2enUnion[i2]="<<i2enUnion[i2]<<"\t"
						<<"i2enUnion[i3]="<<i2enUnion[i3]<<"\t"
						<<"nv1="<<nv1<< endl;
				cout << "Error en grid3D::Junta, linea 2032"<<endl;
				exit(0);
			}
			int ih0=Cara[iC].ih[0];
			int ih1=nH1+g2.Cara[i].ih[0];

			//
			Cara[iC].nVolumenes=2;
			Cara[iC].ih[1]=ih1; //Nuevo bloque de la cara == bloque de la gara en malla g2
			Cara[iC].iBC=0;
			//			iP=h3D[ih0].BuscaPoligono();
			{
				Hexa3D *hexa3D = &h3D[ih0];
				for (j=0;j<hexa3D->vecino.size();j++) {
					if ((hexa3D->tipo_vecino[j]==ES_CARA || hexa3D->tipo_vecino[j]==ES_CARA_L2)&&
							hexa3D->vecino[j]==iC ) { //Te encontre
						hexa3D->tipo_vecino[j]=ES_BLOQUE;
						hexa3D->vecino[j]=ih1;
					}
				}


				hexa3D = &h3D[ih1];
				for (j=0;j<hexa3D->vecino.size();j++) {
					if ((hexa3D->tipo_vecino[j]==ES_CARA || hexa3D->tipo_vecino[j]==ES_CARA_L2 ) &&
							hexa3D->vecino[j]==i ) { //Te encontre
						hexa3D->icara[j]=iC;
						hexa3D->tipo_vecino[j]=ES_BLOQUE;
						hexa3D->vecino[j]=ih0;
					}
				}
			}
		} else { //Cara nueva
			this->nCaras++;
#if DBG >1
			cout<<"Agregando Cara "<<this->nCaras<<endl;
#endif
			Cara.push_back(g2.Cara[i]);
			Cara3D *nuevaCara= &Cara[nCaras-1];
			for (j=0;j<4;j++) {
				nuevaCara->iv[j]=i2enUnion[nuevaCara->iv[j]]; //cambio de numeracion g2 a nueva
			}
			nuevaCara->no=this->nCaras-1;
			for (j=0;j<nuevaCara->nVolumenes;j++) {
				int ih,k;
				ih=nuevaCara->ih[j]+=nH1; //cambio de numeracion g2 a nueva
				for (k=0;k<h3D[ih].vecino.size();k++){
					if ( (h3D[ih].tipo_vecino[k]==ES_CARA ||h3D[ih].tipo_vecino[k]==ES_CARA_L2 ) && h3D[ih].vecino[k]==i) {
						h3D[ih].vecino[k]=nCaras-1;
					}
				}
				for (k=0;k<6;k++){
					if (h3D[ih].icara[k]==i) {
						h3D[ih].icara[k]=nCaras-1;
					}
				}
			}
		}
	}


	for (i=0;i<nV3D;i++) {
		v3D[i].no=i;
		v3D[i].papa=this;
	}
	for (i=0;i<nH3D;i++) {
		h3D[i].no=i;
		h3D[i].papa=this;
	}


}

void grid3D::Rota90Z()
{
	int i;
	double xL,yL;
	for (i=0;i<nV3D ;i++){
		xL=v3D[i].x;
		yL=v3D[i].y;
		v3D[i].x = -yL;
		v3D[i].y = xL;
	}
}

//----------------Traslaciones
void R3::Traslada(double dx,double dy,double dz)
{
	x += dx;
	y += dy;
	z += dz;
}

const R3& R3::operator = ( const R3& v)
{
	x=v.x;
	y=v.y;
	z=v.z;
	L=v.L;
    return *this;
}
R3 R3::operator -(const R3& v1)
{
    R3 v;
    v.x=x-v1.x;
    v.y=y-v1.y;
    v.z=z-v1.z;
    return v;
}


void PoligonoPlano::Traslada(double dx,double dy,double dz)
{
	int i;
	for (i=0;i<punto.size() ;i++) punto[i].Traslada( dx, dy, dz);
	centro.Traslada( dx, dy, dz);

}
void Vertex3D::Traslada(double dx,double dy,double dz)
{
	x += dx;
	y += dy;
	z += dz;

}

void Cara3D::Traslada(double dx,double dy,double dz)
{
	centro.Traslada( dx, dy, dz);

}

void Hexa3D::Traslada(double dx,double dy,double dz)
{

	int i;
	for (i=0;i<Poligono.size() ;i++) Poligono[i].Traslada( dx, dy, dz);
	centro.Traslada( dx, dy, dz);

}
void grid3D::Traslada(double dx,double dy,double dz)
{
	int i;
	for (i=0;i<v3D.size() ;i++) v3D[i].Traslada( dx, dy, dz);
	for (i=0;i<h3D.size() ;i++) h3D[i].Traslada( dx, dy, dz);
	for (i=0;i<Cara.size() ;i++) Cara[i].Traslada( dx, dy, dz);
	xmin+=dx;
	xmax+=dx;
	ymin+=dy;
	ymax+=dy;
	zmin+=dz;
	zmax+=dz;

}





void R3::NormaUnitario()
{
	L = sqrt(x*x+y*y+z*z);
	x/=L;
	y/=L;
	z/=L;
	L=1.0;
}


//----------------Escalamientos Z
void R3::EscalaZ(double lambda)
{
	z *= lambda;
	L = sqrt(x*x+y*y+z*z);
}

void PoligonoPlano::EscalaZ(double lambda)
{
	int i;
	double Ax=AreaPoligono*normal.x*lambda;
	double Ay=AreaPoligono*normal.y*lambda;
	double Az=AreaPoligono*normal.z;
	AreaPoligono=sqrt(Ax*Ax+Ay*Ay+Az*Az);


	double Dab_x=Dab*normal.x;
	double Dab_y=Dab*normal.y;
	double Dab_z=Dab*normal.z*lambda;
	Dab=sqrt(Dab_x*Dab_x+Dab_y*Dab_y+Dab_z*Dab_z);


	for (i=0;i<punto.size() ;i++) punto[i].EscalaZ(lambda);

	normal.z /= lambda;
	double denom=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
	normal.x /= denom;
	normal.y /= denom;
	normal.z /= denom;


	centro.EscalaZ(lambda);

}
void Vertex3D::EscalaZ(double lambda)
{
	z *= lambda;
}

void Cara3D::EscalaZ(double lambda)
{




	centro.EscalaZ(lambda);


	normalCara.z /= lambda;
	double denom=sqrt(normalCara.x*normalCara.x+normalCara.y*normalCara.y+normalCara.z*normalCara.z);
	normalCara.x /= denom;
	normalCara.y /= denom;
	normalCara.z /= denom;



}


void Hexa3D::CalculaVolumen()
{
	int i;
	volumen=0;
	for (i=0;i<Poligono.size() ;i++) {
		volumen += Poligono[i].AreaPoligono * Poligono[i].Dab/6;
		if (tipo_vecino[i]==ES_CARA ) {
			Cara3D * CaraI =  & (papa->Cara[vecino[i]]);
			if (CaraI->iBC ==2 || CaraI->iBC ==3 ) {
				CaraI->volumen = Poligono[i].AreaPoligono*Poligono[i].Dab/2;
			}
		}

	}
}


void VolumenFinito::CalculaVolumen()
{
	int i;
	volumen=0;
	for (i=0;i<Poligono.size() ;i++) {
		volumen += Poligono[i].AreaPoligono * Poligono[i].Dab/6;
	}
}



void grid3D::Soporte_Vertices()
{
	int i,j;
	for (i=0;i<v3D.size() ;i++) {
		v3D[i].soporte.resize(0);
	}
	for (i=0;i<h3D.size() ;i++) {
		for (j=0;j<8;j++) {
		v3D[h3D[i].iv[j]].soporte.push_back(i);
		}
	}
	for (i=0;i<TriPrisma3D.size() ;i++) {
		for (j=0;j<6;j++) {
		v3D[TriPrisma3D[i].iv[j]].soporte.push_back(i+h3D.size());
		}
	}

}


void grid3D::CalculaVolumen()
{
	int i;
	for (i=0;i<h3D.size() ;i++) {
		h3D[i].CalculaVolumen();
	}
	for (i=0;i<VolFinito.size() ;i++) {
		VolFinito[i].CalculaVolumen();
	}

}

void Hexa3D::EscalaZ(double lambda)
{

	int i;
	for (i=0;i<Poligono.size() ;i++) Poligono[i].EscalaZ(lambda);
	centro.EscalaZ(lambda);

}
void grid3D::EscalaZ(double lambda)
{
	int i;
	for (i=0;i<v3D.size() ;i++) v3D[i].EscalaZ(lambda);
	for (i=0;i<h3D.size() ;i++) h3D[i].EscalaZ(lambda);
	for (i=0;i<Cara.size() ;i++) Cara[i].EscalaZ(lambda);
	zmin*=lambda;
	zmax*=lambda;
	if(lambda<0) {
		double tmp=zmax;
		zmax=zmin;
		zmin=tmp;
	}

}


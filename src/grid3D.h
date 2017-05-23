//#pragma once


#include "Class_Vector.h"
#include<vector>


int const maxpasadas=20;
extern float factorV, factorVh;
extern int MODO_NumeraH,MODO_NumeraFF;
extern vector<double> PotencialPsi,UU,VV,WW;
extern int binario;
extern float FactorNormales,FactorSuavidad;

class grid3D;

class R3{ //Puntos,vectores y Doblepuntos de \R^3
public:
	double x,y,z,L;//L se usa para trazos que unen dos puntos en los poligonos

//-----
	void save(ofstream &myfile);
	void read(ifstream &myfile);
	void Traslada(double dx,double dy,double dz);
	void EscalaZ(double lambda);
	void NormaUnitario();

};

double ppunto(R3 a,R3 b);

double ppuntodiff(R3 a,R3 b,R3 c);

class PoligonoPlano {
public:
	double AreaPoligono,Dab;
	vector<R3> punto;
	R3 normal;
	R3 centro;

//------
	void save(ofstream &myfile);
	void read(ifstream &myfile);
	void Traslada(double dx,double dy,double dz);
	void EscalaZ(double lambda);

};

class Vertex3D {
public:
	double x,y,z;
	int no;
	grid3D *papa;
	R3 normalVetex;

//----
	void save(ofstream &myfile);
	void read(ifstream &myfile,grid3D *papaL);
	void Traslada(double dx,double dy,double dz);
	void EscalaZ(double lambda);
};

class Cara3D {
public:
	grid3D *papa;
	int no,nvCara,nVolumenes,iBC;
	int iv[4],ih[2];
	double BC,BC2,volumen;
	R3 centro;
	R3 normalCara;

//----
	void save(ofstream &myfile);
	void inicializa(grid3D *pp);
	void read(ifstream &myfile,grid3D *papaL);
	void Traslada(double dx,double dy,double dz);
	void EscalaZ(double lambda);

	void drawGL();      //Impime numeror, centro, etc
	void draw_caraGL();  //Dibuja el poligono ==cara

};


class Hexa3D {
	// Hexaedros:
	//	  2------3
	//   /|     /|
	//  6-|----7 |
	//	| |    | |
	//	| 0----|-1
	//	|/     |/
	//  4------5

public:
	vector<PoligonoPlano> Poligono;		// El hexahedro [i] con el g.h3D[i].vecino[j] se unen por g.h3D[i].Poligono[j]
	vector<int> vecino;					// Lista de Hexahedros vecinos (O Cara en el borde)
	vector<int> tipo_vecino;			// Lista del mismo largo, == ES_BOQUE o ES_CARA o ES_CARA_L2
	// Cuando g.h3D[i].tipo_vecino[j] == ES_CARA  ==> iC=g.h3D[i].vecino[j] es una Cara verdadera: g.Cara[iC]
	vector<int> dibujado;

	int iv[8];
	int icara[6];
	int no;
	double volumen;
	R3 centro;
	grid3D *papa;

//-----
	void save(ofstream &myfile);
	void read(ifstream &myfile,grid3D *papaL);
	void Traslada(double dx,double dy,double dz);
	void EscalaZ(double lambda);

	void draw_caraGL(int ,int,int,int);
	void draw_caraGL(vector<double> F,double,double,int ,int,int,int);
	void draw_edgeGL(int i0,int i1);
	void CalculaVolumen();
};


class TriPrisma {
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
public:

	grid3D *papa;
	int no;
	int iv[6];
	double volumen;
	int icara[5];
	R3 centro;

	vector<PoligonoPlano> Poligono;		// El TriPrisma [i] con el g.h3D[i].vecino[j] se unen por g.h3D[i].Poligono[j]
	vector<int> vecino;					// Lista de TriPrismas vecinos (O Cara en el borde)
	vector<int> tipo_vecino;			// Lista del mismo largo, == ES_BOQUE o ES_CARA o ES_CARA_L2
	// Cuando g.h3D[i].tipo_vecino[j] == ES_CARA  ==> iC=g.h3D[i].vecino[j] es una Cara verdadera: g.Cara[iC]
	vector<int> dibujado;

	
	
//-----
	void save(ofstream &myfile);
	void readMSH(ifstream &myfile,grid3D *papaL);
	void read(ifstream &myfile,grid3D *papaL);
	void Traslada(double dx,double dy,double dz);
	void EscalaZ(double lambda);

	void draw_caraGL(int ,int,int,int);
	void draw_caraGL(vector<double> F,double,double,int ,int,int,int);
	void draw_edgeGL(int i0,int i1);
	void CalculaVolumen();
	void DrawCentro();
};


class grid3D
{
public:
	int nH3D,nV3D,nCaras,nPoligonos,QuienGeneraPoligonos;
	double xmin,xmax,ymin,ymax,zmin,zmax;
	
	vector<Vertex3D> v3D;
	vector<Hexa3D>   h3D;
	vector<Cara3D> Cara;
	
	//Version >= 3
	int nTriPrisma3D,TriPri3DAnalizados=0;
	vector<TriPrisma>   TriPrisma3D;
	

//----------------------

	void CalculaNormalVertex();
	void write(ofstream &myfile);
	void read(ifstream &myfile);
	void write(char *);
	void read(char *);
	void readMSH3D(char *ifile_name);

	void minmax();

	void drawGL();
	void drawGL(vector<double> F);
	void drawVoronoi();

	void drawVelGL_TriPrisma(vector<double> U,vector<double> V,vector<double> W);
	void drawVelGL(vector<double>,vector<double>,vector<double>);
	void drawVelGL2(vector<double>,vector<double>,vector<double>);

	void GeneraCaras(int inicia=false);	
	void GeneraCarasTriPri();
	int BuscaCara3(int i0,int i1,int i2) ;
	int AddCara3(int ib,int i0,int i1,int i2);
	int BuscaCara4(int i0,int i1,int i2,int i3) ;
	int AddCara4(int ib,int i0,int i1,int i2,int i3);
	void draw_caraGL(int ii[4]);

	void draw_caraGL(vector<double>F,double minF,double maxF,int ii[4]);
	void generaPoligonos2();
	void generaPoligonos2Algunos(vector<int> &CualesRehacer);
	void GeneraPoligonoInicial(R3 a, R3 b, PoligonoPlano &P);
	void CentroCarasBloques();

	void CalculaVolumen();
	void PosINI(int i);
	void PosINI3(double posX, double posY, double posZ);



	void cubo(int,int,int,float=1,float=1,float=1);
	void Junta(grid3D g1,grid3D g2);
	void Junta(grid3D g2);
	void Rota90Z();
	void Traslada(double dx,double dy,double dz);
	void EscalaZ(double lambda);
	grid3D(void);
	~grid3D(void);

};
#define ES_BLOQUE 1
#define ES_CARA   2
#define ES_CARA_L2   3

#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#ifdef __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        #include <GLUT/glut.h>
        #include <OpenGL/OpenGL.h>
//        #define mkdir(x) system(sprintf("mkdir %s",((x))))
    #endif
#elif defined _WIN32 || defined _WIN64
	#include "GL/freeglut.h"
	//#include <GL\glut.h>
	#define GLUI_FREEGLUT 1
	//#include "GL/glut.h"
	//#ifdef _WIN32
	#include <windows.h>
	#include <Commdlg.h>
//   #define mkdir(x,y) _mkdir((x))
//   #define rmdir(x) _rmdir((x))
   #define getcwd _getcwd

#endif

#include <stdio.h>
#include "globales.h"
#include <iomanip>
using namespace std;
//#endif

#include "comunes.h"

extern int nParticulas;
extern double ThetaMax,ThetaMin,dTheta_med;
extern  int primerdrawVelGL;
////////////////////////////////////WEB

void				GuardarInstantanea();
char  text[200000] = {"Hello World!"};

//#define PAUSA 	                       }iEtapa++;cout<<"iEtapa="<<iEtapa<<endl;if (Etapa==iEtapa) { InicioEtapaP=InicioEtapa;InicioEtapa=Etapa;Guardar=1;
//#define PAUSAF 	                       }iEtapa++;cout<<"iEtapa="<<iEtapa<<endl;if (Etapa==iEtapa) { Guardar=1;
//#define PAUSA2 	Falta_llamar_etapaS=1; }iEtapa++;cout<<"iEtapa="<<iEtapa<<endl;if (Etapa==iEtapa) { Guardar=0;

#define PAUSA 	                       }iEtapa++;if (Etapa==iEtapa) { InicioEtapaP=InicioEtapa;InicioEtapa=Etapa;Guardar=0;
#define PAUSAF 	                       }iEtapa++;if (Etapa==iEtapa) { Guardar=0;
#define PAUSA2 	llamar_etapa_Siguiente_PAUSA2=1; }iEtapa++;if (Etapa==iEtapa) { Guardar=0;



#if defined _WIN32 || defined _WIN64s
string  GetFileName( const string & prompt ) {
    const int BUFSIZE = 1024;
    char buffer[BUFSIZE] = {0};
    OPENFILENAME ofns = {0};
    ofns.lStructSize = sizeof( ofns );
    ofns.lpstrFile = buffer;
    ofns.nMaxFile = BUFSIZE;
    ofns.lpstrTitle = prompt.c_str();
    GetOpenFileName( & ofns );
    return buffer;
}
#endif

void TesteDeVariablesGlobales() ;

void calculaFracionVolumen(vector<double> &Temp) {
	int i;
//	cout<<"calculaFracionVolumen()"<<endl;
	double FraccionVolumen=0,VolumenTotal=0;
	for (i=0;i<gtotal->h3D.size();i++) {
		VolumenTotal += gtotal->h3D[i].volumen;
		if (Temp[i]>TLimite) FraccionVolumen += gtotal->h3D[i].volumen;

	}
	//cout<<"calculaFracionVolumen()2"<<endl;
	for (i=0;i<gtotal->Cara.size();i++) {
		if (gtotal->Cara[i].iBC ==2 || gtotal->Cara[i].iBC ==3 ) {
			VolumenTotal += gtotal->Cara[i].volumen;
			if (gtotal->Cara[i].BC2>TLimite) FraccionVolumen += gtotal->Cara[i].volumen;
		}
	}

	//cout<<"Volumen con T>"<<TLimite<<" = "<<FraccionVolumen<<"\tVolumenTotal"<<VolumenTotal<<"\t(nH3D="<<gtotal->nH3D<<")"<<endl;
	FraccionVolumen /= VolumenTotal;

	if (TipoCalculo==CalculoEvolucion) {
		cout<<"Fraccion Volumen con T>"<<TLimite<<" = "<<FraccionVolumen
				<<"\tT = "<<TiempoCalculo<<endl;
		myfileSalida<<"Fraccion Volumen con T>"<<TLimite<<" = "<<FraccionVolumen
				<<"\tT = "<<TiempoCalculo<<endl;
		myfileVol<<TiempoCalculo<<" "<<FraccionVolumen<<endl;
	} else {
		cout<<"Fraccion Volumen con T>"<<TLimite<<" = "<<FraccionVolumen<<endl;
		myfileSalida<<"Fraccion Volumen con T>"<<TLimite<<" = "<<FraccionVolumen<<endl;
	}

	char s[100];
	sprintf(s,"Fraccion=%f\n",FraccionVolumen);if (glui != NULL) glui_porcentaje->set_name(s);

//	cout<<"calculaFracionVolumen():END"<<endl;
}



void Lectura_Bahia_y_CalculosGeometricosMalla(char * fname) {


	clock_t start_t, end_t;
	double total_t;

	//Etapa de Lectura de la malla

	cout<<"lectura de bahia-TriPrismas.msh3D..."<<endl;
	start_t = clock();
	gtotal->readMSH3D(fname);

	end_t = clock();
	total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	cout<<"Lista la lectura en "<<total_t<<" seg";
	if (total_t>60) {
		int min=total_t/60; total_t-=min*60;
		cout<<" ( "<<min<<":"<<total_t<<"min)";
	}
	cout <<endl;

	sprintf(text,"%sFin Etapa\n",text);


	cout<<"gtotal->GeneraCarasTriPri()..."<<endl;

	start_t = clock();
	gtotal->GeneraCarasTriPri();

	end_t = clock();
	total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;


	cout<<"Listo gtotal->GeneraCarasTriPri() ";
	cout<<" en "<<total_t<<"seg";
	if (total_t>60) {
		int min=total_t/60; total_t-=min*60;
		cout<<" ( "<<min<<":"<<total_t<<"min)";
	}
	cout <<endl;


	gtotal->minmax();
	gtotal->CentroCarasBloques();


	gtotal->generaPoligonos2();
//	Modo_DibujaCentroBloques=true;
//		Modo_DibujaCentroCaras=true;
	err0=1e-12;


	gtotal->CalculaVolumen();

}


void malla1(int &Etapa, int &iEtapa) {

#if DBG==1
	cout<<"malla1()"<<endl;
#endif

	int i,j,iL,malla;
	double x1,x2,x2a,y1,y2,xL,yL,R,xF,yF,RF,R1,R2,RE,th,pi=4*atan(1.0);
	double LZ=Dominio_Hsup; //Basico

#if DBG==1
	cout << "nRLC=" << nRLC << endl;
	cout << "nThLC=" << nThLC << endl;
#endif
	if (nRLC>0) nR=nRLC;
	if (nThLC>0) nTh=nThLC;

	x1=Dominio_Rint;x2a=Dominio_Rmed;x2=Dominio_Xmax-x2a;



	if (Etapa==iEtapa) {

		Escala=1/Dominio_Xmax;
		printf("Mallando \n");
		myfileSalida<<"Mallando "<<endl;
		gtotal->cubo(nR,nTh,nZ,1,1,LZ);g2.cubo(nTh,nR,nZ,1,1,LZ);


		//PAUSA
		ThetaMax=atan(1)*2;
//		printf("Etapa: Se comprime g ");cout<<endl;
		double q=exp(0.4*(log(Dominio_Rmed/Dominio_Rint)/(nR)));
		cout<<"q="<<q<<endl;
		myfileSalida<<"q="<<q<<endl;
		double Sumq=0,qi=1;
		for (i=0;i<nR;i++) {Sumq +=qi;qi*=q;}
		//cout<<"Sumq="<<Sumq<<endl;
		double L0=(Dominio_Rmed-Dominio_Rint)/Sumq;
		for (i=0;i<gtotal->nV3D;i++) {
			xL=gtotal->v3D[i].x; yL=gtotal->v3D[i].y;
			int nRL=(xL*nR+.5);
			Sumq=0;qi=1;
			for (j=0;j<nRL;j++) {Sumq +=qi;qi*=q;}
			//cout<<"Sumqi="<<Sumq<<endl;
			double Rloc=L0*Sumq;
			th=atan(yL);
			double co=cos(th);
			if (xL<2.0/nR) co=1;
			R1=(x1+Rloc)/co;
			R2=(x1+Rloc);
			R=R2+(R1-R2)*xL;
			gtotal->v3D[i].x=R*cos(th);
			gtotal->v3D[i].y=R*sin(th);
		}

		//PAUSA

//		printf("Etapa: Se comprime g2\n");cout<<endl;
		for (i=0;i<g2.nV3D;i++) {
			xL=g2.v3D[i].x;	yL=g2.v3D[i].y;
			int nRL=(yL*nR+.5);
			Sumq=0;qi=1;
			for (j=0;j<nRL;j++) {Sumq +=qi;qi*=q;}
			//cout<<"Sumqi="<<Sumq<<endl;
			double Rloc=L0*Sumq;
			th=atan(xL);
			double co=cos(th);
			if (yL<2.0/nR) co=1;
			R1=(x1+Rloc)/co;
			R2=(x1+Rloc);
			R=R2+(R1-R2)*yL;
			g2.v3D[i].x=R*sin(th);
			g2.v3D[i].y=R*cos(th);
		}
		g1=*gtotal;
		*gtotal=g2;
		th=1;
		gtotal->GeneraCaras(-1);

		//PAUSA

//		printf("Etapa: junto g y g2 \n");cout<<endl;
		gtotal->Junta(g1);

		gtotal->GeneraCaras(gtotal->nH3D); //A partir de ahora se agregan las caras para los bloques actuales
PAUSA2

		//printf("Etapa: Se agrega corona 2 lado\n");cout<<endl;
		g2.cubo(nR2,nTh,nZ,x2,x2a,LZ);g2.Traslada(x2a,0,0);gtotal->Junta(g2);

		gtotal->GeneraCaras(gtotal->nH3D); //A partir de ahora se agregan las caras para los bloques acuales
PAUSA2

		//printf("Etapa: Se copia corona lateral 2 veces\n");cout<<endl;
		g2.cubo(nTh,nR2,nZ,x2a,x2,LZ);g2.Traslada(0,x2a,0);gtotal->Junta(g2);
		g2.cubo(nR2,nR2,nZ,x2,x2,LZ);g2.Traslada(x2a,x2a,0);gtotal->Junta(g2);


		gtotal->GeneraCaras(gtotal->nH3D); //A partir de ahora se agregan las caras para los bloques acuales
PAUSA

		sprintf(text,"%sRetoco la malla\n",text);if (glui != NULL)glui_edittext->set_text(text);


		gtotal->minmax();
		gtotal->CentroCarasBloques();

		vector<R3> SumaCoor(gtotal->nV3D);
		vector<int> NSumaCoor(gtotal->nV3D);

		double err,errG=0,x0,y0,x1,y1;
		for (int iter=0;iter<100;iter++) {
			for (i=0;i<gtotal->nV3D; i++) {
				SumaCoor[i].x=0;
				SumaCoor[i].y=0;
				NSumaCoor[i]=0;
			}

			for (i=0;i<gtotal->nCaras; i++) {
				int iv1=gtotal->Cara[i].iv[0];
				int iv2=gtotal->Cara[i].iv[1];
				int iv3=gtotal->Cara[i].iv[2];
				int iv4=gtotal->Cara[i].iv[3];

				if (sqr(gtotal->v3D[iv1].x)+sqr(gtotal->v3D[iv1].y)+1e-5<Dominio_Rint) continue;
				if (sqr(gtotal->v3D[iv2].x)+sqr(gtotal->v3D[iv2].y)+1e-5<Dominio_Rint) continue;
				if (sqr(gtotal->v3D[iv3].x)+sqr(gtotal->v3D[iv3].y)+1e-5<Dominio_Rint) continue;
				if (sqr(gtotal->v3D[iv4].x)+sqr(gtotal->v3D[iv4].y)+1e-5<Dominio_Rint) continue;

				if (fabs(gtotal->Cara[i].normalCara.z)>0.9) {
					SumaCoor[iv1].x += gtotal->v3D[iv2].x;
					SumaCoor[iv1].y += gtotal->v3D[iv2].y;
					SumaCoor[iv1].x += gtotal->v3D[iv4].x;
					SumaCoor[iv1].y += gtotal->v3D[iv4].y;
					NSumaCoor[iv1]+=2;
					SumaCoor[iv2].x += gtotal->v3D[iv3].x;
					SumaCoor[iv2].y += gtotal->v3D[iv3].y;
					SumaCoor[iv2].x += gtotal->v3D[iv1].x;
					SumaCoor[iv2].y += gtotal->v3D[iv1].y;
					NSumaCoor[iv2]+=2;
					SumaCoor[iv3].x += gtotal->v3D[iv4].x;
					SumaCoor[iv3].y += gtotal->v3D[iv4].y;
					SumaCoor[iv3].x += gtotal->v3D[iv2].x;
					SumaCoor[iv3].y += gtotal->v3D[iv2].y;
					NSumaCoor[iv3]+=2;
					SumaCoor[iv4].x += gtotal->v3D[iv1].x;
					SumaCoor[iv4].y += gtotal->v3D[iv1].y;
					SumaCoor[iv4].x += gtotal->v3D[iv3].x;
					SumaCoor[iv4].y += gtotal->v3D[iv3].y;
					NSumaCoor[iv4]+=2;
				}
			}

			errG=0;
			for (i=0;i<gtotal->nV3D; i++) {
				if (NSumaCoor[i]>4){
					x1=SumaCoor[i].x/NSumaCoor[i];
					y1=SumaCoor[i].y/NSumaCoor[i];
					x0=gtotal->v3D[i].x;
					y0=gtotal->v3D[i].y;
					err=(fabs(x0-x1)+fabs(y0-y1))/(fabs(x0)+fabs(y0));
					if (err>errG) errG=err;
					gtotal->v3D[i].x=x1;
					gtotal->v3D[i].y=y1;
				}
#if DBG==1
				cout <<"NSumaCoor[i]="<<NSumaCoor[i]<<endl;
#endif

			}
		}


		sprintf(text,"%sErrG=%e\nerrMalla=%e\n",text,errG,errMalla);if (glui != NULL)glui_edittext->set_text(text);

		if(errG>errMalla)		Etapa--;

PAUSA

	}
}


void malla2(int &Etapa, int &iEtapa) {

	int i,j,iL,malla;
	double x1,x2,y1,y2,xL,yL,R,xF,yF,RF,R1,R2,RE,th,pi=4*atan(1.0);
	//	int nR=5,nTh=5,nZ=10;LZ=5;
	//	int nR=7,nTh=4,nZ=1;LZ=1;
	//	int nR=12,nTh=6,nZ=1;LZ=1;
	//	int nR=12,nTh=3,nZ=1;LZ=Dominio_Hsup; //Basico
	//	int nR=34,nTh=10,nZ=1;
	double LZ=Dominio_Hsup; //Basico
	//	int nR=25,nTh=10,nZ=1;LZ=Dominio_Hsup; //Refinado
	x1=Dominio_Rint;x2=Dominio_Xmax;

	cout << "malla2(Etapa=" << Etapa << ",iEtapa="<<iEtapa<<")"<<endl;
	myfileSalida << "malla2(Etapa=" << Etapa << ",iEtapa="<<iEtapa<<")"<<endl;

	if (Etapa==iEtapa) {


		switch (CualMalla) {
		case 2:
//			nR=34;nTh=10;
			nTh=nTh/2;    //Despues se duplicará la malla ( nth/2*2=nTh)
			ThetaMax=atan(1)*4; //pi+duplicacion
			ThetaMin=-atan(1)*0;

			break;
		case 3:
			//			nR=34;nTh=1;
			ThetaMax=atan(1)/15; //
			ThetaMin=-atan(1)/15;
//			ThetaMax=atan(1)/2; //Test
//			ThetaMin=-atan(1)*0;

			break;
		case 4:
			nR=34;nTh=6;
			ThetaMax=atan(1)*2; //
			ThetaMin=-atan(1)*0;

			break;
		default:
			break;
		}

		dTheta_med=(ThetaMax-ThetaMin)/nTh;
		Escala=1/x2;
		printf("Etapa: Se definen g\n");
		gtotal->cubo(nR,nTh,nZ,1,1,LZ);


		//PAUSA
		printf("Etapa: Se Transforma g ");cout<<endl;
		for (i=0;i<gtotal->nV3D;i++) {
			xL=gtotal->v3D[i].x; yL=gtotal->v3D[i].y;
			//			xL *= sqrt(xL);
			if (refinoR==1)
				xL=(1-cos(pi*xL))/2;
			th=ThetaMin+(ThetaMax-ThetaMin)*yL;
			RE=x2;
			R1=x1+(RE-x1)*xL;
			R2=x1+(x2-x1)*xL;
			R=R2+(R1-R2)*xL;
			gtotal->v3D[i].x=R*cos(th);
			gtotal->v3D[i].y=R*sin(th);
		}

		if (CualMalla==2) {
			g2=*gtotal;g2.Rota90Z();g2.Rota90Z();gtotal->Junta(g2);
			ThetaMax=atan(1)*8;
			nTh=nTh*2;  // Vuelvo a valor original (nTh/2*2)
		}

		gtotal->GeneraCaras(-1);    //Inicializa el numero de caras generadas ==0
		gtotal->GeneraCaras(gtotal->nH3D); //A partir de ahora se agregan las caras para los bloques acuales
#if DBG==1
		if (DBG) cout<<"ThetaMax="<<ThetaMax<<endl;
#endif
	}
}


void Calculo_EtapaS(int inicializa)
{
	int iEtapa,i;
	static int inicio=0;

#if DBGMain
	cout<<"\nCalculo_EtapaS(): Etapa="<<Etapa<<"\tinicio="<<inicio<<"\tFalta_llamar_etapaS="<<llamar_etapa_Siguiente_PAUSA2<<endl;
#endif

	if (inicializa) {
		Etapa=0;
	}
	Etapa++;
	iEtapa=1;

#if DBGMain
	cout<<"\nCalculo_EtapaS()[341]... Etapa++="<<Etapa<<":"<<endl;
#endif

	if (CalculoContinuo==0 && inicio==0 && llamar_etapa_Siguiente_PAUSA2==0) {
		sprintf(text,"Etapa=%d\n",Etapa);
		if (glui != NULL) {
			glui_edittext->set_text(text);glui_edittext->redraw_window();
			glui->refresh();
			glutSetWindow(main_window);
			glutPostRedisplay();
		}
		inicio =1;
		Etapa--;

#if DBGMain
		cout<<"\nCalculo_EtapaS()[353]... Etapa--="<<Etapa<<":"<<endl;
#endif
		llamar_etapa_Siguiente_PAUSA2=1;
		return;
	}
	inicio=0;
	llamar_etapa_Siguiente_PAUSA2=0;

	caso=2;
	CasoLectura=3; //1:LeeMatlab, 3:Leebinario
	int step=1000;

	if (Etapa==iEtapa) {

		char fn[100],fnmsh[100],fnbin[100];
		sprintf(fn,"bahia-TriPrismas%d.msh3D",caso);
		sprintf(fnmsh,"malla_gtotal%d.msh",caso);
		sprintf(fnbin,"malla_gtotal%d.bin",caso);
		switch (CasoLectura){
		case 1: //Leeer archivo generado por matlab (leeento)
			//Lectura_Bahia_y_CalculosGeometricosMalla("bahia-TriPrismas.msh3D");
			//Lectura_Bahia_y_CalculosGeometricosMalla("bahia-TriPrismas2.msh3D");
			Lectura_Bahia_y_CalculosGeometricosMalla(fn);
			binario=0;

			gtotal->write(fnmsh);
			binario=1;
			gtotal->write(fnbin);
			break;
		case 2: //Lee archivo ASCIII y escribe Binario
			gtotal->read(fnmsh);
			//			gtotal->CentroCarasBloques();
			binario=1;
			gtotal->write(fnbin);
			break;
		case 3: //Lee el archivo binario
			binario=1;
			gtotal->read(fnbin);
			binario=0;
//			gtotal->write("malla_gtotal2.msh");
			break;
		}

//TODO
		//gtotal->xmax
		gtotal->minmax();
		vecXEsfera[0]=(gtotal->xmax+gtotal->xmin)/2;
		vecXEsfera[1]=(gtotal->ymax+gtotal->ymin)/2;
		vecXEsfera[2]=(gtotal->zmax+gtotal->zmin)/2;

//		cout<<"E vecUEsfera="<<vecUEsfera[0]<<","<<vecUEsfera[1]<<"."<<vecUEsfera[2]<<","<<vecUEsfera[3]<<endl;

		tic(); cout<<"gtotal->CalculaNormalVertex()"<<endl;
		gtotal->CalculaNormalVertex();
		cout<<"FIN:gtotal->CalculaNormalVertex() en ";toc();

PAUSA;

		//Lectura de campo de Velocidades

		cout<<"Lectura de campo de Velocidades"<<endl;

		U.resize(gtotal->nTriPrisma3D);V.resize(gtotal->nTriPrisma3D);W.resize(gtotal->nTriPrisma3D);

		cout<<"532"<<endl;
		  FILE * pFile;
		  int nn,tmp;
		   char name[100];
		   sprintf(name,"UVW%d_%05d.dat",caso,step);

		   cout<<"532"<<endl;

		   pFile = fopen (name,"r");

		   fscanf(pFile,"%d\n",&nn);
		   if (nn != gtotal->nTriPrisma3D) {
				cout<<"nn != gtotal->nTriPrisma3D: "<<nn<<" != "<<gtotal->nTriPrisma3D<<endl;

			   exit(1);
		   }

			cout<<"549"<<endl;

		   for (i=0;i<nn;i++) {
			   double v1,v2,v3;
			   fscanf(pFile,"%d %lf %lf %lf\n",&tmp,&v1,&v2,&(W[i]));
			   U[i]=v1;V[i]=v2;//W[i]=v3;
			   if (i<10) {
				   cout<<tmp<<" "<<v1<<" "<<v2<<" "<<v3<<endl;
				   cout<<tmp<<" "<<U[i]<<" "<<V[i]<<" "<<W[i]<<endl;
			   }
			   if (tmp!=i) {
					cout<<"tmp!=i"<<tmp<<" "<<i<<endl;
				   exit(1);
			   }
		   }
		   fclose(pFile);

			if (glui != NULL) {
				PanelFlimite->enable();
				Checkbox_particulas->enable();
				PanelParticulas->enable();
			}

PAUSA;
			Etapa--; //Ultima etapa por ahora
PAUSA;

		EtapaGlobal=ETAPA_CALCULO_T_ARRIBA;EtapaGlobal2Local=Etapa;

#if DBGMain
		cout<<"Etapa="<<Etapa<<"IniciEtapa="<<InicioEtapa <<"EtapaGlobal2Local="<<EtapaGlobal2Local<<endl;
#endif
		cout<<"------------------------------------------------------"<<endl;
		cout<<"Calculo Escurrimiento y Temperaturas  (con err0="<<err0<<")"<<endl;
		myfileSalida<<"------------------------------------------------------"<<endl;
		myfileSalida<<"Calculo Escurrimiento y Temperaturas  (con err0="<<err0<<")"<<endl;


		sprintf(text,"%sEtapa:%d:Calculo V,T Arriba (err0=%.2e)\n",text,EtapaGlobal,err0);if (glui != NULL) glui_edittext->set_text(text);


PAUSA;

		Guardar=1;
		double minPsi,maxPsi,err,err2,errComb;
		double minTemp,maxTemp;
		cout<<"Interaciones hasta que: err<"<<err0<<endl;
		myfileSalida<<"Interaciones hasta que: err<"<<err0<<endl;

#if DBGMain
		cout<<"***Etapa="<<Etapa<<"IniciEtapa="<<InicioEtapa <<"EtapaGlobal2Local="<<EtapaGlobal2Local<<endl;
#endif

		err=CalculaMpunto(PotencialPsi,Temperatura,UU,VV,WW,*gtotal,gtotal->nH3D,err0);
		err2=CalculaTempSuperficie(Temperatura,PotencialPsi,UU2,VV2,WW2,*gtotal,gtotal->nH3D,err0);
		errComb=max(err,err2);
		U.resize(gtotal->nV3D);V.resize(gtotal->nV3D);W.resize(gtotal->nV3D);	F.resize(gtotal->nV3D);
		U.assign(gtotal->nV3D,0);V.assign(gtotal->nV3D,0);W.assign(gtotal->nV3D,0);F.assign(gtotal->nV3D,0);
		vector<int> cuantos(gtotal->nV3D);
		cuantos.assign(gtotal->nV3D,0);

		CopiaBloquesAVertices(PotencialPsi,F,&minPsi,&maxPsi,1);
		printf("minPotencialVel=%f, maxPotencialVel=%f, errPV=%.2e",minPsi,maxPsi,err);cout<<endl;
		myfileSalida<<"minPotencialVel="<<minPsi<<", maxPotencialVel="<<maxPsi<<", errPV="<<err<<endl;
		sprintf(s,"e=%.0e,FF[%.0e,%.0e]\n",errComb,minPsi,maxPsi);

		sprintf(text,"%serr=%.2e err2=%.2e\n",text,err,err2);if (glui != NULL) glui_edittext->set_text(text);


		CopiaBloquesAVertices(UU,U,&minPsi,&maxPsi,0);
		//		printf("minUU=%e, maxUU=%e, errABS=%g",minF,maxF,err);cout<<endl;
		CopiaBloquesAVertices(VV,V,&minPsi,&maxPsi,0);
		//		printf("minVV=%e, maxVV=%e, errABS=%g",minF,maxF,err);cout<<endl;
		CopiaBloquesAVertices(WW,W,&minPsi,&maxPsi,0);
		//		printf("minWW=%e, maxWW=%e, errABS=%g",minF,maxF,err);cout<<endl;




		//if (glui != NULL) glui_MSG->set_name(s);


		minTemp=maxTemp=Temperatura[0];
		for (i=0;i<gtotal->nH3D;i++) {
			if (minTemp>Temperatura[i]) minTemp=Temperatura[i];
			if (maxTemp<Temperatura[i]) maxTemp=Temperatura[i];
		}

		printf("minTemp=%f\tmaxTemp=%f (int)\terrT=%.2e",minTemp,maxTemp,err2);cout<<endl;
		myfileSalida<<"minTemp="<<minTemp<<"\tmaxTemp="<<maxTemp<<" (int)\terrT="<<err2<<endl;
		sprintf(text,"%sminT=%.2f maxT=%.2f\n",text,minTemp,maxTemp);if (glui != NULL) glui_edittext->set_text(text);

		F2Nodos.resize(gtotal->nV3D);
		CopiaBloquesAVertices(Temperatura,F2Nodos,&minTemp,&maxTemp,2);

		printf("minTemp=%f\tmaxTemp=%f (wBC)\terrT=%.2e",minTemp,maxTemp,err2);cout<<endl;
		myfileSalida<<"minTemp="<<minTemp<<"\tmaxTemp="<<maxTemp<<" (wBC)\terrT="<<err2<<endl;
		sprintf(text,"%sminT=%.2f maxT=%.2f (wBC)\n",text,minTemp,maxTemp);if (glui != NULL) glui_edittext->set_text(text);


		if (gtotal->nH3D<40){
			int j;
			cout <<"xC=[";j=0;
			for (i=0;i<gtotal->nH3D;i++) {
				cout <<gtotal->h3D[i].centro.x<<" ";j++;
				if (j>12) {cout<<"..."<<endl;j=0;}
			} cout <<"];"<<endl;

			cout <<"TC=["; j=0;
			for (i=0;i<gtotal->nH3D;i++) {
				cout <<Temperatura[i]<<" ";j++;
				if (j>12) {cout<<"..."<<endl;j=0;}
			} cout <<"];"<<endl;
		}


		err0=errComb*1e-4;
		if (err0<ErrorMax_Cada_t) err0=ErrorMax_Cada_t;
		if (errComb>ErrorMax_Cada_t)	Etapa=InicioEtapa-1;

		if (DBG) cout<<"Voy a calculaFracionVolumen(Temperatura). Etapa="<<Etapa<<endl;
		calculaFracionVolumen(Temperatura) ;

		if (DBG) cout<<"Voy Volvi calculaFracionVolumen(Temperatura). Etapa="<<Etapa<<endl;
		sprintf(text,"%sFin Etapa\n",text);	if (glui != NULL) glui_edittext->set_text(text);

PAUSA
		EtapaGlobal=ETAPA_MALLADO_2D_3D;EtapaGlobal2Local=Etapa;
		cout<<"Mallando2D-->3D "<<endl;
		myfileSalida<<"Mallando2D-->3D "<<endl;
		InicioEtapa=Etapa;


		if (glui != NULL) {
			PanelFlimite->disable();
			MODO_CampoVelocidades=0;
			glui->sync_live();
			Checkbox_particulas->disable();
			PanelParticulas->disable();
		}


		//sprintf(text,"%sCambio malla a dominio inferior\n",text);if (glui != NULL) glui_edittext->set_text(text);

		//TODO   Cambio malla a dominio inferior
		sprintf(text,"%sCambio CB\n",text);if (glui != NULL) glui_edittext->set_text(text);

		CualesRehacer.resize(0);
		for ( i=0 ; i<gtotal->nCaras ; i++ ) {
			if ( gtotal->Cara[i].nVolumenes == 1 && gtotal->Cara[i].iBC == 2) {
				gtotal->Cara[i].iBC = 1;    //Condicion Neumann homogeneo
				CualesRehacer.push_back(gtotal->Cara[i].ih[0]);
//				cout<<"CualesRehacer.size()="<<CualesRehacer.size()<<endl;
//				cout<<"CualesRehacer.end()="<<CualesRehacer.back()<<endl;
			}
		}

		gtotal->CentroCarasBloques();
		sprintf(text,"%s A la proxima: Poligonos2Algunos\n",text);if (glui != NULL) glui_edittext->set_text(text);
PAUSA2
		sprintf(text,"%sGenero Poligonos2Algunos\n",text);if (glui != NULL) glui_edittext->set_text(text);
		cout<<"Genero Poligonos2Algunos: "<<CualesRehacer.size()<<endl;
		myfileSalida<<"Genero Poligonos2Algunos: "<<CualesRehacer.size()<<endl;
		gtotal->generaPoligonos2Algunos(CualesRehacer);
PAUSA2



		sprintf(text,"%sCambio malla a dominio inferior\n",text);if (glui != NULL) glui_edittext->set_text(text);

		g2=*gtotal;
		g2.Traslada(0,0,-Dominio_Hsup);
		g2.EscalaZ(Dominio_Hmax/Dominio_Hsup/NDivZ);
		*gtotal=g2;

		sprintf(text,"%sFin Etapa\n",text);

		if (glui != NULL) glui_edittext->set_text(text);

PAUSA2

		for (i=1;i<NDivZ;i++) {
			g2.Traslada(0,0,-Dominio_Hmax/NDivZ);
			gtotal->Junta(g2);
		}
		sprintf(text,"%sFin Etapa (listo para calcular?)\n",text);	if (glui != NULL) glui_edittext->set_text(text);

PAUSA2

		sprintf(text,"%sg.CentroCarasBloques()\n",text);	if (glui != NULL) glui_edittext->set_text(text);

		gtotal->minmax();
		gtotal->CentroCarasBloques();



PAUSA2

		sprintf(text,"%sArreglo CB nuevas\n",text);	if (glui != NULL) glui_edittext->set_text(text);

		CualesRehacer.resize(0);
		for ( i=0 ; i<gtotal->nCaras ; i++ ) {
			if ( gtotal->Cara[i].nVolumenes == 2) {
				gtotal->Cara[i].iBC =0 ;  ///nodo interno
			} else {
				double x,y,z;
				x=gtotal->Cara[i].centro.x;
				y=gtotal->Cara[i].centro.y;
				z=gtotal->Cara[i].centro.z;
				gtotal->Cara[i].iBC = 1;    //Condicion Neumann homogeneo
				gtotal->Cara[i].BC  = 0;
				//				if (sqrt(sqr(x)+sqr(y))+1e-5>=Dominio_Rmax*cos(dTheta_med)
				//						|| z+Dominio_Hmax< 1e-5 ) {
				if ( z-1e-5 < -Dominio_Hmax ) { //Abajo
					gtotal->Cara[i].iBC = 11; //Condicion Convectiva

					int iC=i;
					if(1==0) cout<<"g.Cara[iC].BC2="<<gtotal->Cara[iC].BC2
							<<"\t.BC="<<gtotal->Cara[iC].BC
							<<"\tg.Cara[iC].iBC="<<gtotal->Cara[iC].iBC
							<<"\tiC="<<iC
							<<"\tx="<<x
							<<"\ty="<<y
							<<"\tz="<<z
							<<endl;
				}
				if ( x+1e-5 > Dominio_Xmax ) { // Adelante
					gtotal->Cara[i].iBC = 12; //Condicion Convectiva mas espesor

				}
				if ( y+1e-5 > Dominio_Xmax ) { //Derecha
					gtotal->Cara[i].iBC = 12; //Condicion Convectiva mas espesor

				}
				if (z>=-1e-5) {

					//TODO 	CualesRehacer.resize(0);

					CualesRehacer.push_back(gtotal->Cara[i].ih[0]);

					gtotal->Cara[i].iBC = 2;    //Condicion Temperatura conocida
					gtotal->Cara[i].BC  = 0;
					gtotal->Cara[i].BC2  = Temperatura[ gtotal->Cara[i].ih[0] ];

					int iC=i;
					if(1==0) cout<<"g.Cara[iC].BC2="<<gtotal->Cara[iC].BC2
							<<"\t.BC="<<gtotal->Cara[iC].BC
							<<"\tg.Cara[iC].iBC="<<gtotal->Cara[iC].iBC
							<<"\tiC="<<iC
							<<"\tx="<<x
							<<"\ty="<<y
							<<"\tz="<<z
							<<endl;
				}
				int iC=i;
				if(1==0) cout<<"g.Cara[iC].BC2="<<gtotal->Cara[iC].BC2
						<<"\t.BC="<<gtotal->Cara[iC].BC
						<<"\tg.Cara[iC].iBC="<<gtotal->Cara[iC].iBC
						<<"\tiC="<<iC
						<<"\tx="<<x
						<<"\ty="<<y
						<<"\tz="<<z
						<<endl;

			}
		}


PAUSA2
		printf("Calculos Geometrico malla 3D");cout<<endl;
		myfileSalida<<"Calculos Geometrico malla 3D"<<endl;
		sprintf(text,"%sSCalculos Geometrico malla 3D\n",text);if (glui != NULL) glui_edittext->set_text(text);

PAUSA2
		gtotal->generaPoligonos2Algunos(CualesRehacer);
		err0=1e-10;

		//cout<<"***Etapa="<<Etapa<<"IniciEtapa="<<InicioEtapa <<"EtapaGlobal2Local="<<EtapaGlobal2Local<<endl;

		gtotal->CalculaVolumen();

		sprintf(text,"%sFin Etapa\n",text);if (glui != NULL) glui_edittext->set_text(text);

		TiempoCalculo=Datos_dt ;
		Reiterando=0;
		cout<<"Inicializo Temperaturas = Tambiente "<<endl;
		myfileSalida<<"Inicializo Temperaturas = Tambiente "<<endl;
		TempPilaBloquesPrevia.resize(gtotal->nH3D);
		TempPilaBloques.resize(gtotal->nH3D);
		for (i=0;i<gtotal->nH3D;i++) {
			TempPilaBloquesPrevia[i]=Datos_Tambiente;
			TempPilaBloques[i]=Datos_Tambiente;
		}

PAUSA
		EtapaGlobal=ETAPA_CALCULO_T_PILA; EtapaGlobal2Local=Etapa;Guardar=1;

		if (Reiterando==0) {
			cout<<"============================================================"<<endl;
			myfileSalida<<"============================================================"<<endl;
			if (TipoCalculo==CalculoEvolucion) {
				double tmin=TiempoCalculo/60;
				double thoras=tmin/60;
				cout<<"Calculo para TiempoCalculo= "<<TiempoCalculo<<" seg."<<" = "<<tmin<<" min."<<" = "<<thoras<<" hrs."<<endl;
				myfileSalida<<"Calculo para TiempoCalculo= "<<TiempoCalculo<<" seg."<<" = "<<tmin<<" min."<<" = "<<thoras<<" hrs."<<endl;
			} else {
				cout<<"Calculo Estacionario:"<<endl;
				myfileSalida<<"Calculo Estacionario:"<<endl;
			}
		}

/////////////////////////////////////////////////////////////////////////////////
//   Calculo de temperaturas en la pila : Modelo de Evolucion
//
//
//
		//cout<<"Etapa="<<Etapa<<"IniciEtapa="<<InicioEtapa <<"EtapaGlobal2Local="<<EtapaGlobal2Local<<endl;

		cout<<"------------------------------------------------------"<<endl;
		myfileSalida<<"------------------------------------------------------"<<endl;

		printf("Etapa: Calculo T° en la Pila, con err0=%e",err0);cout<<endl;
		myfileSalida<<"Etapa: Calculo T° en la Pila, con err0="<<err0<<endl;

		if (TipoCalculo==CalculoEvolucion) {
			sprintf(text,"%sCalculo T en Pila (t=%.0f err0=%.2e)\n",text,TiempoCalculo,err0);if (glui != NULL) glui_edittext->set_text(text);
		} else {
			sprintf(text,"%sCalculo T en Pila Estacionario (err0=%.2e)\n",text,err0);if (glui != NULL) glui_edittext->set_text(text);

		}
		if (glui != NULL) PanelFlimite->enable();
		double err2,minTemp,maxTemp;

		printf("numero de celdas=%d",gtotal->nH3D);cout<<endl;
		myfileSalida<<"numero de celdas="<<gtotal->nH3D<<endl;
		PotencialVInfiltracion.resize(gtotal->nH3D);
		TempPilaBloques.resize(gtotal->nH3D);
		UU2.resize(gtotal->nH3D);
		VV2.resize(gtotal->nH3D);
		WW2.resize(gtotal->nH3D);
		TempPilaVertices.resize(gtotal->nV3D);
		for (i=0;i<gtotal->nH3D;i++) {
			PotencialVInfiltracion[i]=gtotal->h3D[i].centro.z*Datos_Vinyeccion;
		}

		//// Esta funcion hace el calculo de TempPilaBloques hasta que el error sea < err0
		err2=CalculaTemperaturaPilaEnTmasDt(TempPilaBloques,PotencialVInfiltracion,UU2,VV2,WW2,
				*gtotal,gtotal->nH3D,err0,TempPilaBloquesPrevia);


		F.resize(gtotal->nV3D);
		F2Nodos.resize(gtotal->nV3D);
		CopiaBloquesAVertices(TempPilaBloques,F2Nodos,&minTemp,&maxTemp,1);


		minTemp=maxTemp=TempPilaBloques[0];
		for (i=0;i<gtotal->nH3D;i++) {
			if (minTemp>TempPilaBloques[i]) minTemp=TempPilaBloques[i];
			if (maxTemp<TempPilaBloques[i]) maxTemp=TempPilaBloques[i];
		}
//		printf("min,max TempPilaBloques=%f, %f, errABS=%g (%d)",minTemp,maxTemp,err2,gtotal->nH3D);cout<<endl;

//		sprintf(text,"%sminT=%.2f maxT=%.2f\n errS=%.2e\n",text,minTemp,maxTemp,err2);if (glui != NULL) glui_edittext->set_text(text);

		printf("minTemp=%f\tmaxTemp=%f (int)\terrT=%.2e",minTemp,maxTemp,err2);cout<<endl;
		myfileSalida<<"minTemp="<<minTemp<<"\tmaxTemp="<<maxTemp<<" (int)\terrT="<<err2<<endl;

		sprintf(text,"%s(errT=%.2e)\n",text,err2);if (glui != NULL) glui_edittext->set_text(text);

		sprintf(text,"%sminT=%.2f maxT=%.2f (int)\n",text,minTemp,maxTemp);if (glui != NULL) glui_edittext->set_text(text);


		CopiaBloquesAVertices(TempPilaBloques,F,&minTemp,&maxTemp,2);
		CopiaBloquesAVertices(TempPilaBloques,F2Nodos,&minTemp,&maxTemp,2);



		printf("minTemp=%f\tmaxTemp=%f (wBC)\terrT=%.2e",minTemp,maxTemp,err2);cout<<endl;
		myfileSalida<<"minTemp="<<minTemp<<"\tmaxTemp="<<maxTemp<<" (wBC)\terrT="<<err2<<endl;

		sprintf(text,"%sminT=%.2f maxT=%.2f (wBC)\n",text,minTemp,maxTemp);if (glui != NULL) glui_edittext->set_text(text);


		calculaFracionVolumen(TempPilaBloques) ;

		err0=err2*1e-4;
		if (err0<ErrorMax_Cada_t) err0=ErrorMax_Cada_t;

		Reiterando=0;
		if (err2>ErrorMax_Cada_t) {
			cout<<"Reitero..."<<endl;
			myfileSalida<<"Reitero..."<<endl;
			Reiterando=1;
			Etapa=InicioEtapa-1;
		} else {
			// Termine con el calculo para este Tiempo
			if (TipoCalculo==CalculoEvolucion) {
				cout<<"Termine con el calculo para este Tiempo"<<endl;
				myfileSalida<<"Termine con el calculo para este Tiempo"<<endl;

				//cout<<"CalculoContinuo="<<CalculoContinuo<<endl;
				if (CalculoContinuo) {
					GuardarInstantanea();
					Guardar=0;
				}

				TiempoCalculo += Datos_dt ;
				if (TiempoCalculo<=Datos_Tmax) {
					//Paso al Tiempo siguiente....
					//err0=1e-10;
					for (i=0;i<gtotal->nH3D;i++) {
						TempPilaBloquesPrevia[i]=TempPilaBloques[i];
					}
					cout<<"Paso al T= "<<TiempoCalculo<<" seg"<<endl;
					myfileSalida<<"Paso al T= "<<TiempoCalculo<<" seg"<<endl;
					Etapa=InicioEtapa-1;

				} else {
					TipoCalculo=CalculoEstacionario;

					cout<<"Terminé evolucion: Comienzo caso Estacionario..."<<endl;
					myfileSalida<<"Terminé evolucion: Comienzo caso Estacionario..."<<endl;
					err0=1e-10;
					Etapa=InicioEtapa-1;
				}
			}
		}

		sprintf(text,"%sFin Etapa\n",text);

		if (glui != NULL) glui_edittext->set_text(text);

PAUSAF
		cout<<"Fin"<<endl;

		EtapaGlobal=EtapaFIN;

		FinEtapas=1;
		CalculoContinuo=0;
		sprintf(text,"%sNada mas\n",text);if (glui != NULL) glui_edittext->set_text(text);
		Etapa--;

		PAUSAF
		cout<<"Etapa: Nada mas"<<endl;

		EtapaGlobal=EtapaFIN;

		FinEtapas=1;
		CalculoContinuo=0;
		sprintf(text,"%sNada mas\n",text);if (glui != NULL) glui_edittext->set_text(text);
		Etapa--;

		PAUSAF
		cout<<"Etapa: Nada mas"<<endl;

		EtapaGlobal=EtapaFIN;

		FinEtapas=1;
		CalculoContinuo=0;
		sprintf(text,"%sNada mas\n",text);if (glui != NULL) glui_edittext->set_text(text);
		Etapa--;


	}


#ifdef NODEF
	F.init(gtotal->nV3D);
	U.init(gtotal->nV3D);
	V.init(gtotal->nV3D);
	W.init(gtotal->nV3D);

	for (i=0;i<gtotal->nV3D;i++) {
		float x,y,z;
		x=gtotal->v3D[i].x;
		y=gtotal->v3D[i].y;
		z=gtotal->v3D[i].z;
		F[i]=sqrt(x*x+z*z);
		U[i]=-y;
		V[i]=x;
		W[i]=x/20;
	}
#endif
}


void NuevaLecturaDeDatos() {


#if defined _WIN32 || defined _WIN64s

	string fname = GetFileName( "Number which file: " );
/*	ifstream ifs( fname.c_str() );
	if ( ! ifs.is_open() ) {
		cerr << "cannot open " << fname << " for input" << endl;
	}
	else {
	*/
		strcpy(file_name,fname.c_str());
		SaveOrRead(file_name,SaveReadMode);

		if (SaveReadMode==2) { //2:read
			sprintf(text,"%s\nEtapa=%d\n",file_name,Etapa);
			glui_edittext->set_text(text);glui_edittext->redraw_window();
			glui->refresh();
//			glutSetWindow(main_window);
//			glutPostRedisplay();
		}
		/*
		string line;
		int lineno = 1;
		while( getline( ifs, line ) ) {
			cout << setw(5) << right << lineno++ << " : " << line << "\n";
		}
		*/
	//}
#endif

}

#if defined(GLUI_GLUI_H)
void control_cb_file( int control )
{
	printf( "\control_cb_file(%d)", control );cout<<endl;
	if (control==0) {
		glui_hide=1;
		glui->hide();
	}
	if (control==7) {
		strcpy(file_name,fb->archivo);
		cout <<"\nfile_name=" <<file_name<<endl;

		glui2->hide();
		SaveOrRead(file_name,SaveReadMode);

		if (SaveReadMode==2) { //2:read
			sprintf(text,"%s\nEtapa=%d\n",file_name,Etapa);
			glui_edittext->set_text(text);glui_edittext->redraw_window();
			glui->refresh();
			glutSetWindow(main_window);
			glutPostRedisplay();
		}

		//				glui2->show();
	}
}

void control_cb( int control )
{

	glui->sync_live();

#if DBG==1
	printf( "control_cb: %d", control );cout<<endl;
#endif
	if (control==0) {
		glui_hide=1;
		glui->hide();
	}
	if (control==7) {
		string file_name;
		file_name = "";
		file_name = fb->get_file();
#if DBG==1
		cout <<"\nfile_name=" <<file_name<<endl;
#endif
	}


	if (control==1002) {  // Save
		SaveReadMode=1;
		NuevaLecturaDeDatos();
		/*
		fb->entrando=1;
		fb->EditText_archivo->orig_text="";

		fb->fbreaddir(".");
		fb->execute_callback();
		glui2->show();
		*/

	}
	if (control==1003) {  // Read
		SaveReadMode=2;
		/*
		fb->EditText_archivo->orig_text="";
		fb->entrando=1;
		fb->fbreaddir(".");
		fb->execute_callback();
		glui2->show();
*/
		NuevaLecturaDeDatos();



	}

	if (control==1102) {  // Plot Particulas
//		MODO_Ejes=!MODO_Ejes;
	}

	if (control==1101) {  // Plot Particulas
//		MODO_CampoVelocidades=!MODO_CampoVelocidades;
	}

	if (control==11030) {  //Previo a 1103
		int i,j,nt,tmp;
		nt=gtotal->Cara.size();
		AlgunosI.resize(nt);
		AlgunosRND.resize(nt);
		for(i=0;i<nt;i++) {
			AlgunosI[i]=i;
			AlgunosRND[i]=rand();
		}
		for(i=0;i<nt;i++) {
			for (j=0;j<nt;j++) {
				if (AlgunosRND[i]<AlgunosRND[j]) {
					tmp=AlgunosRND[i];
					AlgunosRND[i]=AlgunosRND[j];
					AlgunosRND[j]=tmp;
					tmp=AlgunosI[i];
					AlgunosI[i]=AlgunosI[j];
					AlgunosI[j]=tmp;
				}
			}
		}
		control=1103;
	}
	if (control==1103) {  //

		cout<< "ModoDibujaAlgunos="<< ModoDibujaAlgunos<<endl;
		if (ModoDibujaAlgunos) {
			int i,cuantos=10,j;
			cuantos=Algunos_Porcentaje*gtotal->Cara.size()/100;
			CualesCarasDibuja.resize(cuantos);
			cuantos=gtotal->h3D.size()/3;
			cuantos=std::min(500,cuantos);
			CualesBloquesDibuja.resize(cuantos);
//			cout <<"gtotal->nH3D="<<gtotal->nH3D<<endl;
//			int rmax=0;
			for (i=0;i<CualesCarasDibuja.size();i++) {
				CualesCarasDibuja[i]=AlgunosI[i];
				//				rmax=max(rmax,CualesCarasDibuja[i]);
			}
			for (i=0;i<CualesBloquesDibuja.size();i++) {
				CualesBloquesDibuja[i]=rand()*gtotal->h3D.size()/RAND_MAX;
//				rmax=max(rmax,CualesCarasDibuja[i]);
			}
//			cout<<"rmax="<<rmax<<endl;

		}
	}

	if (control==1105) {  //Calculo la proporcion de volument sobre TLimite

		cout<<"cb: Calcular proporcion de volumen sobre TLimite, EtapaGlobal="<<EtapaGlobal<<endl;
		if(EtapaGlobal==ETAPA_CALCULO_T_ARRIBA)
			calculaFracionVolumen(Temperatura);
		if(EtapaGlobal==ETAPA_CALCULO_T_PILA)
			calculaFracionVolumen(TempPilaBloques);
	}

	if (control==1001) Calculo_EtapaS();

	if (control==9001) { // TestDeVariables
		vecUEsfera[0]=0;
		vecUEsfera[1]=0;
		vecUEsfera[2]=0;
	}

	if (control==9002) { // TestDeVariables


		cout<<"M \nGlobalOldFovy="<<GlobalOldFovy<<" GlobalFovy="<<GlobalFovy<<endl;
		cout<<"M A1 vecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<","<<vecUEsfera[3]<<"]"<<endl;


#if (1==1)
		GLdouble xP,yP,zP,xW,yW,zW;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective((GLdouble)GlobalOldFovy, aspect, (GLdouble)1, (GLdouble)100.0);
		glTranslated( 0, 0, -10);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated( 0, -1, -10);

		FuncionesOpenGL::World2Win((GLdouble)vecUEsfera[0], (GLdouble)vecUEsfera[1], (GLdouble)vecUEsfera[2],
				&xP,&yP,&zP);
		cout<<"M xyzP=[ "<<xP<<" , "<<yP<<" , "<<zP<<" ]"<<endl;
		cout<<"M A2 vecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<","<<vecUEsfera[3]<<"]"<<endl;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective((GLdouble)GlobalFovy, aspect, (GLdouble)1, (GLdouble)100.0);
		glTranslated( 0, 0, -10);
		FuncionesOpenGL::Win2World(xP,yP,zP, &xW,&yW,&zW);
		vecUEsfera[0]=xW;
		vecUEsfera[1]=yW;
		vecUEsfera[2]=zW;
		cout<<"M A3 vecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<","<<vecUEsfera[3]<<"]"<<endl;


#else

		glGetDoublev( GL_PROJECTION_MATRIX, FuncionesOpenGL::projection );
		//Coordenadas screen= Projection*(Old)vecU
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated( 0, -1, -10);
		glGetDoublev( GL_PROJECTION_MATRIX, FuncionesOpenGL::modelview);

		MatrizTrXvector4(FuncionesOpenGL::modelview,vecUEsfera,vecDUEsfera);  //Eye_Coord
		MatrizTrXvector4(FuncionesOpenGL::projection,vecDUEsfera,vecUEsfera); //Clip_Coord
//		vecUEsfera[0] /= vecUEsfera[3];
//		vecUEsfera[1] /= vecUEsfera[3];
//		vecUEsfera[2] /= vecUEsfera[3];
//		vecUEsfera[3] /= vecUEsfera[3];
		cout<<"M BvecDUEsfera=["<<vecDUEsfera[0]<<","<<vecDUEsfera[1]<<","<<vecDUEsfera[2]<<","<<vecDUEsfera[3]<<"]"<<endl;
		cout<<"M CvecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<","<<vecUEsfera[3]<<"]"<<endl;

		//Encuentra nuevas matrices

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective((GLdouble)GlobalFovy, aspect, (GLdouble)1, (GLdouble)100.0);
		glTranslated( 0, 0, -10);
		glGetDoublev( GL_PROJECTION_MATRIX, FuncionesOpenGL::projection );

		InvierteMatriz(FuncionesOpenGL::projection,MatrizINV);
		MatrizTrXvector4(MatrizINV,vecUEsfera,vecDUEsfera);
		InvierteMatriz(FuncionesOpenGL::modelview,MatrizINV);
		MatrizTrXvector4(MatrizINV,vecDUEsfera,vecUEsfera);
		//		MatrizXvector4(FuncionesOpenGL::projection,vecDUEsfera,vecUEsfera);
#endif

		cout<<"M BvecDUEsfera=["<<vecDUEsfera[0]<<","<<vecDUEsfera[1]<<","<<vecDUEsfera[2]<<","<<vecDUEsfera[3]<<"]"<<endl;
		cout<<"M FvecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<","<<vecUEsfera[3]<<"]"<<endl;
			Escala *= GlobalFovy/GlobalOldFovy;
		GlobalOldFovy=GlobalFovy;
	}


	if (control==10001) {
		char *str,str2[1000],str3[1000];
		str=(char *)Glui3_EditParametros->get_text();
		cout<<"str="<<str<<endl;

		glui3->hide();
		char nombre[100];
		double valor;

		string snombre,svalor,linea;

		snombre=str;
		istringstream is1( snombre );


		while (getline(is1,linea)) {
			if(DBG) cout<<"linea="<<linea<<endl;
			istringstream trozo( linea );
			string snombre,svalor;
			if (linea[0]=='#') continue;
			if (!getline( trozo, snombre, '=' )) continue;
			replaceAll(snombre, "\t","");
			replaceAll(snombre, " ","");
			if (!getline( trozo, svalor, '\n' )) continue;
			double ff=atof(svalor.c_str());

			if 		(snombre=="malla"			) {CualMalla		=ff;}
			else if (snombre=="CalculoContinuo"	) {CalculoContinuo	=ff;}
			else if (snombre=="TipoCalculo"	    ) {TipoCalculo   	=ff;}
			else if (snombre=="nR"				) {nR				=ff;}
			else if (snombre=="nR2"				) {nR2				=ff;}
			else if (snombre=="nTh"				) {nTh				=ff;}
			else if (snombre=="NDivZ"			) {NDivZ			=ff;}
			else if (snombre=="Dominio_Xmax"	) {Dominio_Xmax		=ff;}
			else if (snombre=="Dominio_Hmax"	) {Dominio_Hmax		=ff;}
			else if (snombre=="Dominio_Hsup"	) {Dominio_Hsup		=ff;}
			else if (snombre=="Dominio_Rint"	) {Dominio_Rint		=ff;}
			else if (snombre=="rhof"			) {Datos_rhof		=ff;}
			else if (snombre=="rhos"			) {Datos_rhos		=ff;}
			else if (snombre=="phi"				) {Datos_phi		=ff;}
			else if (snombre=="cf"				) {Datos_cf			=ff;}
			else if (snombre=="Tinyeccion"		) {Datos_Tinyeccion	=ff;}
			else if (snombre=="Tambiente"		) {Datos_Tambiente	=ff;}
			else if (snombre=="TLimite" 		) {TLimite      	=ff;}
			else if (snombre=="hc_superior"		) {Datos_hc_superior=ff;}
			else if (snombre=="hc_inferior"		) {Datos_hc_inferior=ff;}
			else if (snombre=="hc_lateral"		) {Datos_hc_lateral	=ff;}
			else if (snombre=="KTermofilm"		) {Datos_KTermofilm	=ff;}
			else if (snombre=="eTermofilm"		) {Datos_eTermofilm	=ff;}
			else if (snombre=="VinyeccionLtsHr"	) {VinyeccionLtsHr	=ff;}
			else if (snombre=="kf"				) {Datos_kf			=ff;}
			else if (snombre=="ks"				) {Datos_ks				=ff;}
			else if (snombre=="Kevaporacion"	) {Datos_Kevaporacion	=ff;}
			else if (snombre=="HumedadAmbiental") {Datos_HumedadAmbiental=ff;}
			else if (snombre=="DistanciaAlBorde") {Datos_DistanciaAlBorde=ff;}
			else if (snombre=="CalorLatenteFluido") {Datos_CalorLatenteFluido=ff;}
			else {
				cout <<"Comando en Archivo de datos no considerado:"<<endl;
				cout <<"variable="<< snombre<<"\t="<<ff<<endl;
			}



		}

	}
	if (control==10002) {
		glui3->hide();
	}


	if (control==2223) 		{
#if DBG==1
		if (DBG) cout <<"nParticulas="<<nParticulas<<endl;
#endif
		primerdrawVelGL=1;
	}
	else if (control>100 && control <10000) CB_keyboard(control-100);

}
#endif

int main(int argc,char **argv)
{
#if DBG==1
	if (DBG) cout<<"Linea 479"<<endl;
#endif
	glutInit(&argc, argv);




	gtotal=new grid3D;

	//------------------Linea de comandos
	strcpy(FDatos,"Datos.txt");
	int i;
	cout<<"argc="<<argc<<endl;
	cout<<"argv[0]="<<argv[0]<<endl;
	cout<<"_getcwd="<<getcwd<<endl;

	char cCurrentPath[FILENAME_MAX];


	 if (!getcwd(cCurrentPath, sizeof(cCurrentPath)))
	     {
	     return errno;
	     }

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	printf ("The current working directory is %s\n", cCurrentPath);

	sprintf(mensajes0,"argc=%d\n",argc);
	sprintf(mensajes0,"argv[0]=%s\n",argv[0]);
	if (argc<=1) LecturaArchivoDeDatos();
	for (i=1;i<argc;i++) {
#if DBG>0
		cout<<"argv[i]="<<argv[i]<<endl;
#endif

		if (strcmp(argv[i],"-Datos")==0) {
			strcpy(FDatos,argv[i+1]);i++;
			LecturaArchivoDeDatos();
		}
		else if (strcmp(argv[i],"-malla")==0     		) {CualMalla			=atoi(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-NDivZ")==0			) {NDivZ				=atoi(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-CalculoContinuo")==0	) {CalculoContinuo=1;}
		else if (strcmp(argv[i],"-TipoCalculo")==0	    ) {TipoCalculo          =atoi(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-dt")==0				) {Datos_dt				=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Tmax")==0				) {Datos_Tmax			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-nR")==0				) {nR					=atoi(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-nR2")==0				) {nR2					=atoi(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-nTh")==0				) {nTh					=atoi(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Dominio_Xmax")==0		) {Dominio_Xmax			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Dominio_Hmax")==0		) {Dominio_Hmax			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Dominio_Hsup")==0		) {Dominio_Hsup			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Dominio_Rint")==0		) {Dominio_Rint			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Dominio_Rmed")==0		) {Dominio_Rmed			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-rhof")==0				) {Datos_rhof			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-rhos")==0				) {Datos_rhos			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-phi")	==0				) {Datos_phi			=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-cf")==0				) {Datos_cf				=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-cs")==0				) {Datos_cs				=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Tinyeccion")==0		) {Datos_Tinyeccion		=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Tambiente")==0		) {Datos_Tambiente		=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-TLimite")==0	    	) {TLimite	            =atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-hc_superior")==0		) {Datos_hc_superior	=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-hc_inferior")==0		) {Datos_hc_inferior	=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-hc_lateral")==0		) {Datos_hc_lateral		=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-KTermofilm")==0		) {Datos_KTermofilm		=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-eTermofilm")==0		) {Datos_eTermofilm		=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-VinyeccionLtsHr")==0	) {VinyeccionLtsHr		=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-kf")==0				) {Datos_kf				=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-ks")==0				) {Datos_ks				=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-Kevaporacion")==0		) {Datos_Kevaporacion	=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-HumedadAmbiental")==0	) {Datos_HumedadAmbiental=atof(argv[i+1]);i++;}
		else if (strcmp(argv[i],"-DistanciaAlBorde")==0	) {Datos_DistanciaAlBorde=atof(argv[i+1]);i++;}




	}

	//cout<<"nR2="<<nR2<<endl;

	myfileDBG.open ("DBG");

	if (CalculoContinuo==1) {

		time_t _tm =time(NULL );

		struct tm * curtime = localtime ( &_tm );


		sprintf(nombre0,"/Soluciones/Sal_%02d.%02d_%02d.%02d.%02d_Malla=%d_nR=%d_nTg=%d_NDivZ=%d_",
				curtime->tm_mon+1,curtime->tm_mday,
				curtime->tm_hour,curtime->tm_min,curtime->tm_sec,CualMalla,nR,nTh,NDivZ);


		sprintf(nombre0,"/Soluciones/Sal_%02d.%02d_%02d.%02d.%02d_",
				curtime->tm_mon+1,curtime->tm_mday,
				curtime->tm_hour,curtime->tm_min,curtime->tm_sec);


		char nombre[100];
		sprintf(nombre,"%s_t_porcentaje.dat",nombre0);


		mkdir("/Soluciones", 0755 );
		rmdir(nombre);


		myfileVol.open (nombre);
		sprintf(nombre,"%s_Salida.dat",nombre0);
		rmdir(nombre);
		myfileSalida.open (nombre);

		myfileSalida<<mensajes0;


		sprintf(nombre,"%s_Etapa=%02d_Parametros.dat",nombre0,0);
		rmdir(nombre);
		ofstream myfile;
		myfile.open (nombre);


		LecturaArchivoDeDatos_Post(myfile);
		myfile.close();

		Calculo_EtapaS();
		while(FinEtapas==0) {

#if DBGMain
			cout<<"\n-----------------------------------------------------------------------"
					<<"\nmain():[1080] Guardar="<<Guardar<<"\tEtapa"<<Etapa<<endl;
#endif
			Calculo_EtapaS();
#if DBGMain
			cout<<"\nmain():[1082] Guardar="<<Guardar<<"\tEtapa"<<Etapa<<endl;
#endif
			if (Guardar) {

				GuardarInstantanea();
			}
		}

	} else {
		//---------------------------

		LecturaArchivoDeDatos_Post(cout);
		int anchoT,altoT;

		anchoT=glutGet(GLUT_SCREEN_WIDTH);if (anchoT>1980) anchoT=1980;

		altoT=glutGet(GLUT_SCREEN_HEIGHT);

		printf("ancho=%d, alto=%d\n",anchoT,altoT);cout<<endl;

		width=anchoT-10*0;
		height=altoT-40*0;
		glutInitWindowSize(width, height);

		glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

		main_window =glutCreateWindow("VersionGLUT-cubo");

		glutPositionWindow(glutGet(GLUT_SCREEN_WIDTH)-width-5, glutGet(GLUT_SCREEN_HEIGHT)-height-5);




		/// #AQUI

		inicializacion(); ///Se leen los datos físicos del problema



#if FREEGLUT
		glutMouseWheelFunc(CB_mouse_whell);
#endif
		glutMouseFunc(CB_mouse);
		glutMotionFunc(CB_motion);
		glutKeyboardFunc(CB_keyboard);
		glutSpecialFunc( CB_keyboardSpecial );



		glutVisibilityFunc(visible);
		//  glutKeyboardUpFunc(keyup);
		//  glutSpecialUpFunc(specialup);

#if DBG==1
		if (DBG) cout<<"Inicio3+"<<endl;
#endif
#if defined(GLUI_GLUI_H)
#if DBG==1
		if (DBG) cout<<"Inicio3+"<<endl;
#endif
		GLUI_Master.set_glutReshapeFunc( ResizeGraphics );
#if DBG==1
		if (DBG) cout<<"Inicio3+"<<endl;
#endif
		//	GLUI_Master.set_glutKeyboardFunc(CB_keyboard);

#if DBG==1
		if (DBG) cout<<"Inicio3++"<<endl;
#endif
		formulario_glui();

#if DBG==1
		if (DBG) cout<<"Inicio3++"<<endl;
#endif
#else
		glutReshapeFunc(ResizeGraphics);
#endif

		//	glutSetCursor(GLUT_CURSOR_CYCLE);

		glutDisplayFunc(DrawGraphics);
#if DBG==1
		if (DBG) cout<<"Inicio4"<<endl;
#endif
		glutMainLoop();
		printf("hola");

	}
	exit(0);
}

void GuardarInstantanea() {
	char nombre[100];
	int tmp=InicioEtapa;
	InicioEtapa=EtapaGlobal2Local;
	if (TipoCalculo==CalculoEstacionario) {
		sprintf(nombre,"%s_Etapa=%02d_Size=%d.dat",nombre0,EtapaGlobal,gtotal->nH3D);
	} else {
		sprintf(nombre,"%s_Etapa=%02d_Size=%d_t=%.0f.dat",nombre0,EtapaGlobal,gtotal->nH3D,TiempoCalculo);
	}
	rmdir(nombre);


	cout<<"Save:"<<nombre<<endl;
	myfileSalida<<"Save:"<<nombre<<endl;

#if DBGMain
	cout<<"EtapaGlobal2Local="<<EtapaGlobal2Local<<endl;

#endif
	SaveOrRead(nombre,1);


	InicioEtapa=tmp;
}



#if defined(GLUI_GLUI_H)
void   formulario_glui()
{
	GLUI_Spinner *tsp;
	/////GLUI:
	//	glui = GLUI_Master.create_glui( "GLUI", 0, 90, 90 ); // name, flags, x, and y

	glui = GLUI_Master.create_glui_subwindow(main_window,GLUI_SUBWINDOW_RIGHT);
	glui->set_main_gfx_window( main_window);


	GLUI_Panel *mipanel=glui->add_panel("Clipping");

	gluiClipping = glui->add_checkbox_to_panel(mipanel,"'P'= Clipping",&ClippingON, 'P'+100 ,control_cb );

	tsp=glui->add_spinner_to_panel( mipanel, "Ax:" ,GLUI_SPINNER_FLOAT, &Ax );
	tsp->set_alignment(GLUI_ALIGN_LEFT);	tsp->w=10;
	cout<<"Antes set_w ....."<<endl;
	tsp=glui->add_spinner_to_panel( mipanel, "+By:",GLUI_SPINNER_FLOAT, &By );
	tsp->set_alignment(GLUI_ALIGN_LEFT);	tsp->w=10;
	tsp=glui->add_spinner_to_panel( mipanel, "+Cz:",GLUI_SPINNER_FLOAT, &Cz );
	tsp->set_alignment(GLUI_ALIGN_LEFT);	tsp->w=10;
	tsp=glui->add_spinner_to_panel( mipanel, " =D:" ,GLUI_SPINNER_FLOAT, &DD );
	tsp->set_alignment(GLUI_ALIGN_LEFT);	tsp->w=10;
	cout<<"Despues set_w"<<endl;


	PanelFlimite = glui->add_panel("",GLUI_PANEL_EMBOSSED);
	GLUI_Panel *ptmp2 = glui->add_panel_to_panel(PanelFlimite,"",GLUI_PANEL_NONE);
//	ptmp->set_alignment(GLUI_ALIGN_LEFT);
	glui->add_checkbox_to_panel(ptmp2,"TLimite",&TLimite_if);
	glui->add_column_to_panel(ptmp2,false);
	tsp=glui->add_spinner_to_panel(ptmp2,"" ,GLUI_SPINNER_FLOAT, &TLimite , 1105, control_cb );


	glui_porcentaje=glui->add_statictext_to_panel(PanelFlimite,"");

	PanelFlimite->disable();



	ptmp2 = glui->add_panel("",GLUI_PANEL_NONE);
	glui->add_button_to_panel(ptmp2,"Save", 1002 ,control_cb );
	glui->add_column_to_panel(ptmp2,false);
	glui->add_column_to_panel(ptmp2,false);
	glui->add_button_to_panel(ptmp2,"Read", 1003 ,control_cb );

	gluiMueve		=glui->add_checkbox("[M] Mueve centro",&MueveCentro);
	//	gluiNumera		=glui->add_checkbox("'N' Numera Vertices(on/off)",NULL, 'N'+100 ,control_cb );
	glui->add_checkbox("[ ] Ejes ",&MODO_Ejes, 1102 ,control_cb);
	//glui->add_checkbox("[ ] Vel ",&MODO_CampoVelocidades2);
//	gluiNormales		=glui->add_checkbox("[N] Normales ",&ModoDibujaNormales);
	gluiInterior		=glui->add_checkbox("[I] Interior ",&ModoDibujaInterior);
	gluiBordes		=glui->add_checkbox("[B] Bordes ",&ModoDibujaFrontera);
	glui->add_checkbox("[ ] centros ",&Modo_DibujaCentroBloques);

	glui->add_checkbox("Algunos ",&ModoDibujaAlgunos, 11030 ,control_cb);
	Spinner_Algunos =tsp=glui->add_spinner("Porcentaje",GLUI_SPINNER_INT, &Algunos_Porcentaje,1103,control_cb);

	tsp->set_int_limits(0,100);

	glui->add_statictext( "" );

	TesteDeVariablesGlobales();


	glui->add_statictext( "" );
	glui->add_button("Etapa Siguiente [Space]", 1001 ,control_cb );
	glui->add_statictext( "" );


	PanelParticulas = glui->add_panel("",GLUI_PANEL_EMBOSSED);
	Checkbox_particulas=glui->add_checkbox_to_panel(PanelParticulas,"Particulas ?",&MODO_CampoVelocidades, 1101 ,control_cb );
	glui->add_checkbox_to_panel(PanelParticulas,"Origen",&MODO_Origen);
	glui->add_checkbox_to_panel(PanelParticulas,"Pausa",&MODO_Pausa);


	Spinner_particulas =tsp=glui->add_spinner_to_panel(PanelParticulas,"N Particulas",GLUI_SPINNER_INT, &nParticulas,2223,control_cb);

	tsp->set_int_limits(1,6000);
//	tsp=glui->add_spinner("Factor[0,1]",GLUI_SPINNER_FLOAT, &FactorCercania );
//	tsp->set_int_limits(0,1);
	tsp=glui->add_spinner_to_panel(PanelParticulas,"Lento=",GLUI_SPINNER_INT, &npasadas );
	tsp->set_int_limits( 1, maxpasadas);
	//	tsp->edittext->set_w(0);




//	glui->add_spinner("[ ]=FactV",GLUI_SPINNER_FLOAT, &factorV );
	glui->add_spinner_to_panel(PanelParticulas,"Factor Vh",GLUI_SPINNER_FLOAT, &factorVh );

	glui->add_statictext( "" );
//	glui->add_statictext( "");
	glui_FPS=glui->add_statictext( "FPS" );
	glui_FPS->set_alignment(GLUI_ALIGN_CENTER);
//	glui_MSG=glui->add_statictext( "" );
//	glui_MSG->set_alignment(GLUI_ALIGN_LEFT);


	glui_edittext= new GLUI_TextBox(glui,text);
	glui_edittext->set_w(220);
	glui_edittext->set_h(120);

	cout<<"formulario_glui()2"<<endl;

	mipanel=glui->add_panel("Uso del Boton 1 del Mouse");
	glui_GrupoModoDelMouse=glui->add_radiogroup_to_panel(mipanel,&MODO_de_mover);
	glui->add_radiobutton_to_group(glui_GrupoModoDelMouse,"[t]=Trasladar");
	glui->add_radiobutton_to_group(glui_GrupoModoDelMouse,"[r]=Rotar");
	glui->add_radiobutton_to_group(glui_GrupoModoDelMouse,"[s]=Spin Z");
	glui->add_radiobutton_to_group(glui_GrupoModoDelMouse,"[e]=Escala");


//	glui->add_button("'R'=Reset View", 'R'+100 ,control_cb );  //Eliminado en Version1
	glui->add_button("'F'=Full(on/off)", 'F'+100 ,control_cb );
	//	glui->add_button("'G'=Game", 'g'+100 ,control_cb );
	glui->add_button("'C'=Color", 'C'+100 ,control_cb );


	glui->add_button("[Z]=Hide", 'Z'+100,control_cb );


	gluiHelp		=glui->add_checkbox("[V] Verbose ",&MODO_MenuMENSAJES); //Eliminado en Version 1
	glui->add_checkbox("[ ] NumH ",&MODO_NumeraH);
//	glui->add_checkbox("[ ] NumFF ",&MODO_NumeraFF); //Eliminado en Version 1

	if (1==0) { // Formulario para abrir archivo
		glui2 = GLUI_Master.create_glui("GLUI Window");

		cout<<"glui2->glui_id="<<glui2->get_glut_window_id()<<endl;


		GLUI_Panel *panel2 = glui2->add_panel( "" );
		//		panel2->set_w(300);
		//		panel2->set_h(500);

		new GLUI_StaticText(panel2,"Open File:");
		cout<<"1002"<<endl;
		fb = new GLUI_FileBrowser2(panel2, "", false, 17, control_cb_file);
		cout<<"972"<<endl;
		//fb = new GLUI_FileBrowser(glui2, "", GLUI_PANEL_EMBOSSED, 7, control_cb);
		fb->set_w(300);
		fb->set_h(500);
		cout<<"fb->allow_change_dir="<<fb->allow_change_dir<<endl;
		fb->set_allow_change_dir(1);
		cout<<"fb->allow_change_dir="<<fb->allow_change_dir<<endl;
		glui2->add_column_to_panel(panel2,false);
		//		fb2 = new GLUI_List(panel2, "", GLUI_PANEL_EMBOSSED, 7, control_cb);
		glui2->add_column(false);

		fb->fbreaddir("*.txt");
		//		fbreaddir2(fb, "");
		//		glutPositionWindow(glutGet(GLUT_SCREEN_WIDTH)-10, glutGet(GLUT_SCREEN_HEIGHT)-10);
		glui2->hide();


	}

	if (1==1) { // Formulario para abrir archivo
		glui3 = GLUI_Master.create_glui("GLUI Window");


		GLUI_Panel *panel3 = glui3->add_panel( "P" );


//		glui3->add_edittext_to_panel(panel3, "CalculoContinuo", GLUI_EDITTEXT_INT, &E_CalculoContinuo);
		Glui3_EditParametros= new GLUI_TextBox(panel3, StringParametros);

		Glui3_EditParametros->set_w(320);
		Glui3_EditParametros->set_h(520);
//		Glui3_EditParametros->set_font( GLUT_BITMAP_8_BY_13);


		GLUI_Panel *panel3b = glui3->add_panel( "" );
		panel3b->set_w(320);
		glui3->add_button_to_panel(panel3b,"Cambia", 10001 ,control_cb )->set_alignment(GLUI_ALIGN_LEFT);
		glui3->add_column_to_panel(panel3b,false);
		glui3->add_statictext_to_panel(panel3b,"       ");
		glui3->add_column_to_panel(panel3b,false);
		glui3->add_button_to_panel(panel3b,"Hide", 10002 ,control_cb )->set_alignment(GLUI_ALIGN_RIGHT);

		glui3 ->hide();
	}
	//	glutIdleFunc( idleevent );
	GLUI_Master.set_glutIdleFunc( idleevent );
	//	glui_hide=false;
	//	master->hide(); //Borrar pantalla principal para test


	/*
	GLUI_Control *gluiNode=(GLUI_Control *)glui->main_panel->first_child();
	while (gluiNode!=NULL) {
		cout << "gluiNode->name="<<gluiNode->name<<endl;;
		gluiNode->set_h( gluiNode->h/2);
		gluiNode=(GLUI_Control *)gluiNode->next();
	}
	 */



	//Checkbox_particulas->deactivate();
	Checkbox_particulas->disable();

	PanelParticulas->disable();
	cout<<"formulario_glui()end"<<endl;
}


void TesteDeVariablesGlobales() {

	GLUI_Spinner *tsp;
	GLUI_Panel *ptmp2;
	///// Test de algunas Variables
	tsp=glui->add_spinner("FactorNormales",GLUI_SPINNER_FLOAT, &FactorNormales);
	tsp->set_float_limits(0,1000);
	tsp=glui->add_spinner("FactorSuavidad",GLUI_SPINNER_FLOAT, &FactorSuavidad);
	tsp->set_float_limits(0,1);
	tsp=glui->add_spinner("FactorAchica",GLUI_SPINNER_FLOAT, &FactorAchica);
	tsp->set_float_limits(0,1);
	tsp=glui->add_spinner("FactorZ",GLUI_SPINNER_FLOAT, &FactorZ);
	tsp->set_float_limits(0,1000);
	tsp->set_speed(0.1);

/*
	tsp=glui->add_spinner("Ambient",GLUI_SPINNER_FLOAT, &FactorAmbient);
	tsp->set_float_limits(0,3);
	tsp->set_speed(0.1);

	tsp=glui->add_spinner("Difusse",GLUI_SPINNER_FLOAT, &FactorDifusse);
	tsp->set_float_limits(0,3);
	tsp->set_speed(0.1);

	tsp=glui->add_spinner("Specular",GLUI_SPINNER_FLOAT, &FactorSpecular);
	tsp->set_float_limits(0,3);
	tsp->set_speed(0.1);

	tsp=glui->add_spinner("Emission",GLUI_SPINNER_FLOAT, &FactorEmission);
	tsp->set_float_limits(0,3);
	tsp->set_speed(0.1);

*/



	ptmp2 = glui->add_panel("",GLUI_PANEL_RAISED);
	glui->add_button_to_panel(ptmp2,"Reset centro", 9001 ,control_cb );
	glui->add_column_to_panel(ptmp2,false);
	glui->add_column_to_panel(ptmp2,false);
	glui->add_button_to_panel(ptmp2,"Reset centro2", 9001 ,control_cb );


	tsp=glui->add_spinner("Fovy",GLUI_SPINNER_FLOAT, &GlobalFovy, 9002 ,control_cb);
	tsp->set_float_limits(0.001,90);
	tsp->set_speed(1);

	tsp=glui->add_spinner("SizeCentros",GLUI_SPINNER_FLOAT, &GlobalCentros);
	tsp->set_float_limits(0.001,1);
	tsp->set_speed(1);


}

#endif




#ifdef _WIN32
#include <windows.h>
#endif
void fbreaddir2(GLUI_FileBrowser *fb, const char *d) {
	GLUI_String item;
	int i = 0;


#ifdef _WIN32

	WIN32_FIND_DATAW FN;
	HANDLE hFind;
	//char search_arg[MAX_PATH], new_file_path[MAX_PATH];
	//sprintf(search_arg, "%s\\*.*", path_name);

	hFind = FindFirstFileW(L"*.*", &FN);
	if (fb->list) {
		fb->list->delete_all();
		if (hFind != INVALID_HANDLE_VALUE) {
			do {

				size_t origsize = wcslen(FN.cFileName) + 1;
				const size_t newsize = 100;
				size_t convertedChars = 0;
				char nstring[newsize];
				//			wcstombs_s(&convertedChars, nstring, origsize, FN.cFileName, _TRUNCATE);
				wcstombs(nstring,  FN.cFileName, origsize);



				int len = wcslen(FN.cFileName);
				if (FN.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					item = '\\';
					item += nstring;
					fb->list->add_item(i,item.c_str());
				} else {
					item = nstring;
					//		  fb->list->add_item(i,item.c_str());
				}
				i++;
			} while (FindNextFileW(hFind, &FN) != 0);

			if (GetLastError() == ERROR_NO_MORE_FILES)
				FindClose(&FN);
			else
				perror("fbreaddir");
		}
	}

	hFind = FindFirstFileW(L"*.txt", &FN);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {

			size_t origsize = wcslen(FN.cFileName) + 1;
			const size_t newsize = 100;
			size_t convertedChars = 0;
			char nstring[newsize];
			//			wcstombs_s(&convertedChars, nstring, origsize, FN.cFileName, _TRUNCATE);
			wcstombs(nstring,  FN.cFileName, origsize);



			int len = wcslen(FN.cFileName);
			if (FN.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				item = '\\';
				item += nstring;
				//		  fb->list->add_item(i,item.c_str());
			} else {
				item = nstring;
				fb->list->add_item(i,item.c_str());
			}
			i++;
		} while (FindNextFileW(hFind, &FN) != 0);

		if (GetLastError() == ERROR_NO_MORE_FILES)
			FindClose(&FN);
		else
			perror("fbreaddir");
	}

#elif defined(__GNUC__)

	DIR *dir;
	struct dirent *dirp;
	struct stat dr;

	if (fb->list) {
		fb->list->delete_all();
		if ((dir = opendir(d)) == NULL)
			perror("fbreaddir:");
		else {
			while ((dirp = readdir(dir)) != NULL)   /* open directory     */
			{
				if (!lstat(dirp->d_name,&dr) && S_ISDIR(dr.st_mode)) /* dir is directory   */
					item = dirp->d_name + GLUI_String("/");
				else
					item = dirp->d_name;

				fb->list->add_item(i,item.c_str());
				i++;
			}
			closedir(dir);
		}
	}
#endif
}

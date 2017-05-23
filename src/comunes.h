#pragma once

#if defined _WIN32 || defined _WIN64s
   #define mkdir(x,y) _mkdir((x))
   #define rmdir(x) _rmdir((x))

#endif

#include <sstream>

extern double ThetaMax;

void DrawMensajesRight();

void SaveOrRead(char *ifile_name,int iSaveReadMode);

void control_cb( int control );

void AddMensaje(char* newMensaje)
{
	int i;
	for (i=0;i<NMensajes-1;i++) {
		strcpy(Mensaje[i],Mensaje[i+1]);
	}
	strcpy(Mensaje[NMensajes-1],newMensaje);
}

void AddMensajeRight(char* newMensaje)
{
//	cout<<"M AddMensajeRight(char* "<<newMensaje<<")"<<endl;
	int i;
	if (NMensajeRight==MaxMensajeRight)
		for (i=0;i<NMensajeRight-1;i++) {
			strcpy(MensajeRight[i],MensajeRight[i+1]);
		}
	else
		NMensajeRight++;
//	cout<<"M NMensajeRight="<<NMensajeRight<<endl;
	strcpy(MensajeRight[NMensajeRight-1],newMensaje);
}


void rotacion(float wAngleX,float wAngleY) {
	glLoadIdentity();
	glRotatef(wAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(wAngleY, 0.0f, 1.0f, 0.0f);
	glMultMatrixf((GLfloat *)MatrizRotacionGlobal);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)MatrizRotacionGlobal);
	glLoadIdentity();
	glMultMatrixf((GLfloat *)MatrizRotacionGlobalINV);
	glRotatef(-wAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(-wAngleX, 1.0f, 0.0f, 0.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)MatrizRotacionGlobalINV);
	FuncionesOpenGL::modelview_calculado=false;
}


void MyDBG() {
	int i,dif=0;
	for (i=0;i<16;i++) {
		if (fabs(MatrizRotacionGlobal[i]-MatrizRotacionGlobal0[i])>1e-5) dif=1;
	}
	if (dif>0) {
		myfileDBG << "MatrizRotacionGlobal=";
		for (i=0;i<16;i++) {
			myfileDBG <<MatrizRotacionGlobal[i]<<" ";
			MatrizRotacionGlobal0[i]=MatrizRotacionGlobal[i];
		}
		myfileDBG <<endl;
	}
}

void print_text(int x, int y, char* s) 
{

//	cout<<"M print_text(int "<<x<<", int "<<y<<", char* "<<s<<") "<<endl;
	int lines;
	char* p;
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, width, 
			0, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3ub(128, 0, 255);
	glRasterPos2i(x, y);
	for(p = s; *p; p++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *p);
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void TrasponeMatriz() {

	MatrizRotacionGlobalINV[0]=MatrizRotacionGlobal[0];
	MatrizRotacionGlobalINV[1]=MatrizRotacionGlobal[4];
	MatrizRotacionGlobalINV[2]=MatrizRotacionGlobal[8];
	MatrizRotacionGlobalINV[3]=MatrizRotacionGlobal[12];

	MatrizRotacionGlobalINV[4]=MatrizRotacionGlobal[1];
	MatrizRotacionGlobalINV[5]=MatrizRotacionGlobal[5];
	MatrizRotacionGlobalINV[6]=MatrizRotacionGlobal[9];
	MatrizRotacionGlobalINV[7]=MatrizRotacionGlobal[13];

	MatrizRotacionGlobalINV[8]=MatrizRotacionGlobal[2];
	MatrizRotacionGlobalINV[9]=MatrizRotacionGlobal[6];
	MatrizRotacionGlobalINV[10]=MatrizRotacionGlobal[10];
	MatrizRotacionGlobalINV[11]=MatrizRotacionGlobal[14];

	MatrizRotacionGlobalINV[12]=MatrizRotacionGlobal[3];
	MatrizRotacionGlobalINV[13]=MatrizRotacionGlobal[7];
	MatrizRotacionGlobalINV[14]=MatrizRotacionGlobal[11];
	MatrizRotacionGlobalINV[15]=MatrizRotacionGlobal[15];
}

void CopiaBloquesAVertices(vector<double> FFB,vector<double> &FV,double *minF,double *maxF,int iBC) {
	int i,j;
	vector<int> cuantos(FV.size());
	for (i=0;i<gtotal->nV3D;i++) {
		cuantos[i]=0;
		FV[i]=0;
	}
	for (i=0; i<gtotal->nH3D ; i++) {
		for( j=0 ; j<8 ; j++) {
			int iv=gtotal->h3D[i].iv[j];
			FV[iv] += FFB[i];
			cuantos[iv] ++;
		}
	}

	if (iBC>0) {

		for (i=0; i<gtotal->nCaras ; i++) {
			if (gtotal->Cara[i].iBC ==2 || gtotal->Cara[i].iBC ==3) {
				for (j=0; j<4 ; j++) {
					FV[gtotal->Cara[i].iv[j]]=0;
					cuantos[gtotal->Cara[i].iv[j]]=0;
				}
			}
		}
		for (i=0; i<gtotal->nCaras ; i++) {
			if (gtotal->Cara[i].iBC ==2 || gtotal->Cara[i].iBC ==3) {
				for (j=0; j<4 ; j++) {
					switch (iBC)
					{
					case 1:
						FV[gtotal->Cara[i].iv[j]] += gtotal->Cara[i].BC;
						cuantos[gtotal->Cara[i].iv[j]]++;
						break;
					case 2:
						FV[gtotal->Cara[i].iv[j]] += gtotal->Cara[i].BC2;
						cuantos[gtotal->Cara[i].iv[j]]++;
						if(1==0)
							cout<<"g.Cara[i].BC2="<<gtotal->Cara[i].BC2
							<<"\tcuantos[g.Cara[i].iv[j]]="<<cuantos[gtotal->Cara[i].iv[j]]
																	 <<"g.Cara[i].iv[j]="<<gtotal->Cara[i].iv[j]
																											  <<endl;
						break;
					};
				}
			}
		}
	}

	*maxF=*minF=FV[0]/cuantos[0];
	for (i=0;i<gtotal->nV3D;i++) {
		FV[i] /= cuantos[i];
		if (*minF>FV[i]) {
			*minF=FV[i];
			if(1==0) cout<<"FV[i]="<<FV[i]<<"\tcuantos[i]="<<cuantos[i]<<"\ti="<<i<<endl;
		}
		if (*maxF<FV[i]) *maxF=FV[i];
	}

}

void tic() {



	start_t = clock();

}

void toc() {

	end_t = clock();
	total_t = ((double)(end_t - start_t)) / CLOCKS_PER_SEC;


	cout <<total_t<<" seg";
	if (total_t>60) {
		int min=total_t/60; total_t-=min*60;
		cout<<" ( "<<min<<":"<<total_t<<"min)";
	}
	cout<<endl;
}



void DrawGraphics()
{
	if (DBG) cout<<"DrawGraphics()"<<endl;
	static int contador=0;
	static int nframes2=0;
	char linea[100];
	int i,j;

	if (!DrawYES) return; 
	DrawYES=0;

	if (DBG) cout<<"DrawGraphics()138"<<endl;
	glClear(GL_COLOR_BUFFER_BIT );
	glClear(GL_DEPTH_BUFFER_BIT);


#if DBGMouse
	MyDBG();
#endif

	glDisable(GL_CLIP_PLANE0);
	if (DBG) cout<<"DrawGraphics()143"<<endl;




#if 0
	{
		glPushAttrib( GL_LIGHTING_BIT );
		glDisable( GL_LIGHTING );


		glMatrixMode (GL_MODELVIEW); glPushMatrix (); glLoadIdentity (); 
		glMatrixMode (GL_PROJECTION); glPushMatrix (); glLoadIdentity ();

		glBegin (GL_QUADS); 
		glColor3d(.1, 0, .1);
		glVertex3f (-1, -1, -1.5); glVertex3f (1, -1, -1.5); glVertex3f (1, 1, -1.5); glVertex3f (-1, 1, -1.5); 
		glEnd ();
		glPopMatrix (); glMatrixMode (GL_MODELVIEW); glPopMatrix ();


		glPopAttrib();
	}
#endif
	glClear(GL_DEPTH_BUFFER_BIT);
	if (DBG) cout<<"DrawGraphics()166"<<endl;

	/*
	//Test Ortogonal
	cout<<"MatrizRotacionGlobal="<<endl;
	cout<< MatrizRotacionGlobal[0]<<"\t"<<MatrizRotacionGlobal[1]<<"\t"
			<<MatrizRotacionGlobal[2]<<"\t"<<MatrizRotacionGlobal[3]<<endl;
	cout<< MatrizRotacionGlobal[4]<<"\t"<<MatrizRotacionGlobal[5]<<"\t"
			<<MatrizRotacionGlobal[6]<<"\t"<<MatrizRotacionGlobal[7]<<endl;
	cout<< MatrizRotacionGlobal[8]<<"\t"<<MatrizRotacionGlobal[9]<<"\t"
			<<MatrizRotacionGlobal[10]<<"\t"<<MatrizRotacionGlobal[11]<<endl;
	cout<< MatrizRotacionGlobal[12]<<"\t"<<MatrizRotacionGlobal[13]<<"\t"
			<<MatrizRotacionGlobal[14]<<"\t"<<MatrizRotacionGlobal[15]<<endl;

	cout<<"MatrizRotacionGlobalINV="<<endl;

	cout<< MatrizRotacionGlobalINV[0]<<"\t"<<MatrizRotacionGlobalINV[1]<<"\t"
			<<MatrizRotacionGlobalINV[2]<<"\t"<<MatrizRotacionGlobalINV[3]<<endl;
	cout<< MatrizRotacionGlobalINV[4]<<"\t"<<MatrizRotacionGlobalINV[5]<<"\t"
			<<MatrizRotacionGlobalINV[6]<<"\t"<<MatrizRotacionGlobalINV[7]<<endl;
	cout<< MatrizRotacionGlobalINV[8]<<"\t"<<MatrizRotacionGlobalINV[9]<<"\t"
			<<MatrizRotacionGlobalINV[10]<<"\t"<<MatrizRotacionGlobalINV[11]<<endl;
	cout<< MatrizRotacionGlobalINV[12]<<"\t"<<MatrizRotacionGlobalINV[13]<<"\t"
			<<MatrizRotacionGlobalINV[14]<<"\t"<<MatrizRotacionGlobalINV[15]<<endl;

	 */



//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-10, 10,	-10, 10, -1000, 1000);



	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective((GLdouble)GlobalFovy, aspect, (GLdouble)1, (GLdouble)100.0);

//	glViewport(0, 0, width, height);
	    glTranslated( 0, 0, -10);



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated( 0, -1, -10);

	FuncionesOpenGL::ActivaLuz0();
	glShadeModel(GL_SMOOTH);

	glTranslatef(vecUEsfera[0], vecUEsfera[1],vecUEsfera[2]);

	FuncionesOpenGL::material(0);   FuncionesOpenGL::esfera(0.002*GlobalFovy,20);

	glScalef(Escala, Escala, Escala);
	glMultMatrixf((GLfloat *)MatrizRotacionGlobal);
	glScalef(1, 1, FactorZ);
	//Cursor centro
	//FuncionesOpenGL::material(0);   FuncionesOpenGL::esfera(0.002,20);
	glTranslatef(-vecXEsfera[0],-vecXEsfera[1],-vecXEsfera[2]);

	if (DBG) cout<<"DrawGraphics()209"<<endl;

	if (MODO_Ejes) {
		FuncionesOpenGL::ejes();
	}

	if (ClippingON) {
		double eq[4];
		eq[0]=-Ax;	eq[1]=-By;	eq[2]=-Cz;	eq[3]=DD;
		glClipPlane(GL_CLIP_PLANE0, eq);
		glEnable(GL_CLIP_PLANE0);
	} 
	if (DBG) cout<<"DrawGraphics()221"
			<<"\nColorON="<<ColorON
			<<"\n gtotal="<<gtotal
			<<endl;


	//glEnable(GL_CULL_FACE);
	switch (ColorON)
	{
	case 0:  //Caso Normal
		FuncionesOpenGL::material(1);gtotal->drawGL();
		break;
	case 1:  //Dibuja Campo 1
		gtotal->drawGL(F);
		break;
	case 2:  //Dibuja Campo 2
		gtotal->drawGL(F2Nodos);
		break;
	case 3:
		FuncionesOpenGL::material(1);gtotal->drawGL();
		FuncionesOpenGL::material(2);gtotal->drawVoronoi();
		break;
	};
	if (DBG) cout<<"DrawGraphics()244"<<endl;

	if (MODO_CampoVelocidades) {
//		FuncionesOpenGL::material(0);	gtotal->drawVelGL(U,V,W);
		FuncionesOpenGL::material(0);	gtotal->drawVelGL_TriPrisma(U,V,W);
	}
	if (DBG) cout<<"DrawGraphics()249"<<endl;
	if (MODO_CampoVelocidades2) {
		FuncionesOpenGL::material(1);	gtotal->drawVelGL2(UU,VV,WW);
	}
	if (DBG) cout<<"DrawGraphics()253"<<endl;

	{/////////////////bloque que imprime texto......
		glDisable(GL_CLIP_PLANE0);
		glPushAttrib( GL_LIGHTING_BIT );
		glDisable( GL_LIGHTING );

		if (DBG) cout<<"DrawGraphics()260"
				<<"\n MODO_MenuMENSAJES="<<MODO_MenuMENSAJES
				<<endl;
		if (MODO_MenuMENSAJES)
			DrawMensajes();
		DrawMensajesRight();
		if(1==1) {
			clock2F=clockF=clock ();
			nframes++;nframes2++;
			if (DBG) cout<<"DrawGraphics()267"<<endl;

			FPS=(nframes*1.0)*CLOCKS_PER_SEC/(clockF-clock0);
			FPS2=(nframes2*1.0)*CLOCKS_PER_SEC/(clock2F-clock2);
			if (clockF-clock0>CLOCKS_PER_SEC) {
				glColor3d(.8,.9, 1);
				glRasterPos3f(-2.07*aspect,1.95,5);
				///modificado GLUT
				sprintf(s,"FPS=%.2f (%.2f)\r",FPS2,FPS);//fflush(stdout);
				//sprintf(s,"%.0f F/S",FPS);FuncionesOpenGL::Print(s,1);
				clock0=clockF;
				nframes=0;
				glui_FPS->set_name(s);
				//					printf("%s",s);
			}
			//			print_text(width-150,5,s);

		}
		glPopAttrib();
	}

	glutSwapBuffers();

	DrawYES=1;
	if (DBG) cout<<"DrawGraphics():END"<<endl;

}

void save(vector<double> &F,ofstream &myfile) {
	int i;
	myfile  <<F.size()<<endl;
	for (i=0;i<     F.size();i++) { myfile<<     F[i]<<" "; } myfile<<endl;

}

void read(vector<double> &F,ifstream &myfile) {
	int i,sizeL;
	myfile  >> sizeL; F.resize(sizeL);
	for (i=0;i<F.size();i++) { myfile>>F[i]; }

}

void DrawMensajesDatos()
{
	// Nueva version....
	cout <<"DrawMensajesDatos()"<<endl;
	char str[100];
	int i;


	for (i=0;i<NMensajes;i++) {
		strcpy(Mensaje[i],"");
	}

	i=0;
	sprintf(str,"#Parametros usados:"); strcpy(Mensaje[i],str);i++;
	sprintf(str,"-------------------"); strcpy(Mensaje[i],str);i++;


	sprintf(str,"malla           =%d",CualMalla          ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"CalculoContinuo =%d",CalculoContinuo	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"TipoCalculo     =%d",TipoCalculo    	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"nR	             =%d",nR				    ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"nR2             =%d",nR2				); strcpy(Mensaje[i],str);i++;
	sprintf(str,"nTh             =%d",nTh				); strcpy(Mensaje[i],str);i++;
	sprintf(str,"NDivZ           =%d",NDivZ			    ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"Dominio_Xmax    =%f",Dominio_Xmax	   ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"Dominio_Rint    =%f",Dominio_Rint	   ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"Dominio_Rmed    =%f",Dominio_Rmed	   ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"Dominio_Hmax    =%f",Dominio_Hmax	   ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"Dominio_Hsup    =%f",Dominio_Hsup		); strcpy(Mensaje[i],str);i++;
	sprintf(str,"rhof            =%f",Datos_rhof			); strcpy(Mensaje[i],str);i++;
	sprintf(str,"rhos            =%f",Datos_rhos			); strcpy(Mensaje[i],str);i++;
	sprintf(str,"phi             =%f",Datos_phi			); strcpy(Mensaje[i],str);i++;
	sprintf(str,"cf              =%f",Datos_cf			); strcpy(Mensaje[i],str);i++;
	sprintf(str,"Tinyeccion      =%f",Datos_Tinyeccion	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"Tambiente       =%f",Datos_Tambiente	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"TLimite         =%f",TLimite       	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"hc_superior     =%f",Datos_hc_superior	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"hc_inferior     =%f",Datos_hc_inferior	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"hc_lateral      =%f",Datos_hc_lateral	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"KTermofilm      =%e",Datos_KTermofilm	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"eTermofilm      =%e",Datos_eTermofilm	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"VinyeccionLtsHr =%f",VinyeccionLtsHr	); strcpy(Mensaje[i],str);i++;
	sprintf(str,"kf              =%f",Datos_kf			); strcpy(Mensaje[i],str);i++;
	sprintf(str,"ks              =%f",Datos_ks				 ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"Kevaporacion     =%e",Datos_Kevaporacion	     ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"HumedadAmbiental =%f",Datos_HumedadAmbiental  ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"DistanciaAlBorde =%f",Datos_DistanciaAlBorde  ); strcpy(Mensaje[i],str);i++;
	sprintf(str,"CalorLatenteFluido =%e",Datos_CalorLatenteFluido); strcpy(Mensaje[i],str);i++;

}


void DrawMensajesDatosGui3()
{
	// Nueva version....
	char str[100];
	int i;

	sprintf(StringParametros,"#Parametros usados:\n");


	sprintf(StringParametros,"%smalla           =%d\n",StringParametros,CualMalla           );
	sprintf(StringParametros,"%sCalculoContinuo =%d\n",StringParametros,CalculoContinuo	    );
	sprintf(StringParametros,"%sTipoCalculo     =%d\n",StringParametros,TipoCalculo	        );
	sprintf(StringParametros,"%snR              =%d\n",StringParametros,nR				    );
	sprintf(StringParametros,"%snR2             =%d\n",StringParametros,nR2				    );
	sprintf(StringParametros,"%snTh             =%d\n",StringParametros,nTh				    );
	sprintf(StringParametros,"%sNDivZ           =%d\n",StringParametros,NDivZ			    );
	sprintf(StringParametros,"%sDominio_Xmax    =%f\n",StringParametros,Dominio_Xmax	    );
	sprintf(StringParametros,"%sDominio_Rint    =%f\n",StringParametros,Dominio_Rint	    );
	sprintf(StringParametros,"%sDominio_Rmed    =%f\n",StringParametros,Dominio_Rmed	    );
	sprintf(StringParametros,"%sDominio_Hmax    =%f\n",StringParametros,Dominio_Hmax	    );
	sprintf(StringParametros,"%sDominio_Hsup    =%f\n",StringParametros,Dominio_Hsup		);
	sprintf(StringParametros,"%srhof            =%f\n",StringParametros,Datos_rhof			);
	sprintf(StringParametros,"%srhos            =%f\n",StringParametros,Datos_rhos			);
	sprintf(StringParametros,"%sphi             =%f\n",StringParametros,Datos_phi			);
	sprintf(StringParametros,"%scf              =%f\n",StringParametros,Datos_cf			);
	sprintf(StringParametros,"%sTinyeccion      =%f\n",StringParametros,Datos_Tinyeccion	);
	sprintf(StringParametros,"%sTambiente       =%f\n",StringParametros,Datos_Tambiente	    );
	sprintf(StringParametros,"%sTLimite        =%f\n",StringParametros,TLimite 	    );
	sprintf(StringParametros,"%shc_superior     =%f\n",StringParametros,Datos_hc_superior	);
	sprintf(StringParametros,"%shc_inferior     =%f\n",StringParametros,Datos_hc_inferior	);
	sprintf(StringParametros,"%shc_lateral      =%f\n",StringParametros,Datos_hc_lateral	);
	sprintf(StringParametros,"%sKTermofilm      =%e\n",StringParametros,Datos_KTermofilm	);
	sprintf(StringParametros,"%seTermofilm      =%e\n",StringParametros,Datos_eTermofilm	);
	sprintf(StringParametros,"%sVinyeccionLtsHr =%f\n",StringParametros,VinyeccionLtsHr	    );
	sprintf(StringParametros,"%skf              =%f\n",StringParametros,Datos_kf			);
	sprintf(StringParametros,"%sks              =%f\n",StringParametros,Datos_ks				     );
	sprintf(StringParametros,"%sKevaporacion       =%e\n",StringParametros,Datos_Kevaporacion	     );
	sprintf(StringParametros,"%sHumedadAmbiental   =%f\n",StringParametros,Datos_HumedadAmbiental    );
	sprintf(StringParametros,"%sDistanciaAlBorde   =%f\n",StringParametros,Datos_DistanciaAlBorde    );
	sprintf(StringParametros,"%sCalorLatenteFluido =%e\n",StringParametros,Datos_CalorLatenteFluido);


	if (glui3 != NULL) Glui3_EditParametros->set_text(StringParametros);

}


void DrawMensajesRight()
{

//	cout<<"M DrawMensajesRight"<<endl;
	int i;
	glPushAttrib( GL_LIGHTING_BIT );

	glDisable( GL_LIGHTING );


	glColor3d(.5,1, 0.1);


	for (i=0;i<NMensajeRight;i++){
		print_text(width-640,height-17*(i+1),MensajeRight[i]);
	}
}

void DrawMensajes()
{
	int i;
	glPushAttrib( GL_LIGHTING_BIT );

	glDisable( GL_LIGHTING );


	glColor3d(1,1, 0.7);


	for (i=0;i<NMensajes;i++){
//		print_text(3,height-17*(NMensajes-i),Mensaje[i]);
		print_text(3,height-17*(i+1),Mensaje[i]);
	}




	switch (mode)
	{
	case modeT : 
		glPushMatrix();
		glColor3d(.8,.9, 1);

		glTranslatef(-2.07*aspect,-2,5);
		glRasterPos2f(0,0);

		glListBase(baseBIT);
		glCallLists(12, GL_UNSIGNED_BYTE, "(T)raslación"); 

		glPopMatrix();
		break;
	case modeR:
		glPushMatrix();
		glColor3d(.8,.9, 1);

		glTranslatef(-2.07*aspect,-2,5);
		glRasterPos2f(0,0);

		glListBase(baseBIT);
		glCallLists(10, GL_UNSIGNED_BYTE, "(R)otación"); 

		glPopMatrix();
		break;
	}
	glPopAttrib();

}


void MatrizXvector4(GLfloat *mat,GLfloat *vec,GLfloat *resultado) {
	resultado[0]=mat[0]*vec[0] + mat[4]*vec[1] + mat[ 8]*vec[2] + mat[12]*vec[3];
	resultado[1]=mat[1]*vec[0] + mat[5]*vec[1] + mat[ 9]*vec[2] + mat[13]*vec[3];
	resultado[2]=mat[2]*vec[0] + mat[6]*vec[1] + mat[10]*vec[2] + mat[14]*vec[3];
	resultado[3]=mat[3]*vec[0] + mat[7]*vec[1] + mat[11]*vec[2] + mat[15]*vec[3];
}


void MatrizXvector4(GLdouble *mat,GLfloat *vec,GLfloat *resultado) {
	resultado[0]=mat[0]*vec[0] + mat[4]*vec[1] + mat[ 8]*vec[2] + mat[12]*vec[3];
	resultado[1]=mat[1]*vec[0] + mat[5]*vec[1] + mat[ 9]*vec[2] + mat[13]*vec[3];
	resultado[2]=mat[2]*vec[0] + mat[6]*vec[1] + mat[10]*vec[2] + mat[14]*vec[3];
	resultado[3]=mat[3]*vec[0] + mat[7]*vec[1] + mat[11]*vec[2] + mat[15]*vec[3];
}

void MatrizTrXvector4(GLdouble *mat,GLfloat *vec,GLfloat *resultado) {
	resultado[0]=mat[ 0]*vec[0] + mat[ 1]*vec[1] + mat[ 2]*vec[2] + mat[ 3]*vec[3];
	resultado[1]=mat[ 4]*vec[0] + mat[ 5]*vec[1] + mat[ 6]*vec[2] + mat[ 7]*vec[3];
	resultado[2]=mat[ 8]*vec[0] + mat[ 9]*vec[1] + mat[10]*vec[2] + mat[11]*vec[3];
	resultado[3]=mat[12]*vec[0] + mat[13]*vec[1] + mat[14]*vec[2] + mat[15]*vec[3];
}


void ZGlobal(double*v) {
	v[0]=MatrizRotacionGlobalINV[8];
	v[1]=MatrizRotacionGlobalINV[9];
	v[2]=MatrizRotacionGlobalINV[10];
}

void inicializacionGL()
{
	if (DBG) cout<<"inicializacionGL()"<<endl;
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective( 0.0 , 640.0/480.0, 0.001, 100.0);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef(-60,1,0,0);
	glRotatef(-135,0,0,1);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)MatrizRotacionGlobal);
	glLoadIdentity();
	glRotatef(135,0,0,1);
	glRotatef(60,1,0,0);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)MatrizRotacionGlobalINV);
	FuncionesOpenGL::modelview_calculado=false;
	if (DBG) cout<<"inicializacionGL():END"<<endl;
}
void inicializacion()
{
	int i,j,iL,malla;
	double x1,x2,y1,y2,xL,yL,R,xF,yF,RF,th,pi=4*atan(1.0);

	for (i=0;i<NMensajes;i++) {
		Mensaje[i]=(char *)(new char[100]);
		strcpy(Mensaje[i],"");
	}

	for (i=0;i<MaxMensajeRight;i++) {
		MensajeRight[i]=(char *)(new char[100]);
		strcpy(MensajeRight[i],"");
	}

	clock2=clock0=clock ();
	glClearColor(.9, .9, 1.0, 1.0f);
	glClearDepth(1.0);

	malla=0;
	gtotal->cubo(5,2,2);
	g1.cubo(5,2,2);
	g2.cubo(5,2,2);
	switch (malla) 
	{
	case 1:
		gtotal->cubo(2,2,2);
		g2.cubo(1,2,2);
		x1=0.1;x2=1;
		y1=0.1;y2=1;
		for (i=0;i<gtotal->nV3D ;i++){
			xL=gtotal->v3D[i].x ;
			yL=gtotal->v3D[i].y ;
			gtotal->v3D[i].x = x1+xL*(x2-x1);
			gtotal->v3D[i].y = yL*(y1+xL*(y2-y1));
		}
		x1=x2;x2=1.5;
		for (i=0;i<g2.nV3D ;i++){
			xL=g2.v3D[i].x ;
			g2.v3D[i].x = x1+xL*(x2-x1);
		}
		gtotal->Junta(g2);
		g2=*gtotal;

		for (i=0;i<g2.nV3D ;i++){
			g2.v3D[i].y *= -1;
		}
		for (i=0;i<g2.nH3D ;i++){
			for (j=0;j<4;j++) {
				iL=g2.h3D[i].iv[j];
				g2.h3D[i].iv[j]=g2.h3D[i].iv[7-j];
				g2.h3D[i].iv[7-j]=iL;
			}
		}
		gtotal->Junta(g2);

		g2=*gtotal;
		g2.Rota90Z();	gtotal->Junta(g2);
		g2.Rota90Z();	gtotal->Junta(g2);
		g2.Rota90Z();	gtotal->Junta(g2);
		g2.cubo(1,1,2);
		x1=1;x2=1.5;
		for (i=0;i<g2.nV3D ;i++){
			xL=g2.v3D[i].x ;
			yL=g2.v3D[i].y ;
			g2.v3D[i].x = x1+xL*(x2-x1);
			g2.v3D[i].y = x1+yL*(x2-x1);
		}
		gtotal->Junta(g2);
		g2.Rota90Z();	gtotal->Junta(g2);
		g2.Rota90Z();	gtotal->Junta(g2);
		g2.Rota90Z();	gtotal->Junta(g2);
		break;
	case 2:
		gtotal->cubo(2,2,2);g2=*gtotal;
		x1=0.05;x2=1;y1=0.1;y2=1;
		for (i=0;i<gtotal->nV3D;i++) {
			xL=gtotal->v3D[i].x; yL=gtotal->v3D[i].y;
			R=x1+(x2-x1)*xL;
			th=pi/4*yL;
			xF=R; yF=R*yL;
			xF=xF*xL+(1-xL)*R*cos(th);
			yF=yF*xL+(1-xL)*R*sin(th);
			gtotal->v3D[i].x=xF;
			gtotal->v3D[i].y=yF;
		}
		for (i=0;i<g2.nV3D;i++) {
			xL=g2.v3D[i].x;	yL=g2.v3D[i].y;
			R=x1+(x2-x1)*yL; th=pi/4*xL;
			yF=R; xF=R*xL;
			xF=xF*yL+(1-yL)*R*sin(th);
			yF=yF*yL+(1-yL)*R*cos(th);
			g2.v3D[i].x=xF;
			g2.v3D[i].y=yF;
		}
		gtotal->Junta(g2);

		g2=*gtotal;g2.Rota90Z();gtotal->Junta(g2);g2.Rota90Z();gtotal->Junta(g2);g2.Rota90Z();gtotal->Junta(g2);
		g2=*gtotal;
		g2.Traslada(2,0,0);gtotal->Junta(g2);
		g2.Traslada(0,2,0);gtotal->Junta(g2);
		g2.Traslada(-2,0,0);gtotal->Junta(g2);


	}

	F.resize(gtotal->nV3D);
	U.resize(gtotal->nV3D);
	V.resize(gtotal->nV3D);
	W.resize(gtotal->nV3D);

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
	inicializacionGL();
}

///Cambiado para GLUT de () a void ResizeGraphics(int lwidth, int lheight)
void ResizeGraphics(int lwidth, int lheight)
{
	// Get new window size

	if (DBG) cout<<"ResizeGraphics()"<<endl;
	int tx, ty, tw, th;
	tx=0; ty=0;	tw= lwidth;	th = lheight;

#if defined(GLUI_GLUI_H)
	if (!glui_hide) {
		GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	}
#endif
	width = tw;
	height = th;

	aspect = (GLfloat) width / height;

	// Adjust graphics to window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective((GLdouble)GlobalFovy, aspect, (GLdouble)1, (GLdouble)100.0);
	glViewport(tx, ty, width, height);
	    glTranslated( 0, 0, -10);
	glMatrixMode(GL_MODELVIEW);
	FuncionesOpenGL::projection_calculado=false;
	FuncionesOpenGL::viewport_calculado=false;
	if (DBG) cout<<"ResizeGraphics():END"<<endl;
}

void CB_mouse_whell(int button, int state, int x, int y)
{

	//	printf("CB_mouse_whell: button=%d, state=%d, x=%d, y=%d\n",button,state,x,y);	cout<<endl;
	switch (state)
	{
	case 1:

		Escala *= 1.2;
		FuncionesOpenGL::modelview_calculado=false;
		break;
	case -1:

		Escala /= 1.2;
		FuncionesOpenGL::modelview_calculado=false;
		break;
	}
	return;
}

bool gluInvertMatrix(const GLfloat  m[16], GLfloat  invOut[16])
{
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}


bool InvierteMatriz(const GLdouble  m[16], GLdouble  invOut[16])
{
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}



void CB_mouse(int button, int state, int x, int y)
{
	xPos0 = x;
	yPos0 = y;

#if DBGMouse
	myfileDBG<<"CB_mouse: B="<<button<<" st="<<state<<" x="<<x<<" y="<<y<<endl;
#endif

	cout<<"M CB_mouse(int "<<button<<", int "<<state<<", int "<<x<<", int "<<y<<")"<<endl;
	//	printf("CB_mouse: button=%d, state=%d, x=%d, y=%d\n",button,state,x,y);
	KeyControlAltShift = glutGetModifiers();
	//printf("glutGetModifiers=%d",KeyControlAltShift);	cout<<endl;


	if (state==GLUT_UP) {iPush=0;}
	else {
		switch (button)
		{
		case GLUT_LEFT_BUTTON:

			if (MODO_Rotacion2==0) iPush=1;
			else {
				cout<<"MODO_Rotacion2=="<<MODO_Rotacion2<<endl;
				iPush=3;
			}

			if (KeyControlAltShift==GLUT_ACTIVE_CTRL) iPush=2;


			break;

		case GLUT_RIGHT_BUTTON:
			iPush=3;
			break;
		case GLUT_MIDDLE_BUTTON:

			iPush=2;


		}

		if (iPush==2) {
			if (Add_Particulas) {
				iPush=0;
				//Convertir coordenadas de la pantalla a OpenGL.....


				//float x=xPos0,y=yPos0;
				GLint viewport[4];
				GLdouble modelview[16];
				GLdouble projection[16];
				GLfloat winX, winY, winZ;
				GLdouble posX, posY, posZ;

				FuncionesOpenGL::ObtieneMatrices();

				winX = (float)x;
				winY = (float)FuncionesOpenGL::viewport[3] - (float)y;
				glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

				FuncionesOpenGL::Win2World(winX, winY, winZ, &posX, &posY, &posZ);

				printf("%f %f %f\n",posX,posY,posZ);


				gtotal->PosINI3(posX,posY,posZ);





			} else if (MueveCentro)
			{
				iPush=0;
				//Convertir coordenadas de la pantalla a OpenGL.....


				//float x=xPos0,y=yPos0;
				GLfloat winX, winY, winZ;
				GLdouble posX, posY, posZ;


				FuncionesOpenGL::ObtieneMatrices();

				winX = (float)x;
				winY = (float)FuncionesOpenGL::viewport[3] - (float)y;
//				winY = -(float)y;
				glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

				FuncionesOpenGL::Win2World(winX, winY, winZ, &posX, &posY, &posZ);
				//gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

				cout<<"M posX,Y,Z="<<posX<<" "<<posY<<" "<<posZ<<endl;
				vecDXEsfera[0]=posX-vecXEsfera[0];
				vecDXEsfera[1]=posY-vecXEsfera[1];
				vecDXEsfera[2]=posZ-vecXEsfera[2];
				vecXEsfera[0]=posX;
				vecXEsfera[1]=posY;
				vecXEsfera[2]=posZ;

				cout<<"M vecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<"]"<<endl;
				gluInvertMatrix(MatrizRotacionGlobal,MatrizRotacionGlobalINV);
				MatrizXvector4(MatrizRotacionGlobal,vecDXEsfera,vecDUEsfera);
				vecUEsfera[0]+=vecDUEsfera[0]*Escala;
				vecUEsfera[1]+=vecDUEsfera[1]*Escala;
				vecUEsfera[2]+=vecDUEsfera[2]*Escala;
				cout<<"M vecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<"]"<<endl;
			}
		}

	}

	//cout<<"CB_mouse()END: iPush="<<iPush<<endl;

}

void CB_motion(int x, int y)
{
	//	printf("CB_motion: iPush=%d, x=%d, y=%d",iPush,x,y);cout<<endl;
	float dx,dy;
	GLdouble winX,winY,winZ;
	xPos = x;
	yPos = y;

	if (iPush==0) return;
#if DBGMouse
	myfileDBG<<"CB_motion: x="<<x<<" y="<<y<<endl;
#endif

	int lMODO_de_mover=MODO_de_mover;

	//cout<<"iPush="<<iPush<<" lMODO_de_mover="<<lMODO_de_mover<<" KeyControlAltShift="<<KeyControlAltShift<<endl;

	if (KeyControlAltShift==GLUT_ACTIVE_CTRL)
		lMODO_de_mover=0;
	if (iPush==2) lMODO_de_mover=3;
	if (iPush==3) lMODO_de_mover=0;
	switch (lMODO_de_mover)
	{
	case 0: //Trasladar
		dx=(xPos-xPos0+0.0);
		dy=-(yPos-yPos0+0.0);
		double dxE,dyE,dzE,xP,yP,zP;

		cout <<"M \ndxy=["<<dx<<" , "<<dy<<endl;
		cout<<"M A1 vecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<","<<vecUEsfera[3]<<"]"<<endl;


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective((GLdouble)GlobalFovy, aspect, (GLdouble)1, (GLdouble)100.0);
		glTranslated( 0, 0, -10);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated( 0, -1, -10);

		FuncionesOpenGL::World2Win((GLdouble)vecUEsfera[0], (GLdouble)vecUEsfera[1], (GLdouble)vecUEsfera[2],
				&xP,&yP,&zP);
		cout<<"M xyzP=[ "<<xP<<" , "<<yP<<" , "<<zP<<" ]"<<endl;

		FuncionesOpenGL::Win2World(xP+dx, yP+dy, zP, &dxE, &dyE, &dzE);
		cout <<"M dxyzE=["<<dxE<<" , "<<dyE<<" , "<<dzE<<endl;

		vecUEsfera[0] =dxE;
		vecUEsfera[1] =dyE;
		vecUEsfera[2] =dzE;
		cout<<"M A2 vecUEsfera=["<<vecUEsfera[0]<<","<<vecUEsfera[1]<<","<<vecUEsfera[2]<<","<<vecUEsfera[3]<<"]"<<endl;
		FuncionesOpenGL::modelview_calculado=false;
		break;
	case 1: //Rotar
		rotacion(yPos-yPos0, xPos-xPos0);


#if DBGMouse
		myfileDBG<<"Rotacion Mouse"<<endl;
		MyDBG();
#endif
		break;
	case 2: //Spin en torno a Z
		int dx1,dy1,x1,y1;
		dx1=xPos-xPos0;dy1=yPos-yPos0;
		x1=xPos0-width/2;y1=yPos0-height/2;

		FuncionesOpenGL::World2Win(vecXEsfera[0],vecXEsfera[1],vecXEsfera[2], &winX, &winY, &winZ);
		printf("xPos0=%d,winX=%f,yPos0=%d,winY=%f\n",xPos0,winX,yPos0,winY);
		x1=xPos0-winX;y1=yPos0-(height-winY);

		printf("x1=%d,y1=%d\n",x1,y1);

		wAngleZ=-(dx1*(-y1)+dy1*x1+0.0)/(x1*x1+y1*y1+1.0)*180/3.14;
		glLoadIdentity();
		glRotatef(wAngleZ, 0.0f, 0.0f, 1.0f);
		glMultMatrixf((GLfloat *)MatrizRotacionGlobal);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)MatrizRotacionGlobal);
		glLoadIdentity();
		glMultMatrixf((GLfloat *)MatrizRotacionGlobalINV);
		glRotatef(-wAngleZ, 0.0f, 0.0f, 1.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)MatrizRotacionGlobalINV);
		FuncionesOpenGL::modelview_calculado=false;
		break;

	case 3:
		Escala *= 1-2*(yPos-yPos0+0.0)/height;
		FuncionesOpenGL::modelview_calculado=false;
		break;

	}
	yPos0=yPos;
	xPos0=xPos;
	return;
}

void CB_keyboardSpecial( int key, int x, int y )
{
	// manejo de teclas especiales
	printf("CB_keyboardSpecial: char=%d, x=%d, y=%d\n",key,x,y);cout<<endl;
	switch (key) {
	case 100:
		rotacion(0,-1);
		break;
	case 101:
		rotacion(-1,0);
		break;
	case 102:
		rotacion(0,1);
		break;
	case 103:
		rotacion(1,0);
		break;

	}
	glutPostRedisplay();
}


void idleevent()
{
	static int generador=0;
	if(DBG)cout<<"idleevent()"<<endl;

	if ( glutGetWindow() != main_window ) 
		glutSetWindow(main_window);  


	if(DBG)cout<<"idleevent(): Falta_llamar_etapaS="<<llamar_etapa_Siguiente_PAUSA2<<endl;
	if(llamar_etapa_Siguiente_PAUSA2){
		Calculo_EtapaS();
	}


	if(DBG)cout<<"idleevent(): CalculoContinuo="<<CalculoContinuo<<endl;
	if (CalculoContinuo) {
		if (Etapa==0){
			Calculo_EtapaS(); //Lanzar la primera etapa

			if (nRLC>0) nR=nRLC;
			if (nThLC>0) nTh=nThLC;

			time_t _tm =time(NULL );

			struct tm * curtime = localtime ( &_tm );
			sprintf(nombre0,"Soluciones/Sal_%02d.%02d_%02d.%02d.%02d_Malla=%d_nR=%d_nTg=%d_NDivZ=%d_",
					curtime->tm_mon,curtime->tm_mday,
					curtime->tm_hour,curtime->tm_min,curtime->tm_sec,CualMalla,nR,nTh,NDivZ);
		}


		Calculo_EtapaS();

		char nombre[100];
		sprintf(nombre,"%s_Size=%d_Etapa=%d.dat",nombre0,gtotal->nH3D,Etapa);
		SaveOrRead(nombre,1);
	} else	if (Etapa==0){
		Calculo_EtapaS(); //Lanzar la primera etapa
	}


	generador++;
	if (generador >0) {
		generador=0;
		//		g.GeneraCaras(g.nH3D);
		//		g.GeneraCaras();

	}
	glutPostRedisplay();

	if(DBG)cout<<"idleevent():END"<<endl;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void LecturaArchivoDeDatos() {
	ifstream myfile;
	ofstream myfile2;
	int numlinea=0;

	char mensajeE[10000];
	myfile2.open("dondeestoy.txt");
	myfile2<<"hola"<<endl;
	myfile2.close();
#if DBG == 1
		myfile2.open("dondeestoy.txt");
		myfile2<<"hola"<<endl;
		myfile2.close();
#endif
		cout<<"LecturaArchivoDeDatos():"<<FDatos<<endl;
		sprintf(mensajes0,"%sLecturaArchivoDeDatos():%s\n",mensajes0,FDatos);

		sprintf(mensajeE,"Archivo: \"%s\" \n",FDatos);

	myfile.open (FDatos);
	string linea;
	int errordatos=0;

	while (getline(myfile,linea)) {
		numlinea++;
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
		else if (snombre=="TipoCalculo"	    ) {TipoCalculo	    =ff;}
		else if (snombre=="dt"				) {Datos_dt			=ff;}
		else if (snombre=="Tmax"			) {Datos_Tmax		=ff;}
		else if (snombre=="nR"				) {nR				=ff;}
		else if (snombre=="nR2"				) {nR2				=ff;}
		else if (snombre=="nTh"				) {nTh				=ff;}
		else if (snombre=="NDivZ"			) {NDivZ			=ff;}
		else if (snombre=="Dominio_Xmax"	) {Dominio_Xmax		=ff;}
		else if (snombre=="Dominio_Hmax"	) {Dominio_Hmax		=ff;}
		else if (snombre=="Dominio_Hsup"	) {Dominio_Hsup		=ff;}
		else if (snombre=="Dominio_Rint"	) {Dominio_Rint		=ff;}
		else if (snombre=="Dominio_Rmed"	) {Dominio_Rmed		=ff;}
		else if (snombre=="rhof"			) {Datos_rhof		=ff;}
		else if (snombre=="rhos"			) {Datos_rhos		=ff;}
		else if (snombre=="phi"				) {Datos_phi		=ff;}
		else if (snombre=="cf"				) {Datos_cf			=ff;}
		else if (snombre=="cs"				) {Datos_cs			=ff;}
		else if (snombre=="Tinyeccion"		) {Datos_Tinyeccion	=ff;}
		else if (snombre=="Tambiente"		) {Datos_Tambiente	=ff;}
		else if (snombre=="TLimite"		    ) {TLimite       	=ff;}
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
		else if (snombre=="Solucion_error") {ErrorMax_Cada_t=ff;}
		else {
			cout <<"Comando en Archivo de datos no considerado:"<<endl;
			cout <<"variable="<< snombre<<"\t="<<ff<<endl;
			sprintf(mensajeE,"%sLinea=%d, Variable \"%s\" no tiene sentido (= %f)\n",mensajeE,numlinea,snombre.c_str(),ff);
			cout <<"variable="<< snombre<<"\t="<<ff<<endl;
			errordatos=1;
		}

	}


	myfile.close();
	if (errordatos==1) {

#if defined _WIN32 || defined _WIN64s
		MessageBox( 0, mensajeE, "Error Grave en Archivo de Datos", 0 );
#endif
		exit(1);
	}

}

void LecturaArchivoDeDatos_Post(ostream& os) {



	os<<"#Parametros usados:\n"<<endl;


	os<<"malla              ="<<CualMalla       <<endl;
	os<<"CalculoContinuo    ="<<CalculoContinuo	<<endl;
	os<<"TipoCalculo        ="<<TipoCalculo	    <<endl;
	os<<"dt                 ="<<Datos_dt		<<endl;
	os<<"Tmax               ="<<Datos_Tmax		<<endl;
	os<<"nR                 ="<<nR				<<endl;
	os<<"nR2                ="<<nR2				<<endl;
	os<<"nTh                ="<<nTh				<<endl;
	os<<"NDivZ              ="<<NDivZ			<<endl;
	os<<"Dominio_Xmax       ="<<Dominio_Xmax	<<endl;
	os<<"Dominio_Rint       ="<<Dominio_Rint	<<endl;
	os<<"Dominio_Rmed       ="<<Dominio_Rmed	<<endl;
	os<<"Dominio_Hmax       ="<<Dominio_Hmax	<<endl;
	os<<"Dominio_Hsup       ="<<Dominio_Hsup	<<endl;
	os<<"rhof               ="<<Datos_rhof		<<endl;
	os<<"rhos               ="<<Datos_rhos		<<endl;
	os<<"phi                ="<<Datos_phi		<<endl;
	os<<"cf                 ="<<Datos_cf		<<endl;
	os<<"cs                 ="<<Datos_cs		<<endl;
	os<<"Tinyeccion         ="<<Datos_Tinyeccion<<endl;
	os<<"Tambiente          ="<<Datos_Tambiente	<<endl;
	os<<"TLimite            ="<<TLimite     	<<endl;
	os<<"hc_superior        ="<<Datos_hc_superior<<endl;
	os<<"hc_inferior        ="<<Datos_hc_inferior<<endl;
	os<<"hc_lateral         ="<<Datos_hc_lateral	<<endl;
	os<<"KTermofilm         ="<<Datos_KTermofilm	<<endl;
	os<<"eTermofilm         ="<<Datos_eTermofilm	<<endl;
	os<<"VinyeccionLtsHr    ="<<VinyeccionLtsHr	<<endl;
	os<<"kf                 ="<<Datos_kf			<<endl;
	os<<"ks                 ="<<Datos_ks				<<endl;
	os<<"Kevaporacion       ="<<Datos_Kevaporacion	<<endl;
	os<<"HumedadAmbiental   ="<<Datos_HumedadAmbiental<<endl;
	os<<"DistanciaAlBorde   ="<<Datos_DistanciaAlBorde<<endl;
	os<<"CalorLatenteFluido ="<<Datos_CalorLatenteFluido<<endl;
	os<<"Solucion_error     ="<<ErrorMax_Cada_t<<endl;

	Datos_KtEt=Datos_KTermofilm/Datos_eTermofilm;
	Datos_htilde=(Datos_hc_superior*Datos_KtEt)/(Datos_hc_superior+Datos_KtEt);
	Datos_Vinyeccion=VinyeccionLtsHr/1000/3600; //% m^3/m^2/s
	Datos_km=Datos_phi*Datos_kf+(1-Datos_phi)*Datos_ks;
	Datos_km2=(1-Datos_phi)*Datos_ks;
	Datos_rhom=Datos_phi*Datos_rhof+(1-Datos_phi)*Datos_rhos;
	Datos_cm=Datos_phi*Datos_cf+(1-Datos_phi)*Datos_cs;

	os<<"\n#Parametros derivados:\n"<<endl;
	os<<"# KtEt      =KTermofilm/eTermofilm                    = "<<Datos_KtEt<<endl;
	os<<"# htilde    =(hc_superior*KtEt)/(hc_superior+KtEt)    = "<<Datos_htilde<<endl;
	os<<"# Vinyeccion=VinyeccionLtsHr/1000/3600; //% m^3/m^2/s = "<<Datos_Vinyeccion<<endl;
	os<<"# km        =phi*kf+(1-phi)*ks                        = "<<Datos_km<<endl;
	os<<"# km2       =(1-phi)*ks                               = "<<Datos_km2<<endl;
	os<<"# rhom      =phi*rhof+(1-phi)*rhos                    = "<<Datos_rhom<<endl;
	os<<"# cm        =phi*cf  +(1-phi)*cs                      = "<<Datos_cm<<endl;


}
void SaveOrRead(char *ifile_name,int iSaveReadMode) {

	char leyendo[100];
	char leyendo2[100]={'aa'};
	char ArchivoParametros[200];
	int i=0;

	if (iSaveReadMode==1) { //Save


		//Busca Nombre pila del archivo y genera el nombre de los parametros
		strcpy(leyendo2,ifile_name);
		char *st=leyendo2;

		while(strncmp(st,"Etapa",5)!=0 && i<100) {st++;i++;}
		cout<<"i="<<i<<endl;
		if (i==100) {
			sprintf(leyendo2,"%s_Etapa=%02d.dat",leyendo2,EtapaGlobal);
			sprintf(ifile_name,"%s_Etapa=%02d.dat",ifile_name,EtapaGlobal);
			st=leyendo2;i=0;
			while(strncmp(st,"Etapa",5)!=0 && i<100) {st++;i++;}
		}
		cout<<"i="<<i<<endl;
		*st=0;
		cout<<"leyendo2="<<leyendo2<<endl;
		sprintf(FDatos,"%sEtapa=00_Parametros.dat",leyendo2);
		cout<<FDatos<<endl;

		rmdir(FDatos);
		ofstream myfile;
		myfile.open (FDatos);


		LecturaArchivoDeDatos_Post(myfile);
		myfile.close();

		myfile.open (ifile_name);

		myfile.precision(17);
		VersionDatos=0.20;
		myfile<<"#Version "<<VersionDatos<<" "<<CualMalla<<endl;
		cout<<"#Version "<<VersionDatos<<" "<<CualMalla<<endl;
		if(VersionDatos>=0.1999)	{
			myfile<<EtapaGlobal<<"  "<<TiempoCalculo<<endl;
		}
		gtotal->write(myfile);
		myfile<<Etapa<<endl;
		myfile<<InicioEtapa<<endl;
		save(F,myfile);
		save(PotencialPsi,myfile);
		save(Temperatura,myfile);
		save(F2Nodos,myfile);
		save(PotencialVInfiltracion,myfile);
		save(TempPilaBloques,myfile);
		save(U,myfile);
		save(V,myfile);
		save(W,myfile);
		myfile.close();
	} else {   //Read
		int num1,num2;
		ifstream myfile;


#if DBGMouse
		myfileDBG << "Voy a leer"<<endl;
		MyDBG();
#endif

		//Busca Nombre pila del archivo y genera el nombre de los parametros
		strcpy(leyendo2,ifile_name);
		char *st=leyendo2;

		while(strncmp(st,"Etapa",5)!=0 && i<100) {st++;i++;}

		cout<<"i="<<i<<endl;
		*st=0;
		cout<<"leyendo2="<<leyendo2<<endl;
		sprintf(FDatos,"%sEtapa=00_Parametros.dat",leyendo2);
		cout<<FDatos<<endl;

		//Leo archivo de Parametros

		cout<<"Leo archivo de Parametros..."<<endl;

		LecturaArchivoDeDatos();
		LecturaArchivoDeDatos_Post(cout);
		CalculoContinuo=0;

		// Leo archivo de resultados0
		cout<<"Leo archivo de resultados..."<<endl;
		time_t _tm0 =time(NULL );

		cout<<"1:"<<ifile_name<<endl;
		myfile.open (ifile_name);
		cout<<"2"<<endl;
		myfile.ignore(100,' ');
		cout<<"3"<<endl;
		myfile >>VersionDatos>>CualMalla;
		cout<<"4"<<endl;
		cout<<"VersionDatos="<<VersionDatos<<"\tCualMalla="<<CualMalla<<endl;

		if(VersionDatos>=0.1999)	{
			myfile>>EtapaGlobal>>TiempoCalculo;
			cout<<"EtapaGlobal(VersionDatos>=0.20)="<<EtapaGlobal<<endl;
			cout<<"TiempoCalculo(VersionDatos>=0.20)="<<TiempoCalculo<<endl;
		}


		gtotal->read(myfile);
		if (DBG) cout<<"Malla Ok"<<endl;
		myfile>>Etapa;
		cout<<"InicioEtapa(antes)="<<InicioEtapa<<endl;
		if(VersionDatos>0.109)	{
			myfile>>InicioEtapa;
			cout<<"InicioEtapa(VersionDatos>0.109)="<<InicioEtapa<<endl;
		}
		else
		{
			InicioEtapa=Etapa;
			cout<<"InicioEtapa(=Etapa)="<<InicioEtapa<<endl;
		}

		read(F,myfile);
		if (DBG) cout<<"F Ok"<<endl;
		read(PotencialPsi,myfile);
		if (DBG) cout<<"FF Ok"<<endl;
		read(Temperatura,myfile);
		if (DBG) cout<<"FF2 Ok"<<endl;
		read(F2Nodos,myfile);
		if (DBG) cout<<"F2Nodos Ok"<<endl;
		read(PotencialVInfiltracion,myfile);
		if (DBG) cout<<"PotencialVInfiltracion Ok"<<endl;
		read(TempPilaBloques,myfile);
		if (DBG) cout<<"TempPilaBloques Ok"<<endl;
		read(U,myfile);
		if (DBG) cout<<"U Ok"<<endl;
		read(V,myfile);
		if (DBG) cout<<"V Ok"<<endl;
		read(W,myfile);
		if (DBG) cout<<"W Ok"<<endl;
		myfile.close();

		err0=1e-8;
		switch (CualMalla) {
		case 1:
			ThetaMax=atan(1)*2;
			if (Etapa==7) InicioEtapa=Etapa-1;
			break;
		}

		time_t _tm1 =time(NULL );

		cout<< "lectura en "<<_tm1-_tm0<<" seg"<<endl;
		if (glui != NULL) {
			control_cb(1105);
			PanelFlimite->execute_callback();
			PanelFlimite->enable();
		}


#if DBGMouse
		myfileDBG << "Ya Lei"<<endl;
		MyDBG();
#endif

	}
}


void visible(int vis)
{
	cout<<"visible()"<<endl;

	if (vis == GLUT_VISIBLE) {

		glutIdleFunc(idleevent);

	} else {
		glutIdleFunc(NULL);
	}
	cout<<"visible():END"<<endl;
}

double HumedadSaturacion(double T) {

	double TVapor[25],PVapor[25];

	TVapor[ 0]=0  ; PVapor[ 0]=0.0060;
	TVapor[ 1]=5  ; PVapor[ 1]=0.0086;
	TVapor[ 2]=10 ; PVapor[ 2]=0.0121;
	TVapor[ 3]=15 ; PVapor[ 3]=0.0168;
	TVapor[ 4]=20 ; PVapor[ 4]=0.0231;
	TVapor[ 5]=25 ; PVapor[ 5]=0.0313;
	TVapor[ 6]=30 ; PVapor[ 6]=0.0419;
	TVapor[ 7]=35 ; PVapor[ 7]=0.0555;
	TVapor[ 8]=40 ; PVapor[ 8]=0.0728;
	TVapor[ 9]=45 ; PVapor[ 9]=0.0946;
	TVapor[10]=50 ; PVapor[10]=0.1217;
	TVapor[11]=55 ; PVapor[11]=0.1553;
	TVapor[12]=60 ; PVapor[12]=0.1966;
	TVapor[13]=65 ; PVapor[13]=0.2468;
	TVapor[14]=70 ; PVapor[14]=0.3075;
	TVapor[15]=75 ; PVapor[15]=0.3804;
	TVapor[16]=80 ; PVapor[16]=0.4673;
	TVapor[17]=85 ; PVapor[17]=0.5706;
	TVapor[18]=90 ; PVapor[18]=0.6918;
	TVapor[19]=95 ; PVapor[19]=0.8341;
	TVapor[20]=100; PVapor[20]=0.9999;

	int i;
	double Pt,Psi;
	if (T< TVapor[0]) Pt=PVapor[ 0];
	else if (T>= TVapor[20]) Pt=PVapor[ 20];
	else
		for (i=0;i<20;i++) {
			if (TVapor[i]<=T && T< TVapor[i+1] ) {
				double lambda=(T-TVapor[i])/(TVapor[i+1]-TVapor[i]);
				Pt=PVapor[i]+lambda*(PVapor[i+1]-PVapor[i]);
			}
		}

	Psi=0.6242*Pt / (1-Pt);
	return(Psi);


}


double Psi_ev(double Tr) {
	double Psi=Datos_Kevaporacion*(HumedadSaturacion(Tr)-Datos_HumedadAmbiental*HumedadSaturacion(Datos_Tambiente));
	return(Psi);
}

double CalculaMpunto(vector<double> &F,vector<double> &Temp,vector<double> &U,vector<double> &V,
		vector<double> &W,grid3D g,int niteraciones,double err0)
{
	int iiter,i,j,iC;
	double SumaCoeffDif_F,SumaCoeffDif,Coeff_Difusion,err,errG,nF;
	if(DBG) cout<<"CalculaMpunto"<<endl;
	if (F.size() != g.nH3D) F.resize(g.nH3D);
	if (U.size() != g.nH3D) U.resize(g.nH3D);
	if (V.size() != g.nH3D) V.resize(g.nH3D);
	if (W.size() != g.nH3D) W.resize(g.nH3D);
	//Resuelvo la ecuación varias veces
	niteraciones=g.nH3D*10;
	if (niteraciones<30000) niteraciones=30000;
	cout <<"niteraciones="<<niteraciones<<endl;
	myfileSalida <<"niteraciones="<<niteraciones<<endl;

	if(DBG) cout<<"CalculaMpunto(): Potencial"<<endl;
	for (iiter=0 ; iiter<niteraciones ; iiter++) {
		errG=0;
		int i0=g.nH3D-1,istep=-1;
		for (i=i0 ; i<g.nH3D && i>= 0 ; i+=istep) {
			//Escribo la ecuación para cada hexahedro [i]
			SumaCoeffDif_F=0;SumaCoeffDif=0;
			for (j=0 ; j< g.h3D[i].vecino.size() ;j++) {
				//recorro cada vecino==cara [i]--[j]

				Coeff_Difusion = g.h3D[i].Poligono[j].AreaPoligono /Dominio_Hsup/ g.h3D[i].Poligono[j].Dab;
				if (g.h3D[i].tipo_vecino[j] == ES_BLOQUE) {
					SumaCoeffDif_F += Coeff_Difusion * F[ g.h3D[i].vecino[j] ] ;
					SumaCoeffDif   += Coeff_Difusion;
				} else {
					iC=g.h3D[i].vecino[j];
					//if (g.Cara[iC].iBC ==1) // Nada que hacer: Derivada normal igual a cero
					if (g.Cara[iC].iBC ==2 ||g.Cara[iC].iBC ==3 ) {
						//						if (iiter==0 ) cout<<"g.Cara[iC].iBC="<<g.Cara[iC].iBC<<endl;
						SumaCoeffDif_F += Coeff_Difusion * g.Cara[iC].BC ;
						SumaCoeffDif   += Coeff_Difusion;
					}
					if (g.Cara[iC].iBC ==10 ) { // Cara de la infiltración
						SumaCoeffDif_F -= Datos_rhof*Datos_Vinyeccion*g.h3D[i].Poligono[j].AreaPoligono;
						//Aqui ponemos la evaporación
						SumaCoeffDif_F -= Psi_ev(Temp[i])*g.h3D[i].Poligono[j].AreaPoligono;
					}

				}
			}
			nF = SumaCoeffDif_F/SumaCoeffDif;
			err=fabs(nF-F[i])/(fabs(nF)+1e-20);
			if (err > errG) errG=err;
			F[i]=nF;
			//			if (F[i]==0) F[i]=0.5;

		}
		if (errG<err0) {
			cout<<"break: errG<"<<err0<<", iiter="<<iiter<<endl;
			myfileSalida<<"break: errG<"<<err0<<", iiter="<<iiter<<endl;
			break;
		}
	}

	if(DBG) cout<<"CalculaMpunto(): Velocidades"<<endl;
	for (i=0 ; i<g.nH3D ; i++) {
		SumaCoeffDif_F=0;SumaCoeffDif=0;
		double A,AA,AB,AC,RA;
		double BA,BB,BC,RB;
		double CA,CB,CC,RC;
		double nx,ny,nz,DET;
		AA=0;AB=0;AC=0;RA=0;
		BA=0;BB=0;BC=0;RB=0;
		CA=0;CB=0;CC=0;RC=0;
		for (j=0 ; j< g.h3D[i].vecino.size() ;j++) {
			if(DBG) cout<<"CalculaMpunto(): ...1115"<<endl;
			if (g.h3D[i].tipo_vecino[j] == ES_BLOQUE) {
				Coeff_Difusion = ( F[ g.h3D[i].vecino[j] ] - F[i] ) / g.h3D[i].Poligono[j].Dab;
			} else {
				iC=g.h3D[i].vecino[j];
				Coeff_Difusion=0;
				if (g.Cara[iC].iBC ==2 ||g.Cara[iC].iBC ==3) {
					Coeff_Difusion = ( g.Cara[iC].BC - F[i] ) / g.h3D[i].Poligono[j].Dab;

				}
				if (g.Cara[iC].iBC ==10) {
					Coeff_Difusion = -Datos_rhof*Datos_Vinyeccion*Dominio_Hsup;

				}
				if (g.Cara[iC].iBC ==110) {
					Coeff_Difusion = Datos_rhof*Datos_Vinyeccion*Dominio_Hsup;

				}
			}
			A=g.h3D[i].Poligono[j].AreaPoligono;
			if(DBG) cout<<"CalculaMpunto(): ...1138: A="<<A<<endl;
			nx=g.h3D[i].Poligono[j].normal.x ;
			ny=g.h3D[i].Poligono[j].normal.y ;
			nz=g.h3D[i].Poligono[j].normal.z ;
			AA += nx*nx*A; AB+= nx*ny*A; AC+= nx*nz*A; RA += -nx*Coeff_Difusion*A;
			BA += ny*nx*A; BB+= ny*ny*A; BC+= ny*nz*A; RB += -ny*Coeff_Difusion*A;
			CA += nz*nx*A; CB+= nz*ny*A; CC+= nz*nz*A; RC += -nz*Coeff_Difusion*A;
		}
		// AA AB AC --> RA
		// BA BB BC --> RB
		// CA CB CC --> RC
		DET= AA*(BB*CC-BC*CB)+BA*(CB*AC-AB*CC)+CA*(AB*BC-BB*AC) ;
		if(DBG) cout<<"CalculaMpunto(): ...1150: i,U,det ="<<i<<","<<U.size()<<","<<DET<<endl;
		U[i]= ( RA*(BB*CC-BC*CB)+RB*(CB*AC-AB*CC)+RC*(AB*BC-BB*AC) )/DET;
		V[i]=-( RA*(BA*CC-BC*CA)+RB*(CA*AC-AA*CC)+RC*(AA*BC-BA*AC) )/DET;
		W[i]= ( RA*(BA*CB-BB*CA)+RB*(CA*AB-AA*CB)+RC*(AA*BB-BA*AB) )/DET;
	}

	if(DBG) cout<<"CalculaMpunto():END"<<endl;
	return(errG);
}


double CalculaTempSuperficie(vector<double> &Temp,vector<double> &PotencialV,vector<double> &U,
		vector<double> &V,vector<double> &W,grid3D g,int niteraciones,double err0)
{
	int iiter,i,j,iC;
	double SumaCoeffDif_F2,SumaCoeffDif,Coeff_Difusion,err,errG,nTemp;
	if (Temp.size() !=g.nH3D) Temp.resize(g.nH3D);
	if (U.size() !=g.nH3D) U.resize(g.nH3D);
	if (V.size() !=g.nH3D) V.resize(g.nH3D);
	if (W.size() !=g.nH3D) W.resize(g.nH3D);
	//Resuelvo la ecuación varias veces
	niteraciones=g.nH3D*50;
	if (niteraciones<30000) niteraciones=30000;
	cout <<"niteraciones="<<niteraciones<<endl;
	myfileSalida <<"niteraciones="<<niteraciones<<endl;
	for (iiter=0 ; iiter<niteraciones ; iiter++) {
		errG=0;
		for (i=0 ; i<g.nH3D ; i++) {
			if(DBG) {
				if (i==20 && iiter<40) {
					cout<<"Temp[20]="<<Temp[20]<<endl;
				}
				if (i==44) {
					cout<<"Temp[44]="<<Temp[44]<<endl;
				}
			}
			//Escribo la ecuación para cada hexahedro [i]
			SumaCoeffDif_F2=0;SumaCoeffDif=0;
			double PotencialV_i=PotencialV[i],PotencialV_j;
			for (j=0 ; j< g.h3D[i].vecino.size() ;j++) {
				if(1==0) cout <<"CalculaLaplacianoCero2: iiter,i,j="<<iiter<<" "<<i<<" "<<j
						<< "\tPotencialV.size=" << PotencialV.size()
						<<"\tg.h3D[i].vecino[j]="<<g.h3D[i].vecino[j]
																   <<"\tg.h3D[i].tipo_vecino[j]="<<g.h3D[i].tipo_vecino[j]
																														<<endl;
				//recorro cada vecino==cara [i]--[j]

				if (g.h3D[i].tipo_vecino[j] == ES_BLOQUE) {
					PotencialV_j=PotencialV[ g.h3D[i].vecino[j] ];
					if (PotencialV_j>PotencialV_i) Coeff_Difusion = g.h3D[i].Poligono[j].AreaPoligono/Dominio_Hsup / g.h3D[i].Poligono[j].Dab
							*(PotencialV_j-PotencialV_i)*Datos_cf;
					else Coeff_Difusion=0;
					SumaCoeffDif_F2 += Coeff_Difusion * Temp[ g.h3D[i].vecino[j] ] ;
					SumaCoeffDif    += Coeff_Difusion;
				} else {
					iC=g.h3D[i].vecino[j];
					//1== Derivada normal igual a cero
					if (g.Cara[iC].iBC ==2 ||g.Cara[iC].iBC ==3 ) { //2,3 son condiciones DIrichlet
						PotencialV_j=g.Cara[iC].BC;
						if (PotencialV_j>PotencialV_i) Coeff_Difusion = g.h3D[i].Poligono[j].AreaPoligono/Dominio_Hsup / g.h3D[i].Poligono[j].Dab
								*(PotencialV_j-PotencialV_i)*Datos_cf;

						//						if (iiter==0 ) cout<<"g.Cara[iC].iBC="<<g.Cara[iC].iBC<<endl;
						if (1==0) cout<<"g.Cara[iC].BC2="<<g.Cara[iC].BC2
								<<"\t.BC="<<g.Cara[iC].BC
								<<"\tg.Cara[iC].iBC="<<g.Cara[iC].iBC
								<<"\tiC="<<iC
								<<"\tCoeff_Difusion="<<Coeff_Difusion
								<<"\tPotencialV_i="<<PotencialV_i<<"PotencialV_j="<<PotencialV_j
								<<endl;
						SumaCoeffDif_F2 += g.Cara[iC].BC2 * Coeff_Difusion;
						SumaCoeffDif += Coeff_Difusion;
					}
					if (g.Cara[iC].iBC ==11 ) {
						Coeff_Difusion=Datos_htilde*g.h3D[i].Poligono[j].AreaPoligono;;
						SumaCoeffDif_F2 += Coeff_Difusion*Datos_Tambiente;
						SumaCoeffDif    += Coeff_Difusion;
						//Evaporacion
						SumaCoeffDif_F2 -= Datos_CalorLatenteFluido*Psi_ev(Temp[i])*g.h3D[i].Poligono[j].AreaPoligono;
					}

				}
			}
			nTemp = SumaCoeffDif_F2/SumaCoeffDif;
			err=fabs(nTemp-Temp[i])/(fabs(nTemp)+1e-20);
			if (err>1) {
				cout <<"i="<<i
						<<"\tiiter="<<iiter
						<< "\tTemperatura previa="<<Temp[i]
														 <<"\t Nueva="<<nTemp;
				nTemp=Temp[i]+0.3*(nTemp-Temp[i]);
				cout <<"\t Nueva2="<<nTemp<<endl;

			} else {
				nTemp=Temp[i]+0.7*(nTemp-Temp[i]);
			}
			err=fabs(nTemp-Temp[i])/(fabs(nTemp)+1e-20);
			if (err > errG) errG=err;
			Temp[i]=nTemp;
			//			if (F[i]==0) F[i]=0.5;
		}
		if (errG<err0) {
			cout<<"break: errG<"<<err0<<", iiter="<<iiter<<endl;
			myfileSalida<<"break: errG<"<<err0<<", iiter="<<iiter<<endl;
			break;
		}
	}
	for (i=0 ; i<g.nH3D ; i++) {
		double A,AA,AB,AC,RA;
		double BA,BB,BC,RB;
		double CA,CB,CC,RC;
		double nx,ny,nz,DET;
		AA=0;AB=0;AC=0;RA=0;
		BA=0;BB=0;BC=0;RB=0;
		CA=0;CB=0;CC=0;RC=0;
		for (j=0 ; j< g.h3D[i].vecino.size() ;j++) {
			if (g.h3D[i].tipo_vecino[j] == ES_BLOQUE) {
				Coeff_Difusion = ( Temp[ g.h3D[i].vecino[j] ] - Temp[i] ) / g.h3D[i].Poligono[j].Dab;
			} else {
				iC=g.h3D[i].vecino[j];
				Coeff_Difusion=0;
				if (g.Cara[iC].iBC ==2 ||g.Cara[iC].iBC ==3) {
					Coeff_Difusion = ( g.Cara[iC].BC2 - Temp[i] ) / g.h3D[i].Poligono[j].Dab;

				}
			}
			A=g.h3D[i].Poligono[j].AreaPoligono;
			nx=g.h3D[i].Poligono[j].normal.x ;
			ny=g.h3D[i].Poligono[j].normal.y ;
			nz=g.h3D[i].Poligono[j].normal.z ;
			AA += nx*nx*A; AB+= nx*ny*A; AC+= nx*nz*A; RA += -nx*Coeff_Difusion*A;
			BA += ny*nx*A; BB+= ny*ny*A; BC+= ny*nz*A; RB += -ny*Coeff_Difusion*A;
			CA += nz*nx*A; CB+= nz*ny*A; CC+= nz*nz*A; RC += -nz*Coeff_Difusion*A;
		}
		// AA AB AC --> RA
		// BA BB BC --> RB
		// CA CB CC --> RC
		DET= AA*(BB*CC-BC*CB)+BA*(CB*AC-AB*CC)+CA*(AB*BC-BB*AC) ;
		U[i]= ( RA*(BB*CC-BC*CB)+RB*(CB*AC-AB*CC)+RC*(AB*BC-BB*AC) )/DET;
		V[i]=-( RA*(BA*CC-BC*CA)+RB*(CA*AC-AA*CC)+RC*(AA*BC-BA*AC) )/DET;
		W[i]= ( RA*(BA*CB-BB*CA)+RB*(CA*AB-AA*CB)+RC*(AA*BB-BA*AB) )/DET;
	}
	return(errG);
}

double MediaArmonica(double h1,double h2)
{
 return ((h1*h2) / (h1+h2));
}

double CalculaTemperaturaPilaEnTmasDt(vector<double> &Temp,vector<double> &PotencialV,vector<double> &U,
		vector<double> &V,vector<double> &W,grid3D g,int niteraciones,double err0,vector<double> &TempPrevia)
{
	int iiter,i,j,iC;
	double SumaCoeffDif_F2,SumaCoeffDif,Coeff_Difusion,err,errG,nF,SumaVolumen;
	if (Temp.size() ==0) Temp.resize(g.nH3D);
	//Resuelvo la ecuación varias veces
	niteraciones=g.nH3D*50;
	if (niteraciones<30000) niteraciones=30000;
	cout <<"niteraciones="<<niteraciones<<endl;
	myfileSalida <<"niteraciones="<<niteraciones<<endl;
	double SumCoeffEstacionarios=0,SumCoeffTemporales=0;
	int    NCoeffEstacionarios=0;
	for (iiter=0 ; iiter<niteraciones ; iiter++) {
		errG=0;
		for (i=0 ; i<g.nH3D ; i++) {
			//Escribo la ecuación para cada hexahedro [i]
			SumaCoeffDif_F2=0;SumaCoeffDif=0;SumaVolumen=0;
			double PotencialV_i=PotencialV[i],PotencialV_j;
			for (j=0 ; j< g.h3D[i].vecino.size() ;j++) {
				if(1==0) cout <<"CalculaLaplacianoCero2: iiter,i,j="<<iiter<<" "<<i<<" "<<j
						<< "\tPotencialV_.size=" << PotencialV.size()
						<<"\tg.h3D[i].vecino[j]="<<g.h3D[i].vecino[j]
																   <<"\tg.h3D[i].tipo_vecino[j]="<<g.h3D[i].tipo_vecino[j]
																														<<endl;
				//recorro cada vecino==cara [i]--[j]

				if (g.h3D[i].tipo_vecino[j] == ES_BLOQUE) {
					PotencialV_j=PotencialV[ g.h3D[i].vecino[j] ];
					if (PotencialV_j>PotencialV_i)
						Coeff_Difusion = Datos_rhof * Datos_cf *(PotencialV_j-PotencialV_i) *
						g.h3D[i].Poligono[j].AreaPoligono / g.h3D[i].Poligono[j].Dab;
					else Coeff_Difusion=0;

					Coeff_Difusion += Datos_km * g.h3D[i].Poligono[j].AreaPoligono / g.h3D[i].Poligono[j].Dab;

					SumaCoeffDif_F2 += Coeff_Difusion * Temp[ g.h3D[i].vecino[j] ] ;
					SumaCoeffDif    += Coeff_Difusion;
				} else {
					iC=g.h3D[i].vecino[j];
					double htilde_local;
					//if (g.Cara[iC].iBC==1) Se trata de Derivada normal igual a cero (nada que hacer)
					switch (g.Cara[iC].iBC) {
					case 2:
					case 3:   //Condicion Dirichlet (como un bloque con T conocida == BC2)
						PotencialV_j=g.Cara[iC].BC;
						if (PotencialV_j>PotencialV_i)
							Coeff_Difusion = Datos_rhof * Datos_cf *(PotencialV_j-PotencialV_i) *
							g.h3D[i].Poligono[j].AreaPoligono / g.h3D[i].Poligono[j].Dab;
						else Coeff_Difusion=0;

						Coeff_Difusion += Datos_km * g.h3D[i].Poligono[j].AreaPoligono / g.h3D[i].Poligono[j].Dab;

						if (1==0) cout<<"g.Cara[iC].BC2="<<g.Cara[iC].BC2
								<<"\t.BC="<<g.Cara[iC].BC
								<<"\tg.Cara[iC].iBC="<<g.Cara[iC].iBC
								<<"\tiC="<<iC
								<<"\tCoeff_Difusion="<<Coeff_Difusion
								<<"\tPotencialV_i="<<PotencialV_i<<"PotencialV_j="<<PotencialV_j
								<<endl;
						SumaCoeffDif_F2 += Coeff_Difusion * g.Cara[iC].BC2;
						SumaCoeffDif    += Coeff_Difusion;
						break;

					case 11:   // Cara convectiva abajo
						htilde_local=MediaArmonica(Datos_km/(g.h3D[i].Poligono[j].Dab/2),Datos_hc_inferior);

						Coeff_Difusion=htilde_local*g.h3D[i].Poligono[j].AreaPoligono;
						SumaCoeffDif_F2 += Coeff_Difusion * Datos_Tambiente;
						SumaCoeffDif    += Coeff_Difusion;
						break;
					case 12:   // Cara convectiva lateral
						htilde_local
						=MediaArmonica(Datos_km/(g.h3D[i].Poligono[j].Dab/2),Datos_km2/Datos_DistanciaAlBorde);
						htilde_local=MediaArmonica(htilde_local,Datos_hc_lateral);
						Coeff_Difusion=htilde_local*g.h3D[i].Poligono[j].AreaPoligono;
						SumaCoeffDif_F2 += Coeff_Difusion * Datos_Tambiente;
						SumaCoeffDif    += Coeff_Difusion;
						break;
					}

				}
			}

			if (TipoCalculo==CalculoEvolucion) {
				///////////////////Aporte del termino temporal.....
				double CoeffT=Datos_rhom*Datos_cm*g.h3D[i].volumen/Datos_dt;

				//Estadistica (cual es mas importante)
				SumCoeffEstacionarios += SumaCoeffDif;
				SumCoeffTemporales    += CoeffT;
				NCoeffEstacionarios   ++;


				SumaCoeffDif_F2 += CoeffT*TempPrevia[i];
				SumaCoeffDif    += CoeffT;
			}
			nF = SumaCoeffDif_F2/SumaCoeffDif;
			err=fabs(nF-Temp[i])/(fabs(nF)+1e-20);
			if (err > errG) errG=err;
			Temp[i]=nF;
			//			if (F[i]==0) F[i]=0.5;
		}
		if (errG<err0) {
			cout<<"break: errG<"<<err0<<endl;
			myfileSalida<<"break: errG<"<<err0<<endl;
			break;
		}
	}
	cout<<"iiter_final="<<iiter<<endl;
	myfileSalida<<"iiter_final="<<iiter<<endl;
	if (TipoCalculo==CalculoEvolucion) {
		//Estadistica (cual es mas importante)
		cout << "<CoeffEstacionarios>="<<SumCoeffEstacionarios /NCoeffEstacionarios;
		cout << "\t<SumCoeffTemporales>="<<SumCoeffTemporales / NCoeffEstacionarios <<endl;
		myfileSalida << "<CoeffEstacionarios>="<<SumCoeffEstacionarios /NCoeffEstacionarios;
		myfileSalida << "\t<SumCoeffTemporales>="<<SumCoeffTemporales / NCoeffEstacionarios <<endl;
	}
	for (i=0 ; i<g.nH3D ; i++) {
		double A,AA,AB,AC,RA;
		double BA,BB,BC,RB;
		double CA,CB,CC,RC;
		double nx,ny,nz,DET;
		AA=0;AB=0;AC=0;RA=0;
		BA=0;BB=0;BC=0;RB=0;
		CA=0;CB=0;CC=0;RC=0;
		for (j=0 ; j< g.h3D[i].vecino.size() ;j++) {
			if (g.h3D[i].tipo_vecino[j] == ES_BLOQUE) {
				Coeff_Difusion = ( Temp[ g.h3D[i].vecino[j] ] - Temp[i] ) / g.h3D[i].Poligono[j].Dab;
			} else {
				iC=g.h3D[i].vecino[j];
				Coeff_Difusion=0;
				if (g.Cara[iC].iBC ==2 ||g.Cara[iC].iBC ==3) {
					Coeff_Difusion = ( g.Cara[iC].BC2 - Temp[i] ) / g.h3D[i].Poligono[j].Dab;

				}
			}
			A=g.h3D[i].Poligono[j].AreaPoligono;
			nx=g.h3D[i].Poligono[j].normal.x ;
			ny=g.h3D[i].Poligono[j].normal.y ;
			nz=g.h3D[i].Poligono[j].normal.z ;
			AA += nx*nx*A; AB+= nx*ny*A; AC+= nx*nz*A; RA += -nx*Coeff_Difusion*A;
			BA += ny*nx*A; BB+= ny*ny*A; BC+= ny*nz*A; RB += -ny*Coeff_Difusion*A;
			CA += nz*nx*A; CB+= nz*ny*A; CC+= nz*nz*A; RC += -nz*Coeff_Difusion*A;
		}
		// AA AB AC --> RA
		// BA BB BC --> RB
		// CA CB CC --> RC
		DET= AA*(BB*CC-BC*CB)+BA*(CB*AC-AB*CC)+CA*(AB*BC-BB*AC) ;
		U[i]= ( RA*(BB*CC-BC*CB)+RB*(CB*AC-AB*CC)+RC*(AB*BC-BB*AC) )/DET;
		V[i]=-( RA*(BA*CC-BC*CA)+RB*(CA*AC-AA*CC)+RC*(AA*BC-BA*AC) )/DET;
		W[i]= ( RA*(BA*CB-BB*CA)+RB*(CA*AB-AA*CB)+RC*(AA*BB-BA*AB) )/DET;
	}
	return(errG);
}


void CB_keyboard(unsigned char key, int x, int y)
{

	double gLeft=-.1,gRight=.1, gBottom=-.1, gTop=.1, gNear=0, gFar=1000000;
	//cout<<"CB_keyboard()"<<endl;
	//printf("CB_keyboard: char=%d(%c), x=%d, y=%d",key,key,x,y);	cout<<endl;

	switch(key) {
	case 27: /* ESC */
		exit(0);
		break;

	case 32: /* Espacio */
		cout<<"Lanzo Calculo_EtapaS()"<<Etapa<<endl;
		Calculo_EtapaS();
		break;
	case 8: /* BackSpace */
		cout<<"Etapa="<<Etapa<<",InicioEtapa="<<InicioEtapa<<endl;
		Etapa=InicioEtapa-1;
		Calculo_EtapaS();
		break;
	case '1': 
		//Calculo_EtapaS(true);
		break;
	case 'W':
	case 'w':
		DrawMensajesDatosGui3();
		glui3->show();
		break;
	case 'v':
	case 'V':
		gluiHelp->set_int_val(!MODO_MenuMENSAJES);
		MODO_MenuMENSAJES=gluiHelp->get_int_val();
		if (MODO_MenuMENSAJES)
			DrawMensajesDatos();
		break;
	case 'n':
	case 'N':
		gluiNormales->set_int_val(!gluiNormales->int_val);
		break;
	case 'b':
	case 'B':
		gluiBordes->set_int_val(!ModoDibujaFrontera);ModoDibujaFrontera=gluiBordes->get_int_val();
		break;
	case 'i':
	case 'I':
		gluiInterior->set_int_val(!ModoDibujaInterior);ModoDibujaInterior=gluiInterior->get_int_val();
		break;


#if defined(GLUI_GLUI_H)
	case 'Z':
	case 'z':
		if (glui_hide) 		
			glui->show();
		else 		
			glui->hide();
		glui_hide=!glui_hide;
		ResizeGraphics(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
		break;
#endif
	case 'T':
	case 't':
		glui_GrupoModoDelMouse->set_int_val(0);MODO_de_mover=glui_GrupoModoDelMouse->get_int_val();
		break;
	case 'R':
	case 'r':

		//		glLoadIdentity();
		//		glOrtho(gLeft, gRight, gBottom, gTop, gFar, -gFar);
		//		glGetFloatv( GL_MODELVIEW_MATRIX, (GLfloat*)MatrizRotacionGlobal );
		//		TrasponeMatriz();

		glui_GrupoModoDelMouse->set_int_val(1);MODO_de_mover=glui_GrupoModoDelMouse->get_int_val();
		break;
	case 'S':
	case 's':
		glui_GrupoModoDelMouse->set_int_val(2);MODO_de_mover=glui_GrupoModoDelMouse->get_int_val();
		break;
	case 'E':
	case 'e':
		glui_GrupoModoDelMouse->set_int_val(3);MODO_de_mover=glui_GrupoModoDelMouse->get_int_val();
		break;
	case '+':
		if (NumON==1 ) {
			NumEscala /=1.2;
		} else {
			char s[100];
			npasadas*=2; 
			if (npasadas>maxpasadas) 	npasadas=maxpasadas;
			sprintf(s,"(+)=npasadas++=%d",npasadas);
			AddMensaje(s);
		}
		break;
	case '-':
		if (NumON==1 ) {
			NumEscala *=1.2;
		} else {
			char s[100];
			npasadas/=2; 
			if (npasadas<=0) 				npasadas=1;
			sprintf(s,"(-)=npasadas--=%d",npasadas);
			AddMensaje(s);
		}
		break;
	case 'M':
	case 'm':
		//TODO
		gluiMueve->set_int_val(!MueveCentro);MueveCentro=gluiMueve->get_int_val();
		if (MueveCentro)    {
			AddMensajeRight((char *)"M=Mueve Centro");
			cout<<"E vecUEsfera="<<vecUEsfera[0]<<","<<vecUEsfera[1]<<"."<<vecUEsfera[2]<<","<<vecUEsfera[3]<<endl;

			Add_Particulas=0;
		}
		else  {
			AddMensajeRight("");AddMensajeRight("");
		}
		break;
	case 'A': //Add particulas con el mouse
	case 'a':
		Add_Particulas=1-Add_Particulas;
		if (Add_Particulas) {
			AddMensajeRight((char *)"A=Add Particulas");
			MueveCentro=0;

		} else {
			AddMensajeRight("");AddMensajeRight("");
		}
		break;
	case 'P':
	case 'p':
		gluiClipping->set_int_val(!ClippingON);ClippingON=gluiClipping->get_int_val();
		/*
		ClippingON=1-ClippingON;
		 */
		if (ClippingON)    AddMensaje("P= Cli(P)ping on..");
		else                AddMensaje("P= Cli(P)ping off..");
		break;
	case 'C':
	case 'c':
		cout<<"case 'C': ColorON="<<ColorON<<"-->";
		ColorON++;
		if (ColorON==1 & F.size()!=gtotal->nV3D) ColorON++;
		if (ColorON==1 & EtapaGlobal==ETAPA_CALCULO_T_PILA) ColorON++;

		if (ColorON==2 & F2Nodos.size()!=gtotal->nV3D) ColorON++;


		if (ColorON>3)
			ColorON=0;
		if (ColorON)    AddMensaje("C= Color on..");
		else                AddMensaje("C= Color off..");
		cout<<ColorON<<endl;

		break;

	case 'F':
	case 'f':
		fullscreen = !fullscreen;
		if (fullscreen) {
			old_x = glutGet(GLUT_WINDOW_X);
			old_y = glutGet(GLUT_WINDOW_Y);
			old_width = glutGet(GLUT_WINDOW_WIDTH);
			old_height = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();
		} else {
			glutReshapeWindow(old_width, old_height);
			glutPositionWindow(old_x, old_y);
		}
		break;

	case 'G':
	case 'g':
		ModoGame++;if (ModoGame>3) ModoGame=0;
		printf("ModoGame=%d\n",ModoGame);
		switch (ModoGame) 
		{
		case 1:
		case 2:
		case 3:
			if (ModoGame==1) glutGameModeString("1280x1024:32@60");
			if (ModoGame==2) glutGameModeString("800x600:16@60");
			if (ModoGame==3) glutGameModeString("640x480:16@60");
			glutEnterGameMode();

			main_window = glutGetWindow();
			//		initWindow();
			glutDisplayFunc(DrawGraphics);
			glutReshapeFunc(ResizeGraphics);
			glutMouseFunc(CB_mouse);
			glutMotionFunc(CB_motion);
			glutKeyboardFunc(CB_keyboard);
			glutSpecialFunc( CB_keyboardSpecial );

			glutIdleFunc( idleevent );
			glutVisibilityFunc(visible);
			inicializacionGL();
			DrawGraphics();

			break;
		case 0:

			glutLeaveGameMode();
			main_window = glutGetWindow();
			glutDisplayFunc(DrawGraphics);
			glutReshapeFunc(ResizeGraphics);
			glutMouseFunc(CB_mouse);
			glutMotionFunc(CB_motion);
			glutKeyboardFunc(CB_keyboard);
			glutSpecialFunc( CB_keyboardSpecial );

			glutIdleFunc( idleevent );
			glutVisibilityFunc(visible);
			inicializacionGL();
			DrawGraphics();
			break;
		}
	}
	//cout<<"CB_keyboard():END"<<endl;
}


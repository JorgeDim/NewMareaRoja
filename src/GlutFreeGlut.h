#pragma once

#define UsarFreeGlut 0
#ifdef __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        #include <GLUT/glut.h>
        #include <OpenGL/OpenGL.h>
//        #define mkdir(x) system(sprintf("mkdir %s",((x))))
    #endif
#elif defined _WIN32 || defined _WIN64
	#if UsarFreeGlut==1
		#include "GL/freeglut.h"
		#define GLUI_FREEGLUT 1
	#else
		#include "GL/glut.h"
	#endif
		#include "GL/glui.h"
	//#ifdef _WIN32
	#include <windows.h>
	#include <Commdlg.h>
//   #define mkdir(x,y) _mkdir((x))
//   #define rmdir(x) _rmdir((x))
   #define getcwd _getcwd

#endif

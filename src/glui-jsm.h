//#pragma once


#ifdef __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        #include <GLUT/glut.h>
        #include <OpenGL/OpenGL.h>
		#include "GLUI/glui.h"

    #endif
#elif defined _WIN32 || defined _WIN64
	#include "GL/freeglut.h"
	//#include <GL\glut.h>
	#define GLUI_FREEGLUT 1
	//#include "GL/glut.h"
	#include "GL/glui.h"

#endif
#include <sys/types.h>

#ifdef __GNUC__
#include <dirent.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <sys/stat.h>


class GLUI_FileBrowser2 : public GLUI_FileBrowser
{
	
public:
    void fbreaddir(const char *);
    static void dir_list_callback(GLUI_Control*);
    GLUI_FileBrowser2( GLUI_Node *parent, 
                      const char *name,
                      int frame_type = GLUI_PANEL_EMBOSSED,
                      int user_id = -1,
                      GLUI_CB callback = GLUI_CB());
    const char* get_file() { return file.c_str(); }
	
    GLUI_List *list2;
    GLUI_Panel *panel;
    GLUI_EditText *EditText_archivo;
	static void control_cb(GLUI_Control*);
    void set_allow_change_dir(int c) { allow_change_dir = c; }

    void set_w(int w) {};
    void set_h(int h) {};

	char filtro[200];
	char archivo[200];
	int entrando;
//private:
    int last_item;
    GLUI_String file;
    GLUI_StaticText *mensaje1;
    GLUI_Listbox *disk;
    int allow_change_dir;
};


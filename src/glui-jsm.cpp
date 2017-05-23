#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//#include <fstream>
#include <iomanip>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/timeb.h>

#include "glui-jsm.h"
#include "Macros.h"



#ifdef _WIN32 || defined _WIN64
   #define getcwd _getcwd

#endif

extern char  texto[200];
int var_live_disk=0;

using namespace std;
/****************************** GLUI_FileBrowser::draw() **********/

GLUI_FileBrowser2::GLUI_FileBrowser2( GLUI_Node *parent, 
		const char *name,
		int type,
		int id,
		GLUI_CB cb) : GLUI_FileBrowser( parent, name,
				type,
				id,
				cb)
{

	printf("GLUI_FileBrowser2::GLUI_FileBrowser2");std::cout<<std::endl;

	/*//Hecho por constructor heredado
  common_init();

  set_name( name );
  user_id    = id;
  int_val    = type;
  callback   = cb;

  parent->add_control( this );
  list = new GLUI_List(this, true, 1);
  list->set_object_callback( GLUI_FileBrowser::dir_list_callback, this );
  list->set_click_type(GLUI_DOUBLE_CLICK);
  this->fbreaddir(this->current_dir.c_str());
	 */

	if (DBG) cout<<"55"<<endl;
	cout<<"57"<<endl;
	cout<<"list="<<list<<endl;
	if (list==NULL) {
		 common_init();

		  set_name( name );
		  user_id    = id;
		  int_val    = type;
		  callback   = cb;

		  parent->add_control( this );
		  list = new GLUI_List(this, true, 1);
		  list->set_object_callback( GLUI_FileBrowser::dir_list_callback, this );
		  list->set_click_type(GLUI_DOUBLE_CLICK);
		  this->fbreaddir(this->current_dir.c_str());
	}
	cout<<"list->name"<<list->name<<endl;
	list->set_object_callback( GLUI_FileBrowser2::dir_list_callback, this );
	if (DBG) cout<<"55"<<endl;

	GLUI_StaticText *tmp= new GLUI_StaticText(this,"Directorio:");
	if (DBG) cout<<"55"<<endl;
	{
		//Intercambio el orden de objetos para que el Titulo esté antes.
		tmp->unlink();
		tmp->link_this_to_parent_first( this );
	}
	if (DBG) cout<<"55"<<endl;
	/*
  this->add_control( list );
  new GLUI_Column( this, false );
  this->add_control( list->scrollbar );
	 */
	list->set_w(200);
	if (DBG) cout<<"55"<<endl;
	list->set_h(300);
	if (DBG) cout<<"55"<<endl;

	strcpy(filtro,"*.*");
	strcpy(archivo,"a");


	this->mensaje1=new GLUI_StaticText(this,"Archivo:");

	this->disk=new GLUI_Listbox(this,"Disco",&var_live_disk,12, cb );
	this->disk->do_selection(2);

#if defined _WIN32 || defined _WIN64
	 DWORD drives = GetLogicalDrives();
	 for (int i=0; i<26; i++)
	 {
	    if( ( drives & ( 1 << i ) ) )
	    {
	       char driveName[] = { 'A' + i, ':', '\\', '\0' };
	       if (DBG) cout<< driveName <<endl;
	    	int item=0;
	    	if (GetDriveType(driveName)==DRIVE_FIXED) {
	    		this->disk->add_item(++item,driveName);
	    	}
	    }
	 }

	 if (DBG) cout<<"this->disk->can_activate="<<this->disk->can_activate<<endl;
#endif


	new GLUI_Column( this, false );
	new GLUI_StaticText(this,"Archivo:");
	list2 = new GLUI_List(this, true, 1);
	list2->set_name("list2");
	list2->set_w(500);
	list2->set_h(300);
	if (DBG) std::cout<<"53"<<std::endl;

	list2->set_object_callback( GLUI_FileBrowser2::dir_list_callback, this );

	if (DBG) std::cout<<"92"<<std::endl;

	list2->set_click_type(GLUI_DOUBLE_CLICK);
	list2->set_click_type(GLUI_SINGLE_CLICK);
	//  this->fbreaddir(this->current_dir.c_str());
	if (DBG) cout <<"this->current_dir.c_str()=" << this->current_dir.c_str()<<endl;
	std::cout<<"96"<<std::endl;
	new GLUI_EditText( this, "Filtro:", GLUI_EDITTEXT_TEXT, filtro , 8, this->control_cb );
	if (DBG) std::cout<<"92"<<std::endl;
	EditText_archivo=new GLUI_EditText( this, "File:", GLUI_EDITTEXT_TEXT, archivo , 7, this->control_cb );
	EditText_archivo->set_w(500);
	if (DBG) std::cout<<"92"<<std::endl;

	new GLUI_Button(this,"OK",7,cb);


	{
		char cCurrentPath[FILENAME_MAX];
		getcwd(cCurrentPath, sizeof(cCurrentPath));

		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

		printf ("The current working directory is %s", cCurrentPath);cout<<endl;
		this->mensaje1->set_text(cCurrentPath);
	}


	if (DBG) printf("GLUI_FileBrowser2::GLUI_FileBrowser2::END\n");std::cout<<std::endl;

}

#if defined _WIN32 || defined _WIN64
void  char2LPCWSTR(const char *charstring ,LPCWSTR lpcwstr )
{
	std::wstring widestring;

	for (unsigned int i = 0; i < strlen(charstring); i++)
		widestring += (wchar_t)charstring[i];
	lpcwstr = widestring.c_str();
}
#endif


void GLUI_FileBrowser2::control_cb( GLUI_Control *glui_object)
{
	static int exec_prev=0;
	GLUI_EditText *EditText = dynamic_cast<GLUI_EditText*>(glui_object);

	printf("GLUI_FileBrowser2::control_cb(");cout<<EditText->name<<')'<<endl;


	if (!EditText)
		return;
	GLUI_FileBrowser2 *me = dynamic_cast<GLUI_FileBrowser2 *>(EditText->parent());
	if (!me)
		return;

	if (EditText->name.compare("File:")==0) {
		if (me->entrando==1) {
			me->entrando=0;
			EditText->active=false;
			me->execute_callback();
			}
	} else {

		exec_prev=0;

		me->fbreaddir(".");
	}

}

	void GLUI_FileBrowser2::dir_list_callback(GLUI_Control *glui_object)
{


	static unsigned long int ms_prev;
	unsigned long int ms;
	timeb time;
	ftime(&time);
	ms = time.millitm + (time.time)*1000;

	GLUI_List *list = dynamic_cast<GLUI_List*>(glui_object);

	printf("GLUI_FileBrowser2::dir_list_callback(");cout<<list->name<<')'<<endl;
	if (!list)
		return;

	GLUI_FileBrowser2 *me = dynamic_cast<GLUI_FileBrowser2 *>(list->associated_object);
	if (!me)
		return;


	int this_item;
	std::string jsm_str ;

	const char *selected;
	this_item = list->get_current_item();
	if (this_item >= 0) { /* file or directory selected */
		jsm_str=list->get_item_ptr( this_item )->text;
		selected = jsm_str.c_str();
		if (selected[0] == '/' || selected[0] == '\\') {
			if (DBG) cout<<"127"<<endl;
			if (DBG) cout<<"me->allow_change_dir="<<me->allow_change_dir<<endl;
			if (me->allow_change_dir) {
#ifdef __GNUC__
				chdir(selected+1);
				if (DBG) cout<<"131"<<endl;
#endif
#ifdef _WIN32

				if (DBG) cout<<"135"<<endl;
				// 	LPCWSTR lpcwstr_selected;
				char * lpcwstr_selected;
				std::wstring widestring;

				for (unsigned int i = 0; i < strlen(selected); i++)
					widestring += (wchar_t)selected[i];
				lpcwstr_selected = (char *)widestring.c_str();

				//	char2LPCWSTR(selected,lpcwstr_selected);
				SetCurrentDirectory(lpcwstr_selected+1);
#endif
				me->fbreaddir(".");
			}
		} else {
			me->file = selected;
			me->current_dir;
			strcpy(me->archivo,selected);
			me->sync_live(1,1);

			if (DBG) cout <<"ms-ms_prev="<< ms-ms_prev<< endl;
			if (ms-ms_prev<250) {
				if (DBG) cout<<"Doble Click"<<endl;
				me->execute_callback();
			}
			ms_prev=ms;

		}
		if (DBG) cout <<"177: selected="<< selected <<endl;
		if (DBG) cout <<"178: me->current_dir="<< me->current_dir <<endl;


		 char cCurrentPath[FILENAME_MAX];

		getcwd(cCurrentPath, sizeof(cCurrentPath));

		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

		if (DBG) printf ("The current working directory is %s", cCurrentPath);cout<<endl;
		me->mensaje1->set_text(cCurrentPath);
	}
}



void GLUI_FileBrowser2::fbreaddir(const char *d) {
	GLUI_String item;
	int i = 0;

	if (!d)
		return;

#ifdef _WIN32

	WIN32_FIND_DATAW FN;
	HANDLE hFind;
	//char search_arg[MAX_PATH], new_file_path[MAX_PATH];
	printf("GLUI_FileBrowser2::fbreaddir(%s)\n", d);

	hFind = FindFirstFileW(L"*.*", &FN);
	if (list) {
		list->delete_all();
		list2->delete_all();
		printf("list->delete_all()\n" );
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
					list->add_item(i,item.c_str());i++;
				} else {
					item = nstring;
					//		  list->add_item(i,item.c_str());;i++;
				}
			} while (FindNextFileW(hFind, &FN) != 0);

			if (GetLastError() == ERROR_NO_MORE_FILES)
				FindClose(&FN);
			else
				perror("fbreaddir");
		}
	}


	LPCWSTR lpcwstr;
	std::wstring widestring;

	for (int i = 0; i < strlen(texto); i++)
		widestring += (wchar_t)filtro[i];
	lpcwstr = widestring.c_str();


	i=0;
	hFind = FindFirstFileW(lpcwstr, &FN);
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
				//		  list->add_item(i,item.c_str());;i++;
			} else {
				item = nstring;
				list2->add_item(i,item.c_str());;i++;
				if (i==1) {
					strcpy(archivo,item.c_str());
				}
			}
		} while (FindNextFileW(hFind, &FN) != 0);

		if (GetLastError() == ERROR_NO_MORE_FILES)
			FindClose(&FN);
		else
			perror("fbreaddir");
	}

	sync_live(1,1);

#elif defined(__GNUC__)

	DIR *dir;
	struct dirent *dirp;
	struct stat dr;

	if (list) {
		list->delete_all();
		if ((dir = opendir(d)) == NULL)
			perror("fbreaddir:");
		else {
			while ((dirp = readdir(dir)) != NULL)   /* open directory     */
			{
				if (!lstat(dirp->d_name,&dr) && S_ISDIR(dr.st_mode)) /* dir is directory   */
					item = dirp->d_name + GLUI_String("/");
				else
					item = dirp->d_name;

				list->add_item(i,item.c_str());
				i++;
			}
			closedir(dir);
		}
	}
#endif
}

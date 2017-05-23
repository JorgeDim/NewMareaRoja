//#pragma once

#ifndef _CLASS_VECTOR_H
#define _CLASS_VECTOR_H 1
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <assert.h>
#include <time.h>
//#include "CheckPtr.h"  // use it to check memory leaks
#define mmax(a,b)(a>b?a:b)
#define mmin(a,b)(a<b?a:b)
 
template <class T> class Vector
{
 public: 
    T *cc;
    int size;
	static int const Vectordebug=1;
        
    Vector(int csize = 0){init (csize);}
    void  init(int csize = 0);
    void destroy()
    {
        delete [] cc;
        size = 0; 
    }  
    ~Vector() 
    {
        destroy();
    }  
    
    T&  operator [](int i) const
    {
        assert ( cc &&(i >= 0)&&(i < size) ); 
        return cc[i];
    }
    Vector ( const Vector& v );
    const Vector& operator = (const T& r);
    const Vector& operator= ( const Vector& v);
    Vector& operator += (const Vector& v1);
    Vector  operator + (const Vector& v1);
    Vector  proy(const Vector& v1);
    Vector& operator -= (const Vector& v1);
    Vector  operator - (const Vector& v1);
    Vector  operator* (const double& a);
    Vector  operator/ (const double& a);
    void show();
    
void load(char* path1,char* path2);

void load(char* path);

void save(char* path,int precision=10);
void save(char* path1,char* path2,int precision=10);
};
                 
//#include "grid.h"
//#include "CMatricial.h"
//template <class T> 
//int p1top2(const Grid &gp1,const Vector<T> & vp1, Vector <T> &vp2);
template <class T> double norma2(const Vector<T>& v);
template <class T> double ppunto(const Vector<T>& v1,const Vector<T>& v2); 
template <class T> 
void Vector<T>::init(int csize)
{
    const T zero(0);
    size = csize; 
    if (size > 0 )
    { 
        cc = new T[size];
        for(int i=0;i<size;i++) cc[i] = zero;
    }
    else cc = NULL;
} 

template <class T> Vector<T>::Vector ( const Vector& v )
{
    size = v.size; 
    if (size > 0 ) cc = new T[size];  else cc = NULL;
    for(int i = 0; i<size;i++) cc[i] = v.cc[i];
}

template <class T> const Vector<T>&  Vector<T>::operator = ( const T& r)
{       
    for (int i=0; i<size;i++) cc[i] = r; 
    return *this;  
}

template <class T> const Vector<T>& Vector<T>::operator = ( const Vector<T>& v)
{       
    assert(v.size==size); 
    for (int i=0; i<size;i++) cc[i] = v.cc[i]; 
    return *this;  
}
template <class T> Vector<T>& Vector<T>::operator +=(const Vector<T>& v1)
{        
    assert(v1.size == size);
    for(int i=0;i<v1.size;i++) cc[i] += v1.cc[i]; 
    return *this;
}
template <class T> Vector<T> Vector<T>::operator +(const Vector<T>& v1)
{        
    assert(v1.size == size);
    Vector v(v1);
    for(int i=0;i<v1.size;i++) v.cc[i] += cc[i]; 
    return v;
}
template <class T> Vector<T>& Vector<T>::operator -=(const Vector<T>& v1)
{        
    assert(v1.size == size);
    for(int i=0;i<v1.size;i++) cc[i] -= v1.cc[i]; 
    return *this;
}
template <class T> Vector<T> Vector<T>::operator -(const Vector<T>& v1)
{        
    assert(v1.size == size);
    Vector v(*this);
    for(int i=0;i<v1.size;i++) v.cc[i] -= v1.cc[i]; 
    return v;
}
template <class T> Vector<T> Vector<T>::operator *(const double& a)
{        
    Vector v(size);
    for(int i=0;i<size;i++) v.cc[i] = cc[i] * a; 
    return v;
}
template <class T> Vector<T> Vector<T>::operator /(const double& a)
{        
    Vector v(size);
    for(int i=0;i<size;i++) v.cc[i] =  cc[i] / a; 
    return v;
}
template <class T> Vector<T> Vector<T>::proy (const Vector<T>& v1)
{        
    assert(v1.size == size);
    Vector v(v1);
    for(int i=0;i<v1.size;i++) v.cc[i] = cc[i].proy(v1[i]); //cc[i] != double
    //for(int i=0;i<v1.size;i++) v.cc[i] = cc[i]*(1.0-v1[i]); //cc[i] ==double
    return v;
}
template <class T> void Vector<T>::show()
{
    for(int i=0; i<size;i++){ std::cout<<i<<":"<<cc[i]<<std::endl;}
    std::cout<<"**"<<std::endl;
}

template <class T> 
void Vector<T>::load(char* path1,char* path2)
{
    char path[100];
    strcpy(path,path1);
    strcat(path,path2);
    load(path);
}
template <class T> 
void Vector<T>::load(char* path)
{  
    std::ifstream file(path);
    if (Vectordebug) std::cout <<"Vector::load(T:"<<sizeof(T)<<") File:" << path << "	n=" << size;
    if (file.fail()) std::cout <<"FILE NOT FOUND!!";
    int ns1;
    file >> ns1;
    if (Vectordebug) std::cout <<"="<<ns1<<std::endl;
    for(int i=0; i<ns1; i++) file >> cc[i];
    file.close();
}

using namespace std;


template <class T> 
void Vector<T>::save(char* path,int precision)
{  
	std::ofstream file(path);
        assert(!file.fail());
	std::cout <<"Vector::save (T:"<<sizeof(T)<<") File:"<<path<<"	precisión="
		<<precision<<"	n="<<size<<std::endl;
	file << size << std::endl;
	file<<setprecision (precision);
	for(int i=0; i<size; i++) file << cc[i] << std::endl;
        file.close();
}
template <class T> 
void Vector<T>::save(char* path1,char* path2,int precision)
{
    char path[100];
    strcpy(path,path1);
    strcat(path,path2);
    save(path,precision);
}
template <class T> double norma2(const Vector<T>& v) 
{
    double t=0;
    for (int i=0;i<v.size;i++) 
        t+=norma2(v.cc[i]);
    return t;
}
template <class T> double ppunto(const Vector<T>& v1,const Vector<T>& v2) 
{
    double t=0;
    for (int i=0;i<v1.size;i++) 
        t+=ppunto(v1.cc[i],v2.cc[i]);
    return t;
}
#endif 

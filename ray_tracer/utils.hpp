#ifndef __UTILS_H__
#define __UTILS_H__

#include <bits/stdc++.h>
#include <omp.h>
#define M_PI 3.1415926535897932384626433832795
#define INF 0x3f3f3f
#define eps 1e-6

typedef double ld;
typedef unsigned char uchar;
typedef unsigned short ushort;
using namespace std;

#ifndef __STB_IMAGE_H__
#define __STB_IMAGE_H__
#include "stb_image.h"
#endif

enum Refl_t { DIFF, SPEC, REFR };  // material types, used in radiance()
double erand48(ushort seed[3]){return (ld)rand()/(ld)RAND_MAX;}



inline double clamp(double x){ return x<0?0:x>1?1:x;}
inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }

struct Vec {
    ld x, y, z; // position, also color (r,g,b)
    Vec(ld x_=0,ld y_=0,ld z_=0):x(x_),y(y_),z(z_){}
    Vec operator+(const Vec &a) const{return Vec(x+a.x,y+a.y,z+a.z);}
    Vec operator-(const Vec &a) const{return Vec(x-a.x,y-a.y,z-a.z);}
    Vec operator+(ld p) const{return Vec(x+p,y+p,z+p);}
    Vec operator-(ld p) const{return Vec(x-p,y-p,z-p);}
    Vec operator*(ld p) const{return Vec(x*p,y*p,z*p);}
    Vec operator/(ld p) const{return Vec(x/p,y/p,z/p);}
    Vec&operator+=(const Vec&a) {return *this=*this+a;}
    Vec&operator-=(const Vec&a) {return *this=*this-a;}
    Vec&operator+=(ld p){return *this=*this+p;}
    Vec&operator-=(ld p){return *this=*this-p;}
    Vec&operator*=(ld p){return *this=*this*p;}
    Vec&operator/=(ld p){return *this=*this/p;}
    bool operator==(const Vec&a) const{return x==a.x && y==a.y &&z==a.z;}
    bool operator!=(const Vec&a) const{return x!=a.x || y!=a.y ||z!=a.z;}
    Vec operator%(Vec&a){return Vec(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x);}
    ld operator|(const Vec&a) const{return x*a.x+y*a.y+z*a.z;}
    ld len() const{return sqrt(x*x+y*y+z*z);}
    ld len2() const{return x*x+y*y+z*z;}
    Vec&norm(){return *this=(*this)/len();}
    Vec mult(const Vec&a) const{return Vec(x*a.x,y*a.y,z*a.z);}
    ld dot(const Vec&a) const{return x*a.x+y*a.y+z*a.z;}
    ld max() const{return x>y&&y>z?x:y>z?y:z;}
    ld min() const{return x<y&&y<z?x:y<z?y:z;}
    Vec max(const Vec&a) const{return Vec(std::max(x,a.x),std::max(y,a.y),std::max(z,a.z));}
    Vec min(const Vec&a) const{return Vec(std::min(x,a.x),std::min(y,a.y),std::min(z,a.z));}
    Vec clamp() {return Vec(x<0?0:x>1?1:x,y<0?0:y>1?1:y,z<0?0:z>1?1:z);}
    void print() const{
        std::cout<<x<<" "<<y<<" "<<z<<" "<<std::endl;
    }
};
#endif
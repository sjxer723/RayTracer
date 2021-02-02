#ifndef __OBJ_H__
#define __OBJ_H__

#include "utils.hpp"
#include "ray.hpp"
#include "texture.hpp"
#include <omp.h>

//Vec can denote position,emission,color;
//Refl_t:reflection type (DIFFuse, SPECular,REFRactive)

class Object{
public:
    Texture texture;
    Object(Texture t_):texture(t_){}
    Object(std::string _,ld b_,Vec c_,Vec e_,Refl_t r_):texture(_,b_,c_,e_,r_){}
    virtual ld intersect(Ray r){puts("virtual error in intersect!");}
};
class Sphere_object :public Object{
    ld rad;
    Vec p;
    Sphere_object(ld rad_,Vec p_,std::string _, ld b_, Vec c_,Vec e_,Refl_t r_):
        rad(rad_),p(p_),Object(_,b_,c_,e_,r_){}
    ld intersect(Ray r) const { // returns distance, 0 if nohit
        Vec op=p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
        ld t,b=op.dot(r.d),det=b*b-op.dot(op)+rad*rad;
        if (det<0) return 0; else det=sqrt(det);
        return (t=b-det)>eps?t:((t=b+det)>eps?t:0);
    }
};
struct Sphere {
    ld rad;
    Vec p,e,c;
    Refl_t refl;
    Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_t refl_):
        rad(rad_), p(p_), e(e_), c(c_), refl(refl_) {}
    ld intersect(Ray r) const { // returns distance, 0 if nohit
        Vec op=p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
        ld t,b=op.dot(r.d),det=b*b-op.dot(op)+rad*rad;
        if (det<0) return 0; else det=sqrt(det);
        return (t=b-det)>eps?t:((t=b+det)>eps?t:0);
    }
};
struct Cube {
    Vec m0,m1;
    Refl_t refl;
    Cube(Vec m0_,Vec m1_,Refl_t refl_):m0(m0_),m1(m1_),refl(refl_){}
    ld intersect(Ray r) const{
        ld ft=INF,t;
        Vec fq=Vec(),q;
        // x dir
        t=(m0.x-r.o.x)/r.d.x;
        if (0<t && t<ft){
            q=r.get(t);
            if (m0.y <= q.y && q.y <= m1.y && m0.z <= q.z && q.z <= m1.z)
                ft=t,fq=q;
        }
        t=(m1.x-r.o.x)/r.d.x;
        if (0<t && t<ft){
            q=r.get(t);
            if (m0.y <= q.y && q.y <= m1.y && m0.z <= q.z && q.z <= m1.z)
                ft=t, fq=q;
        }
        // y dir
        t=(m0.y-r.o.y)/r.d.y;
        if (0<t && t<ft){
            q=r.get(t);
            if (m0.x <= q.x && q.x <= m1.x && m0.z <= q.z && q.z <= m1.z)
                ft=t,fq=q;
        }
        t=(m1.y-r.o.y)/r.d.y;
        if (0<t && t<ft){
            q=r.get(t);
            if (m0.x <= q.x && q.x <= m1.x && m0.z <= q.z && q.z <= m1.z)
                ft=t, fq=q;
        }
        // z dir
        t=(m0.z-r.o.z)/r.d.z;
        if (0<t && t<ft){
            q=r.get(t);
            if (m0.x <= q.x && q.x <= m1.x && m0.y <= q.y && q.y <= m1.y)
                ft=t,fq=q;
        }
        t=(m1.z-r.o.z)/r.d.z;
        if (0<t && t<ft){
            q=r.get(t);
            if (m0.x <= q.x && q.x <= m1.x && m0.y <= q.y && q.y <= m1.y)
                ft=t, fq=q;
        }
        return ft;
    }
};
struct Plane { //store ax+by+cz=1 n=(a,b,c)
    Vec n,n0;
    Refl_t refl;
    Plane(Vec n_,Vec n0_,Refl_t refl_):n(n_),n0(n0_),refl(refl_){}
    ld intersect(Ray r)const{
        ld t=(1-r.o.dot(n))/(r.d.dot(n));
        if (t<eps) return INF; // parallel case
        return t;
    }

};
//Texture: Texture t1=Texture();
////Scene: radius, position, emission, color, material, texture
Sphere spheres[] = {
  Sphere(1e5, Vec( 1e5+1,40.8,81.6), Vec(),Vec(.75,.25,.25),DIFF),//Left
  Sphere(1e5, Vec(-1e5+99,40.8,81.6),Vec(),Vec(.25,.25,.75),DIFF),//Rght
  Sphere(1e5, Vec(50,40.8, 1e5),     Vec(),Vec(.75,.75,.75),DIFF),//Back
  Sphere(1e5, Vec(50,40.8,-1e5+170), Vec(),Vec(),           DIFF),//Frnt
  Sphere(1e5, Vec(50, 1e5, 81.6),    Vec(),Vec(.75,.75,.75),DIFF),//Botm
  Sphere(1e5, Vec(50,-1e5+81.6,81.6),Vec(),Vec(.75,.75,.75),DIFF),//Top
  Sphere(16.5,Vec(27,16.5,47),       Vec(),Vec(1,1,1)*.999, SPEC),//Mirr
  Sphere(16.5,Vec(73,16.5,78),       Vec(),Vec(1,1,1)*.999, REFR),//Glas
  Sphere(600, Vec(50,681.6-.27,81.6),Vec(12,12,12),  Vec(), DIFF) //Lite
};
#endif
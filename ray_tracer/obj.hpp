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
    virtual ld intersect(Ray){puts("virtual error in intersect!");}
    virtual Vec norm(Vec){puts("virtual in norm!");}
};
class Sphere_object :public Object{
public:
    ld rad;
    Vec p;
    Sphere_object(ld r_,Vec o_, Refl_t refl, ld brdf = 1.5, Vec color = Vec(), Vec e_ = Vec(), std::string s_ = ""):
		rad(r_),p(o_),Object(s_, brdf, color, e_,refl) {}
    virtual ld intersect(Ray r) { // returns distance, 0 if nohit
        Vec op=p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
        ld t,b=op.dot(r.d),det=b*b-op.dot(op)+rad*rad;
        if (det<0) return 0; else det=sqrt(det);
        return (t=b-det)>eps?t:((t=b+det)>eps?t:0);
    }
    virtual Vec norm(Vec x) { return (x-p).norm();}
};
class Cube_object:public Object{
public:
    Vec m0,m1;
    Cube_object(Vec m0_,Vec m1_, Refl_t refl, ld brdf = 1.5, Vec color = Vec(), Vec e_ = Vec(), std::string s_ = ""):
		m0(m0_),m1(m1_),Object(s_, brdf, color, e_,refl) {}
    virtual ld intersect(Ray r) {
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
    virtual Vec norm(Vec p) {
		if (std::abs(p.x - m0.x) < eps || std::abs(p.x - m1.x) < eps)
			return Vec(std::abs(p.x - m1.x) < eps ? 1 : -1, 0, 0);
		if (std::abs(p.y - m0.y) < eps || std::abs(p.y - m1.y) < eps)
			return Vec(0, std::abs(p.y - m1.y) < eps ? 1 : -1, 0);
		if (std::abs(p.z - m0.z) < eps || std::abs(p.z - m1.z) < eps)
			return Vec(0, 0, std::abs(p.z - m1.z) < eps ? 1 : -1);
		assert(1 == 0);
	}
};
class Plane_object: public Object { //store ax+by+cz=1 n=(a,b,c)
public:
    Vec n,n0;
    Plane_object(Vec n_,Vec n0_, Refl_t refl, ld brdf = 1.5, Vec color = Vec(), Vec e_ = Vec(), std::string s_ = ""):
		n(n_),n0(n0_),Object(s_, brdf, color, e_,refl) {}
    ld intersect(Ray r) {
        ld t=(1-r.o.dot(n))/(r.d.dot(n));
        if (t<eps) return INF; // parallel case
        return t;
    }
};

#endif
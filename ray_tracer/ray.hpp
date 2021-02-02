#ifndef __RAY_H__
#define __RAY_H__

#include "utils.hpp"

class Ray {
public:
    Vec o,d;
    Ray(Vec o_,Vec d_): o(o_), d(d_) {} 
    Vec get(ld t){ return o+d*t;}
};
#endif

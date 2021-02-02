#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "utils.hpp"

class Texture {
public:
	Vec color, emission;
	Refl_t refl;
	ld brdf;
	std::string filename;
	uchar *buf;         // store the image, size of uchar is 8bits, so every index can denote a channel. 
	int w,h,c;          // w:width, h:height, c:the number of channels
	Texture(const Texture&t): brdf(t.brdf), filename(t.filename), color(t.color),emission(t.emission), refl(t.refl) {
		if (t.filename!="") buf = stbi_load(filename.c_str(),&w,&h,&c,0);
		else buf = NULL;
	}
	Texture(std::string _, ld b, Vec col, Vec e, Refl_t r): brdf(b),filename(_),color(col),emission(e),refl(r) {
		if(_ != "") buf = stbi_load(filename.c_str(),&w,&h,&c,0);
		else buf = NULL;
	}
	std::pair<Refl_t, Vec> getcol(ld a, ld b) {
		if (buf == NULL) return std::make_pair(refl, color);
        int pw = (int(a*w)%w + w)%w, ph = (int(b*h)%h + h)%h;
		int idx=(ph*w+pw)*c;
		int x = buf[idx], y = buf[idx + 1], z = buf[idx + 2];
		// printf("find point %d %d %lf %lf\n", ph, pw,a,b);
		if (x == 233 && y == 233 && z == 233) {
			return std::make_pair(SPEC, Vec(1, 1, 1)*.999);
		}
		return std::make_pair(refl,Vec(x, y, z)/255.);
	}
};

#endif // __TEXTURE_H__
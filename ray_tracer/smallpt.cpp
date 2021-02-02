/* smallpt: 
      Make : g++ -O3 -fopenmp smallpt.cpp -o smallpt
*/
#include "utils.hpp"
#include "obj.hpp"
#include "ray.hpp"
#include "render.hpp"



int main(int argc, char *argv[]){
  int w=1024, h=768, samps = 1 ;//argc==2 ? atoi(argv[1])/4 : 1; // # samples
  Ray cam(Vec(50,52,295.6),Vec(0,-0.042612,-1).norm()); // cam pos, dir
  Vec cx=Vec(w*.5135/h);
  Vec cy=(cx%cam.d).norm()*.5135;
  Vec r; // used for colors of samples
  Vec *c=new Vec[w*h];
#pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP
  for (int y=0;y<h;y++){ // Loop over image rows
    // *** Commented out for Visual Studio, fprintf is not thread-safe
    fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
    ushort Xi[3]={0,0,y*y*y}; // *** Moved outside for VS2012
    for (ushort x=0;x<w; x++)   // Loop cols
      for (int sy=0,i=(h-y-1)*w+x;sy<2; sy++)     // 2x2 subpixel rows
        for (int sx=0;sx<2;sx++,r=Vec()){        // 2x2 subpixel cols
          for (int s=0;s<samps;s++){
            ld r1=2*erand48(Xi), dx=r1<1?sqrt(r1)-1:1-sqrt(2-r1);
            ld r2=2*erand48(Xi), dy=r2<1?sqrt(r2)-1:1-sqrt(2-r2);
            Vec d = cx*(((sx+.5+dx)/2+x)/w-.5) +
                    cy*(((sy+.5+dy)/2+y)/h-.5) + cam.d;
            r = r + radiance(Ray(cam.o+d*140,d.norm()),0,Xi)*(1./samps);
          } // Camera rays are pushed ^^^^^ forward to start in interior
          c[i] = c[i] + Vec(clamp(r.x),clamp(r.y),clamp(r.z))*.25;
        }
  }
  FILE *f = fopen("image1.ppm", "w");         // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
  for (int i=0; i<w*h; i++)
    fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
}
#ifndef _SCENE_H__
#define _SCENE_H__

#include "utils.hpp"
#include "obj.hpp"

int scene_num=13;

//Scene: radius, position, emission, color, material, texture
Object* choice_1[]={
	new Sphere_object(1e5, Vec(1e5+1,40.8,81.6),   DIFF, 1.5, Vec(.1,.25,.25), Vec(), "wallls.com_156455.png"),//Left
	new Sphere_object(1e5,Vec(-1e5+299,40.8,81.6), DIFF, 1.5, Vec(.25,.75,.25)),//Right
	new Sphere_object(1e5,Vec(50,40.8, 1e5),       DIFF, 1.5, Vec(1,1,1)*.999, Vec(), "greenbg.jpg"),//Back
	new Sphere_object(1e5,Vec(50,40.8,-1e5+190),   DIFF, 1.5, Vec(.25,.25,.25)),//Front
	new Sphere_object(1e5, Vec(50, 1e5, 81.6),     DIFF, 1.5, Vec(.75,.75,.75), Vec(), "star.png"),//Botrom
	new Sphere_object(1e5,Vec(50,-1e5+81.6,81.6),  DIFF, 1.5, Vec(.75,.75,.75)),//Top
	new Cube_object  (Vec(0,8,0),Vec(30,10,30),    DIFF, 1.5, Vec(76/255.,34/255.,27/255.)),
	new Sphere_object(16.5, Vec(73,16.5,40),       DIFF, 1.7, Vec(1,1,1)*.999, Vec(), "rainbow.png"),//Main Ball
	new Sphere_object(6,Vec(45,6,45),              REFR, 1.7, Vec(.5,.5,1)*.999),//SmallBall0
	new Sphere_object(3,Vec(52,3,75),              REFR, 1.7, Vec(1,.5,.5)*.999),//SmallBall1
	new Sphere_object(3,Vec(65.5,3,88),            REFR, 1.7, Vec(.5,1,.5)*.999),//SmallBall2
	new Sphere_object( 3,Vec(77,3,92),             REFR, 1.7, Vec(1,1,.5)*.999),//SmallBall3
	new Sphere_object(600,Vec(50,681.6-.27,81.6),  DIFF, 1.5, Vec(), Vec(1,1,1)*20) //Lite
};
   

Object ** scene=choice_1;
std::pair<Refl_t, Vec> get_feature(Object* obj, Vec x, ushort *X) {
	std::pair<Refl_t, Vec> feature ;
    /*Texture t_ = obj-> texture;
    if (t_.filename == "star.png"){
		feature = t_.getcol(x.z/15, x.x/15);
        //feature.second.print();
    }
    else 
    */
    return obj->texture.getcol(x.z,x.x);           
}
#endif
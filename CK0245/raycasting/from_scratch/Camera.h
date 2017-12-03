#ifndef _Camera_H
#define _Camera_H

#include "Vect.h"

class Camera
{
	// cam position, cam direction, cam right, cam down
	Vect campos, camdir, camright, camdown;
	
	public:
	
	Camera ();
	
	Camera (Vect, Vect, Vect, Vect);
	
	// method functions
	Vect getCameraPosition(); 
	Vect getCameraDirection();
	Vect getCameraRight();
	Vect getCameraDown();
	
};

Camera::Camera ()
{
	campos = Vect(0,0,0);
	camdir = Vect(0,0,1);
	camright = Vect(0,0,0);
	camdown = Vect(0,0,0);
}

Camera::Camera (Vect pos, Vect dir, Vect right, Vect down) 
{
	campos = pos;
	camdir = dir;
	camright = right;
	camdown = down;
}

#endif

#ifndef _SPHERE_H
#define _SPHERE_H

#include"math.h"
#include"./Vect.h"
#include"./Color.h"
#include"./Object.h"

class Sphere : public Object {
	
	Vect center;
	Color color;
	double radius;
	
	public:
	
	Sphere ();
	Sphere (Vect, double, Color);
	
	double getSphereRadius();
	double indIntersection(Ray);
	
	Color getColor();
	Vect getNormalAt(Vect);
	Vect getSphereCenter();
};

Sphere::Sphere () {
	center = Vect(0,0,0);
	radius = 1.0;
	color = Color(0.5,0.5,0.5, 0);
}

Sphere::Sphere (Vect centerValue, double radiusValue, Color colorValue) {
	center = centerValue;
	radius = radiusValue;
	color = colorValue;
}

#endif

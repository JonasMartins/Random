#ifndef _Plane_H
#define _Plane_H

#include"math.h"
#include"./Object.h"
#include"./Vect.h"
#include"./Color.h"

class Plane : public Object {
	
	Vect normal;
	Color color;

	double distance;
	
	public:
	
	Plane ();
	
	Plane (Vect, double, Color);
	
	// method functions
	Vect getPlaneNormal () { return normal; }
	Color getColor () { return color; }
	double getPlaneDistance () { return distance; }
	
	Vect getNormalAt(Vect point) { return normal; }
	
	// retorna a dinstancia da origem até o ponto de 
	// intersecção
	double findIntersection(Ray ray)
	{
		Vect ray_direction = ray.getRayDirection();	
		double a = ray_direction.dotProduct(normal);
		
		// ray is parallel to the plane
		if (a == 0) { return -1;}
		else {
			
			double b = normal.dotProduct(ray.getRayOrigin().vectAdd(normal.vectMult(distance).negative()));
			// distancia entre origem e ponto de intersecção
			return -1*b/a;
		}
	}
};

Plane::Plane () {
	// x is up, z is depth, y is left right of the plane
	normal = Vect(1,0,0);
	distance = 0;
	color = Color(0.5,0.5,0.5, 0);
}

Plane::Plane (Vect normalValue, double distanceValue, Color colorValue) {
	normal = normalValue;
	distance = distanceValue;
	color = colorValue;
}

#endif

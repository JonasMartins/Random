#ifndef _VECT_H
#define _VECT_H

#include "math.h"

class Vect 
{

	double x, y, z;

	public:
		Vect ();
		Vect (double, double, double);
		
		Vect negative();
		Vect normalize();
		Vect vectAdd(Vect);
		Vect vectMult(double);
		Vect crossProduct(Vect);

		double getVectZ();	
		double getVectY();
		double getVectX();
		double magnitude();
		double dotProduct(Vect);

		
	
	private:
};

Vect::Vect()
{
	x = 0;
	y = 0;
	z = 0;
}

Vect::Vect(double i, double j, double k) 
{
	x = i;
	y = j;
	z = k;
}

#endif
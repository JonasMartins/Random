#ifndef _VECT_H
#define _VECT_H

#include "math.h"

class Vect 
{

	double x, y, z;

	public:
		Vect ();
		Vect (double, double, double);
		
		Vect Negative();
		Vect Normalize();
		Vect VectAdd(Vect);
		Vect VectMult(double);
		Vect CrossProduct(Vect);

		double getVectZ();	
		double getVectY();
		double getVectX();
		double Magnitude();
		double DotProduct(Vect);
	
	private:
};

#endif
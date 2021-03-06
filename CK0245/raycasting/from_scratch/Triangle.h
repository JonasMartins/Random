#ifndef _Triangle_H
#define _Triangle_H

#include"math.h"
#include"./Object.h"
#include"./Vect.h"
#include"./Color.h"

class Triangle : public Object {
	Vect A,B,C;	
	Vect normal;
	Color color;

	double distance;
	
	public:
	
	Triangle ();
	
	Triangle (Vect,Vect,Vect,Color);
	
	// method functions
	Vect getTriangleNormal () { 

		// vetores formados pelos pontos do triangulo para calcular a normal a sua face 
		Vect CA(C.getVectX() - A.getVectX(),C.getVectY() - A.getVectY(),C.getVectZ() - A.getVectZ());
		Vect BA(B.getVectX() - A.getVectX(),B.getVectY() - A.getVectY(),B.getVectZ() - A.getVectZ());
		normal = CA.crossProduct(BA).normalize();
		return normal; 
	}
	virtual Color getColor() { return color; }

	// distancia, é representada pelo produto da normal com algum dos pontos daquele plano.
	double getTriangleDistance () { 
		normal = getTriangleNormal();
		distance = normal.dotProduct(A);
		return distance; 
	}
	
	Vect getNormalAt(Vect point) { 
		normal = getTriangleNormal();
		return normal; 
	}
	
	// retorna a dinstancia da origem até o ponto de 
	// intersecção
	virtual double findIntersection(Ray ray)
	{
		Vect ray_direction = ray.getRayDirection();
		Vect ray_origin = ray.getRayOrigin();

		normal = getTriangleNormal();
		distance = getTriangleDistance();

		double a = ray_direction.dotProduct(normal);
		
		// ray is parallel to the Triangle
		if (a == 0) { return -1;}
		else {
			
			double b = normal.dotProduct(ray.getRayOrigin().vectAdd(normal.vectMult(distance).negative()));
			double distanceToPlane = -1*b/a;

			// encontrando o ponto de intersecção
			double Qx = ray_direction.vectMult(distanceToPlane).getVectX() + ray_origin.getVectX();
			double Qy = ray_direction.vectMult(distanceToPlane).getVectY() + ray_origin.getVectY();
			double Qz = ray_direction.vectMult(distanceToPlane).getVectZ() + ray_origin.getVectZ();

			Vect Q(Qx,Qy,Qz);

			/**
			 * Q = ponto de intersecção
			 *
			 * [CAxQA]*n >= 0 test1
			 * [BCxQC]*n >= 0 test2
			 * [ABxQB]*n >= 0 test3
			 *
			 */
			Vect CA(C.getVectX() - A.getVectX(),C.getVectY() - A.getVectY(),C.getVectZ() - A.getVectZ());
			Vect QA(Q.getVectX() - A.getVectX(),Q.getVectY() - A.getVectY(),Q.getVectZ() - A.getVectZ());
			double test1 = (CA.crossProduct(QA)).dotProduct(normal);


			Vect BC(B.getVectX() - C.getVectX(),B.getVectY() - C.getVectY(),B.getVectZ() - C.getVectZ());
			Vect QC(Q.getVectX() - C.getVectX(),Q.getVectY() - C.getVectY(),Q.getVectZ() - C.getVectZ());
			double test2 = (BC.crossProduct(QC)).dotProduct(normal);

			Vect AB(A.getVectX() - B.getVectX(),A.getVectY() - B.getVectY(),A.getVectZ() - B.getVectZ());
			Vect QB(Q.getVectX() - B.getVectX(),Q.getVectY() - B.getVectY(),Q.getVectZ() - B.getVectZ());
			double test3 = (AB.crossProduct(QB)).dotProduct(normal);


			// se essas 3 condições forem verdadeiras, o ponto Q está dentro do triangulo, então retornamos a sua distancia 
			if((test1>=0) && (test2>=0) && (test3>=0)){
				return distanceToPlane;
			} else {
				return -1; // miss the triangle
			}

		}
	}
};

Triangle::Triangle () {

	A = Vect(1,0,0);
	B = Vect(0,1,0);
	C = Vect(0,0,1);
	color = Color(0.5,0.5,0.5, 0);
}

Triangle::Triangle (Vect pointA,  Vect pointB, Vect pointC, Color colorValue) {
	A = pointA;
	B = pointB;
	C = pointC;

	color = colorValue;
}

#endif

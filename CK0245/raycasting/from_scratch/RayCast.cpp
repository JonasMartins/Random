#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<limits>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>


#include"./RayCast.h"
#include"./Vect.h"
#include"./Ray.h"
#include"./Camera.h"
#include"./Color.h"
#include"./Light.h"
#include"./Sphere.h"
#include"./Object.h"
#include"./Plane.h"



using namespace std;

void RayCast::Run()
{
	cout<<"rendering..."<<endl;
	
	unsigned short i;
	unsigned short j;
	unsigned short width = 640;
	unsigned short height = 480;
	unsigned short dpi = 72;
	unsigned short thisOne;

	RGBType *pixels;
	pixels = new RGBType[width * height]; 
	//pixels = (RGBType*)malloc(sizeof((width * heigth)* RGBType)); //?	

	Vect O (0,0,0);
	Vect X (1,0,0);
	Vect Y (0,1,0);
	Vect Z (0,0,1);

	// vetor posição da camera
	Vect campos (3, 1.5, -4);

	Vect look_at (0, 0, 0);
	// vector diff between
	// registra a diferença entre a posição da camera e a posição do look_at
	Vect diff_btw (campos.getVectX() - look_at.getVectX(), campos.getVectY() - look_at.getVectY(), campos.getVectZ() - look_at.getVectZ());

	// vetor normalizado da posição oposta do vetor direção da posição da camera e do look_at
	
	// kc 
	Vect camdir = diff_btw.negative().normalize();
	
	// Ic 
	Vect camright = Y.crossProduct(camdir).normalize();

	//Jc
	Vect camdown = camright.crossProduct(camdir);

	// Instancia do objeto camera
	Camera scene_cam (campos, camdir, camright, camdown);

	Color white_light (1.0, 1.0, 1.0, 0);
	Color pretty_green (0.5, 1.0, 0.5, 0.3);
	Color maroon (0.5, 0.25, 0.25, 0);
	Color tile_floor (1, 1, 1, 2);
	Color gray (0.5, 0.5, 0.5, 0);
	Color black (0.0, 0.0, 0.0, 0);

	Vect light_position (-7,10,-10);
	Light scene_light (light_position, white_light);

	// scene objects
	Sphere scene_sphere (O, 1, pretty_green);
	
	// Y representa a normal ao plano
	// -1 distancia para o centro
	Plane scene_plane (Y, -1, maroon);	


	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			thisOne = (j*width) + i;
			pixels[thisOne].r = .01;
			pixels[thisOne].g = .9;
			pixels[thisOne].b = .02;			
		}
	}
	Savebmp("scene.bmp",width,height,dpi,pixels);	
}

void RayCast::Savebmp (const char *filename, unsigned short w, unsigned short h, unsigned short dpi, RGBType *data) 
{
	FILE *f;
	int k = w*h;
	int s = 4*k;
	int filesize = 54 + s;
	
	double factor = 39.375;
	int m = static_cast<int>(factor);
	
	int ppm = dpi*m;
	
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
	
	/**
	 *
	 * 
	 *	 	BITWISE OPERATION EXAMPLE;
	 *
	 *	 	3 = 0011
	 *		3 << 1 = 0110 = 6
	 *		3 << 2 = 1100 = 12
	 *		3 << 3 = 1000 = 8
	 *	 
	 *		12 = 1100
	 *		12 >> 1 = 0110 = 6
	 *		12 >> 2 = 0011 = 3
	 *		12 >> 3 = 0001 = 1
	 *
	 */
	

	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>>8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);
	
	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w>>8);
	bmpinfoheader[ 6] = (unsigned char)(w>>16);
	bmpinfoheader[ 7] = (unsigned char)(w>>24);
	
	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);
	
	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);
	
	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);
	
	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);
	
	f = fopen(filename,"wb");
	
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	
	for (int i = 0; i < k; i++) {
		RGBType rgb = data[i];
		
		double red = (data[i].r)*255;
		double green = (data[i].g)*255;
		double blue = (data[i].b)*255;
		
		unsigned char floor_blue = (int)floor(blue);
		unsigned char floor_green = (int)floor(green);
		unsigned char floor_red = (int)floor(red);
		
		// b,g,r
		unsigned char color[3] = {floor_blue,floor_green,floor_red};
		
		fwrite(color,1,3,f);
	}
	
	fclose(f);
}

/* VECTOR CLASS METHODS =========================================================== */

double Vect::getVectX() { return x; }
double Vect::getVectY() { return y; }
double Vect::getVectZ() { return z; }

double Vect::magnitude()
{
	return sqrt((x*x) + (y*y) + (z*z));
}

Vect Vect::normalize ()
{
	double magnitude = sqrt((x*x) + (y*y) + (z*z));
	return Vect (x/magnitude, y/magnitude, z/magnitude);
}

Vect Vect::negative()
{
	return Vect (-x, -y, -z);
}

double Vect::dotProduct(Vect v)
{
	return x*v.getVectX() + y*v.getVectY() + z*v.getVectZ();
}

Vect Vect::crossProduct(Vect v)
{
	return Vect (y*v.getVectZ() - z*v.getVectY(), z*v.getVectX() - x*v.getVectZ(), x*v.getVectY() - y*v.getVectX());
}

Vect Vect::vectAdd (Vect v)
{
	return Vect (x + v.getVectX(), y + v.getVectY(), z + v.getVectZ());
}

Vect Vect::vectMult (double scalar)
{
	return Vect (x*scalar, y*scalar, z*scalar);
}
/* ========================================================================== */


/* CAMERA CLASS METHODS =========================================================== */

Vect Camera::getCameraPosition () { return campos; }
Vect Camera::getCameraDirection () { return camdir; }
Vect Camera::getCameraRight () { return camright; }
Vect Camera::getCameraDown () { return camdown; }

/* ========================================================================== */



/* COLOR CLASS METHODS =========================================================== */

double Color::getColorRed() { return red; }
double Color::getColorGreen() { return green; }
double Color::getColorBlue() { return blue; }
double Color::getColorSpecial() { return special; }

double Color::setColorRed(double redValue) { red = redValue; }
double Color::setColorGreen(double greenValue) { green = greenValue; }
double Color::setColorBlue(double blueValue) { blue = blueValue; }
double Color::setColorSpecial(double specialValue) { special = specialValue; }

double Color::brightness() 
{
	return(red + green + blue)/3;
}

Color Color::colorScalar(double scalar) 
{
	return Color (red*scalar, green*scalar, blue*scalar, special);
}

Color Color::colorAdd(Color color) 
{
	return Color (red + color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special);
}

Color  Color::colorMultiply(Color color) 
{
	return Color (red*color.getColorRed(), green*color.getColorGreen(), blue*color.getColorBlue(), special);
}

Color Color::colorAverage(Color color) 
{
	return Color ((red + color.getColorRed())/2, (green + color.getColorGreen())/2, (blue + color.getColorBlue())/2, special);
}

Color Color::clip() 
{
	double alllight = red + green + blue;
	double excesslight = alllight - 3;
	if (excesslight > 0) {
		red = red + excesslight*(red/alllight);
		green = green + excesslight*(green/alllight);
		blue = blue + excesslight*(blue/alllight);
	}
	if (red > 1) {red = 1;}
	if (green > 1) {green = 1;}
	if (blue > 1) {blue = 1;}
	if (red < 0) {red = 0;}
	if (green < 0) {green = 0;}
	if (blue < 0) {blue = 0;}
	
	return Color (red, green, blue, special);
}
/* ========================================================================== */



/* LIGHT CLASS METHODS =========================================================== */

Vect Light::getLightPosition () { return position; }
Color Light::getLightColor () { return color; }

/* ========================================================================== */




/* SPHERE CLASS METHODS =========================================================== */



Color Sphere::getColor () { return color; }
Vect Sphere::getSphereCenter () { return center; }
double Sphere::getSphereRadius () { return radius; }

Vect Sphere::getNormalAt(Vect point)
{
	// normal always points away from the center of a sphere
	Vect normal_Vect = point.vectAdd(center.negative()).normalize();
	return normal_Vect;
}

double Sphere::indIntersection(Ray ray)
{
	Vect ray_origin = ray.getRayOrigin();
	double ray_origin_x = ray_origin.getVectX();
	double ray_origin_y = ray_origin.getVectY();
	double ray_origin_z = ray_origin.getVectZ();
	
	Vect ray_direction = ray.getRayDirection();
	double ray_direction_x = ray_direction.getVectX();
	double ray_direction_y = ray_direction.getVectY();
	double ray_direction_z = ray_direction.getVectZ();
	
	Vect sphere_center = center;
	double sphere_center_x = sphere_center.getVectX();
	double sphere_center_y = sphere_center.getVectY();
	double sphere_center_z = sphere_center.getVectZ();
	
	double a = 1; // normalized
	double b = (2*(ray_origin_x - sphere_center_x)*ray_direction_x) + (2*(ray_origin_y - sphere_center_y)*ray_direction_y) + (2*(ray_origin_z - sphere_center_z)*ray_direction_z);
	double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - (radius*radius);
	
	double discriminant = b*b - 4*c;
	
	if (discriminant > 0) {
		/// the ray intersects the sphere
		
		// the first root
		double root_1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;
		
		if (root_1 > 0) {
			// the first root is the smallest positive root
			return root_1;
		}
		else {
			// the second root is the smallest positive root
			double root_2 = ((sqrt(discriminant) - b)/2) - 0.000001;
			return root_2;
		}
	}
	else {
		// the ray missed the sphere
		return -1;
	}
}




/* ========================================================================== */
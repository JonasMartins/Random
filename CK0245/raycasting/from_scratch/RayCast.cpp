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
#include"./Source.h"
#include"./Object.h"
#include"./Plane.h"

using namespace std;
/**
 *
 * função mais complexa do trabalho.
 * pega a cor do objeto interseptado, a normal no local de intersecção, loop pelas fontes de luz, 
 * determina em qual direção ir do nosso ponto de intersecção até a fonte de luz, então cria raios para
 * a direção das fontes de luz, se tiver alguma intersecção, a primeira intersecção vai estar com sombra
 *
 */
Color getColorAt(Vect intersection_position, Vect intersecting_ray_direction, vector<Object*> scene_objects, int index_of_winning_object, vector<Source*> light_sources, double accuracy, double ambientlight) {
	
	// int reflection_index;
	// int object_index;
	// int light_index;
	// int square;

	// normal e cor do objeto interseptado.
	Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();
	Vect winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);
	
	Color final_color = winning_object_color.colorScalar(ambientlight);
	
	// if (winning_object_color.getColorSpecial() == 2) {
	// 	// checkered/tile floor pattern
		
	// 	int square = (int)floor(intersection_position.getVectX()) + (int)floor(intersection_position.getVectZ());
		
	// 	if ((square % 2) == 0) {
	// 		// black tile
	// 		winning_object_color.setColorRed(0);
	// 		winning_object_color.setColorGreen(0);
	// 		winning_object_color.setColorBlue(0);
	// 	}
	// 	else {
	// 		// white tile
	// 		winning_object_color.setColorRed(1);
	// 		winning_object_color.setColorGreen(1);
	// 		winning_object_color.setColorRed(1);
	// 	}
	// }
	
	// Color final_color = winning_object_color.colorScalar(ambientlight);
	
	// if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
	// 	// reflection from objects with specular intensity
	// 	double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negative());
	// 	Vect scalar1 = winning_object_normal.vectMult(dot1);
	// 	Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
	// 	Vect scalar2 = add1.vectMult(2);
	// 	Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
	// 	Vect reflection_direction = add2.normalize();
		
	// 	Ray reflection_ray (intersection_position, reflection_direction);
		
	// 	// determine what the ray intersects with first
	// 	vector<double> reflection_intersections;
		
	// 	for (int reflection_index = 0; reflection_index < scene_objects.size(); reflection_index++) {
	// 		reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
	// 	}
		
	// 	int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);
		
	// 	if (index_of_winning_object_with_reflection != -1) {
	// 		// reflection ray missed everthing else
	// 		if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
	// 			// determine the position and direction at the point of intersection with the reflection ray
	// 			// the ray only affects the color if it reflected off something
				
	// 			Vect reflection_intersection_position = intersection_position.vectAdd(reflection_direction.vectMult(reflection_intersections.at(index_of_winning_object_with_reflection)));
	// 			Vect reflection_intersection_ray_direction = reflection_direction;
				
	// 			Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientlight);
				
	// 			final_color = final_color.colorAdd(reflection_intersection_color.colorScalar(winning_object_color.getColorSpecial()));
	// 		}
	// 	}
	// }
	
	//loop pelas fonte de luz
	for (int light_index = 0; light_index < light_sources.size(); light_index++) {
		
		Vect light_direction = light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize();
		
		// coseno do angulo entre dois vetores
		float cosine_angle = winning_object_normal.dotProduct(light_direction);
		
		// test for shadows
		if (cosine_angle > 0) {
		
			bool shadowed = false;

			// distancia da fonte de luz para o nosso ponto de intersecção
			Vect distance_to_light = light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize();
			
			float distance_to_light_magnitude = distance_to_light.magnitude();

			// Raio que vai do nosso ponto de interseção para a fonte de luz
			// testar se o raio intersepta alguma coisa no caminho do ponto de intersecção e a fonte de luz. 
			// se Sim, siginifca que o ponto de intersecção está sob sombras
			Ray shadow_ray (intersection_position, light_sources.at(light_index)->getLightPosition().vectAdd(intersection_position.negative()).normalize());
			
			vector<double> secondary_intersections;
			
			for (int object_index = 0; object_index < scene_objects.size() && shadowed == false; object_index++) {
				secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_ray));
			}
			// loop pelas intersecções secundárias, se houver um ponto de intersecção lá, que seja menor que a distancia
			// da fonte de luz, isso significa que o pixel não está sob sombra.
			for (int c = 0; c < secondary_intersections.size(); c++) {
				if (secondary_intersections.at(c) > accuracy) {
					if (secondary_intersections.at(c) <= distance_to_light_magnitude) {
						shadowed = true;
					}
				break; // se esse break estiver depois dos ifs, apenas serão postas sombras sob o primeiro objeto e não nos outros
				}
			}
			
			if (shadowed == false) {
				final_color = final_color.colorAdd(winning_object_color.colorMultiply(light_sources.at(light_index)->getLightColor()).colorScalar(cosine_angle));
				
				// determinando o valor especial da propriedade do objeto.
				if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
					// special [0-1]
					double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negative());
					Vect scalar1 = winning_object_normal.vectMult(dot1);
					Vect add1 = scalar1.vectAdd(intersecting_ray_direction);
					Vect scalar2 = add1.vectMult(2);
					Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);
					Vect reflection_direction = add2.normalize();
					
					double specular = reflection_direction.dotProduct(light_direction);
					if (specular > 0) {
						specular = pow(specular, 10);
						final_color = final_color.colorAdd(light_sources.at(light_index)->getLightColor().colorScalar(specular*winning_object_color.getColorSpecial()));
					}
				}
			}
		}
	}
	
	return final_color;
}

// gambiarra 
int winningObjectIndex(vector<double> object_intersections) {
	// return the index of the winning intersection
	int index_of_minimum_value;
	// prevent unnessary calculations
	// if there are no intersections
	if (object_intersections.size() == 0) {	return -1; }
		// aqui pegamos a primeira intersecção
	else if (object_intersections.size() == 1) {
			// if that intersection is greater than zero then its our index of minimum value
		if (object_intersections.at(0) > 0) { return 0;}
		// otherwise the only intersection value is negative
		else { return -1; }
	}
	// se existem mais de um ponto de intersecção	
	else {
		// otherwise there is more than one intersection
		// first find the maximum value
		double max = 0;
		for (int i = 0; i < object_intersections.size(); i++) {
			if (max < object_intersections.at(i)) {
				max = object_intersections.at(i);
			}
		}
		// then starting from the maximum value find the minimum positive value
		if (max > 0) {
			// we only want positive intersections
			for (int index = 0; index < object_intersections.size(); index++) {
				if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
					max = object_intersections.at(index);
					index_of_minimum_value = index;
				}
			}
			return index_of_minimum_value;
		}
		// all the intersections were negative
		else {	return -1; }
	}
}// end of winningObjectIndex

void RayCast::Run()
{
	cout<<"rendering..."<<endl;
	
	// VGA: 640 x 480 pixels;
	// WVGA: 800 x 480 pixels;
	// FWVGA: 854 x 480 pixels;
	// QVGA: 320 x 240 pixels;
	// QQVGA: 160 x 120 pixels;
	// HQVGA: 240 x 160 pixels;
	// WQVGA: 400 x 240 pixels;
	// HVGA: 480 x 320 pixels;
	// WVGA: 800 x 480 pixels;
	// SVGA: 800 x 600 pixels;
	// DVGA: 960 x 640 pixels;
	// WSVGA: 1024 x 600 pixels.

	// 1152 x 768 pixels;
	// 1280 x 720 pixels;
	// 1280 x 768 pixels;
	// 1280 x 800 pixels;
	// 1360 x 768 pixels;
	// 1366 x 768 pixels.

	unsigned short i;
	unsigned short j;
	unsigned short width = 800;
	unsigned short height = 600;
	unsigned short dpi = 72; // padrão suficiente

	double aspectratio = (double)width/(double)height;
	double ambientlight = 0.2;
	double accuracy = 0.00000001;


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
	vector<Source*> light_sources;
	
	// multiple light sources
	light_sources.push_back(dynamic_cast<Source*>(&scene_light));
	

	// scene objects
	Sphere scene_sphere (O, 1, pretty_green);
	
	// Y representa a normal ao plano
	// -1 distancia para o centro
	Plane scene_plane (Y, -1, maroon);	

	// colocando os objetos dentro de um array
	vector<Object*> scene_objects;
	scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
	scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

	double xamnt,yamnt; // um pouco mais a direita, e um pouco mais a esquerda da direção da camera.
	Vect cam_ray_origin;
	Vect cam_ray_direction;
	Vect intersection_position;
	Vect intersecting_ray_direction;
	
	Color intersection_color;

	for(i=0;i<width;i++){

		for(j=0;j<height;j++){
			
			int thisOne = j*width + i;

			/**
			 *
			 * xamnt e yamnt para cirar raios para ir para
			 * a diretira e para a esquerda com relação a
			 * direção que aponta a camera
			 *
			 */

			// no anti-aliasing 
			if (width > height) {
				// the image is wider than it is tall
				xamnt = ((i+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
				yamnt = ((height - j) + 0.5)/height;
			}
			else if (height > width) {
				// the imager is taller than it is wide
				xamnt = (i + 0.5)/ width;
				yamnt = (((height - j) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
			}else {
				// the image is square
				xamnt = (i + 0.5)/width;
				yamnt = ((height - j) + 0.5)/height;
			}
			// get camera origin 
			cam_ray_origin = scene_cam.getCameraPosition();
			// direção que a camera aponta 
			cam_ray_direction = camdir.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();
			
			Ray cam_ray (cam_ray_origin, cam_ray_direction);

			
			
			/**
			 *
			 * Loop por todos os obejtos da cena, e usa o metodo para achar a intersecção
			 * lembrando que o metodo intersecção é implementado por cada objeto separadamente
			 * ou seja, vai ter um mmétodo para cada tipo de objeto sendo que todos herdam da classe
			 * Object.h, isso vai retornar um valor, e esse valor é armazenado dentro do vetor de 
			 * doubles intersections.
			 *
			 */
			vector<double> intersections;

			for(int index = 0; index < scene_objects.size(); index++) {
				intersections.push_back(scene_objects.at(index)->findIntersection(cam_ray));
			}
			// -1,0 ou 1 
			int index_of_winning_object = winningObjectIndex(intersections);


			if (index_of_winning_object == -1) {
				
				pixels[thisOne].r = 0;
				pixels[thisOne].g = 0;
				pixels[thisOne].b = 0;
			} else {
				// index coresponds to an object in our scene
				if (intersections.at(index_of_winning_object) > accuracy){
					// determine the position and direction vectors at the point of intersection
					intersection_position = cam_ray_origin.vectAdd(cam_ray_direction.vectMult(intersections.at(index_of_winning_object)));
					intersecting_ray_direction = cam_ray_direction;


					intersection_color = getColorAt(intersection_position,intersecting_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy, ambientlight); 

					pixels[thisOne].r = intersection_color.getColorRed();
					pixels[thisOne].g = intersection_color.getColorGreen();
					pixels[thisOne].b = intersection_color.getColorBlue();					
				}
			}			
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

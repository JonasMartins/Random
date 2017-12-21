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
#include"./Triangle.h"

using namespace std;


vector<Object*> scene_objects;


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

/**
 *
 * função mais complexa do trabalho. -> RAYCASTING
 * pega a cor do objeto interseptado, a normal no local de intersecção, loop pelas fontes de luz, 
 * determina em qual direção ir do nosso ponto de intersecção até a fonte de luz, então cria raios para
 * a direção das fontes de luz, se tiver alguma intersecção, a primeira intersecção vai estar com sombra
 *
 */
Color getColorAtRaycasting(Vect intersection_position, Vect intersecting_ray_direction, vector<Object*> scene_objects, int index_of_winning_object, vector<Source*> light_sources, double accuracy, double ambientlight) {
	
		// normal e cor do objeto interseptado.
	Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();
	Vect winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);
	
	Color final_color = winning_object_color.colorScalar(ambientlight);
	
	if (winning_object_color.getColorSpecial() == 2) {
		// checkered/tile floor pattern
		
		int square = (int)floor(intersection_position.getVectX()) + (int)floor(intersection_position.getVectZ());
		
		if ((square % 2) == 0) {
			// black tile
			winning_object_color.setColorRed(0);
			winning_object_color.setColorGreen(0);
			winning_object_color.setColorBlue(0);
		}
		else {
			// white tile
			winning_object_color.setColorRed(1);
			winning_object_color.setColorGreen(1);
			winning_object_color.setColorRed(1);
		}
	}
	
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
	
	return final_color.clip();
}

/**
 *
 * função mais complexa do trabalho. -> RAYCASTING
 * pega a cor do objeto interseptado, a normal no local de intersecção, loop pelas fontes de luz, 
 * determina em qual direção ir do nosso ponto de intersecção até a fonte de luz, então cria raios para
 * a direção das fontes de luz, se tiver alguma intersecção, a primeira intersecção vai estar com sombra
 *
 */
Color getColorAtRaytracer(Vect intersection_position, Vect intersecting_ray_direction, vector<Object*> scene_objects, int index_of_winning_object, vector<Source*> light_sources, double accuracy, double ambientlight) {
	
	// normal e cor do objeto interseptado.
	Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();
	Vect winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);
	
	Color final_color = winning_object_color.colorScalar(ambientlight);
	
	if (winning_object_color.getColorSpecial() == 2) {
		// checkered/tile floor pattern
		
		int square = (int)floor(intersection_position.getVectX()) + (int)floor(intersection_position.getVectZ());
		
		if ((square % 2) == 0) {
			// black tile
			winning_object_color.setColorRed(0);
			winning_object_color.setColorGreen(0);
			winning_object_color.setColorBlue(0);
		}
		else {
			// white tile
			winning_object_color.setColorRed(1);
			winning_object_color.setColorGreen(1);
			winning_object_color.setColorBlue(1);
		}
	}
	
	/**
	 *
	 * Como ver com o que o raio intersepta primeiramente?, na forma de determinar em qual direção o raio vai
	 * para haver uma reflexão, a reflexão funciona da seguinte forma: o raio sai da camera, intersepta um objeto na nossa
	 * cena, reflete desse objeto e intersepta com outro objeto na cena, se esse raio intersepta outro objeto, teremos uma
	 * do segundo objeto que acabou de ser interseptado, e essa cor vai ser adicionado a cor do nosso primeiro objeto.
	 *
	 */
	
	// indicando capacidade de reflexão.
	if (winning_object_color.getColorSpecial() > 0 && winning_object_color.getColorSpecial() <= 1) {
		
		// reflection from objects with specular intensity
		double dot1 = winning_object_normal.dotProduct(intersecting_ray_direction.negative());

		Vect scalar1 = winning_object_normal.vectMult(dot1);

		Vect add1 = scalar1.vectAdd(intersecting_ray_direction);

		Vect scalar2 = add1.vectMult(2);

		Vect add2 = intersecting_ray_direction.negative().vectAdd(scalar2);

		Vect reflection_direction = add2.normalize();
		
		Ray reflection_ray (intersection_position, reflection_direction);
		
		// determine what the ray intersects with first
		vector<double> reflection_intersections;
		
		for (int reflection_index = 0; reflection_index < scene_objects.size(); reflection_index++) {
			reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
		}
		
		int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);
		
		if (index_of_winning_object_with_reflection != -1) {
			// reflection ray missed everthing else
			if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
				// determine the position and direction at the point of intersection with the reflection ray
				// the ray only affects the color if it reflected off something
				
				Vect reflection_intersection_position = intersection_position.vectAdd(reflection_direction.vectMult(reflection_intersections.at(index_of_winning_object_with_reflection)));
				Vect reflection_intersection_ray_direction = reflection_direction;
				
				Color reflection_intersection_color = getColorAtRaytracer(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_winning_object_with_reflection, light_sources, accuracy, ambientlight);
				
				final_color = final_color.colorAdd(reflection_intersection_color.colorScalar(winning_object_color.getColorSpecial()));
			}
		}
	}
	
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
	
	return final_color.clip();
}


void RayCast::Run()
{
	cout<<"rendering..."<<endl;
	
	// capturar tempo de execução inicial
	clock_t t1, t2;
	t1 = clock();

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
	//Vect campos (20, 5, 0);
	Vect campos (10, 10, 10);

	//Vect look_at (20, 0, 20); // padrão
	Vect look_at (0, 0, 0); // superior
	
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

	/* Cores usadas  http://avatar.se/molscript/doc/colour_names.html */
	Color white_light (1.0, 1.0, 1.0, 0);
	Color pretty_green (0.5, 1.0, 0.5, 0.3);
	Color maroon (0.5, 0.25, 0.25, 1); // 2 siginifaca criar o padrão quadriculado no piso
	Color tile_floor (1, 1, 1, 2);
	Color gray (0.5, 0.5, 0.5, 0);
	Color black (0.0, 0.0, 0.0, 0);
	Color paleturquoise( 0.686275, 0.933333, 0.933333,0);
	Color hotpink(1, 0.411765, 0.705882,0.3);
	Color ghostwhite(0.972549, 0.972549, 1,0.3);
	Color darkorange(1, 0.54902, 0,0);

	Color wine(0.447, 0.184, 0.215,0.0);
	Color metallic_gold(0.83,0.686,0.215,0.3);
	Color blueviolet(0.5411, 0.1686, 0.8862,0.3);
	Color gold(1, 0.8431, 0,0.3);

	Color mediumblue(0, 0, 0.80392,0.3);
	// lights
	vector<Source*> light_sources;

	Vect light_position1 (4,7,-7);
	//Vect light_position2 (25,3,18); 

	Light scene_light1 (light_position1, white_light);
	//Light scene_light2 (light_position2, white_light);
	
	//light_sources.push_back(dynamic_cast<Source*>(&scene_light2));
	light_sources.push_back(dynamic_cast<Source*>(&scene_light1));

	// parede de fundo
	Triangle bacgroundWall1 = Triangle(Vect(0,0,20),Vect(35,0,20),Vect(0,15,20),wine);
	Triangle bacgroundWall2 = Triangle(Vect(0,15,20),Vect(35,0,20),Vect(35,15,20),wine);
 
	 // parede lado direito imagem
	Triangle rightWall1 = Triangle(Vect(26.5,0,20),Vect(26.5,0,0),Vect(26.5,25,20),wine);

	// // temple floor
	// Triangle templeFloor1 = Triangle(Vect(16,0,10),Vect(21,0,10),Vect(21,0,18.66),ghostwhite);
	// Triangle templeFloor2 = Triangle(Vect(16,0,18.66),Vect(16,0,10),Vect(21,0,18.66),ghostwhite);

	// // temple roof
	// Triangle templeRoof1 = Triangle(Vect(16,4,10),Vect(21,4,10),Vect(21,4,18.66),ghostwhite);
	// Triangle templeRoof2 = Triangle(Vect(16,4,18.66),Vect(16,4,10),Vect(21,4,18.66),ghostwhite);

	// // columns direita dianteira
	// Triangle column1p1 = Triangle(Vect(21,0,10),Vect(21,4,10),Vect(21,4,10.5),ghostwhite);
	// Triangle column1p2 = Triangle(Vect(21,4,10.5),Vect(21,0,10),Vect(21,0,10.5),ghostwhite);
	// Triangle column1p3 = Triangle(Vect(21,0,10),Vect(21,4,10),Vect(20.5,4,10),ghostwhite);
	// Triangle column1p4 = Triangle(Vect(20.5,4,10),Vect(21,0,10),Vect(20.5,0,10),ghostwhite);

	// // columns direita traseira
	// Triangle column3p1 = Triangle(Vect(21,0,18.66),Vect(21,4,18.66),Vect(21,4,17.66),ghostwhite);
	// Triangle column3p2 = Triangle(Vect(21,4,17.66),Vect(21,0,18.66),Vect(21,0,17.66),ghostwhite);


	// // columns esquerda dianteira
	// Triangle column2p1 = Triangle(Vect(16,0,10),Vect(16,4,10),Vect(16,4,10.5),ghostwhite);
	// Triangle column2p2 = Triangle(Vect(16,4,10.5),Vect(16,0,10),Vect(16,0,10.5),ghostwhite);
	// Triangle column2p3 = Triangle(Vect(16,0,10),Vect(16,4,10),Vect(16.5,4,10),ghostwhite);
	// Triangle column2p4 = Triangle(Vect(16.5,4,10),Vect(16,0,10),Vect(16.5,0,10),ghostwhite);

	// // columns esquerda traseira
	// Triangle column4p1 = Triangle(Vect(16,0,18.66),Vect(16,4,18.66),Vect(16,4,17.66),ghostwhite);
	// Triangle column4p2 = Triangle(Vect(16,4,17.66),Vect(16,0,18.66),Vect(16,0,17.66),ghostwhite);

	// // temple triengle dome
	// Triangle dome = Triangle(Vect(21,4,10),Vect(16,4,10),Vect(18.5,5.5,10),ghostwhite);

	// // esfera central no domo
	// Sphere contral_overal_sphere = Sphere(Vect(18.5,4.75,10),0.4,metallic_gold);

	Vect picoGreatPyramid = Vect(18.5,7,10.5);

	// pyramid floor
	Triangle pyramidFloor1 = Triangle(Vect(15,0,7),Vect(22,0,7),Vect(22,0,14),ghostwhite);
	Triangle pyramidFloor2 = Triangle(Vect(15,0,14),Vect(15,0,7),Vect(22,0,14),ghostwhite);	

	// picoGreatPyramid da piramide: (18.5,7,10.5);
	Triangle greatPyramidFace1 = Triangle(Vect(15,0,14),Vect(15,0,7),picoGreatPyramid,metallic_gold);
	Triangle greatPyramidFace2 = Triangle(Vect(15,0,7),Vect(22,0,7),picoGreatPyramid,metallic_gold);
	Triangle greatPyramidFace3 = Triangle(picoGreatPyramid,Vect(22,0,7),Vect(22,0,14),metallic_gold);
	Triangle greatPyramidFace4 = Triangle(Vect(15,0,14),picoGreatPyramid,Vect(22,0,14),metallic_gold);		

	Vect picoSmallPyramid = Vect(22,4,9); // nice 24,4,9

	Triangle samallPyramidFace1 = Triangle(Vect(20,0,11),Vect(20,0,7),picoSmallPyramid,metallic_gold);
	Triangle samallPyramidFace2 = Triangle(Vect(20,0,7),Vect(24,0,7),picoSmallPyramid,hotpink);
	Triangle samallPyramidFace3 = Triangle(picoSmallPyramid,Vect(24,0,7),Vect(24,0,11),metallic_gold);
	Triangle samallPyramidFace4 = Triangle(Vect(24,0,11),picoSmallPyramid,Vect(24,0,11),metallic_gold);

	Vect v1 = Vect(0,0,0);
	Vect v2 = Vect(2,0,0);
	Vect v3 = Vect(2,0,2);
	Vect v4 = Vect(0,0,2);
	Vect v5 = Vect(0,2,0);
	Vect v6 = Vect(2,2,0);
	Vect v7 = Vect(2,2,2);
	Vect v8 = Vect(0,2,2);


	Triangle cuboFace1 = Triangle(v2,v3,v6,metallic_gold);
	Triangle cuboFace2 = Triangle(v6,v3,v7,metallic_gold);
	Triangle cuboFace3 = Triangle(v5,v6,v8,metallic_gold);
	Triangle cuboFace4 = Triangle(v6,v7,v8,metallic_gold);


	Triangle cuboFace5 = Triangle(v3,v4,v7,metallic_gold);
	Triangle cuboFace6 = Triangle(v4,v8,v7,metallic_gold);
	Triangle cuboFace7 = Triangle(v5,v8,v1,metallic_gold);
	Triangle cuboFace8 = Triangle(v8,v4,v1,metallic_gold);


	Triangle cuboFace9 = Triangle(v1,v4,v3,metallic_gold);
	Triangle cuboFace10 = Triangle(v1,v3,v2,metallic_gold);
	Triangle cuboFace11 = Triangle(v1,v6,v5,metallic_gold);
	Triangle cuboFace12 = Triangle(v1,v2,v6,metallic_gold);


	Vect picoSmallPyramid2 = Vect(15,5,20);

	Triangle samallPyramid2Face1 = Triangle(Vect(10,0,20),Vect(15,0,15),picoSmallPyramid2,paleturquoise);
	Triangle samallPyramid2Face2 = Triangle(Vect(15,0,15),Vect(20,0,20),picoSmallPyramid2,maroon);
	Triangle samallPyramid2Face3 = Triangle(picoSmallPyramid2,Vect(20,0,20),Vect(15,0,25),metallic_gold);
	Triangle samallPyramid2Face4 = Triangle(Vect(10,0,20),picoSmallPyramid2,Vect(15,0,25),metallic_gold);

	Sphere sun = Sphere(Vect(24,8,20),1,ghostwhite);


	Vect prismPicUp = Vect(14.5,8,12.5);
	Vect prismPicDown = Vect(14.5,4,12.5);

	// 1-4 up
	Triangle prismFace1 = Triangle(Vect(13,6,14),Vect(13,6,11),prismPicUp,maroon);
	Triangle prismFace2 = Triangle(Vect(13,6,11),Vect(16,6,11),prismPicUp,blueviolet);
	Triangle prismFace3 = Triangle(prismPicUp,Vect(16,6,11),Vect(16,6,14),black);
	Triangle prismFace4 = Triangle(Vect(13,6,14),prismPicUp,Vect(16,6,14),metallic_gold);

	// 5-8 down
	Triangle prismFace5 = Triangle(Vect(13,6,14),Vect(13,6,11),prismPicDown,ghostwhite);
	Triangle prismFace6 = Triangle(Vect(13,6,11),Vect(16,6,11),prismPicDown,paleturquoise);
	Triangle prismFace7 = Triangle(prismPicDown,Vect(16,6,11),Vect(16,6,14),gold);
	Triangle prismFace8 = Triangle(Vect(13,6,14),prismPicDown,Vect(16,6,14),metallic_gold);


	Sphere sphere1 = Sphere(Vect(0,0,0),1,mediumblue);
	Sphere sphere2 = Sphere(Vect(19,1,6),0.5,pretty_green);

	// quadriculado
	//Plane scene_plane (Y, -1, tile_floor);
	Plane scene_plane (Y, 0, darkorange);

	scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

	// scene_objects.push_back(dynamic_cast<Object*>(&bacgroundWall1));
	// scene_objects.push_back(dynamic_cast<Object*>(&bacgroundWall2));
	// scene_objects.push_back(dynamic_cast<Object*>(&rightWall1));

	// scene_objects.push_back(dynamic_cast<Object*>(&templeFloor1));
	// scene_objects.push_back(dynamic_cast<Object*>(&templeFloor2));
	// scene_objects.push_back(dynamic_cast<Object*>(&templeRoof1));
	// scene_objects.push_back(dynamic_cast<Object*>(&templeRoof2));
	// scene_objects.push_back(dynamic_cast<Object*>(&column1p1));
	// scene_objects.push_back(dynamic_cast<Object*>(&column1p2));
	// scene_objects.push_back(dynamic_cast<Object*>(&column1p3));
	// scene_objects.push_back(dynamic_cast<Object*>(&column1p4));
	// scene_objects.push_back(dynamic_cast<Object*>(&column2p1));
	// scene_objects.push_back(dynamic_cast<Object*>(&column2p2));
	// scene_objects.push_back(dynamic_cast<Object*>(&column2p3));
	// scene_objects.push_back(dynamic_cast<Object*>(&column2p4));
	// scene_objects.push_back(dynamic_cast<Object*>(&column3p1));
	// scene_objects.push_back(dynamic_cast<Object*>(&column3p2));
	// scene_objects.push_back(dynamic_cast<Object*>(&column4p1));
	// scene_objects.push_back(dynamic_cast<Object*>(&column4p2));
	// scene_objects.push_back(dynamic_cast<Object*>(&dome));
	// scene_objects.push_back(dynamic_cast<Object*>(&contral_overal_sphere));
	 
	 // scene_objects.push_back(dynamic_cast<Object*>(&pyramidFloor1));
	 // scene_objects.push_back(dynamic_cast<Object*>(&pyramidFloor2));
	 // scene_objects.push_back(dynamic_cast<Object*>(&greatPyramidFace1));
	 // scene_objects.push_back(dynamic_cast<Object*>(&greatPyramidFace2));
	 // scene_objects.push_back(dynamic_cast<Object*>(&greatPyramidFace3));
	 // scene_objects.push_back(dynamic_cast<Object*>(&greatPyramidFace4));


	// cenario padrão

	// scene_objects.push_back(dynamic_cast<Object*>(&samallPyramidFace1));
	// scene_objects.push_back(dynamic_cast<Object*>(&samallPyramidFace2));
	// scene_objects.push_back(dynamic_cast<Object*>(&samallPyramidFace3));
	// scene_objects.push_back(dynamic_cast<Object*>(&samallPyramidFace4));

	// scene_objects.push_back(dynamic_cast<Object*>(&samallPyramid2Face1));
	// scene_objects.push_back(dynamic_cast<Object*>(&samallPyramid2Face2));
	// scene_objects.push_back(dynamic_cast<Object*>(&samallPyramid2Face3));
	// scene_objects.push_back(dynamic_cast<Object*>(&samallPyramid2Face4));

	// scene_objects.push_back(dynamic_cast<Object*>(&sun));


	// scene_objects.push_back(dynamic_cast<Object*>(&prismFace1));
	// scene_objects.push_back(dynamic_cast<Object*>(&prismFace2));
	// scene_objects.push_back(dynamic_cast<Object*>(&prismFace3));
	// scene_objects.push_back(dynamic_cast<Object*>(&prismFace4));

	// scene_objects.push_back(dynamic_cast<Object*>(&prismFace5));
	// scene_objects.push_back(dynamic_cast<Object*>(&prismFace6));
	// scene_objects.push_back(dynamic_cast<Object*>(&prismFace7));
	// scene_objects.push_back(dynamic_cast<Object*>(&prismFace8));

	//scene_objects.push_back(dynamic_cast<Object*>(&sphere1));
	// scene_objects.push_back(dynamic_cast<Object*>(&sphere2));

	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace1));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace2));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace3));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace4));

	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace5));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace6));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace7));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace8));

	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace9));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace10));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace11));
	scene_objects.push_back(dynamic_cast<Object*>(&cuboFace12));

	double xamnt,yamnt; 
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
			// if (width > height) {
			// 	// the image is wider than it is tall
			 	xamnt = ((i+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
			 	yamnt = ((height - j) + 0.5)/height;
			// }
			// else if (height > width) {
			// 	// the imager is taller than it is wide
			// 	xamnt = (i + 0.5)/ width;
			// 	yamnt = (((height - j) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
			// }else {
			// 	// the image is square
			// 	xamnt = (i + 0.5)/width;
			// 	yamnt = ((height - j) + 0.5)/height;
			// }



			// get camera origin 
			cam_ray_origin = scene_cam.getCameraPosition();
			// direção que a camera aponta 
			cam_ray_direction = camdir.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();
			//cam_ray_direction = camdir.vectAdd(camright.vectAdd(camdown)).normalize();
			
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

			// pintando o background
			if (index_of_winning_object == -1) {
				
				pixels[thisOne].r = paleturquoise.getColorRed();
				pixels[thisOne].g = paleturquoise.getColorGreen();
				pixels[thisOne].b = paleturquoise.getColorBlue();
			} else {
				// index coresponds to an object in our scene
				if (intersections.at(index_of_winning_object) > accuracy){
					// determine the position and direction vectors at the point of intersection
					intersection_position = cam_ray_origin.vectAdd(cam_ray_direction.vectMult(intersections.at(index_of_winning_object)));
					intersecting_ray_direction = cam_ray_direction;

					intersection_color = getColorAtRaycasting(intersection_position,intersecting_ray_direction, scene_objects, index_of_winning_object, light_sources, accuracy, ambientlight); 

					pixels[thisOne].r = intersection_color.getColorRed();
					pixels[thisOne].g = intersection_color.getColorGreen();
					pixels[thisOne].b = intersection_color.getColorBlue();					
				}
			}			
		}
	}

	t2 = clock();
	float diff = ((float)t2 - (float)t1)/1000;
	cout << diff << " seconds" << endl;

	Savebmp("scene.bmp",width,height,dpi,pixels);	

	delete pixels; // deslocando a memoria
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

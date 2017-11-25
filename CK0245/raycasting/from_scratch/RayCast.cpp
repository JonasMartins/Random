#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<limits>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>


#include"./RayCast.h"

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

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

typedef struct 
{
	double r;
	double g;
	double b;

}RGBType;

class RayCast
{

	public:
		RayCast(); // construtor
		void Run();

	private:

		void Savebmp(const char *,unsigned short,unsigned short,unsigned short,RGBType *);

	 	// unsigned short width;
	  // 	unsigned short height;
	  // 	unsigned short i;
  	// 	unsigned short j;
	  	
};
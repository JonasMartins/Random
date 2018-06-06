#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<string>
#include<map>
#include"./HashJoin.h"



using namespace std;

// g++ HashJoin.cpp -o HashJoin Main.cpp -o Main.exe


// chasing
// chasing

int main(int argc, char **argv)
{
	/*

	//int c;
//	int a;
//	const char * dd;
//	string s;
//	char b;
//	int i=0;
//	int j=1;
//	FILE * arq;
//	char line[50];
//	char buffer[] = {'0'};
*/

	// esquema para ler linha por linha via fread

	FILE * arq;
	arq = fopen("lineitem.txt","r+");
	//long lSize;
	fpos_t pos;
	char * buffer;
	size_t result;
	//fseek (arq, 0 , SEEK_END);
	//lSize = ftell (arq);
	//rewind (arq);
	//cout << sizeof(char)*lSize << endl;
	// buffer tem o tamanho de todo o arquivo em memória
	//buffer = (char*) malloc (sizeof(char)*lSize);
	//if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
	//cout << sizeof(buffer) << endl;
	fgetpos(arq,&pos);
	buffer  = (char*)malloc(sizeof(char)*256);
	
	// lembrando que result é o número de 
	// carabteres lidos bem sucedidos pelo fread
	fread(buffer,1,256,arq);
	cout << buffer << endl;

	char * clean;
	unsigned j=0;
	for(unsigned i=150;i<256;i++)
	{
		if(buffer[i] == '\n'){
			j=i;
			i=256;
		}
	}
	cout << j << endl;
	clean  = (char*)malloc(sizeof(char)*j);
	fsetpos(arq,&pos);
	fread(clean,1,j,arq);
	cout << clean << endl;
	free(clean);
	free(buffer);

	//HashJoin hash(a);
	//cout<<hash.getBinaryStringNumber(423)<<endl;
	
	//cout << hash.getBucketIndex("0100") << endl;

	return EXIT_SUCCESS;
}

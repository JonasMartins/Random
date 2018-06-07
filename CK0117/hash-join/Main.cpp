#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<string>
#include<map>
#include<ctime>
#include"./HashJoin.h"



using namespace std;

// g++ HashJoin.cpp -o HashJoin Main.cpp -o Main.exe
// g++ HashJoin.cpp -o HashJoin Main.cpp -o Main.exe -std=c++11

// g++ HashJoin.cpp -o HashJoin Main.cpp -o Main.exe -std=c++11
// ./Main.exe lineitem.txt col1 partsupp.txt col2


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
	int start_s=clock();

	 FILE * arq;
	 arq = fopen("/home/jonas/Documentos/SGBD/Tables/orders.dat","rb+");
	 //long lSize;
	 if(arq==NULL)
		 exit(1);
	 
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
 	for(unsigned i=50;i<250;i++)
 	{
 		if(buffer[i] == '\n'){
 			j=i;
 			i=250;
 		}
 	}
 	cout << j << endl;
	clean  = (char*)malloc(sizeof(char)*j);
	fsetpos(arq,&pos);
	fread(clean,1,j,arq);
	cout << clean << endl;
	free(clean);
	free(buffer);
	
	int stop_s=clock();
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << endl;


	//HashJoin hash(argc,argv);
	//string match = "l_suppkey";
	//char * a = (char*)"l_orderkey,l_partkey,l_suppkey,l_linenumber,l_quantity,l_extendedprice,l_discount,l_tax,l_returnflag,l_linestatus,l_shipDATE,l_commitDATE,l_receiptDATE,l_shipinstruct,l_shipmode,l_comment";
	//hash.getKeyColumn(a,match);
	//cout<<hash.getBinaryStringNumber(423)<<endl;
	
	//

	//cout << hash.getBucketIndex("0100") << endl;

	return EXIT_SUCCESS;
}

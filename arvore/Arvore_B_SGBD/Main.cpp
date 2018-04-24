#include <iostream>
#include <cstdio>
#include <cstring>
#include <typeinfo>

#include "ArvoreB.h"

using namespace std;

int insert_count ;

void menu()
{
    printf( "Menu:\n" ) ;
    printf( "Inserir: insert [key] [value]\n" ) ;
    printf( "Remover: remove [key]\n" ) ;
    printf( "Consulta: query [key]\n" ) ;
}

// g++ -lstdc++ ArvoreB.cpp -o ArvoreB Main.cpp -o Main.exe

int main(int argc, char **argv )
{
	menu();
	start();
	char * a = (char*)"test1";
	char * b = (char*)"test2";
	char * c = (char*)"test3";

	insert_bpt(1,a);
	insert_bpt(2,b);
	insert_bpt(3,c);
}
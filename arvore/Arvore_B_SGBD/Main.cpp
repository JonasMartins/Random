#include <iostream>
#include <cstdio>
#include <cstring>
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
	char * a = (char*)"test";
	insert_bpt(1,a);
}
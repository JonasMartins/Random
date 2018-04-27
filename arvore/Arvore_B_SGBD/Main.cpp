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
// g++ ArvoreB.cpp -o ArvoreB Main.cpp -o Main.exe

int main(int argc, char **argv )
{
	menu();
	start();
	char * a = (char*)"__8";
	char * b = (char*)"__5";
	char * c = (char*)"__1";
	char * d = (char*)"__7";

	insert_bpt(1,a);
	insert_bpt(2,b);
	insert_bpt(3,c);
	insert_bpt(4,d);

	//showSearch(2);
	//showDelete(2);

}
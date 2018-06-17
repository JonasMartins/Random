#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<string>
#include<map>
#include"./HashJoin.h"

using namespace std;

//g++ HashJoin.cpp -o HasJoin Main.cpp -o Main.exe
//./Main.exe ~/Documentos/SGBD/Tables/lineitem.dat l_ordeerkey ~/Documentos/SGBD/Tables/orders.dat o_orderkey

int main(int argc, char **argv)
{
	HashJoin hash(argc,argv);
	
	return EXIT_SUCCESS;
}

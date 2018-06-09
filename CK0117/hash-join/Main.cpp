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



	HashJoin hash(argc,argv);
	//string match = "l_suppkey";
	//char * a = (char*)"l_orderkey,l_partkey,l_suppkey,l_linenumber,l_quantity,l_extendedprice,l_discount,l_tax,l_returnflag,l_linestatus,l_shipDATE,l_commitDATE,l_receiptDATE,l_shipinstruct,l_shipmode,l_comment";
	//hash.getKeyColumn(a,match);
	//cout<<hash.getBinaryStringNumber(423)<<endl;
	
	//

	//cout << hash.getBucketIndex("0100") << endl;

	//l_orderkey,l_partkey,l_suppkey,l_linenumber,l_quantity,l_extendedprice,l_discount,l_tax,l_returnflag,l_linestatus,l_shipDATE,l_commitDATE,l_receiptDATE,l_shipinstruct,l_shipmode,l_comment

	//o_orderkey,o_custkey,o_orderstatus,o_totalprice,o_orderDATE,o_orderpriority,o_clerk,o_shippriority,o_comment

	// l_orderkey junta com o_orderkey

	return EXIT_SUCCESS;
}

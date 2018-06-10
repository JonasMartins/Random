#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<string>
#include<map>
#include<ctime>
#include"./HashJoin.h"

using namespace std;

int main(int argc, char **argv)
{


	HashJoin hash(argc,argv);

	//l_orderkey,l_partkey,l_suppkey,l_linenumber,l_quantity,l_extendedprice,l_discount,l_tax,l_returnflag,l_linestatus,l_shipDATE,l_commitDATE,l_receiptDATE,l_shipinstruct,l_shipmode,l_comment

	//o_orderkey,o_custkey,o_orderstatus,o_totalprice,o_orderDATE,o_orderpriority,o_clerk,o_shippriority,o_comment

	// l_orderkey junta com o_orderkey

	return EXIT_SUCCESS;
}

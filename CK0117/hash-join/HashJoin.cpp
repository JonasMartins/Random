#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<sstream>
#include<string>
#include"./HashJoin.h"

using namespace std;

// cout snippet @c 

// Recebe um numero decimal e retorna a
// sua representação em binario em uma string 
// porem está invertida
string  HashJoin::numberToBinaryInvert(int number)
{
	string v = "";
	unsigned int i;
	int buffer = number;
	while(buffer > 0)
	{
		i = buffer%2;
		buffer /= 2;
		v += to_string(i);
	}

	return v;

}


// pega a string representando o binário do número
// invertida e revert retornando a string correta
string HashJoin::getBinaryStringNumber(int value)
{
	
	string number = numberToBinaryInvert(value);
	string reverse = "";
	unsigned i; 
	for(i = number.length()-1;i>0;i--)
	{
		reverse += number.at(i);
	}
	reverse += number.at(0);
	return reverse;
}

// Gerar todos os buckets, com 4 níveis de números
// e já preencher a partir dos ids da tabela costumers
// esse buckets, cada bucket vai conter a tupla
// que é uma string do arquivo, com seu id correspondente
void HashJoin::generateAndFillBuckets()
{

}








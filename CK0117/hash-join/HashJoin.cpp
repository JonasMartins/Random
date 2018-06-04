#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<sstream>
#include<string>
#include"./HashJoin.h"

using namespace std;

HashJoin::HashJoin(string tuple)
{
	generateAndFillBuckets();
	string key = getCostumersKey(tuple);
	string bin = getBinaryStringNumber(stoi(key));
  string pattern = getPattern(bin);	
	unsigned index = getBucketIndex(pattern);
	cout << bin << endl;
	cout << pattern << endl;
	cout << "Bucket: " << index << endl;
	addToBuckets(index,tuple);
	showBucketContent(index);
}


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
	return adjustBits(reverse);
}

// Ajusta o tamanho da string para ter 16 bits de comprimento 
string HashJoin::adjustBits(string number)
{
	while(number.length()<16){
		number.insert(0,"0");
	}

	return number;
}


// Gerar todos os buckets, com 4 níveis de números
// e já preencher a partir dos ids da tabela costumers
// esse buckets, cada bucket vai conter a tupla
// que é uma string do arquivo, com seu id correspondente
void HashJoin::generateAndFillBuckets()
{
	initializeBuckets();

}

// inicializando o reconhecimento de bits
// para ser adicionado as primeiras posições
// da matriz de buckets 
void HashJoin::initializeBuckets()
{
	string possibilities[16] = {
		 "0000","0001","0010","0011", 
		 "0100","0101","0110","0111", 
		 "1000","1001","1010","1011",
		 "1100","1101","1110","1111",	
	};
	for(unsigned i = 0;i<16;i++)
		buckets[i][0] = possibilities[i];
	
	for(unsigned i = 0;i<16;i++)
		bucketsIndex[possibilities[i]] = i;
}

// uma forma de agilizar a inserção
// de uma string em um bucket, pegando já 
// o indice apropriado dele através de map
unsigned HashJoin::getBucketIndex(string bucket)
{
	return bucketsIndex[bucket];
}

// Adicionando ao array de buckets, 
// um push sempre em uma string vazia;
bool HashJoin::addToBuckets(unsigned bucket,string number)
{
	bool flag = false;
	for(unsigned i=0;i<50;i++)
	{
		if(buckets[bucket][i].compare("") == 0)
		{
			buckets[bucket][i] = number;
			flag = true;
			cout <<"Added!" << endl;		
			i = 50;
		}
	}
	return flag;
}


// Pegando a chave de uma tupla
// da tabela costumers 
string HashJoin::getCostumersKey(string tuple)
{
	
	size_t pos = tuple.find(";");
	string key = tuple.substr(0,pos);
	// key é exatamente o id de costumer
	// que vai servir para armazenar a tupla 
	// no seu bucket correspondente;
	return key;
}

// pegando os últimos 4 bits da representação
// em binario da chave de junção de uma tabela
string HashJoin::getPattern(string key)
{
	return key.substr(12,15);
}

void HashJoin::showBucketContent(int index)
{
	cout << "Conteúdo do bucket "<<index<<":"<<endl; 
	unsigned i = 0;
	while(buckets[index][i].compare("") != 0 )
	{
		cout << buckets[index][i] << endl;
		i++;
	}
}







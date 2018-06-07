#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<sstream>
#include<string>
#include<ctime>
#include"./HashJoin.h"

using namespace std;

HashJoin::HashJoin(int argc, char ** argv)
{
	// salvando o nome das tabelas passadas
	setTableNames(argv);

	exceptionInputs(argc,argv);
	getCleanLine();

	// generateAndFillBuckets();
	// string key = getCostumersKey(tuple);
	// string bin = getBinaryStringNumber(stoi(key));
 //  	string pattern = getPattern(bin);	
	// unsigned index = getBucketIndex(pattern);
	// cout << bin << endl;
	// cout << pattern << endl;
	// cout << "Bucket: " << index << endl;
	// addToBuckets(index,tuple);
	// showBucketContent(index);
}

void HashJoin::setTableNames(char ** argv)
{
	table1Name = argv[1];
	table2Name = argv[3];
}
// lendo os arquivos passados pela execoção
bool HashJoin::readTables(char ** argv)
{
	bool flag = true;
	table1 = fopen(argv[1],"rb+");
	table2 = fopen(argv[3],"rb+");
	if (table1 == NULL || table2 == NULL){
		flag = false;
		fclose(table1);
		fclose(table2);
	}
	return flag;
}

// lendo os nomes dos campos junção passados pela execução
bool HashJoin::readKeys(char ** argv)
{
	bool flag = true;
	key1 = argv[2];
	key2 = argv[4];
	if (key1 == NULL || key2 == NULL)
		flag = false;
	return flag;
}

// analisa a validade dos inputs passados na execução
void HashJoin::exceptionInputs(int argc, char **argv)
{
	if((argc < 5)){
		cout<<"Quantidade de parametros incorreta: "<<endl;
		cout<<"tabela1.txt key1 tabela2.txt key2"<<endl;
		exit(1);	
	}

	if((!readTables(argv)) || (!readKeys(argv)))
	{
		cout<<"Erro nos arquivos ou strings passadas, tabelas ou chaves de junção"<<endl;
		exit(1);
	} else {
		cout << "Files readed corretly." << endl;
	}
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

char * HashJoin::getCleanLine()
{

	 //FILE * arq;
	 //arq = fopen("/home/jonas/Documentos/SGBD/Tables/orders.dat","rb+");
	 //long lSize;
	 //if(arq==NULL)
		// exit(1);
	 
	table1 = fopen(getTable1Name(),"rb+");
	
	 //int start_s=clock();

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
	fgetpos(table1,&pos);
	buffer = (char*)malloc(sizeof(char)*256);

 	// lembrando que result é o número de 
 	// carabteres lidos bem sucedidos pelo fread
 	fread(buffer,1,256,table1);
 	//cout << buffer << endl;

 	char * clean;
 	unsigned j=0;
 	for(unsigned i=50;i<250;i++)
 	{
 		if(buffer[i] == '\n'){
 			j=i;
 			i=250;
 		}
 	}
 	//cout << j << endl;
	clean  = (char*)malloc(sizeof(char)*j);
	fsetpos(table1,&pos);
	fread(clean,1,j,table1);
	cout << clean << endl;
	free(clean);
	free(buffer);
	
	//int stop_s=clock();
	//cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC) << endl;

	return clean;

}


// pegando uma tabela dada por um arquivo e lendo
// e retornando, essa função é chamada dentro 
// de um for e a sua funcionalidade depende do set
// e get position do arquivo para ler corretamente.
void HashJoin::readCleanFileLine(char * file)
{

}

// retorna o número da coluna, sa não achar, retorna 99
unsigned HashJoin::getKeyColumn(char *a,string match)
{
	unsigned i,j,k,l;
	i=j=k=0;
	l=99;
	string buffer = "";
	string aa;
	aa.assign(a);
	while(j<aa.length()){
		if(aa[j] == ','){
			l=i;
			i++;
			if(match.compare(aa.substr(k,(j-k))) == 0){				
				j=aa.length();
			}else {
				k=j+1;
			}
		}
		j++;			
	}
	cout<<l<<endl;
	return l;
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

// Ajusta o tamanho da string para ter 32  bits de comprimento 
string HashJoin::adjustBits(string number)
{
	while(number.length()<32){
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
	for(unsigned i=0;i<100;i++)
	{
		if(buckets[bucket][i].compare("") == 0)
		{
			buckets[bucket][i] = number;
			flag = true;
			cout <<"Added!" << endl;		
			i = 100;
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
	return key.substr(28,31);
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

char *  HashJoin::getTable1Name()
{
	return table1Name; 
}

char *  HashJoin::getTable2Name()
{
	return table2Name; 
}



#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<sstream>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdexcept>
#include"./HashJoin.h"

using namespace std;

HashJoin::HashJoin(int argc, char ** argv)
{

	exceptionInputs(argc,argv);
	
	// salvando o nome das tabelas passadas
	setTableNames(argv);
	generateAndFillBuckets();
	
	readCleanFileLine(); // lendo as linhas da tabela e armazenando nos buckets
	
	showAllBucketsContent();
		
	readSecondTable();
	succesfullyOutput();
}




// Setando os nomes e os atributos de junção nas
// variáveis, sempre colocando o menor arquivo na
// tabela1 para ser armazenada em memória
void HashJoin::setTableNames(char ** argv)
{
	struct stat filestatus;
	stat(argv[1],&filestatus);
	long size1 = filestatus.st_size;
	stat(argv[3],&filestatus);
	long size2 = filestatus.st_size;
	
	if(size1<=size2){
		table1Name = argv[1];
		table2Name = argv[3];
		key1 = argv[2];
		key2 = argv[4];
	}	else {
		table1Name = argv[3];
		table2Name = argv[1];
		key1 = argv[4];
		key2 = argv[2];
	}

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

// Dentro do arquivo binário, após pular a primeira linha que contém
// uma frase solta que quebraria a implementação do programa, existe uma
// linha com os nomes das colunas da tabela, nessa função, armazenamos
// o número dessa coluna, se a mesma for igual ao nome passado por argumento
// depois de ler a primeira linha, retorna o ponteiro do arquivo para
// a próxima linha, onde outro método vai ler o restante do arquivo e armazenar
// as tuplas no seu bucket correspondente.
fpos_t  HashJoin::getCleanHeader()
{
	fpos_t pos;// = jumpBrokenLine();
	char * clean;
	char * buffer;
 	unsigned j=0;
	unsigned i;
	table1 = fopen(getTable1Name(),"rb+");
	fgetpos(table1,&pos);
	buffer = (char*)malloc(sizeof(char)*256);
	//fsetpos(table1,&pos); // setando a posição depois de ter pulado a linha quebrada
 	fread(buffer,1,256,table1);
 	//cout << "buffer:"<<buffer << endl;
	for(i=50;i<250;i++){
 		if(buffer[i] == '\n'){
 			j=i+1;
 			i=256;
 		}
 	}
	clean = (char*)malloc(sizeof(char)*j);
	fsetpos(table1,&pos);// setando novamente no inicio  da linha do buffer
	fread(clean,1,j,table1);
	fgetpos(table1,&pos);// setando o ponteiro no final da linha de cabeçalho
	clean[j-1]='\0';
	free(buffer);
	unsigned index = getKeyColumn(clean,getColumn1Name());
	if(index == 99){
		cout << "Coluna de junção não encontrada para essa tabela"<<endl;
		exit(0);
	}else {
	 	key1Position = index; //armazeno o indice da coluna do atributo de junção da tabela 1
	}
	fclose(table1);
	free(clean);
	return pos;
}

// Método que vai ler linha por linha da tabela a ser armazenada
// no seu devido bucket
void HashJoin::readCleanFileLine()
{
	int key;
	string bin,pattern;
	fpos_t pos = getCleanHeader();
	char * clean;
	char * buffer;
 	unsigned j=0;
	unsigned i,k,index;
	table1 = fopen(getTable1Name(),"rb+");
	for(unsigned ii=0;ii<7900;ii++)// 3000 limite...
	{
		buffer = (char*)malloc(sizeof(char)*256);
		fsetpos(table1,&pos); // setando a posição depois de ter pulado a linha quebrada
	 	fread(buffer,1,256,table1);
 		//cout << "buffer:"<<buffer << endl;
		for(i=20;i<250;i++){
 			if(buffer[i] == '\n'){
 				j=i+1;
 				i=250;
 			}
 		}
		clean = (char*)malloc(sizeof(char)*j);
		fsetpos(table1,&pos);// setando novamente no inicio  da linha do buffer
		fread(clean,1,j,table1);
		fgetpos(table1,&pos);// setando o ponteiro no final da linha de cabeçalho
		clean[j-1]='\0';
		// k é o inicio da string do atributo de junção.
		k = getJoinColumnPosition(clean,getKey1Position());

		// key é a string do atributo de junção.
		key = getJoinColumn(clean,k);		
		bin = getBinaryStringNumber(key);
		pattern = getPattern(bin);
		index = getBucketIndex(pattern);
		if(!addToBuckets(index,clean))
		{
			cout <<"Esouro de bucket, sem algoritimo de duplicamento ainda.."<<endl;
			exit(1);
		}
		free(clean);
		free(buffer);
	}
	fclose(table1);
}
// Pegando a posição inicial da  coluna de junção
// na tupla recem lida da tabela que vai ser armazenada na memória.
unsigned  HashJoin::getJoinColumnPosition(char * tuple,unsigned col)
{
	unsigned pos;
	size_t found; 
	size_t sum = 0;
	string buffer = "";
 	string aux = "";
	buffer.assign(tuple);	
	for(unsigned i = 0;i<col;i++){
		found = buffer.find(";");
		sum+=(found+1);
		aux = buffer;
		buffer = aux.erase(0,found+1);
		//cout <<"buffer: "<<buffer<<endl;
	}
	pos = static_cast<unsigned>(sum);
	return pos;
}

// Recebe a posição inicial da coluna de junção, a tupla 
// e lê os póximos caracteres até encontrar a virgula
// pegando exatamente o valor do atributo de junção
int  HashJoin::getJoinColumn(char * tuple,unsigned pos)
{
	int ikey;
	unsigned i=pos;
	string key="";
	while(tuple[i]!=';'/* || tuple[i]!=last*/){
		key+=tuple[i];
		i++;
	}
	try{
		ikey = stoi(key);
	} catch(invalid_argument& e){
		cout<<"A coluna passada não é do tipo int, erro."<<endl;
		exit(1);
	}
	return ikey;
}


// retorna o número da coluna, sa não achar, retorna 99
unsigned HashJoin::getKeyColumn(char *a,string match)
{
	//cout <<"match "<<match << endl;
	unsigned i,j,k,l;
	i=j=k=0;
	l=99;
	string buffer = "";
	string aa;
	aa.assign(a);
	char last = aa[aa.length()-1];
	while(j<aa.length()){
		// para ficar mais eficiente, vamos assumir que a junção nunca é
		// a ultima coluna
		if(aa[j] == ';' /*|| aa[j] == last*/){
			l=i;
			i++;
			if(match.compare(aa.substr(k,(j-k))) == 0){				
				j=aa.length();
			}else {
				k=j+1;
				l=99;
			}
		}
		j++;			
	}
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
// da matriz de buckets, a ideia inicial era ter 16 buckets
// mas ao testar a tabela orders, foi visto que a mesma não
// tem no atributo de junção números que possam
// aparecer na segunnda metade dos buckets, logo
// para uma demonstração'é preferível economizar 
// memória ao máximo.
void HashJoin::initializeBuckets()
{
	string possibilities[8] = {
		 "0000","0001","0010","0011", 
		 "0100","0101","0110","0111" /*, 
		 "1000","1001","1010","1011",
		 "1100","1101","1110","1111",	*/
	};
	for(unsigned i = 0;i<8;i++)
		buckets[i][0] = possibilities[i];
	
	for(unsigned i = 0;i<8;i++)
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
	for(unsigned i=0;i<1000;i++)
	{
		if(buckets[bucket][i].compare("") == 0)
		{
			buckets[bucket][i] = number;
			flag = true;
			i = 1000;
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

// Mostrando todo o conteúdo de todos os buckets
void HashJoin::showAllBucketsContent()
{
	unsigned i;
	//cout<<"Conteúdo de todos os buckets com as tuplas da tabela menor:"<<endl;
	for(i=0;i<8;i++){
		showBucketContent(i);
	}
}

void HashJoin::showBucketContent(int index)
{
	//cout << "Conteúdo do bucket "<<index<<":"<<endl; 
	unsigned i = 0;
	while(buckets[index][i].compare("") != 0 )
	{
		//cout << buckets[index][i] << endl;
		i++;
	}
	//cout<<"Posições ocupadas: "<<i<<endl;
	bucketsLength[index] = i; // salvando o comprimento do bucket.
}

// Descobrindo quantas tuplas tem a tabela que será
// ESSE MÉTODO NÃO SERÁ USADO, se fossemos armazenar orders 
// em memŕia os bueckts teriam que ter 93.751 espaços de armazenamento
// orders tem 1.500.001 tuplas
long HashJoin::getTable1Count()
{
	long tuples = 0;
	FILE * arq = fopen(getTable1Name(),"r");
	int ch;
	while(EOF != (ch=getc(arq)))
	{
		if('\n'==ch)
			++tuples;
	}
	return tuples;
}

// Lendo a segunda tabela, comparando o atributo de
// junção no bucket correspondente e escrevendo no arquivo
// de saída.
void HashJoin::readSecondTable()
{
	int key;
	char * lineChar;
	unsigned ch,index,k,j,i=0;
	string bin,pattern,line="",header="";
	table2 = fopen(getTable2Name(),"rb+");

	FILE * arq = fopen("result.txt","w");

	// Lendo o cabealho da segunda tabela
	while('\n'!=ch)
	{
		ch=getc(table2);
		header+=ch;
	}
	index = getKeyColumn((char*)header.c_str(),getColumn2Name());
	if(index == 99){
		cout << "Coluna de junção não encontrada para essa tabela"<<endl;
		exit(0);
	}else {
	 	key2Position = index;
	}
	while(i<10000)
	{
		ch=getc(table2);
		line+=ch;
		if('\n'==ch)
		{
			++i;
			//cout<<line<<endl;
			lineChar = (char*)line.c_str();
			// k é o inicio da string do atributo de junção.
			k = getJoinColumnPosition(lineChar,getKey2Position());
			// key é a string do atributo de junção.
			key = getJoinColumn(lineChar,k);
			bin = getBinaryStringNumber(key);
			pattern = getPattern(bin);
			j = getBucketIndex(pattern);
			compareKeyBucket(arq,j,lineChar,key);

			line.clear();
		}
	}
	fclose(table2);
	fclose(arq);
}

// passar a coluna, o indice do bucket e o atributo de junção 
// dentro do bucket correspondente
void HashJoin::compareKeyBucket(FILE * file, unsigned id,char * line,int key)
{
	
	int kkey;
	string buffer;
	char * char_buffer;
	unsigned index,k,j,i=1;
	// precorre o bucket para ver se encontra, se sim
	// sai do loop, pior caso, percorre as 1000 posições.
	while(i<bucketsLength[id])
	{
		buffer = buckets[id][i];
		char_buffer = (char*)buffer.c_str();
		k = getJoinColumnPosition(char_buffer,getKey1Position());		
		kkey = getJoinColumn(char_buffer,k);
		if(kkey==key){
			fprintf(file,"%s",line);
			fprintf(file,"%s",char_buffer);
			//cout<<kkey<<endl;
			i=bucketsLength[id];
		}

		i++;
	}
} 

void HashJoin::succesfullyOutput()
{
	cout<<"Esse programa executou a seguinte consulta: "<<endl;
	cout<<"SELECT *"<<endl;
	cout<<"FROM "<<getTable1Name()<<","<<endl;
	cout<<getTable2Name()<<endl;
	cout<<"WHERE "<<getColumn1Name()<<" = "<<getColumn2Name()<<" LIMIT 8000;"<<endl;
}

// ================== GETTERS AND SETTERS

char *  HashJoin::getTable1Name()
{
	return table1Name; 
}

char *  HashJoin::getTable2Name()
{
	return table2Name; 
}

char *  HashJoin::getColumn1Name()
{
	return key1; 
}

char *  HashJoin::getColumn2Name()
{
	return key2; 
}

unsigned HashJoin::getKey1Position()
{
	return key1Position;
}

unsigned HashJoin::getKey2Position()
{
	return key2Position;
}	


#include<string.h>
#include<iostream>
#include<map>
using namespace std;


class HashJoin 
{

	public:

		HashJoin(int, char **);
		
		string getBinaryStringNumber(int);
		
		char * getTable1Name();
		char * getTable2Name();
		char * getColumn1Name();
		char * getColumn2Name();
	
		unsigned getKey1Position();
		unsigned getKey2Position();
		unsigned getBucketIndex(string);
		unsigned getKeyColumn(char *,string);

	private:

		string buckets[8][1000];
		string adjustBits(string);
		string getPattern(string);
		string getCostumersKey(string);
		string numberToBinaryInvert(int);

		long getTable1Count();
		
		
		fpos_t getCleanHeader();


		void succesfullyOutput();
		void readCleanFileLine();
		void setTableNames(char **);
		void compareKeyBucket(FILE * ,unsigned,char *,int);

		map<string,unsigned> bucketsIndex;

		bool readKeys(char **);
		bool readTables(char **);
		bool addToBuckets(unsigned,string);

		void readSecondTable();
		void initializeBuckets();
		void showBucketContent(int);
		void showAllBucketsContent();
		void generateAndFillBuckets();
		void exceptionInputs(int, char **);
		

		int  getJoinColumn(char *,unsigned);
	
		unsigned getJoinColumnPosition(char *,unsigned);

		// ====================== VARIÁVEIS
		
		unsigned key1Position;
		unsigned key2Position;
		unsigned bucketsLength[8];
		
		char * key1;
		char * key2;
		char * table1Name;
		char * table2Name;

		FILE * table1;
		FILE * table2;
};


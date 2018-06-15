#include<string.h>
#include<iostream>
#include<map>
using namespace std;


class HashJoin 
{

	public:

		HashJoin(int, char **);
		string getBinaryStringNumber(int);
		
		unsigned getKeyColumn(char *,string);
		unsigned getBucketIndex(string);
		
		char * getTable1Name();
		char * getTable2Name();
		
		char * getColumn1Name();
		char * getColumn2Name();
	
		unsigned getKey1Position();
		unsigned getKey2Position();

	private:
		string numberToBinaryInvert(int);
		string adjustBits(string);
		string getCostumersKey(string);
		string buckets[16][200];
		string getPattern(string);
		int  getJoinColumn(char *,unsigned);
		
		long getTable1Count();
		
		//fpos_t jumpBrokenLine();
		
		fpos_t getCleanHeader();


		map<string,unsigned> bucketsIndex;
	

		void setTableNames(char **);
		void readCleanFileLine();


		bool readKeys(char **);
		bool readTables(char **);
		bool addToBuckets(unsigned,string);

		void exceptionInputs(int, char **);
		void initializeBuckets();
		void generateAndFillBuckets();
		void showBucketContent(int);
		void showAllBucketsContent();
		
		void readingTable2();

		unsigned getJoinColumnPosition(char *,unsigned);


		// ====================== VARIÁVEIS
		
		unsigned key1Position;
		unsigned key2Position;
		char * key1;
		char * key2;
		char * table1Name;
		char * table2Name;

		FILE * table1;
		FILE * table2;
};


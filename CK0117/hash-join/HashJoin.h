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
	
	private:
		string numberToBinaryInvert(int);
		string adjustBits(string);
		string getCostumersKey(string);
		string buckets[16][100];
		string getPattern(string);

		
		
		char * getCleanLine();


		map<string,unsigned> bucketsIndex;
	

		void setTableNames(char **);
		void readCleanFileLine(char *);


		bool readKeys(char **);
		bool readTables(char **);
		bool addToBuckets(unsigned,string);

		void exceptionInputs(int, char **);
		void initializeBuckets();
		void generateAndFillBuckets();
		void showBucketContent(int);

		char * key1;
		char * key2;
		char * table1Name;
		char * table2Name;

		FILE * table1;
		FILE * table2;
};


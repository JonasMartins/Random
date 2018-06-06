#include<string.h>
#include<iostream>
#include<map>
using namespace std;


class HashJoin 
{

	public:

		HashJoin(int, char **);
		string getBinaryStringNumber(int);
		
		unsigned getBucketIndex(string);
	
	private:
		string numberToBinaryInvert(int);
		string adjustBits(string);
		string getCostumersKey(string);
		string buckets[16][100];
		string getPattern(string);
	  
		
		map<string,unsigned> bucketsIndex;
	
		void readCleanFileLine(char *);

		bool readKeys(char **);
		bool readTables(char **);
		bool addToBuckets(unsigned,string);

		void exceptionInputs(int, char **);
		void initializeBuckets();
		void generateAndFillBuckets();
		void showBucketContent(int);

};


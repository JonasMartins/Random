#include<string.h>
#include<iostream>
#include<map>
using namespace std;


class HashJoin 
{

	public:

		HashJoin();
		string getBinaryStringNumber(int);
		
		unsigned getBucketIndex(string);
	
	private:
		string numberToBinaryInvert(int);
		string adjustBits(string);
		
		string buckets[16][50];
	  map<string,unsigned> bucketsIndex;
	
		
		bool addToBuckets(unsigned,string);
		void initializeBuckets();
		void generateAndFillBuckets();
};


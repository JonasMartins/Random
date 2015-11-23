#include<string.h>
#include<iostream>
using namespace std;


class getFuncoes{

	public:
	getFuncoes(string);
	void setFunctionName(string);
	string getFunctionName();
	int Length();
	string cleanString(string);
	void showCharacters(string);
	
	private:
	string functionName;
	void separateCharacters();	
	char operadores [20];
	double numeros [20];

};
 

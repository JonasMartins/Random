#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<sstream>
#include"./getFuncoes.h"

using namespace std;
	
	int i=0;
	int j=0;
	int k=0;
	double d;	

	getFuncoes::getFuncoes(string function){ // construtor
		setFunctionName( function );
	}

	void getFuncoes::setFunctionName(string name){ //setter
		functionName = cleanString(name);
	}
	string getFuncoes::getFunctionName(){//getter
		return functionName;
	}

	int getFuncoes::Length(){		
		for(i=0;i<getFunctionName().length();i++){
			 	getFunctionName()[i]; 
		}
		return i;
	}

	string getFuncoes::cleanString(string s){
		char clean[100];		
		for(i=0;i!='\n';i++){
			clean[i]=s[i];
		}
		return clean;
	}
	void getFuncoes::showCharacters(string s){
	for(i=0;i<s.length();i++){
			cout << s[i]; 
		} 
	}
	void getFuncoes::separateCharacters(){

		string s = cleanString(getFunctionName());
		string s2 = s;
		std::ostringstream buff;
		std::string str;
		while(s2.length()>0){
		d = atof(s2.c_str());
		if(d!=0){
			numeros[i] = d;
			i++;
			buff << d;			
			str = buff.str();
			s2.erase(0,str.length()); 
			buff.str(std::string()); 	
		}else{
			operadores[j] = s2[k-1]; 
			j++;
			s2.erase(0,1);
			}
		k++;
	}
	/*
		AQUI OS NUMEROS E O CARACTERES JÁ ESTÃO EM SEUS
		RESPECTIVOS ARRAYS	
	*/

	}











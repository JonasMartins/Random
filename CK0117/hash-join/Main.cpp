#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<string>
#include"./HashJoin.h"



using namespace std;

// g++ HashJoin.cpp -o HashJoin Main.cpp -o Main.exe


int main(int argc, char **argv)
{
	

	fpos_t pos; // character position into file
	int c;
	int a;
	const char * dd;
	string s;
	char b;
	int i=0;
	int j=1;
	FILE * arq;
	char line[50];
	
	arq = fopen("orders.txt","r+");
	if( arq == NULL) perror("Error");
	else {

			srand(time(NULL));

			while(j<600){

			//c = rand()%400 +1;
			//cout << c << endl;
			
			
			//if(fgets(c,1,arq) != NULL){
				//cout << c;
			//}
			//c = fgetc(arq);
			//b = c;
			//cout << b;
			//fseek(arq,i,SEEK_SET);
			//c = fgetc(arq);
			//if ((char)c == '\n')
			//	cout << "A\n"; 
		
		
			c = fgetc(arq);
			//i++;
			if((char)c == '%'){
				j++; // line number, same as tuple id
				//fseek(arq,i+1,SEEK_SET);
				a = rand()%550+1;// random number from 1 to 400
				//a = j;
				s = to_string(a);// convert the a number to string
				dd = s.c_str();// convert the string number a to const char *
				//cout << dd;
				fputs(dd,arq);
			}	
		}
	}	
	fclose(arq);
	//const char * dd;
	//string str;
	//str = to_string(340);
	//dd = str.c_str();
	//cout << dd  << endl;

	return EXIT_SUCCESS;
}

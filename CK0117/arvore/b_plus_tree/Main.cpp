#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include"./BplusTree.h"


// g++ BplusTree.cpp -o BplusTree Main.cpp -o Main.exe

int main(int argc,char **argv){

	int n;
  cout<<"enter the no of elements to be inserted\n";
  cin>>n;

  // order
  BplusTree tree(5);

  tree.run(n);

	return EXIT_SUCCESS;
}
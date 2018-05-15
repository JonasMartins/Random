#include<stdio.h>
#include<iostream>

using namespace std;

struct node
{
  int *data; // array com os valores dos espaços, caixas
  node **child_ptr; // lista de graus +1 ponteiros que apontam para outros nós
  bool leaf; // boolean para saber se este nó é folha 
  int n; // contador de espaços preenchidos do nó
};

class BplusTree 
{

public:

	BplusTree(int);
	
	void traverse(node *);
	void sort(int *,int);
	void insert(int);
	void run(int);

	int split_child(node *,int);

	node * init();

private:
	int degree;
	node *root = NULL;
	node *np = NULL; 
	node *x = NULL;

};
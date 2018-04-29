#include<stdio.h>
#include<iostream>

using namespace std;

struct node
{
    int *data;
    node **child_ptr;
    bool leaf;
    int n;
};

class BplusTree 
{

public:

	BplusTree();
	
	void traverse(node *);
	void sort(int *,int);
	void insert(int);
	void run(int);

	int split_child(node *,int);

	node * init();

private:
	node *root = NULL;
	node *np = NULL;
	node *x = NULL;

};
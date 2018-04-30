#include<stdio.h>
#include<iostream>
#include"./BplusTree.h"

BplusTree::BplusTree(int degree_size) 
{
	degree = degree_size;
}

void BplusTree::run(int n)
{
	int i,t;
  for(i = 0; i < n; i++)
  {
    cout<<"enter the element\n";
    cin>>t;
    insert(t);
  }
  cout<<"traversal of constructed tree\n";
  traverse(root);
  fflush(stdin);
  getchar();
}


node * BplusTree::init()
{
  int i;
  np = new node;
  np->data = new int[degree]; // array of degree spaces
  np->child_ptr = new node *[degree+1]; // aray of degree + 1 spaces
  np->leaf = true;
  np->n = 0;
  for (i = 0; i < degree+1; i++)
  {
  	np->child_ptr[i] = NULL;
  }
  return np;
}

void BplusTree::traverse(node *p)
{
  cout<<endl;
  int i;
  for (i = 0; i < p->n; i++)
  {
    if (p->leaf == false)
    {
    	traverse(p->child_ptr[i]);
    }
    cout << " " << p->data[i];
  } 
  if (p->leaf == false)
  {
  	traverse(p->child_ptr[i]);
  }
  cout<<endl;
}

void BplusTree::sort(int *p, int n)
{
  int i, j, temp;
  for (i = 0; i < n; i++)
  {
    for (j = i; j <= n; j++)
    {
      if (p[i] > p[j])
      {
          temp = p[i];
          p[i] = p[j];
          p[j] = temp;
      }
    }
  }
}

int BplusTree::split_child(node *x, int i)
{
  int j, mid;
  node *np1, *np3, *y;
  np3 = init();
  np3->leaf = true;
  if (i == -1)
  {
    mid = x->data[2];
    x->data[2] = 0;
    x->n--;
    np1 = init();
    np1->leaf = false;
    x->leaf = true;
    for (j = 3; j < degree; j++)
    {
        np3->data[j - 3] = x->data[j];
        np3->child_ptr[j - 3] = x->child_ptr[j];
        np3->n++;
        x->data[j] = 0;
        x->n--;
    }
    for(j = 0; j < degree+1; j++)
    {
        x->child_ptr[j] = NULL;
    }
    np1->data[0] = mid;
    np1->child_ptr[np1->n] = x;
    np1->child_ptr[np1->n + 1] = np3;
    np1->n++;
    root = np1;
  }
  else
  {
    y = x->child_ptr[i];
    mid = y->data[2];
    y->data[2] = 0;
    y->n--;
    for (j = 3; j < degree; j++)
    {
      np3->data[j - 3] = y->data[j];
      np3->n++;
      y->data[j] = 0;
      y->n--;
 		}
    x->child_ptr[i + 1] = y;
    x->child_ptr[i + 1] = np3; 
  }
  return mid;
}

void BplusTree::insert(int a)
{
	cout<<"value to add: "<<a<<endl;
  int i, temp;
  x = root;
  if (x == NULL) // if root is null,
  {
    root = init();
    x = root;
    cout<<"root added!\n"; 
  }
  else // root is not null
  {
    if (x->leaf == true && x->n == degree) // se é folha e não tem mais espaços vazios
    {
    cout<<"é folha e não tem mais espaços vazios\n";
      temp = split_child(x, -1); // split nesse nó, temp é um int
      cout<<"temp1: "<<temp<<endl;
      x = root; // x continua sendo o root
			cout<<"espaços preenchidos nesse nó: "<<x->n<<endl;
      for (i = 0; i < (x->n); i++) // for pelos espaços preenchidos desse nó 
      {
      	// se o valor a ser adicionado é maior do que a posição atual
      	// e menor do que a próxima, incrementa i
        if ((a > x->data[i]) && (a < x->data[i + 1]))
        {
        		cout<<"enter 2 if\n";
            i++;
            break;
        }
        // se o valor a ser adicionado for menor que o primeiro elemento do nó, 
        // break e pego o i
        else if (a < x->data[0])
        { cout<<"enter 3 if\n"; break; }
        else
        { cout<<"enter 4 if\n"; continue; }
      }
      x = x->child_ptr[i]; // desço para o filho com valor i
    	cout<<"i: "<<i<<endl;
    }
    else // se não é folha ou tem espaços vazios no nó
    {
    	cout<<"se não é folha ou tem espaços vazios no nó\n";
      while (x->leaf == false) // enquanto esse nó não for folha, 
      {
      for (i = 0; i < (x->n); i++) // for pelos espaços preenchidos desse nó
      {	
      	// se o valor a ser adicionado é maior do que a posição atual
      	// e menor do que a próxima, incrementa i
        if ((a > x->data[i]) && (a < x->data[i + 1]))
        {
        	cout<<"enter 5 if\n";
          i++;
          break;
        }
        // se o valor a ser adicionado for menor que o primeiro elemento do nó, 
        // break e pego o i
        else if (a < x->data[0])
        { cout<<"enter 6 if\n"; break; }
        else
        { cout<<"enter 7 if\n"; continue; }
      }
      	// se o filho desse nó não tiver mais espaços vazios
        if ((x->child_ptr[i])->n == degree)
        {
          temp = split_child(x, i);
         	cout<<"temp2: "<<temp<<endl;
          x->data[x->n] = temp;
          x->n++;
          continue;
        }
        else
        {
        	cout<<"enter 8 if\n";
          x = x->child_ptr[i];
        }
      }
    }
  }
  x->data[x->n] = a;
  sort(x->data, x->n);
  x->n++; // incrementa o contador mostrando que um dos espaços do nó foi preenchido
  cout<<"espaços preenchidos nesse nó: "<<x->n<<endl;
}
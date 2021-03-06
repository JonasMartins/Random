#ifndef __GP__BPT__
#define __GP__BPT__

#include <iostream> 
#include <string> 
#include <vector> 
#include <typeinfo>

const int M = 3; // max comprimento do no 

struct node {
  bool is_leaf;
  bool is_root;
  int key_num;
  int key[M];
  void * pointer[M + 1];
  void * father;
};

node * new_node();
void showSearch(int key);
void showDelete(int key);
void splite(node * node);
void printNode(node * node);

extern int node_count;
extern int splite_count;
extern void start();
extern bool insert_bpt(int key, void * value);
extern bool delete_bpt(int key);
extern char * query_bpt(int key);

#endif
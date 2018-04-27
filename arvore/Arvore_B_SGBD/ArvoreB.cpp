#include <iostream>
#include <string>
#include <typeinfo>
#include "ArvoreB.h"
using namespace std;


node *root ;
node * nodd;
node * fatther;

int node_count ;
int splite_count ;

void insert_node(node *node , int key , void *value );
void delete_node(node *node , int key );
char * query_bpt( int key );

void start()
{
  root = new_node() ;
  root->is_root = true ;
  root->is_leaf = true ;
  node_count = 0 ;
  splite_count = 0 ;

  cout<<"Start build first node, the Tree Root"<<endl;
}

node * new_node()
{
  node_count ++ ;

  node *p = new node ;
  p->is_leaf = false ;
  p->is_root = false ;
  p->key_num = 0 ;
  p->pointer[ 0 ] = NULL ;
  p->father = NULL ;
  return p ;
}

node *find_leaf( int key )
{
   node *now = root ;
   while ( !now->is_leaf )
   {
    for ( int i = 0 ; i <= now->key_num ; i ++ )
      if ( i == now->key_num || key < now->key[ i ] )
      {
        now = ( node *) now->pointer[ i ] ;
        break ;
      }
  }
  return now ;
}

void split( node *_node )
{   
  //node * fatther = (node*)malloc(sizeof(node));
  fatther = new_node();
  splite_count ++ ;
  cout << endl << "split!: | ";//<< _node->key_num<<" | "<< _node->key[0]<<" | "<< _node->key[1]<<endl;
  nodd = new_node();

  int mid_key = _node->key[ M / 2 ] ;
  //cout<<"mid_key: "<<mid_key<<endl;

  nodd->key_num = M - M / 2 - 1 ;
  //cout<<"nodd->key_num: "<<nodd->key_num<<endl;

  for ( int i = 0 ; i < nodd->key_num ; i ++ )
  {
    nodd->key[ i ] = _node->key[ i + ( M / 2 + 1 ) ] ;
    nodd->pointer[ i ] = _node->pointer[ i + ( M / 2 + 1 ) ] ;
  }
  nodd->pointer[ nodd->key_num ] = _node->pointer[ M ] ;
  _node->key_num = M / 2 ;

  if ( _node -> is_leaf )
  {
    _node->key_num ++ ;
    nodd->pointer[ 0 ] = _node->pointer[ 0 ] ;
    _node->pointer[ 0 ] = nodd ;
    nodd->is_leaf = true ;
    mid_key = _node->key[ M / 2 + 1 ] ;
  }

  if ( _node -> is_root )
  {
    _node-> is_root = false ;
    root = new_node() ;
    root->is_root = true ;
    root->key[ 0 ] = mid_key ;
    root->pointer[ 0 ] = _node ;
    root->pointer[ 1 ] = nodd ;
    root->key_num = 1 ;

    _node->father = nodd->father = root ;
  } else
  {
    nodd->father = _node->father;
    insert_node( (node*)_node->father,mid_key,(void *)nodd ) ;
  }
  //fatther = (node*)_node->father
  
  // cout << "midnum: " << mid_key << endl;
  // cout << "father: " << (( node * )_node -> father )-> key_num << ' '<< ((node*)_node -> father )-> key[ 0 ] << endl;
  // cout << "node: " << _node -> key_num << ' ' << _node -> key[ 0 ] << ' ' << _node -> key[ 1 ] << endl;
  // cout << "nodd: " << nodd -> key_num << ' ' << nodd -> key[ 0 ] << ' ' << nodd -> key[ 1 ] << endl << endl ;

  printNode(_node);
  printNode(nodd);

  //cout<<"left->father: \n";
  // fatther = (node*)_node->father;
  // printNode(fatther);
  // cout<<"right->father: \n";
  // fatther = (node*)nodd->father;
  // printNode(fatther);
  // cout<<"left: \n";
  // printNode(_node);
  // cout<<"right: \n";
  // printNode(nodd);
    
}

void insert_node( node *node , int key , void *value )
{   
  //char * buffer;
  int x = 0 ;
  while (x < node->key_num && node->key[x]<key) x ++;
  for (int i=node->key_num; i>x; i--)
    node->key[i] = node->key[i-1];
  for (int i=node->key_num+1; i>x+1; i--)
    node->pointer[i] = node->pointer[i-1];
  node->key[ x ] = key ;
  node->pointer[ x + 1 ] = value ;

  cout << "\n*****************************************"<<endl;
  // cout << "length: "<< x+1 <<endl;
  // //buffer = (char *)node->pointer[x+1]; 

  // // printf("%s%s\n","pointer x+1: ",buffer);
  // for(int j=0;j<=x+1;j++){
  //   try {
  //     buffer = (char *)node->pointer[j];
  //     printf("%s%d%s%s\n","pointer: ",j," -> ",buffer);
  //   }catch(const std::exception &exc){
  //     std::cerr << exc.what(); 
  //   }
  // }

  //cout <<"pointer_with_x: "<< x+1 << node->pointer[x+1]<<endl;
  //printf("%s%s\n","pointer_with_x: ",node->pointer[x+1] );
  
  node -> key_num ++ ;
  
  printNode(node);

  //cout << "TYPE: "<< typeid(node->pointer[x+1]).name() << endl;
  if (node->key_num==M) // split
      split( node ) ;

  
}

void delete_node(node *node , int key )
{
    int x = 0 ;
    while ( key != node -> key[ x ] ) x ++ ;
    for ( int i = x ; i < node -> key_num - 1 ; i ++ )
        node -> key[ i ] = node -> key[ i + 1 ] ;
    for ( int i = x + 1 ; i < node -> key_num ; i ++ )
        node -> pointer[ i ] = node -> pointer[ i + 1 ] ;
    node -> key_num -- ;
}
// value ponteiro para void
bool insert_bpt( int key , void *value )
{
    node *leaf = find_leaf( key ) ;
    for (int i=0; i < leaf->key_num; i++ )
        if ( key == leaf->key[ i ] )
            return false ; 
    insert_node( leaf , key , value ) ;
    return true ;
}

bool delete_bpt( int key )
{
  node *leaf = find_leaf( key ) ;
  for ( int i = 0 ; i < leaf -> key_num ; i ++ )
      if ( key == leaf -> key[ i ] )
      {
        delete_node( leaf , key ) ;
        return true ;
      }
  return false ;
}

void showDelete(int key)
{
  if(delete_bpt(key))
    printf("%s%d%s\n","Key with value: ",key," has been deleted!");
  else
    printf("%s\n","Key was not deleted, probably was not found!");
}

void showSearch(int key)
{
  const char * buffer = "Not found!";
  cout<<"Search for value of key with node: "<<key<<endl;
  buffer = query_bpt(key);
  printf("%s\n", buffer);

}

char * query_bpt( int key )
{
    node *leaf = find_leaf( key ) ;
    for ( int i = 0 ; i < leaf -> key_num ; i ++ )
        if ( key == leaf -> key[ i ] )
            return ( char * ) leaf -> pointer[ i + 1 ] ;
    return NULL ;
}

void printNode(node *node)
{ 
  char * buffer;
  //int x = 0 ;
  printf("\n=======================\nNode info:\n");
  printf("%s%d\n","is_leaf: ",node->is_leaf );
  printf("%s%d\n","is_root: ",node->is_root );
  printf("%s%d\n%s\n","key_num: ",node->key_num,"=======================" );
  for(int j=0;j<M;j++){
    try {
      buffer = (char *)node->pointer[j];
      printf("%s%d%s%s\n","pointer: ",j," -> ",buffer);
    }catch(const std::exception &exc){
      std::cerr << exc.what(); 
    }
  }
  cout << "*****************************************\n\n";
  //cout << "TYPE: "<< typeid(node->pointer[4]).name() << endl;
}
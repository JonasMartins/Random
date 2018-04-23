#include <iostream>
#include <string>
#include "ArvoreB.h"
using namespace std;


node *root ;
node * nodd;
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
    splite_count ++ ;
    
    cout << endl << "split!:" << _node->key_num << ' ' << _node->key[ 0 ] << ' ' << _node->key[ 1 ] << ' ' << _node->key[ 2 ] << endl;
    
    nodd = new_node() ;
    int mid_key = _node->key[ M / 2 ] ;

    nodd->key_num = M - M / 2 - 1 ;
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
    
    cout << "midnum: " << mid_key << endl;
    cout << "father: " << (_node->father )<< ' ' << _node->key_num << ' '<< (_node -> father )<< ' ' << _node->key[ 0 ] << endl;
    cout << "node: " << _node->key_num << ' ' << _node -> key[ 0 ] << ' ' << _node -> key[ 1 ] << endl;
    cout << "nodd: " << nodd->key_num << ' ' << nodd -> key[ 0 ] << ' ' << nodd -> key[ 1 ] << endl << endl ;
    
}

void insert_node( node *node , int key , void *value )
{
    int x = 0 ;
    while ( x < node -> key_num && node -> key[ x ] < key ) x ++ ;
    for ( int i = node -> key_num ; i > x ; i -- )
        node -> key[ i ] = node -> key[ i - 1 ] ;
    for ( int i = node -> key_num + 1 ; i > x + 1 ; i -- )
        node -> pointer[ i ] = node -> pointer[ i - 1 ] ;
    node -> key[ x ] = key ;
    node -> pointer[ x + 1 ] = value ;
    node -> key_num ++ ;

    if ( node -> key_num == M ) // split
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

bool insert_bpt( int key , void *value )
{
    node *leaf = find_leaf( key ) ;
    for ( int i = 0 ; i < leaf -> key_num ; i ++ )
        if ( key == leaf -> key[ i ] )
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

char * query_bpt( int key )
{
    node *leaf = find_leaf( key ) ;
    for ( int i = 0 ; i < leaf -> key_num ; i ++ )
        if ( key == leaf -> key[ i ] )
            return ( char * ) leaf -> pointer[ i + 1 ] ;
    return NULL ;
}
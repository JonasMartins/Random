#include <iostream>
#include <string>
#include "bpt.h"
using namespace std;


node *root ;
int node_count ;
int splite_count ;


void start()
{
    root = new_node() ;
    root -> is_root = true ;
    root -> is_leaf = true ;
    node_count = 0 ;
    splite_count = 0 ;
}

node *new_node()
{
    node_count ++ ;

    node *p = new node ;
    p -> is_leaf = false ;
    p -> is_root = false ;
    p -> key_num = 0 ;
    p -> pointer[ 0 ] = NULL ;
    p -> father = NULL ;
    return p ;
}

node *find_leaf( int key )
{
   node *now = root ;
   while ( !now -> is_leaf )
   {
      for ( int i = 0 ; i <= now -> key_num ; i ++ )
        if ( i == now -> key_num || key < now -> key[ i ] )
        {
            now = ( node *) now -> pointer[ i ] ;
            break ;
        }
	}
	return now ;
}

void insert(node *node , int key , void *value );

void split( node *node )
{
    splite_count ++ ;
    
    cout << endl << "split!:" << node -> key_num << ' ' << node -> key[ 0 ] << ' ' << node -> key[ 1 ] << ' ' << node -> key[ 2 ] << endl;
    
    node *nodd = new_node() ;
    int mid_key = node -> key[ M / 2 ] ;

    nodd -> key_num = M - M / 2 - 1 ;
    for ( int i = 0 ; i < nodd -> key_num ; i ++ )
    {
        nodd -> key[ i ] = node -> key[ i + ( M / 2 + 1 ) ] ;
        nodd -> pointer[ i ] = node -> pointer[ i + ( M / 2 + 1 ) ] ;
    }
    nodd -> pointer[ nodd -> key_num ] = node -> pointer[ M ] ;
    node -> key_num = M / 2 ;

    if ( node -> is_leaf )
    {
        node -> key_num ++ ;
        nodd -> pointer[ 0 ] = node -> pointer[ 0 ] ;
        node -> pointer[ 0 ] = nodd ;
        nodd -> is_leaf = true ;
        mid_key = node -> key[ M / 2 + 1 ] ;
    }

    if ( node -> is_root )
    {
        node -> is_root = false ;
        root = new_node() ;
        root -> is_root = true ;
        root -> key[ 0 ] = mid_key ;
        root -> pointer[ 0 ] = node ;
        root -> pointer[ 1 ] = nodd ;
        root -> key_num = 1 ;

        node -> father = nodd -> father = root ;
    } else
    {
        nodd -> father = node -> father ;
        insert_in_node( ( node * ) node -> father , mid_key , ( void *) nodd ) ;
    }
    /*
    cout << "midnum: " << mid_key << endl;
    cout << "father: " << (( node * )node -> father )-> key_num << ' '<< ((node*)node -> father )-> key[ 0 ] << endl;
    cout << "node: " << node -> key_num << ' ' << node -> key[ 0 ] << ' ' << node -> key[ 1 ] << endl;
    cout << "nodd: " << nodd -> key_num << ' ' << nodd -> key[ 0 ] << ' ' << nodd -> key[ 1 ] << endl << endl ;
    */
}
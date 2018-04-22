#ifndef __GP__BPT__
#define __GP__BPT__

#include <iostream>
#include <string>
#include <vector>

const int M = 4 ; // comprimento do no 

struct node
{
    bool is_leaf ;
    bool is_root ;
    int key_num ;
    int key[ M ] ;
    void *pointer[ M + 1 ] ;
    void *father ;
} ;


extern int node_count ;
extern int splite_count ;
extern void start() ;
extern bool insert( int key , void *value ) ;
extern bool delete_in_bpt( int key ) ;
// extern char *query_in_bpt( int key ) ;


#endif
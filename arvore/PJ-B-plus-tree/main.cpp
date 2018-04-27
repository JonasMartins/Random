#include <iostream>
#include <cstdio>
#include <cstring>
#include "bpt.h"

// https://github.com/gugugupan/PJ-B-plus-tree

using namespace std;

int insert_count ;

void usage()
{
    printf( "Usage:\n" ) ;
    printf( "Insert operation: insert [key] [value]\n" ) ;
    printf( "Delete operation: delete [key]\n" ) ;
    printf( "Query  operation: query [key]\n" ) ;
}

int main()
{
    FILE *fp = fopen( "test" , "r" ) ;
    if ( fp == NULL )
    {
        cout << "." << endl;
        return 0 ;
    }

    initial_bpt() ;
    int f_num ;
    char tmp_c[ 10 ] ;
    insert_count = 0 ;

    while ( fscanf( fp , "%d%s" ,&f_num , tmp_c ) != EOF )
    {
        char *f_value = ( char * ) new char[ strlen( tmp_c ) + 1 ] ;
        strcpy( f_value , tmp_c ) ;
        if ( insert_in_bpt( f_num , f_value ) )
        {
            printf( "Insert %d %s OK!\n" , f_num , f_value ) ;
            insert_count ++ ;
        } else
            printf( "Ignore %d %s\n" , f_num , f_value ) ;
    }
    fclose( fp ) ;

    printf( "B plus tree build OK.\n" ) ;
    printf( "node_cout is : %d\n" , node_count ) ;
    printf( "insert_count is : %d\n" , insert_count ) ;
    printf( "splite_count is : %d\n" , splite_count ) ;

    while ( 1 )
    {
        usage() ;
        scanf( "%s" , tmp_c ) ;
        if ( strcmp( tmp_c , "insert" ) == 0 )
        {
            scanf( "%d%s" , &f_num , tmp_c ) ;
            char *f_value = ( char * ) new char[ strlen( tmp_c ) + 1 ] ;
            strcpy( f_value , tmp_c ) ;
            if ( insert_in_bpt( f_num , f_value ) )
            {
                //printf( "Insert %d %s OK!\n" , f_num , f_value ) ;
                insert_count ++ ;
            } else
                //printf( "Ignore %d %s\n" , f_num , f_value ) ;

        } else
        if ( strcmp( tmp_c , "delete" ) == 0 )
        {
            scanf( "%d" , &f_num ) ;
            if ( delete_in_bpt( f_num ) )
                printf( "Delete %d OK!\n" , f_num ) ;
            else
                printf( "can't delete key%d\n" , f_num ) ;
        } else
        if ( strcmp( tmp_c , "query" ) == 0 )
        {
            scanf( "%d" , &f_num ) ;
            char *tmp_c = query_in_bpt( f_num ) ;
            if ( tmp_c == NULL )
                printf( "can't find key%d\n" , f_num ) ;
            else
                printf( "value of key%d is : %s\n" , f_num , tmp_c ) ;
        } else usage() ;
    }

    return 0;
}


// #include <iostream>
// #include <cstdio>
// #include <cstring>
// #include <typeinfo>

// #include "bpt.h"

// using namespace std;

// int insert_count ;

// void menu()
// {
//     printf( "Menu:\n" ) ;
//     printf( "Inserir: insert [key] [value]\n" ) ;
//     printf( "Remover: remove [key]\n" ) ;
//     printf( "Consulta: query [key]\n" ) ;
// }

// // g++ -lstdc++ ArvoreB.cpp -o ArvoreB Main.cpp -o Main.exe
// // g++ ArvoreB.cpp -o ArvoreB Main.cpp -o Main.exe

// // g++ bpt.cpp -o bpt main.cpp -o main.exe

// int main(int argc, char **argv )
// {
//     menu();
//     initial_bpt();
//     char * a = (char*)"__a";
//     char * b = (char*)"__b";
//     char * c = (char*)"__c";
//     //char * d = (char*)"__d";

//     insert_in_bpt(1,a);
//     insert_in_bpt(2,b);
//     insert_in_bpt(3,c);
//     //insert_in_bpt(4,d);
// }


#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

void p_b( bool a )
{
    printf( a ? "True\n" : "False\n" );
}

int exp_log( int a , int b )
{
    if ( b == 0 )
    {
        return 1;
    }
    else if ( b == 1 )
    {
        return a;
    }
    else if ( b % 2 == 1 )
    {
        return exp_log( a , b / 2 ) * exp_log( a , ( b / 2 ) + 1 );
    }
    else
    {
        return exp_log( a , b / 2 )* exp_log( a , b / 2 );
    }
}

int exp_mod( int a , int b , int n )
{
    if ( b == 0 )
    {
        return 1 % n;
    }
    else if ( b == 1 )
    {
        return a % n;
    }
    else if ( b % 2 == 1 )
    {
        int temp = exp_mod( a , ( b - 1 ) / 2 , n );
        return ( ( a % n ) * ( ( temp * temp ) % n ) ) % n;
    }
    else
    {
        int temp =( exp_mod( a , b / 2 , n ) % n ) % n;
        return ( temp * temp ) % n;
    }
}

bool fermat_witness(int n , int a )
{
    return exp_mod( a , n - 1 , n ) == 1;
}

bool fermat_primality_test( int n , int k )
{
    for ( int i = 0 ; i < k ; i++ )
    {
        int u = ( rand() % ( n - 3 ) ) + 2;
        if ( !( fermat_witness( n , u ) ) )
        {
            return false;
        }
    }
    return true;
}

void decompose( int n , int* s , int* d )
{
    *s = 1;
    *d = ( n - 1 ) / 2;
    while ( *d % 2 == 0 )
    {
        (*s)++;
        *d /= 2;
    }
}

bool miller_witness( int n , int a )
{
    int *s = malloc( sizeof( int ) );
    int *d = malloc( sizeof( int ) );
    decompose( n , s , d );
    if ( exp_mod( a , *d , n ) != 1 )
    {
        for ( int r = 0 ; r < *s ; r++ )
        {
            if ( exp_mod( a , *d * exp_log( 2 , r ) , n ) == n - 1 )
            {
                free(s); free(d);
                return false;
            }
        }
        free(s); free(d);
        return true;
    }
    free(s); free(d);
    return false;
}

bool miller_rabin95( int n )
{
    int k = 3; //detaille sur la feuille
    for ( int i = 0 ; i < k ; i++ )
    {
        int a = ( rand() % ( n - 3 ) ) + 2;
        if ( miller_witness( n , a ) )
        {
            return false;
        }
    }
    return true;
}

int main()
{
    srand( time(NULL) );

    int a = 1234565;
    int b = 30000;
    int n = 1234567;
    int e = exp_log( a , b ) % n;
    int r = exp_mod( a , b , n );

    printf( "resultat %d , %d , %d\n" , e , r , 8 % 7);
    p_b( fermat_witness( a , n ) );
    p_b( fermat_primality_test( 13441 , 3 ) );

    int* s = malloc( sizeof( int ) );
    int* d = malloc( sizeof( int ) );

    decompose( 1025 , s , d );

    printf( "s : %d , d : %d\n" , *s , *d );
    p_b( miller_witness( 98 , 8 ) );
    p_b( miller_rabin95(10111) );

    free(s); free(d);
    return 0;
}

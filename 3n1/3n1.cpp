/*
 * =====================================================================================
 *
 *       Filename:  3n1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/24/2011 05:06:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), chenming@sohu-rd.com
 *        Company:  imeresearch@sogou
 *
 * =====================================================================================
 */

#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

const int MAXN = 1000000;
int results[MAXN]; 

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  presolve
 *  Description:  
 * =====================================================================================
 */
    void
presolve (  )
{
    memset(results, -1, MAXN*sizeof(int));
    results[0] = 0;
    results[1] = 1;
    for(int i = 2; i < MAXN; ++i) {
        int steps = 0;
        unsigned int cur = i;
        while ( cur >= MAXN || results[cur] == -1 ) {
            ++steps;
            if ( cur & 0x1 ) {
                cur = 3*cur + 1;
            } else {
                cur >>= 1;
            }
        }
        results[i] = steps + results[cur];
    }
    return ;
}		/* -----  end of function presolve  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    presolve();
    int a, b;
    while ( scanf("%d %d", &a, &b) == 2 ) {
        int from = a > b ? b : a;
        int to = a > b ? a : b;
        int maxlen = 0;
        for(int i = from; i <= to; ++i) {
            if ( results[i] > maxlen ) {
                maxlen = results[i];
            }
        }
        printf("%d %d %d\n", a, b, maxlen);
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

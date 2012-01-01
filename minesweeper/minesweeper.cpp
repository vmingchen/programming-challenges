/*
 * =====================================================================================
 *
 *       Filename:  minesweeper.cpp
 *
 *    Description:  UVa 10189
 *
 *        Version:  1.0
 *        Created:  03/25/2011 12:55:44 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), chenming@sohu-rd.com
 *        Company:  imeresearch@sogou
 *
 * =====================================================================================
 */

#include	<stdio.h>
#include	<stdlib.h>

const int MAXN = 101;

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int i, j, n, m, x, y;
    char field[MAXN][MAXN]; 
    for ( int c=1; scanf("%d %d", &n, &m) == 2 && n != 0; ++c ) {
        for ( i = 0; i < n; ++i ) {
            scanf("%s", field[i]);
        }
        if ( c > 1 ) printf("\n"); 
        printf("Field #%d:\n", c);
        for ( i = 0; i < n; ++i ) {
            for ( j = 0; j < m; ++j ) {
                if ( field[i][j] == '*' ) {
                    printf("*");
                } else {
                    int count = 0;
                    for ( x = max(0, i-1); x <= min(i+1, n-1); ++x ) {
                        for ( y = max(0, j-1); y <= min(j+1, m-1); ++y ) {
                            if ( field[x][y] == '*' ) ++count;
                        }
                    }
                    printf("%d", count);
                }
            }
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

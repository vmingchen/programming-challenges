/*
 * ===========================================================================
 *
 *       Filename:  weryu.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  12/22/2011 10:39:03 AM
 *
 *    Description:  PC/UVa, 110301/10082
 *
 *       Revision:  none
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<stdio.h>

#define N_CHAR 44

char mapping[][N_CHAR+1] = {
    " 1234567890-=WERTYUIOP[]\\SDFGHJKL;'XCVBNM,./", 
    " `1234567890-QWERTYUIOP[]ASDFGHJKL;ZXCVBNM,."};

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int i, c;
    char map[128];

    for (i = 0; i < 128; ++i) map[i] = i;
    for (i = 0; i < N_CHAR; ++i) {
        map[mapping[0][i]] = mapping[1][i];
    }

    while((c = getchar()) != EOF) {
        putchar(map[c]);
    }
    putchar('\n');
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/*
 * ===========================================================================
 *
 *       Filename:  hartal.cpp
 *
 *    Description:  PC/UVa, 110203/10050
 *
 *        Version:  1.0
 *        Created:  07/04/2011 08:30:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), chenming@sohu-rd.com
 *        Company:  imeresearch@sogou
 *
 * ===========================================================================
 */

#include	<stdio.h>
#include	<stdlib.h>

const int MAXP = 101;
/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int T, N, P, parties[MAXP];
    scanf("%d\n", &T);
    for (int i=0; i < T; ++i) {
        scanf("%d\n%d", &N, &P);
        for (int p=0; p < P; ++p) {
            scanf("%d", parties+p);
        }
//        printf("T: %d, N: %d, P: %d\n", T, N, P);
        int count = 0;
        for (int n=1; n <= N; ++n) {
            int remain = n % 7;
            if (remain == 6 || remain == 0) continue;
            for (int p=0; p < P; ++p) {
                if ((n % parties[p]) == 0) { 
                    ++count;
                    break;
                }
            }
        }
        printf("%d\n", count);
    }
    return EXIT_SUCCESS;
}			/* ----------  end of function main  ---------- */

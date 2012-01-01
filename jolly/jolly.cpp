/*
 * ===========================================================================
 *
 *       Filename:  jolly.cpp
 *
 *    Description:  PC/UVa 110201/10038
 *
 *        Version:  1.0
 *        Created:  06/12/2011 10:17:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), chenming@sohu-rd.com
 *        Company:  imeresearch@sogou
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<string.h>
#include	<stdio.h>

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    const int MAXN = 3001;
    int n, pre, cur, diff[MAXN];
    while(scanf("%d", &n) != EOF) {
        bool res = true;
        memset(diff, 0, MAXN*sizeof(int));
        scanf("%d", &pre);
        for(int i=1; i < n; ++i) {
            scanf("%d", &cur);
            if (!res) continue;
            int d = pre > cur ? pre - cur : cur - pre;
            if (d <= 0 || d >= n || diff[d] != 0) {
                res = false;
                continue;
            }
            diff[d] = 1;
            pre = cur;
        }
        if (res) {
            printf("Jolly\n");
        } else {
            printf("Not jolly\n");
        }
    }
    return EXIT_SUCCESS;
}			/* ----------  end of function main  ---------- */

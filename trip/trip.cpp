/*
 * ===========================================================================
 *
 *       Filename:  trip.cpp
 *
 *    Description:  PC/UVa 110103/10137
 *
 *        Version:  1.0
 *        Created:  06/08/2011 10:46:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), chenming@sohu-rd.com
 *        Company:  imeresearch@sogou
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<stdio.h>
#include	<math.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    const static int MAXS = 1000;
    long long nstudent, costs[MAXS];
    while ((scanf("%Ld", &nstudent) != EOF) && nstudent != 0) {
        double l = 0.0;
        long long allcost = 0, average = 0, remains = 0, result = 0;
        for(int i=0; i<nstudent; ++i) {
            scanf("%lf", &l);
            costs[i] = (long long)round(l * 100);
            allcost += costs[i];
        }
        average = allcost/nstudent;
        remains = allcost%nstudent;
        for(int i=0; i<nstudent; ++i) {
            if (costs[i]<=average) continue;
//                result += (costs[i] - average);
            if (remains>0) {
                result += (costs[i] - average - 1); 
                --remains;
            } else {
                result += (costs[i] - average); 
            }
        }
        printf("$%.2lf\n", result/100.0);
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

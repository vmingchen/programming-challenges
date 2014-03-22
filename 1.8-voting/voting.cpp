/*
 * ===========================================================================
 *
 *       Filename:  voting.cpp
 *
 *    Description:  PC/UVa 110108/10142
 *
 *        Version:  1.0
 *        Created:  06/19/2011 04:01:18 PM
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
#include	<string.h>

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{
    const int MAX_VOTE = 1002;
    const int MAX_CAND = 22;
    const int MAX_NAME = 82;
    char names[MAX_CAND][MAX_NAME];
    int votes[MAX_VOTE][MAX_CAND];
    int cursor[MAX_VOTE];
    int counter[MAX_CAND];
    int n = 0, nCand, nVote, vMax, iMax, vMin, iMin, nValidVote, nValidCand;
    bool valid[MAX_CAND];
    char line[200];

    fgets(line, 200, stdin);
    sscanf(line, "%d", &n);
    fgets(line, 200, stdin);
    while ( n > 0 ) { 
        fgets(line, 200, stdin);
        sscanf(line, "%d", &nCand);
        nValidCand = nCand;
        for (int j = 1; j <= nCand; ++j) {
            fgets(names[j], MAX_NAME, stdin);
            counter[j] = 0;
            valid[j] = true;
        }
        nVote = 0;
        while(fgets(line, 200, stdin) != NULL) {
            if (strlen(line) == 1) break;
            ++nVote;
            char *pline = line;
            for (int j=1; j<=nCand; ++j) {
                sscanf(pline, "%d", &votes[nVote][j]);
                pline += (votes[nVote][j] > 10) ? 3 : 2;
            }
        }
        nValidVote = nVote;
        memset(counter, 0, sizeof(counter));
        memset(cursor, 0, sizeof(cursor));

        for (int j = 1; j <= nVote; ++j) {
            cursor[j] = 1;
            ++counter[votes[j][1]];
        }
        while (true) { 
            vMax = 0;
            vMin = nVote;
            for (int i = 1; i <= nCand; ++i) {
                if (!valid[i]) continue;
                int v = counter[i];
                if (v > vMax) {
                    vMax = v;
                    iMax = i;
                }
                if (v < vMin) {
                    vMin = v;
                    iMin = i;
                }
            }
            if (2*vMax > nValidVote || vMin == vMax) break;
            // invalidate candidates
            for (int i = 1; i <= nCand; ++i) {
                if (counter[i] == vMin) {
                    valid[i] = false;
                }
                counter[i] = 0;
            }
            for (int j = 1; j <= nVote; ++j) {
                if (cursor[j] > nCand) continue;    // invalid vote
                while(cursor[j] <= nCand && !valid[votes[j][cursor[j]]]) { 
                    ++cursor[j];
                }
                if ( cursor[j] <= nCand ) { 
                    ++counter[votes[j][cursor[j]]];
                    ++nValidVote;
                } 
            }
        }
        if (2*vMax > nValidVote) {
            printf("%s", names[iMax]);
        } else {
            for (int j = 1; j <= nCand; ++j) {
                if (valid[j] && counter[j] == vMax) {
                    printf("%s", names[j]);
                }
            }
        }

        if (--n > 0) printf("\n");
    }
    
    return EXIT_SUCCESS;
}			/* ----------  end of function main  ---------- */

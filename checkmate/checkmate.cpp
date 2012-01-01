/*
 * ===========================================================================
 *
 *       Filename:  checkmate.cpp
 *
 *    Description:  PC/UVa, 110107/10196
 *
 *        Version:  1.0
 *        Created:  07/02/2011 09:14:24 PM
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

const int N = 8;
char chessboard[N][N+1]; 

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  checkpoint
 *  Description:  
 * ===========================================================================
 */
    bool
checkpoint ( int i, int j, char target )
{
    if (i < 0 || i >= N || j < 0 || j >= N) return false;
    return chessboard[i][j] == target;
}		/* -----  end of function checkpoint  ----- */


/* 
 * ===  FUNCTION  ============================================================
 *         Name:  checkline
 *  Description:  
 * ===========================================================================
 */
    bool
checkline ( int i, int j, int di, int dj, char target )
{
    i += di; 
    j += dj;
    while (i>=0 && i<N && j>=0 && j<N && chessboard[i][j] == '.') {
        i += di;
        j += dj;
    }
    return checkpoint(i, j, target);
}		/* -----  end of function checkline  ----- */

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int result = 0;     // 1 white win, -1 black win
    bool empty = false;
    for(int count=1; !empty; ++count) { 
        result = 0;
        empty = true;
        for(int i=0; i < N; ++i) {
            int c = 0, j = 0;
            while((c=getchar()) != '\n' && c != EOF) { 
                chessboard[i][j++] = c;
                empty = empty && (c == '.');
            }
        }
        if (empty) break;
        getchar();
        for(int i=0; i < N && result == 0; ++i) {
            for (int j=0; j < N && result == 0; ++j) {
                switch(chessboard[i][j]) {
                    case 'p':
                        if (checkpoint(i+1, j-1, 'K') 
                                || checkpoint(i+1, j+1, 'K')) 
                            result = -1;
                        break;
                    case 'n':
                        if (checkpoint(i+1, j+2, 'K') 
                                || checkpoint(i+1, j-2, 'K')
                                || checkpoint(i-1, j+2, 'K') 
                                || checkpoint(i-1, j-2, 'K')
                                || checkpoint(i+2, j+1, 'K') 
                                || checkpoint(i+2, j-1, 'K')
                                || checkpoint(i-2, j+1, 'K') 
                                || checkpoint(i-2, j-1, 'K')) 
                            result = -1;
                        break;
                    case 'b':
                        if (checkline(i, j, 1, 1, 'K') 
                                || checkline(i, j, 1, -1, 'K')
                                || checkline(i, j, -1, 1, 'K')
                                || checkline(i, j, -1, -1, 'K'))
                            result = -1;
                        break;
                    case 'r':
                        if (checkline(i, j, 1, 0, 'K')
                                || checkline(i, j, -1, 0, 'K')
                                || checkline(i, j, 0, 1, 'K')
                                || checkline(i, j, 0, -1, 'K'))
                            result = -1;
                        break;
                    case 'q':
                        if (checkline(i, j, 1, 1, 'K') 
                                || checkline(i, j, 1, -1, 'K')
                                || checkline(i, j, -1, 1, 'K')
                                || checkline(i, j, -1, -1, 'K')
                                || checkline(i, j, 1, 0, 'K')
                                || checkline(i, j, -1, 0, 'K')
                                || checkline(i, j, 0, 1, 'K')
                                || checkline(i, j, 0, -1, 'K'))
                            result = -1;
                        break;
                    case 'P':
                        if (checkpoint(i-1, j-1, 'k') 
                                || checkpoint(i-1, j+1, 'k')) 
                            result = 1;
                        break;
                    case 'N':
                        if (checkpoint(i+1, j+2, 'k') 
                                || checkpoint(i+1, j-2, 'k')
                                || checkpoint(i-1, j+2, 'k') 
                                || checkpoint(i-1, j-2, 'k')
                                || checkpoint(i+2, j+1, 'k') 
                                || checkpoint(i+2, j-1, 'k')
                                || checkpoint(i-2, j+1, 'k') 
                                || checkpoint(i-2, j-1, 'k')) 
                            result = 1;
                        break;
                    case 'B':
                        if (checkline(i, j, 1, 1, 'k') 
                                || checkline(i, j, 1, -1, 'k')
                                || checkline(i, j, -1, 1, 'k')
                                || checkline(i, j, -1, -1, 'k'))
                            result = 1;
                        break;
                    case 'R':
                        if (checkline(i, j, 1, 0, 'k')
                                || checkline(i, j, -1, 0, 'k')
                                || checkline(i, j, 0, 1, 'k')
                                || checkline(i, j, 0, -1, 'k'))
                            result = 1;
                        break;
                    case 'Q':
                        if (checkline(i, j, 1, 1, 'k') 
                                || checkline(i, j, 1, -1, 'k')
                                || checkline(i, j, -1, 1, 'k')
                                || checkline(i, j, -1, -1, 'k')
                                || checkline(i, j, 1, 0, 'k')
                                || checkline(i, j, -1, 0, 'k')
                                || checkline(i, j, 0, 1, 'k')
                                || checkline(i, j, 0, -1, 'k'))
                            result = 1;
                        break;
                }
            }
        }
        if (result == 1) {
            printf("Game #%d: black king is in check.\n", count);
        } else if (result == -1) {
            printf("Game #%d: white king is in check.\n", count);
        } else {
            printf("Game #%d: no king is in check.\n", count);
        }
    }
    return EXIT_SUCCESS;
}			/* ----------  end of function main  ---------- */

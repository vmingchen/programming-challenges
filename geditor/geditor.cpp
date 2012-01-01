/*
 * ===========================================================================
 *
 *       Filename:  geditor.cpp
 *
 *    Description:  PC/UVa
 *
 *        Version:  1.0
 *        Created:  06/11/2011 02:34:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), brianchenming@gmail.com
 *        Company:  imeresearch@sogou
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

const static int MAXS = 1024;
const static int MAXN = 251;

void expand(int x, int y, int M, int N, int oldc, int newc, 
        char canvas[MAXN][MAXN]) {
    canvas[x][y] = newc;
    if (x > 1 && canvas[x-1][y] == oldc) 
        expand(x-1, y, M, N, oldc, newc, canvas);
    if (x < M && canvas[x+1][y] == oldc) 
        expand(x+1, y, M, N, oldc, newc, canvas);
    if (y > 1 && canvas[x][y-1] == oldc)
        expand(x, y-1, M, N, oldc, newc, canvas);
    if (y < N && canvas[x][y+1] == oldc) 
        expand(x, y+1, M, N, oldc, newc, canvas);
}

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    char cmd, color, line[MAXS], canvas[MAXN][MAXN];
    int x1, y1, x2, y2, t, M = 0, N = 0;
    while (fgets(line, MAXS, stdin) != NULL) {
        switch(line[0]) {
            case 'I':
                sscanf(line, "%c %d %d", &cmd, &M, &N);
                memset(canvas, 'O', MAXN*MAXN);
                break;
            case 'C':
                memset(canvas, 'O', MAXN*MAXN);
                break;
            case 'L':
                sscanf(line, "%c %d %d %c", &cmd, &x1, &y1, &color);
                canvas[x1][y1] = color;
                break;
            case 'V':
                sscanf(line, "%c %d %d %d %c", &cmd, &x1, &y1, &y2, &color);
                if (y1 > y2) {
                    t = y1; y1 = y2; y2 = t;
                }
                for (int y=y1; y<=y2; ++y) {
                    canvas[x1][y] = color;
                }
                break;
            case 'H':
                sscanf(line, "%c %d %d %d %c", &cmd, &x1, &x2, &y1, &color);
                if (x1 > x2) {
                    t = x1; x1 = x2; x2 = t;
                }
                for (int x=x1; x<=x2; ++x) {
                    canvas[x][y1] = color;
                }
                break;
            case 'K':
                sscanf(line, "%c %d %d %d %d %c", &cmd, &x1, &y1, 
                        &x2, &y2, &color);
                if (x1 > x2) {
                    t = x1; x1 = x2; x2 = t;
                }
                if (y1 > y2) {
                    t = y1; y1 = y2; y2 = t;
                }
                for (int x = x1; x <= x2; ++x) {
                    for (int y = y1; y <= y2; ++y) {
                        canvas[x][y] = color;
                    }
                }
                break;
            case 'F':
                sscanf(line, "%c %d %d %c", &cmd, &x1, &y1, &color);
                if (color != canvas[x1][y1]) { 
                    expand(x1, y1, M, N, canvas[x1][y1], color, canvas);
                }
                break;
            case 'S':
                printf("%s", line+2);
                for(int y=1; y<=N; ++y) {
                    for(int x=1; x<=M; ++x) {
                        putchar(canvas[x][y]);
                    }
                    printf("\n");
                }
                break;
            case 'X':
                return EXIT_SUCCESS;
            default:
                break;
        }
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

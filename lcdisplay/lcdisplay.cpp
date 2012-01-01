/*
 * ===========================================================================
 *
 *       Filename:  lcdisplay.cpp
 *
 *    Description:  PC/UVa 110104/706
 *
 *        Version:  1.0
 *        Created:  06/10/2011 08:21:45 AM
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

const int WIDTH = (10 + 2 + 1)*8 + 1;
const int HEIGHT = (2*10 + 3 + 1)*8;
char screen[WIDTH][HEIGHT];

void draw(int offset, int size, int pattern) 
{
    int top = 0, middle = size+1, bottom = 2*size+2;
    int left = offset, right = offset+size+1;
    if (pattern & 0x01) {
        for (int j = left+1; j < right; ++j) {
            screen[top][j] = '-';
        }
    }
    if (pattern & 0x02) {
        for (int i = top+1; i < middle; ++i) {
            screen[i][left] = '|';
        }
    }
    if (pattern & 0x04) {
        for (int i = top+1; i < middle; ++i) {
            screen[i][right] = '|';
        }
    }
    if (pattern & 0x08) {
        for (int j = left+1; j < right; ++j) {
            screen[middle][j] = '-';
        }
    }
    if (pattern & 0x10) {
        for (int i = middle+1; i < bottom; ++i) {
            screen[i][left] = '|';
        }
    }
    if (pattern & 0x20) {
        for (int i = middle+1; i < bottom; ++i) {
            screen[i][right] = '|';
        }
    }
    if (pattern & 0x40) {
        for (int j = left+1; j < right; ++j) {
            screen[bottom][j] = '-';
        }
    }
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
    int s, patterns[10] = {
        0x01 | 0x02 | 0x04 | 0x10 | 0x20 | 0x40,
        0x04 | 0x20,
        0x01 | 0x04 | 0x08 | 0x10 | 0x40,
        0x01 | 0x04 | 0x08 | 0x20 | 0x40,
        0x02 | 0x04 | 0x08 | 0x20,
        0x01 | 0x02 | 0x08 | 0x20 | 0x40,
        0x01 | 0x02 | 0x08 | 0x10 | 0x20 | 0x40,
        0x01 | 0x04 | 0x20,
        0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20 | 0x40,
        0x01 | 0x02 | 0x04 | 0x08 | 0x20 | 0x40
    };
    char n[10];
    while ((scanf("%d %s\n", &s, n) != EOF) && s != 0) {
        int l = strlen(n);
        int h = 2*s + 3;
        int w = (s + 2)*l + l-1;
        memset(screen, ' ', WIDTH*HEIGHT);
        for(int i=0; i<h; ++i) screen[i][w] = '\0';
        for(int i=0; i<l; ++i) {
            draw((s + 3)*i, s, patterns[n[i]-'0']);
        }
        for(int i=0; i<h; ++i) {
            printf("%s\n", screen[i]);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

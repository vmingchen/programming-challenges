/*
 * ===========================================================================
 *
 *       Filename:  elephant.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  12/26/2011 12:40:21 PM
 *
 *    Description:  PC/UVa 111101/10131
 *
 *       Revision:  none
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<stdio.h>

#define MAXN 1001

typedef struct {
    int id, weight, iq;
} Elephant;

typedef struct {
    int value, parent;
} State;

Elephant elephants[MAXN];
State states[MAXN];


/* 
 * ===  FUNCTION  ============================================================
 *         Name:  cmp
 *  Description:  
 * ===========================================================================
 */
    int
cmp ( const void *p1, const void *p2 )
{
    const Elephant *e1 = (const Elephant*)p1;
    const Elephant *e2 = (const Elephant*)p2;
    return (e1->weight == e2->weight) 
        ? (e1->iq < e2->iq ? -1 : 1)
        : (e1->weight > e2->weight ? -1 : 1);
}		/* -----  end of function cmp  ----- */

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int n = 0;
    Elephant *p = elephants;

    for (n = 0; scanf("%d %d", &(p->weight), &(p->iq)) != EOF; ++n) {  
        p->id = n+1;
        ++p;
    }

    if (n == 0) { 
        printf("0\n");
        return 0;
    }

    // sort elephants by weight (decreasingly)
    qsort(elephants, n, sizeof(Elephant), cmp);
//    p = elephants;
//    for (int i = 0; i < n; ++i, ++p) {
//        printf("%d\t%d\t%d\n", p->id, p->weight, p->iq);
//    }

    // init statue
    for (int i = 0; i < n; ++i) {
        states[i].parent = -1;
        states[i].value = 1;
    }

    // DP
    int mi = 0, mv = 0;
    for (int i = 0; i < n; ++i) {
        p = elephants + i;
        for (int j = 0; j < i && elephants[j].weight > p->weight; ++j) {
            if (elephants[j].iq < p->iq 
                    && states[j].value + 1 > states[i].value) {
                states[i].value = states[j].value + 1;
                states[i].parent = j;
            }
        }
        if (states[i].value > mv) {
            mi = i;
            mv = states[i].value;
        }
    }

    // reconstruct
    printf("%d\n", mv);
    while (mi >= 0) {
        printf("%d\n", elephants[mi].id);
        mi = states[mi].parent;
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

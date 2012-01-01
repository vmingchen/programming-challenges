/*
 * ===========================================================================
 *
 *       Filename:  wheels.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  11/09/2011 09:37:31 AM
 *
 *    Description:  PC/UVa 110902/10067
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<iostream>
#include	<deque>
#include	<vector>
#include	<set>
#include	<stdlib.h>

const int MAXN = 10000;
const int NEIGHBORS = 8;
const int scales[] = {1, 10, 100, 1000, 10000};

using namespace std;


/* 
 * ===  FUNCTION  ============================================================
 *         Name:  get_edge
 *  Description:  
 * ===========================================================================
 */
    int
get_edge ( int curva, int neighbor )
{

    int pos = neighbor >> 1;
    int dir = neighbor & 1;
    int val = (curva / scales[pos]) % 10;
    
    if (val == 0 && dir == 0) {
        val = 9;
    } else if (val == 9 && dir == 1) {
        val = 0;
    } else {
        val += (dir ? 1 : -1);
    }

    return (curva/scales[pos+1])*scales[pos+1] 
        + val*scales[pos] + curva%scales[pos];
}		/* -----  end of function get_edge  ----- */


/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{
    int n;

//    for (int i = 0; i < NEIGHBORS; ++i) {
//        cout << get_edge(8059, i) << endl;
//    }
//    cout << endl;

    for (cin >> n; n > 0; --n) {
        int src, dst, t[4];
        cin >> t[0] >> t[1] >> t[2] >> t[3];
        src = t[0]*1000 + t[1]*100 + t[2]*10 + t[3];
        cin >> t[0] >> t[1] >> t[2] >> t[3];
        dst = t[0]*1000 + t[1]*100 + t[2]*10 + t[3];

        set<int> forbidden;
        int nf;
        for (cin >> nf; nf > 0; --nf) {
            cin >> t[0] >> t[1] >> t[2] >> t[3];
            forbidden.insert(t[0]*1000 + t[1]*100 + t[2]*10 + t[3]);
        }

        vector<int> distances(MAXN, -1);
        deque<int> bfs;
        bfs.push_back(src);
        distances[src] = 0;
        while (!bfs.empty()) {
            int node = bfs.front();
            if (node == dst) break;
            bfs.pop_front();
            for (int i = 0; i < NEIGHBORS; ++i) {
                int nxt = get_edge(node, i);
                if (forbidden.find(nxt) == forbidden.end() 
                        && distances[nxt] == -1) { 
                    distances[nxt] = distances[node]+1;
                    bfs.push_back(nxt);
                }
            }
        }

        cout << distances[dst] << endl;
    }
    
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/*
 * ===========================================================================
 *
 *       Filename:  bicoloring.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  11/08/2011 10:57:57 PM
 *
 *    Description:  PC/UVA 110901/10004
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<stdio.h>
#include	<vector>
#include	<iostream>
#include	<deque>

const int MAXN = 200;

using namespace std;

enum VertexState { BLACK = 0, WHITE, UNKNOWN };

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int nv, ne;

    while (cin >> nv && nv > 0) {
        vector< vector<bool> > adj_matrix(nv, vector<bool>(nv));
        cin >> ne;
        for (int i = 0; i < ne; ++i) {
            int a, b;
            cin >> a >> b;
            adj_matrix[a][b] = adj_matrix[b][a] = true;
        }
        vector<bool> visited(nv, false);
        bool bicolorable = true;

        for (int i = 0; bicolorable && i < nv; ++i) { 
            // for every node in the forest, bfs from vertex (i)
            if (visited[i]) continue;
            vector<int> states(nv, UNKNOWN);
            deque<int> bfs_queue(nv);
            bfs_queue.push_back(i);
            states[i] = BLACK;
            while (bicolorable && !bfs_queue.empty()) {
                int v = bfs_queue.front();
                visited[v] = true;
                bfs_queue.pop_front();
                for (int j = 0; j < nv; ++j) { 
                    if (!adj_matrix[v][j]) continue;
                    if (states[j] & UNKNOWN) {  // NO COLOR
                        bfs_queue.push_back(j);
                        states[j] = states[v] == BLACK ? WHITE : BLACK;
                    } else if (states[j] == states[v]) {    // SAME COLOR
                        bicolorable = false;
                        break;
                    } 
                }
            }
        }

        cout << (bicolorable ? "" : "NOT ") << "BICOLORABLE." << endl;
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

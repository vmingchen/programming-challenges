/*
 * ===========================================================================
 *
 *       Filename:  unitsp.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  01/03/2012 10:44:55 PM
 *
 *    Description:  PC/UVa 111104/116, DP
 *
 *       Revision:  none
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<iostream>
#include	<vector>
#include	<list>
#include	<bitset>
#include	<map>

using namespace std;

void swap(int &a, int &b) { int t = a; a = b; b = t; } 
void trisort(int &a, int &b, int &c) {
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
}

const int MAXN = 101;

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int m, n;
    while (cin >> m >> n) {
        vector< vector<long long> > matrix(m, vector<long long>(n, 0));
        vector< vector<long long> > dp(m, vector<long long>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> matrix[i][j];
                dp[i][j] = matrix[i][j];
            }
        }

        // DP
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                int a = dp[(i-1+m)%m][j-1];
                int b = dp[i][j-1];
                int c = dp[(i+1)%m][j-1];
                dp[i][j] += (a > b ? (b > c ? c : b) : (a > c ? c : a));
            }
        }

        // find optimal
        int ri = 0, rj = n-1;
        for (int i = 1; i < m; ++i) {
            if (dp[i][rj] < dp[ri][rj]) 
                ri = i;
        }

        // find the left-most smallest row that can lead to an optimal, by BFS
        // and mark all blocks on the way to any optimal result
        int res = dp[ri][rj];
        vector< bitset<MAXN> > reachable(m, bitset<MAXN>());
        for (int i = 0; i < m; ++i) {
            if (dp[i][n-1] == res) {
                reachable[i].set(n-1);
            }
        }
        for (int j = n; j >= 0; --j) {
            for (int i = 0; i < m; ++i) {
                if (reachable[i][j]) {
                    for (int k = -1; k <= 1; ++k) { 
                        if (dp[(i+k+m) % m][j-1] == dp[i][j] - matrix[i][j]) 
                            reachable[(i+k+m)%m].set(j-1);
                    }
                }
            }
        }

        int r = 0;      // smallest row in 1-st column that lead to an optimal
        while (!reachable[r][0]) ++r;

        // find path
        for (int j = 0; j < n-1; ++j) {
            cout << (r+1) << " ";
            int rs[] = {(r-1+m)%m, r, (r+1)%m};
            trisort(rs[0], rs[1], rs[2]);
            for (int k = 0; k <= 2; ++k) { 
                if (reachable[rs[k]][j+1]
                        && dp[rs[k]][j+1] == dp[r][j]+matrix[rs[k]][j+1]) {
                    r = rs[k];
                    break;
                }
            }
        }
        cout << (r+1) << endl;
        cout << res << "\n";
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

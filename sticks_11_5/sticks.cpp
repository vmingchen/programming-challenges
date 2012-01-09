/*
 * ===========================================================================
 *
 *       Filename:  sticks.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  01/05/2012 10:16:48 AM
 *
 *    Description:  PC/UVa, 111105
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<iostream>
#include	<vector>
#include	<stdlib.h>

using namespace std;

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int l, n;
    while (cin >> l && l != 0 ) {
        cin >> n;
        vector<int> places(n+2);
        for (int i = 1; i <= n; ++i) 
            cin >> places[i];
        places[0] = 0;
        places[n+1] = l;
        // dp[i][j] (j > i), best cut from places[i] to places[j]
        vector< vector<int> > dp(n+2, vector<int>(n+2, 0));
        for (int k = 2; k < n+2; ++k) {
            for (int i = 0; i < n+2-k; ++i) {
                int j = i + k;
                int mincut = dp[i][i+1] + dp[i+1][j];
                for (int m = i+1; m < j; ++m) {
                    if (dp[i][m] + dp[m][j] < mincut) {
                        mincut = dp[i][m] + dp[m][j];
                    }
                }
                dp[i][j] = mincut + (places[j] - places[i]);
            }
        }
//        for (int i = 0; i < n+2; ++i) {
//            for (int j = 0; j < n+2; ++j) {
//                cout << ((j > i) ? dp[i][j] : 0) << " ";
//            }
//            cout << endl;
//        }
        cout << "The minimum cutting is " << dp[0][n+1] << ".\n";
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

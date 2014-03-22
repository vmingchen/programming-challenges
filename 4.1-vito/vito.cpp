/*
 * ===========================================================================
 *
 *       Filename:  vito.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  03/05/2013 09:28:33 AM
 *
 *    Description:  PC/UVa 110401/10041
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<vector>
#include	<algorithm>
#include	<iostream>

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
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int len;
		cin >> len;
		vector<int> ss(len);
		for (int j = 0; j < len; ++j) {
			cin >> ss[j];
		}
		nth_element(ss.begin(), ss.begin() + len/2, ss.end());
		int median = ss[len/2];
		int dist = 0;
		for (int j = 0; j < len; ++j) {
			dist += (ss[j] > median) ? (ss[j] - median) : (median - ss[j]);
		}
		cout << dist << endl;
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

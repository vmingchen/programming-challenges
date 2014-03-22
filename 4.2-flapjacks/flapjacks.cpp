/*
 * ===========================================================================
 *
 *       Filename:  flapjacks.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  03/07/2013 11:29:54 PM
 *
 *    Description:  PC/UVa: 110402/120
 *
 *       Revision:  none
 *
 * ===========================================================================
 */


#include	<iostream>
#include	<stdlib.h>
#include	<vector>
#include	<string>
#include	<sstream>
#include	<algorithm>
#include	<assert.h>
#include	<iterator>

using namespace std;

void flip(vector<int> &pancakes, int b, int e) {
	assert(b < e);
	for (; b < e; ++b, --e) {
		int t = pancakes[b];
		pancakes[b] = pancakes[e];
		pancakes[e] = t;
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
	string str;
	while (getline(cin, str)) {
		istringstream iss(str);
		vector<int> pancakes;
		int cake;
		while (iss >> cake) {
			pancakes.push_back(cake);
		}

		copy(pancakes.begin(), pancakes.end(),
				ostream_iterator<int>(cout, " "));
		cout << endl;
		
		unsigned len = pancakes.size();
		unsigned i = pancakes.size();
		for (; i > 1; --i) {
			unsigned maxi = 0;
			int maxv = pancakes[0];
			for (unsigned j = 1; j < i; ++j) {
				if (pancakes[j] > maxv) {
					maxi = j;
					maxv = pancakes[j]; 
				}
			}
			if (maxi == i - 1)
				continue;
			if (maxi != 0) {
				cout << (len - maxi) << " ";
				flip(pancakes, 0, maxi);
			}
			cout << (len - i + 1) << " ";
			flip(pancakes, 0, i-1);
		}
		cout << 0 << endl;
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

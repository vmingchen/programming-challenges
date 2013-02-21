/*
 * ===========================================================================
 *
 *       Filename:  commperm.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  02/21/2013 09:28:59 AM
 *
 *    Description:  PC/UVa: 110303/10252
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<string>
#include	<iostream>
#include	<vector>
#include	<algorithm>

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
	string a, b;
	while (getline(cin, a) && getline(cin, b)) {
		vector<unsigned> a_bin(26, 0);
		vector<unsigned> b_bin(26, 0);
		for (unsigned i = 0; i < a.length(); ++i) {
			a_bin[a[i]-'a'] += 1;
		}
		for (unsigned i = 0; i < b.length(); ++i) {
			b_bin[b[i]-'a'] += 1;
		}
		string res;
		for (unsigned i = 0; i < 26; ++i) {
			unsigned n = min(a_bin[i], b_bin[i]);
			res += string(n, 'a'+i);
		}
		//cout << a << ", " << b << endl;
		cout << res << endl;
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

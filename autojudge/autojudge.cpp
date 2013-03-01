/*
 * ===========================================================================
 *
 *       Filename:  autojudge.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  02/28/2013 09:02:48 PM
 *
 *    Description:  PC/UVa: 110305/10188
 *
 *       Revision:  none
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<string.h>
#include	<vector>
#include	<string>
#include	<iostream>

using namespace std;

enum Result {
	AC = 0,
	PE = 1,
	WA = 2,
};

inline const char *advance(const char *p) {
	while (*p && (*p > '9' || *p < '0'))
		++p;
	return p;
}

int compare_str(const char *p, const char *q) {
	if (strcmp(p, q) == 0)
		return AC;
	p = advance(p);
	q = advance(q);
	while (*p && *q && *p == *q) {
		p = advance(++p);
		q = advance(++q);
	}
	return (*p == 0 && *q == 0) ? PE : WA;
}

int read_lines(string &lines) {
	string s;
	int n;
	if (!getline(cin, s) || (n = atoi(s.c_str())) <= 0) {
		return 0;
	}
	for (int i = 0; i < n; ++i) {
		if (getline(cin, s)) {
			lines.append(s);
			lines.append(",");
		} else {
			return -i;
		}
	}
	return n;
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
	//cout << compare_str("mean", "good") << endl;
	//return 0;
	string s;
	for (int i = 1; ; ++i) {
		string solution, answer;
		int n = read_lines(solution);
		if (n == 0) break;
		read_lines(answer);
		int r = compare_str(solution.c_str(), answer.c_str());
		if (r == AC) {
			cout << "Run #" << i << ": Accepted" << endl;
		} else if (r == PE) {
			cout << "Run #" << i << ": Presentation Error" << endl;
		} else if (r == WA) {
			cout << "Run #" << i << ": Wrong Answer" << endl;
		} else {
			cerr << "Unknown error" << endl;
		}
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

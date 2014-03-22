/*
 * ===========================================================================
 *
 *       Filename:  crypt2.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  02/24/2013 11:57:23 PM
 *
 *    Description:  PC/UVa: 110304/850
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<vector>
#include	<string>
#include	<iostream>
#include	<stdlib.h>

using namespace std;

bool match_key(vector<int> &map, const char *line) {
	static const char *key = "the quick brown fox jumps over the lazy dog";
	const char *p, *q;
	vector<int> tmap(26, -1);
	for (p = key, q = line; *p && *q; ++p, ++q) {
		if (*p == ' ' && *q == ' ')
			continue;
		if (*p == ' ' && *q != ' ')
			break;
		int c = tmap[*q - 'a'];
		if (c != -1 && 'a' + c != *p)
			break;
		if (c == -1)
			tmap[*q - 'a'] = *p - 'a';
	}
	if (! (*p || *q)) {
		copy(tmap.begin(), tmap.end(), map.begin());
		return true;
	}
	return false;
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
	int ncase;
	string line;
	if (getline(cin, line)) {
		ncase = atoi(line.c_str());
		getline(cin, line);	// get rid of the new line
	}

	for (int i = 0; i < ncase; ++i) {
		vector<string> inputs;
		vector<int> map(26, -1);
		int found = 0;
		while (getline(cin, line) && line.length() > 0) {
			inputs.push_back(line);
			if (found == 0 && match_key(map, line.c_str())) {
#ifdef DEBUG
				cout << line << " matched the key" << endl;
#endif
				found = 1;
			}
		}
		if (i > 0) cout << endl;
		if (found == 0) {
			cout << "No solution." << endl;
		} else {
			for (unsigned j = 0; j < inputs.size(); ++j) {
				for (const char *p = inputs[j].c_str(); *p; ++p) {
					cout << (char)((*p == ' ') ? ' ' : ('a' + map[*p - 'a']));
				}
				cout << endl;
			}
		}
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/*
 * ===========================================================================
 *
 *       Filename:  filefrag.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  02/23/2013 09:51:47 AM
 *
 *    Description:  PC/UVa: 110306/10132
 *
 *       Revision:  none
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<iostream>
#include	<vector>
#include	<string>

using namespace std;

bool mismatch(const string &seg, vector<int> &head) {
	for (unsigned i = 0; i < seg.length(); ++i) {
		if ((seg[i] == '0' && head[i] > 0)
				|| (seg[i] == '1' && head[i] < 0))
			return true;
	}
	return false;
}

int val(char c) { return c == '0' ? -1 : 1; }

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

	getline(cin, line);
	ncase = atoi(line.c_str());
	getline(cin, line);

	while (ncase > 0) {
		vector<string> segments;
		vector<int> head(2048, 0);
		vector<int> tail(2048, 0);
		unsigned nchar = 0, nseg = 0;
		while (getline(cin, line) && line.length() > 0) {
			segments.push_back(line);
			unsigned len = line.length();
			for (unsigned i = 0; i < len; ++i) {
				int v = val(line[i]);
				head[i] += v;
				tail[len - i - 1] += v;
			}
			nchar += len;
			nseg++;
		}
		unsigned slen = nchar * 2 / nseg;
		for (unsigned i = 0; i < slen; ++i) {
			head[slen-i-1] += tail[i];
		}
		unsigned nsolved = 0;
		for (unsigned i = 0; i < slen; ++i) {
			if (head[i] != 0) {
				nsolved++;
			}
		}
		for (unsigned i = 0; i < slen && nsolved < slen; ++i) {
			if (mismatch(segments[i], head)) {
				int len = segments[i].length();
				for (unsigned j = 0; j < segments[i].length(); ++j) {
					if (head[slen-1-j] == 0) {
						head[slen-1-j] = val(segments[i][len-1-j]);
						nsolved++;
					}
				}
			}
		}
		if (nsolved > 0) {
			for (unsigned i = 0; i < slen; ++i) 
				cout << (head[i] <= 0 ? '0' : '1');
			cout << endl;
		} else {
			for (unsigned i = 0; i < segments.size(); ++i) {
				if (segments[i] != segments[0]) {
					cout << segments[0] << segments[i] << endl;
					break;
				}
			}
		}
		if (--ncase > 0) cout << endl;
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

/*
 * ===========================================================================
 *
 *       Filename:  waldorf.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  02/20/2013 07:44:12 PM
 *
 *    Description:  PC/UV: 110302/10010
 *
 *       Revision:  none
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<ctype.h>
#include	<vector>
#include	<string>
#include	<iostream>
#include	<algorithm>

using namespace std;

string read_string(istream &cin) {
	string s, r;
	cin >> s;
	for (unsigned i = 0; i < s.length(); ++i)
		r.push_back(tolower(s[i]));
	return r;
}

string get_string(const vector<string> &grid, int x, int y, int dir) {
	const static int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
	const static int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
	int m = grid.size();
	int n = grid[0].length();
	string res;
	while (x >= 0 && x < m && y >= 0 && y < n) {
		res.push_back(grid[x][y]);
		x += dx[dir];
		y += dy[dir];
	}
	return res;
}

int compare(const string &prefix, const string &target) {
	const char *p = prefix.c_str();
	const char *q = target.c_str();
	while (*p && *p == *q) {
		++p;
		++q;
	}
	return *p == 0 ? 0 : (*p - *q);
}

int lookup(const vector<string> &dict, const string &target) {
	// binary search
	unsigned b = 0, e = dict.size(), m = 0;
	while (b < e) {
		m = (b + e) / 2;
		int r = compare(dict[m], target);
		if (r == 0) {
#ifdef DEBUG
			cout << dict[m] << " = " << target << endl;
#endif
			return m;
		} else if (r < 0) {
			b = m + 1;
		} else {
			e = m;
		}
	}
	return -1;
}

void solve(const vector<string> &grid, const vector<string> &dict,
		int m, int n, int k) {
	// sort a copy of the dict so that we don't change the order of words
	vector<string> sdict(dict.begin(), dict.end());
	sort(sdict.begin(), sdict.end());
	vector<unsigned> results(k, 0);
	for (int x = 0; x < m; ++x) {
		for (int y = 0; y < n; ++y) {
			for (int d = 0; d < 8; ++d) {
				string target = get_string(grid, x, y, d);
				int di = -1;
				while ((di = lookup(sdict, target)) >= 0) {
					vector<string>::iterator it = sdict.begin() + di;
					for (unsigned i = 0; i < dict.size(); ++i) {
						if (*it == dict[i] && results[i] == 0) {
							results[i] = ((x+1) << 8) | (y+1);
						}
					}
					sdict.erase(it);
				}
			}
		}
	}
	for (unsigned i = 0; i < results.size(); ++i) {
		cout << (results[i] >> 8) << " " << (results[i] & 0xFF) << endl;
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
	int ncase;
	cin >> ncase;
	for (int i = 0; i < ncase; ++i) {
		int m, n, k;
		cin >> m >> n;
		string str;
		vector<string> grid(m);
		for (int j = 0; j < m; ++j) {
			grid[j] = read_string(cin);
		}
		cin >> k;
		vector<string> dict(k);
		for (int j = 0; j < k; ++j) {
			dict[j] = read_string(cin);
		}

#ifdef DEBUG
		for (int j = 0; j < m; ++j)
			cout << grid[j] << endl;
		for (int j = 0; j < k; ++j)
			cout << dict[j] << endl;
		cout << get_string(grid, 0, 0, 0) << endl;
#endif

		if (i > 0) cout << endl;
		solve(grid, dict, m, n, k);
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

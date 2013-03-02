/*
 * ===========================================================================
 *
 *       Filename:  doublets.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  03/01/2013 09:18:49 PM
 *
 *    Description:  PC/UVa: 110307/10150
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<iostream>
#include	<vector>
#include	<list>
#include	<string>
#include	<stdlib.h>
#include	<algorithm>

using namespace std;
const int MAXL = 16;

// by default make_heap is a max-heap, (MAXL-dist) convert min to max
inline int make_node(int id, int dist) { return (id | ((MAXL-dist) << 16)); }
inline int get_id(int node) { return node & ((1 << 16) - 1); }
inline int get_dist(int node) { return MAXL - (node >> 16); }

// a should be of the same length as b
int str_distance(const string &a, const string &b) {
	const char *p = a.c_str(), *q = b.c_str();
	int d = 0;
	while (*p) {
		d += (*p++ != *q++);
	}
	return d;
}

bool solve(const vector<list<int> > &adj, int src, int dst,
		vector<int> &path) {
	vector<bool> visited(adj.size(), false);
	vector<unsigned char> dists(adj.size(), -1);	// distances to dest
	dists[dst] = 0;
	vector<int> heap(1, make_node(dst, 0));
	while (! heap.empty()) {
		int unode = heap.front();
		pop_heap(heap.begin(), heap.end());
		heap.pop_back();
		int uid = get_id(unode);
		int ump = get_dist(unode);
		if (! visited[uid]) {
			for (list<int>::const_iterator it = adj[uid].begin(); 
					it != adj[uid].end(); ++it) {
				int vid = *it;
				if (ump + 1 < dists[vid]) {
					dists[vid] = ump + 1;
					heap.push_back(make_node(vid, ump+1));
					push_heap(heap.begin(), heap.end());
				}
			}
			visited[uid] = true;
		}
	}
	unsigned mpath = dists[src];
	if (mpath != (unsigned char)(-1)) {
		// rebuild path
		int id = src;
		path.push_back(id);
		while (id != dst) {
			for (list<int>::const_iterator it = adj[id].begin(); 
					it != adj[id].end(); ++it) {
				int nid = *it;
				if (dists[nid] == mpath-1) {
					id = nid;
					path.push_back(nid);
					--mpath;
					break;
				}
			}
		}
		return true;
	}
	return false;
}

// l: length of words in dict
void build_adj(int l, const vector<string> &dict, vector<list<int> > &adj) {
	for (unsigned i = 0; i < dict.size(); ++i) {
		for (unsigned j = i + 1; j < dict.size(); ++j) {
			if (str_distance(dict[i], dict[j]) == 1) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
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
	vector< vector<string> > dicts(16 + 1);
	string str;
	while (getline(cin, str) && str.length() > 0) {
		dicts[str.length()].push_back(str);
	}
	vector< vector<list<int> > > adjlists(16 + 1);
	for (int i = 1; i <= 16; ++i) {
		vector<string> &dict = dicts[i];
		if (dict.size() <= 1)
			continue;
		// sort and de-dup
		sort(dict.begin(), dict.end());
		vector<string>::iterator it = unique(dict.begin(), dict.end());
		dict.resize(std::distance(dict.begin(), it));
		// build adajacent list
		adjlists[i] = vector<list<int> >(dict.size());
		build_adj(i, dict, adjlists[i]);
#ifdef DEBUG
		cout << "================ " << i << endl;
		for (unsigned j = 0; j < dict.size(); ++j) {
			list<int> &db = adjlists[i][j];
			cout << dict[j] << ":";
			for (list<int>::iterator it = db.begin();
					it != db.end(); ++it) {
				cout << " " << dict[*it];
			}
			cout << endl;
		}
#endif
	}

	string a, b;
	for (int n = 0; cin >> a >> b; ++n) {
		unsigned len = a.length();
		vector<string> &dict = dicts[len];
		vector<string>::iterator beg = dict.begin();
		vector<string>::iterator end = dict.end();
		if (n > 0) cout << endl;
		if (a.length() != b.length() 
				|| ! binary_search(beg, end, a)
				|| ! binary_search(beg, end, b)) {
			cout << "No solution." << endl;
		} else {
			vector<int> path;
			int i = std::distance(beg, lower_bound(beg, end, a));
			int j = std::distance(beg, lower_bound(beg, end, b));
			if (solve(adjlists[len], i, j, path)) {
				for (unsigned i = 0; i < path.size(); ++i)
					cout << dict[path[i]] << endl;
			} else {
				cout << "No solution." << endl;
			}
		}
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

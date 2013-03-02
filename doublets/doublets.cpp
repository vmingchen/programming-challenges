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

//inline int make_node(int id, int dist) { return (id | (dist << 16)); }
//inline int get_id(int node) { return node & ((1 << 16) - 1); }
//inline int get_dist(int node) { return node >> 16; }

// a should be of the same length as b
int str_distance(const string &a, const string &b) {
	const char *p = a.c_str(), *q = b.c_str();
	int d = 0;
	while (*p) {
		d += (*p++ != *q++);
	}
	return d;
}

bool solve(vector<vector<int> > &adj, int src, int dst,
		vector<int> &path) {
	vector<bool> visited(adj.size(), false);
	vector<unsigned char> dists(adj.size(), -1);	// distances to dest
	dists[dst] = 0;
	vector<int> heap(1, src);
	while (! heap.empty()) {
		int uid = heap.front();
		//int unode = heap.front();
		//int ump = get_dist(node);
		//int uid = get_id(node);
		if (visited[uid]) continue;
		for (unsigned i = 0; i < adj[uid].size(); ++i) {
			int vid = adj[uid][i];
			//int vmp = get_dist(vnode);
			//int vid = get_id(vnode);
			if (ump + 1 < dists[vid]) {
				//dists[vid] = ump + vmp;
				//heap.push_back(make_node(vid, ump + vmp));
				dists[vid] = ump + 1;
				heap.push_heap(vid);
				push_heap(heap.begin(), heap.end());
			}
		}
		pop_heap(heap.begin(), heap.end());
		visited[uid] = true;
	}
	unsigned mpath = dists[src];
	if (mpath != (unsigned char)(-1)) {
		// rebuild path
		int id = src;
		path.push_back(id);
		while (id != dst) {
			for (unsigned i = 0; i < adj[id].size(); ++i) {
				int nid = adj[id][i];
				if (dists[nid] == mpath-1) {
					id = nid;
					path.push_back(nid);
					break;
				}
			}
		}
	}
	return false;
}

unsigned hash(const char *p, int mask_index) {
	unsigned h = 17;
	for (int i = 0; *p; ++i, ++p) {
		if (i != mask_index) {
			h = (h << 4) + (*p - 'a');
		}
	}
	return h;
}

// l: length of words in dict
void build_adj(int l, const vector<string> &dict, vector<vector<int> > &adj) {
	for (unsigned i = 0; i < dict.size(); ++i) {
		vector<int> &db = adj[i];
		for (unsigned j = i + 1; j < dict.size(); ++j) {
			if (str_distance(dict[i], dict[j]) == 1) {
				db.push_back(j);
				//db.push_back(make_node(j, 1));
			}
		}
	}
	//for (int i = 0; i < l; ++i) {
		//// consider all doubles, of which the i-th char is different
		//const unsigned H = (1 << 15);
		//vector<list<int> > hashmap(H);
		//// build hashes for all words when the i-th char is masked
		//for (unsigned j = 0; j < dict.size(); ++j) {
			//unsigned h = hash(dict[j].c_str(), i) & (H - 1);
			//hashmap[h].push_back(j);
		//}
		//vector<list<int> >::iterator it = hashmap.begin();
		//for (; it != hashmap.end(); ++it) {
			//if (it->size() < 2)
				//continue;
			//list<int> &cand = *it;		// doublets candidates
			//// match all candidates, which have the same hash
			//for (list<int>::iterator lit = cand.begin(); 
					//lit != cand.end(); ++lit) {
				//int j = *lit;
				//list<int>::iterator nit = lit;
				//for (++nit; nit != cand.end(); ++nit) {
					//int k = *nit;
					//if (str_distance(dict[j], dict[k]) == 1) {
						//adj[j].push_back(k);
						//adj[k].push_back(j);
					//}
				//}
			//}
		//}
	//}
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
	while (cin >> str && str.length() > 0) {
		dicts[str.length()].push_back(str);
	}
	vector< vector<vector<int> > > adjlists(16 + 1);
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
	while (cin >> a >> b) {
		unsigned len = a.length();
		vector<string> &dict = dicts[len];
		vector<string>::iterator beg = dict.begin();
		vector<string>::iterator end = dict.end();
		if (a.length() != b.length() 
				|| ! binary_search(beg, end(), a)
				|| ! binary_search(beg, end(), b)) {
			cout << "No solution." << endl;
		} else {
			vector<int> path;
			int i = std::distance(beg, lower_bound(beg, end, a));
			int j = std::distance(beg, lower_bound(beg, end, b));
			solve(adjlists[len], i, j, path);
			for (unsigned i = 0; i < path.size(); ++i)
				cout << dict[path[i]] << endl;
		} else {
			cout << "No solution." << endl;
		}
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

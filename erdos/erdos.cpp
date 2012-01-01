/*
 * ===========================================================================
 *
 *       Filename:  erdos.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  09/11/2011 03:51:30 PM
 *
 *    Description:  PC/UVa 110206, Erdos Number
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<ctype.h>
#include	<iostream>
#include	<vector>
#include	<string>
#include	<deque>
#include	<list>
#include	<map>
#include	<set>

using namespace std;
typedef list<int>::iterator lit;
string Erdos = "Erdos, P.";


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  trim
 *  Description:  
 * =====================================================================================
 */
    string
trim ( const string& str )
{
    int b = 0, e = str.length()-1;
    while (isspace(str[b]) && b <= e) ++b;
    while (isspace(str[e]) && e >= b) --e;
    return str.substr(b, e-b+1);
}		/* -----  end of function trim  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  split
 *  Description:  
 * =====================================================================================
 */
    vector<string>
split ( const string& str, int delim )
{
    vector<string> pieces;
    string::size_type offset = 0;
    string::size_type idx = 0;
    while ((idx = str.find(delim, offset)) != string::npos) {
        pieces.push_back(trim(str.substr(offset, idx-offset)));
        offset = idx + 1;
    }
    pieces.push_back(trim(str.substr(offset)));
    return pieces;
}		/* -----  end of function split  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int S = 0;
    cin >> S;
    for (int i=1; i<=S; ++i) {
//    for (int i=1; ; ++i) { 
        int P, N;
        cin >> P >> N;
//        if ( P == 0 ) break;
        string line;
        getline(cin, line);
        map<string, int> names;
        names[Erdos] = 0;
        vector< set<int> > relations(1);
        for (int j=0; j<P; ++j) {
            getline(cin, line);
            list<int> authors;
            vector<string> tokens = split(line.substr(0, line.find(':')), ',');
            for (size_t i=0; i < tokens.size()/2; ++i) {
                string author = tokens[2*i] + ", " + tokens[2*i+1];
                if (names.find(author) == names.end()) {
                    names[author] = relations.size();
                    relations.push_back(set<int>());
                }
                int iauthor = names[author];
                for (lit it = authors.begin(); it != authors.end(); ++it) {
                    relations[iauthor].insert(*it);
                    relations[*it].insert(iauthor);
                }
                authors.push_back(iauthor);
            }
        }
//        for (size_t j=0; j<relations.size(); ++j) {
//            cout << j;
//            for (set<int>::iterator it = relations[j].begin(); 
//                    it != relations[j].end(); ++it) {
//            }
//            cout << endl;
//        }
//
        vector<string> interest_authors(N);
//        set<int> author_ids();
        for (int j=0; j<N; ++j) {
            getline(cin, line);
            interest_authors[j] = trim(line);
//            author_ids.insert(names[line]);
        }

        vector<int> distances((names.size() > N ? names.size() : N), P+1);
        deque<int> opened;
        opened.push_back(0);
        distances[0] = 0;
        while (!opened.empty()) {
            int visit = opened[0];
            int ndist = distances[visit] + 1;
            for (set<int>::iterator it = relations[visit].begin(); 
                    it != relations[visit].end(); ++it) {
                if (ndist < distances[*it]) {
                    distances[*it] = ndist;
                    opened.push_back(*it);
                }
            }
            opened.pop_front();
        }

        cout << "Scenario " << i << endl;
//        cout << "Database #" << i << endl;
        for (int j=0; j<N; ++j) {
            cout << interest_authors[j] << " ";
            if (names.find(interest_authors[j]) == names.end()) {
                cout << "infinity" << endl;
                continue;
            }
            int iauthor = names[interest_authors[j]];
            if (distances[iauthor] == P+1) {
                cout << "infinity" << endl;
            } else {
                cout << distances[iauthor] << endl;
            }
        }
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

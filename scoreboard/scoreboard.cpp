/*
 * ===========================================================================
 *
 *       Filename:  scoreboard.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  09/14/2011 08:34:24 AM
 *
 *    Description:  UVA/PC 10258/110207, Contest Scoreboard 
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<iostream>
#include	<stdlib.h>
#include	<algorithm>
#include	<sstream>
#include	<vector>
#include	<string.h>

using namespace std;

const int NUM_PROBLEM = 9;
const int NUM_CONTESTANT = 100;
const int PENALTY = 20;

class Constentant {
public:
    int number;     // constentant number
    int scored;     // how many problem solved
    int penalty;
    int status;     
    int icounts[NUM_PROBLEM+1];
    Constentant() : scored(0), penalty(0), status(0) {
        memset(icounts, 0, sizeof(int)*(NUM_PROBLEM+1));
    };
    void record(int iProblem, int time, int L) {
        if ((status >> iProblem) & 0x01) return ;
        status |= 0x01;     // mark for participating constentant
        if (L == 'C') {
            scored += 1;
            penalty += (time + PENALTY*icounts[iProblem]);
            status |= (0x01 << iProblem);
        } 
        if (L == 'I') {
            ++icounts[iProblem];
        }
    };
    bool participated() const { return status & 0x01; }
};

bool operator<(const Constentant& a, const Constentant& b) {
    if (a.participated() != b.participated()) return a.participated();
    if (a.scored != b.scored) return a.scored > b.scored;
    if (a.penalty != b.penalty) return a.penalty < b.penalty;
    return a.number < b.number;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int nCase = 0;
    cin >> nCase;
    string line;
    getline(cin, line);
    getline(cin, line);
    for(int i=0; i < nCase; ++i) {
        vector< Constentant > board(NUM_CONTESTANT+1);
        int maxIConstentant = 0;
        while(getline(cin, line) && line.length()>1) {
            int nc, np, time;
            char L;
            istringstream iss(line);
            iss >> nc >> np >> time >> L;
            board[nc].record(np, time, L);
            maxIConstentant = (nc > maxIConstentant) ? nc : maxIConstentant;
        }
        for (int j=1; j <= maxIConstentant; ++j) {
            board[j].number = j;
        }
        sort(board.begin()+1, board.begin()+1+maxIConstentant);
        if (i != 0) cout << endl;
        for (int j=1; j <= maxIConstentant; ++j) {
            if (!board[j].participated()) break;
            cout << board[j].number << " "
                << board[j].scored << " "
                << board[j].penalty << endl;
        }
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

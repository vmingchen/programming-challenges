/*
 * ===========================================================================
 *
 *       Filename:  stackthemup.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  09/10/2011 09:04:55 PM
 *
 *    Description:  UVA/PC 10205/110205
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<vector>
#include	<sstream>
#include	<string>
#include	<iostream>

using namespace std;

const int MAX_SHUFFLE_NUM = 100;
const int CARD_NUM = 52;
const int NAME_NUM = 13;
const int SUIT_NUM = 4;
const char* NAMES[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", 
    "Jack", "Queen", "King", "Ace"};
const char* SUITS[] = {"Clubs", "Diamonds", "Hearts", "Spades"};

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  outcard
 *  Description:  
 * =====================================================================================
 */
    void
outcard ( int cardno )
{
    int isuit = (cardno-1)/NAME_NUM;
    int iname = (cardno-1)%NAME_NUM;
    cout << NAMES[iname] << " of " << SUITS[isuit] << endl;
}		/* -----  end of function outcard  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  shuffle
 *  Description:  
 * =====================================================================================
 */
    void
shuffle ( int *deck, const vector<int>& op )
{
    char newdeck[CARD_NUM+1];
    for(int j=1; j<=CARD_NUM; ++j) {
        newdeck[j] = deck[op[j]];
    }
    for(int j=1; j<=CARD_NUM; ++j) {
        deck[j] = newdeck[j];
    }
}		/* -----  end of function shuffle  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int ntestcase = 0;
    cin >> ntestcase;

    for (int i=0; i < ntestcase; ++i) {
        if (i > 0) cout << endl;
        int nshuffle;
        cin >> nshuffle;
        vector< vector<int> > operators(nshuffle, vector<int>(CARD_NUM+1));
        for (int j=0; j < nshuffle; ++j) {
            for (int l=1; l <= CARD_NUM; ++l) 
                cin >> operators[j][l];
        }
        int deck[CARD_NUM+1];
        for (int i=1; i<=CARD_NUM; ++i) 
            deck[i] = i;

        string line;
        getline(cin, line);
        while (getline(cin, line)) {
            if (line.length() == 0) break;
            istringstream iss(line);
            int k = 0;
            if (iss >> k) {
//                cout << "k = " << k << endl;
                shuffle(deck, operators[k-1]);
            }
        }
        for (int j=1; j<=CARD_NUM; ++j) {
            outcard(deck[j]);
        }
    }


    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

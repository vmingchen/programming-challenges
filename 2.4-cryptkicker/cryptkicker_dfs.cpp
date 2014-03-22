/*
 * ============================================================================
 *       Filename:  cryptkicker.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/2011 06:02:16 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), chenming@sohu-rd.com
 *        Company:  imeresearch@sogou
 *
 * ============================================================================
 */

#include	<stdlib.h>
#include	<assert.h>
#include	<iostream>
#include	<string>
#include	<iterator>
#include	<sstream>
#include	<vector>
#include	<list>

using namespace std;

const size_t ABSIZE = 26;
const size_t MAX_WORD_LEN = 16;
vector< list<string> > dictionary(MAX_WORD_LEN, list<string>());
typedef vector<string>::iterator vit;
typedef list<string>::iterator lit;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cmap
 *  Description:  
 * =====================================================================================
 */
    bool
cmap (vector<char>& table, const string& enc, 
        const string& dec, unsigned &changes)
{
    assert(dec.length() == enc.length());
    for (size_t i=0; i < enc.length(); ++i) {
        if (table[enc[i]-'a'] != 0 && table[enc[i]-'a'] != dec[i]) 
            return false;
        if (table[enc[i]-'a'] == 0) { 
            changes |= (0x1 << (enc[i]-'a'));
            table[enc[i]-'a'] = dec[i];
        }
    }
    return true;
}		/* -----  end of function cmap  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  uncmap
 *  Description:  
 * =====================================================================================
 */
    void
uncmap ( vector<char>& table, unsigned changes )
{
    for (size_t i=0; i < ABSIZE; ++i) {
        if ((changes >> i) & 0x01) 
            table[i] = 0;
    }
}		/* -----  end of function uncmap  ----- */

/* 
 * ===  FUNCTION  =============================================================
 *         Name:  decrypt
 *  Description:  
 * ============================================================================
 */
    bool 
decrypt ( size_t ie, const vector<string>& encs, vector<char>& table )
{
    if (ie == encs.size()) return true;
    lit beg = dictionary[encs[ie].length()-1].begin();
    lit end = dictionary[encs[ie].length()-1].end();
    for (lit dit = beg; dit != end; ++dit) { 
        unsigned changes = 0;
        if (cmap(table, encs[ie], *dit, changes)) {
            if (decrypt(ie+1, encs, table)) return true;
        }
        uncmap(table, changes);
    }

    return false;
}		/* -----  end of function decrypt  ----- */

/* 
 * ===  FUNCTION  =============================================================
 *         Name:  main
 *  Description:  
 * ============================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int n;
    string word;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> word;
        dictionary[word.length()-1].push_front(word);
    }

    string line;
    while (getline(cin, line)) {
        if (line.length() <= 1) continue;
        istringstream iss(line);
        std::vector<string> enc_words;
        while (iss >> word) {
            enc_words.push_back(word);
        }
        std::vector<char> codebook(ABSIZE, 0);
        bool res = decrypt(0, enc_words, codebook); 
        if (!res) {
            for (size_t i = 0; i < ABSIZE; ++i) {
                codebook[i] = '*';
            }
        }
        for(vit it = enc_words.begin(); it != enc_words.end(); ++it) {
            for(size_t i=0; i<it->length(); ++i) {
                cout << codebook[(*it)[i] - 'a'];
            }
            cout << ' ';
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

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
#include	<string.h>
#include	<iostream>
#include	<string>
#include	<iterator>
#include	<sstream>
#include	<vector>
#include	<list>
#include	<set>

using namespace std;

const size_t PRIME = 1117;
const size_t ABSIZE = 26;
const size_t MAX_WORD_LEN = 16;
vector< list<string> > dictionary(PRIME, list<string>());
typedef vector<string>::iterator vit;
typedef set<string>::iterator sit;
typedef list<string>::iterator lit;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cmap
 *  Description:  
 * =====================================================================================
 */
    bool
cmap (vector<char>& codebook, unsigned& occupied, const string& enc, 
        const string& dec, unsigned &changes)
{
    for (size_t i=0; i < enc.length(); ++i) {
        if (codebook[enc[i]-'a'] != 0) {
            if (codebook[enc[i]-'a'] != dec[i]) return false;
        } else {
            if (occupied & (0x01 << (dec[i]-'a'))) return false;
            changes |= (0x1 << (enc[i]-'a'));
            occupied |= (0x1 << (dec[i]-'a'));
            codebook[enc[i]-'a'] = dec[i];
       }
    }
    return true;
}		/* -----  end of function cmap  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  hashcode
 *  Description:  
 * =====================================================================================
 */
    size_t
hashcode ( const string& str )
{
    size_t m = 0;
    char occurences[ABSIZE+1] = "00000000000000000000000000";
    for(size_t i=0; i<str.length(); ++i) {
        if (occurences[str[i]-'a'] == '0') {
            occurences[str[i]-'a'] = i+1;
        }
        m += occurences[str[i]-'a'];
        m <<= 4;
        m %= PRIME;
    }
    return m;
}		/* -----  end of function hashcode  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  uncmap
 *  Description:  
 * =====================================================================================
 */
    void
uncmap ( vector<char>& codebook, unsigned &occupied, unsigned changes )
{
    for (size_t i=0; i < ABSIZE; ++i) {
        if ((changes >> i) & 0x01) { 
            occupied ^= (0x1 << (codebook[i]-'a'));
            codebook[i] = 0;
        }
    }
}		/* -----  end of function uncmap  ----- */

/* 
 * ===  FUNCTION  =============================================================
 *         Name:  decrypt
 *  Description:  
 * ============================================================================
 */
    bool 
decrypt (size_t ie, const vector<string>& encs, 
        vector<char>& codebook, unsigned &occupied)
{
    if (ie == encs.size()) return true;
    size_t hc = hashcode(encs[ie]);
    lit beg = dictionary[hc].begin();
    lit end = dictionary[hc].end();
    for (lit dit = beg; dit != end; ++dit) { 
        if (dit->length() != encs[ie].length()) continue;
        unsigned changes = 0;
        if (cmap(codebook, occupied, encs[ie], *dit, changes)) {
            if (decrypt(ie+1, encs, codebook, occupied)) 
                return true;
        }
        uncmap(codebook, occupied, changes);
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
        size_t hc = hashcode(word);
        dictionary[hc].push_back(word);
    }

    string line;
    getline(cin, line);
    while (getline(cin, line)) {
        istringstream iss(line);
        if (line.length() <= 1) {
            cout << endl;
            continue;
        }
        std::set<string> words;
        while (iss >> word) {
            words.insert(word);
        }
        std::vector<string> enc_words(words.begin(), words.end());
        std::vector<char> codebook(ABSIZE, 0);
        unsigned occupied = 0;
        bool res = decrypt(0, enc_words, codebook, occupied); 
        if (!res) {
            for (size_t i = 0; i < ABSIZE; ++i) {
                codebook[i] = '*';
            }
        }
        for(size_t i=0; i<line.length(); ++i) {
            if (line[i] == ' ') {
                cout << ' ';
            } else {
                cout << codebook[line[i] - 'a'];
            }
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

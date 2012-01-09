/*
 * ===========================================================================
 *
 *       Filename:  ferry.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  01/05/2012 11:55:32 PM
 *
 *    Description:  PC/UVa, 111106/10261
 *
 *       Revision:  none
 *
 * ===========================================================================
 */


#include	<stdlib.h>
#include	<iostream>
#include	<vector>
#include	<bitset>
#include	<algorithm>
#include	<string.h>
#include	<set>

const int MAXL = 10000;
const int MAXLSR = 100;
const int MAXC = 200;

using namespace std;

class bitmap {
public:
    bitmap(int s) : size(s) {
        int msz = (size + 8 - 1)/8;
        data = new unsigned char[msz];
        clear();
    };
    ~bitmap() {
        delete[] data;
    }
    bool operator[](const int& i) { return 0x1 & (data[i>>3] >> (i & 7)); }
    void set(int i) { data[i>>3] |= (0x1 << (i & 7)); }
    void reset(int i) { data[i>>3] ^= (0x1 << (i & 7)); }
    void clear() { memset(data, 0, (size+8-1)/8); }
private:
    unsigned char *data;
    int size;
};

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    int n;
    for (cin >> n; n > 0; --n) {
        int len;
        cin >> len;
        len *= 100;

        int dp[MAXC+1][MAXL+1];
        int sum[MAXC+1];
        memset(dp, 0, sizeof(int)*(MAXC+1)*(MAXL+1));
        memset(sum, 0, sizeof(int)*(MAXC+1));
        int carlen, ncar;
        for (ncar = 0; cin >> carlen && carlen != 0; ++ncar)
            if (ncar < MAXC) sum[ncar+1] = sum[ncar] + carlen;
        int m;
        dp[0][0] = 1;
        for (m = 1; m <= ncar && m <= MAXC; ++m) {
            bool full = true;
            carlen = sum[m] - sum[m-1];
            for (int i = max(sum[m-1]-len, 0); i <= min(sum[m], len-carlen); ++i) {
                if (dp[m-1][i]) { 
                    dp[m][i+carlen] = 1;
                    full = false;
                }
            }
            for (int i = max(sum[m]-len, 0); i <= min(sum[m], len); ++i) {
                if (dp[m-1][i]) {
                    dp[m][i] = 1;
                    full = false;
                }
            }
            
            if (full) 
                break;
        }
        cout << m-1 << endl;
        int portlen = 0;
        for (portlen = 0; portlen <= len && dp[m-1][portlen] == 0; ++portlen)
            ;
        cout << portlen << endl;
        vector<bool> path(m);
        for (int i = m-1; i > 0; --i) {
            if (portlen >= (sum[i]-sum[i-1]) 
                    && dp[i-1][portlen - (sum[i] - sum[i-1])]) {
                portlen -= (sum[i] - sum[i-1]);
                path[i] = true;
            } else {
                path[i] = false;
            }
        }
        for (int i = 1; i < m; ++i) {
            cout << (path[i] ? "port" : "starboard") << endl;
        }
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

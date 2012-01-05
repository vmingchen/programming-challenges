/*
 * ===========================================================================
 *
 *       Filename:  distinct.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  01/02/2012 01:00:07 PM
 *
 *    Description:  PC/UVa 111102/10069
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<string>
#include	<string.h>
#include	<iostream>
#include	<vector>

#define MAXL 101

using namespace std;

class Num {
public:
    Num(int i) { 
        memset(val, 0, MAXL);
        width = 0;
        while (i > 0) {
            val[width++] = i % 10; 
            i /= 10;
        }
    };
    Num& operator+=(const Num& other) {
        int carry = 0;
        for(int i = 0; i < width || i < other.width; ++i) {
            int t = carry + val[i] + other.val[i];
            carry = t >= 10;
            val[i] = t >= 10 ? t - 10 : t;
        }
        if (other.width > width) width = other.width;
        if (carry > 0) val[width++] = carry;
        return *this;
    };
    char val[MAXL];
    int width;
};

ostream& operator<<(ostream& out, const Num& num) {
    for (int i = num.width-1; i >= 0; --i) 
        out << (int)num.val[i];
    return out;
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
    int n;
    cin >> n;
    while (n-- > 0) {
        string sa, sb;
        cin >> sa >> sb;
        vector< vector<Num> > dp(sa.length()+1, 
                vector<Num>(sb.length()+1, Num(0)));
        for (size_t i = 0; i <= sa.length(); ++i) { 
            dp[i][0] = Num(1);
        }
        for (size_t i = 1; i <= sa.length(); ++i) {
            for (size_t j = 1; j <= sb.length(); ++j) {
                dp[i][j] += dp[i-1][j];
                if (sa[i-1] == sb[j-1]) {
                    dp[i][j] += dp[i-1][j-1];
                }
            }
        }
        cout << dp[sa.length()][sb.length()] << endl;
    }
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

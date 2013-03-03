/*
 * ===========================================================================
 *
 *       Filename:  fmt.cpp
 *         Author:  Ming Chen, brianchenming@gmail.com
 *        Created:  03/03/2013 12:29:54 AM
 *
 *    Description:  PC/UVa: 110308/848
 *
 *       Revision:  none
 *
 * ===========================================================================
 */

#include	<iostream>
#include	<string>
#include	<iostream>
#include	<stdlib.h>
#include	<ctype.h>
#include	<stdio.h>

using namespace std;

bool isblackline(const string &str) {
	for (const char *p = str.c_str(); *p; ++p) {
		if (!isblank(*p))
			return false;
	}
	return true;
}

inline const char *head(const string &s) { return s.c_str(); }
inline const char *tail(const string &s) { return s.c_str() + s.length() - 1; }

inline bool canbreak(char c) { return c == 0 || isblank(c); }

string rtrim(const string &str) {
	const char *beg = head(str);
	const char *end = tail(str);
	while (beg <= end && isblank(*end))
		--end;
	return beg <= end ? string(beg, end+1) : "";
}

string trim(const char *beg, const char *end) {
	while (beg <= end && isblank(*beg))
		++beg;
	while (beg <= end && isblank(*end))
		--end;
	return beg <= end ? string(beg, end+1) : "";
}

void putline(const char *beg, const char *end) {
	for (; beg <= end; ++beg)
		putchar(*beg);
	putchar('\n');
}

void breakline(string &buffer) {
	while (buffer.length() > 72) {
		const char *p = buffer.c_str() + 72 - 1;
		if (!isblank(*p) && canbreak(*(p+1))) {
			// p is at the right boundary of a word
			putline(head(buffer), p);
			buffer = trim(p+1, tail(buffer));
			continue;
		}
		int i = 72;
		// find a blank
		for (; i > 0 && !isblank(*p); --i, --p)
			;
		if (i <= 0) { // no blank found
			for (p = buffer.c_str() + 72; *p && !isblank(*p); ++p)
				;
			putline(buffer.c_str(), p-1);
			buffer = trim(p, tail(buffer));
			continue;
		}
		// find the end of line of the formated string
		for (; i > 0 && isblank(*p); --i, --p)
			;
		if (i <= 0) { // all preceeding chars are blank
			putchar('\n');
			for (p = head(buffer) + 72; !isblank(*p); --p)
				;
			buffer = trim(p+1, tail(buffer));
			continue;
		}

		// now p is the end of a new line, print it
		putline(buffer.c_str(), p);

		buffer = trim(p+1, tail(buffer));
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
	string buffer;
	string line;
	while (getline(cin, line)) {
		if (isblackline(line)) {
			if (! isblackline(buffer))
				cout << rtrim(buffer) << endl;
			buffer = "";
			putchar('\n');
			continue;
		}
		if (isblank(line[0])) {
			if (! isblackline(buffer))
				cout << rtrim(buffer) << endl;
			buffer = line;
			continue;
		}
		if (buffer.length() > 0) {
			buffer.append(" ");
			buffer.append(trim(head(line), tail(line)));
		} else {
			buffer = rtrim(line);
		}
		breakline(buffer);
	}
	breakline(buffer);
	if (! isblackline(buffer)) {
		cout << buffer << endl;
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

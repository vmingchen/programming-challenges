#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
	while (true) {
		string a, b;
		cin >> a >> b;
		if (a == "0" && b == "0") {
			break;
		}
		int carry = 0;
		int n = 0;
		int la = a.length();
		int lb = b.length();
		const int len = std::max(la, lb);
		for (int i = 0; i < len; ++i) {
			int value = carry;
			if (i < la) value += (a[la - 1 - i] - '0');
			if (i < lb) value += (b[lb - 1 - i] - '0');
			if (value >= 10) {
				++n;
			}
			carry = value / 10;
		}
		if (n == 0) {
			cout << "No carry operation." << endl;
		} else if (n == 1) {
			cout << "1 carry operation." << endl;
		} else {
			cout << n << " carry operations." << endl;
		}
	}
	return 0;
}

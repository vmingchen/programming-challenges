#include <iostream>

using namespace std;

// The results should be:
// (1, 9]:		Stan
// (9, 18]:		Ollie
// (18, 2*9^2]:		Stan
// (2*9^2, 2^2*9^2]:	Ollie
// (2^2*9^2, 2^2*9^3]:	Stan
// (2^2*9^3, 2^3*9^3]:	Ollie
// (2^3*9^3, 2^3*9^4]:	Stan
// ...
// 
// The idea is like this: 
// 1. With 1 steps, Stan will multiply the total to 9, so Stan wins between (1, 9];
// 2. With 2 steps, Ollie will multiply the total to (at least) 2*9 where the 2
//    comes from Stan and the 9 comes from Ollie, so Ollie wins (9, 2*9];
// 3. With 3 steps, Stan will multiply the total to (at least) 2*9^2 where the
//    2 comes from Ollie and the two 9s come from Stan, so Stan wins
//    any number within (2*9, 2*9^2];
// 4. With 4 steps, Ollie will multiply the total to (at least) 2^2*9^2 where
//    the two 2s come from Stan and the two 9s come from Ollie, so Ollie wins any
//    number between (2*9^2, 2^2*9^2];
// 5. With 5 steps, Stan will multiply the total to (at least) 2^2*9^3 where
//    the two 2s come from Ollie and the three 9s come from Stan, so Stan wins
//    any number between (2^2*9^2, 2^2*9^3];
// ...
// 2n. With 2n steps, Ollie wins (2^(n-1)*9^n, 2^n*9^n];
// 2n+1. With 2n+1 steps, Stan wins (2^n*9^n, 2^n*9^(n+1)];
int find_winner(unsigned long n) {
	if (n <= 9) {
		return 0; // Stan;
	} else if (n <= 18) {
		return 1; // Ollie
	} else {
		unsigned long t = 18;
		for (int i = 0; ; ++i) {
			int j = i % 2;
			t *= ((j == 0) ? 9 : 2);
			if (n <= t) {
				return j;
			}
		}
	}
}

int main() {
	unsigned long n;
	while (cin >> n) {
		int res = find_winner(n);
		cout << (res == 0 ? "Stan" : "Ollie") << " wins." << endl;
	}
	return 0;
}

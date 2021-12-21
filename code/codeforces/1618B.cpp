#include <bits/stdc++.h>
using namespace std;

inline int rd() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) f |= (c == '-');
	for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

string s;

inline void work() {
	int n = rd();
	cin >> s;
	string t;
	bool fl = 0;
	for (int i = 2; i <= n - 2; ++i) {
		cin >> t;
		if (t[0] != s[s.length() - 1]) {fl = 1; s += t;}
		else s += t[1];
	}
	if (!fl) s += 'a';
	cout << s << endl;
}

int main() {
	for (int t = rd(); t; --t) work();
	return 0;
}
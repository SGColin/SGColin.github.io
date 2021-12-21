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

int a[8];

inline void work() {
	for (int i = 1; i <= 7; ++i) a[i] = rd();
	if (a[1] + a[2] + a[3] == a[7]) printf("%d %d %d\n", a[1], a[2], a[3]);
	else printf("%d %d %d\n", a[1], a[2], a[4]);
}

int main() {
	for (int t = rd(); t; --t) work();
	return 0;
}
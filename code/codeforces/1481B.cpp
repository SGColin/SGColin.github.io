#include <bits/stdc++.h>
#define N 100007
using namespace std;
typedef long long ll;

inline int rd() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	for(; !isdigit(c); c = getchar()) 
		if (c == '-') f = 1;
	for(; isdigit(c); c = getchar())
		x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

int n, k, p, h[107];

inline int findpos() {
	for (int i = 1; i < n; ++i)
		if (h[i] < h[i + 1]) return i;
	return -1;
}

inline void work() {
	n = rd(); k = rd();
	for (int i = 1; i <= n; ++i) h[i] = rd();
	for (int i = 1; i <= k; ++i) {
		p = findpos();
		if (p == -1) {
			puts("-1"); return;
		} ++h[p];
	}
	printf("%d\n", p);
}

int main() {
	int t = rd();
	while (t--) work();
	return 0;
}
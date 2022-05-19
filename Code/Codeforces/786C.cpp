#include <bits/stdc++.h>
#define N 100007
using namespace std;

inline int rd() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) f |= (c == '-');
	for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

int n, a[N], vis[N];

inline int calc(int x) {
	int ans = 0, cnt = 0;
	memset(vis, -1, sizeof(vis));
	for (int i = 1; i <= n; ++i) {
		if (vis[a[i]] != ans) {
			if (cnt == x) {cnt = 0; ++ans;}
			++cnt; vis[a[i]] = ans;
		}
	}
	return ans + 1;
}

inline int getr(int x) {
	int l = 1, r = n;
	while (l < r) {
		int mid = (l + r + 1) / 2;
		calc(mid) < x ? r = mid - 1 : l = mid;
	}
	return l;
}

int main() {
	n = rd();
	int lim = sqrt(n * log2(n));
	for (int i = 1; i <= n; ++i) a[i] = rd();
	for (int i = 1; i <= lim; ++i)
		printf("%d ", calc(i));
	for (int l = lim + 1, r; l <= n; l = r + 1) {
		int t = calc(l); r = getr(t);
		for (int i = l; i <= r; ++i) printf("%d ", t);
	}
	return 0;
}
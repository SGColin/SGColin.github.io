#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100005
#define gc getchar
#define ls son[u][0]
#define rs son[u][1]
using namespace std;
typedef long long ll;

inline int rd() {
	int x = 0;
	char c = gc();
	while (!isdigit(c)) c = gc();
	while (isdigit(c)) {
		x = x * 10 + (c ^ 48);
		c = gc();
	}
	return x;
}

int n, m, a[N];

int son[N][2], stk[N], top;

ll sum[N], f[N], g[N];

int dfs(int u, int fa) {
	if (!u) return 0;
	int wd = dfs(ls, u) + dfs(rs, u) + 1;
	sum[u] = a[u] + sum[ls] + sum[rs];
	f[u] = f[ls] + f[rs];
	ll rem = 1ll * (a[u] - a[fa]) * wd - (g[ls] + g[rs]);
	f[u] += max(0ll, (rem + m - 1) / m);
	g[u] = f[u] * m - (sum[u] - 1ll * a[fa] * wd);
	return wd;
}

int main() {
	n = rd(); m = rd();
	for (int i = 1; i <= n; ++i) a[i] = rd();
	for (int i = 1; i <= n; ++i) {
		while (top && a[stk[top]] > a[i]) {
			son[i][0] = stk[top]; --top;
		}
		son[stk[top]][1] = i; stk[++top] = i;
	}
	dfs(stk[1], 0);
	printf("%lld\n", f[stk[1]]);
	return 0;
}

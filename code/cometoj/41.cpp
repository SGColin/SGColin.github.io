#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 105
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

ll f[N][N][N], g[N][N];

int dfs(int u, int fa) {
	if (!u) return 0;
	int wdl = dfs(ls, u), wdr = dfs(rs, u);
	ll wd = wdl + wdr + 1, ht = a[u] - a[fa];
	memset(g, 0xcf, sizeof(g));
	f[u][0][0] = g[0][0] = 0;
	for (int i = 0; i <= wdl && i <= m; ++i)
		for (int j = 0; j <= wdr && i + j <= m; ++j)
			for (int x = 0; x <= wdl; ++x)
				for (int y = 0; y <= wdr; ++y)
					g[i + j][x + y] = max(g[i + j][x + y], f[ls][i][x] + f[rs][j][y] + ht * (x + y));
	for (int i = 0; i <= wd && i <= m; ++i)
		for (int x = 0; x <= wd; ++x) {
			f[u][i][x] = max(f[u][i][x], g[i][x]);
			if (i + 1 <= min(wd, (ll)m))  f[u][i + 1][wd] = max(f[u][i + 1][wd], g[i][x] +  ht * (wd - x));
		}
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
	memset(f, 0xcf, sizeof(f));
	f[0][0][0] = 0;
 	dfs(stk[1], 0);
	ll ans = 0;
	for (int i = 0; i <= n; ++i) ans = max(ans, f[stk[1]][m][i]);
	printf("%lld\n", ans);
	return 0;
}

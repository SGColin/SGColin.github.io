#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define pii pair<int, int>

#define N 10007

struct UFS {
	int f[N];
	void reset(int n) {
		for (int i = 1; i <= n; ++i) f[i] = i;
	}
	int find(int u) {
		return u == f[u] ? u : (f[u] = find(f[u]));
	}
	void merge(int u, int v) {
		f[find(u)] = find(v);
	}
}ufs;

vector<pii> e[N];

int n, m, q, t, fa[N][15], dep[N], sum[N];

void dfs(int u) {
	for (auto cur : e[u]) {
		int v = cur.first;
		int w = cur.second;
		if (v != fa[u][0]) {
			fa[v][0] = u;
			dep[v] = dep[u] + 1;
			sum[v] = sum[u] + w;
			dfs(v);
		}
	}
}

inline int lca(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	for (int i = t; ~i; --i)
		if (dep[fa[v][i]] >= dep[u]) v = fa[v][i];
	if (u == v) return u;
	for (int i = t; ~i; --i)
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i]; v = fa[v][i];
		}
	return fa[u][0];
}

inline void work() {

	ufs.reset(n);

	for (int i = 1, u, v, w; i <= m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		ufs.merge(u, v);
		e[u].pb(mp(v, w));
		e[v].pb(mp(u, w));
	}

	for (int u = 1; u <= n; ++u)
		if (!fa[u][0]) {
			fa[u][0] = u; dfs(u);
		}

	t = __lg(n - 1) + 1;
	for (int i = 1; i <= t; ++i)
		for (int u = 1; u <= n; ++u)
			fa[u][i] = fa[fa[u][i - 1]][i - 1];

	for (int i = 1, u, v; i <= q; ++i) {
		scanf("%d%d", &u, &v);
		if (ufs.find(u) != ufs.find(v)) puts("Not connected");
		else printf("%d\n", sum[u] + sum[v] - 2 * sum[lca(u, v)]);
	}

	for (int u = 1; u <= n; ++u) {
		fa[u][0] = dep[u] = sum[u] = 0; e[u].clear();
	}
}

int main() {
	while(scanf("%d%d%d", &n, &m, &q) != EOF) work();
	return 0;
}
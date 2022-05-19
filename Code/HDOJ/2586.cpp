#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define pii pair<int, int>

#define N 40007

vector<pii> e[N];

int t, fa[N][17], dep[N], sum[N];

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
	int n, q;
	cin >> n >> q;
	for (int i = 1, u, v, w; i < n; ++i) {
		cin >> u >> v >> w;
		e[u].pb(mp(v, w));
		e[v].pb(mp(u, w));
	}

	fa[1][0] = 1; dfs(1);

	t = __lg(n - 1) + 1;
	for (int i = 1; i <= t; ++i)
		for (int u = 1; u <= n; ++u)
			fa[u][i] = fa[fa[u][i - 1]][i - 1];

	for (int i = 1, u, v; i <= q; ++i) {
		cin >> u >> v;
		cout << sum[u] + sum[v] - 2 * sum[lca(u, v)] << endl;
	}

	for (int u = 1; u <= n; ++u) {
		fa[u][0] = dep[u] = sum[u] = 0; e[u].clear();
	}
}

int main() {
	cin.tie(nullptr) -> sync_with_stdio(false);
	int t;
	for (cin >> t; t; --t) work();
	return 0;
}
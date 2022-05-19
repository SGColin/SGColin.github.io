#include<bits/stdc++.h>
using namespace std;

#define pb push_back

int cnt;

unordered_map<string, int> id;

int getid(string &s) {
	if (id[s] == 0) id[s] = ++cnt;
	return id[s];
}

#define N 100007

vector<int> son[N];

int t, fa[N][18], dep[N];

void dfs(int u) {
	for (auto v : son[u]) {
		dep[v] = dep[u] + 1; dfs(v);
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
	string a, b;
	cin >> n >> q;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> a >> b;
		u = getid(a); 
		v = getid(b);
		fa[u][0] = v; 
		son[v].pb(u);
	}
	for (int u = 1; u <= n; ++u)
		if (fa[u][0] == 0) {
			fa[u][0] = u; dfs(u); break;
		}

	t = __lg(n - 1) + 1;
	for (int i = 1; i <= t; ++i)
		for (int u = 1; u <= n; ++u)
			fa[u][i] = fa[fa[u][i - 1]][i - 1];

	for (int i = 1, u, v, anc; i <= q; ++i) {
		cin >> a >> b;
		if (a == b) {puts("0"); continue;}
		u = getid(a);
		v = getid(b);
		anc = lca(u, v);
		printf("%d\n", anc == u ? 1 : dep[u] - dep[anc] + (anc != v));
	}

	for (int u = 1; u <= n; ++u) {
		fa[u][0] = dep[u] = 0; son[u].clear();
	}
	cnt = 0; id.clear();
}

int main() {
	cin.tie(nullptr) -> sync_with_stdio(false);
	int t;
	for (cin >> t; t; --t) work();
	return 0;
}
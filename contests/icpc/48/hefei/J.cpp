#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tii;

inline int rd() {
	int x = 0;
	bool f = 0;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) f |= (c == '-');
	for (; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
	return f ? -x : x;
}

#define N 300007
#define eb emplace_back

int f[N], mx[2][N];

vector<pii> e[N];

vector<tii> edge;

int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}

void dfs(int u, int fa, int x) {
	for (auto [v, w] : e[u])
		if (v != fa) {
			mx[x][v] = max(mx[x][u], w);
			dfs(v, u, x);
		}
}

int main() {
	int n = rd(), m = rd();
	for (int i = 1; i <= m; ++i) {
		int u = rd(), v = rd(), w = rd();
		edge.eb(w, u, v);
	}
	for (int i = 1; i <= n; ++i) f[i] = i;
	sort(edge.begin(), edge.end());
	for (auto [w, u, v] : edge) {
		if (find(u) != find(v)) {
			f[find(u)] = find(v);
			e[u].eb(v, w); e[v].eb(u, w);
		}
	}
	dfs(1, 1, 1); 
	dfs(n, n, 0);
	int ans = INT_MAX;
	for (auto [w, u, v] : edge) {
		if (mx[0][u] <= w && mx[1][v] <= w) ans = min(ans, w + max(mx[0][u], mx[1][v]));
		if (mx[1][u] <= w && mx[0][v] <= w) ans = min(ans, w + max(mx[1][u], mx[0][v]));
	}
	printf("%d\n", ans);
	return 0;
}
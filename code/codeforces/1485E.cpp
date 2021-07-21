#include <bits/stdc++.h>
#define N 200007
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

struct edge{
	int to, nxt;
} e[N << 1];

int tot, hd[N], a[N], s[N];

int mxa[N], mna[N], d[N], fa[N];

ll mxp[N], mxm[N], f[N];

inline void add(int u, int v) {
	e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot; 
	e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

void dfs1(int u) {
	d[u] = d[fa[u]] + 1;
	mxa[d[u]] = max(mxa[d[u]], a[u]);
	mna[d[u]] = min(mna[d[u]], a[u]);
	for (int i = hd[u], v; i; i = e[i].nxt)
		if ((v = e[i].to) != fa[u]) {
			fa[v] = u; dfs1(v);
		} 
}

inline bool cmpd(int x, int y) {
	return d[x] > d[y];
}



inline void work() {
	tot = 0;
	int n = rd();
	for (int i = 1; i <= n; ++i) {
		s[i] = i;
		hd[i] = mxa[i] = 0; 
		f[i] = mxp[i] = 0ll; 
		mxm[i] = -1e9; mna[i] = 1e9;
	}
	for (int i = 2; i <= n; ++i) add(i, rd());
	for (int i = 2; i <= n; ++i) a[i] = rd();
	dfs1(1); 
	sort(s + 1, s + 1 + n, cmpd);
	int mxd = d[s[1]];
	for (int k = 1, u; k <= n; ++k) {
		u = s[k];
		for (int i = hd[u], v; i; i = e[i].nxt)
			if ((v = e[i].to) != fa[u]) f[u] = max(f[u], f[v]);
		f[u] += max(mxa[d[u]] - a[u], a[u] - mna[d[u]]);
		if (d[u] != mxd) {
			f[u] = max(f[u], mxp[d[u] + 1] - a[u]);
			f[u] = max(f[u], mxm[d[u] + 1] + a[u]);
		}
		mxp[d[u]] = max(mxp[d[u]], f[u] + a[fa[u]]);
		mxm[d[u]] = max(mxm[d[u]], f[u] - a[fa[u]]);
	}
	printf("%lld\n", f[1]);
}

int main(){
	int t = rd();
	while (t--) work();
    return 0;
}
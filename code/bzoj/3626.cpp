#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 50005
#define gc getchar
#define inf 1000000000
#define mid ((l + r) >> 1)
#define mod 201314ll
using namespace std;
typedef long long LL;

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = 1;
    c = gc();
  }
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

struct node{
  int ls, rs;
  vector<pair<int, int> > s;
} c[N << 1];

int n, m, ptr, root, tot, hd[N];

struct edge{int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

void build(int &rt, int l, int r) {
  rt = ++ptr;
  if (l == r) return;
  build(c[rt].ls, l, mid);
  build(c[rt].rs, mid + 1, r);
}

void updata(int rt, int l, int r, int L, int R, int x, int id) {
  if (L <= l && r <= R) {
    c[rt].s.push_back(make_pair(x, id));
    return;
  }
  if (L <= mid) updata(c[rt].ls, l, mid, L, R, x, id);
  if (R > mid) updata(c[rt].rs, mid + 1 ,r, L, R, x, id);
}

int f[N], d[N], sz[N], son[N];

void dfs1(int u) {
  sz[u] = 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != f[u]) {
      f[v] = u; d[v] = d[u] + 1;
      dfs1(v); sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

int cnt, dfn[N], ed_dfn[N], topf[N];

void dfs2(int u) {
  dfn[u] = ++cnt;
  if (!topf[u]) topf[u] = u;
  if (son[u]) topf[son[u]] = topf[u], dfs2(son[u]);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != f[u] && v != son[u]) dfs2(v);
  ed_dfn[u] = cnt;
}

inline int lca(int u, int v) {
  while (topf[u] != topf[v]) {
    if (d[topf[u]] < d[topf[v]]) swap(u, v);
    u = f[topf[u]];
  }
  return d[u] < d[v] ? u : v;
}

LL g[N], h[N], ans[N];

int tota, a[N << 2], top, stk[N], ll, rr;

inline bool cmp(int x, int y){return dfn[x] < dfn[y];}

void dp1(int u, int fa) {
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) {dp1(v, u); sz[u] += sz[v];}
  h[u] += 1ll * sz[u] * d[u];
}

void dp2(int u, int fa) {
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) {
      g[v] = g[u] + 1ll * (sz[u] - sz[v]) * d[u];
      h[v] += g[v]; dp2(v, u);
    }
}

inline void work() {
  tot = 0;
  sort(a + 1, a + 1 + tota, cmp);
  for (int i = 1, lim = tota; i < lim; ++i) a[++tota] = lca(a[i], a[i + 1]);
  sort(a + 1, a + 1 + tota, cmp);
  tota = unique(a + 1, a + 1 + tota) - a - 1;
  for (int i = 1; i <= tota; ++i) {
    hd[a[i]] = 0;
    g[a[i]] = h[a[i]] = 0;
    sz[a[i]] = (a[i] >= ll && a[i] <= rr);
  }
  top = 0;
  for (int i = 1, u; i <= tota; ++i) {
    u = a[i];
    while (top && ed_dfn[stk[top]] < dfn[u]) --top;
    stk[++top] = u;
    if (top >= 2) add(stk[top], stk[top - 1]);
  }
  dp1(a[1], 0); dp2(a[1], 0);
}

void solve(int rt, int l, int r) {
  if (c[rt].s.size()) {
    tota = 0;
    for (int i = l; i <= r; ++i) a[++tota] = i;
    for (int i = c[rt].s.size() - 1; ~i; --i) a[++tota] = c[rt].s[i].first;
    ll = l; rr = r; work();
    for (int i = c[rt].s.size() - 1; ~i; --i)
      ans[c[rt].s[i].second] += h[c[rt].s[i].first];
  }
  if (l == r) return;
  solve(c[rt].ls, l, mid);
  solve(c[rt].rs, mid + 1, r);
}

int main() {
  n = rd(); m = rd();
  build(root, 1, n);
  for (int i = 2; i <= n; ++i) add(i, rd() + 1);
  d[1] = 1; dfs1(1); dfs2(1);
  for (int i = 1; i <= n; ++i) hd[i] = 0;
  for (int i = 1, l, r, x; i <= m; ++i) {
    l = rd() + 1; r = rd() + 1; x = rd() + 1;
    updata(root, 1, n, l, r, x, i);
  }
  solve(root, 1, n);
  for (int i = 1; i <= m; ++i) printf("%lld\n", ans[i] % mod);
  return 0;
}

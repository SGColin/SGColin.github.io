#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200005
#define gc getchar
#define mid ((l + r) >> 1)
#define inf 2000000000
using namespace std;

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

int tot, n, m, q;

vector<int> e[N], r[N];

inline void adde(int u, int v) {
  e[u].push_back(v); e[v].push_back(u);
}

inline void addr(int u, int v) {
  r[u].push_back(v); r[v].push_back(u);
}

multiset<int> w[N];

int cnt, dfn[N], low[N], top, stk[N];

void tarjan(int u) {
  stk[++top] = u;
  dfn[u] = low[u] = ++cnt;
  for (int i = e[u].size() - 1, v, tmp; ~i; --i)
    if (!dfn[v = e[u][i]]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if (dfn[u] <= low[v]) {
        addr(++tot, u);
        do {
          tmp = stk[top--];
          addr(tot, tmp);
        } while (tmp != v);
      }
    } else low[u] = min(low[u], dfn[v]);
}

int d[N], f[N], sz[N], son[N], topf[N], pos[N];

void dfs1(int u) {
  sz[u] = 1;
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != f[u]) {
      f[v] = u; d[v] = d[u] + 1;
      dfs1(v); sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
      if (u > n) w[u].insert(*w[v].begin());
    }
}

void dfs2(int u) {
  pos[dfn[u] = ++cnt] = u;
  if (!topf[u]) topf[u] = u;
  if (son[u]) topf[son[u]] = topf[u], dfs2(son[u]);
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != f[u] && v != son[u]) dfs2(v);
}

int root, ptr;

struct node{
  int ls, rs, w;
} c[N << 1];

void build(int &rt, int l, int r) {
  rt = ++ptr;
  if (l == r) {
    c[rt].w = *w[pos[l]].begin();
    return;
  }
  build(c[rt].ls, l, mid);
  build(c[rt].rs, mid + 1, r);
  c[rt].w = min(c[c[rt].ls].w, c[c[rt].rs].w);
}

void updata(int rt, int l, int r, int p, int x) {
  if (l == r) {c[rt].w = x; return;}
  if (p <= mid) updata(c[rt].ls, l, mid, p, x);
  else updata(c[rt].rs, mid + 1, r, p, x);
  c[rt].w = min(c[c[rt].ls].w, c[c[rt].rs].w);
}

int query(int rt, int l, int r, int L, int R) {
  if (l >= L && r <= R) return c[rt].w;
  int ans = inf;
  if (L <= mid) ans = min(ans, query(c[rt].ls, l, mid, L, R));
  if (R > mid) ans = min(ans, query(c[rt].rs, mid + 1, r, L, R));
  return ans;
}

pair<int, int> lca(int u, int v) {
  int ans = inf;
  while (topf[u] != topf[v]) {
    if (d[topf[u]] < d[topf[v]]) swap(u, v);
    ans = min(ans, query(root, 1, tot, dfn[topf[u]], dfn[u]));
    u = f[topf[u]];
  }
  if (d[u] > d[v]) swap(u, v);
  ans = min(ans, query(root, 1, tot, dfn[u], dfn[v]));
  return make_pair(u, ans);
}

int main() {
  tot = n = rd();
  m = rd(); q = rd();
  for (int i = 1; i <= n; ++i) w[i].insert(rd());
  for (int i = 1; i <= m; ++i) adde(rd(), rd());
  tarjan(1);
  cnt = 0; d[1] = 1; dfs1(1); dfs2(1);
  for (int i = 0; i <= tot; ++i) w[i].insert(inf);
  build(root, 1, tot);
  char ch;
  for (int i = 1, a, b; i <= q; ++i) {
    ch = gc();
    while (!isalpha(ch)) ch = gc();
    a = rd(); b = rd();
    if (ch == 'C') {
      int lst = *w[f[a]].begin();
      w[f[a]].erase(w[f[a]].lower_bound(*w[a].begin()));
      w[f[a]].insert(b);
      if (*w[f[a]].begin() != lst)
        updata(root, 1, tot, dfn[f[a]], *w[f[a]].begin());
      w[a].erase(*w[a].begin());
      w[a].insert(b);
      updata(root, 1, tot, dfn[a], b);
    } else {
      pair<int, int> res = lca(a, b);
      int l = res.first, ans = res.second;
      if (l > n) ans = min(ans, *w[f[l]].begin());
      printf("%d\n", ans);
    }
  }
  return 0;
}

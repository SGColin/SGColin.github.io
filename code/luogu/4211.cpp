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
#define mod 201314
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

int n, m, ptr, root, tot, hd[N], ans[N];

struct edge{int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
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

int cnt, dfn[N], top[N];

void dfs2(int u) {
  dfn[u] = ++cnt;
  if (!top[u]) top[u] = u;
  if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != f[u] && v != son[u]) dfs2(v);
}

inline int lca(int u, int v) {
  while (top[u] != top[v]) {
    if (d[top[u]] < d[top[v]]) swap(u, v);
    u = f[top[u]];
  }
  return d[u] < d[v] ? u : v;
}

struct node{int ls, rs, sum, tag;} c[N << 1];

inline int mo(int x) {return x >= mod ? x - mod : x;}

inline void pushup(int rt) {
  c[rt].sum = mo(c[c[rt].ls].sum + c[c[rt].rs].sum);
}

inline void pushdown(int rt, int l, int r) {
  c[c[rt].ls].tag += c[rt].tag;
  c[c[rt].rs].tag += c[rt].tag;
  c[c[rt].ls].sum = mo(c[c[rt].ls].sum + (mid - l + 1) * c[rt].tag);
  c[c[rt].rs].sum = mo(c[c[rt].rs].sum + (r - mid) * c[rt].tag);
  c[rt].tag = 0;
}

void build(int &rt, int l, int r) {
  rt = ++ptr;
  if (l == r) return;
  build(c[rt].ls, l, mid);
  build(c[rt].rs, mid + 1, r);
}

void updata(int rt, int l, int r, int L, int R) {
  if (L <= l && r <= R) {
    ++c[rt].tag;
    c[rt].sum = mo(c[rt].sum + (r - l + 1));
    return;
  }
  if (c[rt].tag) pushdown(rt, l, r);
  if (L <= mid) updata(c[rt].ls, l, mid, L, R);
  if (R > mid) updata(c[rt].rs, mid + 1 ,r, L, R);
  pushup(rt);
}

int query(int rt, int l, int r, int L, int R) {
  if (L <= l && r <= R) return c[rt].sum;
  int ans = 0;
  if (c[rt].tag) pushdown(rt, l, r);
  if (L <= mid) ans = query(c[rt].ls, l, mid, L, R);
  if (R > mid) ans = mo(ans + query(c[rt].rs, mid + 1, r, L, R));
  pushup(rt);
  return ans;
}

void modify(int u) {
  while (top[u] != 1) {
    updata(root, 1, n, dfn[top[u]], dfn[u]);
    u = f[top[u]];
  }
  updata(root, 1, n, 1, dfn[u]);
}

int ask(int u) {
  int res = 0;
  while (top[u] != 1) {
    res = mo(res + query(root, 1, n, dfn[top[u]], dfn[u]));
    u = f[top[u]];
  }
  res = mo(res + query(root, 1, n, 1, dfn[u]));
  return res;
}

vector<pair<int, int> > s[N];

int main() {
  n = rd(); m = rd();
  build(root, 1, n);
  for (int i = 2; i <= n; ++i) add(i, rd() + 1);
  d[1] = 1; dfs1(1); dfs2(1);
  for (int i = 1, l, r, x; i <= m; ++i) {
    l = rd() + 1; r = rd() + 1; x = rd() + 1;
    s[r].push_back(make_pair(x, i));
    if (l != 1) s[l - 1].push_back(make_pair(-x, i));
  }
  for (int i = 1; i <= n; ++i) {
    modify(i);
    for (int j = s[i].size() - 1, p, x; ~j; --j) {
      x = s[i][j].first; p = s[i][j].second;
      ans[p] += (x < 0 ? -1 : 1) * ask(abs(x));
    }
  }
  for (int i = 1; i <= m; ++i) printf("%d\n", (ans[i] % mod + mod) % mod);
  return 0;
}

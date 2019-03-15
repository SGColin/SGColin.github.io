#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 100005
#define mod 998244353
#define mid ((l + r) >> 1)
using namespace std;

inline int rd() {
  int x = 0;
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = getchar();
  }
  return x;
}

inline int mo(int x) {
  if (x <= mod) x += mod;
  return x >= mod ? x - mod : x;
}

int n, m, tot, hd[N], a[N], sum1[N], sum2[N];

struct edge{int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

int fa[N], dep[N], son[N], sz[N];

void dfs1(int u, int fafa) {
  sz[u] = 1;
  fa[u] = fafa;
  dep[u] = dep[fa[u]] + 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa[u]) {
      dfs1(v, u); sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

int cnt, dfn[N], topfa[N];

void dfs2(int u, int tptp) {
  dfn[u] = ++cnt;
  topfa[u] = tptp;
  if (son[u]) dfs2(son[u], tptp);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa[u] && v != son[u]) dfs2(v, v);
}

int root, ptr;

struct node{
  int ls, rs, tag, sum;
} c[N << 1];

void build(int &rt, int l, int r) {
  rt = ++ptr;
  if (l == r) return;
  build(c[rt].ls, l, mid);
  build(c[rt].rs, mid + 1, r);
}

inline void pushdown(int rt, int l, int r) {
  c[c[rt].ls].tag = mo(c[c[rt].ls].tag + c[rt].tag);
  c[c[rt].rs].tag = mo(c[c[rt].rs].tag + c[rt].tag);
  c[c[rt].ls].sum = mo(c[c[rt].ls].sum + 1ll * c[rt].tag * (mid - l + 1) % mod);
  c[c[rt].rs].sum = mo(c[c[rt].rs].sum + 1ll * c[rt].tag * (r - mid) % mod);
  c[rt].tag = 0;
}

inline void pushup(int rt) {
  c[rt].sum = mo(c[c[rt].ls].sum + c[c[rt].rs].sum);
}

void updata(int rt, int l, int r, int L, int R, int x) {
  if (L <= l&& r <= R) {
    c[rt].tag = mo(c[rt].tag + x);
    c[rt].sum = mo(c[rt].sum + 1ll * (r - l + 1) * x % mod);
    return;
  }
  if (c[rt].tag) pushdown(rt, l, r);
  if (L <= mid) updata(c[rt].ls, l, mid, L, R, x);
  if (R > mid) updata(c[rt].rs, mid + 1, r, L, R, x);
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

int dlt[N];

inline void modify(int u, int x) {
  while (topfa[u] != 1) {
    updata(root, 1, n, dfn[topfa[u]], dfn[u], x);
    u = fa[topfa[u]];
  }
  updata(root, 1, n, 1, dfn[u], x);
}

inline int ask(int u) {
  int ans = 0;
  while (topfa[u] != 1) {
    ans = mo(ans + query(root, 1, n, dfn[topfa[u]], dfn[u]));
    u = fa[topfa[u]];
  }
  ans = mo(ans + query(root, 1, n, 1, dfn[u]));
  return ans;
}

int main() {
  n = rd(); m = rd();
  for (int i = 1; i < n; ++i) add(rd(), rd());
  for (int i = 1; i <= n; ++i) a[i] = rd();
  dfs1(1, 0); dfs2(1, 1);
  for (int i = 1; i <= n; ++i) {
    sum2[i] = mo(sum2[i - 1] + i);
    sum1[i] = mo(sum1[i - 1] + 1ll * dep[a[i]] * i % mod);
  }
  build(root, 1, n);
  for (int i  = 1; i <= n; ++i) {
    modify(a[i], i);
    dlt[i] = mo(sum1[i] + 1ll * dep[a[i]] * sum2[i] % mod);
    dlt[i] = ((dlt[i] - 2 * ask(a[i])) % mod + mod) % mod;
  }
  for (int i = 1; i <= n; ++i) dlt[i] = mo(dlt[i] + dlt[i - 1]);
  for (int i = 1; i <= n; ++i) dlt[i] = mo(dlt[i] + dlt[i - 1]);
  for (int i = 1; i <= m; ++i) printf("%d\n", dlt[rd()]);
  return 0;
}

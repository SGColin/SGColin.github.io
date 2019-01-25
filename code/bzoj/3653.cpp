#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 300010
#define gc getchar
#define rg register
#define mid ((l + r) >> 1)
using namespace std;
typedef long long ll;

inline int rd() {
  rg int x = 0;
  rg bool f = 0;
  rg char c = gc();
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

int n, m, tot, hd[N];

struct edge {int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

int cnt, sz[N], d[N], dfn[N], pos[N];

void dfs(int u, int fa) {
  sz[u] = 1;
  dfn[u] = ++cnt; pos[cnt] = u;
  for (rg int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa){
      d[v] = d[u] + 1;
      dfs(v, u); sz[u] += sz[v];
    }
}

int rot[N], ptr;

struct node {
  int ls, rs; ll sum;
} c[N << 5];

void build(int &rt, int lst, int l, int r, int p, int x) {
  c[rt = ++ptr] = c[lst];
  c[rt].sum += x;
  if (l == r) return;
  if (p <= mid) build(c[rt].ls, c[lst].ls, l, mid, p, x);
  else build(c[rt].rs, c[lst].rs, mid + 1, r, p, x);
}

ll query(int rtl, int rtr, int l, int r, int L, int R) {
  if (L <= l && r <= R) return c[rtr].sum - c[rtl].sum;
  ll ans = 0;
  if (L <= mid) ans += query(c[rtl].ls, c[rtr].ls, l, mid, L, R);
  if (R > mid) ans += query(c[rtl].rs, c[rtr].rs, mid + 1, r, L, R);
  return ans;
}

int main() {
  n = rd(); m = rd();
  for (rg int i = 1; i < n; ++i) add(rd(), rd());
  dfs(1, 0);
  for (rg int i = 1; i <= n; ++i) build(rot[i], rot[i - 1], 1, n, d[pos[i]], sz[pos[i]] - 1);
  int k, u;
  while (m--) {
    u = rd(); k = rd();
    ll ans = 1ll * min(k, d[u]) * (sz[u] - 1);
    ans += query(rot[dfn[u]], rot[dfn[u] + sz[u] - 1], 1, n, d[u], d[u] + k);
    printf("%lld\n", ans);
  }
  return 0;
}

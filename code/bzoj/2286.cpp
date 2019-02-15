#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 250005
#define gc getchar
using namespace std;
typedef long long ll;

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

int n, m, k, tot, hd[N], s[N << 1];

struct edge{
  int to, nxt, w;
} e[N << 1];

inline void add(int u, int v, int w) {
  e[++tot].to = v; e[tot].w = w;
  e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].w = w;
  e[tot].nxt = hd[v]; hd[v] = tot;
}

inline void addx(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
}

ll mn[N];

int sz[N], d[N], f[N], son[N];

void dfs1(int u, int fa) {
  sz[u] = 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) {
      d[v] = d[u] + 1; f[v] = u;
      mn[v] = min((ll)e[i].w, mn[u]);
      dfs1(v, u); sz[u] += sz[v];
      if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

int cnt, dfn[N], ed_dfn[N], topf[N];

void dfs2(int u, int fa) {
  dfn[u] = ++cnt;
  if (!topf[u]) topf[u] = u;
  if (son[u]) topf[son[u]] = topf[u], dfs2(son[u], u);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa && v != son[u]) dfs2(v, u);
  ed_dfn[u] = cnt;
}

inline int lca(int u, int v) {
  while (topf[u] != topf[v]) {
    if (d[topf[u]] < d[topf[v]]) swap(u, v);
    u = f[topf[u]];
  }
  return d[u] < d[v] ? u : v;
}

bool fl[N];

int stk[N], top;

inline bool cmp(int x, int y) {return dfn[x] < dfn[y];}

ll dfs(int u, int fa) {
  if (!hd[u]) return mn[u];
  ll sum = 0;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) sum += dfs(v, u);
  return min(sum, mn[u]);
}

inline void work() {
  k = rd(); tot = 0;
  for (int i = 1; i <= k; ++i) fl[s[i] = rd()] = 1;
  sort(s + 1, s + 1 + k, cmp);
  for (int i = 1, lim = k; i < lim; ++i) s[++k] = lca(s[i], s[i + 1]);
  sort(s + 1, s + 1 + k, cmp);
  k = unique(s + 1, s + 1 + k) - s - 1;
  for (int i = 1; i <= k; ++i) hd[s[i]] = 0;
  top = 0;
  for (int i = 1, u; i <= k; ++i) {
    u = s[i];
    while (top && ed_dfn[stk[top]] < dfn[u]) --top;
    stk[++top] = u;
    if (top >= 2) addx(stk[top - 1], stk[top]);
    if (fl[u]) while (i < k && dfn[s[i + 1]] < ed_dfn[u]) ++i;
  }
  for (int i = 1; i <= k; ++i) fl[s[i]] = 0;
  printf("%lld\n", dfs(s[1], 0));
}

int main() {
  n = rd();
  for (int i = 1, u, v, w; i < n; ++i) {
    u = rd(); v = rd(); w = rd(); add(u, v, w);
  }
  d[1] = 1; mn[1] = 1ll << 60;
  dfs1(1, 0); dfs2(1, 0);
  for (int i = 1; i <= n; ++i) hd[i] = 0;
  m = rd();
  while (m--) work();
  return 0;
}

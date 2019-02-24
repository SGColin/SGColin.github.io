#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 500005
#define gc getchar
using namespace std;
typedef long long ll;

inline int rd() {
  int x = 0;
  char c = gc();
  while (!isdigit(c)) c = gc();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = gc();
  }
  return x;
}

vector<int> r[N], z;

int n, m, tot, hd[N], tots, s[N];

struct edge {int to, nxt, w;} e[N];

inline void adde(int u, int v, int w) {
  e[++tot].to = v; e[tot].w = w;
  e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].w = w;
  e[tot].nxt = hd[v]; hd[v] = tot;
}

inline void addr(int u, int v) {
  r[u].push_back(v); r[v].push_back(u);
}

ll mn[N];

int d[N], f[N], sz[N], son[N];

void dfs1(int u) {
  sz[u] = 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != f[u]) {
      f[v] = u; d[v] = d[u] + 1;
      mn[v] = min(mn[u], (ll) e[i].w);
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

bool sp[N];

int top, stk[N];

inline bool cmp(int u, int v) {return dfn[u] < dfn[v];}

ll dfs(int u, int fa) {
  if (sp[u]) {sp[u] = 0; return mn[u];}
  ll sum = 0;
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != fa) sum += dfs(v, u);
  return min(sum, mn[u]);
}

int cnti = 0;

inline void work() {
  top = 0; tots = rd();
  for (int i = 1; i <= tots; ++i) {s[i] = rd(); sp[s[i]] = 1;}
  sort(s + 1, s + 1 + tots, cmp);
  for (int i = 2, lim = tots; i <= lim; ++i) s[++tots] = lca(s[i - 1], s[i]);
  sort(s + 1, s + 1 + tots, cmp);
  tots = unique(s + 1, s + 1 + tots) - s - 1;
  for (int i = 1, u; i <= tots; ++i) {
    u = s[i]; r[u] = z;
    while (top && ed_dfn[stk[top]] < dfn[u]) --top;
    stk[++top] = u;
    if (top >= 2) addr(stk[top], stk[top - 1]);
  }
  printf("%lld\n", dfs(s[1], 0));
  for (int i = 1; i <= tots; ++i) sp[s[i]] = 0;
}

int main() {
  n = rd();
  for (int i = 1, u, v, w; i < n; ++i) {
    u = rd(); v = rd(); w = rd(); adde(u, v, w);
  }
  d[1] = 1; mn[1] = 1ll << 60;
  dfs1(1); dfs2(1);
  m = rd();
  while (m--) work();
  return 0;
}

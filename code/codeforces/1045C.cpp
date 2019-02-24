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

int n, m, q, stk[N], top;

vector<int> e[N >> 1], r[N];

inline void adde(int u, int v) {
  e[u].push_back(v); e[v].push_back(u);
}

inline void addr(int u, int v) {
  r[u].push_back(v); r[v].push_back(u);
}

int tot, cnt, dfn[N], low[N];

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
        } while(tmp != v);
      }
    }
    else low[u] = min(low[u], dfn[v]);
}

int f[N], d[N], sz[N], son[N], topf[N];

void dfs1(int u) {
  sz[u] = 1;
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != f[u]) {
      f[v] = u; d[v] = d[u] + 1;
      dfs1(v); sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u) {
  dfn[u] = ++cnt;
  if (!topf[u]) topf[u] = u;
  if (son[u]) topf[son[u]] = topf[u], dfs2(son[u]);
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != f[u] && v != son[u]) dfs2(v);
}

inline int lca(int u, int v) {
  while (topf[u] != topf[v]) {
    if (d[topf[u]] < d[topf[v]]) swap(u, v);
    u = f[topf[u]];
  }
  return d[u] < d[v] ? u : v;
}

int main() {
  tot = n = rd(); m = rd(); q = rd();
  for (int i = 1; i <= m; ++i) adde(rd(), rd());
  tarjan(1); cnt = 0;
  d[1] = 1; dfs1(1); dfs2(1);
  for (int i = 1, u, v; i <= q; ++i) {
    u = rd(); v = rd();
    printf("%d\n", (d[u] + d[v] - 2 * d[lca(u, v)]) / 2);
  }
  return 0;
}

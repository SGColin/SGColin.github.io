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
  char c = gc();
  while (!isdigit(c)) c = gc();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = gc();
  }
  return x;
}

int n, m;

vector<int> e[N], r[N], t;

void adde(int u, int v) {
  e[u].push_back(v); e[v].push_back(u);
}

void addr(int u, int v) {
  r[u].push_back(v); r[v].push_back(u);
}

int tot, cnt, dfn[N], low[N], top, stk[N];

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

int f[N], d[N], sz[N], son[N];

void dfs1(int u) {
  sz[u] = 1;
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != f[u]) {
      f[v] = u; d[v] = d[u] + 1;
      dfs1(v); sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

int ed_dfn[N], topf[N];

void dfs2(int u) {
  dfn[u] = ++cnt;
  if (!topf[u]) topf[u] = u;
  if (son[u]) topf[son[u]] = topf[u], dfs2(son[u]);
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != f[u] && v != son[u]) dfs2(v);
  ed_dfn[u] = cnt;
}

inline int lca(int u, int v) {
  while (topf[u] != topf[v]) {
    if (d[topf[u]] < d[topf[v]]) swap(u, v);
    u = f[topf[u]];
  }
  return d[u] < d[v] ? u : v;
}

int totn, s[N];

inline bool cmp(int u, int v) {return dfn[u] < dfn[v];}

inline int calc() {
  int ans = -totn;
  sort(s + 1, s + 1 + totn, cmp);
  for (int i = 1, lim = totn; i < lim; ++i) s[++totn] = lca(s[i], s[i + 1]);
  sort(s + 1, s + 1 + totn, cmp);
  totn = unique(s + 1, s + 1 + totn) - s - 1;
  top = 0;
  for (int i = 1, u; i <= totn; ++i) {
    u = s[i]; ans += (u <= n);
    while (top && ed_dfn[stk[top]] < dfn[u]) --top;
    stk[++top] = u;
    if (top >= 2) ans += max(0, (d[stk[top]] - d[stk[top - 1]]) / 2 - (stk[top] <= n && stk[top - 1] <= n));
  }
  return ans;
}

void work() {
  tot = n = rd(); m = rd();
  for (int i = 1;  i <= (n << 1); ++i)
    dfn[i] = low[i] = son[i] = topf[i] = 0;
  for (int i = 1; i <= (n << 1); ++i) e[i] = r[i] = t;
  for (int i = 1; i <= m; ++i) adde(rd(), rd());
  tarjan(1);
  cnt = 0; d[1] = 1; dfs1(1); dfs2(1);
  int q = rd();
  while (q--) {
    totn = rd();
    for (int i =1; i <= totn; ++i) s[i] = rd();
    printf("%d\n", calc());
  }
}

int main() {
  int t = rd();
  while (t--) work();
  return 0;
}

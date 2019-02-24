#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000005
#define gc getchar
#define inf 1ll << 60
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

vector<int> e[N], r[N], z;

int n, m, tots, s[N << 1];

inline void adde(int u, int v) {
  e[u].push_back(v); e[v].push_back(u);
}

inline void addr(int u, int v) {
  r[u].push_back(v); r[v].push_back(u);
}

int f[N], d[N], sz[N], son[N];

void dfs1(int u) {
  sz[u] = 1;
  for (int i = e[u].size() - 1, v; ~i; --i)
    if ((v = e[u][i]) != f[u]) {
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
  for (int i = e[u].size() - 1, v; ~i; --i)
    if ((v = e[u][i]) != f[u] && v != son[u]) dfs2(v);
  ed_dfn[u] = cnt;
}

inline int lca(int u, int v) {
  while (topf[u] != topf[v]) {
    if (d[topf[u]] < d[topf[v]]) swap(u, v);
    u = f[topf[u]];
  }
  return d[u] < d[v] ? u : v;
}

int top, stk[N];

inline bool cmp(int u, int v) {return dfn[u] < dfn[v];}

bool sp[N];

ll S, ans1, ans2, ans3, g[N], h[N];

void dfs(int u, int fa) {
  if (sp[u]) g[u] = 0;
  for (int i = r[u].size() - 1, v, w; ~i; --i)
    if ((v = r[u][i]) != fa) {
      dfs(v, u);
      sz[u] += sz[v];
      w = d[v] - d[u];
      ans1 += 1ll * sz[v] * (S - sz[v]) * w;
      ans2 = min(ans2, g[v] + g[u] + w);
      g[u] = min(g[u], g[v] + w);
      ans3 = max(ans3, h[v] + h[u] + w);
      h[u] = max(h[u], h[v] + w);
    }
}

inline void work() {
  S = tots = rd(); top = 0;
  for (int i = 1; i <= tots; ++i) {
    s[i] = rd(); sp[s[i]] = 1; sz[s[i]] = 1;
  }
  sort(s + 1, s + 1 + tots, cmp);
  for (int i = 2, lim = tots; i <= lim; ++i) s[++tots] = lca(s[i - 1], s[i]);
  sort(s + 1, s + 1 + tots, cmp);
  tots = unique(s + 1, s + 1 + tots) - s - 1;
  for (int i=  1; i <= tots; ++i) r[s[i]] = z;
  for (int i = 1, u; i <= tots; ++i) {
    u = s[i]; g[u] = inf; h[u] = 0;
    while (top && ed_dfn[stk[top]] < dfn[u]) --top;
    stk[++top] = u;
    if (top >= 2) addr(stk[top - 1], stk[top]);
  }
  ans1 = ans3 = 0; ans2 = inf;
  dfs(s[1], 0);
  printf("%lld %lld %lld\n", ans1, ans2, ans3);
  for (int i = 1; i <= tots; ++i) {sp[s[i]] = 0; sz[s[i]] = 0;}
}

int main() {
  n = rd();
  for (int i = 1; i < n; ++i) adde(rd(), rd());
  d[1] = 1; dfs1(1); dfs2(1);
  m = rd();
  for (int i = 1; i <= n; ++i) sz[i] = 0;
  while (m--) work();
  return 0;
}

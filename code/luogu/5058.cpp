#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 2005
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

int n, u, v, stk[N], top;

vector<int> e[N], r[N];

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

int f[N], d[N];

void dfs(int u) {
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != f[u]) {
      f[v] = u; d[v] = d[u] + 1; dfs(v);
    }
}

inline int lca(int u, int v) {
  int ans = 2000000000;
  if (d[u] < d[v]) swap(u, v);
  while (d[u] > d[v]) {
    u = f[u];
    if (u != v) ans = min(ans, u);
  }
  while (u != v) {
    u = f[u]; v = f[v];
    ans = min(ans, min(u, v));
  }
  return ans;
}

int main() {
  tot = n = rd();
  while(1) {
    u = rd(); v = rd();
    if (!u && !v) break;
    adde(u, v);
  }
  tarjan(1); d[1] = 1; dfs(1);
  int l = lca(rd(), rd());
  if (l > n) puts("No solution");
  else printf("%d\n", l);
  return 0;
}

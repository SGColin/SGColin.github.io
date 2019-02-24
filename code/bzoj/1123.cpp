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

void wt(ll x, bool f) {
  if (!x && f) return;
  wt(x / 10, 1);
  putchar('0' + x % 10);
  if (!f) putchar('\n');
}

ll ans[N];

int n, m, stk[N], top;

vector<int> e[N], r[N];

inline void adde(int u, int v) {
  e[u].push_back(v); e[v].push_back(u);
}

inline void addr(int u, int v) {
  r[u].push_back(v); r[v].push_back(u);
}

int tot, cnt, dfn[N], low[N], sz[N];

void tarjan(int u) {
  stk[++top] = u;
  dfn[u] = low[u] = ++cnt;
  for (int i = e[u].size() - 1, v; ~i; --i)
    if (!dfn[v = e[u][i]]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if (dfn[u] <= low[v]) {
        ++tot;
        addr(tot, u);
        int tmp;
        do {
          tmp = stk[top--];
          addr(tot, tmp);
        } while(tmp != v);
      }
    }
    else low[u] = min(low[u], dfn[v]);
}

void dfs(int u, int fa) {
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != fa) {
      dfs(v, u);
      ans[u] += 2ll * sz[u] * sz[v];
      sz[u] += sz[v];
    }
  sz[u] += (u <= n);
  ans[u] += 2ll * (sz[u] - 1) * (n - sz[u]);
}

int main() {
  tot = n = rd(); m = rd();
  for (int i = 1; i <= m; ++i) adde(rd(), rd());
  tarjan(1); dfs(1, 0);
  for (int i = 1; i <= n; ++i) wt(ans[i] + 2 * (n - 1), 0);
  return 0;
}

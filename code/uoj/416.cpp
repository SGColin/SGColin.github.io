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

ll ans;

int n, m, stk[N], top, w[N];

vector<int> e[N], r[N];

inline void adde(int u, int v) {
  e[u].push_back(v); e[v].push_back(u);
}

inline void addr(int u, int v) {
  r[u].push_back(v); r[v].push_back(u);
}

bool vis[N];

int totn, tot, cnt, dfn[N], low[N], sz[N];

void tarjan(int u) {
  vis[u] = 1; ++totn;
  stk[++top] = u;
  dfn[u] = low[u] = ++cnt;
  for (int i = e[u].size() - 1, v, tmp; ~i; --i)
    if (!dfn[v = e[u][i]]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
      if (dfn[u] <= low[v]) {
        w[++tot] = 1;
        addr(tot, u);
        do {
          ++w[tot];
          tmp = stk[top--];
          addr(tot, tmp);
        } while(tmp != v);
      }
    }
    else low[u] = min(low[u], dfn[v]);
}

void dfs(int u, int fa) {
  ll tmp = 0;
  sz[u] = (u <= n);
  for (int i = r[u].size() - 1, v; ~i; --i)
    if ((v = r[u][i]) != fa) {
      dfs(v, u);
      tmp += 2ll * sz[u] * sz[v];
      sz[u] += sz[v];
    }
  ans += (tmp + 2ll * sz[u] * (totn - sz[u])) * w[u];
}

int main() {
  tot = n = rd(); m = rd();
  for (int i = 1; i <= m; ++i) adde(rd(), rd());
  for (int i = 1; i <= n; ++i) w[i] = -1;
  for (int i = 1; i <= n; ++i)
    if (!vis[i]) {totn = 0; tarjan(i); dfs(i, 0);}
  printf("%lld\n", ans);
  return 0;
}

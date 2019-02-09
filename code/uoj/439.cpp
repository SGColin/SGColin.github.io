#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 5005
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

vector<int> son[N], z;

bool c[N << 1], nw[N << 1];

int n, m, tot = 1, hd[N];

int ptr, ans[N], deg[N], stk[N];

struct edge{
  int to, nxt;
} e[N << 1];

inline void add(int u, int v) {
  ++deg[u]; ++deg[v];
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

bool in[N];

queue<int> q;

inline void toposort() {
  for (int i = 1; i <= n; ++i)
    if (deg[i] == 1) in[i] = 1, q.push(i);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = hd[u], v; i; i = e[i].nxt) {
      --deg[v = e[i].to];
      c[i] = c[i ^ 1] = 1;
      if (deg[v] <= 1 && !in[v]) in[v] = 1, q.push(v);
    }
  }
}

void dfs1(int u, int fa) {
  son[u] = z;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa && !nw[i]) {
      son[u].push_back(v); dfs1(v, u);
    }
  sort(son[u].begin(), son[u].end());
}

void dfs2(int u) {
  stk[++ptr] = u;
  for (int i = 0, lim = son[u].size(); i < lim; ++i) dfs2(son[u][i]);
}

inline void check() {
  bool fl = 0;
  for (int i = 1; i <= n; ++i) {
    if (stk[i] < ans[i]) {
      fl = 1; break;
    }
    if (stk[i] > ans[i]) break;
  }
  if (fl) for (int i = 1; i <= n; ++i) ans[i] = stk[i];
}

int main() {
  n = rd(); m = rd();
  for (int i = 1; i <= m; ++i) add(rd(), rd());
  if (m == n - 1) {
    dfs1(1, 0); dfs2(1);
    for (int i = 1; i <= n; ++i) printf("%d ", stk[i]);
    return 0;
  }
  toposort();
  ans[1] = n + 1;
  for (int i = 2; i <= tot; i += 2)
    if (!c[i]) {
      nw[i] = nw[i ^ 1] = 1;
      dfs1(1, 0);
      ptr = 0; dfs2(1);
      nw[i] = nw[i ^ 1] = 0;
      check();
    }
  for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
  return 0;
}

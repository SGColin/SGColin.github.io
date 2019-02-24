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

int n, m, k, tot, hd[N], s[N];

struct edge{
  int to, nxt, w;
} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v;
  e[tot].nxt = hd[u]; hd[u] = tot;
  e[tot].w = e[tot + 1].w = rd();
  e[++tot].to = u;
  e[tot].nxt = hd[v]; hd[v] = tot;
}

inline void addx(int u, int v) {
  e[++tot].to = v;
  e[tot].nxt = hd[u]; hd[u] = tot;
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

int cnt, dfn[N], topf[N];

void dfs2(int u, int fa) {
  dfn[u] = ++cnt;
  if (!topf[u]) topf[u] = u;
  if (son[u]) topf[son[u]] = topf[u], dfs2(son[u], u);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa && v != son[u]) dfs2(v, u);
}

inline int lca(int u, int v) {
  while (topf[u] != topf[v]) {
    if (d[topf[u]] < d[topf[v]]) swap(u, v);
    u = f[topf[u]];
  }
  return d[u] < d[v] ? u : v;
}

int stk[N], top;

inline bool cmp(int x, int y) {return dfn[x] < dfn[y];}

inline void insert(int u) {
  if (top == 1) {stk[++top] = u; return;}
  int l = lca(u, stk[top]);
  if (l == stk[top]) return;
  while (top > 1 && dfn[stk[top - 1]] >= dfn[l]) {
    addx(stk[top - 1], stk[top]); --top;
  }
  if (l != stk[top]) addx(l, stk[top]), stk[top] = l;
  stk[++top] = u;
}

ll dfs(int u) {
  if (!hd[u]) return mn[u];
  ll sum = 0;
  for (int i = hd[u]; i; i = e[i].nxt) sum += dfs(e[i].to);
  hd[u] = 0;
  return min(sum, mn[u]);
}

inline void work() {
  k = rd();
  top = tot = 0;
  for (int i = 1; i <= k; ++i) s[i] = rd();
  sort(s + 1, s + 1 + k, cmp);
  stk[++top] = 1;
  for (int i = 1; i <= k; ++i) insert(s[i]);
  while(--top) addx(stk[top], stk[top + 1]);
  printf("%lld\n", dfs(1));
}

int main() {
  n = rd();
  for (int i = 1; i < n; ++i) add(rd(), rd());
  d[1] = 1; mn[1] = 1ll << 60;
  dfs1(1, 0); dfs2(1, 0);
  for (int i = 1; i <= n; ++i) hd[i] = 0;
  m = rd();
  while (m--) work();
  return 0;
}

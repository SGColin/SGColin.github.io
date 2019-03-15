#include <cmath>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 300005
#define mod 998244353
using namespace std;

inline int rd() {
  int x = 0;
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48);
    c = getchar();
  }
  return x;
}

inline int mo(int x) {
  if (x < 0) x += mod;
  return x >= mod ? x - mod : x;
}

int n, m, qtot, tot, hd[N], s[N];

struct E{int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

int fa[N], dep[N], son[N], sz[N];

void dfs1(int u, int fafa) {
  sz[u] = 1;
  fa[u] = fafa;
  dep[u] = dep[fa[u]] + 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa[u]) {
      dfs1(v, u); sz[u] += sz[v];
      if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

int cnt, dfn[N], topfa[N];

void dfs2(int u, int tptp) {
  dfn[u] = ++cnt;
  topfa[u] = tptp;
  if (son[u]) dfs2(son[u], tptp);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa[u] && v != son[u]) dfs2(v, v);
}

bool vis[N];

int f[N][20];

queue<int> q;

inline void bfs(){
  q.push(1); vis[1] = 1;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = hd[u], v; i; i = e[i].nxt)
      if (!vis[v = e[i].to]) {
        vis[v] = 1; f[v][0] = u;
        for (int j = 1; j < 20; ++j) f[v][j] = f[f[v][j - 1]][j - 1];
        q.push(v);
      }
  }
}

int lca(int u, int v) {
  while (topfa[u] != topfa[v]) {
    if (dep[topfa[u]] < dep[topfa[v]]) swap(u, v);
    u = fa[topfa[u]];
  }
  return dep[u] < dep[v] ? u : v;
}

int lstson(int u, int v) {
  if (u == v) return 0;
  while (topfa[u] != topfa[v]) {
    if (fa[topfa[u]] == v) return topfa[u];
    u = fa[topfa[u]];
  }
  return son[v];
}

inline int anc(int u, int len) {
  for (int i = 19; ~i; --i)
    if (len >= (1 << i)) {len -= (1 << i); u = f[u][i];}
  return u;
}

inline int dis(int u, int v) {
  int l = lca(u, v);
  return dep[u] + dep[v] - dep[l] * 2;
}

bool use[N];

int stk[N], top;

inline void work() {
  m = rd();
  for (int i = 1; i <= m; ++i) s[i] = rd();
  if (m == 1) {printf("%d\n", n); return;}
  int ans1, ans2, mx = 0;
  for (int i = 2, d; i <= m; ++i) {
    d = dis(s[i], s[1]);
    if (d > mx) mx = d, ans1 = s[i];
  }
  mx = 0;
  for (int i = 1, d; i <= m; ++i) {
    d = dis(s[i], ans1);
    if (d > mx) mx = d, ans2 = s[i];
  }
  if (mx & 1) {puts("0"); return;}
  int l = lca(ans1, ans2);
  int len1 = dep[ans1] - dep[l];
  int len2 = dep[ans2] - dep[l];
  if (len1 < len2) swap(ans1, ans2);
  int mid = anc(ans1, mx / 2);
  for (int i = 1; i <= m; ++i)
    if (dis(s[i], mid) != mx / 2) {puts("0"); return;}
  top = 0;
  int del = 0, fl = 0;
  for (int i = 1, lsts; i <= m; ++i)
    if (lca(s[i], mid) == mid) {
      if (!use[lsts = lstson(s[i], mid)]) {
        use[lsts] = 1;
        del += sz[lsts];
        stk[++top] = lsts;
      }
    } else fl = 1;
  printf("%d\n", (fl ? sz[mid] : n) - del);
  for (int i = 1; i <= top; ++i) use[stk[i]] = 0;
}

int main() {
  n = rd(); qtot = rd();
  for (int i = 1; i < n; ++i) add(rd(), rd());
  dfs1(1, 0); dfs2(1, 1); bfs();
  while (qtot--) work();
  return 0;
}

#include <bits/stdc++.h>
#define N 40005
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

bool vis[N];

int n, m, tot, hd[N], sz[N];

int mx, rt, ans, totn, dis[N], s[N];

struct edge{int to, nxt, w;} e[N << 1];

inline void add(int u, int v, int w) {
  e[++tot].to = v; e[tot].w = w;
  e[tot].nxt = hd[u]; hd[u] = tot;
}

inline void getroot(int u, int fa) {
  sz[u] = 1;
  int mxs = 0;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa && !vis[v]) {
      getroot(v, u);
      sz[u] += sz[v];
      mxs = max(mxs, sz[v]);
    }
  mxs = max(mxs, totn - sz[u]);
  if (mxs < mx) mx = mxs, rt = u;
}

inline void dfs(int u, int fa) {
  s[++s[0]] = dis[u];
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa && !vis[v]) {
      dis[v] = dis[u] + e[i].w; dfs(v, u);
    }
}

inline void calc(int u, int val, int o) {
  dis[u] = val;
  s[0] = 0; dfs(u, 0);
  sort(s + 1, s + 1 + s[0]);
  int l = 1, r = s[0];
  while (l < r) {
    while (s[l] + s[r] > m && l < r) --r;
    ans += (r - l) * o; ++l;
  }
}

void work(int u) {
  vis[u] = 1;
  calc(u, 0, 1);
  for (int i = hd[u], v; i; i = e[i].nxt)
    if (!vis[v = e[i].to]){
      calc(v, e[i].w, -1);
      mx = totn = sz[v];
      getroot(v, 0); work(v);
    }
}

int main() {
  n = mx = totn = rd();
  for (int i = 1; i <= n; ++i) hd[i] = 0;
  for (int i = 1, u, v, w; i < n; ++i) {
    u = rd(); v = rd(); w = rd();
    add(u, v, w); add(v, u, w);
  }
  m = rd();
  getroot(1, 0);
  work(rt);
  printf("%d\n", ans);
  return 0;
}

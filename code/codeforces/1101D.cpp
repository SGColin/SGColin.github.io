#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200010
#define gc getchar
#define rg register
using namespace std;

inline int rd() {
  rg int x = 0;
  rg bool f = 0;
  rg char c = gc();
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

int mindiv[N], prm[N];

inline void liner_shaker() {
  for (rg int i = 2; i < N; ++i) {
    if (!mindiv[i]) prm[++prm[0]] = mindiv[i] = i;
    for (rg int j = 1, k; j <= prm[0] && (k = i * prm[j]) < N; ++j) {
      mindiv[k] = prm[j]; if (i % prm[j] == 0) break;
    }
  }
}

vector<int> s[N];

int n, w[N], f[N], vis[N];

int ans = 0, mx, tot, hd[N];

struct edge {
  int to, nxt;
} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

void dfs(int u, int t) {
  f[u] = 0; vis[u] = t;
  for (rg int i = hd[u], v; i; i = e[i].nxt)
    if(vis[v = e[i].to] != t) {
      if(w[v] % t != 0) continue;
      dfs(v, t);
      ans = max(ans, f[u] + f[v] + 1);
      f[u] = max(f[u], f[v] + 1);
    }
}

int main() {
  n = rd();
  liner_shaker();
  for (rg int i = 1, x, tmp; i <= n; ++i) {
    x = w[i] = rd();
    mx = max(mx, x);
    while (x != 1) {
      s[mindiv[x]].push_back(i);
      tmp = mindiv[x];
      while(mindiv[x] == tmp) x /= mindiv[x];
    }
  }
  if (mx == 1) {puts("0"); return 0;}
  for (rg int i = 1; i < n; ++i) add(rd(), rd());
  for (rg int i = 1; i <= prm[0]; ++i)
    for (rg int j = s[prm[i]].size() - 1; ~j; --j)
      if (vis[s[prm[i]][j]] != prm[i]) dfs(s[prm[i]][j], prm[i]);
  printf("%d\n", ans + 1);
  return 0;
}

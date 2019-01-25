#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100005
#define gc getchar
#define rg register
#define inf 2000000000000000000ll
using namespace std;
typedef long long ll;

inline ll rd() {
  rg ll x = 0;
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

ll S, w[N], d[N];

int L, n, t, ans, tot, hd[N], f[N][20], len[N];

struct edge{int to, nxt;} e[N<<1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

inline int find(int u) {
  ll rem = S;
  int res = 0;
  for (rg int i = t; ~i; --i)
    if (d[u] - d[f[u][i]] <= rem) {
      rem -= d[u] - d[f[u][i]];
      res += (1 << i); u = f[u][i];
    }
  return res - 1;
}

void dfs1(int u, int fa, int k) {
  for (rg int i = hd[u], v; i; i = e[i].nxt)
    if((v = e[i].to) != fa) {
      d[v] = d[u] + w[v]; f[v][0] = u;
      for (rg int j = 1; j <= t; ++j) f[v][j] = f[f[v][j-1]][j-1];
      len[v] = (d[v] <= S ? k : find(v));
      len[v] = min(len[v], L); dfs1(v, u, k + 1);
    }
}

int dfs2(int u, int fa) {
  int res = -1;
  for (rg int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) res = max(res, dfs2(v, u) - 1);
  if (res >= 0) return res;
  ++ans; return len[u];
}

int main() {
  t = log2(n = rd());
  L =rd() - 1; S = rd();
  for (rg int i = 1; i <= n; ++i){
    w[i] = rd();
    if (w[i] > S) {puts("-1"); return 0;}
  }
  for (rg int i = 2; i <= n; ++i) add(i, rd());
  d[0] = -inf;
  d[1] = w[1]; len[1] = 1;
  dfs1(1, 0, 1); dfs2(1, 0);
  printf("%d\n", ans);
  return 0;
}

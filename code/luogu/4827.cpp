#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 155
#define N 50005
#define mod 10007
#define gc getchar
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

int n, m, tot, hd[N];

int fac[M] = {1}, s[M][M] = {1}, f[N][M], g[N][M];

struct edge{int to, nxt;} e[N << 1];

inline void add(int u, int v) {
  e[++tot].to = v; e[tot].nxt = hd[u]; hd[u] = tot;
  e[++tot].to = u; e[tot].nxt = hd[v]; hd[v] = tot;
}

void dfs1(int u, int fa) {
  f[u][0] = 1;
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) {
      dfs1(v, u);
      f[u][0] = (f[u][0] + f[v][0]) % mod;
      for (int j = 1; j <= m; ++j)
        f[u][j] = (f[u][j] + f[v][j - 1] + f[v][j]) % mod;
    }
}

void dfs2(int u, int fa) {
  if (fa) {
    g[u][0] = n - f[u][0];
    for (int j = 1; j <= m; ++j) {
      g[u][j] = (g[fa][j - 1] + g[fa][j] + f[fa][j - 1] + f[fa][j]) % mod;
      g[u][j] = ((g[u][j] - f[u][j] - 2 * f[u][j - 1] - f[u][j - 2]) % mod + mod)% mod;
    }
  }
  for (int i = hd[u], v; i; i = e[i].nxt)
    if ((v = e[i].to) != fa) dfs2(v, u);
}

int main() {
  n = rd(); m = rd();
  for (int i = 1; i < n; ++i) add(rd(), rd());
  for (int i = 1; i <= m; ++i)
    for (int j = 1; j <= i; ++j)
      s[i][j] = (s[i - 1][j] * j + s[i - 1][j - 1]) % mod;
  for (int i = 1; i <= m; ++i) fac[i] = fac[i - 1] * i % mod;
  dfs1(1, 0); dfs2(1, 0);
  for (int i = 1; i <= n; ++i) {
    int ans = 0;
    for (int j = 1; j <= m; ++j)
      ans = (ans + s[m][j] * fac[j] % mod * (f[i][j] + g[i][j])) % mod;
    printf("%d\n", ans);
  }
  return 0;
}

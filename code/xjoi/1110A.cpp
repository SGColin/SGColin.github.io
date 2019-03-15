#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 7005
#define mod 998244353
using namespace std;

inline int rd() {
  int x = 0;
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = getchar();
  }
  return x;
}

inline int mo(int x) {return x >= mod ? x - mod : x;}

int n, m, r[N], f[N][N];

int dfs(int u) {
    int tmp, tot, tots;
    f[u][1] = 1;
    for (int v = u + 1; v <= r[u]; v = r[v] + 1) {
      tot = v - u;
      tots = dfs(v);
      for (int j = tot - 1; j; --j)
        f[u][j] = mo(f[u][j] + f[u][j + 1]);
      for (int j = tot; j; --j) {
        tmp = f[u][j]; f[u][j] = 0;
        for (int k = 1; k <= tots; k++)
          f[u][j + k] = mo(f[u][j + k] + 1ll * f[v][k] * tmp % mod);
      }
    }
    return r[u] - u + 1;
}

int main() {
  n = rd(); m = rd();
  for (int i = 1, x, y; i <= m; ++i) {
    x = rd(); y = rd();
    r[x] = max(r[x], y);
  }
  for (int i = n; i; --i) {
    r[i] = max(r[i], i);
    for (int j = i + 1; j <= r[i]; ++j) r[i] = max(r[i], r[j]);
  }
  r[1] = n; dfs(1);
  int ans = 0;
  for (int i = 1; i <= n; ++i) ans = mo(ans + f[1][i]);
  printf("%d\n", ans);
  return 0;
}

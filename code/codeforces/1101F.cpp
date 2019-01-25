#include <set>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 401
#define gc getchar
#define rg register
using namespace std;
typedef long long ll;

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

int n, m, dis[N], f[N][N][N];

int main() {
  n = rd(); m = rd();
  memset(f, 0x3f, sizeof f);
  for (rg int i = 1; i <= n; ++i) dis[i] = rd();
  for (rg int i = 1; i <= n; ++i)
    for (rg int j = 0; j <= n; ++j) f[i][i][j] = 0;
  for (rg int k = 1; k <= n; ++k)
    for (rg int l = 1; l <= n; ++l) {
      int ptr = l, now, nxt;
      for (rg int r = l + 1; r <= n; ++r) {
        now = max(f[l][ptr][k - 1], dis[r] - dis[ptr]);
        nxt = max(f[l][ptr + 1][k - 1], dis[r] - dis[ptr + 1]);
        while (ptr < r - 1 && now > nxt) {
          ++ptr; now = nxt;
          nxt = max(f[l][ptr + 1][k - 1], dis[r] - dis[ptr + 1]);
        }
        f[l][r][k] = now;
      }
    }
  ll ans = 0;
  for (rg int i = 1, l, r, c, t; i <= m; ++i) {
    l = rd(); r = rd(); c = rd(); t = rd() + 1;
    ans = max(ans, 1ll * f[l][r][min(t, r - l)] * c);
  }
  printf("%I64d\n", ans);
  return 0;
}

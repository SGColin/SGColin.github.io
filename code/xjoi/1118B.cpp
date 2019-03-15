#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define M 513
#define gc getchar
#define mod 998244353
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

int n, ans, f[M][M];

const int lim = (1 << 9) - 1;

inline int mo(int x) {return x >= mod ? x - mod : x;}

int main() {
  n = rd();
  for (int i = 1, x, nw, a, b; i <= n; ++i) {
    x = rd(); nw = 0;
    a = (x >> 9); b = (x & lim);
    for (int j = a; j <= lim; j = ((j + 1) | a)) nw = mo(nw + f[j][b]);
    ans = mo(ans + nw); ++nw;
    for (int j = b; ; j = ((j - 1) & b)) {
      f[a][j] = mo(f[a][j] + nw);
      if (!j) break;
    }
  }
  printf("%d\n", ans);
  return 0;
}

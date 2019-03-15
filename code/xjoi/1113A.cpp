#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000000;

const int N = 11, M = 262145;

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

int n, m, c, f[N][M], sum[M];

inline void work() {
  n = rd(); m = rd();
  int lim = (1 << m) - 1;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= lim; ++j) f[i][j] = 0;
  for (int i = 0; i <= lim; ++i) sum[i] = 1;
  for (int i = 1, c; i <= n; ++i) {
    c = rd();
    for (int s = 0; s <= lim; ++s)
      if (s % c) f[i][s] = sum[lim ^ s];
    for (int j = 0; j <= lim; ++j) sum[j] = f[i][j];
    for (int j = 0; j <= 18; ++j)
      for (int k = 0; k <= lim; ++k)
        if (k & (1 << j)) sum[k] = mo(sum[k] + sum[k ^ (1 << j)]);
  }
  int ans = 0;
  for (int s = 0; s <= lim; ++s) ans = mo(ans + f[n][s]);
  printf("%d\n", ans);
}

int main() {
  int t = rd();
  while (t--) work();
  return 0;
}

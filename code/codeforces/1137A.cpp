#include <bits/stdc++.h>
#define N 1005
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

int n, m, a[N][N], low[N][N], up[N][N], s[N], low1[N][N], up1[N][N];

int main() {
  n = rd(); m = rd();
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) a[i][j] = rd();
  for (int i = 1, tot; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) s[j] = a[i][j];
    sort(s + 1, s + 1 + m);
    tot = unique(s + 1, s + 1 + m) - s - 1;
    for (int j = 1; j <= m; ++j) {
      low[i][j] = lower_bound(s + 1, s + 1 + tot, a[i][j]) - s;
      up[i][j] = tot - low[i][j];
    }
  }
  for (int i = 1, tot; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) s[j] = a[j][i];
    sort(s + 1, s + 1 + n);
    tot = unique(s + 1, s + 1 + n) - s - 1;
    for (int j = 1; j <= n; ++j) {
      low1[j][i] = lower_bound(s + 1, s + 1 + tot, a[j][i]) - s;
      up1[j][i] = tot - low1[j][i];
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j)
      printf("%d ", max(low[i][j], low1[i][j]) + max(up[i][j], up1[i][j]));
    puts("");
  }
  return 0;
}

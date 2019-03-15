#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 200005
#define gc getchar
using namespace std;

char ss[N];

int len, s[N], sa[N], rk[N], t1[N], t2[N], bkt[N], h[N], st[N][18];

void da(int n, int m) {
  s[n++] = 0;
  int *x = t1, *y = t2;
  for (int i = 0; i < m; ++i) bkt[i] = 0;
  for (int i = 0; i < n; ++i) ++bkt[x[i] = s[i]];
  for (int i = 1; i < m; ++i) bkt[i] += bkt[i - 1];
  for (int i = n - 1; ~i; --i) sa[--bkt[x[i]]] = i;
  for (int k = 1, p = 0; k <= n && p < n; k <<= 1, m = p) {
    p = 0;
    for (int i = n - k; i < n; ++i) y[p++] = i;
    for (int i = 0; i < n; ++i) if (sa[i] >= k) y[p++] = sa[i] - k;
    for (int i = 0; i < m; ++i) bkt[i] = 0;
    for (int i = 0; i < n; ++i) ++bkt[x[y[i]]];
    for (int i = 1; i < m; ++i) bkt[i] += bkt[i - 1];
    for (int i = n - 1; ~i; --i) sa[--bkt[x[y[i]]]] = y[i];
    swap(x, y); x[sa[0]] = 0; p = 1;
    for (int i = 1; i < n; ++i)
      x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p - 1 : p++;
  }
  --n; h[0] = 0;
  for (int i = 0; i < n; ++i) sa[i] = sa[i + 1];
  for (int i = 0; i < n; ++i) rk[sa[i]] = i;
  for (int i = 0, p = 0; i < n; ++i) {
    if (!rk[i]) continue;
    if (p) --p;
    while (s[i + p] == s[sa[rk[i] - 1] + p]) ++p;
    h[rk[i]] = p;
  }
}

inline int mn(int x, int y) {return h[x] < h[y] ? x : y;}

inline void build(int n) {
  for (int i = 0; i < n; ++i) st[i][0] = i;
  for (int j = 1; (1 << j) <= n; ++j)
    for (int i = 0; i + (1 << j) - 1 < n; ++i)
      st[i][j] = mn(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}

inline int query(int l, int r) {
  int t = log2(r - l + 1);
  return mn(st[l][t], st[r - (1 << t) + 1][t]);
}

inline double sqr(const double &x) {return x * x;}

inline double solve(int l, int r) {
  if (l == r) return len - sa[l];
  int p = query(l + 1, r);
  double lans = solve(l, p - 1), rans = solve(p, r);
  return (lans * rans - sqr(h[p])) / (lans + rans - 2 * h[p]);
}

int main() {
  scanf("%s", ss);
  len = strlen(ss);
  for (int i = 0; i < len; ++i) s[i] = ss[i] - 'a' + 1, h[i] = 0;
  da(len, 256); build(len);
  printf("%.6lf\n", solve(0, len - 1));
  return 0;
}

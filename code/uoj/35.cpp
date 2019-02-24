#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100005
#define gc getchar
using namespace std;

char ss[N];

int n, m = 256, s[N];

int sa[N], rk[N], h[N], bkt[N], t1[N], t2[N];

void da() {
  s[n++] = 0;
  int *x = t1, *y = t2;
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

int main() {
  scanf("%s", ss);
  n = strlen(ss);
  for (int i = 0; i < n; ++i) s[i] = ss[i] - 'a' + 1;
  da();
  for (int i = 0; i < n; ++i) printf("%d ", sa[i] + 1);
  puts("");
  for (int i = 1; i < n; ++i) printf("%d ", h[i]);
  return 0;
}

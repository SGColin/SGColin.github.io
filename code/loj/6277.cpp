#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define gc getchar
using namespace std;

inline int rd() {
  int x = 0;
  bool f = 0;
  char c = gc();
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

int n, m, s[50005], bl[50005], tg[305];

int main() {
  freopen("1.in","r",stdin);
  freopen("1.out","w",stdout);
  n = rd();
  m = sqrt(n) + 1;
  for (int i = 1; i <= n; ++i)
    s[i] = rd(), bl[i] = (i - 1) / m + 1;
  for (int i = 1, op, l, r, c; i <= n; ++i) {
    op = rd(); l = rd();
    r = rd(); c = rd();
    if (op) printf("%d\n", s[r] + tg[bl[r]]);
    if (!op) {
      if (bl[l] == bl[r]) {
        for (int j = l; j <= r; ++j) s[j] += c;
        continue;
      }
      int lim = bl[l] * m;
      for (int j = l; j <= lim; ++j) s[j] += c;
      for (int j = bl[l] + 1; j < bl[r]; ++j) tg[j] += c;
      for (int j = (bl[r] - 1) * m + 1; j <= r; ++j) s[j] += c;
    }
  }
  return 0;
}

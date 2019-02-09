#include <cmath>
#include <bitset>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 105
#define M 25005
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

bool f[M];

int n, ans, a[N];

inline void work() {
  n = rd();
  for (int i = 1; i <= n; ++i) a[i] = rd();
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= a[n]; ++i) f[i] = 0;
  f[0] = 1; ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (f[a[i]]) continue;
    ++ans;
    for (int j = a[i]; j <= a[n]; ++j) f[j] |= f[j - a[i]];
  }
  printf("%d\n", ans);
}

int main() {
  int t = rd();
  while (t--) work();
  return 0;
}

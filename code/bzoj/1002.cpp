#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 105
using namespace std;

struct Bigint {
  int len, a[N];
} f[N];

void calc(Bigint &res, const Bigint &x, const Bigint &y) {
  res = x;
  int tmp = 0;
  for (int i = 1; i <= res.len; ++i) {
    tmp += res.a[i] * 3;
    res.a[i] = tmp % 10; tmp /= 10;
  }
  while (tmp) {
    res.a[++res.len] = tmp % 10;
    tmp /= 10;
  }
  res.a[1] += 2;
  for (int i = 1; i <= res.len; ++i) {
    res.a[i] -= y.a[i];
    if (res.a[i] < 0) res.a[i] += 10, --res.a[i + 1];
  }
  while (res.a[res.len] == 0) --res.len;
}

int main() {
  int n;
  scanf("%d", &n);
  f[1].len = f[1].a[1] = 1;
  for (int i = 2; i <= n; ++i) calc(f[i], f[i - 1], f[i - 2]);
  for (int i = f[n].len; i; --i) putchar('0' + f[n].a[i]);
  return 0;
}

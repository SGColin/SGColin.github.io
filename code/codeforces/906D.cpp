#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100010
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

ll p[50];

int n, m, l, r, a[N];

inline ll qpow(ll x, ll t, ll mod) {
  ll res = 1;
  while (t) {
    if (t & 1) res *= x %= mod;
    x *= x;
  }
  return res;
}

void dfs(int p) {
  if (p == ptr || p == r - l + 1) return 0;
  dfs(qpow(a[l + 1], a[r]))
}

inline void work() {
  l = rd(), r = rd();
  dfs(1);
}

inline int getphi(int x) {
  int res = x;
  for (rg int i = 2, lim = sqrt(x); i <= lim; ++i)
    if (x % i == 0) {
      res -= res / i;
      while (x % i == 0) x /= i;
      if (x == 1) return res;
    }
  if (x > 1) res -= res / x;
  return res;
}

int main() {
  n = rd();
  p[0] = rd();
  int ptr = 0;
  while (p[ptr] != 1)
    ++ptr, p[ptr] = getphi(p[ptr - 1]);
  for (rg int i = 1; i <= n; ++i) a[i] = rd();
  m = rd();
  while (m--) work();
  return 0;
}

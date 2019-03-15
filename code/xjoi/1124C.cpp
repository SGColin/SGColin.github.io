#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000005
#define mod 998244353
using namespace std;

int n, m, inv[N], fac[N], ifac[N];

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod; t >>= 1;
  }
  return res;
}

inline int C (int n, int m) {
  return 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
  scanf("%d%d", &n, &m);
  inv[0] = inv[1] = 1;
  fac[0] = fac[1] = 1;
  ifac[0] = ifac[1] = 1;
  for (int i = 2; i < N; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % mod;
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
  }
  int mn = min(n, m), ans = 0;
  for (int i = 1; i <= mn; ++i)
    ans = (ans + 1ll * C(i << 1, i) * C(n + m - (i << 1), n - i)) % mod;
  ans = 1ll * ans * qpow(C(n + m, n), mod - 2) % mod * ifac[2] % mod;
  printf("%d\n", (mn - ans + mod) % mod);
  return 0;
}

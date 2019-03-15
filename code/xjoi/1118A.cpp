#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define N 262145
#define mod 998244353
using namespace std;

int n, m, ans, rev[N], f[N], p[N];

int inv[N], ifac[N], a[N], b[N];

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod; t >>= 1;
  }
  return res;
}

inline int mo(int x) {
  return x >= mod ? x - mod : x;
}

inline int Rev(int n) {
  int len = 1, bit = 0;
  while (len <= n) ++bit, len <<= 1;
  for (int i = 0; i < len; ++i)
    rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (bit - 1)));
  return len;
}

inline void NTT(int *f, int len, int o) {
  for (int i = 0; i < len; ++i)
    if (i > rev[i]) swap(f[i], f[rev[i]]);
  for (int i = 1; i < len; i <<= 1) {
    int wn = qpow(3, (mod - 1) / (i << 1));
    if (o == -1) wn = qpow(wn, mod - 2);
    for (int j = 0; j < len; j += (i << 1)) {
      int w = 1, x, y;
      for (int k = 0; k < i; ++k, w = 1ll * w * wn % mod) {
        x = f[j + k]; y = 1ll * w * f[i + j + k] % mod;
        f[j + k] = mo(x + y); f[i + j + k] = mo(x - y + mod);
      }
    }
  }
  if (o == -1) {
    int invl = qpow(len, mod - 2);
    for (int i = 0; i < len; ++i) f[i] = 1ll * f[i] * invl % mod;
  }
}

int main() {
  scanf("%d", &n);
  inv[0] = inv[1] = 1;
  ifac[0] = ifac[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % mod;
  }
  p[0] = p[1] = 1; p[2] = 1;
  f[0] = f[1] = 0; f[2] = 1;
  for (int i = 3; i <= n; ++i) {
    p[i] = 1ll * p[i - 1] * (i - 1) % mod;
    f[i] = 1ll * (i - 1) * (f[i - 1] + f[i - 2]) % mod;
  }
  int len = Rev(n << 1);
  a[0] = 1;
  a[1] = mod - 1;
  b[1] = n;
  for (int i = 2; i <= n; ++i) {
    a[i] = 1ll * (i & 1 ? mod - 1 : 1) * ifac[i] % mod;
    b[i] = 1ll * i * (qpow(i, n) - 1 + mod) % mod;
    b[i] = 1ll * b[i] * inv[i - 1] % mod * ifac[i] % mod;
  }
  NTT(a, len, 1); NTT(b, len, 1);
  for (int i = 0; i < len; ++i) a[i] = 1ll * a[i] * b[i] % mod;
  NTT(a, len, -1);
  for (int i = 0; i <= n; ++i) ans = mo(ans + 1ll * f[i] * p[i] % mod * a[i] % mod);
  printf("%d\n", ans);
  return 0;
}

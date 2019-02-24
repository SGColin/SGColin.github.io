#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 2100005
#define gc getchar
#define mod 998244353ll
using namespace std;
typedef long long ll;

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

inline ll qpow(ll x, ll t) {
  ll res = 1ll;
  while (t) {
    if (t & 1) res = res * x % mod;
    x = x * x % mod; t >>= 1;
  }
  return res;
}

int n, m, bit, rev[N];

ll l = 1, a[N], b[N];

inline ll mo(ll x) {
  return x >= mod ? x - mod : x;
}

inline void NTT(ll *f, int o) {
  for (int i = 0; i < l; ++i)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int i = 1; i < l; i <<= 1) {
    ll wn = qpow(3, (mod - 1) / (i << 1));
    if (o == -1) wn = qpow(wn, mod - 2);
    for (int j = 0; j < l; j += (i << 1)) {
      ll w = 1, x, y;
      for (int k = 0; k < i; ++k, w = w * wn % mod) {
        x = f[j + k];
        y = w * f[i + j + k] % mod;
        f[i + j + k] = mo(x - y + mod);
        f[j + k] = mo(x + y);
      }
    }
  }
}

int main() {
  n = m = rd();
  char c;
  for (int i = n - 1; ~i; --i) {
    c = gc();
    while (!isdigit(c)) c = gc();
    a[i] = c - '0';
  }
  for (int i = n - 1; ~i; --i) {
    c = gc();
    while (!isdigit(c)) c = gc();
    b[i] = c - '0';
  }
  while (l <= n + m) ++bit, l <<= 1;
  for (int i = 1; i < l; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  NTT(a, 1); NTT(b, 1);
  for (int i = 0; i < l; ++i) a[i] = a[i] * b[i] % mod;
  NTT(a, -1);
  ll inv = qpow(l, mod - 2);
  for (int i = 0; i < l; ++i) a[i] = a[i] * inv % mod;
  ll tot = n + n, rem = 0;
  for (int i = 0; i <= n + m; ++i) {
    a[i] += rem;
    rem = a[i] / 10;
    a[i] = a[i] % 10;
  }
  while (!a[tot] && tot) --tot;
  for (int i = tot; ~i; --i) putchar(a[i] + '0');
  return 0;
}

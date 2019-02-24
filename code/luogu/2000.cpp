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

int l = 1, bit, rev[N];

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

struct Bigint {

  ll len, a[N];

  inline void add() {
    ++a[0];
    int rem = 0;
    for (int i = 0; i <= len; ++i) {
      rem = rem + a[i];
      a[i] = rem % 10; rem = rem / 10;
      if (!rem) break;
    }
    if (rem) a[++len] =rem;
  }

  inline void div() {
    int rem = 0;
    for (int i = len; ~i; --i) {
      rem = rem * 10 + a[i];
      a[i] = rem / 24; rem = rem % 24;
    }
    while (!a[len] && len) --len;
  }

  inline void print() {
    for (int i = len; ~i; --i) putchar('0' + a[i]);
  }

} x, x1, x2, x3;

char s[N];

inline void mul(Bigint &x, Bigint &y) {
  l = 1; bit = 0;
  while (l <= x.len + y.len + 2) ++bit, l <<= 1;
  for (int i = 1; i < l; ++i)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  NTT(x.a, 1); NTT(y.a, 1);
  for (int i = 0; i < l; ++i) x.a[i] = x.a[i] * y.a[i] % mod;
  NTT(x.a, -1);
  ll inv = qpow(l, mod - 2);
  for (int i = 0; i < l; ++i) x.a[i] = x.a[i] * inv % mod;
  ll tot = l, rem = 0;
  for (int i = 0; i <= tot; ++i) {
    rem = rem + x.a[i];
    x.a[i] = rem % 10; rem = rem / 10;
  }
  while (!x.a[tot] && tot) --tot;
  x.len = tot;
}

int main() {
  scanf("%s", s);
  x.len = strlen(s) - 1;
  for (int i = x.len; ~i; --i) x.a[x.len - i] = s[i] - '0';
  x.add();
  x1 = x; x1.add();
  x2 = x1; x2.add();
  x3 = x2; x3.add();
  mul(x, x1); mul(x, x2); mul(x, x3);
  x.div(); x.print();
  return 0;
}

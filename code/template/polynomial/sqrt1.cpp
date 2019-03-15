#include <bits/stdc++.h>
#define N 262145
#define gc getchar
#define mod 998244353
#define inv2 499122177
#define mo(x) (x >= mod ? x - mod : x)
using namespace std;

int rev[N], a[N], b[N], a0[N], b0[N], tmp[N];

inline int rd() {
  int x = 0;
  char c = gc();
  while (!isdigit(c)) c = gc();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = gc();
  }
  return x;
}

void print(int x, bool f) {
  if (!x && f) return;
  print(x / 10, 1);
  putchar('0' + x % 10);
  if (!f) putchar(' ');
}

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod; t >>= 1;
  }
  return res;
}

inline int Rev(int n) {
  int len = 1, bit = 0;
  while (len < n) ++bit, len <<= 1;
  for (int i = 0; i < len; ++i)
    rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (bit - 1)));
  return len;
}

inline void NTT(int *f, int len, int o) {
  for (int i = 1; i < len; ++i)
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

inline void Inv(int *a, int *b, int n) {
  if (n == 1) {b[0] = qpow(a[0], mod - 2); return;}
  Inv(a, b, (n + 1) >> 1);
  int len = Rev(n << 1);
  for (int i = 0; i < n; ++i) tmp[i] = a[i];
  for (int i = n; i < len; ++i) b[i] = tmp[i] = 0;
  NTT(b, len, 1); NTT(tmp, len, 1);
  for (int i = 0; i < len; ++i)
    b[i] = (2ll - 1ll * tmp[i] * b[i] % mod + mod) * b[i] % mod;
  NTT(b, len, -1);
  for (int i = 0; i < len; ++i) tmp[i] = 0;
  for (int i = n; i < len; ++i) b[i] = 0;
}

inline void Sqrt(int *a, int *b, int n) {
  if (n == 1) {b[0] = 1; return;}
  Sqrt(a, b, (n + 1) >> 1);
  Inv(b, b0, n);
  int len = Rev(n << 1);
  for (int i = 0; i < n; ++i) a0[i] = a[i];
  for (int i = n; i < len; ++i) a0[i] = 0;
  NTT(a0, len, 1); NTT(b0, len, 1);
  for (int i = 0; i < len; ++i) a0[i] = 1ll * a0[i] * b0[i] % mod;
  NTT(a0, len, -1);
  for (int i = 0; i < n; ++i) b[i] = 1ll * (b[i] + a0[i]) % mod * inv2 % mod;
  for (int i = n; i < len; ++i) b[i] = 0;
}

int main() {
  int n = rd();
  for (int i = 0; i < n; ++i) a[i] = rd();
  Sqrt(a, b, n);
  for (int i = 0; i < n; ++i) print(b[i], 0);
  return 0;
}
#include <bits/stdc++.h>
#define N 262145
#define gc getchar
#define mod 998244353
#define mo(x) (x >= mod ? x - mod : x)
using namespace std;

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

int a[N], b[N], ar[N], br[N], invb[N];

int rev[N], d[N], r[N], tmp[N];

inline int Rev(int n) {
  int len = 1, bit = 0;
  while (len <= n) ++bit, len <<= 1;
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

inline void Div(int *a, int *b, int n, int m) {
  for (int i = 0; i <= n; ++i) ar[i] = a[n - i];
  for (int i = 0; i <= m; ++i) br[i] = b[m - i];
  for (int i = n - m + 2; i <= n; ++i) ar[i] = 0;
  for (int i = n - m + 2; i <= m; ++i) br[i] = 0;
  Inv(br, invb, n - m + 1);
  int len = Rev((n - m + 1) << 1);
  NTT(ar, len, 1); NTT(invb, len, 1);
  for (int i = 0; i < len; ++i) ar[i] = 1ll * ar[i] * invb[i] % mod;
  NTT(ar, len, -1);
  for (int i = 0; i <= n - m; ++i) tmp[i] = d[i] = ar[n - m - i];
  len = Rev(n << 1);
  for (int i = n - m + 1; i <= len; ++i) tmp[i] = 0;
  NTT(b, len, 1); NTT(tmp, len, 1);
  for (int i = 0; i < len; ++i) b[i] = 1ll * b[i] * tmp[i] % mod;
  NTT(b, len, -1);
  for (int i = 0; i <= m; ++i) r[i] = mo(a[i] - b[i] + mod);
}

int main() {
  int n = rd(), m = rd();
  for (int i = 0; i <= n; ++i) a[i] = rd();
  for (int i = 0; i <= m; ++i) b[i] = rd();
  Div(a, b, n, m);
  for (int i = 0; i <= n - m; ++i) print(d[i], 0);
  puts("");
  for (int i = 0; i < m; ++i) print(r[i], 0);
  return 0;
}

#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 524289
#define mod 998244353
using namespace std;

char s[N];

int n, m, k, ans, A[N], B[N];

int len, res[N], rev[N], a[N], b[N];

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod; t >>= 1;
  }
  return res;
}

inline int mo(int x) {return x >= mod ? x - mod : x;}

inline int trans(char c) {
  if (c == 'Z') return 0;
  if (c == 'P') return 1;
  if (c == 'S') return 2;
  return 3;
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

inline void work(int x) {
  for (int i = 0; i < len; ++i) a[i] = b[i] = 0;
  for (int i = 0, lst = -1; i < n; ++i) {
    if (A[i] == x) lst = i;
    if (i - k > lst) lst = -1;
    a[i] |= (lst != -1);
  }
  for (int i = n - 1, lst = -1; ~i; --i) {
    if (A[i] == x) lst = i;
    if (i + k < lst) lst = -1;
    a[i] |= (lst != -1);
  }
  for (int i = m - 1; ~i; --i) b[m - 1 - i] = (B[i] == x);
  NTT(a, len, 1); NTT(b, len, 1);
  for (int i = 0; i < len; ++i) a[i] = 1ll * a[i] * b[i] % mod;
  NTT(a, len, -1);
  for (int i = 0; i < n; ++i) res[i] = mo(res[i] + a[i]);
}

int main() {
  scanf("%d", &k);
  scanf("%s", s); n = strlen(s);
  for (int i = 0; i < n; ++i) A[i] = trans(s[i]);
  scanf("%s", s); m = strlen(s);
  for (int i = 0; i < m; ++i) B[i] = trans(s[i]);
  if (n < m) {puts("0"); return 0;}
  len = Rev(n + m);
  for (int i = 0; i < 4; ++i) work(i);
  for (int i = 0; i < n; ++i) ans += (res[i] == m);
  printf("%d\n", ans);
  return 0;
}

/*
Author: SGColin
Problem: BZOJ 4175
Algorithm: Suffix Automaton + EGF + polynomial fast pow
*/
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define N 262145
#define mod 1005060097
using namespace std;

int n, m, k, a[N];

namespace SAM {

  char ss[N];

  int ptr, lst, bkt[N], seq[N];

  struct node {
    int fa, sz, mx, tr[26];
  } c[N];

  inline int newnode(int mx, int sz = 0) {
    c[++ptr].mx = mx; c[ptr].sz = sz; return ptr;
  }

  inline void extend(int x) {
    int p = lst;
    int np = newnode(c[p].mx + 1, 1);
    lst = np;
    for (; p && !c[p].tr[x]; p = c[p].fa) c[p].tr[x] = np;
    if (!p) {c[np].fa = 1; return;}
    int q = c[p].tr[x];
    if (c[q].mx == c[p].mx + 1) c[np].fa = q;
    else {
      int nq = newnode(c[p].mx + 1);
      c[nq].fa = c[q].fa;
      for (int i = 0; i < 26; ++i) c[nq].tr[i] = c[q].tr[i];
      c[q].fa = c[np].fa = nq;
      for (; p && c[p].tr[x] == q; p = c[p].fa) c[p].tr[x] = nq;
    }
  }

  inline void build() {
    ptr = lst = 1;
    scanf("%s", ss + 1);
    int len = strlen(ss + 1);
    for (int i = 1; i <= len; ++i) extend(ss[i] - 'a');
    for (int i = 1; i <= ptr; ++i) ++bkt[c[i].mx];
    for (int i = 1; i <= ptr; ++i) bkt[i] += bkt[i - 1];
    for (int i = 1; i <= ptr; ++i) seq[bkt[c[i].mx]--] = i;
    for (int i = ptr; i; --i) c[c[seq[i]].fa].sz += c[seq[i]].sz;
    for (int i = 2; i <= ptr; ++i)
      a[c[i].sz] = (a[c[i].sz] + 1ll * (c[i].mx - c[c[i].fa].mx) * c[i].sz) % mod;
  }

}

namespace Poly {

  int a[N], b[N], c[N], d[N];

  int tmp[N], n, rev[N], w[2][N], mxlen;

  inline int Rev(int n) {
    int len = 1, bit = 0;
    while (len <= n) ++bit, len <<= 1;
    for (int i = 0; i < len; ++i)
      rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (bit - 1)));
    return len;
  }

  inline int mo(int x) {return x >= mod ? x - mod : x;}

  inline int fpow(int x, int t = mod - 2) {
    int res = 1;
    while (t) {
      if (t & 1) res = 1ll * res * x % mod;
      x = 1ll * x * x % mod; t >>= 1;
    }
    return res;
  }

  inline void NTT(int *f, int len, int o) {
    for (int i = 0; i < len; ++i)
      if (i > rev[i]) swap(f[i], f[rev[i]]);
    for (int i = 1; i < len; i <<= 1) {
      int wn = mxlen / (i << 1);
      for (int j = 0; j < len; j += (i << 1)) {
        int nw = 0, x, y;
        for (int k = 0; k < i; ++k, nw += wn) {
          x = f[j + k];
          y = 1ll * w[o][nw] * f[i + j + k] % mod;
          f[j + k] = mo(x + y);
          f[i + j + k] = mo(x - y + mod);
        }
      }
    }
    if (o == 1) {
      int invl = fpow(len);
      for (int i = 0; i < len; ++i) f[i] = 1ll * f[i] * invl % mod;
    }
  }

  inline void Inv(int *a, int *b, int n) {
    if (n == 1) {b[0] = fpow(a[0]); return;}
    Inv(a, b, (n + 1) >> 1);
    int len = Rev(n << 1);
    for (int i = 0; i < n; ++i) tmp[i] = a[i];
    for (int i = n; i < len; ++i) b[i] = tmp[i] = 0;
    NTT(b, len, 0); NTT(tmp, len, 0);
    for (int i = 0; i < len; ++i)
      b[i] = (2ll - 1ll * tmp[i] * b[i] % mod + mod) * b[i] % mod;
    NTT(b, len, 1);
    for (int i = 0; i < len; ++i) tmp[i] = 0;
    for (int i = n; i < len; ++i) b[i] = 0;
  }

  inline void Der(int *a, int n) {
    for (int i = 1; i < n; ++i) a[i - 1] = 1ll * i * a[i] % mod;
    a[n - 1] = 0;
  }

  inline void Int(int *a, int n) {
    for (int i = n; i; --i) a[i] = 1ll * a[i - 1] * fpow(i, mod - 2) % mod;
    a[0] = 0;
  }

  inline void Ln(int *a, int *b, int n) {
    Inv(a, b, n); Der(a, n);
    int len = Rev(n << 1);
    NTT(a, len, 0); NTT(b, len, 0);
    for (int i = 0; i < len; ++i) a[i] = 1ll * a[i] * b[i] % mod;
    NTT(a, len, 1); Int(a, n);
  }

  inline void Exp(int *a, int *b, int n) {
    if (n == 1) {b[0] = 1; return;}
    Exp(a, b, (n + 1) >> 1);
    for (int i = 0; i < n; ++i) d[i] = b[i];
    Ln(b, c, n);
    for (int i=  1; i <= n; ++i) b[i] = mo(mod - b[i] + a[i]);
    b[0] = mo(b[0] + 1);
    int len = Rev(n << 1);
    NTT(b, len, 0); NTT(d, len, 0);
    for (int i = 0; i < len; ++i) b[i] = 1ll * b[i] * d[i] % mod;
    NTT(b, len, 1);
    for (int i = n; i < len; ++i) b[i] = 0;
    for (int i = 0; i < len; ++i) d[i] = 0;
  }

  inline void init() {
    mxlen = (1 << 18);
    w[0][0] = w[1][0] = 1;
    int per = fpow(5, (mod - 1) / mxlen);
    int invper = fpow(per);
    for (int i = 1; i < mxlen; ++i) {
      w[0][i] = 1ll * w[0][i - 1] * per % mod;
      w[1][i] = 1ll * w[1][i - 1] * invper % mod;
    }
  }

  inline int Fpow(int *a, int n, int k) {
    init();
    int B = a[1], invB = fpow(B);
    for (int i = 0; i < n; ++i) a[i] = 1ll * a[i + 1] * invB % mod;
    for (int i = n - 1; i < mxlen; ++i) a[i] = 0;
    Ln(a, b, n);
    for (int i = 0; i < n; ++i) a[i] = 1ll * a[i] * k % mod;
    memset(b, 0, sizeof(b));
    Exp(a, b, n);
    return 1ll * b[m - k] * fpow(B, k) % mod;
  }

}

int main() {
  scanf("%d%d", &k, &m);
  SAM::build();
  printf("%d\n", Poly::Fpow(a, m + 1, k));
  return 0;
}

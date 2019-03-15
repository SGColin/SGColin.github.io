#include <bits/stdc++.h>
#define N 200005
#define M 1000005
#define gc getchar
#define mod 998244353
#define lowbit(x) (x & (-x))
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

inline void print(int x){
  int y = 10, len = 1;
  while (y <= x) {y *= 10; ++len;}
  while (len--) {y /= 10; putchar(x / y + 48); x %= y;}
  putchar('\n');
}

inline int qpow(int x, int t) {
  int res = 1;
  while (t) {
    if (t & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod; t >>= 1;
  }
  return res;
}

int n, m, a[N], pre[N], ans[N];

int mindiv[M], prm[M], inv[M], cnt[M];

inline void calc() {
  inv[0] = inv[1] = 1;
  for (int i = 2; i < M; ++i) {
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    if (!mindiv[i]) mindiv[i] = prm[cnt[i] = ++prm[0]] = i;
    for (int j = 1, k; j <= prm[0] && (k = i * prm[j]) < M; ++j) {
      mindiv[k] = prm[j];
      if (i % prm[j] == 0) break;
    }
  }
}

struct Q {int l, r, id;} q[N];

inline bool cmp(Q x,Q y) {return x.r < y.r;}

int c[N], lst[M];

inline void mul(int p, int x) {
  for (; p <= n; p += lowbit(p)) c[p] = 1ll * c[p] * x % mod;
}

inline int prod(int p) {
  int res = 1;
  for (; p; p -= lowbit(p)) res = 1ll * res * c[p] % mod;
  return res;
}

inline void fac(int x, int p) {
  while (x != 1) {
    int nw = mindiv[x];
    if (lst[nw]) mul(lst[nw], 1ll * inv[nw - 1] * nw % mod);
    lst[nw] = p; mul(p, 1ll * inv[nw] * (nw - 1) % mod);
    while (mindiv[x] == nw) x /= nw;
  }
}

int main(){
  calc();
  n = rd(); pre[0] = 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = rd(); c[i] = 1;
    pre[i] = 1ll * pre[i - 1] * a[i] % mod;
  }
  m = rd();
  for (int i = 1; i <= m; ++i) {
    q[i].l = rd(); q[i].r = rd(); q[i].id = i;
  }
  sort(q + 1, q + 1 + m, cmp);
  for (int i = 1, ptr = 1; i <= n; ++i) {
    fac(a[i], i);
    while (q[ptr].r == i) {
      ans[q[ptr].id] = qpow(1ll * prod(q[ptr].l - 1) * pre[q[ptr].l - 1] % mod, mod - 2);
      ans[q[ptr].id] = 1ll * ans[q[ptr].id] * prod(q[ptr].r) % mod * pre[q[ptr].r] % mod;
      ++ptr;
    }
  }
  for (int i = 1; i <= m; ++i) print(ans[i]);
  return 0;
}

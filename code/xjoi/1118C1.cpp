#include <bits/stdc++.h>
#define N 200005
#define M 1000005
#define gc getchar
#define mod 998244353
#define rg register
#define mid ((l + r) >> 1)
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
  rg int y = 10, len = 1;
  while (y <= x) {y *= 10; ++len;}
  while (len--) {y /= 10; putchar(x / y + 48); x %= y;}
  putchar('\n');
}

int n, m, a[N], bl[N];

int mindiv[M], prm[M], inv[M], cnt[M];

inline void calc() {
  inv[0] = inv[1] = 1;
  for (rg int i = 2; i < M; ++i) {
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
    if (!mindiv[i]) mindiv[i] = prm[cnt[i] = ++prm[0]] = i;
    for (rg int j = 1, k; j <= prm[0] && (k = i * prm[j]) < M; ++j) {
      mindiv[k] = prm[j];
      if (i % prm[j] == 0) break;
    }
  }
}

struct Q {int l, r, id;} q[N];

inline bool cmp(Q x,Q y){
  if (bl[x.l] != bl[y.l]) return bl[x.l] < bl[y.l];
  return bl[x.l] & 1 ? x.r < y.r : x.r > y.r;
}

inline void init() {
  calc(); n = rd();
  int t = max((int)sqrt(n), 570);
  for (rg int i = 1; i <= n; ++i) {
    a[i] = rd(); bl[i] = i / t + 1;
  }
  m = rd();
  for (rg int i = 1; i <= m; ++i) {
    q[i].l = rd(); q[i].r = rd(); q[i].id = i;
  }
  sort(q + 1, q + 1 + m, cmp);
}

struct node {
  int ls, rs;
  bitset<170> w;
} c[N << 1];

int root, ptr, res = 1, mx[N], ans[N], bkt[M];

inline void fac(int x, bitset<170> &s, int &mxfac) {
  while (x != 1) {
    int nw = mindiv[x];
    mxfac = max(mxfac, nw);
    if (nw < 1000) s[cnt[nw]] = 1;
    while (mindiv[x] == nw) x /= nw;
  }
  if (mxfac < 1000) mxfac = 0;
}

void build(int &rt, int l, int r) {
  rt = ++ptr;
  if (l == r) {
    fac(a[l], c[rt].w, mx[l]);
    return;
  }
  build(c[rt].ls, l, mid);
  build(c[rt].rs, mid + 1, r);
  c[rt].w = c[c[rt].ls].w | c[c[rt].rs].w;
}

bitset<170> query(int rt, int l, int r, int L, int R) {
  if (l >= L && r <= R) return c[rt].w;
  if (R <= mid) return query(c[rt].ls, l, mid, L, R);
  if (L > mid) return query(c[rt].rs, mid + 1, r, L, R);
  return query(c[rt].ls, l, mid, L, R) | query(c[rt].rs, mid + 1, r, L, R);
}

inline void del(int x) {
  res = 1ll * res * inv[a[x]] % mod;
  if ((x = mx[x]) != 0) {
    --bkt[x];
    if (!bkt[x]) res = 1ll * res * inv[x - 1] % mod * x % mod;
  }
}

inline void ins(int x) {
  res = 1ll * res * a[x] % mod;
  if ((x = mx[x]) != 0) {
    if (!bkt[x]) res = 1ll * res * (x - 1) % mod * inv[x] % mod;
    ++bkt[x];
  }
}

int main(){
  init();
  build(root, 1, n);
  bitset<170> s;
  ins(1);
  int l = 1, r = 1;
  for (rg int i = 1, nw; i <= m; ++i) {
    while (l < q[i].l) {del(l); ++l;}
    while (l > q[i].l) {--l; ins(l);}
    while (r > q[i].r) {del(r); --r;}
    while (r < q[i].r) {++r; ins(r);}
    nw = res;
    s = query(root, 1, n, l, r);
    for (rg int j = 1; j < 170; ++j)
      if (s[j]) nw = 1ll * nw * inv[prm[j]] % mod * (prm[j] - 1) % mod;
    ans[q[i].id] = nw;
  }
  for (rg int i = 1; i <= m; ++i) print(ans[i]);
  return 0;
}

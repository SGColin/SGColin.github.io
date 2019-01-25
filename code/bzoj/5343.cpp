#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100010
#define gc getchar
#define rg register
#define mid ((l + r) >> 1)
using namespace std;
typedef long long ll;

inline ll rd() {
  rg ll x = 0;
  rg bool f = 0;
  rg char c = gc();
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

int n, m, mx;

struct D {
  int d, p, s;
} d[N];

inline bool cmp(D x, D y) { return x.d < y.d; }

int rot[N], ptr;

struct node {
  int ls, rs; ll s, w;
} c[N * 21];

void build(int &rt, int lst, int l, int r, int p, int s) {
  c[rt = ++ptr] = c[lst];
  c[rt].s += s; c[rt].w += 1ll * s * p;
  if (l == r) return;
  if (p <= mid) build(c[rt].ls, c[lst].ls, l, mid, p, s);
  else build(c[rt].rs, c[lst].rs, mid + 1, r, p, s);
}

ll query(int rt, int l, int r, ll s) {
  if (l == r) return s * l;
  if(c[c[rt].ls].s >= s) return query(c[rt].ls, l, mid, s);
  else return c[c[rt].ls].w + query(c[rt].rs, mid + 1, r, s - c[c[rt].ls].s);
}

inline void work() {
  ll w = rd(), s = rd();
  int L = 0, R = n, M;
  while (L < R) {
    M = (L + R + 1) >> 1;
    (c[rot[M]].s >= s && w >= query(rot[M], 1, mx, s)) ? L = M: R = M - 1;
  }
  printf("%d\n", L == 0 ? -1 : d[L].d);
}

int main() {
  n = rd(); m = rd();
  for (rg int i = 1; i <= n; ++i) {
    d[i].d = rd(); mx = max(mx, d[i].p = rd()); d[i].s = rd();
  }
  sort(d + 1, d + 1 + n, cmp);
  for (rg int i = n; i; --i)
    build(rot[i], rot[i + 1], 1, mx, d[i].p, d[i].s);
  while(m--) work();
  return 0;
}

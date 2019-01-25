#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 50010
#define gc getchar
#define rg register
#define mid ((l + r) >> 1)
#define inf 1000000000
using namespace std;
typedef long long ll;

inline int rd() {
  rg int x = 0;
  rg bool f = 0;
  rg char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = 1;
    c = gc();
  }
  while (isdigit(c)) {
    x = (x * 10) + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

int root, ptr;

inline int newnode(){ return ++ptr; }

struct node {
  int ls, rs, tag;
  ll sum;
} c[N << 1];

inline void build(int &rt, int l, int r) {
  rt = newnode();
  if (l == r) return;
  build(c[rt].ls, l, mid);
  build(c[rt].rs, mid + 1, r);
}

inline void pushdown(int rt, int l, int r) {
  c[c[rt].ls].sum += c[rt].tag * (mid - l + 1);
  c[c[rt].rs].sum += c[rt].tag * (r - mid);
  c[c[rt].ls].tag += c[rt].tag;
  c[c[rt].rs].tag += c[rt].tag;
  c[rt].tag = 0;
}

inline void pushup(int rt) {
  c[rt].sum = c[c[rt].ls].sum + c[c[rt].rs].sum;
}

void upd(int rt, int l, int r, int L, int R, int x) {
  if (L <= l && r <= R) {
    c[rt].tag += x;
    c[rt].sum += x * (r - l + 1);
    return;
  }
  if (c[rt].tag) pushdown(rt, l, r);
  if (L <= mid) upd(c[rt].ls, l, mid, L, R, x);
  if (R > mid) upd(c[rt].rs, mid + 1, r, L, R, x);
  pushup(rt);
}

ll querysum(int rt, int l, int r, int L, int R) {
  if (L <= l && r <= R) return c[rt].sum;
  if (c[rt].tag) pushdown(rt, l, r);
  ll sum = 0;
  if (L <= mid) sum += querysum(c[rt].ls, l, mid, L, R);
  if (R > mid) sum += querysum(c[rt].rs, mid + 1, r, L, R);
  return sum;
}

struct Q {
  int id, l, r;
  ll x;
} ql[N], qr[N], q[N];

int n, m, isq[N], ans[N];

void solve(int l, int r, int st, int ed) {
  if (st > ed) return;
  if (l == r) {
     for (rg int i = st; i <= ed; ++i)
        if (q[i].id) ans[q[i].id] = l;
     return;
  }
  int totl = 0, totr = 0;
  for (rg int i = st; i <= ed; ++i)
    if (!q[i].id) {
      if (q[i].x > mid) {
        upd(root, 1, n, q[i].l, q[i].r, 1);
        qr[++totr] = q[i];
      }
      else ql[++totl] = q[i];
    }
    else {
      ll cnt = querysum(root, 1, n, q[i].l, q[i].r);
      if (cnt >= q[i].x) qr[++totr] = q[i];
      else q[i].x -= cnt, ql[++totl] = q[i];
    }
    for (rg int i = 1; i <= totr; ++i)
      if(!qr[i].id) upd(root, 1, n, qr[i].l, qr[i].r, -1);
    for (rg int i = 1; i <= totl; ++i) q[st + i - 1] = ql[i];
    for (rg int i = 1; i <= totr; ++i) q[st + totl + i - 1] = qr[i];
    solve(l, mid, st, st + totl - 1);
    solve(mid + 1, r, st + totl, ed);
}

int main() {
  n = rd(); m = rd();
  build(root, 1, n);
  for (rg int i = 1; i <= m; ++i) {
    isq[i] = (rd() == 2);
    q[i].id = i * isq[i];
    q[i].l = rd(); q[i].r = rd(); q[i].x = rd();
  }
  solve(-n, n, 1, m);
  for (rg int i = 1; i <= m; ++i)
    if(isq[i]) printf("%d\n", ans[i]);
  return 0;
}

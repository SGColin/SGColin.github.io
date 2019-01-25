#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 500005
#define gc getchar
#define rg register
#define mid ((l + r) >> 1)
using namespace std;

inline int rd() {
  rg int x = 0;
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

int n, m, ty, lstans;

int ptr, rot[N], val[N];

struct node {
  int ls, rs, id, sum;
} c[N * 75];

inline int newnode() {return ++ptr;}

void build(int &rt, int l, int r) {
  rt = newnode();
  if(l == r) return;
  build(c[rt].ls, l, mid);
  build(c[rt].rs, mid + 1, r);
}

inline void pushup(int rt) {
  c[rt].sum = c[c[rt].ls].sum + c[c[rt].rs].sum;
}

inline void pushdown(int rt, int l, int r) {
  int ls = c[rt].ls, rs = c[rt].rs;
  c[c[rt].ls = newnode()] = c[ls];
  c[c[rt].rs = newnode()] = c[rs];
  c[c[rt].ls].sum = (mid - l + 1) * val[c[rt].id];
  c[c[rt].rs].sum = (r - mid) * val[c[rt].id];
  c[c[rt].ls].id = c[c[rt].rs].id = c[rt].id;
  c[rt].id = 0;
}

void update(int rt, int l, int r, int L, int R, int x) {
  if (L <= l && r <= R) {
    c[rt].id = x;
    c[rt].sum = val[x] * (r - l + 1);
    return;
  }
  int fl = 0, ls = c[rt].ls, rs = c[rt].rs;
  if (c[rt].id) fl = 1, pushdown(rt, l, r);
  if (L <= mid) {
    if (!fl) c[c[rt].ls = newnode()] = c[ls];
    update(c[rt].ls, l, mid, L, R, x);
  }
  if (R > mid) {
    if (!fl) c[c[rt].rs = newnode()] = c[rs];
    update(c[rt].rs, mid + 1, r, L, R, x);
  }
  pushup(rt);
}

int queryid(int rt, int l, int r, int x) {
  if (l == r) return c[rt].id;
  if (c[rt].id) pushdown(rt, l, r);
  if (x <= mid) return queryid(c[rt].ls, l, mid, x);
  else return queryid(c[rt].rs, mid + 1, r, x);
}

int querysum(int rt, int l, int r, int L, int R) {
  if (L <= l && r <= R) return c[rt].sum;
  int ans = 0;
  if (c[rt].id) pushdown(rt, l, r);
  if (L <= mid) ans += querysum(c[rt].ls, l, mid, L, R);
  if (R > mid) ans += querysum(c[rt].rs, mid + 1, r, L, R);
  return ans;
}

int main() {
  n = rd(); m = rd();
  ty = rd(); lstans = 0;
  build(rot[0], 1, n);
  for (rg int i = 1, op, l, r; i <= m; ++i) {
    op = rd();
    c[rot[i] = newnode()] = c[rot[i -1]];
    if (op == 1) {
      l = (rd() + lstans * ty) % n + 1;
      r = (rd() + lstans * ty) % n + 1;
      if (l > r) swap(l, r);
      lstans = querysum(rot[i], 1, n, l, r);
      printf("%d\n",lstans);
    }
    else if (op == 2) {
      l = (rd() + lstans * ty) % n + 1;
      int id = queryid(rot[i], 1, n, l);
      if (id) update(rot[i], 1, n, l, l, queryid(rot[id - 1], 1, n, l));
    }
    else if (op == 3) {
      l = (rd() + lstans * ty) % n + 1;
      r = (rd() + lstans * ty) % n + 1;
      if (l > r) swap(l, r);
      val[i] = rd();
      update(rot[i], 1, n, l, r, i);
    }
  }
  return 0;
}

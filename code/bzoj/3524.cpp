#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 500010
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

int rot[N], ptr;

struct node {
  int ls, rs, cnt;
}c[N << 5];

void build(int &rt, int lst, int l, int r, int x) {
  c[rt = ++ptr] = c[lst];
  ++c[rt].cnt;
  if (l == r) return;
  if (x <= mid) build(c[rt].ls, c[lst].ls, l, mid, x);
  else build(c[rt].rs, c[lst].rs, mid + 1, r, x);
}

int query(int rtl, int rtr, int l, int r, int x) {
  if (l == r) return l;
  int suml = c[c[rtr].ls].cnt - c[c[rtl].ls].cnt;
  if (suml > x) return query(c[rtl].ls, c[rtr].ls, l, mid, x);
  int sumr = c[c[rtr].rs].cnt - c[c[rtl].rs].cnt;
  if (sumr > x) return query(c[rtl].rs, c[rtr].rs, mid + 1, r, x);
  return 0;
}

int main() {
  int n = rd(), m = rd(), l, r;
  for (rg int i = 1;  i <= n; ++i) build(rot[i], rot[i-1], 1, n, rd());
  while (m--) {
    l = rd(); r = rd();
    printf("%d\n", query(rot[l - 1], rot[r], 1, n, (r - l + 1) / 2));
  }
  return 0;
}

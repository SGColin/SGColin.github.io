#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 4000005
#define gc getchar
#define ls (rt << 1)
#define rs (rt << 1 | 1)
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

int n, lstans, a[N], u[2], bl[N], tr[16][16];

struct node{int sz, len, w;} c[N << 2];

inline void init() {
  int c1, c2, c3, c4;
  for (int i = 0, a1, a2, a3, a4; i < 16; ++i) {
    a1 = ((i & 1) > 0); a2 = ((i & 2) > 0);
    a3 = ((i & 4) > 0); a4 = ((i & 8) > 0);
    for (int j = 0, b1, b2, b3, b4; j < 16; ++j) {
      b1 = ((j & 1) > 0); b2 = ((j & 2) > 0);
      b3 = ((j & 4) > 0); b4 = ((j & 8) > 0);
      c1 = ((a1 + a2 * b1) & 1);
      c2 = ((a2 * b2) & 1);
      c3 = ((a3 + a4 * b1 + b3) & 1);
      c4 = ((a4 * b2 + b4) & 1);
      tr[i][j] = c1 + (c2 << 1) + (c3 << 2) + (c4 << 3);
    }
  }
}

inline void build(int rt, int l, int r) {
  c[rt].len = r - l + 1;
  if (l == r) {bl[l] = rt; return;}
  build(ls, l, mid);
  build(rs, mid + 1, r);
}

inline bool full(int rt) {
  return (c[ls].sz + c[rs].sz == c[rt].len);
}

inline void push_back(int p, int x) {
  c[bl[p]].sz = 1;
  c[bl[p]].w = u[x];
  int rt = bl[p];
  while (full(rt >> 1)) {
    rt = rt >> 1;
    c[rt].sz = c[rt].len;
    c[rt].w = tr[c[ls].w][c[rs].w];
  }
}

void query(int rt, int l, int r, int L, int R) {
  if (l >= L && r <= R) {
    lstans = tr[lstans][c[rt].w]; return;
  }
  if (L <= mid) query(ls, l, mid, L, R);
  if (R > mid) query(rs, mid + 1, r, L, R);
}

/*
inline void print(int x, int y, int z) {
  int a1 = ((x & 1) > 0), a2 = ((x & 2) > 0);
  int a3 = ((x & 4) > 0), a4 = ((x & 8) > 0);
  printf("%d %d\n%d %d\n*\n",a1, a2, a3, a4);
  a1 = ((y & 1) > 0); a2 = ((y & 2) > 0);
  a3 = ((y & 4) > 0); a4 = ((y & 8) > 0);
  printf("%d %d\n%d %d\n=\n",a1, a2, a3, a4);
  a1 = ((z & 1) > 0); a2 = ((z & 2) > 0);
  a3 = ((z & 4) > 0); a4 = ((z & 8) > 0);
  printf("%d %d\n%d %d\n",a1, a2, a3, a4);
  puts("==========================");
}
*/

int main() {
  init();
  scanf("%d", &n);
  build(1, 1, n);
  u[0] = 12, u[1] = 15;
  int tot = 0, a1, a2;
  for (int i = 1, op, l, r; i <= n; ++i) {
    op = rd();
    if (op == 1)  {
      a[++tot] = rd() ^ lstans; push_back(tot, a[tot]);
    } else {
      l = rd(); r = rd();
      if (lstans) {l = tot - l + 1; r = tot - r + 1; swap(l, r);}
      if (l == r) {putchar('0' + (lstans = a[l])); putchar('\n');}
      else {
        lstans = 2;
        query(1, 1, n, l + 1, r);
        a1 = ((lstans & 1) > 0);
        a2 = ((lstans & 4) > 0);
        lstans = ((a[l] + a[l] * a1 + a2) & 1);
        putchar('0' + lstans); putchar('\n');
      }
    }
  }
  return 0;
}

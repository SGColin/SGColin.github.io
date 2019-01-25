#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100005
#define M 2000005
#define gc getchar
#define rg register
#define mid ((l + r) >> 1)
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
    x = x * 10 + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

int root, ptr, rot[N];

int n, m, s, mx, tot, tmp[N];

inline int newnode(){return ++ptr;}

struct node {
  ll sum;
  int ls, rs, cnt;
}c[M];

inline void pushup(int rt) {
  c[rt].sum = c[c[rt].ls].sum + c[c[rt].rs].sum;
  c[rt].cnt = c[c[rt].ls].cnt + c[c[rt].rs].cnt;
}

void build(int &rt, int lst, int l, int r, int x) {
  rt = newnode();
  c[rt].sum = c[lst].sum + x;
  c[rt].cnt = c[lst].cnt + 1;
  if (l == r) return;
  if(x <= tmp[mid]) {
    build(c[rt].ls, c[lst].ls, l, mid, x);
    if (c[lst].rs) c[rt].rs = c[lst].rs;
  }
  else {
    build(c[rt].rs, c[lst].rs, mid + 1, r, x);
    if (c[lst].ls) c[rt].ls = c[lst].ls;
  }
}

ll query(int rtl, int rtr, int l, int r, int k) {
  if (c[rtr].cnt - c[rtl].cnt <= k) return c[rtr].sum - c[rtl].sum;
  if (l == r) return (c[rtr].sum - c[rtl].sum) / (c[rtr].cnt - c[rtl].cnt) * k;
  if (c[c[rtr].rs].cnt - c[c[rtl].rs].cnt >= k)
    return query(c[rtl].rs, c[rtr].rs, mid + 1, r, k);
  ll ans = c[c[rtr].rs].sum - c[c[rtl].rs].sum;
  int cnt = c[c[rtr].rs].cnt - c[c[rtl].rs].cnt;
  return ans + query(c[rtl].ls, c[rtr].ls, l, mid, k - cnt);
}

ll ans;

void solvel(int l, int r, int L, int R){
  if (l > r) return;
  ll res = 0, tmp, ansp = 0;
  for (rg int p = L, rem; p <= R; ++p) {
    if (p == s) rem = m - (s - mid);
    else rem = m - (s - mid) * 2 - (p - s);
    if (rem <= 0) break;
    tmp = query(rot[mid - 1], rot[p], 1, tot, rem);
    if (tmp > res) { res = tmp; ansp = p;}
  }
  ans = max(ans, res);
  solvel(l, mid-1, L, ansp);
  solvel(mid + 1, r, ansp, R);
}

void solver(int l, int r, int L, int R){
  if (l > r) return;
  ll res = 0, tmp, ansp = 0;
  for (rg int p = R, rem; p >= L; --p) {
    if (p == s) rem = m - (mid - s);
    else rem = m - (mid - s) * 2 - (s - p);
    if (rem <= 0) break;
    tmp = query(rot[p - 1], rot[mid], 1, tot, rem);
    if (tmp > res) { res = tmp; ansp = p;}
  }
  ans = max(ans, res);
  solver(l, mid-1, L, ansp);
  solver(mid + 1, r, ansp, R);
}

ll findMaxAttraction(int _n, int _s, int _d, int val[]) {
  n = _n; s = _s + 1; m = _d;
  for (rg int i = 0; i < n; ++i) tmp[i + 1] = val[i];
  sort(tmp + 1, tmp + 1 + n);
  for (rg int i = 1; i <= n; ++i) {
    tmp[++tot] = tmp[i];
    while (tmp[i + 1] == tmp[i]) ++i;
  }
  for (rg int i = 0; i < n; ++i) build(rot[i + 1], rot[i], 1, tot, val[i]);
  solvel(1, s, s, n);
  solver(s, n, 1, s);
  return ans;
}

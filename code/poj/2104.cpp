#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 100005
#define gc getchar
#define rg register
#define inf 2000000000
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

int n, m, tot, ans[N];

struct queue { int id, l, r, x; } ql[N << 1], qr[N << 1], q[N << 1];

int c[N];

inline int lowbit(int x) { return x & -x; }

inline void add(int p, int x) {
  for (; p <= n; p += lowbit(p)) c[p] += x;
}

inline int sum(int p){
  int res = 0;
  for (; p; p -= lowbit(p)) res += c[p];
  return res;
}

void solve(int L, int R, int st, int ed) {
  if (st > ed) return;
  if (L == R) {
    for (rg int i = st; i <= ed; ++i)
      if (q[i].id > 0) ans[q[i].id] = L;
    return;
  }
  int mid = (L + R) >> 1;
  int totl = 0, totr = 0;
  for (rg int i = st; i <= ed; ++i)
    if (!q[i].id) {
      if (q[i].x <= mid) add(q[i].l, 1), ql[++totl] = q[i];
      else qr[++totr] = q[i];
    }
    else {
      int cnt = sum(q[i].r) - sum(q[i].l - 1);
      if (cnt >= q[i].x) ql[++totl] = q[i];
      else q[i].x -= cnt, qr[++totr] = q[i];
    }
    for (rg int i = 1; i <= totl; ++i) q[st + i - 1] = ql[i];
    for (rg int i = 1; i <= totr; ++i) q[st + totl + i - 1] = qr[i];
    for (rg int i = 1; i <= totl; ++i) if (!ql[i].id) add(ql[i].l, -1);
    solve(L, mid, st, st + totl - 1);
    solve(mid + 1, R, st + totl, ed);
}

int main() {
  n = rd(); m = rd();
  for (rg int i = 1; i <= n; ++i) {
    q[++tot].l = i; q[tot].x = rd();
  }
  for (rg int i = 1; i <= m; ++i) {
    q[++tot].l = rd(); q[tot].r = rd();
    q[tot].id = i; q[tot].x = rd();
  }
  solve(-inf, inf, 1, tot);
  for (rg int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
  return 0;
}

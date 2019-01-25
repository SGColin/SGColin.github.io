#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 510
#define M 60005
#define rg register
using namespace std;

char buf[1<<21],*p1=buf,*p2=buf;
inline int gc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}

inline int rd() {
  rg int x = 0;
  rg bool f = 0;
  rg char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = 1;
    c = gc();
  }
  while (isdigit(c)) {
    x = (x << 1) + (x << 3) + (c ^ 48);
    c = gc();
  }
  return f ? -x : x;
}

int n, m, tot, ans[M], c[N][N];

struct node{ int r,c,x; }s[N * N];

inline bool cmp(const node &x, const node &y) { return x.x < y.x; }

inline int lowbit(const int &x) { return x & -x; }

inline void add(const int &x, const int &y, const int &d) {
  for (rg int i = x; i <= n; i += lowbit(i))
    for (rg int j = y; j <= n; j += lowbit(j)) c[i][j] += d;
}

inline int sum(const int &x, const int &y) {
  int res = 0;
  for (rg int i = x; i; i -= lowbit(i))
    for (rg int j = y; j; j -= lowbit(j)) res += c[i][j];
  return res;
}

struct queue{int id, r1, c1, r2, c2, x; } q[M], ql[M], qr[M];

inline void solve(const int &L, const int &R, const int &st, const int &ed) {
  if (st > ed) return;
  if (L == R) {
    for (rg int i = st; i <= ed; ++i) ans[q[i].id] = s[L].x;
    return;
  }
  int mid = (L + R) >> 1;
  int totl = 0, totr = 0;
  for (rg int i = L; i <= mid; ++i) add(s[i].r, s[i].c, 1);
  for (rg int i = st; i <= ed; ++i) {
    int cnt = sum(q[i].r2, q[i].c2) + sum(q[i].r1 - 1, q[i].c1 - 1);
    cnt -= sum(q[i].r2, q[i].c1 - 1) + sum(q[i].r1 - 1, q[i].c2);
    if (cnt >= q[i].x) ql[++totl] = q[i];
    else q[i].x -= cnt, qr[++totr] = q[i];
  }
  for (rg int i = L; i <= mid; ++i) add(s[i].r, s[i].c, -1);
  for (rg int i = 1; i <= totl; ++i) q[st + i - 1] = ql[i];
  for (rg int i = 1; i <= totr; ++i) q[st + totl + i - 1] = qr[i];
  solve(L, mid, st, st + totl - 1);
  solve(mid + 1, R, st + totl, ed);
}

int main() {
  n = rd(); m = rd();
  for (rg int r = 1; r <= n; ++r)
    for (rg int c = 1; c <= n; ++c)
      s[++tot] = (node){ r, c, rd()};
  sort(s + 1, s + 1 + tot, cmp);
  tot = 0;
  for (rg int i = 1; i <= m; ++i) {
    q[++tot].id = i;
    q[tot].r1 = rd(); q[tot].c1 = rd();
    q[tot].r2 = rd(); q[tot].c2 = rd();
    q[tot].x = rd();
  }
  solve(1, n * n, 1, tot);
  for (rg int i = 1; i <= m; ++i) printf("%d\n",ans[i]);
  return 0;
}

#include <cmath>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 300010
#define gc getchar
#define rg register
#define inf 1000000000ll
#define lowbit(x) (x & -x)
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

vector<int> s[N];

int n, m, k, ans[N];

ll c[N];

struct Q { int id; ll x; } q[N], ql[N], qr[N];

struct W {int l, r, x; } w[N];

inline void add(int p, ll x) {
  for (; p <= m; p += lowbit(p)) c[p] = c[p] + x;
}

inline ll query(int p) {
  ll res = 0;
  for (; p; p -= lowbit(p)) res += c[p];
  return res;
}

inline void solve(int l, int r, int st, int ed) {
  if (st > ed) return;
  if (l == r) {
    for (rg int i = st; i <= ed; ++i) ans[q[i].id] = l;
    return;
  }
  int mid = (l + r) >> 1, totl = 0, totr = 0;
  for (rg int i = l; i <= mid; ++i)
    if (w[i].l <= w[i].r) { add(w[i].l, w[i].x); add(w[i].r + 1, -w[i].x); }
    else { add(1, w[i].x); add(w[i].r + 1, -w[i].x); add(w[i].l, w[i].x); }
  for (rg int i = st, id; i <= ed; ++i) {
    ll res = 0; id = q[i].id;
    for (rg int j = s[id].size() - 1; ~j; --j) res = min(res + query(s[id][j]), inf);
    if (res >= q[i].x) ql[++totl] = q[i];
    else q[i].x -= res, qr[++totr] = q[i];
  }
  for (rg int i = l; i <= mid; ++i)
    if (w[i].l <= w[i].r) { add(w[i].l, -w[i].x); add(w[i].r + 1, w[i].x); }
    else { add(1, -w[i].x); add(w[i].r + 1, w[i].x); add(w[i].l, -w[i].x); }
  for (rg int i = 1; i <= totl; ++i) q[st + i - 1] = ql[i];
  for (rg int i = 1; i <= totr; ++i) q[st + totl + i - 1] = qr[i];
  solve(l, mid, st, st + totl - 1);
  solve(mid + 1, r, st + totl, ed);
}

int main() {
  n = rd(); m = rd();
  for (rg int i = 1; i <= m; ++i) s[rd()].push_back(i);
  for (rg int i = 1; i <= n; ++i) q[i].id = i, q[i].x = rd();
  k = rd();
  for (rg int i = 1; i <= k; ++i) {
    w[i].l = rd(); w[i].r = rd(); w[i].x = rd();
  }
  w[k + 1].l = 1; w[k + 1].r = m; w[k + 1].x = inf;
  solve(1, k + 1, 1, n);
  for (rg int i = 1; i <= n; ++i) {
    if (ans[i] == k + 1) puts("NIE");
    else printf("%d\n", ans[i]);
  }
  return 0;
}

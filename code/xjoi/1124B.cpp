#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 40005
#define inf 2000000000
using namespace std;

inline int rd() {
  int x = 0;
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = getchar();
  }
  return x;
}

int n, m, mod, app[N];

inline int mo(int x) {
  return x >= mod ? x - mod : x;
}

int min_edge[256][256], mn_set[65536];

inline int Cost_set(int x, int y) {
  int res = inf;
  for (int i = 0; i < 8; ++i)
    for (int j = 0; j < 8; ++j)
      if (((x >> i) & 1) && ((y >> j) & 1)) res = min(res, i ^ j);
  return res;
}

int dis[65537], mst[65537];

inline int Prim(int x) {
  for (int i = 0; i < 16; ++i) dis[i] = inf;
  for (int i = 0; i < 16; ++i)
    if ((x >> i) & 1) {dis[i] = 0; break;}
  int ans = 0;
  while(x) {
    int mn = inf, mp;
    for (int i = 0; i < 16; ++i)
      if (((x >> i) & 1) && mn > dis[i]) mp = i, mn = dis[i];
    ans += mn; x -= (1 << mp);
    for (int i = 0; i < 16; ++i)
      if ((x >> i) & 1) dis[i] = min(dis[i], mp ^ i);
  }
  return ans;
}

int ptr = 0, f[16][N];

struct node{
  int s, ans, ls, rs;
  node(int _s = 0, int _ans = 0, int _ls = 0, int _rs = 0) {
    s = _s; ans = _ans; ls = _ls; rs = _rs;
  }
} c[N << 5];

inline void Build(int len) {
  for (int i = 0; i < len; ++i)
    if (app[i]) f[0][i] = ++ptr, c[ptr] = node(1, -1, 0, 0);
  for (int j = 1, k = 1; k < len; ++j, k <<= 1)
    for (int i = 0, ls, rs; i + k < len; ++i) {
      ls = f[j - 1][i];
      rs = f[j - 1][i + k];
      if (!ls && !rs) continue;
      f[j][i] = ++ptr;
      c[ptr] = node(((c[rs].s << k) | c[ls].s), -1, ls, rs);
    }
}

inline int Min_edge(int rt1, int rt2, int len) {
  if (!rt1 || !rt2) return inf;
  if (len == 8) return min_edge[c[rt1].s][c[rt2].s];
  int res = inf, sonlen = len >> 1;
  res = min(res, Min_edge(c[rt1].ls, c[rt2].ls, sonlen));
  res = min(res, Min_edge(c[rt1].rs, c[rt2].rs, sonlen));
  if (res < inf) return res;
  res = min(res, Min_edge(c[rt1].ls, c[rt2].rs, sonlen) + sonlen);
  res = min(res, Min_edge(c[rt1].rs, c[rt2].ls, sonlen) + sonlen);
  return res;
}

int Mst(int rt, int len) {
  if (c[rt].ans != -1) return c[rt].ans;
  if (len <= 16) return c[rt].ans = mst[c[rt].s];
  int sonlen = len >> 1;
  if (!c[rt].ls) return c[rt].ans = Mst(c[rt].rs, sonlen);
  if (!c[rt].rs) return c[rt].ans = Mst(c[rt].ls, sonlen);
  c[rt].ans = Mst(c[rt].ls, sonlen) + Mst(c[rt].rs, sonlen);
  c[rt].ans += Min_edge(c[rt].ls, c[rt].rs, sonlen) + sonlen;
  return c[rt].ans;
}

int main() {
  n = rd(); m = rd(); mod = (1 << m);
  for (int i = 1, x; i <= n; ++i) {
    x = rd(); app[x] = app[x + mod] = 1;
  }
  for (int i = 1; i < 256; ++i)
    for (int j = 1; j < 256; ++j) min_edge[i][j] = Cost_set(i, j);
  for (int i = 1; i < 65536; ++i) mst[i] = Prim(i);
  Build(mod << 1);
  int q = rd(), dlt = 0;
  for (int i = 1; i <= q; ++i) {
    dlt = mo(dlt + mod - rd());
    printf("%d\n", mod <= 16 ? mst[c[f[m][dlt]].s] : Mst(f[m][dlt], mod));
  }
  return 0;
}

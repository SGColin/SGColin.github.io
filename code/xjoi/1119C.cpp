#pragma GCC optimize(2)
#include <cmath>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 205, M = 200005, mod = 998244353;

inline int rd() {
  int x = 0;
  char c = getchar();
  while (!isdigit(c)) c = getchar();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = getchar();
  }
  return x;
}

inline int mo(int x) {return x >= mod ? x - mod : x;}

int n, m, Q, a[M], ans[M], sum[N], tag[N], s[N][N];

struct node{int c, d, id;};

vector<node> q[M];

inline void ins(int k) {
  for (int j = 0, dlt; j <= m; ++j) {
    dlt = mo(s[k][j] + tag[j]);
    tag[j] = mo(tag[j] + dlt);
    s[k][j] = mo(s[k][j] + mod - dlt);
  }
  for (int i = 0; i <= m; ++i)
    if (i != k) sum[i] = mo(sum[i] + sum[k]);
}

inline void del(int k) {
  for (int i = 0, dlt; i <= m; ++i) {
    dlt = mo(mo(s[i][k] + tag[k] - sum[i] + mod));
    s[i][k] = mo(s[i][k] + dlt);
    sum[i] = mo(sum[i] + dlt);
  }
}

inline int query(int c, int d) {
  return mo(mo(s[c][d] + s[0][d]) + mo(tag[d] << 1));
}

int main() {
  n = rd(); m = rd(); Q = rd();
  for (int i = 1; i <= n; ++i) a[i] = rd();
  for (int i = 1, p, c, d; i <= Q; ++i) {
    p = rd(); c = rd(); d = rd();
    q[p].push_back((node){c, d, i});
  }
  for (int i = 0; i <= m; ++i) s[i][i] = sum[i] = 1;
  for (int i = n - 1; i; --i) ins(a[i]);
  for (int i = n; i; --i) {
    for (int j = 0, lim = q[i].size(); j < lim; ++j)
      ans[q[i][j].id] = query(q[i][j].c, q[i][j].d);
    if (i) {del(a[i - 1]); ins(a[i]);}
  }
  for (int i = 1; i <= Q; ++i) printf("%d\n", ans[i]);
  return 0;
}
